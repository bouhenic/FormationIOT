# TP2 - Contrôle de Lumières IoT avec Zigbee et Node-RED

Mise en place d'une interface de contrôle pour une ampoule et un bandeau LED via Zigbee et Node-RED.

## Matériel Requis

- Raspberry Pi
- Dongle USB/Zigbee (Sonoff Zigbee 3.0 ou CC2531)
- Switch IKEA E1524
- Spot LED IKEA 
- Contrôleur LED Strip TuYa
- Bandeau LED

## Installation

1. **Node-RED**
```bash
bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
```

2. **Mosquitto**
```bash
sudo apt update
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto.service
```

3. **Zigbee2MQTT**
```bash
sudo mkdir /opt/zigbee2mqtt
sudo chown -R ${USER}: /opt/zigbee2mqtt
git clone --depth 1 https://github.com/Koenkk/zigbee2mqtt.git /opt/zigbee2mqtt
cd /opt/zigbee2mqtt
npm start
```

## Configuration

1. **Mosquitto** : Éditer `/etc/mosquitto/mosquitto.conf`
```
listener 1883
allow_anonymous true
```

2. **Zigbee2MQTT** : Configurer `/opt/zigbee2mqtt/data/configuration.yaml`
- Base topic : zigbee2mqtt
- Port série : /dev/ttyUSB0 ou /dev/ttyACM0
- PAN ID : 675X (X = numéro de groupe)
- Channel : 11-26

## Interface

### Télécommande
- Boutons haut/bas : ON/OFF
- Boutons gauche/droite : Sélection de lampe

### Dashboard
- Color picker pour LED Strip
- Slider de luminosité
- Affichage de la lampe sélectionnée

## Interface Web

Accessible sur : `http://<IP_RASPBERRY>:8080`

## Test MQTT

```bash
# Allumer l'ampoule
mosquitto_pub -h localhost -t zigbee2mqtt/ampoule/set -m '{"state":"ON"}'

# Définir la luminosité
mosquitto_pub -h localhost -t zigbee2mqtt/ampoule/set -m '{"state":"ON","brightness": 120}'
```
