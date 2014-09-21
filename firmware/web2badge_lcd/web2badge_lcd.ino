//////////////////////////////////////////////////////////
////                                                  ////
////  Web2Badge Project  - BADGE FIRMWARE             ////
////                                                  ////
////   This code uses the following Libraries:        ////
////   Adafruit PCD8544 and GFX - TODO - LINK         ////
////   ManiacBug's lib -     TODO - LINK              ////
////                                                  ////
////                                                  ////
////  This code is CC bySA                            ////
////                                                  ////
////   (c) Ricardo Lameiro 2014                       ////
////   (c) Diogo Gomes 2014                           ////
////                                                  ////
////                                                  ////
////                                                  ////
////                                                  ////
//////////////////////////////////////////////////////////


#include <EEPROM.h>

#define RADIO
#define LCD
///ID vars
char id[2] = {'F  ','M'}; //DG = Diogo Gomes
int addr = 0; //address of the EEPROM where ID is stored

#include <SPI.h>

#ifdef LCD
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// lcd init 6 rst , 5 cselect, 4 data / cmd
Adafruit_PCD8544 display = Adafruit_PCD8544(4, 5, 6);

///lcd vars
int bkpin = 3;           //Backlight pin
int blkrate = 50;        //defines the blinking speed of the backlight
int lcdctr = 50;         // lcd contrat
int bkbright= 15;    //defines backlight brightness
#endif

#ifdef RADIO
#include "nRF24L01.h"
#include "RF24.h"


// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 -> 7-8
RF24 radio(9,10);// CE - CS 
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
#endif

#define DEBUG

#ifdef DEBUG
#define PRINT(X) Serial.print(X);
#define PRINTLN(X) Serial.println(X);
#else
#define PRINT(X)
#define PRINTLN(X)
#endif

#define WHITE 0xFFFF
#define BLACK 0x0000

int serial_putc( char c, FILE * )
{
		Serial.write( c );

		return c;
}

void printf_begin(void)
{
		fdevopen( &serial_putc, 0 );
}



void setID(char *newid){
	EEPROM.write(addr, newid[0]);
	EEPROM.write(addr+1, newid[1]);
	id[0] = newid[0];
	id[1] = newid[1];
}

void setup_radio() {
#ifdef RADIO
       pinMode(10,OUTPUT);
	radio.begin();
        //delay(250); //test
	// enable dynamic payloads
	radio.enableDynamicPayloads();
	// optionally, increase the delay between retries & # of retries
	radio.setRetries(5,5);
	radio.setAutoAck(false);
	radio.setDataRate(RF24_250KBPS);
	
	radio.setPALevel(RF24_PA_MIN);//

	radio.openWritingPipe(pipes[1]);
	radio.openReadingPipe(1,pipes[0]);

	// Start listening
	radio.startListening();
#endif
}

void setup_lcd() {

#ifdef LCD
	pinMode(bkpin, OUTPUT); //backlight setup
	pinMode(8, OUTPUT);
	analogWrite(bkpin, bkbright);

	display.begin(); //display iniT
	display.setContrast(lcdctr);
	display.clearDisplay(); //clears buffer
	display.setCursor(0,0);
	display.setTextColor(0xffff);
	//void setTextColor(uint16_t color, uint16_t backgroundcolor);
	display.setTextSize(1);
	display.setTextWrap(true);
	display.println("TESTE");
	//display.print("done setup()");
	display.display();
	//delay(2000);
#endif
}

void setup() {
	Serial.begin(115200);
	printf_begin();
	Serial.println("webtag1.0");

	id[0] = EEPROM.read(addr);
	id[1] = EEPROM.read(addr+1);

	String id_s = id;
        PRINT("Set ID = ")
        PRINTLN(id_s);

	setup_lcd();

	setup_radio();

// Dump the configuration of the rf unit for debugging
#ifdef DEBUG
	#ifdef RADIO
		radio.printDetails();
	#endif

	#ifdef LCD
		display.print("done setup()");
		display.display();
	#endif
	Serial.println("done setup()");
#endif
}

///////////////////////////////////////
///// END SETUP()                 /////
///////////////////////////////////////


void bckBlink(){  // blinks Background when badge receives new message
	#ifdef LCD
	analogWrite(3, 255);
	delay(blkrate);
	analogWrite(3, 5);
	delay(blkrate);
	analogWrite(3, 200);
	delay(blkrate);
	analogWrite(3, 140);
	delay(blkrate);
	#endif
}

char lcd_buf[84];
int lcd_i = 0;

void printDisplay(char *c) {
        printClean();
        if(strlen(c) > 84-lcd_i) {
          lcd_i = 0;
          memset(lcd_buf,0,84);
        }
        strncpy(&lcd_buf[lcd_i], c, strlen(c));
        lcd_i+=strlen(c);
	#ifdef LCD
        bckBlink();
	display.print(lcd_buf);
        bckBlink();
	#else
        
	Serial.print(lcd_buf);
	#endif
        display.display();
}

void printClean() {
        display.clearDisplay();
        lcd_i = 0;
        memset(lcd_buf,0,84);
        #ifdef LCD
	display.print(lcd_buf);
	#endif
        display.display();
}

void setBackLight(int val) {
    analogWrite(bkpin, val);
  

}

void set_Contrast(int val) {
    display.setContrast(val);
}

void checkCMD(char* arrCMD){
                if(strlen(arrCMD) == 2)
                  printClean();
                else if(arrCMD[0] == '+' && arrCMD[1] == '+') {
			PRINTLN("Command mode");
			switch(arrCMD[2]) {
				case 'I':
					arrCMD[5] = NULL;
					PRINT("Set ID: ");
					PRINTLN(&arrCMD[3]);
					id[0] = arrCMD[3];
					id[1] = arrCMD[4];
                                        setID(id);
					break;
//				case 'B':
//					PRINT("Set Backlight: ");
//					PRINTLN(&arrCMD[3]);
//					setBackLight(atoi(&arrCMD[3]));
//					break;
//				case 'C':
//					PRINT("Set Contrast: ");
//					PRINTLN(&arrCMD[3]);
//					set_Contrast(atoi(&arrCMD[3]));
//					break;
                                case 'X':
                                        printClean();
                                        break;
                      }
                        if (arrCMD[2] == id[0] && arrCMD[3] == id[0]) {
                          switch(arrCMD[4]) {              
                              
				case 'B':
					PRINT("Set Backlight: ");
					PRINTLN(&arrCMD[5]);
					setBackLight(atoi(&arrCMD[5]));
					break;
				case 'C':
					PRINT("Set Contrast: ");
					PRINTLN(&arrCMD[5]);
					set_Contrast(atoi(&arrCMD[5]));
					break;
                                case 'X':
                                        printClean();
                                        break;
			}
                      }
		} else if(arrCMD[0] == id[0] && arrCMD[1] == id[1]) {
			PRINTLN("Message for ME!");
			printDisplay(&arrCMD[2]);

		} else if(arrCMD[0] == '*' && arrCMD[1] == '*') {
			PRINTLN("Message for EVERYONE!");
			printDisplay(&arrCMD[2]);
 
		} else {
			//Serial.println("Invalid Command ID or unidentified message");
		}

}

///////////////////////////////////////
///// MAIN LOOP                   /////
///////////////////////////////////////

void loop() {
  #ifdef RADIO
	
	        //  radio.stopListening();
		//  char *c = "A";
		//  radio.write(c, 1);
		//  radio.startListening();

		//give sometime to reply back with command

		if ( radio.available() ) {
		//Serial.println("Radio disponivel"); //Debug
				uint8_t len;
				char c[128];
				bool done = false;
				while (!done) {
						// Fetch the payload, and see if this was the last one.
						len = radio.getDynamicPayloadSize();
                                                Serial.println(len);
						if(len < 128) {
								done = radio.read(&c, len);
                                                                
								c[len] = NULL; // para terminar a string no fim do array lido

								checkCMD(c);
                                                                display.clearDisplay();

								//bckBlink();
								#ifdef LCD
							//	display.clearDisplay();

								#endif
								//bckBlink();

								//tone(10, 440);
								//delay(200);
								//bckBlink();
								//noTone(10);


								//        tone(10, 880);
								//        delay(200);
								//        noTone(10);
								//        tone(10, 335, 800);
								//        delay(300);
								//        noTone(10);
								//        tone(10, 1000, 1000);
								//        delay(500);
								//        noTone(10);
								//bckBlink();

								delay(250);
								

								//        display.print (c);
								//        display.display();
								//        bckBlink();

						} else {
								PRINTLN("Error receiving GHCommandPacket");
								done =true;

						}
				}

		}
		//      display.clearDisplay();     //TODO : implement time out counter to leave this message in case of long wait

		//      display.print ("tweet me!!!!");
		//      display.display();
  #endif
}
