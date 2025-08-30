#include <SoftwareSerial.h>
#include <MorseCodeDevice.h>
#define ROLE_TX 1  // set to 0 on the receiver

#if ROLE_TX
SoftwareSerial link(8, 10); // RX, TX
#else
SoftwareSerial link(11, 7); // RX, TX(unused)
#endif

MorseCodeDevice morse(13, 9);

void setup(){
  Serial.begin(9600); link.begin(9600);
  morse.setTiming(120); morse.setTones(1200,500);
#if ROLE_TX
  Serial.println("SIMPLEX TX: type a line and Enter.");
#else
  Serial.println("SIMPLEX RX: rendering received text as Morse.");
#endif
}
void loop(){
#if ROLE_TX
  if (Serial.available()){ String msg=Serial.readStringUntil('\n'); link.println(msg); Serial.print("[Sent] "); Serial.println(msg); }
#else
  if (link.available()){ String msg=link.readStringUntil('\n'); Serial.print("[Recv] "); Serial.println(msg); msg.toUpperCase(); msg+=" "; morse.sendString(msg.c_str()); }
#endif
}
