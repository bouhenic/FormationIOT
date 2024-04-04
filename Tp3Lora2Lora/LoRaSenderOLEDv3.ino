#include "LoRaWan_APP.h"
#include "Arduino.h"
#include <Wire.h>               
#include "HT_SSD1306Wire.h"

SSD1306Wire  oledDisplay(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

#define BINOME //NUMERO_BINOME
#define RF_FREQUENCY                                //FREQUENCE // Hz
#define TX_OUTPUT_POWER                             5        // dBm
#define LORA_BANDWIDTH                              0
#define LORA_SPREADING_FACTOR                       //VALEUR_SF
#define LORA_CODINGRATE                             1
#define LORA_PREAMBLE_LENGTH                        8
#define LORA_SYMBOL_TIMEOUT                         0
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false

#define BUFFER_SIZE                                 30 // Define the payload size here

unsigned int packetCounter = 0; // Compteur de paquet

bool lora_idle=true;

static RadioEvents_t RadioEvents;
void OnTxDone( void );
void OnTxTimeout( void );

void setup() {
    Serial.begin(115200);
    Mcu.begin();

    Serial.println();
    VextON();
    delay(100);

    // Initialising the UI will init the display too.
    oledDisplay.init();
    oledDisplay.setFont(ArialMT_Plain_10);
	
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    
    Radio.Init( &RadioEvents );
    Radio.SetChannel( RF_FREQUENCY );
    Radio.SetTxConfig( MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                       LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                       LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                       true, 0, 0, LORA_IQ_INVERSION_ON, 3000 ); 
}

void VextON(void) {
    pinMode(Vext,OUTPUT);
    digitalWrite(Vext, LOW);
}

void loop() {
    char txpacket[BUFFER_SIZE];
    
    if(lora_idle == true) {
        packetCounter++; // Incrémentation du compteur de paquets
        sprintf(txpacket,"Bnm:%d Packet #%u", BINOME, packetCounter); // Préparation du message à envoyer

        // Affichage du message sur l'écran OLED
        oledDisplay.clear();
        oledDisplay.drawStringMaxWidth(0, 0, 128, txpacket);
        oledDisplay.display();
		
        // Envoi du paquet
        Serial.printf("\r\nSending packet: \"%s\"\r\n", txpacket);
        Radio.Send((uint8_t *)txpacket, strlen(txpacket));
        lora_idle = false;
    }
    Radio.IrqProcess();
    delay(2000); // Petite pause pour la stabilité
}

void OnTxDone(void) {
    Serial.println("TX done......");
    lora_idle = true;
}

void OnTxTimeout(void) {
    Radio.Sleep();
    Serial.println("TX Timeout......");
    lora_idle = true;
}

