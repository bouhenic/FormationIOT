#include <LoRa.h>
#include <Crypto.h>
#include <AES.h>
#include "HMAC.h"

// Clé de déchiffrement AES (16 octets pour AES-128)
const byte aesKey[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

// Clé HMAC (32 octets ici)
const byte hmacKey[32] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                           0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                           0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                           0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F };

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation du récepteur LoRa...");

  // Initialisation LoRa
  if (!LoRa.begin(867.5E6)) {
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Message reçu :");

    byte encryptedMessage[16];  // Buffer pour les données chiffrées reçues
    byte receivedHMAC[8];       // Buffer pour les 8 premiers octets du HMAC reçu
    byte calculatedHMAC[32];    // Buffer pour le HMAC recalculé
    byte decryptedMessage[17];  // Buffer pour le message déchiffré (16 + 1 pour '\0')

    // Lire les données chiffrées
    for (int i = 0; i < 16; i++) {
      if (LoRa.available()) {
        encryptedMessage[i] = LoRa.read();
      }
    }

    // Lire le HMAC reçu
    for (int i = 0; i < 8; i++) {
      if (LoRa.available()) {
        receivedHMAC[i] = LoRa.read();
      }
    }

    // Recalculer le HMAC pour authentification
    HMAC::calculateHMAC(hmacKey, sizeof(hmacKey), encryptedMessage, sizeof(encryptedMessage), calculatedHMAC);

    // Comparer le HMAC reçu avec le HMAC recalculé
    bool hmacValid = true;
    for (int i = 0; i < 8; i++) {
      if (receivedHMAC[i] != calculatedHMAC[i]) {
        hmacValid = false;
        break;
      }
    }

    if (!hmacValid) {
      Serial.println("Authentification échouée : HMAC invalide");
      return; // Arrêter le traitement si le HMAC est incorrect
    }

    // Déchiffrer les données
    AES128 aesDecryptor;
    aesDecryptor.setKey(aesKey, sizeof(aesKey));
    aesDecryptor.decryptBlock(decryptedMessage, encryptedMessage);

    // Ajouter le caractère nul pour terminer la chaîne
    decryptedMessage[16] = '\0';

    // Afficher le message déchiffré
    Serial.print("Message déchiffré : ");
    Serial.println((char*)decryptedMessage);
  }
}
