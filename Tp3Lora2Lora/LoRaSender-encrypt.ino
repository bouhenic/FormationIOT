#include <LoRa.h>
#include <Crypto.h>
#include <AES.h>

// Clé de chiffrement AES (16 octets pour AES-128)
const byte key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                       0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation de l'émetteur LoRa...");

  if (!LoRa.begin(867.5E6)) {
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(8);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setTxPower(14);

  Serial.println("LoRa prêt !");
}

void loop() {
  char message[] = "Hello LoRa!"; // Message à envoyer
  byte encryptedMessage[16];     // Buffer pour le message chiffré

  // Initialisation de l'objet AES
  AES128 aesEncryptor;
  aesEncryptor.setKey(key, sizeof(key));

  // Chiffrement AES
  aesEncryptor.encryptBlock(encryptedMessage, (byte*)message);

  // Envoi du message
  LoRa.beginPacket();
  LoRa.write(encryptedMessage, sizeof(encryptedMessage));
  LoRa.endPacket();

  Serial.print("Message chiffré envoyé : ");
  for (int i = 0; i < sizeof(encryptedMessage); i++) {
    Serial.print(encryptedMessage[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  delay(2000); // Pause avant d'envoyer un nouveau message
}
