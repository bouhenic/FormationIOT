#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialisation du récepteur LoRa...");

  // Initialisation LoRa à 868 MHz
  if (!LoRa.begin(867.1E6)) { // Fréquence pour l'Europe
    Serial.println("Erreur lors de l'initialisation LoRa");
    while (1);
  }

  // Configuration du spreading factor (identique à l'émetteur)
  LoRa.setSpreadingFactor(7); // SF7

  // (Optionnel) Configuration de la bande passante et du coding rate
  LoRa.setSignalBandwidth(125E3); // 125 kHz
  LoRa.setCodingRate4(5); // 4/5

  Serial.println("LoRa prêt !");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Message reçu : ");

    // Lire les données reçues
    while (LoRa.available()) {
      char message = (char)LoRa.read();
      Serial.print(message);
    }
    Serial.println();
  }
}
