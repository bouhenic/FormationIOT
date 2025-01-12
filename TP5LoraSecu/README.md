# TP Communication LoRa Sécurisée, implantation du HMAC

Ce TP permet d'explorer la communication sécurisée entre équipements LoRa en utilisant le chiffrement AES et l'authentification HMAC.

## Objectifs

- Établir une communication sécurisée entre deux cartes Arduino MKR WAN 1310
- Mettre en œuvre le chiffrement AES pour la confidentialité des données
- Implémenter l'authentification HMAC pour garantir l'intégrité des messages
- Comprendre les concepts de sécurité dans l'IoT

## Matériel Nécessaire

- 2 cartes Arduino MKR WAN 1310 par binôme
- Ordinateur avec Arduino IDE installé

## Configuration des Fréquences

Chaque binôme doit utiliser une fréquence et un facteur d'étalement (Spreading Factor) spécifiques :

| Binôme | Fréquence (Hz) | Spreading Factor |
|--------|---------------|------------------|
| 1      | 867100000     | 7               |
| 2      | 867100000     | 8               |
| 3      | 867500000     | 7               |
| 4      | 867500000     | 8               |
| 5      | 867900000     | 7               |
| 6      | 867900000     | 8               |
| 7      | 868300000     | 7               |
| 8      | 868300000     | 8               |

## Installation

### Prérequis

1. Arduino IDE installé
2. Bibliothèques requises :
   - LoRa (Sandeep Mistry)
   - Crypto

### Configuration de l'Environnement

1. Sélectionner le type de carte :
   - `Tools > Board > Arduino SAMD Boards > Arduino MKR WAN 1310`
2. Installer les bibliothèques :
   - `Tools > Manage Libraries`
   - Rechercher et installer "LoRa" de Sandeep Mistry
   - Rechercher et installer "Crypto"

## Structure du Projet

Le projet contient deux parties principales :

### 1. Émetteur (`emitter-hmac-lora.ino`)
- Programme pour la carte émettrice
- Fichiers associés :
  - `HMAC.h`
  - `HMAC.cpp`

### 2. Récepteur (`receiver-hmac-lora.ino`)
- Programme pour la carte réceptrice
- Fichiers associés :
  - `HMAC.h`
  - `HMAC.cpp`

## Installation et Configuration

### Pour l'Émetteur

1. Créer un nouveau dossier `LoraSender`
2. Copier les fichiers suivants dans ce dossier :
   - `emitter-hmac-lora.ino`
   - `HMAC.h`
   - `HMAC.cpp`
3. Modifier la fréquence et le facteur d'étalement selon votre numéro de binôme
4. Compiler et téléverser le programme

### Pour le Récepteur

1. Créer un nouveau dossier `LoraReceiver`
2. Copier les fichiers suivants dans ce dossier :
   - `receiver-hmac-lora.ino`
   - `HMAC.h`
   - `HMAC.cpp`
3. Modifier la fréquence et le facteur d'étalement selon votre numéro de binôme
4. Compiler et téléverser le programme

## Fonctionnement

### Sécurité Implémentée

1. **Chiffrement AES-128**
   - Assure la confidentialité des messages
   - Utilise une clé de 16 octets

2. **Authentification HMAC**
   - Garantit l'intégrité et l'authenticité des messages
   - Utilise une clé de 32 octets
   - Vérifie que le message n'a pas été altéré

### Processus de Communication

1. **Émission**
   - Chiffrement du message avec AES
   - Calcul du HMAC
   - Envoi du message chiffré et du HMAC

2. **Réception**
   - Réception du message chiffré et du HMAC
   - Vérification du HMAC
   - Déchiffrement du message si l'authentification est valide

## Débogage

- Utiliser le moniteur série (9600 bauds) pour visualiser :
  - Les messages envoyés/reçus
  - Les données chiffrées
  - Les HMAC calculés
  - Les résultats de l'authentification

## Ressources

- [Documentation Arduino MKR WAN 1310](https://docs.arduino.cc/hardware/mkr-wan-1310)
- [Bibliothèque LoRa](https://github.com/sandeepmistry/arduino-LoRa)
- [HMAC sur Wikipedia](https://fr.wikipedia.org/wiki/HMAC)

## Avertissement

Ce code est fourni à des fins éducatives uniquement. Dans un environnement de production, il faudrait :
- Implémenter une gestion sécurisée des clés
- Ajouter des mécanismes de renouvellement des clés
- Mettre en place des protections supplémentaires contre les attaques

## Licence

Ce projet est fourni à des fins éducatives.
