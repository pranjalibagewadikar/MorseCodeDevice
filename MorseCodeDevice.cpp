#include "MorseCodeDevice.h"

MorseCodeDevice::MorseCodeDevice(uint8_t ledPin, uint8_t buzzerPin)
: _ledPin(ledPin), _buzzerPin(buzzerPin), _dotTime(120) {
  pinMode(_ledPin, OUTPUT);
  if (_buzzerPin != 255) {
    pinMode(_buzzerPin, OUTPUT);
    digitalWrite(_buzzerPin, LOW);
  }
  digitalWrite(_ledPin, LOW);
}

void MorseCodeDevice::setTiming(unsigned int dotTimeMs) {
  _dotTime = dotTimeMs;
}

void MorseCodeDevice::setTones(uint16_t dotHz, uint16_t dashHz) {
  _toneDotHz = dotHz;
  _toneDashHz = dashHz;
}

void MorseCodeDevice::_mark(unsigned long ms, uint16_t freq) {
  digitalWrite(_ledPin, HIGH);
  if (_buzzerPin != 255) {
    tone(_buzzerPin, freq);
  }
  delay(ms);
  digitalWrite(_ledPin, LOW);
  if (_buzzerPin != 255) {
    noTone(_buzzerPin);
  }
}

void MorseCodeDevice::_gap(unsigned long ms) {
  delay(ms);
}

void MorseCodeDevice::sendDot() {
  _mark(_dotTime, _toneDotHz);
  _gap(_dotTime); // intra-character space (1 unit)
}

void MorseCodeDevice::sendDash() {
  _mark(_dotTime * 3UL, _toneDashHz);
  _gap(_dotTime); // intra-character space (1 unit)
}

void MorseCodeDevice::sendChar(char c) {
  if (c == ' ') {
    _gap(_dotTime * 7UL); // word gap
    return;
  }
  const char* patt = charToMorse(c);
  if (!patt) return;
  for (const char* p = patt; *p; ++p) {
    if (*p == '.') sendDot();
    else if (*p == '-') sendDash();
  }
  _gap(_dotTime * 2UL); // add extra 2 units to complete 3-unit letter gap
}

void MorseCodeDevice::sendString(const char* s) {
  if (!s) return;
  while (*s) { sendChar(*s++); }
}

const char* MorseCodeDevice::charToMorse(char c) {
  c = toupper(c);
  switch (c) {
    case 'A': return ".-";   case 'B': return "-..."; case 'C': return "-.-.";
    case 'D': return "-..";  case 'E': return ".";    case 'F': return "..-.";
    case 'G': return "--.";  case 'H': return "...."; case 'I': return "..";
    case 'J': return ".---"; case 'K': return "-.-";  case 'L': return ".-..";
    case 'M': return "--";   case 'N': return "-.";   case 'O': return "---";
    case 'P': return ".--."; case 'Q': return "--.-"; case 'R': return ".-.";
    case 'S': return "...";  case 'T': return "-";    case 'U': return "..-";
    case 'V': return "...-"; case 'W': return ".--";  case 'X': return "-..-";
    case 'Y': return "-.--"; case 'Z': return "--..";
    case '0': return "-----"; case '1': return ".----"; case '2': return "..---";
    case '3': return "...--"; case '4': return "....-"; case '5': return ".....";
    case '6': return "-...."; case '7': return "--..."; case '8': return "---..";
    case '9': return "----.";
    case ' ': return " ";
    default:  return nullptr;
  }
}

char MorseCodeDevice::morseToChar(const char* pattern) {
  if (!pattern) return '_';
  if (!strcmp(pattern, ".-"))   return 'A';
  if (!strcmp(pattern, "-...")) return 'B';
  if (!strcmp(pattern, "-.-.")) return 'C';
  if (!strcmp(pattern, "-.."))  return 'D';
  if (!strcmp(pattern, "."))    return 'E';
  if (!strcmp(pattern, "..-.")) return 'F';
  if (!strcmp(pattern, "--."))  return 'G';
  if (!strcmp(pattern, "....")) return 'H';
  if (!strcmp(pattern, ".."))   return 'I';
  if (!strcmp(pattern, ".---")) return 'J';
  if (!strcmp(pattern, "-.-"))  return 'K';
  if (!strcmp(pattern, ".-..")) return 'L';
  if (!strcmp(pattern, "--"))   return 'M';
  if (!strcmp(pattern, "-."))   return 'N';
  if (!strcmp(pattern, "---"))  return 'O';
  if (!strcmp(pattern, ".--.")) return 'P';
  if (!strcmp(pattern, "--.-")) return 'Q';
  if (!strcmp(pattern, ".-."))  return 'R';
  if (!strcmp(pattern, "..."))  return 'S';
  if (!strcmp(pattern, "-"))    return 'T';
  if (!strcmp(pattern, "..-"))  return 'U';
  if (!strcmp(pattern, "...-")) return 'V';
  if (!strcmp(pattern, ".--"))  return 'W';
  if (!strcmp(pattern, "-..-")) return 'X';
  if (!strcmp(pattern, "-.--")) return 'Y';
  if (!strcmp(pattern, "--..")) return 'Z';
  if (!strcmp(pattern, "-----")) return '0';
  if (!strcmp(pattern, ".----")) return '1';
  if (!strcmp(pattern, "..---")) return '2';
  if (!strcmp(pattern, "...--")) return '3';
  if (!strcmp(pattern, "....-")) return '4';
  if (!strcmp(pattern, ".....")) return '5';
  if (!strcmp(pattern, "-....")) return '6';
  if (!strcmp(pattern, "--...")) return '7';
  if (!strcmp(pattern, "---..")) return '8';
  if (!strcmp(pattern, "----.")) return '9';
  return '_';
}
