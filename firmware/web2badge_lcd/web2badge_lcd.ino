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
//#include <Narcoleptic.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <SerialCommand.h>
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




///ID vars
char id[3] = "00";
int id_state = 0; //If EEPROM ID is diferent from "00" this is 1


///lcd vars
int bkpin = 3;           //Backlight pin
int blkrate = 50;        //defines the blinking speed of the backlight
int lcdctr = 60;         // lcd contrat
int bkbright = 140;      //defines backlight brightness





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


void checkID(){
 //TODO
// read EEPROM address
// check if it is "00"
//if it is != to "00" then write the value to id[] and write 1 to id_state
//else set id_state = 0

}

void setID(){
    checkID();
    if (id_state == 0){
    //Write EEPROM
    PRINTLN(id);
    }
    else if (id_state == 1){
    // do nothing
    } 
    else {
    PRINTLN ("Udefined ID STATE");
    }

}

void setup() {
  
  //////////////////////////////////////////////////////////
  ////                                                  ////
  ////  LCD SETUP   INIT                                ////
  ////                                                  ////
  //////////////////////////////////////////////////////////
  pinMode(bkpin, OUTPUT); //backlight setup
  pinMode(8, OUTPUT);
  analogWrite(bkpin, bkbright);


  
  display.begin(); //display iniT
  display.setContrast(lcdctr);
  display.clearDisplay(); //clears buffer
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  //void setTextColor(uint16_t color, uint16_t backgroundcolor);
  display.setTextSize(1.5);
  display.setTextWrap(true);
  display.println("TESTE");
  //display.print("done setup()");
  display.display();
  //delay(2000);
  
  
  Serial.begin(115200); 
  printf_begin();
  Serial.println("webtag1.0");
  
  
  
  //////////////////////////////////////////////////////////
  ////                                                  ////
  ////  RADIO SETUP   INIT                              ////
  ////                                                  ////
  //////////////////////////////////////////////////////////
  
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
  display.print("done setup()");
  display.display();
  #endif

}

/////////////////////////////////////// 
///// END SETUP()                 ///// 
///////////////////////////////////////


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



void checkCMD(char* arrCMD){
  String inCMD;
  inCMD = arrCMD;
  Serial.print("inCMD: ");
  Serial.println( inCMD);
  Serial.print("arrCMD: ");
  Serial.println(arrCMD);
  
    if (inCMD.substring(0,2) == "++"){
        PRINTLN("Command mode"); 
        PRINTLN(inCMD.substring(2,6));
        PRINTLN(inCMD.substring(6, 8));
//        PRINTLN
      
      
      //id setup(); //proto functions...
        if (inCMD.substring(2,4) == "ID" && inCMD.length() > 4){
          String arg;
          
          arg += inCMD[4];
          arg += inCMD[5];
          PRINT("The ID is: ");
          PRINTLN(arg);
        }
        else if(inCMD.substring(2,6) == "STID" && inCMD.length() > 6){
          String idin;
          idin +=  inCMD.substring(6, 8);
          idin.toCharArray(id, 3);
          setID();
          //ID SET Function -- EEPROM
        }
        
        
        else {
          Serial.println("Invalid Command ID or unidentified message");
        }
        

    }
}
 
 
 
/////////////////////////////////////// 
///// MAIN LOOP                   ///// 
///////////////////////////////////////


void loop() {
  
//  radio.stopListening();
//  char *c = "A";
//  radio.write(c, 1);
//  radio.startListening();

   //give sometime to reply back with command
  
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
        checkCMD(c);
       
        bckBlink();
        display.clearDisplay();
        bckBlink();
        
        //tone(10, 440);
        //delay(200);
        bckBlink();
        //noTone(10);
        
        display.print (c);
        display.display();
        
//        tone(10, 880);
//        delay(200);
//        noTone(10);
//        tone(10, 335, 800);
//        delay(300);
//        noTone(10);
//        tone(10, 1000, 1000);
//        delay(500);
//        noTone(10);
        bckBlink();
        
        delay(250);
        //sCmd.readArray(c);
        
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
}
