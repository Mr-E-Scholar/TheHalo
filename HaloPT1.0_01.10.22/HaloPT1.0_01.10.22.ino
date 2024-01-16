/*
THE HALO LIGHT CONTROLLER PREMIUM VERSION 1.0 (FOR TEENSY 3.2)
COPYRIGHT 12/11/2021 CASEY ATTEBERY, RESONANT DEVICES
*/

////////////////////////////////////////////////////////////////////////////////////
// RING LIGHT NUMBERS
// THESE ARE THE NUMBERS OF PIXELS PER RING LIGHTS, R1 BEING THE OUTER RING, R4 IS THE INNER RING
const int R1 = 45; // OUTER RING
const int R2 = 35; // MIDDLE RING
const int R3 = 24; // INNER RING
////////////////////////////////////////////////////////////////////////////////////
/////////////////// DO NOT ALTER THE CODE BELOW THIS LINE!!! ///////////////////////
////// GO NO FURTHER. THE WRATH OF KHAN SHALL BE WAGED AGAINST YOUR PLANET! ////////
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////
// These are included libraries, definitions and assignments.
/////////////////////////////
#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <Encoder.h>
#include <TimeLib.h>  
#include <Wire.h> 
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
#define SAVE 6
#define RCKR 33
#define NXT 5
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCK 13
#define TFT_CS 15
#define TFT_DC 19
#define TFT_RST 39
#define SD_CS 9

Encoder Enc(PinA, PinB); const int TOT=R1+R2+R3; int valENC=0;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(TOT, DATARING, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel testLED = Adafruit_NeoPixel(1, DATALED, NEO_RGB + NEO_KHZ800);
byte RINGone; byte RINGtwo; byte RINGthree; byte RINGfour;
boolean modeOne = true; boolean modeTwo = true; boolean modeThree = true; boolean modeFour;
boolean onecount = true; boolean twocount = true; boolean threecount = true; boolean fourcount;
boolean modeMem = true;  boolean OPTL = true; boolean OPTM=true; boolean encode = true; boolean encodecount = true; boolean encodeL = true; boolean encodecountL = true; 
boolean nextbut = digitalRead(NXT); boolean tog = digitalRead(RCKR); boolean flip=true;
int startAddress=0; int startAddressL=0; int pixelsL[312]; int pixelsM[312]; int pixelsN[312];
int Pos=0; int PosL=0; int b=1; int r=1; int PIX;  long spot; long spotL;
int valRotary=0; int startnum=0; int endnum=R1; boolean state=HIGH; int lastpix;
int CR; int CG; int CB; int CRN; int CGN; int CBN; int NB; int nNB; int nCR; int nCG; int nCB; int nCRN; int nCGN; int nCBN; int memslot=1; int MEMS=0;
int count=0; int S=0;
time_t t;// = now();

boolean mcnt=true; boolean scnt=true; boolean pcnt=true; boolean acnt=true; boolean hcnt=true; boolean rcnt=true; boolean sdcnt=true; boolean ccnt=true; 
boolean lcnt=true; boolean cacnt=true; boolean tcnt=true; boolean retcnt=true; boolean plcnt=true; 
boolean rectanglecountone=false; boolean rectanglecounttwo=false; boolean rectwocountone=false; boolean rectwocounttwo=false; 
int acounter=0; int tcounter=0; 
String men="off"; String seq; int strt=1; String len="length"; String opt="N"; String cho="choicemenu"; 
int PLACE=0; int MENOP; int SEQOP; int PATOP; int ANIMOP; int LNGTHOP; int AROP=1; int REPOP=1; int CAOP=1; int ARROP=1; int TIMEOP=10; 
int seqlist[6]; int timelist[6]; 
int totalarrays=6;  int arrcursorstrt; int timecursorstrt; int ac=1; int acn=10; int tc=10; int tcn=10; int repnum=1;
int inc=0; int Tc; int arraynumber=1; int timelength=10; int TOTAL=1; int pixelsS1[1872]; int pixelsS2[1872];
boolean startcounter=true; int mancount=0; int RUNOP=1; String br="go";





#include <ST7789_t3.h>
ST7789_t3 tft = ST7789_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

/////////////////////////////
// This is the setup, identifying the pin purposes and calling the LEDs to action.
/////////////////////////////

void setup() {

  if (startcounter==true){
  for (int j=0; j<6; j++){ seqlist[j]=1; timelist[j]=10; }
  tft.init(240, 320, SPI_MODE2); tft.fillScreen(ST7735_BLACK); tft.setRotation(2);
  ring.begin();  testLED.begin();  delay(10); testLED.setBrightness(35); ring.show(); testLED.show();
  pinMode(Btn, INPUT_PULLUP);
  pinMode(NXT, INPUT_PULLUP); pinMode(RCKR, INPUT_PULLUP);
  pinMode(Rone, INPUT_PULLUP); pinMode(Rtwo, INPUT_PULLUP); pinMode(Rthree, INPUT_PULLUP); pinMode(SAVE, INPUT_PULLUP);
  pinMode(DIMM, INPUT_PULLUP); pinMode(RED, INPUT_PULLUP); pinMode(GREEN, INPUT_PULLUP); pinMode(BLUE, INPUT_PULLUP);
  tft.setTextWrap(true); tft.setCursor(22, 65); tft.setTextSize(4); tft.setTextColor(0x067A); tft.print("THE HALO");
 delay(500);
 tft.setCursor(92, 110); tft.setTextSize(2); tft.setTextColor(ST7735_YELLOW); tft.print("from");
 delay(400);
 tft.setCursor(26, 140); tft.setTextSize(4); tft.setTextColor(ST7735_MAGENTA); tft.print("RESONANT"); tft.setCursor(36, 175); tft.print("DEVICES");
delay(2000); startcounter=false;
  }
tft.fillScreen(ST7735_BLACK); tft.setTextColor(ST7735_WHITE); tft.setTextSize(1);
tft.setCursor(90, 310); tft.print("Premium v1.0");
tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.drawLine(0, 153, 240, 153, 0x8811); 
tft.drawLine(120, 15, 120, 153, 0x8811); tft.drawLine(0, 61, 120, 61, 0x8811); tft.drawLine(0, 107, 120, 107, 0x8811);
tft.setTextSize(2);
tft.setTextColor(ST7735_RED); tft.setCursor(15, 33); tft.print("R =");
tft.setTextColor(ST7735_GREEN); tft.setCursor(15, 79); tft.print("G =");
tft.setTextColor(ST7735_BLUE); tft.setCursor(15, 125); tft.print("B ="); 
tft.setTextColor(ST7735_YELLOW); tft.setCursor(145, 45); tft.print("DIMMER"); tft.setCursor(151, 65); tft.print("LEVEL");
tft.setTextSize(3); tft.setTextColor(0x4416); tft.setCursor(22, 185); tft.print("COLOR ARRAY");

}


//////////////////////////////
// This is the MAIN LOOP, toggling between Mode 1 (Live Action Mode) and Mode 0 (Menu Load Mode).
//////////////////////////////

void loop() {
boolean tog = digitalRead(RCKR); int DIAL0 = analogRead(DIMM); int B=map(DIAL0,0,1023,8,255); int NB=map(DIAL0,0,1023,0,100);    
if (men=="menu") {SEQreadFromEEPROM(0, pixelsS1, 1872);  for (int i=0; i<1872; i++) {pixelsS2[i]=pixelsS1[i];} doMenu();}
if (men=="seq" && seq=="seqmenu") {doSequences();} 
if (men=="pat") {doPatterns();}
if (men=="heart") {doHeartMonitor();}
if (men=="sd") {doSD();}
if (men=="custom") {doCustom();}
if (men=="reset") {doReset();}

if (seq=="length") {doLength();}
if (seq=="choose") {doChooseArrays();}
if (seq=="trans") {doTransitions();}
if (seq=="play") {doPlay();}
if (seq=="anim") {doAnimations();}
if (seq=="manual"){doManualRun();}


if (men=="off"){
 if (tog == HIGH) { ring.setBrightness(B);
    if (state==HIGH) {Enc.write(0); r=1; ring.setPixelColor(0,pixelsL[0],pixelsL[1],pixelsL[2]); OPTM=true; flip=true;
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(58, 0); tft.print("The Halo - Live Mode");}
    testLED.setPixelColor(0, 0); doAction(); state=LOW; }
 else if (tog == LOW) { 
 if (state==LOW) {Enc.write(0); r=1; tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(58, 0); tft.print("The Halo - Load Mode");}
  if (OPTM==true) {MEMS=memslot-1; flip=true;
    startAddress = 312*(MEMS);
    readFromEEPROM(startAddress, pixelsN, 312); for (int i=0; i<312; i++) {pixelsM[i]=pixelsN[i];}
   for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsN[jj], pixelsN[jj+1], pixelsN[jj+2]);} ring.show(); OPTM=false;
   } 
 doMenuLoad(); state=HIGH;} 
  testLED.show(); ring.show(); 
  tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(172, 105);
  if (NB<10 && nNB<80) {
  if (nNB!=NB) {tft.fillRect(140,97,70,50,ST7735_BLACK);} 
  tft.setCursor(172, 105); nNB=NB;}
else if (9<NB && NB<100 && nNB<101) {
  if (nNB!=NB) {tft.fillRect(140,97,70,50,ST7735_BLACK);}
  tft.setCursor(162, 105); nNB=NB;}
else if (NB==100) {tft.setCursor(152, 105); nNB=NB;}
tft.print(int(NB));
}


}


//////////////////////////////
// These lines are for writing to memory else do live action mode.
//////////////////////////////
    
void doAction() { 
  tft.setTextSize(6); tft.setTextColor(0xF731, ST7735_BLACK); tft.setCursor(105, 235); tft.print(memslot);
  RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree);
if (digitalRead(Btn)==LOW) {delay(200); encodeL=true; encodecountL=!encodecountL;}
if (digitalRead(NXT)==LOW) {delay(200); memslot=memslot+1; if (memslot == 7){memslot=1;} if (flip==true){time_t t = now(); S=second(t); flip=false;} delay(50);} time_t t = now();
if (digitalRead(NXT)==LOW && second(t)==1+S){flip=true; men="menu"; Enc.write(0); MENOP=1; tft.fillScreen(ST7735_BLACK);}  //doMenu();}
  else if (digitalRead(NXT)==HIGH && second(t)==1+S){flip=true;}
if (encodecountL == false) {doAlterArrayLive(); }
else if (encodecountL == true) {testLED.setPixelColor(0,0); testLED.show(); doLiveAction();}   
}


//////////////////////////////
// These are for the live-action ring/encoder play.
//////////////////////////////

void doLiveAction() { 

if (digitalRead(SAVE)==LOW) {delay(100); if (flip==true){time_t t = now(); S=second(t); flip=false;}} ;
if (digitalRead(SAVE)==LOW && second(t)==2+S){flip=true; for (int i=0; i<312; i++) {pixelsL[i]=pixelsM[i];}}
 int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE);  boolean savebut = digitalRead(SAVE);
CR = map(DIAL1,0,1023,0,255); CG = map(DIAL2,0,1023,0,255); CB = map(DIAL3,0,1023,0,255);
  if (savebut == LOW) { 
    delay(100); MEMS=memslot-1;
    startAddress = 312*(MEMS);
    writeToEEPROM(startAddress, pixelsL, 312);} 
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
   if (CR<10 && nCR<256) { 
    if (nCR!=CR) {tft.fillRect(65,79,50,20,ST7735_BLACK); }
    tft.setCursor(94, 79); nCR=CR;}
  else if (9<CR && CR<100 && nCR<256) {
    if (nCR!=CR) {tft.fillRect(65,79,50,20,ST7735_BLACK); }
    tft.setCursor(82, 79); nCR=CR;}
  else if (99<CR) {tft.setCursor(70, 79); nCR=CR;}
  tft.print(CR); 
 tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  if (CG<10 && nCG<256) { 
    if (nCG!=CG) {tft.fillRect(65,33,50,20,ST7735_BLACK);} 
    tft.setCursor(94, 33); nCG=CG;}
  else if (9<CG && CG<100 && nCG<256) { 
    if (nCG!=CG) {tft.fillRect(65,33,50,20,ST7735_BLACK);} 
    tft.setCursor(82, 33); nCG=CG;}
  else if (99<CG) {tft.setCursor(70, 33); nCG=CG;}
  tft.print(CG); 
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
   if (CB<10 && nCB<256) {
    if (nCB!=CB) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(94, 125); nCB=CB;}
  else if (9<CB && CB<100 && nCB<256) { 
    if (nCB!=CB) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(82, 125); nCB=CB;}
  else if (99<CB) {tft.setCursor(70, 125); nCB=CB;}
  tft.print(CB);
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
if (Pos != count ) { //delay(2);
  valRotary = (((Pos % endnum)+endnum) % endnum); count = Pos; PIX = abs(startnum + valRotary); p=3*PIX;
  pixelsL[p] = CR; pixelsL[p+1] = CG; pixelsL[p+2] = CB; 
}
for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsL[jj], pixelsL[jj+1], pixelsL[jj+2]);} ring.show();
}  




//////////////////////////////
// These lines toggle The Halo into menu/load mode.
//////////////////////////////
boolean memcnt=true; 
void doMenuLoad() { int DIAL0 = analogRead(DIMM); int B=map(DIAL0,0,1023,1,255); ring.setBrightness(B); ring.show();
 boolean nextbut = digitalRead(NXT); RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree);
 tft.setTextSize(6); tft.setTextColor(0xF731, ST7735_BLACK); tft.setCursor(105, 235); tft.print(memslot);
 if (nextbut == LOW) {delay(300);  memslot=memslot+1; if (memslot==7) {memslot=1;} MEMS = memslot-1;
     r=1; tft.setCursor(105, 235); startAddress = 312*(MEMS);
    readFromEEPROM(startAddress, pixelsM, 312); count=0;
    for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);} 
    ring.show(); testLED.setPixelColor(0,0); testLED.show();}
   delay(100);
if (digitalRead(Btn)==LOW) {delay(100); encode=true; encodecount=!encodecount; 
  if (memcnt == false) {writeToEEPROM(startAddress, pixelsM, 312); ring.setPixelColor(PIX, pixelsM[PIX], pixelsM[3*PIX+1], pixelsM[3*PIX+2]); ring.show();}
  memcnt=!memcnt;
}
if (encodecount == false) {doAlterArray(); }
else if (encodecount == true) {testLED.setPixelColor(0,0); testLED.show(); ring.show();
if (digitalRead(SAVE)==LOW) {delay(100); if (flip==true){time_t t = now(); S=second(t); flip=false;}} time_t t = now();
if (digitalRead(SAVE)==LOW && second(t)==2+S){flip=true; for (int i=0; i<312; i++) {pixelsL[i]=pixelsM[i];}}
}  
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

int pl=3*lastpix;
if (PosL != count ) { 
  valRotary = (((PosL % endnum)+endnum) % endnum); count = PosL; PIX = abs(startnum + valRotary); 
  int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE);
  CRN = map(DIAL1,0,1023,0,255); CGN = map(DIAL2,0,1023,0,255); CBN = map(DIAL3,0,1023,0,255); testLED.setPixelColor(0, CRN, CGN, CBN); 
  tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
   if (CRN<10 && nCRN<256) { 
    if (nCRN!=CRN) {tft.fillRect(65,79,50,20,ST7735_BLACK); }
    tft.setCursor(94, 79); nCRN=CRN;}
  else if (9<CRN && CRN<100 && nCRN<256) {
    if (nCRN!=CRN) {tft.fillRect(65,79,50,20,ST7735_BLACK); }
    tft.setCursor(82, 79); nCRN=CRN;}
  else if (99<CRN) {tft.setCursor(70, 79); nCRN=CRN;}
  tft.print(CRN); 
 tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  if (CGN<10 && nCGN<256) { 
    if (nCGN!=CGN) {tft.fillRect(65,33,50,20,ST7735_BLACK);}
    tft.setCursor(94, 33); nCGN=CGN;}
  else if (9<CGN && CGN<100 && nCGN<256) { 
    if (nCGN!=CGN) {tft.fillRect(65,33,50,20,ST7735_BLACK);}
    tft.setCursor(82, 33); nCGN=CGN;}
  else if (99<CGN) {tft.setCursor(70, 33); nCGN=CGN;}
  tft.print(CGN);  
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
   if (CBN<10 && nCBN<256) {
    if (nCBN!=CBN) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(94, 125); nCBN=CBN;}
  else if (9<CBN && CBN<100 && nCBN<256) { 
    if (nCBN!=CBN) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(82, 125); nCBN=CBN;}
  else if (99<CBN) {tft.setCursor(70, 125); nCBN=CBN;}
  tft.print(CBN);
  if (digitalRead(SAVE)==LOW) { pixelsM[pl]=CRN; pixelsM[pl+1]=CGN; pixelsM[pl+2]=CBN;}
  ring.setPixelColor(PIX, pixelsM[pl], pixelsM[pl+1], pixelsM[pl+2]); ring.show(); lastpix=PIX;
}

for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);} ring.show(); delay(12); 
            ring.setPixelColor(PIX, abs(255-pixelsM[3*PIX]), abs(255-pixelsM[3*PIX+1]), abs(255-pixelsM[3*PIX+2])); ring.show(); delay(12);
            ring.setPixelColor(PIX, pixelsM[3*PIX], pixelsM[3*PIX+1], pixelsM[3*PIX+2]); ring.show();
}



//////////////////////////////
//  These lines alter the Live Action Array and restore it as the live array.
//////////////////////////////

void doAlterArrayLive() {
 int count=100; spotL = Enc.read(); PosL = spotL>>2; //int p;
if (encodeL== true && encodecountL == false) {encodeL=!encodeL; }
if (RINGone == LOW) {
    delay(30); r=1; 
    if (onecount == true) {
      PosL=0; Enc.write(0); onecount=!onecount;  
      if (twocount == false) {twocount=!twocount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }    
else if (RINGtwo == LOW) {
    delay(30); r=2;  
    if (twocount == true) {
      PosL=0; Enc.write(0); twocount=!twocount;  
      if (onecount == false) {onecount=!onecount;}
      if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
else if (RINGthree == LOW) {
    delay(30); r=3;  
    if (threecount == true) {
      PosL=0; Enc.write(0); threecount=!threecount; 
      if (onecount == false) {onecount=!onecount;}
      if (twocount == false) {twocount=!twocount;}
      } Enc.write(0);
    }
if (r==1) {startnum=0; endnum=R1;}
else if (r==2) {startnum=R1; endnum=R2;}
else if (r==3) {startnum=R1+R2; endnum=R3;}
if (PosL != count ) {
  valRotary = (((PosL % endnum)+endnum) % endnum); count = PosL; PIX = abs(startnum + valRotary); int pl=3*lastpix;
  int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE);
  CRN = map(DIAL1,0,1023,0,255); CGN = map(DIAL2,0,1023,0,255); CBN = map(DIAL3,0,1023,0,255); testLED.setPixelColor(0, CRN, CGN, CBN); 
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
 if (CRN<10 && nCRN<256) { 
    if (nCRN!=CRN) {tft.fillRect(65,79,50,20,ST7735_BLACK);} 
    tft.setCursor(94, 79); nCRN=CRN;}
  else if (9<CRN && CRN<100 && nCRN<256) {
    if (nCRN!=CRN) {tft.fillRect(65,79,50,20,ST7735_BLACK); }
    tft.setCursor(82, 79); nCRN=CRN;}
  else if (99<CRN) {tft.setCursor(70, 79); nCRN=CRN;}
  tft.print(CRN); 
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  if (CGN<10 && nCGN<256) { 
    if (nCGN!=CGN) {tft.fillRect(65,33,50,20,ST7735_BLACK);}
    tft.setCursor(94, 33); nCGN=CGN;}
  else if (9<CGN && CGN<100 && nCGN<256) { 
    if (nCGN!=CGN) {tft.fillRect(65,33,50,20,ST7735_BLACK);}
    tft.setCursor(82, 33); nCGN=CGN;}
  else if (99<CGN) {tft.setCursor(70, 33); nCGN=CGN;}
  tft.print(CGN);   
tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
   if (CBN<10 && nCBN<256) {
    if (nCBN!=CBN) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(94, 125); nCBN=CBN;}
  else if (9<CBN && CBN<100 && nCBN<256) { 
    if (nCBN!=CBN) {tft.fillRect(65,125,50,20,ST7735_BLACK); }
    tft.setCursor(82, 125); nCBN=CBN;}
  else if (99<CBN) {tft.setCursor(70, 125); nCBN=CBN;}
  tft.print(CBN); 
if (digitalRead(SAVE)==LOW) { delay(10); pixelsL[pl]=CRN; pixelsL[pl+1]=CGN; pixelsL[pl+2]=CBN;}
  ring.setPixelColor(lastpix, pixelsL[pl], pixelsL[pl+1], pixelsL[pl+2]); ring.show(); lastpix=PIX;   
}
for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsL[jj], pixelsL[jj+1], pixelsL[jj+2]);} ring.show(); delay(42); 
            ring.setPixelColor(PIX, abs(255-pixelsL[3*PIX]), abs(255-pixelsL[3*PIX+1]), abs(255-pixelsL[3*PIX+2])); ring.show(); delay(42);
            ring.setPixelColor(PIX, pixelsL[3*PIX], pixelsL[3*PIX+1], pixelsL[3*PIX+2]); ring.show();
//for (int i=0; i<312; i++) {pixelsM[i]=pixelsL[i];}
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



//MAIN MENU
void doMenu() { men="menu";
if (mcnt==true) { tft.fillScreen(ST7735_BLACK);
tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811);  
tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(40, 30); tft.print("MAIN MENU"); tft.drawLine(0, 60, 240, 60, 0x8811); 
tft.drawLine(0, 101, 240, 101, 0x8811); tft.drawLine(0, 142, 240, 142, 0x8811); tft.drawLine(0, 183, 240, 183, 0x8811);
tft.drawLine(0, 224, 240, 224, 0x8811); tft.drawLine(0, 265, 240, 265, 0x8811); 
mcnt=!mcnt;
}

spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 6)+6) % 6); count = PLACE; MENOP = abs(valENC+1);}
tft.setTextSize(2); 

if (MENOP==1){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 73); tft.print("1. SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); men="seq"; scnt=true; SEQOP=1; Enc.write(0); doSequences();}
}
  else if (MENOP!=1 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 73); tft.print("1. SEQUENCES");}
  
if (MENOP==2){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 114); tft.print("2. PATTERNS");
if (digitalRead(Btn)==LOW) {delay(650); men="pat"; pcnt=true; doPatterns();}
}
  else if (MENOP!=2 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 114); tft.print("2. PATTERNS");}
  
if (MENOP==3){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 155); tft.print("3. HEART MONITOR");
if (digitalRead(Btn)==LOW) {delay(650); men="heart"; hcnt=true; doHeartMonitor();}
}
  else if (MENOP!=3 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 155); tft.print("3. HEART MONITOR");}
  
if (MENOP==4){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 196); tft.print("4. SD CARD");
if (digitalRead(Btn)==LOW) {delay(650); men="sd"; sdcnt=true; doSD();}
}
  else if (MENOP!=4 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 196); tft.print("4. SD CARD");}
  
if (MENOP==5){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 237); tft.print("5. CUSTOM LED GRID");
if (digitalRead(Btn)==LOW) {delay(650); men="custom"; ccnt=true; doCustom();}
}
  else if (MENOP!=5 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 237); tft.print("5. CUSTOM LED GRID");}    
      
if (MENOP==6){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("6. RETURN TO HALO");
if (digitalRead(Btn)==LOW) {delay(650); men="off"; mcnt=true; Enc.write(0); setup();}
//if (digitalRead(Btn)==LOW) {delay(650); men="reset"; rcnt=true; doReset();}    men="off"; mcnt=true;  tft.fillScreen(ST7735_BLACK); setup();
  }
  else if (MENOP!=6 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("6. RETURN TO HALO");}

}



void doSequences() {seq="seqmenu";
if (scnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(40, 30); tft.print("SEQUENCES"); tft.drawLine(0, 60, 240, 60, 0x8811); 
tft.drawLine(0, 101, 240, 101, 0x8811); tft.drawLine(0, 142, 240, 142, 0x8811); tft.drawLine(0, 183, 240, 183, 0x8811);
tft.drawLine(0, 224, 240, 224, 0x8811); tft.drawLine(0, 265, 240, 265, 0x8811);
scnt=!scnt;
}

spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 6)+6) % 6); count = PLACE; SEQOP = abs(valENC+1);}
tft.setTextSize(2); 

if (SEQOP==1){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 73); tft.print("1. SEQUENCE LENGTH");
  if (digitalRead(Btn)==LOW) {delay(650); seq="length"; lcnt=true; LNGTHOP=1; Enc.write(0); doLength();}
}
else if (SEQOP!=1 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 73); tft.print("1. SEQUENCE LENGTH");}
  
if (SEQOP==2){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 114); tft.print("2. CHOOSE ARRAYS");
if (digitalRead(Btn)==LOW) {delay(650); cacnt=true; Enc.write(0); CAOP=1; seq="choose"; doChooseArrays();
}
}
else if (SEQOP!=2 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 114); tft.print("2. CHOOSE ARRAYS");}
  
if (SEQOP==3){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 155); tft.print("3. TRANSITIONS");
if (digitalRead(Btn)==LOW) {delay(650); seq="trans"; tcnt=true; doTransitions();}
}
  else if (SEQOP!=3 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 155); tft.print("3. TRANSITIONS");}
  
if (SEQOP==4){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 196); tft.print("4. ANIMATIONS");
if (digitalRead(Btn)==LOW) {delay(650); seq="anim"; acnt=true; doAnimations();}
}
  else if (SEQOP!=4 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 196); tft.print("4. ANIMATIONS");}
  
if (SEQOP==5){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 237); tft.print("5. RUN SEQUENCE");
if (digitalRead(Btn)==LOW) {delay(650); seq="play"; plcnt=true; Enc.write(0); RUNOP=1; inc=0; doPlay();}
}
  else if (SEQOP!=5 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 237); tft.print("5. RUN SEQUENCE");}    
      
if (SEQOP==6){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("6. MAIN MENU");
if (digitalRead(Btn)==LOW) {delay(650); seq="return"; men="menu"; mcnt=true;  MENOP=1; Enc.write(0); tft.fillScreen(ST7735_BLACK); doMenu();}
  }
else if (SEQOP!=6 && seq=="seqmenu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("6. MAIN MENU");}

}


void doPatterns() { 
if (pcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(50, 30); tft.print("PATTERNS"); tft.drawLine(0, 60, 240, 60, 0x8811); pcnt=!pcnt;
}
if (digitalRead(Btn)==LOW) {delay(650); men="menu"; mcnt=true;  tft.fillScreen(ST7735_BLACK); doMenu();}
}




void doHeartMonitor() { 
if (hcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(33, 30); tft.print("HR MONITOR"); tft.drawLine(0, 60, 240, 60, 0x8811); hcnt=!hcnt;
}
if (digitalRead(Btn)==LOW) {delay(650); men="menu"; mcnt=true;  tft.fillScreen(ST7735_BLACK); doMenu();}
}


void doReset() { 
  /*
if (rcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(15, 30); tft.print("RESET DEVICE"); tft.drawLine(0, 60, 240, 60, 0x8811); rcnt=!rcnt;
}
if (digitalRead(Btn)==LOW) {delay(650); men="off"; mcnt=true;  tft.fillScreen(ST7735_BLACK); setup();}
}*/
}


void doSD() { 
if (sdcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(60, 30); tft.print("SD CARD"); tft.drawLine(0, 60, 240, 60, 0x8811); sdcnt=!sdcnt;
}
if (digitalRead(Btn)==LOW) {delay(650); men="menu"; mcnt=true;  tft.fillScreen(ST7735_BLACK); doMenu();}
}

void doCustom() { 
if (ccnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(22, 30); tft.print("CUSTOM GRID"); tft.drawLine(0, 60, 240, 60, 0x8811); ccnt=!ccnt;
}
if (digitalRead(Btn)==LOW) {delay(650); men="menu"; mcnt=true;  tft.fillScreen(ST7735_BLACK); doMenu();}
}




// These are sub-menus in SEQUENCES

void doLength() { seq="length";
if (lcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
  tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
  tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
  lcnt=!lcnt;
  tft.drawLine(70, 65, 170, 65, 0x8811); tft.drawLine(70, 125, 170, 125, 0x8811);
  tft.drawLine(70, 65, 70, 125, 0x8811); tft.drawLine(170, 65, 170, 125, 0x8811);
  tft.drawLine(0, 140, 240, 140, 0x8811); 
  tft.drawLine(70, 188, 170, 188, 0x8811); tft.drawLine(70, 248, 170, 248, 0x8811);
  tft.drawLine(70, 188, 70, 248, 0x8811); tft.drawLine(170, 188, 170, 248, 0x8811);
  tft.drawLine(0, 263, 240, 263, 0x8811); 
}
if (len=="length") {spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; LNGTHOP = abs(valENC+1);}}
else if (len=="lengtharray") {spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = (((PLACE % totalarrays)+totalarrays) % totalarrays); count = PLACE; AROP = abs(valENC+1);}}
else if (len=="repeat") {spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((2-PLACE) % 2)+2) % 2); count = PLACE; REPOP = abs(valENC+1);} 
      if (REPOP==1){opt="N"; repnum=1;} else if (REPOP==2){opt="Y"; repnum=10;}
}

if (LNGTHOP==1){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 30); tft.print("LENGTH");
 if (digitalRead(Btn)==LOW) {delay(400);  rectanglecountone=!rectanglecountone;}
   if (rectanglecountone==false && rectanglecounttwo==false) {tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP);} // not selected
   else if (rectanglecountone==true && rectanglecounttwo==true) {tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 78); tft.print(AROP);} // selected
   else if (rectanglecountone==true && rectanglecounttwo==false) {
      len="lengtharray"; tft.fillRect(71, 66, 98, 58, 0x2A69); tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 78); tft.print(AROP); rectanglecounttwo=!rectanglecounttwo;}
   else if (rectanglecountone==false && rectanglecounttwo==true) {
      len="length"; tft.fillRect(71, 66, 98, 58, ST7735_BLACK); tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP); rectanglecounttwo=!rectanglecounttwo;
      int seqlist[AROP];  for (int j=0; j<AROP; j++) {seqlist[j]=1;} int timelist[AROP];  for (int j=0; j<AROP; j++) {timelist[j]=10; TOTAL=AROP;}  
      }
}
else if (LNGTHOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 30); tft.print("LENGTH"); 
    tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP); //tft.setCursor(90, 78); tft.print("10"); for 10 to under need to do blk rect
}

if (LNGTHOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 155); tft.print("REPEAT");
 if (digitalRead(Btn)==LOW) {delay(400);  rectwocountone=!rectwocountone;}
   if (rectwocountone==false && rectwocounttwo==false) {tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt);} // not selected
   else if (rectwocountone==true && rectwocounttwo==true) {tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 200); tft.print(opt);} // selected
   else if (rectwocountone==true && rectwocounttwo==false) {
      len="repeat"; tft.fillRect(71, 189, 98, 58, 0x2A69); tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 200); tft.print(opt); rectwocounttwo=!rectwocounttwo;}
   else if (rectwocountone==false && rectwocounttwo==true) {
      len="length"; tft.fillRect(71, 189, 98, 58, ST7735_BLACK); tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt); rectwocounttwo=!rectwocounttwo;}
}
else if (LNGTHOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 155); tft.print("REPEAT");
    tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt); 
}

if (LNGTHOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=1; Enc.write(0);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (LNGTHOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}


// seqlist cursor for singles (55, 65+35*j) -- doubles is (45, 65+35*j)
// timelist cursor for singles is (175, 65+35*j) -- doubles is (165, 65+35*j)
// seqrects are (30, 61+35*j, 62, 31,
// timerects are (148, 61+35*j, 62, 31, 

void doChooseArrays() {
if (cacnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.drawLine(120, 15, 120, 268, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.drawLine(0, 58, 240, 58, 0x8811); cacnt=!cacnt; Enc.write(0);
tft.drawLine(0, 268, 240, 268, 0x8811);
tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
for (int j=0; j<AROP; j++){ 
  if (seqlist[j]<10){ tft.setCursor(55,65+35*j);} else if (9<seqlist[j]){ tft.setCursor(45,65+35*j);} tft.print(seqlist[j]); 
  if (timelist[j]<10){ tft.setCursor(175, 65+35*j);} else if (9<timelist[j]){ tft.setCursor(165,65+35*j);} tft.print(timelist[j]); 
  tft.drawLine(0, 93+35*j, 240, 93+35*j, 0x8811);
}
}
if (cho=="choicemenu"){spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; CAOP = abs(valENC+1);}}
else if (cho=="choice"){spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % totalarrays)+totalarrays) % totalarrays); count = PLACE; ARROP = abs(valENC+1); ac=ARROP;} }
else if (cho=="time"){spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 60)+60) % 60); count = PLACE; TIMEOP = abs(valENC+1); tc=TIMEOP;}}

if (CAOP==1 && cho=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 28); tft.print("ARRAY"); 
    if (digitalRead(Btn)==LOW){delay(400); cho="choice"; tft.fillRect(30, 61+35*(acounter), 62, 31, 0x2A69);}
}
if (CAOP==1 && cho=="choice"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 28); tft.print("ARRAY");
    if (acn!=ac){tft.fillRect(30, 61+35*acounter, 62, 31, 0x2A69); acn=ac;} 
    if (ac<10){ tft.setCursor(55,65+35*acounter);} else if (9<ac){ tft.setCursor(45,65+35*acounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(ARROP);
  if (digitalRead(Btn)==LOW){delay(400);  tft.fillRect(30, 61+35*(acounter), 62, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    seqlist[acounter]=ARROP; 
    if (ac<10){ tft.setCursor(55,65+35*acounter);} else if (9<ac){ tft.setCursor(45,65+35*acounter);} tft.print(seqlist[acounter]); 
    acounter=acounter+1; 
    if (acounter==AROP){acounter=0; cho="choicemenu";} else if(acounter!=AROP){tft.fillRect(30, 61+35*(acounter), 62, 31, 0x2A69);}
    ARROP=seqlist[acounter];
  }
  if (digitalRead(NXT)==LOW){ 
    delay(400);  tft.fillRect(30, 61+35*(acounter), 62, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    seqlist[acounter]=ARROP; 
    if (ac<10){ tft.setCursor(55,65+35*acounter);} else if (9<ac){ tft.setCursor(45,65+35*acounter);} tft.print(seqlist[acounter]); 
    tcounter=acounter; CAOP=2; tcn=100; cho="time";
    }
}
else if (CAOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(20, 28); tft.print("ARRAY");}

if (CAOP==2 && cho=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(145, 28); tft.print("TIME");
    if (digitalRead(Btn)==LOW){delay(400); cho="time"; tft.fillRect(148, 61+35*(tcounter), 62, 31, 0x2A69); }
}
if (CAOP==2 && cho=="time"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(145, 28); tft.print("TIME");
    if (tcn!=tc){tft.fillRect(148, 61+35*tcounter, 62, 31, 0x2A69); tcn=tc;} 
    if (tc<10){ tft.setCursor(175, 65+35*tcounter);} else if (9<tc){ tft.setCursor(165,65+35*tcounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(TIMEOP);
  if (digitalRead(Btn)==LOW){ delay(400); tft.fillRect(148, 61+35*tcounter, 63, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    timelist[tcounter]=TIMEOP; 
    if (tc<10){ tft.setCursor(175,65+35*tcounter);} else if (9<tc){ tft.setCursor(165,65+35*tcounter);} tft.print(timelist[tcounter]); 
    tcounter=tcounter+1; 
    if (tcounter==AROP){tcounter=0; cho="choicemenu";} else if(tcounter!=AROP){tft.fillRect(148, 61+35*tcounter, 62, 31, 0x2A69);}
    TIMEOP=timelist[tcounter]; tc=TIMEOP; 
  } 
   if (digitalRead(NXT)==LOW){ 
    delay(400);  tft.fillRect(148, 61+35*(tcounter), 62, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    timelist[tcounter]=TIMEOP; 
    if (tc<10){ tft.setCursor(175,65+35*tcounter);} else if (9<tc){ tft.setCursor(165,65+35*tcounter);} tft.print(timelist[tcounter]); 
    acounter=tcounter; CAOP=1; acn=100; cho="choice";
    }
}
else if (CAOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(145, 28); tft.print("TIME");}
if (CAOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 280); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=1; Enc.write(0);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (CAOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 280); tft.print("RETURN TO SEQUENCES");}
}


void doTransitions() {
if (tcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(23, 30); tft.print("TRANSITIONS"); tft.drawLine(0, 60, 240, 60, 0x8811); tcnt=!tcnt;
}

if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu"; scnt=true;  tft.fillScreen(ST7735_BLACK); doSequences();}

}


void doAnimations() {
if (acnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(35, 30); tft.print("ANIMATIONS"); tft.drawLine(0, 60, 240, 60, 0x8811); acnt=!acnt;
}

if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu"; scnt=true;  tft.fillScreen(ST7735_BLACK); doSequences();}

}


void doPlay() {
if (plcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v1.0");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(15, 30); tft.print("RUN SEQUENCE"); tft.drawLine(0, 60, 240, 60, 0x8811); plcnt=!plcnt;
tft.drawLine(0, 161, 240, 161, 0x8811); tft.drawLine(0, 263, 240, 263, 0x8811); 
tft.drawLine(34, 80, 206, 80, 0x8811); tft.drawLine(34, 141, 206, 141, 0x8811); tft.drawLine(34, 181, 206, 181, 0x8811); tft.drawLine(34, 243, 206, 243, 0x8811);
tft.drawLine(34, 80, 34, 141, 0x8811); tft.drawLine(34, 181, 34, 243, 0x8811); tft.drawLine(206, 80, 206, 141, 0x8811); tft.drawLine(206, 181, 206, 243, 0x8811);
}

spot = Enc.read(); PLACE = spot>>2; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; RUNOP = abs(valENC+1);}

if (RUNOP==1){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(84, 101); tft.print("AUTO");
 if (digitalRead(Btn)==LOW) {delay(250); br="go";
  for (int k=0; k<repnum; k++){
    if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;}
    for (int i=0; i<TOTAL; i++){setTime(0); time_t t = now(); timelength=timelist[i]; if (timelength==0){timelength=1;} arraynumber=seqlist[i]; startAddress = 312*(arraynumber-1); //Serial.println(i); 
      if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;}
      for (int k=0; k<timelength; k++){
         if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;}
         for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} ring.show();
         time_t t = now(); inc=second(t);
         if (digitalRead(SAVE)==LOW){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); br="break"; break;}
         delay(1000);
      }
    inc=0; 
    } 
  }
  for (int j=0; j<TOT; j++) { ring.setPixelColor(j,0);} ring.show(); 
 }
}
else if (RUNOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(84, 101); tft.print("AUTO"); }

if (RUNOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 201); tft.print("MANUAL");
 if (digitalRead(Btn)==LOW) {delay(250); seq="manual"; mancount=0; arraynumber=seqlist[0]; startAddress = 312*(arraynumber-1);  doManualRun();}
} 
else if (RUNOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 201); tft.print("MANUAL");}

if (RUNOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=1; Enc.write(0);  tft.fillScreen(ST7735_BLACK); scnt=true; seq="seqmenu"; doSequences();}
  }
else if (RUNOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}


void doManualRun() {
if (digitalRead(SAVE)==LOW){delay(100); for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); seq="play"; doPlay();}
if (digitalRead(NXT)==LOW){delay(150); mancount=((mancount+1)%AROP); arraynumber=seqlist[mancount]; startAddress = 312*(arraynumber-1);}
if (seq=="manual"){for (int j=0; j<TOT; j++) {int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} ring.show();}
}




// These are sub-menus in ____




void SEQreadFromEEPROM(int address, int pixelsS1[], int arraySize) {
  int addressIndex = 0;
    for (int i=0; i<arraySize; i++) { pixelsS1[i] = EEPROM.read(addressIndex);  addressIndex++;}
}
