# Système de Contrôle d'Éclairage Intelligent avec Zigbee

Ce projet implémente un système de contrôle d'éclairage intelligent utilisant des dispositifs Zigbee, un Raspberry Pi, et Node-RED pour la visualisation et le contrôle.

## 🎯 Objectifs
- Mettre en place un système de contrôle d'éclairage avec multiples dispositifs
- Utiliser le protocole Zigbee pour la communication sans fil
- Créer une interface de contrôle avec Node-RED
- Implémenter un contrôle via MQTT

## 📋 Matériel Requis

- Raspberry Pi
- Dongle USB/Zigbee (au choix) :
  - Sonoff Zigbee 3.0 ([Lien](https://amz.run/6LG0))
  - CC2531 avec firmware pour zigbee2mqtt ([Lien](https://amz.run/6LFw))
- Switch IKEA E1524
- Spot LED IKEA
- Contrôleur LED Strip TuYa
- Bandeau LED

## 🛠️ Installation

### 1. Node-RED
```bash
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

### 2. Broker Mosquitto
```bash
sudo apt update
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto.service
```

Configuration de Mosquitto (`/etc/mosquitto/mosquitto.conf`):
```
listener 1883
allow_anonymous true
```

### 3. Zigbee2mqtt

1. Créer le dossier d'installation :
```bash
sudo mkdir /opt/zigbee2mqtt
sudo chown -R ${USER}: /opt/zigbee2mqtt
```

2. Cloner le dépôt :
```bash
git clone --depth 1 https://github.com/Koenkk/zigbee2mqtt.git /opt/zigbee2mqtt
```

3. Installer les dépendances :
```bash
cd /opt/zigbee2mqtt
npm ci
```

## ⚙️ Configuration

### Configuration Zigbee2mqtt

Fichier de configuration (`/opt/zigbee2mqtt/data/configuration.yaml`) :
```yaml
homeassistant: false
permit_join: true
mqtt:
  base_topic: zigbee2mqtt
  server: mqtt://localhost
serial:
  port: /dev/ttyACM0  # ou /dev/ttyUSB0
advanced:
  network_key: GENERATE
frontend: true
```

## 🔄 Fonctionnalités Dashboard

### Switch IKEA
- Bouton central : ON/OFF des lampes
- Boutons haut/bas : Réglage de la luminosité
- Boutons droite/gauche : Sélection des lampes (spot ou LED)
- Affichage de la sélection de lampe

### Contrôle LED
- Color picker pour la sélection de la couleur
- Contrôle de la luminosité
- État ON/OFF

## 📡 Commandes MQTT

### Spot IKEA GU10
```bash
# Allumer la lampe
mosquitto_pub -h localhost -t zigbee2mqtt/IKEA_GU10/set -m '{"state":"ON"}'

# Régler la luminosité
mosquitto_pub -h localhost -t zigbee2mqtt/IKEA_GU10/set -m '{"state":"ON","brightness": 120}'

# Effet de transition
mosquitto_pub -h localhost -t zigbee2mqtt/IKEA_GU10/set -m '{"brightness":220,"transition": 30}'

# Effet spécial
mosquitto_pub -h localhost -t zigbee2mqtt/IKEA_GU10/set -m '{"effect":"breathe"}'
```

## 🌐 Configuration HiveMQ Cloud (Optionnel)

1. Créer un compte sur [HiveMQ Cloud](https://console.hivemq.cloud)
2. Créer un cluster
3. Configurer le fichier `/opt/zigbee2mqtt/data/configuration.yaml` avec les informations HiveMQ :
```yaml
mqtt:
  base_topic: zigbee2mqtt
  server: mqtts://xxxxx.hivemq.cloud:8883
  user: votre_utilisateur
  password: votre_mot_de_passe
```

## 📁 Structure du Projet

- `configuration.yaml` : Configuration Zigbee2mqtt
- `node-red-flows/` : Flux Node-RED
- `functions/` : Code JavaScript des fonctions Node-RED
  - `function12.js` : Gestion des commandes de lampes
  - `function13.js` : Traitement des sélections
  - `function14.js` : Gestion des couleurs LED

## 🔧 Dépannage

1. Vérifier que tous les services sont en cours d'exécution :
```bash
systemctl status nodered
systemctl status mosquitto
```

2. Vérifier les logs Zigbee2mqtt :
```bash
cd /opt/zigbee2mqtt
npm start
```

## 📚 Documentation

- [Documentation Zigbee2mqtt](https://www.zigbee2mqtt.io/)
- [Documentation Node-RED](https://nodered.org/docs/)
- [Documentation Mosquitto](https://mosquitto.org/documentation/)
- [HiveMQ Cloud Documentation](https://www.hivemq.com/docs/hivemq-cloud/)

## ⚠️ Notes Importantes

- Les dispositifs doivent être appairés avant utilisation
- La configuration du PAN ID doit être unique pour éviter les interférences
- Les mots de passe HiveMQ doivent être conservés de manière sécurisée
- Le Dashboard Node-RED doit être configuré après l'installation des dispositifs

## 📖 Références

Formation IOT originale