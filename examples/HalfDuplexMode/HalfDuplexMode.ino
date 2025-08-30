#include <SoftwareSerial.h>
#include <MorseCodeDevice.h>

SoftwareSerial link(11, 10); // RX, TX
MorseCodeDevice morse(13, 9);
const uint8_t PTT_PIN=2;

void setup(){
  Serial.begin(9600); link.begin(9600);
  pinMode(PTT_PIN, INPUT_PULLUP);
  morse.setTiming(120); morse.setTones(1200,500);
  Serial.println("HALF-DUPLEX: Hold button to talk; type to send.");
}
void loop(){
  bool talk = (digitalRead(PTT_PIN)==LOW);
  if (talk){
    if (Serial.available()){ String msg=Serial.readStringUntil('\n'); link.println(msg); Serial.print("[TX] "); Serial.println(msg); }
  } else {
    if (link.available()){ String msg=link.readStringUntil('\n'); Serial.print("[RX] "); Serial.println(msg); msg.toUpperCase(); msg+=" "; morse.sendString(msg.c_str()); }
  }
}
