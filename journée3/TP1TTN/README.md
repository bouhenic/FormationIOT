# TP1 Arduino MKR1310 sur le Réseau LoRaWAN TTN

## Objectifs

- Créer un compte d'accès au réseau LoRaWAN TTN (The Things Network).
- Connecter la carte Arduino MKR1310 LoRa au réseau TTN.
- Transmettre (uplink) et recevoir (downlink) des données via le réseau TTN.
- Comprendre la classe A pour la réception des données (downlink).
- Utiliser MQTT pour les communications uplink et downlink.
- Mesurer et transmettre la température et l'humidité avec un capteur DHT22.
- Déployer un dashboard sur Node-RED.

---

## Prérequis

- Compte sur [The Things Network](https://thethingsnetwork.org).
- **Arduino IDE** installé.
- **Docker** pour Node-RED.
- Bibliothèques Arduino : `MKRWAN`, `DHT`.

---

## 1. Création du Compte TTN

1. Connectez-vous sur [The Things Network](https://thethingsnetwork.org).
2. Cliquez sur **Sign Up** et suivez les instructions.
3. Sélectionnez le cluster **Europe**.
4. Créez votre première application.
   - Remplissez les champs requis (utilisez des minuscules pour l'ID de l'application).

---

## 2. Connexion de la Carte Arduino MKR1310

### 2.1 Configuration de l'IDE Arduino

1. Connectez la carte Arduino MKR1310 et lancez l'IDE Arduino.
2. Vérifiez que la carte est reconnue (**Outils > Type de carte**).
3. Vérifiez les ports.
4. Chargez le sketch : `Examples/MKRWAN/FirstConfiguration`.
5. Téléversez le programme et copiez le **DevEUI** affiché.

### 2.2 Enregistrement du Device sur TTN

1. Connectez-vous à TTN et enregistrez un **End Device**.
2. Choisissez :
   - **Marque** : Arduino SA
   - **Modèle** : MKR WAN
   - **Version hardware** : 1.0
   - **Version firmware** : 1.2.3
   - **Profile** : EU_863_870
3. Plan de fréquence : **SF9 for RX2**.
4. **Join EUI (App EUI)** : `00 00 00 00 00 00 00 00`
5. **DevEUI** : Valeur copiée depuis l'IDE Arduino.
6. Générez l'**AppKey** et validez.

### 2.3 Configuration OTAA dans l'IDE Arduino

1. Sélectionnez la méthode **OTAA**.
2. Recopiez l'**App EUI** (`0000000000000000`) et l'**App Key** générée sur TTN.
3. Vérifiez que le message **"message sent correctly"** apparaît.
4. Le message reçu apparaît dans l'onglet **Live Data** sur TTN.

### 2.4 Décodage des Données

Utilisez un script JavaScript dans **Payload Formatters** pour décoder les données :

```javascript
function Decoder(bytes, port) {
  var result = "";
  for (var i = 0; i < bytes.length; i++) {
    result += String.fromCharCode(parseInt(bytes[i]));
  }
  return { payload: result };
}
```

---

## 3. Transfert de Données Uplink et Downlink

### 3.1 Envoi de Données (Uplink)

1. Ouvrez le sketch `LoraSendAndReceive.ino`.
2. Configurez le fichier `arduino_secrets.h` avec l'**App EUI** et l'**App Key**.
3. Téléversez le sketch et vérifiez la réception dans **Live Data**.

### 3.2 Réception de Données (Downlink)

1. Dans TTN, allez dans l'onglet **Downlink**.
2. Programmez un message (ex: `AA`).
3. Envoyez un message uplink depuis l'Arduino pour déclencher le downlink.
4. Vérifiez la réception sur le device.

---

## 4. Communication via MQTT

### 4.1 Réception (Uplink)

1. Générez une API Key sur TTN pour l'authentification.
2. Utilisez la commande suivante pour s'abonner aux messages uplink :

```bash
mosquitto_sub -h eu1.cloud.thethings.network -p 8883 \
-u "<username>" -P "<API_KEY>" \
-t 'v3/<application_id>/devices/<device_id>/up'
```

### 4.2 Envoi (Downlink)

1. Utilisez la commande suivante pour publier un message :

```bash
mosquitto_pub -h eu1.cloud.thethings.network -p 8883 \
-u "<username>" -P "<API_KEY>" \
-t 'v3/<application_id>/devices/<device_id>/down/replace' \
-m '{"downlinks":[{"f_port":1,"frm_payload":"AQ=="}]}'
```

`AQ==` en base64 correspond à `01` en hexadécimal.

---

## 5. Mesure de Température et d'Humidité avec un Capteur DHT22

### 5.1 Sketch Arduino

```cpp
#include <MKRWAN.h>
#include "DHT.h"

LoRaModem modem;
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char *appEui = "0000000000000000";
const char *appKey = "<votre_appkey>";

void setup() {
  Serial.begin(115200);
  dht.begin();
  if (!modem.begin(EU868)) { Serial.println("Erreur modem"); while (1); }
  if (!modem.joinOTAA(appEui, appKey)) { Serial.println("Erreur connexion"); while (1); }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) { Serial.println("Erreur capteur"); return; }
  byte payload[4] = {(uint16_t)(humidity*100)>>8, (uint16_t)(humidity*100)&0xFF, (uint16_t)((temperature+100)*100)>>8, (uint16_t)((temperature+100)*100)&0xFF};
  modem.beginPacket(); modem.write(payload, 4); modem.endPacket(true);
  delay(240000);
}
```

### 5.2 Décodage sur TTN

Utilisez un script JavaScript pour décoder les données :

```javascript
function Decoder(bytes, port) {
  var humidity = ((bytes[0] << 8) | bytes[1]) / 100;
  var temperature = (((bytes[2] << 8) | bytes[3]) / 100) - 100;
  return { humidity: humidity, temperature: temperature };
}
```

---

## 6. Déploiement d'un Dashboard sur Node-RED

### 6.1 Installation de Node-RED via Docker

```bash
docker run -it -p 1880:1880 -v node_red_data:/data --name mynodered nodered/node-red:latest
```

### 6.2 Configuration de Node-RED

1. Ajoutez un nœud **MQTT In** et configurez-le avec le serveur TTN.
2. Activez la connexion **SSL/TLS** (port 8883).
3. Utilisez votre **API Key** comme mot de passe.
4. Utilisez un nœud **JSON** pour convertir les données en objet JavaScript.
5. Utilisez des nœuds **Gauge** pour afficher la température et l'humidité.

---

## Ressources Utiles

- [The Things Network Documentation](https://www.thethingsnetwork.org/docs/)
- [Arduino MKRWAN Library](https://www.arduino.cc/en/Guide/MKRWANLibrary)
- [Node-RED Documentation](https://nodered.org/docs/)

---

## Auteurs

Ce TP a été réalisé dans le cadre de la **Formation IoT LoRaWAN** au **Lycée Newton**, Clichy, France.

