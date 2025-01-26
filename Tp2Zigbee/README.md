# TP2 Zigbee - Formation IoT

Ce dépôt contient les ressources pour le TP2 sur la mise en place d'un réseau Zigbee avec MQTT.

## Contenu

- `ConfigurationTp2.yaml` : Configuration Zigbee2MQTT
- `function1.js` : Node-RED fonction pour contrôle des lumières
- `TP2Zigbee.pdf` : Guide détaillé du TP

## Configuration Zigbee2MQTT

```yaml
mqtt:
  base_topic: zigbee2mqtt
  server: mqtt://localhost
serial:
  port: /dev/ttyUSB0
advanced:
  pan_id: 6753  # 675X où X est le numéro du groupe
  channel: 13   # Entre 11 et 26
```

## Fonction Node-RED

La fonction JavaScript (`function1.js`) gère :
- Sélection de lampes (gauche/droite)
- Contrôle de luminosité
- Gestion des couleurs pour la bande LED
- Commandes ON/OFF

## Démarrage

1. Configurer Zigbee2MQTT avec `ConfigurationTp2.yaml`
2. Importer la fonction dans Node-RED
3. Connecter les périphériques Zigbee

## Liste des périphériques autorisés

```yaml
passlist:
  - '0xa4c138de63548d15'
  - '0x90fd9ffffe14c33d'
  - '0xd0cf5efffe18cb8c'
```