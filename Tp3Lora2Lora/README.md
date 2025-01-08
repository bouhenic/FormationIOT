# TP Communication LoRa Arduino

Ce TP permet d'explorer la communication entre équipements LoRa en utilisant des cartes Arduino MKR WAN 1310.

## 🎯 Objectifs

- Établir une communication entre plusieurs équipements LoRa
- Configurer et optimiser les paramètres de communication (fréquence, facteur d'étalement) pour éviter les interférences
- Comprendre l'impact des différents paramètres sur la communication

## 📋 Prérequis

### Matériel
- 2 cartes Arduino MKR WAN 1310 par binôme
- Câbles USB pour la programmation

### Logiciel
- Arduino IDE
- Bibliothèques requises :
  - LoRa by Sandeep Mistry
  - Crypto

## 🛠️ Configuration

Le TP utilise différentes configurations selon les binômes :

| Binôme | Fréquence (Hz) | Facteur d'étalement |
|--------|----------------|---------------------|
| 1      | 867100000      | 7                  |
| 2      | 867100000      | 8                  |
| 3      | 867500000      | 7                  |
| 4      | 867500000      | 8                  |
| 5      | 867900000      | 7                  |
| 6      | 867900000      | 8                  |
| 7      | 868300000      | 7                  |
| 8      | 868300000      | 8                  |

## 📝 Structure du TP

### Partie 1 : Configuration de l'émetteur
- Configuration de la carte Arduino MKR WAN 1310
- Installation des bibliothèques nécessaires
- Programmation de l'émetteur avec les paramètres spécifiques au binôme

### Partie 2 : Configuration du récepteur
- Configuration identique de la carte Arduino
- Programmation du récepteur avec les paramètres correspondants
- Tests de communication

### Partie 3 : Expérimentations
- Modification des paramètres (Spreading Factor, fréquence)
- Analyse des impacts sur la communication
- Compréhension des contraintes du réseau LoRaWAN

## 📚 Fichiers du projet

- `LoRaSender.ino` : Code pour la carte émettrice
- `LoRaReceiver.ino` : Code pour la carte réceptrice

## 🔍 Points clés d'apprentissage

- Importance de la synchronisation des paramètres entre émetteur et récepteur
- Impact du facteur d'étalement sur la communication
- Gestion des fréquences pour éviter les interférences
- Calcul de la capacité théorique du réseau

## 🌐 Spécifications techniques

- Fréquences utilisables : 867.1MHz à 868.5MHz (par palier de 200kHz)
- Facteurs d'étalement disponibles : SF7 à SF12
- Puissance d'émission : 14 dBm
- Bande passante : 125 kHz
- Coding rate : 4/5

## ⚠️ Notes importantes

- Le cycle d'émission en LoRaWAN est limité à 1% du temps
- La configuration doit être identique entre émetteur et récepteur pour une communication réussie
- Respecter les attributions de fréquences et facteurs d'étalement par binôme

## 📖 Documentation

Pour plus d'informations, consulter :
- [Documentation LoRa Library](https://github.com/sandeepmistry/arduino-LoRa)
- [Spécifications LoRaWAN](https://lora-alliance.org/resource_hub/lorawan-specification-v1-0-3/)