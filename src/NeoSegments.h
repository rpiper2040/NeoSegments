#ifndef NEOSEGMENTS_H
#define NEOSEGMENTS_H

#include <Adafruit_NeoPixel.h>

#define MAX_SYMBOLS 10
#define MAX_LAYOUT 32
#define MAX_DIGIT_MAP 20
#define MAX_DIGITS 20 

class NeoSegments {
public:
  NeoSegments(Adafruit_NeoPixel& strip, uint8_t pixelsPerSegment, uint8_t segmentsPerDigit = 7);

  void begin();
  void setString(const char* str);
  void update(); // call in loop()
  void registerDigit(char c, const uint8_t segs[7]);

  // Register a symbol, length, blink status, and "show" status (to skip pixels)
  void registerSymbol(char symbol, uint8_t length, bool show = true);
  void setDigitColor(uint32_t color); 
  uint32_t getDigitColor() const;
  void clear();

private:
  bool layoutDirty = false;

  struct Symbol {
    char character;
    uint8_t length;
    bool show;
  };

  struct Element {
    bool isDigit;
    char character;
    uint16_t startIndex;
  };

  Adafruit_NeoPixel& strip;
  uint8_t pixelsPerSegment;
  uint8_t segmentsPerDigit;
  uint32_t digitColor;

  Symbol symbols[MAX_SYMBOLS];
  uint8_t symbolCount = 0;

  Element layout[MAX_LAYOUT];
  uint8_t layoutCount = 0;

  char lastDisplayed[MAX_LAYOUT + 1] = "";

  uint8_t digitMap[MAX_DIGIT_MAP][7];
  char digitChars[MAX_DIGIT_MAP];
  uint8_t digitCount = 0;

  void initDigitMap();
  void calculateLayout(const char* str);
  void drawLayout();
  void drawDigit(char c, uint16_t startIndex);
  void drawSymbol(const Symbol& sym, uint16_t startIndex);
  Symbol* findSymbol(char c);
  uint8_t* findDigitSegments(char c);
};

#endif
