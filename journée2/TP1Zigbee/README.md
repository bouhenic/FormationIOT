# Système d'Irrigation Intelligent avec Zigbee

Ce projet implémente un système d'irrigation intelligent utilisant des dispositifs Zigbee, un Raspberry Pi, et Node-RED pour la visualisation et le contrôle.

## 🎯 Objectifs
- Mettre en place un système d'irrigation automatisé
- Utiliser le protocole Zigbee pour la communication sans fil
- Créer une interface de contrôle avec Node-RED

## 📋 Matériel Requis

- Raspberry Pi
- Dongle USB/Zigbee (au choix) :
  - Sonoff Zigbee 3.0
  - CC2531 avec firmware pour zigbee2mqtt
- Capteur d'humidité du sol TuYa 0601_soil
- Électrovanne d'irrigation GiEX QT06_2

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

## 📊 Interface Web

- Interface Zigbee2mqtt : `http://<IP_RASPBERRY>:8080`
- Interface Node-RED : `http://<IP_RASPBERRY>:1880`

## 🔄 Fonctionnalités

### Dashboard Node-RED
Le dashboard affiche :

#### Capteur d'humidité
- Niveau de batterie
- Humidité du sol
- Température

#### Électrovanne
- Niveau de batterie
- État (ON/OFF)
- Eau consommée
- Mode de fonctionnement
- Durée d'arrosage
- Temps de début/fin d'arrosage

### Commandes MQTT

Exemples de commandes pour l'électrovanne :
```bash
# Contrôle de l'état
mosquitto_pub -h localhost -t zigbee2mqtt/Valve/set -m '{"state":"OFF"}'

# Configuration du mode
mosquitto_pub -h localhost -t zigbee2mqtt/Valve/set -m '{"mode":"duration"}'

# Réglage de la durée d'arrosage
mosquitto_pub -h localhost -t zigbee2mqtt/Valve/set -m '{"irrigation_target":60}'
```

## 📁 Structure du Projet

- `configuration.yaml` : Configuration Zigbee2mqtt
- `node-red-flows/` : Flux Node-RED
- `functions/` : Code JavaScript des fonctions Node-RED
  - `function4.js` : Gestion de l'état du switch
  - `function5.js` : Configuration du mode
  - `function7.js` : Traitement des données
  - `extractSoilSensor.js` : Extraction des données du capteur

## 📚 Documentation

- [Documentation Zigbee2mqtt](https://www.zigbee2mqtt.io/)
- [Documentation Node-RED](https://nodered.org/docs/)
- [Documentation Mosquitto](https://mosquitto.org/documentation/)

## 📝 Notes

- Le système utilise MQTT pour la communication entre les composants
- L'interface web Zigbee2mqtt permet la gestion des dispositifs
- Le dashboard Node-RED fournit une interface utilisateur conviviale
- Les dispositifs peuvent être contrôlés via MQTT ou l'interface web

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

## 📖 Références

Formation IOT originale par François Riotte
