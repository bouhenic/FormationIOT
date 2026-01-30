// Copyright 2024 Espressif Systems (Shanghai) PTE LTD
// Licensed under the Apache License, Version 2.0

#ifndef ZIGBEE_MODE_ED
#error "Zigbee end device mode is not selected in Tools->Zigbee mode"
#endif

#include "Zigbee.h"

/* Zigbee temperature sensor configuration */
#define TEMP_SENSOR_ENDPOINT_NUMBER 10
uint8_t button = BOOT_PIN;

// Optional Time cluster variables
struct tm timeinfo;
struct tm *localTime;
int32_t timezone;

ZigbeeTempSensor zbTempSensor = ZigbeeTempSensor(TEMP_SENSOR_ENDPOINT_NUMBER);

/************************ Fake Temp sensor *****************************/
static void temp_sensor_value_update(void *arg) {
  (void)arg;

  // (Optionnel) Initialiser le générateur pseudo-aléatoire
  // Sur ESP32, randomSeed() peut prendre un bruit analogique, mais ici on fait simple.
  randomSeed((uint32_t)esp_random());

  for (;;) {
    // Valeur aléatoire entre 15.0 et 30.0 °C
    float fakeTemp = random(150, 300) / 10.0;

    Serial.printf("Updated FAKE temperature value to %.1f°C\r\n", fakeTemp);

    // Update temperature value in Temperature sensor EP
    zbTempSensor.setTemperature(fakeTemp);

    // Toutes les 5 secondes (plus lisible pour les élèves)
    delay(5000);
  }
}

/********************* Arduino functions **************************/
void setup() {
  Serial.begin(115200);

  // Init button switch
  pinMode(button, INPUT_PULLUP);

  // IMPORTANT: identifiants stables pour Zigbee2MQTT + converter externe
  zbTempSensor.setManufacturerAndModel("NewtonCIEL", "ESP32H2_FAKE_TEMP_V1");

  // Plage réaliste
  zbTempSensor.setMinMaxValue(0, 50);
  zbTempSensor.setDefaultValue(20.0);
  zbTempSensor.setTolerance(0.1);

  // Optional: Time cluster configuration (device will receive time from coordinator)
  // Tu peux commenter cette ligne si tu ne veux pas aborder le Time cluster.
  zbTempSensor.addTimeCluster();

  // Add endpoint to Zigbee Core
  Zigbee.addEndpoint(&zbTempSensor);

  Serial.println("Starting Zigbee...");
  // When all EPs are registered, start Zigbee in End Device mode
  if (!Zigbee.begin()) {
    Serial.println("Zigbee failed to start!");
    Serial.println("Rebooting...");
    ESP.restart();
  } else {
    Serial.println("Zigbee started successfully!");
  }

  Serial.println("Connecting to network");
  while (!Zigbee.connected()) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Optional: If time cluster is added, time can be read from the coordinator
  timeinfo = zbTempSensor.getTime();
  timezone = zbTempSensor.getTimezone();

  Serial.println("UTC time:");
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  time_t local = mktime(&timeinfo) + timezone;
  localTime = localtime(&local);

  Serial.println("Local time with timezone:");
  Serial.println(localTime, "%A, %B %d %Y %H:%M:%S");

  // Start Temperature sensor reading task
  xTaskCreate(temp_sensor_value_update, "temp_sensor_upd", 4096, NULL, 10, NULL);

  // Reporting interval (en secondes)
  // Ici: min=10, max=60, delta=0.1°C (delta en 0.1°C => 1)
  // => envoie au moins toutes les 60s OU plus tôt si variation >= 0.1°C après 10s mini
  zbTempSensor.setReporting(10, 60, 1);
}

void loop() {
  // Checking button for factory reset + report immédiat
  if (digitalRead(button) == LOW) {  // Push button pressed
    // Key debounce handling
    delay(100);

    unsigned long startTime = millis();
    while (digitalRead(button) == LOW) {
      delay(50);
      if ((millis() - startTime) > 3000) {
        // If key pressed for more than 3 secs, factory reset Zigbee and reboot
        Serial.println("Resetting Zigbee to factory and rebooting in 1s.");
        delay(1000);
        Zigbee.factoryReset();
      }
    }

    // Appui court: report immédiat
    Serial.println("Button: reportTemperature()");
    zbTempSensor.reportTemperature();
  }

  delay(100);
}
