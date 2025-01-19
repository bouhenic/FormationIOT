# TP6 Sécurité LoRaWAN

Ce projet est un travail pratique portant sur la sécurité des communications LoRaWAN, avec une attention particulière sur la protection contre les attaques par rejeu (replay attacks).

## Objectif
Faire communiquer plusieurs équipements LoRa de manière sécurisée en implémentant :
- Protection contre les attaques par rejeu
- Authentification des messages par HMAC
- Chiffrement AES des communications

## Configuration Matérielle
- Arduino MKR WAN 1310
- Bibliothèques requises :
  - LoRa (Sandeep Mistry)
  - Crypto

## Paramètres de Communication
Le projet supporte différentes configurations selon les binômes :

| Binôme | Fréquence (Hz) | Facteur d'étalement |
|--------|----------------|---------------------|
| 1      | 867.1M        | 7                   |
| 2      | 867.1M        | 8                   |
| 3      | 867.5M        | 7                   |
| 4      | 867.5M        | 8                   |
| 5      | 867.9M        | 7                   |
| 6      | 867.9M        | 8                   |
| 7      | 868.3M        | 7                   |
| 8      | 868.3M        | 8                   |

## Structure du Projet

### Fichiers Source
- `noReplay-emitter-lora.ino` : Code de l'émetteur
- `noReplay-receiver-lora.ino` : Code du récepteur
- `HMAC.h` et `HMAC.cpp` : Implémentation du HMAC

### Mécanismes de Sécurité

#### Protection Anti-Rejeu
- Utilisation d'un compteur global (frameCounter)
- Vérification de la séquence des messages
- Rejet des messages avec compteur invalide ou déjà utilisé

#### Chiffrement
- Utilisation d'AES-128
- Clé de chiffrement de 16 octets
- Chiffrement par blocs de 16 octets

#### Authentification
- HMAC avec clé de 32 octets
- Vérification de l'intégrité des messages
- Protection contre la modification des messages

## Installation et Configuration

### Pour l'Émetteur
1. Configurer Arduino IDE pour Arduino MKR WAN 1310
2. Installer les bibliothèques requises
3. Copier les fichiers HMAC.h et HMAC.cpp
4. Modifier les paramètres de fréquence et facteur d'étalement
5. Téléverser le code émetteur

### Pour le Récepteur
1. Mêmes étapes de configuration initiale
2. S'assurer que les paramètres correspondent à l'émetteur
3. Téléverser le code récepteur

## Format des Messages
- Payload total : 40 octets
  - 32 octets de message chiffré
  - 8 octets de HMAC
- Intégration du compteur dans les 4 derniers octets du message

## Sécurité et Limitations
⚠️ Note importante : Ce code est fourni à des fins éducatives. Pour une utilisation en production :
- Implémenter une rotation des clés
- Ajouter une gestion sécurisée des clés
- Renforcer la protection contre les attaques physiques
- Mettre en place une surveillance des anomalies

## Documentation
Pour plus de détails techniques et le guide complet du TP, consulter le fichier `TP6LoraSecu3.pdf`