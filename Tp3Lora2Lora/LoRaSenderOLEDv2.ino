#include "heltec.h"
#define BINOME VOTRE_NUMERO_DE_BINOME
#define SPREADING_FACTOR VOTRE_SPREADING_FACTOR
#define FREQUENCE VOTRE_FREQUENCE
#define CODING_RATE 5
#define BAND    868E6 
unsigned int counter = 0;

//enlever la partie void logo {…}
void setup()
{
	Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
	LoRa.setSpreadingFactor(SPREADING_FACTOR);
	LoRa.setFrequency(FREQUENCE);
	LoRa.setCodingRate4(CODING_RATE);
	Heltec.display->init();
	Heltec.display->flipScreenVertically();
	Heltec.display->setFont(ArialMT_Plain_10);
//	logo() ;
	delay(1500);
	Heltec.display->clear();
	Heltec.display->drawString(0, 0, "Init. OK!");
	Heltec.display->display();
	delay(1000);
}

void loop()
{
	Heltec.display->clear();
	Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
	Heltec.display->setFont(ArialMT_Plain_10);
	Heltec.display->drawString(0, 0, "Envoi: ");
	Heltec.display->drawString(48, 0, String(counter));
	Heltec.display->display();

	// send packet
	LoRa.beginPacket();
	LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
LoRa.printf("Bnm:%d pck:%d",BINOME,counter);
	LoRa.endPacket();

	counter++;
	digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);                       // wait for a second
	digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);                       // wait for a second
} 
