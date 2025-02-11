# TP2 Serveur LoRaWAN ChirpStack

## Objectifs

- Installer et configurer un serveur LoRaWAN privé avec ChirpStack.
- Configurer une passerelle LoRaWAN.
- Enregistrer et gérer un device sur le serveur privé.

---

## Prérequis

- **Docker** : [Installation Docker](https://docs.docker.com/engine/install/)
- **Docker Compose** : [Installation Docker Compose](https://docs.docker.com/compose/install/)
- **Git** pour cloner les dépôts.

---

## 1. Installation du Serveur ChirpStack

### 1.1 Clonage du projet ChirpStack Docker

```bash
git clone https://github.com/chirpstack/chirpstack-docker.git
cd chirpstack-docker
```

### 1.2 Installation avec Docker et Docker Compose

1. Lancer les conteneurs Docker :
   ```bash
   docker-compose up
   ```

2. Vérifier que les conteneurs sont créés :
   ```bash
   docker ps
   ```

Les principaux services :
- **Gateway Bridge** écoute sur `1700/udp`
- **Application Server** accessible via `http://localhost:8080`

### 1.3 Importation des profils de devices

```bash
make import-lorawan-devices
```

---

## 2. Configuration de la Passerelle

1. Connectez-vous à la passerelle :
   - URL : `gatewayX.local`
   - Identifiants : `root/dragino`

2. Configurez l'adresse IP du serveur ChirpStack et le port `1700` dans l'onglet **LoRaWAN/LoRaWAN Semtech UDP**.

---

## 3. Configuration de ChirpStack

1. Accédez à l'interface web via : `http://@IP-ChirpStack:8080`
   - **Nom d'utilisateur** : `admin`
   - **Mot de passe** : `admin`

2. Ajoutez votre passerelle :
   - Nom : *[Nom de la passerelle]*
   - EUI : *[EUI trouvé sur l'interface de la passerelle]*

---

## 4. Création de la Première Application

### 4.1 Création de l'application

1. Ajoutez une nouvelle application via l'interface.

### 4.2 Création du Device Profile

1. Importez un template (ex : Arduino MKR WAN 1310 en fréquence européenne).
2. Configurez la région et vérifiez que l'OTAA est activé.

---

## 5. Enregistrement du Device

### 5.1 Récupération du DevEUI

1. Connectez la carte Arduino MKR 1310 et ouvrez l'IDE Arduino.
2. Chargez le sketch `FirstConfiguration` depuis `Examples/MKRWAN`.
3. Téléversez le sketch et copiez le DevEUI affiché.

### 5.2 Ajout du Device sur ChirpStack

1. Créez un nouveau device :
   - **Nom** : *[Nom du device]*
   - **Device Profile** : *[Profil créé]*
   - **DevEUI** : *[EUI récupéré]*
   - **JoinEUI (AppEUI)** : `00 00 00 00 00 00 00 00`

2. Générez l'**AppKey** et copiez-la.

### 5.3 Configuration de l'OTAA dans l'IDE Arduino

1. Saisissez l'AppEUI et l'AppKey dans le sketch Arduino.
2. Téléversez le programme et vérifiez la connexion OTAA dans l'onglet **LoRaWAN Frames**.

---

## 6. Réception de Données sur le Serveur ChirpStack

### 6.1 Envoi de Données depuis le Device

1. Ouvrez le sketch `LoraSendAndReceive.ino`.
2. Configurez le fichier `arduino_secrets.h` avec l'AppEUI et l'AppKey.
3. Téléversez le sketch et vérifiez les messages dans l'onglet **Events**.

### 6.2 Transmission de Données depuis le Serveur (Downlink)

1. Accédez à l'onglet **Queue** dans l'interface ChirpStack.
2. Programmez un message en base64, par exemple `SGVsbG8gTG9yYQ==` ("Hello Lora").
3. Vérifiez la réception sur le device.

---

## 7. Uplink et Downlink via MQTT

### 7.1 Réception (Uplink)

1. Abonnez-vous au topic MQTT depuis un terminal :
   ```bash
   mosquitto_sub -h <IP_serveur> -t "application/<app_id>/device/<dev_eui>/event/up"
   ```
2. Envoyez un message depuis l'Arduino et vérifiez la réception.

### 7.2 Envoi (Downlink)

1. Publiez un message vers le device :
   ```bash
   mosquitto_pub -h <IP_serveur> -t "application/<app_id>/device/<dev_eui>/command/down" \
   -m '{"devEui": "<dev_eui>", "confirmed": false, "fPort": 10, "data": "AQ=="}'
   ```
2. Vérifiez que le message est reçu par le device.

---

## Ressources Utiles

- [Documentation ChirpStack](https://www.chirpstack.io/docs/)
- [Installation Docker](https://docs.docker.com/engine/install/)
- [Installation Docker Compose](https://docs.docker.com/compose/install/)

---

## Auteurs

Ce TP a été réalisé dans le cadre de la **Formation IoT LoRaWAN** au **Lycée Newton**, Clichy, France.

