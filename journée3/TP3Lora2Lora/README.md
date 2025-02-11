# TP3 Transmission LoRa Pair à Pair avec Arduino MKR1310

## Objectifs

- Faire communiquer plusieurs équipements LoRa entre eux.
- Ajuster les caractéristiques des émetteurs et récepteurs pour éviter les interférences dans une zone.

---

## Matériel Utilisé

- 2 cartes **Arduino MKR 1310**.
- Bibliothèques :
  - `LoRa` (de **Sandeep Mistry**).
  - `Crypto`.

---

## 1. Configuration des Paramètres

Chaque binôme doit configurer sa fréquence et son facteur d'étalement (**Spreading Factor**) selon le tableau ci-dessous :

| Binôme | Fréquence (Hz) | Spreading Factor |
|---------|-----------------|------------------|
| 1       | 867100000       | 7                |
| 2       | 867100000       | 8                |
| 3       | 867500000       | 7                |
| 4       | 867500000       | 8                |
| 5       | 867900000       | 7                |
| 6       | 867900000       | 8                |
| 7       | 868300000       | 7                |
| 8       | 868300000       | 8                |

---

## 2. Mise en Place de la Communication

### 2.1 Élève 1 : Configuration de l'émetteur

1. Lancez l'IDE Arduino et choisissez **Arduino SAMD Boards / Arduino MKR WAN 1310**.
2. Installez les bibliothèques `LoRa` et `Crypto`.
3. Créez un fichier `LoRaSender.ino` avec le contenu suivant :

```cpp
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation de l'émetteur LoRa...");

  if (!LoRa.begin(867.5E6)) { // Remplacer par votre fréquence
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(7); // Remplacer par votre SF
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setTxPower(14);

  Serial.println("LoRa prêt !");
}

void loop() {
  Serial.println("Envoi du message...");
  LoRa.beginPacket();
  LoRa.print("Hello LoRa !");
  LoRa.endPacket();
  delay(2000);
}
```
4. Téléversez le programme sur la carte.

---

### 2.2 Élève 2 : Configuration du Récepteur

1. Lancez l'IDE Arduino et choisissez **Arduino SAMD Boards / Arduino MKR WAN 1310**.
2. Installez les bibliothèques `LoRa` et `Crypto`.
3. Créez un fichier `LoRaReceiver.ino` avec le contenu suivant :

```cpp
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation du récepteur LoRa...");

  if (!LoRa.begin(867.1E6)) { // Remplacer par votre fréquence
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(7); // Remplacer par votre SF
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Message reçu : ");
    while (LoRa.available()) {
      char message = (char)LoRa.read();
      Serial.print(message);
    }
    Serial.println();
  }
}
```
4. Téléversez le programme sur la carte.

---

## 3. Expérimentations

### 3.1 Observation de la Communication

1. Ouvrez le **Moniteur Série** sur les deux cartes pour vérifier la transmission des messages.
2. Notez le comportement du récepteur.

### 3.2 Modification du Spreading Factor

1. Changez le **Spreading Factor** de l'émetteur en ajoutant 2 (par ex. de 7 à 9).
2. Téléversez et observez le récepteur. Le message ne devrait plus être reçu.
3. Ajustez le **Spreading Factor** du récepteur pour qu'il corresponde à celui de l'émetteur et téléversez. Le message devrait être reçu à nouveau.
4. **Conclusion** : Le **Spreading Factor** doit être identique sur l'émetteur et le récepteur pour une communication correcte.

### 3.3 Modification de la Fréquence

1. Modifiez la fréquence de l'émetteur en ajoutant 200 kHz (par ex. de 867.100.000 à 867.300.000).
2. Téléversez et observez le récepteur. Le message ne devrait plus être reçu.
3. Ajustez la fréquence du récepteur pour qu'elle corresponde à celle de l'émetteur et téléversez. Le message devrait être reçu à nouveau.
4. **Conclusion** : La fréquence doit être identique sur l'émetteur et le récepteur pour une communication correcte.

---

## 4. Généralisation

### 4.1 Nombre de Canaux Disponibles

- Les fréquences utilisables sont comprises entre **867.1 MHz** et **868.5 MHz** par paliers de **200 kHz**.
- **Nombre de canaux** :

```math
\frac{868.5 - 867.1}{0.2} + 1 = 8 \text{ canaux}
```

### 4.2 Nombre d'Émetteurs/Récepteurs Simultanés

- Spreading Factors disponibles : **SF7 à SF12** (6 valeurs).
- Chaque canal peut utiliser ces 6 SF différents.

**Nombre total d'émetteurs/récepteurs sans interférence** :

```math
8 \text{ canaux} \times 6 \text{ SF} = 48 \text{ paires possibles}
```

### 4.3 Limitation de l'Émission sur le Réseau LoRaWAN

- Réglementation : Les émetteurs ne doivent pas émettre plus de **1% du temps**.
- En utilisant tous les canaux et SF disponibles, on peut estimer le **nombre théorique d'émetteurs** supportés dans une même zone.

---

## Ressources Utiles

- [Bibliothèque LoRa de Sandeep Mistry](https://github.com/sandeepmistry/arduino-LoRa)
- [Documentation Arduino MKR WAN 1310](https://www.arduino.cc/en/Guide/MKRWAN1300)

---

## Auteurs

Ce TP a été réalisé dans le cadre de la **Formation IoT LoRaWAN** au **Lycée Newton**, Clichy, France.

