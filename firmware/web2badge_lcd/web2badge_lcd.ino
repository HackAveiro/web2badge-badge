
//#include <Narcoleptic.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// lcd init 6 rst , 5 cselect, 4 data / cmd
Adafruit_PCD8544 display = Adafruit_PCD8544(4, 5, 6);


#include "nRF24L01.h"
#include "RF24.h"


#define DEBUG
#ifdef DEBUG
  #define PRINT(X) Serial.print(X)
  #define PRINTLN(X) Serial.println(X)
#else
  #define PRINT(X)
  #define PRINTLN(X)
#endif

#ifdef ARDUINO

#define WHITE 0xFFFF
#define BLACK 0x0000

//#define BLIGHT 10 



int blkrate = 50; //defines the blinking speed of the backlight
int bkbright = 140; //defines backlight

int serial_putc( char c, FILE * ) 
{
  Serial.write( c );

  return c;
} 

void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

#else
#error This example is only for use on Arduino.
#endif // ARDUINO




// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(7,9);// CE - CS
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };







void setup() {
  
  pinMode(3, OUTPUT); //backlight setup
  analogWrite(3, bkbright);
  
  display.begin(); //display iniT
  display.setContrast(300);

  display.display();
  delay(1500);
  display.clearDisplay(); //clears buffer
    
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  //void setTextColor(uint16_t color, uint16_t backgroundcolor);
  display.setTextSize(1.5);
  display.setTextWrap(true);
  display.println("TESTE");
  //display.print("done setup()");
  display.display();
  delay(2000);
  
  
  Serial.begin(115200); 
  printf_begin();
  Serial.println("webtag1.0");
  
  
  
  
  //
  // Setup and configure rf radio
  //
  radio.begin();
  // enable dynamic payloads
  radio.enableDynamicPayloads();
  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  //radio.setChannel(1); //
  radio.setPALevel(RF24_PA_MIN);//
  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  
  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  #ifdef DEBUG
  radio.printDetails();
  Serial.println("done setup()");
  #endif
  display.print("done setup()");
  display.display();
}

void bckBlink(){  // blinks Background when badge receives new message

    analogWrite(3, 255);
    delay(blkrate);
    analogWrite(3, 5);
    delay(blkrate);
    analogWrite(3, 200);
    delay(blkrate);
    analogWrite(3, 140);
    delay(blkrate);
   
}
void loop() {
  
//  radio.stopListening();
//  char *c = "A";
//  radio.write(c, 1);
//  radio.startListening();

  delay(250); //give sometime to reply back with command
  
  if ( radio.available() ) {
    Serial.println("Radio disponivel"); //Debug
    uint8_t len;
    char c[128];
    bool done = false;
    while (!done) {
      // Fetch the payload, and see if this was the last one.
      len = radio.getDynamicPayloadSize();
      if(len < 128) {
        done = radio.read(&c, len);
        c[len] = NULL; // para terminar a string no fim do array lido
        PRINTLN (c);
        bckBlink();
        display.clearDisplay();
        bckBlink();
        
        tone(10, 440);
        delay(200);
        bckBlink();
        noTone(10);
        
        display.print (c);
        display.display();
        
        tone(10, 880);
        delay(200);
        noTone(10);
        tone(10, 335, 800);
        delay(300);
        bckBlink();
        noTone(10);
        
        tone(10, 1000, 1000);
        
        delay(500);
        bckBlink();
        noTone(10);
        bckBlink();
        
        //display.print (c);
        //display.display();
        //bckBlink();
        
      } else {
        PRINTLN("Error receiving GHCommandPacket");
        done =true;
        
      }
    }

  }
//      display.clearDisplay();     //TODO : implement time out counter to leave this message in case of long wait

//      display.print ("tweet me!!!!");
//      display.display();
}
