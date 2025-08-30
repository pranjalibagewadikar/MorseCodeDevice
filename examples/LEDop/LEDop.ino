#include <MorseCodeDevice.h>
MorseCodeDevice morse(13); // LED only
void setup(){ morse.setTiming(120); }
void loop(){ morse.sendString("HELLO WORLD "); delay(2000); }
