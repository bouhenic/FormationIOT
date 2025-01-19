#include <LoRa.h>
#include <Crypto.h>
#include <AES.h>
#include "HMAC.h"

// Clé de chiffrement AES (16 octets pour AES-128)
const byte aesKey[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                          0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

// Clé HMAC (32 octets ici)
const byte hmacKey[32] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                           0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                           0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                           0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F };

// Compteur global pour identifier les messages (initialisé à 0)
unsigned long frameCounter = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("Initialisation de l'émetteur LoRa...");

    // Initialisation LoRa
    if (!LoRa.begin(867.5E6)) {
        Serial.println("Erreur lors de l'initialisation LoRa");
        while (1);
    }

    LoRa.setSpreadingFactor(7);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.setTxPower(14);

    Serial.println("LoRa prêt !");
}

void loop() {
    char message[] = "Hello LoRa!"; // Message à envoyer
    byte plainMessage[32];          // Message en clair incluant le compteur
    byte encryptedMessage[32] = {0}; // Buffer pour le message chiffré
    byte hmac[32];                  // Buffer pour le HMAC calculé

    // Construction du message avec le compteur
    memset(plainMessage, 0, sizeof(plainMessage)); // Effacer le buffer
    memcpy(plainMessage, message, strlen(message)); // Copier le texte du message
    plainMessage[strlen(message)] = frameCounter & 0xFF;           // Byte 0 du compteur
    plainMessage[strlen(message) + 1] = (frameCounter >> 8) & 0xFF; // Byte 1
    plainMessage[strlen(message) + 2] = (frameCounter >> 16) & 0xFF; // Byte 2
    plainMessage[strlen(message) + 3] = (frameCounter >> 24) & 0xFF; // Byte 3

    // Initialisation de l'objet AES
    AES128 aesEncryptor;
    aesEncryptor.setKey(aesKey, sizeof(aesKey));

    // Chiffrement AES
    aesEncryptor.encryptBlock(encryptedMessage, plainMessage);

    // Calcul du HMAC
    HMAC::calculateHMAC(hmacKey, sizeof(hmacKey), encryptedMessage, sizeof(encryptedMessage), hmac);

    // Préparation du payload (chiffrement + HMAC court)
    byte payload[32 + 8]; // Chiffrement + 8 octets du HMAC
    memcpy(payload, encryptedMessage, sizeof(encryptedMessage));
    memcpy(payload + sizeof(encryptedMessage), hmac, 8); // HMAC court

    // Envoi des données via LoRa
    LoRa.beginPacket();
    LoRa.write(payload, sizeof(payload));
    LoRa.endPacket();

    // Affichage pour débogage
    Serial.print("Message chiffré envoyé : ");
    for (int i = 0; i < sizeof(encryptedMessage); i++) {
        Serial.print(encryptedMessage[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    Serial.print("HMAC envoyé (8 octets) : ");
    for (int i = 0; i < 8; i++) {
        Serial.print(hmac[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    // Affichage du compteur
    Serial.print("Compteur : ");
    Serial.println(frameCounter);

    frameCounter++; // Incrémentation du compteur
    delay(2000);    // Pause avant d'envoyer un nouveau message
}
