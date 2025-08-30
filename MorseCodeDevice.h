#ifndef MORSE_CODE_DEVICE_H
#define MORSE_CODE_DEVICE_H

#include <Arduino.h>

class MorseCodeDevice {
  public:
    // buzzerPin = 255 means "no buzzer"
    MorseCodeDevice(uint8_t ledPin, uint8_t buzzerPin = 255);

    void setTiming(unsigned int dotTimeMs = 120); // Base time unit (ms)
    void setTones(uint16_t dotHz, uint16_t dashHz); // Different tones for dot/dash

    // Low-level sends
    void sendDot();
    void sendDash();

    // High-level helpers
    void sendChar(char c);
    void sendString(const char* s);

    // Utility mappers
    static const char* charToMorse(char c);      // returns "." / "-"
    static char morseToChar(const char* pattern);// returns 'A'..'Z','0'..'9' or '_'

    unsigned int dotTime() const { return _dotTime; }

  private:
    uint8_t _ledPin;
    uint8_t _buzzerPin;
    unsigned int _dotTime;
    uint16_t _toneDotHz = 1000;
    uint16_t _toneDashHz = 500;

    void _mark(unsigned long ms, uint16_t freq);
    void _gap(unsigned long ms);
};

#endif
