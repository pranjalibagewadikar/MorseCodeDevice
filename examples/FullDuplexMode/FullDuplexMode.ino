#include <SoftwareSerial.h>
#include <MorseCodeDevice.h>

SoftwareSerial linkAB(13,10); // RX, TX
SoftwareSerial linkBA(11,12); // RX, TX
MorseCodeDevice morse(13,9);

unsigned long lastListenSwitch=0; const unsigned long listenWindow=20;

void setup(){
  Serial.begin(9600); linkAB.begin(9600); linkBA.begin(9600);
  morse.setTiming(120); morse.setTones(1200,500);
  Serial.println("FULL-DUPLEX demo (time-sliced): type to send.");
}
void loop(){
  if (millis()-lastListenSwitch>listenWindow){
    static bool ab=true; ab=!ab; if (ab) linkAB.listen(); else linkBA.listen(); lastListenSwitch=millis();
  }
  if (Serial.available()){ String msg=Serial.readStringUntil('\n'); linkAB.println(msg); Serial.print("[TX] "); Serial.println(msg); }
  if (linkAB.available()){ String msg=linkAB.readStringUntil('\n'); Serial.print("[RX AB] "); Serial.println(msg); msg.toUpperCase(); msg+=" "; morse.sendString(msg.c_str()); }
  if (linkBA.available()){ String msg=linkBA.readStringUntil('\n'); Serial.print("[RX BA] "); Serial.println(msg); msg.toUpperCase(); msg+=" "; morse.sendString(msg.c_str()); }
}
