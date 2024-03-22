#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <Wire.h>
#include "HT_SSD1306Wire.h" // Assurez-vous d'utiliser la bibliothèque correcte pour l'OLED

// Configuration de l'affichage OLED
SSD1306Wire oleddisplay(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

#define BUFFER_SIZE 64 // Taille de buffer augmentée pour plus de flexibilité

// Paramètres LoRa
#define RF_FREQUENCY 867100000 // Hz, fréquence LoRa
#define LORA_BANDWIDTH 0 // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz]
#define LORA_SPREADING_FACTOR 7 // [SF7..SF12]
#define LORA_CODINGRATE 1 // [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH 8 // Longueur du préambule
#define LORA_SYMBOL_TIMEOUT 0 // Timeout des symboles
#define LORA_FIX_LENGTH_PAYLOAD_ON false // Longueur fixe du payload désactivée
#define LORA_IQ_INVERSION_ON false // Inversion IQ désactivée

char rxBuffer[BUFFER_SIZE]; // Buffer pour les données reçues

static RadioEvents_t RadioEvents; // Évènements LoRa

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialisation de l'écran OLED
  oleddisplay.init();
  oleddisplay.setFont(ArialMT_Plain_10);
  delay(2000); // Délai pour la lecture
  oleddisplay.clear();
  oleddisplay.drawString(0, 0, "Init. OK!");
  oleddisplay.drawString(0, 15, "Wait for data...");
  oleddisplay.display();
  delay(1000);


  // Initialisation LoRa
  Mcu.begin();
  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, true);
  Radio.Rx(0); // Commencez à recevoir
}

void loop() {
  // La logique de traitement des interruptions LoRa est exécutée dans le background
  Radio.IrqProcess();
}

// Callback appelé lorsqu'un paquet est reçu
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
  memcpy(rxBuffer, payload, size);
  rxBuffer[size] = '\0'; // Assurez-vous que la chaîne est correctement terminée

  // Affichage des données reçues et du RSSI sur l'écran OLED
  oleddisplay.clear();
  oleddisplay.drawString(0, 0, "Paquet recu:");
  oleddisplay.drawString(0, 15, String(rxBuffer));
  oleddisplay.drawString(0, 30, "RSSI: " + String(rssi) + " dBm");
  oleddisplay.display();


  Serial.print("Paquet recu: ");
  Serial.println(rxBuffer);
  Serial.print("RSSI: ");
  Serial.println(rssi);

  Radio.Rx(0); // Remet le module LoRa en mode de réception
}
