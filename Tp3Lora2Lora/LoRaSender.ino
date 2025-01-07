#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation de l'émetteur LoRa...");

  // Initialisation LoRa à 868 MHz
  if (!LoRa.begin(867.5E6)) { // Fréquence pour l'Europe
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  // Configuration du spreading factor (entre 6 et 12)
  LoRa.setSpreadingFactor(8); // SF7 : rapide, portée moyenne

  // (Optionnel) Configuration de la bande passante et du coding rate
  LoRa.setSignalBandwidth(125E3); // 125 kHz
  LoRa.setCodingRate4(5); // 4/5

  // Configuration de la puissance d'émission (2 à 20 dBm)
  LoRa.setTxPower(14); // Réglez la puissance sur 14 dBm (par défaut)

  Serial.println("LoRa prêt !");
}

void loop() {
  Serial.println("Envoi du message...");
  LoRa.beginPacket();
  LoRa.print("Hello LoRa !");
  LoRa.endPacket();

  delay(2000); // Attendre 2 secondes avant d'envoyer un nouveau message

