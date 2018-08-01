#include <SPI.h>
#include <LoRa32u4.h>

// uncomment the section corresponding to your board
// BSFrance 2017 contact@bsrance.fr

//  //LoR32u4 433MHz V1.0 (white board)
//  #define SCK     15
//  #define MISO    14
//  #define MOSI    16
//  #define SS      1
//  #define RST     4
//  #define DI0     7
//  #define BAND    433E6
//  #define PABOOST true

//  //LoR32u4 433MHz V1.2 (white board)
//  #define SCK     15
//  #define MISO    14
//  #define MOSI    16
//  #define SS      8
//  #define RST     4
//  #define DI0     7
//  #define BAND    433E6
//  #define PABOOST true

//LoR32u4II 868MHz or 915MHz (black board)
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
#define BAND    868E6  // 915E6
#define PABOOST true

void setup() {
	delay(5000);
	Serial.begin(9600);
	//while (!Serial);
	Serial.println("LoRa Receiver");
	LoRa.setPins(SS,RST,DI0);
	if (!LoRa.begin(868300000,PABOOST)) {
		Serial.println("Starting LoRa failed!");
		while (1);
	}
	LoRa.setSignalBandwidth(125E3);
	LoRa.setSpreadingFactor(9);
	LoRa.setCodingRate4(5);
	LoRa.setSyncWord(0x34);
	LoRa.enableCrc();
}

void loop() {
	// try to parse packet
	int packetSize = LoRa.parsePacket();
	if (packetSize) {
		// received a packet
		Serial.print("Received packet '");

		// read packet
		while (LoRa.available()) {
			Serial.print((char)LoRa.read());
		}

		// print RSSI of packet
		Serial.print("' with RSSI ");
		Serial.print(LoRa.packetRssi());
		Serial.print("' and SNR ");
		Serial.println(LoRa.packetSnr());
	}
}