#include <MorseCodeDevice.h>
MorseCodeDevice morse(13, 9);
const uint8_t BUTTON_PIN = 2;
const unsigned long doubleWindow = 400;
const unsigned long charGap = 1200;

char pattern[8]; uint8_t pattIdx = 0;
int lastButton = HIGH; unsigned long lastPressTime=0, lastActivity=0; bool waitingSecondPress=false;

void resetPattern(){ pattIdx=0; pattern[0]='\0'; }
void appendSymbol(char s){ if(pattIdx<sizeof(pattern)-1){ pattern[pattIdx++]=s; pattern[pattIdx]='\0'; } }

void setup(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  morse.setTiming(120); morse.setTones(1200,500);
  Serial.println("Single press = DOT, double press = DASH");
}
void loop(){
  int b = digitalRead(BUTTON_PIN);
  if (lastButton==HIGH && b==LOW){
    unsigned long now=millis();
    if (waitingSecondPress && (now-lastPressTime)<=doubleWindow){
      appendSymbol('-'); Serial.print("-"); morse.sendDash(); waitingSecondPress=false;
    } else { waitingSecondPress=true; lastPressTime=now; }
    lastActivity=now;
  }
  if (waitingSecondPress && (millis()-lastPressTime)>doubleWindow){
    appendSymbol('.'); Serial.print("."); morse.sendDot(); waitingSecondPress=false; lastActivity=millis();
  }
  if (pattIdx>0 && (millis()-lastActivity)>charGap){
    char c = MorseCodeDevice::morseToChar(pattern);
    Serial.print(" => "); Serial.println(c);
    resetPattern();
  }
  lastButton=b;
}
