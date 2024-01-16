
/*

THE HALO LIGHT CONTROLLER BASIC VERSION 2.5 (FOR TEENSY 3.2)
COPYRIGHT 2021 CASEY ATTEBERY, RESONANT DEVICES

*/

////////////////////////////////////////////////////////////////////////////////////
// RING LIGHT NUMBERS
// THESE ARE THE NUMBERS OF PIXELS PER RING LIGHTS, R1 BEING THE OUTER RING, R4 IS THE INNER RING
const int R1 = 16; // OUTER RING
const int R2 = 8; // INNER RING
const int R3 = 0; // INNER RING
////////////////////////////////////////////////////////////////////////////////////
/////////////////// DO NOT ALTER THE CODE BELOW THIS LINE!!! ///////////////////////
////// GO NO FURTHER. THE WRATH OF KHAN SHALL BE WAGED AGAINST YOUR PLANET! ////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////
// These are included libraries, definitions and assignments.
/////////////////////////////

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <Encoder.h>
#define DATARING 10
#define DATALED 8
#define PinA 31
#define PinB 30
#define Btn 7
#define RED 16
#define GREEN 22
#define BLUE 17
#define DIMM 14
#define Rone 2
#define Rtwo 3
#define Rthree 4
#define Rfour 6
#define RCKR 33
#define MMRY 5
Encoder Enc(PinA, PinB); const int TOT=R1+R2+R3;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(TOT, DATARING, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel testLED = Adafruit_NeoPixel(1, DATALED, NEO_RGB + NEO_KHZ800);
byte RINGone; byte RINGtwo; byte RINGthree; byte RINGfour;
boolean modeOne = true; boolean modeTwo = true; boolean modeThree = true; boolean modeFour;
boolean onecount = true; boolean twocount = true; boolean threecount = true; boolean fourcount;
boolean modeMem = true;  boolean OPTL = true; boolean OPTM = true; boolean encode = true; boolean encodecount = true; 
boolean membut = digitalRead(MMRY); boolean tog = digitalRead(RCKR); //boolean tog = analogRead(RCKR);
int startAddress=0; int pixelsL[312]; int pixelsM[312];
int Pos=0; int PosL=0; int b=1; int r=1; int PIX;  long spot;
int valRotary=0; int startnum=0; int endnum=R1; boolean state=HIGH; int lastpix;
int CRN; int CGN; int CBN; 


/////////////////////////////
// This is the setup, identifying the pin purposes and calling the LEDs to action.
/////////////////////////////

void setup() {
  ring.begin();  testLED.begin();  delay(10); testLED.setBrightness(35); ring.show(); testLED.show();
  //pinMode(PinA, INPUT_PULLUP); pinMode(PinB, INPUT_PULLUP); 
  pinMode(Btn, INPUT_PULLUP);
  pinMode(MMRY, INPUT_PULLUP); pinMode(RCKR, INPUT_PULLUP);
  pinMode(Rone, INPUT_PULLUP); pinMode(Rtwo, INPUT_PULLUP); pinMode(Rthree, INPUT_PULLUP); pinMode(Rfour, INPUT_PULLUP); pinMode(Btn, INPUT_PULLUP); 
  pinMode(DIMM, INPUT_PULLUP); pinMode(RED, INPUT_PULLUP); pinMode(GREEN, INPUT_PULLUP); pinMode(BLUE, INPUT_PULLUP);
}


//////////////////////////////
// This is the MAIN LOOP, toggling between Mode 1 (Live Action Mode) and Mode 0 (Menu Load Mode).
//////////////////////////////

void loop() {
  delay(10); boolean tog = digitalRead(RCKR); int DIAL0 = analogRead(DIMM);   
 if (tog == HIGH) { 
    if (state==HIGH) {Enc.write(0); r=1; ring.setPixelColor(0,pixelsL[0],pixelsL[1],pixelsL[2]);}
    float B = ((DIAL0 * .248)-.5); ring.setBrightness(B); testLED.setPixelColor(0, 0); doAction(); state=LOW;}
 else if (tog == LOW) { 
    if (state==LOW) {Enc.write(0); r=1; }
    float B2 = ((DIAL0 * .24)+6); ring.setBrightness(B2); doMenuLoad(); state=HIGH;} 
  testLED.show(); ring.show();
}


//////////////////////////////
// These lines are for writing to memory else do live action mode.
//////////////////////////////
    
void doAction() { 
  boolean membut = digitalRead(MMRY);
  RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree); RINGfour = digitalRead(Rfour);
  if (membut == LOW) { 
    delay(30); Enc.write(0);
    if (OPTM == true) { startAddress = 0; }
    else if (OPTM == false) { startAddress = 72; }
    writeToEEPROM(startAddress, pixelsL, 72); OPTM=!OPTM;}  
doLiveAction();
}


//////////////////////////////
// These are for the live-action ring/encoder play.
//////////////////////////////

void doLiveAction() { 
 int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE);
 float CR = (DIAL1*.24); float CG = (DIAL2*.24); float CB = (DIAL3*.24);
if (RINGone == LOW) {
    delay(10); r=1; 
    if (onecount == true) {
      Pos=0; Enc.write(0); onecount=!onecount; ring.setPixelColor(0, CR, CG, CB); 
      if (twocount == false) {twocount=!twocount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }    
else if (RINGtwo == LOW) {
    delay(10); r=2;  
    if (twocount == true) {
      Pos=0; Enc.write(0); twocount=!twocount; ring.setPixelColor(R1, CR, CG, CB); 
      if (onecount == false) {onecount=!onecount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
else if (RINGthree == LOW) {
    delay(10); r=3;  
    if (threecount == true) {
      Pos=0; Enc.write(0); threecount=!threecount; ring.setPixelColor(R1+R2, CR, CG, CB); 
      if (onecount == false) {onecount=!onecount;}
      if (twocount == false) {twocount=!twocount;}
      } Enc.write(0);
    }
if (r==1) {startnum=0; endnum=R1;}
else if (r==2) {startnum=R1; endnum=R2;}
else if (r==3) {startnum=R1+R2; endnum=R3;}
int count=100; spot = Enc.read(); Pos = spot>>2; int p;
if (Pos != count ) { delay(2);
  valRotary = (((Pos % endnum)+endnum) % endnum); count = Pos; PIX = abs(startnum + valRotary); p=3*PIX;
  pixelsL[p] = CR; pixelsL[p+1] = CG; pixelsL[p+2] = CB; 
}
for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsL[jj], pixelsL[jj+1], pixelsL[jj+2]);} ring.show();
for (int i=0; i<TOT; i++) {pixelsM[i]=pixelsL[i];}
}


//////////////////////////////
// These lines toggle The Halo into menu/load mode.
//////////////////////////////
boolean memcnt=true;
void doMenuLoad() { 
  boolean membut = digitalRead(MMRY);
  RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree);
if (membut == LOW) { 
    delay(50); r=1; Enc.write(0);
    if (OPTL == true) {startAddress = 0;}
    else if (OPTL == false) {startAddress = 312;}
    readFromEEPROM(startAddress, pixelsM, 312); OPTL=!OPTL; 
    for (int j=0; j<R1+R2+R3; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);} 
    for (int j=R1+R2+R3; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show(); 
    testLED.setPixelColor(0,0); testLED.show();
    }
    delay(50);
if (digitalRead(Btn)==LOW) {delay(20); encode=true; encodecount=!encodecount; 
  if (PIX<TOT) { ring.setPixelColor(PIX, pixelsM[PIX], pixelsM[3*PIX+1], pixelsM[3*PIX+2]);}
  else if (TOT<=PIX) { ring.setPixelColor(PIX, 0);}
  if (memcnt == false) {writeToEEPROM(startAddress, pixelsM, 72);}
  memcnt=!memcnt;
}
if (encodecount == false) {doAlterArray(); }
else if (encodecount == true) {testLED.setPixelColor(0,0); testLED.show(); ring.show();}  
else {ring.setPixelColor(PIX, pixelsM[3*PIX], pixelsM[3*PIX+1], pixelsM[3*PIX+2]); ring.show();}  

  ///this was the change
for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);}; 
delay(50);                                           
}


//////////////////////////////
// These lines alter stored arrays via the encoder as a pixel selector.
//////////////////////////////

void doAlterArray() {
  int PosL; int count=100; spot = Enc.read(); PosL = spot>>2;
if (encode == true && encodecount == false) {encode=!encode; }
if (RINGone == LOW) { 
    delay(30); r=1;
    if (onecount == true) {
      PosL=0; onecount=!onecount; Enc.write(0);
      if (twocount == false) {twocount=!twocount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0); 
}    
else if (RINGtwo == LOW) { 
    delay(30); r=2; 
    if (twocount == true) {
      PosL=0; twocount=!twocount; Enc.write(0);
      if (onecount == false) {onecount=!onecount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
}
else if (RINGthree == LOW) { 
    delay(30); r=3;
    if (threecount == true) {
      PosL=0; threecount=!threecount; Enc.write(0);
      if (onecount == false) {onecount=!onecount;}
      if (twocount == false) {twocount=!twocount;}
      } Enc.write(0);  
} 
if (r==1) {startnum=0; endnum=R1;}
else if (r==2) {startnum=R1; endnum=R2;}
else if (r==3) {startnum=R1+R2; endnum=R3;}
if (PosL != count ) { delay(2);
  valRotary = (((PosL % endnum)+endnum) % endnum); count = PosL; PIX = abs(startnum + valRotary); int p=3*PIX; int pl=3*lastpix;
  int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE);
  CRN = (DIAL1*.24); CGN = (DIAL2*.24); CBN = (DIAL3*.24); testLED.setPixelColor(0, CRN, CGN, CBN); 
if (digitalRead(Rfour)==LOW) { pixelsM[pl]=CRN; pixelsM[pl+1]=CGN; pixelsM[pl+2]=CBN;}
  ring.setPixelColor(lastpix, pixelsM[pl], pixelsM[pl+1], pixelsM[pl+2]);
  ring.setPixelColor(PIX, 0); ring.show(); lastpix=PIX;   
}
/// this was the change!
for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);}; ring.setPixelColor(PIX, 0); ring.show();
}


//////////////////////////////
//  These lines below are for writing to and reading from the EEPROM memory. Alter to handle SPI Flash.
//////////////////////////////

void writeToEEPROM(int address, int pixelsL[], int arraySize) {
  int addressIndex = startAddress;
    for (int i=0; i<arraySize; i++) { EEPROM.write(addressIndex, pixelsL[i]); addressIndex++;}
}

void readFromEEPROM(int address, int pixelsM[], int arraySize) {
  int addressIndex = startAddress;
    for (int i=0; i<arraySize; i++) { pixelsM[i] = EEPROM.read(addressIndex);  addressIndex++;}
}
