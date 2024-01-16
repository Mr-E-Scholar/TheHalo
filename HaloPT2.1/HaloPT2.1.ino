/*
THE HALO LIGHT CONTROLLER PREMIUM VERSION 2.1 (FOR TEENSY 3.2)
COPYRIGHT 06/17/2022 CASEY ATTEBERY, RESONANT DEVICES
*/

////////////////////////////////////////////////////////////////////////////////////
// RING LIGHT NUMBERS
// THESE ARE THE NUMBERS OF PIXELS PER RING LIGHTS, R1 BEING THE OUTER RING, R3 IS THE INNER RING
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
#define RCKRTWO 29
#define RCKRTHREE 32
#define NXT 5
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCK 13
#define TFT_CS 15
#define TFT_DC 19
#define TFT_RST 39
#define SD_CS 9
#define HR_RX 28

Encoder Enc(PinA, PinB); const int TOT=R1+R2+R3; int valENC=0;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(TOT, DATARING, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel testLED = Adafruit_NeoPixel(1, DATALED, NEO_RGB + NEO_KHZ800);
File SDfile; File root;

long debounceDelay = 100; // RING BUTTONS DELAY
long debounceDelay2 = 75; // SAVE AND NEXT BUTTONS DELAY

byte RINGone; byte RINGtwo; byte RINGthree; byte RINGfour;
boolean modeOne = true; boolean modeTwo = true; boolean modeThree = true; boolean modeFour; byte NXTstate; byte MEMstate; byte OFFstate;
boolean onecount = true; boolean twocount = true; boolean threecount = true; boolean fourcount;
boolean modeMem = true;  boolean OPTL = true; boolean OPTM=true; boolean encode = true; boolean encodecount = true; boolean encodeL = true; boolean encodecountL = true; 
boolean nextbut = digitalRead(NXT); boolean tog = digitalRead(RCKR); boolean togTWO = digitalRead(RCKRTWO); boolean togTHREE = digitalRead(RCKRTHREE); boolean flip=true;
int startAddress=0; int startAddressL=0; int pixelsL[312]; int pixelsM[312]; int pixelsN[312];
int Pos=0; int PosL=0; int b=1; int r=1; int PIX;  long spot; long spotL;
int valRotary=0; int startnum=0; int endnum=R1; boolean state=HIGH; int lastpix;
int CR; int CG; int CB; int CRN; int CGN; int CBN; int NB, B; int nNB; int nCR; int nCG; int nCB; int nCRN; int nCGN; int nCBN; int memslot=1; int MEMS=0;
int count=0; int S=0; long lastDebounceTime = 0; 
int lastState1 = LOW; int lastState2 = LOW; int lastState3 = LOW; int lastState4=LOW; int lastState5 = LOW; int lastState6 = LOW; int lastState7 = LOW; int laststate8 = LOW; int state1, state2, state3, state4, state5, state6, state7, state8; 
time_t t; time_t tt;

int Rcolor[16]; boolean checker=true;

boolean mcnt=true; boolean scnt=true; boolean pcnt=true; boolean acnt=true; boolean hcnt=true; boolean afcnt=true; boolean rcnt=true; boolean sdcnt=true; boolean ccnt=true; boolean orcnt=true; boolean keycnt=true; boolean dircnt=true; boolean infocnt=true;
boolean lcnt=true; boolean cacnt=true; boolean tcnt=true; boolean retcnt=true; boolean plcnt=true; boolean startlive=HIGH; boolean startload=HIGH; boolean startmenu=HIGH;
boolean rectanglecountone=false; boolean rectanglecounttwo=false; boolean rectwocountone=false; boolean rectwocounttwo=false;  boolean keyboardcount=false;
int acounter=0; int tcounter=0; int trancounter=0; int animcounter=0; int arcounter=0; int fcounter=0;
String men="off"; String seq; int strt=1; String len="length"; String org="organ"; String opt="N"; boolean power=false; boolean flpower=false; String cho="choicemenu"; String arf="choicemenu"; String transmen="NONE";  String animmen="NONE"; String tra="menu"; String ani="menu"; String mode; String sty="BASIC";
int PLACE=0; int MENOP=1; int SEQOP=1; int PATOP, LNGTHOP, ORGOP, STYOP, POWOP, brightcnt, iter; int xvalue=78; int AROP=1; int REPOP=1; int CAOP=1; int AFOP=1; int ARROP=1; int ARFOP=1; int TIMEOP=5; int FREQOP=1; int TRANOP=1; int ANIMOP=1; int SDOP=1; int KEYOP=1; int DIROP=1; int FILEOP=1; int LOADOP=2;
int tranc=0; int trancn=0; int TPICKOP=0; int HRUNOP=1; int APICKOP=0; int animc=0; int animcn=0;
int seqlist[6]; int timelist[6]; String translist[6]; String animlist[6]; int tempolist[6]; int aflist[6]; int freqlist[6];
int totalarrays=6;  int arrcursorstrt; int timecursorstrt; int ac=1; int acn=10; int tc=5; int tcn=5; int repnum=1; int arc=1; int fc=1; int arcn=10; int fcn=1;
int inc=0; int Tc; int arraynumber=1; int timelength=10; int TOTAL=1; int pixelsS1[1872]; int pixelsS2[1872];
boolean startcounter=true; int mancount=0; int RUNOP=1; String br="go"; int arcount=0; float dt, df; long randomnum;
byte oldSample, sample, decflip; float fval1, fval2; char fout1[4]; char fout2[4];
String filename, filename2, filenametxt; boolean stringupdate=true; int sdstartaddress;  String extension; String fname; String filenamelist[100]; String filenamelistNOext[100];
int filecounter=0; String fnameNOext; boolean newload=true; String seqchoice=" "; boolean listcounter=true; int lengthlist; boolean listcount2; boolean loadcount=true; String seqchoice2; boolean savecount=true;
int loadlevel; String lineread; int RESETOP=1; int VEROP=1; boolean vcnt=true; int DIAL0;


#include <ST7789_t3.h>
ST7789_t3 tft = ST7789_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

/////////////////////////////
// This is the setup, identifying the pin purposes and calling the LEDs to action.
/////////////////////////////

void setup() { Serial.begin(9600); 
 
if (startcounter){
  for (int i=0; i<100; i++) {filenamelist[i]=' '; filenamelistNOext[i]=' ';} for (int i=0; i<312; i++) {pixelsM[i]=0; pixelsN[i]=0; pixelsL[i]=0;} for (int i=0; i<1872; i++) {pixelsS1[i]=0; pixelsS2[i]=0;}
  for (int j=0; j<6; j++){ seqlist[j]=1; timelist[j]=5; translist[j]="NONE"; animlist[j]="NONE"; aflist[j]=1; freqlist[j]=10; }
  tft.init(240, 320, SPI_MODE2); tft.fillScreen(ST7735_BLACK); tft.setRotation(2);
  ring.begin();  testLED.begin();  testLED.setBrightness(35); ring.show(); testLED.show();
  pinMode(Btn, INPUT_PULLUP);
  pinMode(NXT, INPUT_PULLUP); pinMode(RCKR, INPUT_PULLUP); pinMode(RCKRTWO, INPUT_PULLUP); pinMode(RCKRTHREE, INPUT_PULLUP);
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
tft.setCursor(90, 310); tft.print("Premium v2.1");
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
boolean tog = digitalRead(RCKR); boolean togTWO = digitalRead(RCKRTWO); boolean togTHREE = digitalRead(RCKRTHREE); 
DIAL0 = analogRead(DIMM); B=map(DIAL0,0,1023,8,255); NB=map(DIAL0,0,1023,0,100);

if (!tog && togTWO && togTHREE && startlive){delay(10); mode="live"; mcnt=true; Enc.write(0); OPTM=true; seq="off"; men="off"; state=HIGH; startlive=!startlive; startload=!startload;setup();}
else if (tog && !togTWO && togTHREE && startload ){delay(10); mode="load"; mcnt=true; Enc.write(0); OPTM=true; seq="off";men ="off"; state=LOW; startload=!startload; startlive=!startlive;setup();}
else if (tog && togTWO && !togTHREE && startmenu ){delay(10); mcnt=true; Enc.write(0); OPTM=true; seq="off";men ="menu"; SEQreadFromEEPROM(0, pixelsS1, 1872);  for (int i=0; i<1872; i++) {pixelsS2[i]=pixelsS1[i];} startload=!startload; startlive=!startlive; startmenu=!startmenu;}

if (!tog && togTWO && togTHREE && men!="off"){delay(10); mode="live"; mcnt=true; Enc.write(0); OPTM=true; seq="off"; men="off"; state=HIGH; setup();}
else if (tog && !togTWO && togTHREE && men!="off"){delay(10); mode="load"; mcnt=true; Enc.write(0); OPTM=true; seq="off"; men="off"; state=LOW;setup();}


if (men=="menu") {  doMenu();}
if (men=="seq" && seq=="seqmenu") {doSequences();} 
if (men=="organ") {doColorOrgan();}
if (men=="sd") {doSD();}
if (men=="keyboard") {doKeyboard();}
if (men=="showlist") {doListChoose();}
if (men=="directory") {doDirectory();}
if (men=="load") {doSDLOAD();}
if (men=="verify") {doRESETVERIFY();}
if (men=="saveOK") {doSaveOK();}
if (men=="reset") {doReset();}
if (men=="flasher") {doFlasher();}
if (men=="flash") {doFlash();}
if (power && sty=="SPECTRUM" && men=="organ") {doSpectrum();}
if (power && sty=="BASIC" && men=="organ") {doBasic();}
if (power && sty=="TRIAD" && men=="organ") {doTriad();}
if (power && sty=="SEQUENCE" && men=="organ") {doSequence();}
if (seq=="length") {doLength();}
if (seq=="choose") {doChooseArrays();}
if (seq=="trans") {doTransitions();}
if (seq=="play") {doPlay();}
if (seq=="anim") {doAnimations();}
if (seq=="manual"){doManualRun();}

if (men=="off"){
 if (!tog && togTWO && togTHREE) { ring.setBrightness(B);
    if (state) {Enc.write(0); r=1; ring.setPixelColor(0,pixelsL[0],pixelsL[1],pixelsL[2]); OPTM=true; flip=true;
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(58, 0); tft.print("The Halo - Live Mode");}
    testLED.setPixelColor(0, 0); doAction(); state=LOW; }
 else if (!togTWO && togTHREE && tog) { 
 if (state==LOW) {Enc.write(0); r=1; tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(58, 0); tft.print("The Halo - Load Mode");}
  if (OPTM==true) {MEMS=memslot-1; flip=true;
    startAddress = 312*(MEMS);
    readFromEEPROM(startAddress, pixelsN, 312); for (int i=0; i<312; i++) {pixelsM[i]=pixelsN[i];}
   for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsN[jj], pixelsN[jj+1], pixelsN[jj+2]);} ring.show(); OPTM=false;
   } 
 doMenuLoad(); state=HIGH;}
 
 else if ((!togTHREE && tog && tog)){ men="menu"; Enc.write(0); MENOP=1; tft.fillScreen(ST7735_BLACK);} 
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
  RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree); NXTstate=digitalRead(NXT);
if (digitalRead(Btn)==LOW) {delay(200); encodeL=true; encodecountL=!encodecountL;}
if (NXTstate!=lastState4) {lastDebounceTime = millis();}
  if ((millis()-lastDebounceTime) > debounceDelay2) {
    if (NXTstate != state4) { state4 = NXTstate;
      if (state4 == LOW) {  memslot=memslot+1; if (memslot == 7){memslot=1;}  }
    }
  }
lastState4 = NXTstate;
if (encodecountL == false) {doAlterArrayLive(); }
else if (encodecountL == true) {testLED.setPixelColor(0,0); testLED.show(); doLiveAction();}   
}


//////////////////////////////
// These are for the live-action ring/encoder play.
//////////////////////////////

void doLiveAction() { 

if (digitalRead(SAVE)==LOW) {delay(100); if (flip==true){time_t t = now(); S=second(t); flip=false;}} ;
if (digitalRead(SAVE)==LOW && second(t)==2+S){flip=true; for (int i=0; i<312; i++) {pixelsL[i]=pixelsM[i];}}
 int DIAL1 = analogRead(RED); int DIAL2 = analogRead(GREEN); int DIAL3 = analogRead(BLUE); MEMstate = digitalRead(SAVE); NXTstate = digitalRead(NXT);
CR = map(DIAL1,0,1023,0,255); CG = map(DIAL2,0,1023,0,255); CB = map(DIAL3,0,1023,0,255);
  
if (MEMstate != lastState5) {lastDebounceTime = millis();}
  if ((millis()-lastDebounceTime) > debounceDelay2) {
    if (MEMstate != state5) { state5 = MEMstate;
      if (state5 == LOW) { MEMS=memslot-1; startAddress = 312*(MEMS); writeToEEPROM(startAddress, pixelsL, 312); }
    }
  }
lastState5 = MEMstate; 

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
if (RINGone != lastState1) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGone != state1) { state1 = RINGone;
    if (state1 == LOW) { r=1; 
      if (onecount == true) {
        Pos=0; Enc.write(0); onecount=!onecount; ring.setPixelColor(0, CR, CG, CB); 
        if (twocount == false) {twocount=!twocount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState1 = RINGone;
if (RINGtwo != lastState2) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGtwo != state2) { state2 = RINGtwo;
    if (state2 == LOW) { r=2;  
      if (twocount == true) {
        Pos=0; Enc.write(0); twocount=!twocount; ring.setPixelColor(R1, CR, CG, CB); 
        if (onecount == false) {onecount=!onecount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState2 = RINGtwo;
if (RINGthree != lastState3) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
 if (RINGthree != state3) { state3 = RINGthree;
   if (state3 == LOW) { r=3;  
     if (threecount == true) {
       Pos=0; Enc.write(0); threecount=!threecount; ring.setPixelColor(R1+R2, CR, CG, CB); 
       if (onecount == false) {onecount=!onecount;}
       if (twocount == false) {twocount=!twocount;}
     } Enc.write(0);
   }
 }
}
lastState3 = RINGthree;
if (r==1) {startnum=0; endnum=R1;}
else if (r==2) {startnum=R1; endnum=R2;}
else if (r==3) {startnum=R1+R2; endnum=R3;}
int count=100; spot = Enc.read(); Pos = spot>>1; int p;
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
NXTstate = digitalRead(NXT); RINGone = digitalRead(Rone);  RINGtwo = digitalRead(Rtwo);  RINGthree = digitalRead(Rthree);  MEMstate=digitalRead(SAVE);
 tft.setTextSize(6); tft.setTextColor(0xF731, ST7735_BLACK); tft.setCursor(105, 235); tft.print(memslot);
 
if (NXTstate!=lastState4) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay2) {
  if (NXTstate != state4) { state4 = NXTstate;
    if (state4 == LOW) {  
      memslot=memslot+1; if (memslot==7) {memslot=1;} MEMS = memslot-1;
      r=1; tft.setCursor(105, 235); startAddress = 312*(MEMS);
      readFromEEPROM(startAddress, pixelsM, 312); count=0;
      for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);} 
      ring.show(); testLED.setPixelColor(0,0); testLED.show();
    } 
  }
}
lastState4 = NXTstate;
   
if (digitalRead(Btn)==LOW) {delay(400); encode=true; encodecount=!encodecount; 
  if (memcnt == false) {writeToEEPROM(startAddress, pixelsM, 312); for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);} ring.show();} 
  memcnt=!memcnt;
}
if (encodecount == false) {doAlterArray(); }
else if (encodecount == true) {testLED.setPixelColor(0,0); testLED.show(); ring.show();
if (digitalRead(SAVE)==LOW) {delay(100); if (flip==true){time_t t = now(); S=second(t); flip=false;}} time_t t = now();
if (digitalRead(SAVE)==LOW && second(t)==2+S){flip=true; for (int i=0; i<312; i++) {pixelsL[i]=pixelsM[i];}}
}  
}


//////////////////////////////
// These lines alter stored arrays in Load Mode via the encoder as a pixel selector.
//////////////////////////////

void doAlterArray() { 
  int PosL; int count=100; spot = Enc.read(); PosL = spot>>1;
if (encode == true && encodecount == false) {encode=!encode; }
if (RINGone != lastState1) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGone != state1) { state1 = RINGone;
    if (state1 == LOW) { r=1; 
      if (onecount == true) {
        Pos=0; Enc.write(0); onecount=!onecount; ring.setPixelColor(0, CR, CG, CB); 
        if (twocount == false) {twocount=!twocount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState1 = RINGone;
if (RINGtwo != lastState2) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGtwo != state2) { state2 = RINGtwo;
    if (state2 == LOW) { r=2;  
      if (twocount == true) {
        Pos=0; Enc.write(0); twocount=!twocount; ring.setPixelColor(R1, CR, CG, CB); 
        if (onecount == false) {onecount=!onecount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState2 = RINGtwo;
if (RINGthree != lastState3) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
 if (RINGthree != state3) { state3 = RINGthree;
   if (state3 == LOW) { r=3;  
     if (threecount == true) {
       Pos=0; Enc.write(0); threecount=!threecount; ring.setPixelColor(R1+R2, CR, CG, CB); 
       if (onecount == false) {onecount=!onecount;}
       if (twocount == false) {twocount=!twocount;}
     } Enc.write(0);
   }
 }
}
lastState3 = RINGthree;
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
 int count=100; spotL = Enc.read(); PosL = spotL>>1; //int p;
if (encodeL== true && encodecountL == false) {encodeL=!encodeL; }
if (RINGone != lastState1) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGone != state1) { state1 = RINGone;
    if (state1 == LOW) { r=1; 
      if (onecount == true) {
        Pos=0; Enc.write(0); onecount=!onecount; ring.setPixelColor(0, CR, CG, CB); 
        if (twocount == false) {twocount=!twocount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState1 = RINGone;
if (RINGtwo != lastState2) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
  if (RINGtwo != state2) { state2 = RINGtwo;
    if (state2 == LOW) { r=2;  
      if (twocount == true) {
        Pos=0; Enc.write(0); twocount=!twocount; ring.setPixelColor(R1, CR, CG, CB); 
        if (onecount == false) {onecount=!onecount;}
        if (threecount == false) {threecount=!threecount;}
      } Enc.write(0);
    }
  }
}
lastState2 = RINGtwo;
if (RINGthree != lastState3) {lastDebounceTime = millis();}
if ((millis()-lastDebounceTime) > debounceDelay) {
 if (RINGthree != state3) { state3 = RINGthree;
   if (state3 == LOW) { r=3;  
     if (threecount == true) {
       Pos=0; Enc.write(0); threecount=!threecount; ring.setPixelColor(R1+R2, CR, CG, CB); 
       if (onecount == false) {onecount=!onecount;}
       if (twocount == false) {twocount=!twocount;}
     } Enc.write(0);
   }
 }
}
lastState3 = RINGthree;
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
if (mcnt==true) {tft.fillScreen(ST7735_BLACK); for (int i=0; i<TOT; i++){ring.setPixelColor(i,0);} ring.show();
tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811);  
tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(40, 30); tft.print("MAIN MENU"); tft.drawLine(0, 60, 240, 60, 0x8811); 
for (int j=1; j<6; j++){tft.drawLine(0, 60+49*j, 240, 60+49*j, 0x8811);}// tft.drawLine(0, 158, 240, 142, 0x8811); tft.drawLine(0, 183, 240, 183, 0x8811); tft.drawLine(0, 224, 240, 224, 0x8811); tft.drawLine(0, 265, 240, 265, 0x8811); 
mcnt=!mcnt;
}

spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 5)+5) % 5); count = PLACE; MENOP = abs(valENC+1);}
tft.setTextSize(2); 

if (MENOP==1){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 81); tft.print("1. SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); men="seq"; scnt=true; SEQOP=1; Enc.write(0); doSequences();}
}
  else if (MENOP!=1 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 81); tft.print("1. SEQUENCES");}
  
if (MENOP==2){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 130); tft.print("2. COLOR ORGAN");
if (digitalRead(Btn)==LOW) {delay(650); men="organ"; orcnt=true; doColorOrgan();}
}
  else if (MENOP!=2 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 130); tft.print("2. COLOR ORGAN");}
  
if (MENOP==3){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 179); tft.print("3. ARRAY FLASHER");
if (digitalRead(Btn)==LOW) {delay(650); men="flasher"; afcnt=true; Enc.write(1); AFOP=1; doFlasher();}
}
  else if (MENOP!=3 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 179); tft.print("3. ARRAY FLASHER");}

if (MENOP==4){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 228); tft.print("4. SD CARD");
if (digitalRead(Btn)==LOW) {delay(650); men="sd"; SDOP=1;  Enc.write(1); sdcnt=true; doSD();}
}
  else if (MENOP!=4 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 228); tft.print("4. SD CARD");} 
  
if (MENOP==5){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 277); tft.print("5. RESET DEVICE");
if (digitalRead(Btn)==LOW) {delay(650); men="reset"; rcnt=true; doReset();}
}
  else if (MENOP!=5 && men=="menu") {tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 277); tft.print("5. RESET DEVICE");}
}



void doSequences() {seq="seqmenu";
if (scnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(40, 30); tft.print("SEQUENCES"); tft.drawLine(0, 60, 240, 60, 0x8811); 
tft.drawLine(0, 101, 240, 101, 0x8811); tft.drawLine(0, 142, 240, 142, 0x8811); tft.drawLine(0, 183, 240, 183, 0x8811);
tft.drawLine(0, 224, 240, 224, 0x8811); tft.drawLine(0, 265, 240, 265, 0x8811);
scnt=!scnt; SEQOP=1;
}

spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 6)+6) % 6); count = PLACE; SEQOP = abs(valENC+1);}
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



void doColorOrgan() { men="organ";
if (orcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(22, 30); tft.print("COLOR ORGAN"); tft.drawLine(0, 60, 240, 60, 0x8811); orcnt=!orcnt;
ORGOP=1;  Enc.write(1);

  tft.drawLine(30, 108, 210, 108, 0x8811); tft.drawLine(30, 152, 210, 152, 0x8811);
  tft.drawLine(30, 108, 30, 152, 0x8811); tft.drawLine(210, 108, 210, 152, 0x8811);
  tft.drawLine(0, 165, 240, 165, 0x8811); 
  tft.drawLine(30, 210, 210, 210, 0x8811); tft.drawLine(30, 260, 210, 260, 0x8811);
  tft.drawLine(30, 210, 30, 260, 0x8811); tft.drawLine(210, 210, 210, 260, 0x8811);
  tft.drawLine(120, 210, 120, 260, 0x8811); 
  tft.drawLine(0, 274, 240, 274, 0x8811); 
}
if (org=="organ") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; ORGOP = abs(valENC+1);}}
else if (org=="style") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = (((PLACE % 4)+4) % 4); count = PLACE; STYOP = abs(valENC+1); rectanglecounttwo=false;}
      if (STYOP==1){sty="BASIC"; xvalue=78;} else if (STYOP==2){sty="SPECTRUM"; xvalue=50;}  else if (STYOP==3){sty="TRIAD"; xvalue=78;} else if (STYOP==4){sty="SEQUENCE"; xvalue=50;}
}


if (ORGOP==1){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(78, 76); tft.print("STYLE");
 if (digitalRead(Btn)==LOW) {delay(400);  rectanglecountone=!rectanglecountone;}
   if (rectanglecountone==false && rectanglecounttwo==false) {tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(xvalue, 120); tft.print(sty);} // not selected
   else if (rectanglecountone==true && rectanglecounttwo==true) {tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(xvalue, 120); tft.print(sty);} // selected
   else if (rectanglecountone==true && rectanglecounttwo==false) {
      org="style"; tft.fillRect(32, 110, 176, 40, 0x2A69); tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(xvalue, 120); tft.print(sty); rectanglecounttwo=!rectanglecounttwo;}
   else if (rectanglecountone==false && rectanglecounttwo==true) {
      org="organ"; tft.fillRect(32, 110, 176, 40, ST7735_BLACK); tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(xvalue, 120); tft.print(sty); rectanglecounttwo=!rectanglecounttwo;
       ORGOP=2; Enc.write(2);
      }
}
else if (ORGOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(78, 76); tft.print("STYLE"); 
    tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(xvalue, 120); tft.print(sty); //tft.setCursor(90, 78); tft.print("10"); for 10 to under need to do blk rect
}

if (ORGOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(78, 180); tft.print("POWER");
 if (digitalRead(Btn)==LOW) {delay(400);  power=!power;}
   if (!power) {tft.setTextSize(4); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(132, 222); tft.print("OFF"); 
    tft.setTextColor(0x2A69, ST7735_BLACK); tft.setCursor(55, 222); tft.print("ON");} // POWER OFF
   else if (power) {   tft.setTextSize(4); tft.setTextColor(0x2A69, ST7735_BLACK);  tft.setCursor(132, 222); tft.print("OFF"); 
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(55, 222); tft.print("ON");

    while (power && sty=="SPECTRUM"){doSpectrum(); if (digitalRead(Btn)==LOW) {delay(400); for (int i=0; i<104; i++){ring.setPixelColor(i,0); ring.show();} power=false; ORGOP=2; break;}}
    while (power && sty=="BASIC"){doBasic(); if (digitalRead(Btn)==LOW) {delay(400); for (int i=0; i<104; i++){ring.setPixelColor(i,0); ring.show();} power=false; ORGOP=2; break;}}
    while (power && sty=="TRIAD"){doTriad(); if (digitalRead(Btn)==LOW) {delay(400); for (int i=0; i<104; i++){ring.setPixelColor(i,0); ring.show();} power=false; ORGOP=2; break;}}
    while (power && sty=="SEQUENCE"){doSequence(); if (digitalRead(Btn)==LOW) {delay(400); for (int i=0; i<104; i++){ring.setPixelColor(i,0); ring.show();} power=false; ORGOP=2; break;}}
    } // POWER ON
}

else if (ORGOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(78, 180); tft.print("POWER");
     if (!power) {tft.setTextSize(4); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(132, 222); tft.print("OFF"); 
    tft.setTextColor(0x2A69, ST7735_BLACK); tft.setCursor(55, 222); tft.print("ON");} // POWER OFF
   else if (power) {   tft.setTextSize(4); tft.setTextColor(0x2A69, ST7735_BLACK);  tft.setCursor(132, 222); tft.print("OFF"); 
    tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(55, 222); tft.print("ON");} // POWER ON
}

if (ORGOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU");
  if (digitalRead(Btn)==LOW) {delay(650); men="menu";mcnt=true;  MENOP=2; Enc.write(3);  tft.fillScreen(ST7735_BLACK); for (int i=0; i<104; i++){ring.setPixelColor(i,0);} ring.show(); doMenu();}
  }
else if (ORGOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU");}
}


void doBasic() {
  if (Serial.available()) {brightcnt=0; 
    for (int i=0; i<16; i++) {char val = Serial.read(); Rcolor[i]=val;}
    for (int i=0; i<104; i=i+2){ring.setPixelColor(i,Rcolor[3],Rcolor[4],Rcolor[5]);} 
 } 
  else {Rcolor[9]=Rcolor[9]-1; delay(13);
  } 
  ring.setBrightness(5+Rcolor[9]); ring.show();
}

void doSequence() {
    if (Serial.available()) {brightcnt=0; 
   for (int i=0; i<16; i++) {char val = Serial.read(); Rcolor[i]=val;}
   if (digitalRead(NXT)==LOW){delay(250); mancount=((mancount+1)%AROP); arraynumber=seqlist[mancount]; startAddress = 312*(arraynumber-1);}
    for (int j=0; j<TOT; j++) {int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}}
  else {Rcolor[9]=Rcolor[9]-1; delay(13);
  } 
  ring.setBrightness(5+Rcolor[9]); ring.show();
}

void doTriad() {
  if (Serial.available()) {brightcnt=0; 
    for (int i=0; i<16; i++) {char val = Serial.read(); Rcolor[i]=val;}
    for (int i=0; i<45; i=i+2){ring.setPixelColor(i,Rcolor[3],Rcolor[4],Rcolor[5]);} 
    for (int i=45; i<80; i=i+2){ring.setPixelColor(i,Rcolor[10],Rcolor[11],Rcolor[12]);} 
    for (int i=80; i<104; i=i+2){ring.setPixelColor(i,Rcolor[13],Rcolor[14],Rcolor[15]);} 
 } 
  else {Rcolor[9]=Rcolor[9]-1; delay(13);
  } 
  ring.setBrightness(5+Rcolor[9]); ring.show();
}

void doSpectrum() {
  if (Serial.available()) { 
    for (int i=0; i<16; i++) {char val = Serial.read(); Rcolor[i]=val;}
    for (int i=0; i<45; i=i+2){ring.setPixelColor(i,Rcolor[0],Rcolor[1],Rcolor[2]);} 
    for (int i=46; i<82; i=i+2){ring.setPixelColor(i,Rcolor[3],Rcolor[4],Rcolor[5]);}
    for (int i=80; i<104; i=i+2){ring.setPixelColor(i,Rcolor[6],Rcolor[7],Rcolor[8]);}  
 } 
  else {Rcolor[9]=Rcolor[9]-1; delay(13);
  } 
  ring.setBrightness(5+Rcolor[9]); ring.show();
}


void doFlasher() {NXTstate = digitalRead(NXT);
if (afcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 10, 1, 305, 0x8811); tft.drawLine(239, 10, 239, 305, 0x8811); tft.drawLine(120, 10, 120, 243, 0x8811);
tft.drawLine(0, 10, 240, 10, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
afcnt=!afcnt;
tft.drawLine(0, 45, 240, 45, 0x8811);  tft.drawLine(0, 281, 240, 281, 0x8811);
tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
for (int j=0; j<6; j++){ 
  if (aflist[j]<10){ tft.setCursor(55,52+33*j);} else if (9<aflist[j]){ tft.setCursor(45,52+33*j);} tft.print(aflist[j]); 
  if (freqlist[j]<100){ tft.setCursor(155, 52+33*j);} else if (99<freqlist[j]){ tft.setCursor(145,52+33*j);} dtostrf(float(float(freqlist[j])/10),-4,1,fout2); tft.print(fout2); 
  tft.drawLine(0, 78+33*j, 240, 78+33*j, 0x8811);
}
}
if (arf=="choicemenu"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 4)+4) % 4); count = PLACE; AFOP = abs(valENC+1);}}
else if (arf=="choice"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 6)+6) % 6); count = PLACE; ARFOP = abs(valENC+1); arc=ARFOP;} }
else if (arf=="frequency" && digitalRead(SAVE)==HIGH){ spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 999)+999) % 999); count = PLACE; FREQOP = abs(valENC+1); fc=FREQOP; fval1=float(fc)/10; dtostrf(fval1,-4,1,fout1); } }


if (AFOP==1 && arf=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 18); tft.print("ARRAY"); 
    if (digitalRead(Btn)==LOW){delay(400); arf="choice"; tft.fillRect(30, 49+33*(arcounter), 62, 27, 0x2A69);}
}
if (AFOP==1 && arf=="choice"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 18); tft.print("ARRAY");
    if (arcn!=arc){tft.fillRect(30, 49+33*arcounter, 62, 27, 0x2A69); arcn=arc; } 
    if (arc<10){ tft.setCursor(55,52+33*arcounter);} else if (9<arc){ tft.setCursor(45,52+33*arcounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(ARFOP);
  if (digitalRead(Btn)==LOW){delay(400);  tft.fillRect(30, 49+33*(arcounter), 62, 27, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    aflist[arcounter]=ARFOP; 
    if (arc<10){ tft.setCursor(55,52+33*arcounter);} else if (9<arc){ tft.setCursor(45,52+33*arcounter);} tft.print(aflist[arcounter]); 
      arcounter=arcounter+1; Enc.write(2*aflist[arcounter]-2);
    if (arcounter==6){arcounter=0; AFOP=2; Enc.write(2); arf="choicemenu";} else if(arcounter!=6){tft.fillRect(30, 49+33*(arcounter), 62, 27, 0x2A69);}
    ARFOP=aflist[arcounter]; 
  }
  if (digitalRead(NXT)==LOW){ Enc.write(2*freqlist[arcounter]-2);
    delay(400);  tft.fillRect(30, 49+33*(arcounter), 62, 27, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    aflist[arcounter]=ARFOP; 
    if (arc<10){ tft.setCursor(55,52+33*arcounter);} else if (9<arc){ tft.setCursor(45,52+33*arcounter);} tft.print(aflist[arcounter]); 
    fcounter=arcounter; AFOP=2; fcn=100; arf="frequency";
    }
}
else if (AFOP!=1 && arf!="none") {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(20, 18); tft.print("ARRAY");}

if (AFOP==2 && arf=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(165, 18); tft.print("Hz");
    if (digitalRead(Btn)==LOW){delay(400); arf="frequency"; tft.fillRect(130, 49+33*(fcounter), 100, 27, 0x2A69); 
        if (fc<100){ tft.setCursor(155, 52+33*fcounter);} 
        else if (99<fc){ tft.setCursor(145,52+33*fcounter);} 
        tft.setTextColor(ST7735_BLACK, 0x2A69); 
        fval2=float(freqlist[fcounter])/10; dtostrf(fval2,-4,1,fout1); tft.print(fout1); Enc.write(2*freqlist[fcounter]-1);
        
    }
}
if (AFOP==2 && arf=="frequency"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(165, 18); tft.print("Hz");
    if (digitalRead(SAVE)==LOW){delay(100); FREQOP=FREQOP+100; if (999<FREQOP){FREQOP=0;} fc=FREQOP;  fval1=(float(fc)/10); dtostrf(fval1,-4,1,fout1);  Enc.write(2*fc-1); delay(200); }
    if (fcn!=fc){tft.fillRect(130, 49+33*fcounter, 100, 27, 0x2A69); fcn=fc; } 
    if (fc<100){ tft.setCursor(155, 52+33*fcounter);} else if (99<fc){ tft.setCursor(145,52+33*fcounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(fout1);
  if (digitalRead(Btn)==LOW){ delay(400); tft.fillRect(125, 49+33*fcounter, 110, 27, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    freqlist[fcounter]=FREQOP; 
    if (fc<100){ tft.setCursor(155,52+33*fcounter);} else if (99<fc){ tft.setCursor(145,52+33*fcounter);} tft.print(fout1); 
    fcounter=fcounter+1; Enc.write(2*freqlist[fcounter]-2);
    if (fcounter==6){fcounter=0; AFOP=3; Enc.write(4); arf="choicemenu";} else if(fcounter!=6){tft.fillRect(130, 49+33*fcounter, 100, 27, 0x2A69);}
    FREQOP=freqlist[fcounter]; fc=FREQOP; fval2=float(fc)/10; dtostrf(fval2,-4,1,fout2); 
  } 
   if (digitalRead(NXT)==LOW){ Enc.write(2*aflist[fcounter]-2);
    delay(400);  tft.fillRect(125, 49+33*(fcounter), 110, 27, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    freqlist[fcounter]=FREQOP; 
    if (fc<100){ tft.setCursor(155,52+33*fcounter);} else if (99<fc){ tft.setCursor(145,52+33*fcounter);} tft.print(fout1); 
    arcounter=fcounter; AFOP=1; arcn=100; arf="choice";
    }
}
else if (AFOP!=2 && arf!="none") {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(165, 18); tft.print("Hz");}

if ((AFOP==3 && arf=="choicemenu") || (AFOP==3 && arf=="none")){if (arf=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(18, 253); tft.print("POWER");} 
  if (digitalRead(Btn)==LOW) {delay(400);  flpower=!flpower; t = now(); arraynumber=aflist[0]; startAddress = 312*(arraynumber-1); arcount=0; df=float(1)/float(float(freqlist[arcount])/10);}
  if (!flpower) {tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(182, 253); tft.print("OFF");  // POWER OFF
    tft.setTextColor(0x2A69, ST7735_BLACK); tft.setCursor(135, 253); tft.print("ON"); for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show();} 
  else if (flpower) {tft.setTextSize(3); tft.setTextColor(0x2A69, ST7735_BLACK);  tft.setCursor(182, 253); tft.print("OFF"); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(135, 253); tft.print("ON"); // POWER ON
    men="flash"; doFlash(); tft.setTextColor(0x47E0, ST7735_BLACK);  tft.setCursor(55,52+33*arcount); tft.print(aflist[arcount]);
   }
}
else if (AFOP!=3 && arf!="none") {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(18, 253); tft.print("POWER");
    tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(182, 253); tft.print("OFF"); 
    tft.setTextColor(0x2A69, ST7735_BLACK); tft.setCursor(135, 253); tft.print("ON");// POWER OFF
}

if (AFOP==4 && arf=="choicemenu"){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(38, 287); tft.print("RETURN TO MENU");
  if (digitalRead(Btn)==LOW) {delay(650); men="menu";mcnt=true;  MENOP=3; Enc.write(5);  tft.fillScreen(ST7735_BLACK); for (int i=0; i<104; i++){ring.setPixelColor(i,0);} ring.show(); doMenu();}
  }
else if (AFOP!=4 && arf!="none") {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(38, 287); tft.print("RETURN TO MENU");}
}


/// THESE GO WITH doFlasher()
void doFlash() { arf="none";
interrupts(); attachInterrupt(digitalPinToInterrupt(Btn), dobreak, CHANGE); attachInterrupt(digitalPinToInterrupt(NXT), doflashnext, CHANGE);
int DIAL0 = analogRead(DIMM); int B=map(DIAL0,0,1023,8,255); readFromEEPROM(startAddress, pixelsM, 312);    
  for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show();
    delay(int(df*1000)); 
  for (int j=0; j<TOT; j++) { int jj=3*j; ring.setPixelColor(j, pixelsM[jj], pixelsM[jj+1], pixelsM[jj+2]);}  ring.setBrightness(B); ring.show(); delay(5);
  for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show();
}
void dobreak() {for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show(); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  tft.setCursor(55,52+33*arcount); tft.print(aflist[arcount]);men="flasher"; flpower=false; delay(30); AFOP=3; arf="choicemenu"; Enc.write(4);  noInterrupts(); detachInterrupt(digitalPinToInterrupt(Btn)); detachInterrupt(digitalPinToInterrupt(NXT)); delay(600); doFlasher();}
void doflashnext() {delay(100); arf="none"; tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  tft.setCursor(55,52+33*(arcount)); tft.print(aflist[arcount]); 
  arcount=((((arcount+1)%6)+6)%6); df=float(1)/float(float(freqlist[arcount])/10); arraynumber=aflist[arcount]; startAddress = 312*(arraynumber-1); delay(400); 
  tft.setTextColor(0x47E0, ST7735_BLACK);  tft.setCursor(55,52+33*arcount); tft.print(aflist[arcount]);
  doFlash();
} 




void doReset() { 
if (rcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.drawLine(0, 274, 240, 274, 0x8811); 
tft.setTextSize(1); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(15, 30); tft.print("RESET DEVICE"); tft.drawLine(0, 60, 240, 60, 0x8811); 
tft.drawLine(30, 210, 210, 210, 0x8811); tft.drawLine(30, 250, 210, 250, 0x8811); tft.drawLine(30, 210, 30, 250, 0x8811); tft.drawLine(210, 210, 210, 250, 0x8811);
tft.setTextSize(2); tft.setTextColor(0x7BEF, ST7735_BLACK); tft.setCursor(37, 75); tft.print("RESETTING THIS"); tft.setCursor(18, 100); tft.print("DEVICE WILL ERASE"); tft.setCursor(19, 125); tft.print("ALL OF YOUR DATA.");
tft.setCursor(29, 155); tft.print("BE SURE TO SAVE"); tft.setCursor(30, 180); tft.print("BEFORE ERASING.");
rcnt=!rcnt; Enc.write(0);
}

if (men=="reset") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 2)+2) % 2); count = PLACE; RESETOP = abs(valENC+1);} }

if (RESETOP==1) { tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 220); tft.print("RESET NOW"); 
  if (digitalRead(Btn)==LOW) {delay(500); men="verify"; vcnt=true; VEROP=2; Enc.write(3); tft.fillRect(16, 120, 208, 132, ST7735_BLACK); doRESETVERIFY();}
}
else if (RESETOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 220); tft.print("RESET NOW");}

if (RESETOP==2) { tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU"); 
  if (digitalRead(Btn)==LOW) {delay(650); men="off"; mcnt=true;  MENOP=5; Enc.write(9); tft.fillScreen(ST7735_BLACK); doMenu();} //setup();}
}
else if (RESETOP!=2) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU");}
}


void doRESETVERIFY() {
  if (vcnt) { vcnt=!vcnt; tft.fillRect(16, 120, 208, 132, ST7735_BLACK); 
    tft.drawLine(16, 120, 224, 120, ST7735_WHITE); tft.drawLine(16, 252, 224, 252, ST7735_WHITE); tft.drawLine(16, 120, 16, 252, ST7735_WHITE); tft.drawLine(224, 120, 224, 252, ST7735_WHITE);
    tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(48,135); tft.print("ARE YOU SURE"); tft.setCursor(76,155); tft.print("YOU WANT");  tft.setCursor(72,175); tft.print("TO RESET?");
    tft.drawLine(42, 205, 115, 205, 0x07E0); tft.drawLine(42, 235, 115, 235, 0x07E0); tft.drawLine(42, 205, 42, 235, 0x07E0); tft.drawLine(115, 205, 115, 235, 0x07E0); // YES
    tft.drawLine(125, 205, 202, 205, 0xF800); tft.drawLine(125, 235, 202, 235, 0xF800); tft.drawLine(125, 205, 125, 235, 0xF800); tft.drawLine(202, 205, 202, 235, 0xF800); //NO 
  }

if (men=="verify") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 2)+2) % 2); count = PLACE; VEROP = abs(valENC+1);}}

if (VEROP==1 && men=="verify") {tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(53, 210); tft.print("YES");
    if (digitalRead(Btn)==LOW) {delay(400); men="off"; mcnt=true; startcounter=true; MENOP=1; Enc.write(0); tft.fillScreen(ST7735_BLACK); for (int i=0; i<EEPROM.length(); i++){EEPROM.write(i,0);} setup();}
}
else if (VEROP!=1 && men=="verify"){ tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(53, 210); tft.print("YES");}

if (VEROP==2 && men=="verify") {tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(148, 210); tft.print("NO");
  if (digitalRead(Btn)==LOW) {delay(400); men="reset"; rcnt=true;  RESETOP=1; Enc.write(0); doReset();}
}
else if (VEROP!=2 && men=="verify"){tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(148, 210); tft.print("NO");}
}



void doListChoose() { 
if (listcounter) {SD.begin(21); delay(300);  root = SD.open("/");
  if (SD.begin(21)){
      while (true) { extension="";
       File entry = root.openNextFile();
       if (! entry) {break;}
       fname=entry.name(); 
      for (int i=(strlen(entry.name())-4); i<(strlen(entry.name())+1); i++){extension+=fname[i]; } 
      if (!entry.isDirectory() && (strlen(entry.name())<13) && extension==".txt" && fname[0]!='.') {
        filenamelist[filecounter]=fname; filenamelistNOext[filecounter]=fname.remove(strlen(entry.name())-4);  filecounter=filecounter+1; lengthlist=filecounter;
      }
      entry.close();
      }
     }
listcounter=!listcounter; FILEOP=1; men="showlist"; listcount2=true; tft.fillRect(42, 80, 156, 30, 0XC618);
}

if (men=="showlist"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); listcount2=true; valENC = ((((PLACE) % lengthlist)+lengthlist) % lengthlist); count = PLACE; FILEOP = abs(valENC+1);}}

for (int j=0; j<6; j++) {
  if (FILEOP==(j+1) && men=="showlist" && listcount2) { seqchoice=filenamelistNOext[j]; seqchoice2=filenamelist[j]; tft.fillRect(42, 80+30*j, 156, 30, 0XC618); tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, 0XC618);  tft.setCursor(48, 85+30*j); tft.print(filenamelistNOext[j]);
      //if (digitalRead(Btn)==LOW && men=="showlist") {delay(100);  dircnt=true; men="directory"; DIROP=2; Enc.write(3); doDirectory();}
  }
  else if (FILEOP!=(j+1)  && men=="showlist" && listcount2){ tft.fillRect(42, 80+30*j, 156, 30, ST7735_WHITE); tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, ST7735_WHITE); tft.setCursor(48, 85+30*j); tft.print(filenamelistNOext[j]);}
 if (digitalRead(Btn)==LOW && men=="showlist") {delay(100); dircnt=true; men="directory"; DIROP=2; Enc.write(3); doDirectory();}
}
listcount2=false;
}



void doDirectory(){
  if (dircnt) {dircnt=!dircnt; tft.fillRect(28, 38, 184, 258, ST7735_BLACK); tft.fillRect(42, 130, 156, 30, ST7735_WHITE); tft.drawLine(28, 180, 212, 180, 0x8811); tft.drawLine(28, 238, 212, 238, 0x8811);
    for(int j=0; j<4; j++){tft.drawLine(28, 38+j, 212, 38+j, 0x8811); tft.drawLine(28, 296-j, 212, 296-j, 0x8811); tft.drawLine(28+j, 38, 28+j, 296, 0x8811); tft.drawLine(212-j, 38, 212-j, 296, 0x8811);}
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE); tft.setTextSize(3); tft.setCursor(48, 135);  tft.print(seqchoice); 
  }
  if (men=="directory"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; DIROP = abs(valENC+1);}}


  if (DIROP==1 && men=="directory"){ tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setTextSize(2); tft.setCursor(60, 55); tft.print("CHOOSE THE"); tft.setCursor(50, 75); tft.print("SEQUENCE YOU"); tft.setCursor(46, 95); tft.print("WANT TO LOAD:");
     if (digitalRead(Btn)==LOW) {delay(80); newload=false; men="showlist"; listcounter=true; listcount2=true; FILEOP=1; Enc.write(0); tft.fillRect(42, 80, 156, 180, ST7735_WHITE); doListChoose();}
  }
  else if (DIROP!=1 && men=="directory"){tft.setTextColor(0x4416, ST7735_BLACK); tft.setTextSize(2); tft.setCursor(60, 55); tft.print("CHOOSE THE"); tft.setCursor(50, 75); tft.print("SEQUENCE YOU"); tft.setCursor(46, 95); tft.print("WANT TO LOAD:");}

  if (DIROP==2 && men=="directory"){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(85, 200); tft.print("LOAD");
      if (digitalRead(Btn)==LOW && seqchoice!="FILENAME") {delay(400); men="load";loadcount=true; LOADOP=1; Enc.write(0);}
  }
  else if (DIROP!=2 && men=="directory"){tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(85, 200); tft.print("LOAD");}

  if (DIROP==3 && men=="directory"){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(85, 255); tft.print("EXIT");
      if (digitalRead(Btn)==LOW) {delay(400);  men="sd"; SDOP=2; Enc.write(3); sdcnt=true; filecounter=0; newload=true; doSD();}
  }
  else if (DIROP!=3  && men=="directory"){tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(85, 255); tft.print("EXIT");}
}



void doSDLOAD() {
   if (loadcount) {loadcount=!loadcount; tft.fillRect(16, 90, 208, 180, ST7735_BLACK); 
    tft.drawLine(16, 90, 224, 90, ST7735_WHITE); tft.drawLine(16, 270, 224, 270, ST7735_WHITE); tft.drawLine(16, 90, 16, 270, ST7735_WHITE); tft.drawLine(224, 90, 224, 270, ST7735_WHITE);
    tft.setTextSize(2); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(26,105); tft.print("ARE YOU CERTAIN?"); tft.setCursor(30,130); tft.print("LOADING A SAVED"); 
    tft.setCursor(42,155); tft.print("SEQUENCE WILL"); tft.setCursor(26,180); tft.print("OVERWRITE ALL OF"); tft.setCursor(26,205); tft.print("YOUR SAVED DATA!"); LOADOP=2; Enc.write(3);
    tft.drawLine(42, 230, 115, 230, 0x07E0); tft.drawLine(42, 260, 115, 260, 0x07E0); tft.drawLine(42, 230, 42, 260, 0x07E0); tft.drawLine(115, 230, 115, 260, 0x07E0); // YES
    tft.drawLine(125, 230, 202, 230, 0xF800); tft.drawLine(125, 260, 202, 260, 0xF800); tft.drawLine(125, 230, 125, 260, 0xF800); tft.drawLine(202, 230, 202, 260, 0xF800); //NO
   }
   
 if (men="load") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 2)+2) % 2); count = PLACE; LOADOP = abs(valENC+1);}}

if (LOADOP==1 && men=="load"){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(53, 235); tft.print("YES");
  if (digitalRead(Btn)==LOW) { delay(80); int timer=0; int timer1=0; int timer2=0; int timer3=0; //timelist[6]; 
     File myFile = SD.open(seqchoice2.c_str()); //Serial.println(myFile.size());
   if (myFile) {  
     // ARRAY COUNT AND REPEAT Y/N
     if (myFile) {delay(10); String temp1=myFile.readStringUntil('.').trim(); String temp2=myFile.readStringUntil('.').trim();
        opt=temp2; AROP=temp1.toInt(); TOTAL=AROP; LNGTHOP=AROP; for (int i=0; i<AROP; i++){seqlist[i]=(i+1);}  delay(50); if (opt=="Y") {repnum=200;} else if (opt=="N") {repnum=1;}
     }
    for (int loadlevel=0; loadlevel<(313*AROP+13); loadlevel++) {
        if (myFile) { // delay(5);
          // RGB arrays
          if (loadlevel<(312*AROP)) {String pix1=myFile.readStringUntil('.').trim(); int pix2=pix1.toInt(); pixelsS1[timer]=pix2; pixelsS2[timer]=pix2;  timer++;}
          // timelist[]
          if ((312*AROP-1)<loadlevel && loadlevel<(313*AROP)) {String temp3=myFile.readStringUntil('.').trim(); int temp4=temp3.toInt(); if(temp4!=0) {timelist[timer1]=temp4; timer1++;}}
          // translist[]
          if ((313*AROP-1)<loadlevel && loadlevel<(313*AROP+6)) {String temp1=myFile.readStringUntil('.').trim(); translist[timer2]=temp1; timer2++;}
          // animlist[]
          if ((313*AROP+5)<loadlevel && loadlevel<(313*AROP+12)) {String temp2=myFile.readStringUntil('.').trim(); animlist[timer3]=temp2; timer3++;}
        }  
    }
   myFile.close(); 
   }   
      startAddress=0; SDtoEEPROM(startAddress,pixelsS2, 312*6); 
      delay(100); //if (AROP<6) {startAddress=(312*AROP); for (int j=312*AROP; j<(312*6+1); j++){pixelsS2[j]=0;} SDtoEEPROM(startAddress, 0, (312*(6-AROP)));}
      men="seq"; seq="seqmenu"; scnt=true;  filecounter=0; SEQOP=1; Enc.write(0);  tft.fillScreen(ST7735_BLACK); doSequences();
   }
}
  else if (LOADOP!=1 && men=="load"){ tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(53, 235); tft.print("YES");}

  if (LOADOP==2 && men=="load"){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(148, 235); tft.print("NO");
      if (digitalRead(Btn)==LOW) {delay(400); dircnt=true; men="directory"; DIROP=3; Enc.write(5);  
      tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
      tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.drawLine(0, 60, 240, 60, 0x8811); tft.drawLine(0, 131, 240, 131, 0x8811); 
      tft.drawLine(0, 202, 240, 202, 0x8811); tft.drawLine(0, 274, 240, 274, 0x8811);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
      tft.setTextSize(1);  tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
      tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(60, 30); tft.print("SD CARD");
      doDirectory();}
  }
  else if (LOADOP!=2 && men=="load"){tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(148, 235); tft.print("NO"); }
}




void doKeyboard() {
  if (keycnt) {keycnt=!keycnt; tft.fillRect(28, 38, 184, 258, ST7735_BLACK); tft.fillRect(42, 50, 156, 30, ST7735_WHITE); tft.drawLine(28, 267, 212, 267, 0x8811);
    tft.drawLine(41, 49, 199, 49, 0x8811); tft.drawLine(41, 81, 199, 81, 0x8811); tft.drawLine(41, 49, 41, 81, 0x8811); tft.drawLine(199, 49, 199, 81, 0x8811);
    for(int j=0; j<4; j++){tft.drawLine(28, 38+j, 212, 38+j, 0x8811); tft.drawLine(28, 296-j, 212, 296-j, 0x8811); tft.drawLine(28+j, 38, 28+j, 296, 0x8811); tft.drawLine(212-j, 38, 212-j, 296, 0x8811);}
  }
  if (stringupdate){stringupdate=!stringupdate; tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, ST7735_BLACK); tft.setCursor(48,55); tft.print(filename);}
  
if (men=="keyboard"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 39)+39) % 39); count = PLACE; KEYOP = abs(valENC+1);}}

if (KEYOP==1){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 95); tft.print("A");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "A"; delay(400);}
}
else if (KEYOP!=1){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 95); tft.print("A");}

if (KEYOP==2){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(66, 95); tft.print("B");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "B"; delay(400);}
}
else if (KEYOP!=2){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(66, 95); tft.print("B");}

if (KEYOP==3){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(90, 95); tft.print("C");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "C"; delay(400);}
}
else if (KEYOP!=3){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(90, 95); tft.print("C");}

if (KEYOP==4){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(114, 95); tft.print("D");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "D"; delay(400);}
}
else if (KEYOP!=4){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(114, 95); tft.print("D");}

if (KEYOP==5){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(138, 95); tft.print("E");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "E"; delay(400);}
}
else if (KEYOP!=5){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(138, 95); tft.print("E");}

if (KEYOP==6){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(162, 95); tft.print("F");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "F"; delay(400);}
}
else if (KEYOP!=6){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(162, 95); tft.print("F");}

if (KEYOP==7){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(186, 95); tft.print("G");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "G"; delay(400);}
}
else if (KEYOP!=7){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(186, 95); tft.print("G");}

if (KEYOP==8){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 125); tft.print("H");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "H"; delay(400);}
}
else if (KEYOP!=8){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 125); tft.print("H");}

if (KEYOP==9){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(66, 125); tft.print("I");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "I"; delay(400);}
}
else if (KEYOP!=9){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(66, 125); tft.print("I");}

if (KEYOP==10){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(90, 125); tft.print("J");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "J"; delay(400);}
}
else if (KEYOP!=10){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(90, 125); tft.print("J");}

if (KEYOP==11){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(114, 125); tft.print("K");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "K"; delay(400);}
}
else if (KEYOP!=11){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(114, 125); tft.print("K");}

if (KEYOP==12){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(138, 125); tft.print("L");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "L"; delay(400);}
}
else if (KEYOP!=12){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(138, 125); tft.print("L");}

if (KEYOP==13){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(162, 125); tft.print("M");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "M"; delay(400);}
}
else if (KEYOP!=13){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(162, 125); tft.print("M");}

if (KEYOP==14){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(186, 125); tft.print("N");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "N"; delay(400);}
}
else if (KEYOP!=14){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(186, 125); tft.print("N");}

if (KEYOP==15){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 155); tft.print("O");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "O"; delay(400);}
}
else if (KEYOP!=15){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 155); tft.print("O");}

if (KEYOP==16){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(66, 155); tft.print("P");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "P"; delay(400);}
}
else if (KEYOP!=16){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(66, 155); tft.print("P");}

if (KEYOP==17){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(90, 155); tft.print("Q");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "Q"; delay(400);}
}
else if (KEYOP!=17){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(90, 155); tft.print("Q");}

if (KEYOP==18){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(114, 155); tft.print("R");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "R"; delay(400);}
}
else if (KEYOP!=18){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(114, 155); tft.print("R");}

if (KEYOP==19){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(138, 155); tft.print("S");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "S"; delay(400);}
}
else if (KEYOP!=19){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(138, 155); tft.print("S");}

if (KEYOP==20){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(162, 155); tft.print("T");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "T"; delay(400);}
}
else if (KEYOP!=20){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(162, 155); tft.print("T");}

if (KEYOP==21){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(186, 155); tft.print("U");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "U"; delay(400);}
}
else if (KEYOP!=21){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(186, 155); tft.print("U");}

if (KEYOP==22){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 185); tft.print("V");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "V"; delay(400);}
}
else if (KEYOP!=22){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 185); tft.print("V");}

if (KEYOP==23){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(66, 185); tft.print("W");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "W"; delay(400);}
}
else if (KEYOP!=23){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(66, 185); tft.print("W");}

if (KEYOP==24){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(90, 185); tft.print("X");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "X"; delay(400);}
}
else if (KEYOP!=24){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(90, 185); tft.print("X");}

if (KEYOP==25){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(114, 185); tft.print("Y");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "Y"; delay(400);}
}
else if (KEYOP!=25){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(114, 185); tft.print("Y");}

if (KEYOP==26){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(138, 185); tft.print("Z");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "Z"; delay(400);}
}
else if (KEYOP!=26){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(138, 185); tft.print("Z");}

if (KEYOP==27){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(162, 185); tft.print("0"); 
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "0"; delay(400);}
}
else if (KEYOP!=27){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(162, 185); tft.print("0"); }

if (KEYOP==28){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(186, 185); tft.print("1");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "1"; delay(400);}
}
else if (KEYOP!=28){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(186, 185); tft.print("1");}

if (KEYOP==29){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 215); tft.print("2");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "2"; delay(400);}
}
else if (KEYOP!=29){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 215); tft.print("2");}

if (KEYOP==30){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(66, 215); tft.print("3");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "3"; delay(400);}
}
else if (KEYOP!=20){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(66, 215); tft.print("3");}

if (KEYOP==31){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(90, 215); tft.print("4");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "4"; delay(400);}
}
else if (KEYOP!=31){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(90, 215); tft.print("4");}

if (KEYOP==32){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(114, 215); tft.print("5");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "5"; delay(400);}
}
else if (KEYOP!=32){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(114, 215); tft.print("5");}

if (KEYOP==33){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(138, 215); tft.print("6"); 
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "6"; delay(400);}
}
else if (KEYOP!=33){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(138, 215); tft.print("6");} 

if (KEYOP==34){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(162, 215); tft.print("7"); 
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "7"; delay(400);}
}
else if (KEYOP!=34){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(162, 215); tft.print("7");}

if (KEYOP==35){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(186, 215); tft.print("8");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "8"; delay(400);}
}
else if (KEYOP!=35){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(186, 215); tft.print("8");}

if (KEYOP==36){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(42, 245); tft.print("9");
  if (digitalRead(Btn)==LOW && filename.length()<8) {stringupdate=true; filename += "9"; delay(400);}
}
else if (KEYOP!=36){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(42, 245); tft.print("9");}

if (KEYOP==37){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(72, 245); tft.print("ERASE");
  if (digitalRead(Btn)==LOW && 0<filename.length()) {delay(200); int ln=filename.length(); filename.remove(ln-1); tft.fillRect(48+(ln-1)*18, 50, 20, 30, ST7735_WHITE); delay(50); stringupdate=true;} 
}
else if (KEYOP!=37){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(72, 245); tft.print("ERASE");}

if (KEYOP==38){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(150, 245); tft.print("SAVE");
  if (digitalRead(Btn)==LOW && 0<filename.length() && (filename2!=filename)) {delay(400); filenametxt=filename; filenametxt+=".txt"; filename2=filename;
    if (SD.begin(21)) {
    SDfile = SD.open(filenametxt.c_str(), FILE_WRITE); SD.remove(filenametxt.c_str()); SDfile = SD.open(filenametxt.c_str(), FILE_WRITE);
      if (SDfile) { SDfile.println(AROP); SDfile.println("."); SDfile.println(opt); SDfile.println(".");
        for (int i=0; i<AROP; i++) { sdstartaddress=312*(seqlist[i]-1); for (int j=0; j<312; j++){ SDfile.println(EEPROM.read(sdstartaddress+j)); SDfile.println("."); } } 
        for (int i=0; i<AROP; i++) {SDfile.println(timelist[i]); SDfile.println(".");} //SDfile.println("+");
        for (int i=0; i<6; i++) {SDfile.println(translist[i]); SDfile.println(".");} //SDfile.println("+");
        for (int i=0; i<6; i++) {SDfile.println(animlist[i]); SDfile.println(".");} //SDfile.println("+");
        SDfile.close();
      }
    }
    delay(80); men="saveOK"; savecount=true; tft.fillRect(22, 110, 196, 120, ST7735_BLACK); doSaveOK();
  }
}
else if (KEYOP!=38){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(150, 245); tft.print("SAVE");}

if (KEYOP==39){ tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(95, 274); tft.print("EXIT");
  if (digitalRead(Btn)==LOW) {delay(400);  men="sd"; SDOP=1; Enc.write(1); sdcnt=true; filename=""; doSD();}
}
else if (KEYOP!=39){tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(95, 274); tft.print("EXIT");}  
}

void doSaveOK(){men="saveOK";
  if (savecount) {savecount=!savecount; tft.fillRect(22, 110, 196, 120, ST7735_BLACK); //delay(30);  
    tft.drawLine(22, 110, 218, 110, ST7735_WHITE); tft.drawLine(22, 230, 218, 230, ST7735_WHITE); tft.drawLine(22, 110, 22, 230, ST7735_WHITE); tft.drawLine(218, 110, 218, 230, ST7735_WHITE);
    tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(40,125); tft.print("YOUR FILE"); tft.setCursor(42,155); tft.print("IS SAVED!");
    tft.drawLine(84, 190, 156, 190, 0x07E0); tft.drawLine(84, 220, 156, 220, 0x07E0); tft.drawLine(84, 190, 84, 220, 0x07E0); tft.drawLine(156, 190, 156, 220, 0x07E0);
    tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(103,195); tft.print("OK");
  }
  if (digitalRead(Btn)==LOW) {delay(400);  men="sd"; SDOP=1; Enc.write(0); filename=""; savecount=true; sdcnt=true; doSD();}
}


void doSD() { 
if (sdcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.drawLine(0, 60, 240, 60, 0x8811); tft.drawLine(0, 167, 240, 167, 0x8811); tft.drawLine(0, 274, 240, 274, 0x8811);
tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1);  tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(60, 30); tft.print("SD CARD"); sdcnt=!sdcnt;  
}
if (men=="sd"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; SDOP = abs(valENC+1);}}

if (SDOP==1){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(83, 85); tft.print("SAVE A"); tft.setCursor(65, 120); tft.print("SEQUENCE"); tft.setCursor(17, 100); tft.print("1.");
tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(83, 192); tft.print("LOAD A"); tft.setCursor(65, 227); tft.print("SEQUENCE"); tft.setCursor(17, 207); tft.print("2.");
tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU"); 

  if (digitalRead(Btn)==LOW) {delay(400);  men="keyboard"; savecount=true; keycnt=true; KEYOP=1; Enc.write(0); doKeyboard();}
}
 
if (SDOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(83, 192); tft.print("LOAD A"); tft.setCursor(65, 227); tft.print("SEQUENCE"); tft.setCursor(17, 207); tft.print("2.");
tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(83, 85); tft.print("SAVE A"); tft.setCursor(65, 120); tft.print("SEQUENCE"); tft.setCursor(17, 100); tft.print("1.");
tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU");
  if (digitalRead(Btn)==LOW) {delay(400);  men="directory"; dircnt=true; DIROP=1; for (int i=0; i<100; i++){filenamelist[i]=' '; filenamelistNOext[i]=' ';} seqchoice="FILENAME"; Enc.write(0); doDirectory();}
}

if (SDOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(38, 284); tft.print("RETURN TO MENU");
tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(83, 85); tft.print("SAVE A"); tft.setCursor(65, 120); tft.print("SEQUENCE"); tft.setCursor(17, 100); tft.print("1.");
tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(83, 192); tft.print("LOAD A"); tft.setCursor(65, 227); tft.print("SEQUENCE"); tft.setCursor(17, 207); tft.print("2.");
  if (digitalRead(Btn)==LOW) {delay(650); men="menu";mcnt=true;  MENOP=4; Enc.write(7);  tft.fillScreen(ST7735_BLACK); doMenu();}
}
}



// These are sub-menus in SEQUENCES

void doLength() { seq="length";
if (lcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
  tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
  tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
  lcnt=!lcnt; LNGTHOP=1;
  tft.drawLine(70, 65, 170, 65, 0x8811); tft.drawLine(70, 125, 170, 125, 0x8811);
  tft.drawLine(70, 65, 70, 125, 0x8811); tft.drawLine(170, 65, 170, 125, 0x8811);
  tft.drawLine(0, 140, 240, 140, 0x8811); 
  tft.drawLine(70, 188, 170, 188, 0x8811); tft.drawLine(70, 248, 170, 248, 0x8811);
  tft.drawLine(70, 188, 70, 248, 0x8811); tft.drawLine(170, 188, 170, 248, 0x8811);
  tft.drawLine(0, 263, 240, 263, 0x8811); 
}
if (len=="length") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; LNGTHOP = abs(valENC+1);}}
else if (len=="lengtharray") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = (((PLACE % totalarrays)+totalarrays) % totalarrays); count = PLACE; AROP = abs(valENC+1);}}
else if (len=="repeat") {spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((2-PLACE) % 2)+2) % 2); count = PLACE; REPOP = abs(valENC+1);} 
      if (REPOP==1){opt="N"; repnum=1;} else if (REPOP==2){opt="Y"; repnum=200;}
}

if (LNGTHOP==1){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 30); tft.print("LENGTH");
 if (digitalRead(Btn)==LOW) {delay(400);  rectanglecountone=!rectanglecountone;}
   if (rectanglecountone==false && rectanglecounttwo==false) {tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP);} // not selected
   else if (rectanglecountone==true && rectanglecounttwo==true) {tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 78); tft.print(AROP);} // selected
   else if (rectanglecountone==true && rectanglecounttwo==false) {
      len="lengtharray"; tft.fillRect(71, 66, 98, 58, 0x2A69); tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 78); tft.print(AROP); rectanglecounttwo=!rectanglecounttwo;}
   else if (rectanglecountone==false && rectanglecounttwo==true) {
      len="length"; tft.fillRect(71, 66, 98, 58, ST7735_BLACK); tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP); rectanglecounttwo=!rectanglecounttwo;
      int seqlist[AROP];  for (int j=0; j<AROP; j++) {seqlist[j]=1;} int timelist[AROP]; LNGTHOP=1; Enc.write(1); for (int j=0; j<AROP; j++) {timelist[j]=10; TOTAL=AROP;}  
      }
}
else if (LNGTHOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 30); tft.print("LENGTH"); 
    tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 78); tft.print(AROP); //tft.setCursor(90, 78); tft.print("10"); for 10 to under need to do blk rect
}

if (LNGTHOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 155); tft.print("REPEAT");
 if (digitalRead(Btn)==LOW) {delay(400);  rectwocountone=!rectwocountone; Enc.write(1);}
   if (rectwocountone==false && rectwocounttwo==false) {tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt);} // not selected
   else if (rectwocountone==true && rectwocounttwo==true) {tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 200); tft.print(opt);} // selected
   else if (rectwocountone==true && rectwocounttwo==false) {
      len="repeat"; tft.fillRect(71, 189, 98, 58, 0x2A69); tft.setTextSize(5); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 200); tft.print(opt); rectwocounttwo=!rectwocounttwo;}
   else if (rectwocountone==false && rectwocounttwo==true) {
      len="length"; tft.fillRect(71, 189, 98, 58, ST7735_BLACK); tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt); LNGTHOP=2; Enc.write(2);  rectwocounttwo=!rectwocounttwo;}
}
else if (LNGTHOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 155); tft.print("REPEAT");
    tft.setTextSize(5); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); tft.setCursor(108, 200); tft.print(opt); 
}

if (LNGTHOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=1; Enc.write(0);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (LNGTHOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}


void doChooseArrays() {
if (cacnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.drawLine(120, 15, 120, 268, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.drawLine(0, 58, 240, 58, 0x8811); cacnt=!cacnt; Enc.write(0); CAOP=1;
tft.drawLine(0, 268, 240, 268, 0x8811);
tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
for (int j=0; j<AROP; j++){ 
  if (seqlist[j]<10){ tft.setCursor(55,65+35*j);} else if (9<seqlist[j]){ tft.setCursor(45,65+35*j);} tft.print(seqlist[j]); 
  if (timelist[j]<10){ tft.setCursor(175, 65+35*j);} else if (9<timelist[j]){ tft.setCursor(165,65+35*j);} tft.print(timelist[j]); 
  tft.drawLine(0, 93+35*j, 240, 93+35*j, 0x8811);
}
}
if (cho=="choicemenu"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; CAOP = abs(valENC+1);}}
else if (cho=="choice"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % totalarrays)+totalarrays) % totalarrays); count = PLACE; ARROP = abs(valENC+1); ac=ARROP;} }
else if (cho=="time"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 60)+60) % 60); count = PLACE; TIMEOP = abs(valENC+1); tc=TIMEOP;}}

if (CAOP==1 && cho=="choicemenu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 28); tft.print("ARRAY"); 
    if (digitalRead(Btn)==LOW){delay(400); cho="choice"; tft.fillRect(30, 61+35*(acounter), 62, 31, 0x2A69); Enc.write(2*seqlist[acounter]-1);}
}
if (CAOP==1 && cho=="choice"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(20, 28); tft.print("ARRAY");
    if (acn!=ac){tft.fillRect(30, 61+35*acounter, 62, 31, 0x2A69); acn=ac;} 
    if (ac<10){ tft.setCursor(55,65+35*acounter);} else if (9<ac){ tft.setCursor(45,65+35*acounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(ARROP);
  if (digitalRead(Btn)==LOW){delay(400);  tft.fillRect(30, 61+35*(acounter), 62, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    seqlist[acounter]=ARROP; 
    if (ac<10){ tft.setCursor(55,65+35*acounter);} else if (9<ac){ tft.setCursor(45,65+35*acounter);} tft.print(seqlist[acounter]); 
    acounter=acounter+1; Enc.write(2*seqlist[acounter]-1);
    if (acounter==AROP){acounter=0; CAOP=2; Enc.write(2); cho="choicemenu";} else if(acounter!=AROP){tft.fillRect(30, 61+35*(acounter), 62, 31, 0x2A69);}
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
    if (digitalRead(Btn)==LOW){delay(400); cho="time"; tft.fillRect(148, 61+35*(tcounter), 62, 31, 0x2A69); Enc.write(2*timelist[tcounter]-1);}
}
if (CAOP==2 && cho=="time"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(145, 28); tft.print("TIME");
    if (tcn!=tc){tft.fillRect(148, 61+35*tcounter, 62, 31, 0x2A69); tcn=tc;} 
    if (tc<10){ tft.setCursor(175, 65+35*tcounter);} else if (9<tc){ tft.setCursor(165,65+35*tcounter);} tft.setTextColor(ST7735_BLACK, 0x2A69); tft.print(TIMEOP);
  if (digitalRead(Btn)==LOW){ delay(400); tft.fillRect(148, 61+35*tcounter, 63, 31, ST7735_BLACK); tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  
    timelist[tcounter]=TIMEOP; 
    if (tc<10){ tft.setCursor(175,65+35*tcounter);} else if (9<tc){ tft.setCursor(165,65+35*tcounter);} tft.print(timelist[tcounter]); 
    tcounter=tcounter+1; Enc.write(2*timelist[tcounter]-1);
    if (tcounter==AROP){tcounter=0; CAOP=3; Enc.write(4); cho="choicemenu";} else if(tcounter!=AROP){tft.fillRect(148, 61+35*tcounter, 62, 31, 0x2A69);}
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
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=2; Enc.write(3);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (CAOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 280); tft.print("RETURN TO SEQUENCES");}
}


void doTransitions() {
if (tcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.drawLine(0, 58, 240, 58, 0x8811); tcnt=!tcnt;
TRANOP=1; Enc.write(0); tft.drawLine(0, 268, 240, 268, 0x8811);
tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
for (int j=0; j<AROP; j++){ 
  tft.setTextColor(0x4416, ST7735_BLACK); tft.setTextSize(3); tft.setCursor(26,66+35*j); tft.print("T"); tft.setTextSize(2); tft.setCursor(44,73+35*j); tft.print(j+1);
  tft.setCursor(74,69+35*j); tft.print("-"); tft.setTextSize(3); tft.setCursor(110,66+35*j); tft.setTextColor(0xD69A, ST7735_BLACK); tft.print(translist[j]);
  tft.drawLine(0, 93+35*j, 240, 93+35*j, 0x8811);
}
}
if (tra=="menu"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 2)+2) % 2); count = PLACE; TRANOP = abs(valENC+1); trancounter=(TRANOP-1);}}
else if (tra=="choice"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 7)+7) % 7); count = PLACE; TPICKOP = valENC;} tranc=TPICKOP;}
  if (TPICKOP==0){transmen="NONE";} 
  else if (TPICKOP==1){transmen="FADE";}
  else if (TPICKOP==2){transmen="SPIN";}     // translist[6] is a list of strings "NONE" by default
  else if (TPICKOP==3){transmen="FLASH";} 
  else if (TPICKOP==4){transmen="RIPPLE";} 
  else if (TPICKOP==5){transmen="SPIRAL";} 
  else if (TPICKOP==6){transmen="RANDOM";}

if (TRANOP==1 && tra=="menu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(23, 30); tft.print("TRANSITIONS");
  if (digitalRead(Btn)==LOW){delay(400); Enc.write(0); tra="choice"; tft.fillRect(100, 61+35*(trancounter), 124, 31, 0x2A69);}
}
if (TRANOP==1 && tra=="choice"){ 
    if (trancn!=tranc){tft.fillRect(100, 61+35*trancounter, 124, 31, 0x2A69); trancn=tranc;}
    tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setTextSize(3); tft.setCursor(26,66+35*trancounter); tft.print("T"); tft.setTextSize(2); tft.setCursor(44,73+35*trancounter); tft.print(trancounter+1);
    tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(110, 66+35*trancounter); tft.print(transmen);
  if (digitalRead(Btn)==LOW){delay(400); Enc.write(0); tft.fillRect(100, 61+35*trancounter, 124, 31, ST7735_BLACK); tft.setTextColor(0xD69A, ST7735_BLACK);  
      translist[trancounter]=transmen; tft.setCursor(110, 66+35*trancounter); tft.print(translist[trancounter]); 
      tft.setTextSize(3);  tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(26,66+35*trancounter); tft.print("T"); tft.setTextSize(2); tft.setCursor(44,73+35*trancounter); tft.print(trancounter+1); trancounter=trancounter+1;
      if (trancounter==AROP){ TRANOP=2; Enc.write(2); PLACE=Enc.read()>>1; count=PLACE; TPICKOP=trancounter=0; tra="menu";
         transmen=translist[0];
        if (transmen=="NONE"){TPICKOP=0;  } 
        else if (transmen=="FADE"){TPICKOP=1;  }
        else if (transmen=="SPIN"){TPICKOP=2;  }     
        else if (transmen=="FLASH"){TPICKOP=3;  } 
        else if (transmen=="RIPPLE"){TPICKOP=4;  } 
        else if (transmen=="SPIRAL"){TPICKOP=5;  }
        else if (transmen=="RANDOM"){TPICKOP=6;  }
      }
      else if(trancounter!=AROP){tft.fillRect(100, 61+35*(trancounter), 124, 31, 0x2A69);
        transmen=translist[trancounter];
        if (transmen=="NONE"){TPICKOP=0;  } 
        else if (transmen=="FADE"){TPICKOP=1;  }
        else if (transmen=="SPIN"){TPICKOP=2;  }     
        else if (transmen=="FLASH"){TPICKOP=3;  } 
        else if (transmen=="RIPPLE"){TPICKOP=4;  } 
        else if (transmen=="SPIRAL"){TPICKOP=5;  }
        else if (transmen=="RANDOM"){TPICKOP=6;  }  
      }
 }
}
else if (TRANOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(23, 30); tft.print("TRANSITIONS");trancounter=0;}

if (TRANOP==2){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=3; Enc.write(5);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (TRANOP!=2) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}


void doAnimations() {
if (acnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.drawLine(0, 58, 240, 58, 0x8811); acnt=!acnt; tft.drawLine(0, 268, 240, 268, 0x8811);
tft.setTextSize(3); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
for (int j=0; j<AROP; j++){ 
  tft.setTextColor(0x4416, ST7735_BLACK); tft.setTextSize(3); tft.setCursor(26,66+35*j); tft.print("A"); tft.setTextSize(2); tft.setCursor(44,73+35*j); tft.print(j+1);
  tft.setCursor(74,69+35*j); tft.print("-"); tft.setTextSize(3); tft.setCursor(110,66+35*j); tft.setTextColor(0xD69A, ST7735_BLACK); tft.print(animlist[j]);
  tft.drawLine(0, 93+35*j, 240, 93+35*j, 0x8811); ANIMOP=0; Enc.write(0);
}
}
if (ani=="menu"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 2)+2) % 2); count = PLACE; ANIMOP = abs(valENC+1); animcounter=(ANIMOP-1);}}
else if (ani=="choice"){spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 7)+7) % 7); count = PLACE; APICKOP = valENC;} animc=APICKOP;}
  if (APICKOP==0){animmen="NONE";} 
  else if (APICKOP==1){animmen="BLINK";}
  else if (APICKOP==2){animmen="SPARKLE";}     // animlist[6] is a list of strings "NONE" by default
  else if (APICKOP==3){animmen="SPIN";} 
  else if (APICKOP==4){animmen="RIPPLE";} 
  else if (APICKOP==5){animmen="SPIRAL";} 
  else if (APICKOP==6){animmen="RANDOM";}

if (ANIMOP==1 && ani=="menu"){tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(32, 30); tft.print("ANIMATIONS");
  if (digitalRead(Btn)==LOW){delay(400); Enc.write(0); ani="choice"; tft.fillRect(100, 61+35*(animcounter), 136, 31, 0x2A69);}
}
if (ANIMOP==1 && ani=="choice"){ 
    if (animcn!=animc){tft.fillRect(100, 61+35*animcounter, 136, 31, 0x2A69); animcn=animc;}
    tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setTextSize(3); tft.setCursor(26,66+35*animcounter); tft.print("A"); tft.setTextSize(2); tft.setCursor(44,73+35*animcounter); tft.print(animcounter+1);
    tft.setTextSize(3); tft.setTextColor(ST7735_BLACK, 0x2A69); tft.setCursor(108, 66+35*animcounter); tft.print(animmen);
  if (digitalRead(Btn)==LOW){delay(400); Enc.write(0); tft.fillRect(100, 61+35*animcounter, 136, 31, ST7735_BLACK); tft.setTextColor(0xD69A, ST7735_BLACK);  
      animlist[animcounter]=animmen; tft.setCursor(108, 66+35*animcounter); tft.print(animlist[animcounter]); 
      tft.setTextSize(3);  tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(26,66+35*animcounter); tft.print("A"); tft.setTextSize(2); tft.setCursor(44,73+35*animcounter); tft.print(animcounter+1); animcounter=animcounter+1;
      if (animcounter==AROP){ ANIMOP=2; Enc.write(2); PLACE=Enc.read()>>1; count=PLACE; APICKOP=animcounter=0; ani="menu";
         animmen=animlist[0];
        if (animmen=="NONE"){APICKOP=0;  } 
        else if (animmen=="BLINK"){APICKOP=1;  }
        else if (animmen=="SPARKLE"){APICKOP=2;  }     
        else if (animmen=="SPIN"){APICKOP=3;  } 
        else if (animmen=="RIPPLE"){APICKOP=4;  } 
        else if (animmen=="SPIRAL"){APICKOP=5;  }
        else if (animmen=="RANDOM"){APICKOP=6;  }
      }
      else if(animcounter!=AROP){tft.fillRect(100, 61+35*(animcounter), 136, 31, 0x2A69);
        animmen=animlist[animcounter];
        if (animmen=="NONE"){APICKOP=0;  } 
        else if (animmen=="BLINK"){APICKOP=1;  }
        else if (animmen=="SPARKLE"){APICKOP=2;  }     
        else if (animmen=="SPIN"){APICKOP=3;  } 
        else if (animmen=="RIPPLE"){APICKOP=4;  } 
        else if (animmen=="SPIRAL"){APICKOP=5;  }
        else if (animmen=="RANDOM"){APICKOP=6;  }  
      }
 }
}
else if (ANIMOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(32, 30); tft.print("ANIMATIONS");animcounter=0;}

if (ANIMOP==2){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=4; Enc.write(7);  tft.fillScreen(ST7735_BLACK); doSequences();}
  }
else if (ANIMOP!=2) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}

void dobreak2() {delay(50); br="break"; for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show(); RUNOP=1; Enc.write(1); delay(200); noInterrupts(); detachInterrupt(digitalPinToInterrupt(Btn)); delay(100); doPlay();}
void dobreak3() {delay(50); br="break"; for (int j=0; j<TOT; j++) {ring.setPixelColor(j, 0);} ring.show(); Enc.write(3); delay(200); 
    noInterrupts(); detachInterrupt(digitalPinToInterrupt(Btn)); detachInterrupt(digitalPinToInterrupt(NXT)); 
    RUNOP=2; transmen="NONE"; seq="play"; delay(100); doPlay();
}

void doPlay() {  
if (plcnt==true) {tft.fillScreen(ST7735_BLACK); tft.drawLine(1, 15, 1, 305, 0x8811); tft.drawLine(239, 15, 239, 305, 0x8811);
tft.drawLine(0, 15, 240, 15, 0x8811); tft.drawLine(0, 305, 240, 305, 0x8811); tft.setTextColor(ST7735_WHITE, ST7735_BLACK); 
tft.setTextSize(1); tft.setCursor(65, 0); tft.setCursor(75, 0); tft.print("The Halo - Menu"); tft.setCursor(83, 310); tft.print("Premium v2.1");
tft.setTextSize(3); tft.setTextColor(0x47E0); tft.setCursor(15, 30); tft.print("RUN SEQUENCE"); tft.drawLine(0, 60, 240, 60, 0x8811); plcnt=!plcnt;
tft.drawLine(0, 161, 240, 161, 0x8811); tft.drawLine(0, 263, 240, 263, 0x8811); 
tft.drawLine(34, 80, 206, 80, 0x8811); tft.drawLine(34, 141, 206, 141, 0x8811); tft.drawLine(34, 181, 206, 181, 0x8811); tft.drawLine(34, 243, 206, 243, 0x8811);
tft.drawLine(34, 80, 34, 141, 0x8811); tft.drawLine(34, 181, 34, 243, 0x8811); tft.drawLine(206, 80, 206, 141, 0x8811); tft.drawLine(206, 181, 206, 243, 0x8811);
}

for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show();
spot = Enc.read(); PLACE = spot>>1; if (PLACE != count ) { delay(80); valENC = ((((PLACE) % 3)+3) % 3); count = PLACE; RUNOP = abs(valENC+1);}

if (RUNOP==1){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(84, 101); tft.print("AUTO");
if (digitalRead(Btn)==LOW) {delay(250); br="go"; transmen=translist[0]; animmen=animlist[0]; delay(200);
 interrupts(); attachInterrupt(digitalPinToInterrupt(Btn), dobreak2, CHANGE);
  for (int k=0; k<repnum; k++){
    if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;}
    for (int i=0; i<TOTAL; i++){  setTime(0); time_t t = now(); timelength=timelist[i]; if (timelength==0){timelength=1;} arraynumber=seqlist[i]; startAddress = 312*(arraynumber-1); animmen=animlist[i]; transmen=translist[i];for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show();
      if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;}
      for (int k=0; k<timelength; k++){ 
        if (br=="break"){ for (int j=0; j<TOT; j++) {ring.setPixelColor(j,0);} ring.show(); break;} 
        iter=k;
        int DIAL0 = analogRead(DIMM); B=map(DIAL0,0,1023,8,255); ring.setBrightness(B);  
        if (animmen=="NONE"){ for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show();

        delay(1000);
        } 
        if (animmen=="RANDOM"){  long randomnum=random(1,6); delay(50);
            if (randomnum==1){animmen="BLINK";}
            if (randomnum==2){animmen="SPARKLE";}
            if (randomnum==3){animmen="SPIN";}
            if (randomnum==4){animmen="RIPPLE";}
            if (randomnum==5){animmen="SPIRAL";}
          }  
        if (animmen=="BLINK"){ 
          for (int p=0; p<2; p++){
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(168);
              for (int i=0; i<TOT; i++){ring.setPixelColor(i, 0);} ring.show(); delay(78);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(168);
              for (int i=0; i<TOT; i++){ring.setPixelColor(i, 0);} ring.show(); delay(78);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); 
          }
        }
        else if (animmen=="SPARKLE"){ 
          for (int p=0; p<7; p++){ int RTOT=16; int TOTALRAND=TOT; int randomarray[RTOT];
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(20);
          for (int i=0; i<RTOT; i++){ randomarray[i]=random(0,TOTALRAND);}
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 0);} ring.show();
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 255-CR,255-CG,255-CB);} ring.show(); delay(20);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], CR, CG, CB);} ring.show(); delay(20);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 255-CR,255-CG,255-CB);} ring.show(); delay(20);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 0);} ring.show(); delay(20);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], CR, CG, CB);} ring.show(); delay(20);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); //delay(44);
          }     
        }
        else if (animmen=="SPIN"){ int pTOT=45; 
          for (int p=0; p<pTOT; p++) {
          for (int j=0; j<45; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+p+pTOT) % 45)+45) % 45), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //OUTER RING
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(((((j+p+pTOT) % 35)+35) % 35)+45, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //MIDDLE RING
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(((((j+p+pTOT) % 24)+24) % 24)+80, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //INNER RING
          ring.show(); delay(40);
        }
        } 
        else if (animmen=="RIPPLE"){ 
          for (int l=0; l<2; l++){ for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(2);
          for (int k=12; 0<k; k--) {
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(j+80, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //INNER RING
          ring.show(); delay(10);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(j+45, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//MIDDLE RING
          ring.show(); delay(10);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<45; j++) { int jj=(3*(j)+startAddress); ring.setPixelColor(j, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//OUTER RING
          ring.show(); delay(10);} 
          } 
        } 
        else if (animmen=="SPIRAL"){  
          for (int k=0; k<74; k++) {
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+k) % 104)+104) % 104), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}
          ring.show(); delay(11);}
        }
time_t t = now(); inc=second(t); 
} inc=0; 
    
    // TRANSITIONS GO HERE
        transmen=translist[i];
        //if (transmen=="NONE"){   } 
        if (transmen=="RANDOM"){ long randomnum=random(1,6);
            if (randomnum==1){transmen="FADE";}
            if (randomnum==2){transmen="SPIN";}
            if (randomnum==3){transmen="FLASH";}
            if (randomnum==4){transmen="RIPPLE";}
            if (randomnum==5){transmen="SPIRAL";}
         }
        if (transmen=="FADE"){ for (int j=0; j<80; j++){ring.setBrightness(B-j*B/80); ring.show(); delay(10);}  }
        else if (transmen=="SPIN"){  
          for (int k=0; k<40; k++) {
          for (int j=0; j<45; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+k) % 45)+45) % 45), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //OUTER RING
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(((((j+k) % 35)+35) % 35)+45, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //MIDDLE RING
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(((((j+k) % 24)+24) % 24)+80, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //INNER RING
          ring.show(); delay(20);}
        }     
        else if (transmen=="FLASH"){ 
          for (int j=0; j<13; j++){
            if ((j%2)==0){ring.setBrightness(B); ring.show(); delay(50);}
            else if ((j%2)==1){ring.setBrightness(5); ring.show(); delay(50);}  
          }
        } 
        else if (transmen=="RIPPLE"){ 
         for (int l=0; l<3; l++){
         for (int k=12; 0<k; k--) {
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(j+80, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //INNER RING
          ring.show(); delay(5);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(j+45, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//MIDDLE RING
          ring.show(); delay(5);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<45; j++) { int jj=(3*(j)+startAddress); ring.setPixelColor(j, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//OUTER RING
          ring.show(); delay(5);} 
         } 
        }  
        else if (transmen=="SPIRAL"){  
          for (int k=0; k<104; k++) {
          for (int j=0; j<104; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+k) % 104)+104) % 104), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}
          ring.show(); delay(7);}
        }
    } 
  }
  for (int j=0; j<TOT; j++) { ring.setPixelColor(j,0);} ring.show(); 
 }
}
else if (RUNOP!=1) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(84, 101); tft.print("AUTO"); }

if (RUNOP==2){ tft.setTextSize(3); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(68, 201); tft.print("MANUAL");
 if (digitalRead(Btn)==LOW && seq=="play") {delay(350); seq="manual"; mancount=0; arraynumber=seqlist[0]; animmen=animlist[mancount]; transmen=translist[mancount]; startAddress = 312*(arraynumber-1); 
    randomnum=random(1,6); doManualRun();
 }
} 
else if (RUNOP!=2) {tft.setTextSize(3); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(68, 201); tft.print("MANUAL");}

if (RUNOP==3){tft.setTextSize(2); tft.setTextColor(0xFFE0, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");
  if (digitalRead(Btn)==LOW) {delay(650); seq="seqmenu";scnt=true;  SEQOP=5; Enc.write(9);  tft.fillScreen(ST7735_BLACK); scnt=true; seq="seqmenu"; doSequences();}
  }
else if (RUNOP!=3) {tft.setTextSize(2); tft.setTextColor(0x4416, ST7735_BLACK); tft.setCursor(8, 278); tft.print("RETURN TO SEQUENCES");}
}


void donext2() { delay(100);
  transmen=translist[mancount]; 
        if (transmen=="RANDOM" && seq=="manual"){ randomnum=random(1,6);
            if (randomnum==1){transmen="FADE";}
            if (randomnum==2){transmen="SPIN";}
            if (randomnum==3){transmen="FLASH";}
            if (randomnum==4){transmen="RIPPLE";}
            if (randomnum==5){transmen="SPIRAL";}
         }
        if (transmen=="FADE" && seq=="manual"){ for (int j=0; j<80; j++){ring.setBrightness(B-j*B/80); ring.show(); delay(10);}  }
        if (transmen=="SPIN" && seq=="manual"){  
          for (int kk=0; kk<40; kk++) {
          for (int j=0; j<45; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+kk) % 45)+45) % 45), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //OUTER RING
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(((((j+kk) % 35)+35) % 35)+45, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //MIDDLE RING
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(((((j+kk) % 24)+24) % 24)+80, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //INNER RING
          ring.show(); delay(20);}
        }     
        if (transmen=="FLASH" && seq=="manual"){ 
          for (int j=0; j<13; j++){
            if ((j%2)==0){ring.setBrightness(B); ring.show(); delay(50);}
            else if ((j%2)==1){ring.setBrightness(5); ring.show(); delay(50);}  
          }
        } 
        if (transmen=="RIPPLE" && seq=="manual"){ 
         for (int l=0; l<3; l++){
         for (int k=12; 0<k; k--) {
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(j+80, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //INNER RING
          ring.show(); delay(5);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(j+45, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//MIDDLE RING
          ring.show(); delay(5);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<45; j++) { int jj=(3*(j)+startAddress); ring.setPixelColor(j, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//OUTER RING
          ring.show(); delay(5);} 
         } 
        }  
        if (transmen=="SPIRAL" && seq=="manual"){  
          for (int k=0; k<104; k++) {
          for (int j=0; j<104; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+k) % 104)+104) % 104), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}
          ring.show(); delay(7);}
        }
      delay(100); mancount=((((mancount+1)%AROP)+AROP)%AROP);
  
}


void doManualRun() { interrupts(); attachInterrupt(digitalPinToInterrupt(Btn), dobreak3, CHANGE); attachInterrupt(digitalPinToInterrupt(NXT), donext2, CHANGE);
int DIAL0 = analogRead(DIMM); int B=map(DIAL0,0,1023,8,255); ring.setBrightness(B);
  arraynumber=seqlist[mancount]; startAddress = 312*(arraynumber-1); animmen=animlist[mancount]; transmen=translist[mancount]; 
        if (animmen=="NONE"){for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show();} 
        if (animmen=="RANDOM"){  
            if (randomnum==1){animmen="BLINK";}
            if (randomnum==2){animmen="SPARKLE";}
            if (randomnum==3){animmen="SPIN";}
            if (randomnum==4){animmen="RIPPLE";}
            if (randomnum==5){animmen="SPIRAL";}
          }  
        if (animmen=="BLINK"){ 
          for (int p=0; p<2; p++){
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(110);
              for (int i=0; i<TOT; i++){ring.setPixelColor(i, 0);} ring.show(); delay(50);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(110);
              for (int i=0; i<TOT; i++){ring.setPixelColor(i, 0);} ring.show(); delay(50);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); 
          }
        }
        else if (animmen=="SPARKLE"){ 
          //MAKE THE DELAYS EQUAL TO 1000 TOTAL FOR THE TIMING
          for (int p=0; p<7; p++){ int RTOT=16; int TOTALRAND=TOT; int randomarray[RTOT];
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(12);
          for (int i=0; i<RTOT; i++){ randomarray[i]=random(0,TOTALRAND);}
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 0);} ring.show();
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 255-CR,255-CG,255-CB);} ring.show(); delay(12);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], CR, CG, CB);} ring.show(); delay(12);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 255-CR,255-CG,255-CB);} ring.show(); delay(12);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], 0);} ring.show(); delay(12);
          for (int i=0; i<RTOT; i++){ring.setPixelColor(randomarray[i], CR, CG, CB);} ring.show(); delay(12);
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); //delay(44);
          }     
        }
        else if (animmen=="SPIN"){ int pTOT=45;
          for (int p=0; p<pTOT; p++) {
          for (int j=0; j<45; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+p+pTOT) % 45)+45) % 45), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //OUTER RING
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(((((j+p+pTOT) % 35)+35) % 35)+45, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //MIDDLE RING
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(((((j+p+pTOT) % 24)+24) % 24)+80, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);} //INNER RING
          ring.show(); delay(20);
        }
        } 
        else if (animmen=="RIPPLE"){ 
          for (int l=0; l<2; l++){ for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(j, pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}  ring.show(); delay(2);
          for (int k=12; 0<k; k--) {
          for (int j=0; j<24; j++) { int jj=(3*(j+80)+startAddress); ring.setPixelColor(j+80, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //INNER RING
          ring.show(); delay(8);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<35; j++) { int jj=(3*(j+45)+startAddress); ring.setPixelColor(j+45, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//MIDDLE RING
          ring.show(); delay(8);} 
          for (int k=12; 0<k; k--) {
          for (int j=0; j<45; j++) { int jj=(3*(j)+startAddress); ring.setPixelColor(j, pixelsS2[jj]/(3*k+1), pixelsS2[jj+1]/(3*k+1), pixelsS2[jj+2]/(3*k+1));} //ring.show(); delay(10);//OUTER RING
          ring.show(); delay(8);} 
          } 
        } 
        else if (animmen=="SPIRAL" && seq=="manual"){  
          for (int k=0; k<74; k++) {
          for (int j=0; j<TOT; j++) { int jj=(3*j+startAddress); ring.setPixelColor(((((j+k) % 104)+104) % 104), pixelsS2[jj], pixelsS2[jj+1], pixelsS2[jj+2]);}
          ring.show(); delay(8);}
        }
}


void SDtoEEPROM(int address, int pixelsS2[], int arraySize) {
  int addressIndex = startAddress;
    for (int i=0; i<arraySize; i++) { EEPROM.write(addressIndex, pixelsS2[i]); addressIndex++;} 
}


void SEQreadFromEEPROM(int address, int pixelsS1[], int arraySize) {
  int addressIndex = 0;
    for (int i=0; i<arraySize; i++) { pixelsS1[i] = EEPROM.read(addressIndex);  addressIndex++;}
}
