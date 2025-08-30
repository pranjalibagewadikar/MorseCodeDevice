#include <MorseCodeDevice.h>
MorseCodeDevice morse(13, 9); // LED=13, buzzer=9
void setup(){ morse.setTiming(100); morse.setTones(1200, 500); }
void loop(){ morse.sendString("MORSE CODE "); delay(2500); }
