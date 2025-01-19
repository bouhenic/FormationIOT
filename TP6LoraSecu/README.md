# TP6 Sécurité LoRaWAN

Ce projet est un travail pratique portant sur la sécurité des communications LoRaWAN, avec une attention particulière sur la protection contre les attaques par rejeu (replay attacks).

## Description

Le projet implémente un système de communication LoRa sécurisé avec :
- Un émetteur (noReplay-emitter-lora)
- Un récepteur (noReplay-receiver-lora)
- Une implémentation HMAC pour l'authentification des messages

## Contenu du Répertoire

- `HMAC.cpp` et `HMAC.h` : Implémentation de la fonction de hachage HMAC
- `noReplay-emitter-lora.ino` : Code Arduino pour l'émetteur LoRa
- `noReplay-receiver-lora.ino` : Code Arduino pour le récepteur LoRa
- `TP6LoraSecu3.pdf` : Documentation détaillée du TP

## Fonctionnalités de Sécurité

1. **Protection contre les attaques par rejeu** :
   - Utilisation de compteurs de séquence
   - Vérification de la validité temporelle des messages

2. **Authentification des messages** :
   - Implémentation HMAC pour garantir l'intégrité
   - Vérification de l'authenticité de l'émetteur

## Configuration requise

- Arduino IDE
- Modules LoRa compatibles
- Bibliothèques nécessaires (détaillées dans les fichiers source)

## Utilisation

1. **Configuration de l'émetteur** :
   - Charger le code `noReplay-emitter-lora.ino` sur le premier module
   - Configurer les paramètres LoRa selon votre environnement

2. **Configuration du récepteur** :
   - Charger le code `noReplay-receiver-lora.ino` sur le second module
   - S'assurer que les paramètres correspondent à ceux de l'émetteur

## Documentation

Pour plus de détails sur l'implémentation et les concepts de sécurité, consulter le fichier `TP6LoraSecu3.pdf`

## Aspect Pédagogique

Ce TP est conçu pour enseigner :
- Les fondamentaux de la sécurité LoRaWAN
- L'implémentation pratique des mécanismes de sécurité
- La protection contre les attaques courantes dans l'IoT

## Sécurité

⚠️ Ce code est fourni à des fins éducatives. Pour une utilisation en production, des mesures de sécurité supplémentaires doivent être mises en place.
