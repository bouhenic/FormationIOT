#include <LoRa.h>
#include <Crypto.h>
#include <AES.h>

// Clé de déchiffrement AES (identique à l'émetteur)
const byte key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                       0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation du récepteur LoRa...");

  if (!LoRa.begin(867.5E6)) {
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);

  Serial.println("LoRa prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Message reçu : ");

    byte encryptedMessage[16]; // Buffer pour les données chiffrées reçues
    byte decryptedMessage[16]; // Buffer pour le message déchiffré

    // Lire les données reçues
    for (int i = 0; i < packetSize && i < sizeof(encryptedMessage); i++) {
      encryptedMessage[i] = LoRa.read();
    }

    // Déchiffrement AES
    AES128 aesDecryptor;
    aesDecryptor.setKey(key, sizeof(key));
    aesDecryptor.decryptBlock(decryptedMessage, encryptedMessage);

    // Affichage du message déchiffré
    Serial.print("Message déchiffré : ");
    Serial.println((char*)decryptedMessage);
  }
}
