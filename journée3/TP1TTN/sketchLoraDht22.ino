#include <MKRWAN.h>
#include "DHT.h"

LoRaModem modem;

// Définissez les informations de votre réseau LoRaWAN
const char *appEui = "0000000000000000";
const char *appKey = "5C527757EDB0B87DD9767568125889F0"; //indiquer ici votre appkey

#define DHTPIN 2          // Pin où le DHT22 est connecté
#define DHTTYPE DHT22     // Utilisation du DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    while (!Serial);

    dht.begin();
    if (!modem.begin(EU868)) {
        Serial.println("Échec de l'initialisation du modem");
        while (1);
    }
    if (!modem.joinOTAA(appEui, appKey)) {
        Serial.println("Échec de la connexion");
        while (1);
    }
    Serial.println("Connecté au réseau LoRaWAN");
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Échec de la lecture du capteur DHT");
        return;
    }
    // Convertir les valeurs en entiers pour simplifier l'envoi
    uint16_t h = humidity * 100;     // Par exemple, 55.12% devient 5512
    uint16_t t = (temperature + 100) * 100; // Par exemple, 24.76°C devient 2476 (avec un décalage de +100 pour gérer les températures négatives)

    // Créer un tableau de 4 octets pour envoyer les données
    byte payload[4];
    payload[0] = h >> 8;
    payload[1] = h & 0xFF;
    payload[2] = t >> 8;
    payload[3] = t & 0xFF;

    modem.beginPacket();
    modem.write(payload, 4);
    if (modem.endPacket(true) > 0) {
        Serial.println("Message envoyé avec succès");
    } else {
        Serial.println("Erreur lors de l'envoi du message");
    }

    delay(240000); // Attendre 4 minutes avant le prochain envoi
}
