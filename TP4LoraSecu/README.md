# Communication LoRa Sécurisée avec Chiffrement AES

Ce TP permet d'explorer la communication sécurisée entre équipements LoRa en utilisant le chiffrement AES-128.

## 🎯 Objectifs
- Établir une communication sécurisée entre plusieurs équipements LoRa
- Implémenter le chiffrement AES-128 pour la sécurisation des messages
- Comprendre les principes du chiffrement symétrique dans les communications IoT

## 📋 Matériel Requis

- 2 cartes Arduino MKR WAN 1310 par binôme
- Câbles USB pour la programmation

## 📊 Configuration des Binômes

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

## 🛠️ Configuration

### Prérequis Logiciels
- Arduino IDE
- Bibliothèques requises :
  - LoRa by Sandeep Mistry
  - Crypto

## 📡 Structure du Projet

### Émetteur (LoRaSender-encrypt.ino)
- Configuration de la communication LoRa
- Implémentation du chiffrement AES
- Envoi de messages chiffrés

### Récepteur (LoRaReceiver-encrypt.ino)
- Configuration identique de la communication LoRa
- Implémentation du déchiffrement AES
- Réception et décodage des messages

## 🔐 Implémentation du Chiffrement

### Configuration AES
```cpp
const byte key[16] = { 
    0x00, 0x01, 0x02, 0x03, 
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 
    0x0C, 0x0D, 0x0E, 0x0F 
};
```

### Processus de Chiffrement
1. Initialisation de l'objet AES
2. Configuration de la clé
3. Chiffrement du message par blocs
4. Transmission via LoRa

### Processus de Déchiffrement
1. Réception des données chiffrées
2. Initialisation du déchiffreur AES
3. Déchiffrement avec la clé partagée
4. Affichage du message en clair

## 🔧 Caractéristiques Techniques

### Configuration LoRa
- Fréquences : 867.1MHz à 868.3MHz
- Spreading Factor : SF7 ou SF8
- Bande passante : 125 kHz
- Coding rate : 4/5
- Puissance d'émission : 14 dBm

### Sécurité AES
- Mode : AES-128 ECB
- Taille de bloc : 16 octets
- Taille de clé : 128 bits

## 📝 Instructions d'Installation

### Pour l'Émetteur
1. Ouvrir Arduino IDE
2. Sélectionner "Arduino SAMD Boards / Arduino MKR WAN 1310"
3. Installer les bibliothèques requises
4. Charger le fichier `LoRaSender-encrypt.ino`
5. Configurer la fréquence et le spreading factor selon le binôme
6. Téléverser le programme

### Pour le Récepteur
1. Ouvrir Arduino IDE
2. Sélectionner "Arduino SAMD Boards / Arduino MKR WAN 1310"
3. Installer les bibliothèques requises
4. Charger le fichier `LoRaReceiver-encrypt.ino`
5. Configurer la fréquence et le spreading factor selon le binôme
6. Téléverser le programme

## ⚠️ Points Importants

- La clé AES doit être identique sur l'émetteur et le récepteur
- Les paramètres LoRa doivent correspondre entre émetteur et récepteur
- Les messages sont chiffrés par blocs de 16 octets
- Le mode ECB est utilisé pour la simplicité mais présente des limitations en termes de sécurité

## 🔍 Dépannage

1. Vérifier la correspondance des fréquences
2. Confirmer que le spreading factor est identique
3. S'assurer que la clé AES est la même des deux côtés
4. Vérifier les connexions USB et l'alimentation des cartes

## 📚 Documentation

- [Documentation LoRa Library](https://github.com/sandeepmistry/arduino-LoRa)
- [Documentation Crypto Library](https://rweather.github.io/arduinolibs/crypto.html)
- [Spécification AES](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf)

## 📖 Sources
Code source disponible sur GitHub :
- [LoRaSender-encrypt.ino](https://github.com/bouhenic/FormationIOT/blob/main/Tp3Lora2Lora/LoRaSender-encrypt.ino)
- [LoRaReceiver-encrypt.ino](https://github.com/bouhenic/FormationIOT/blob/main/Tp3Lora2Lora/LoRaReceiver-encrypt.ino)