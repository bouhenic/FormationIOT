#include <Arduino.h>
#include "esp_system.h"
#include "esp_mac.h"

// Convertit un tableau de 8 octets en affichage IEEE 0x00124B0001ABCDEF
static void printIEEEFromBytes(const uint8_t eui64[8]) {
  Serial.print("IEEE (EUI-64): 0x");
  for (int i = 0; i < 8; i++) {
    Serial.printf("%02X", eui64[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println();
  Serial.println("=== ESP32-H2 IEEE (EUI-64) ===");

  // 1) Lire l'EUI-64 "base MAC" depuis l'eFuse
  uint8_t eui64[8] = {0};

  // Certaines versions exposent cet API :
  // - esp_efuse_mac_get_default() donne 6 octets (MAC) sur ESP32 classiques
  // Sur ESP32-H2, on a généralement accès à une base MAC et/ou EUI-64 via esp_read_mac/esp_derive
  //
  // Méthode robuste : lire la base MAC (6 octets), puis dériver une EUI-64 "standard"
  uint8_t mac6[6] = {0};
  esp_err_t err = esp_read_mac(mac6, ESP_MAC_BASE);

  if (err != ESP_OK) {
    Serial.printf("ERROR: esp_read_mac failed: %d\n", (int)err);
  } else {
    Serial.print("Base MAC (6 bytes): ");
    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X", mac6[i]);
      if (i < 5) Serial.print(":");
    }
    Serial.println();

    // 2) Dériver une EUI-64 à partir de la MAC (méthode classique EUI-64)
    // Insertion de FF:FE au milieu (MAC-48 -> EUI-64)
    eui64[0] = mac6[0];
    eui64[1] = mac6[1];
    eui64[2] = mac6[2];
    eui64[3] = 0xFF;
    eui64[4] = 0xFE;
    eui64[5] = mac6[3];
    eui64[6] = mac6[4];
    eui64[7] = mac6[5];

    printIEEEFromBytes(eui64);

    Serial.println("Note: Zigbee2MQTT affiche souvent l'IEEE comme 0x............... (16 hex chars).");
  }

  Serial.println("==============================");
}

void loop() {
  delay(2000);
}
