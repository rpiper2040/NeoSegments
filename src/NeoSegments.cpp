#include "NeoSegments.h"
#include <string.h>

NeoSegments::NeoSegments(Adafruit_NeoPixel& s, uint8_t pps, uint8_t spd)
  : strip(s), pixelsPerSegment(pps), segmentsPerDigit(spd), digitColor(strip.Color(0, 150, 0)) {}

void NeoSegments::begin() {
  strip.begin();
  strip.show();
  initDigitMap();
}

void NeoSegments::initDigitMap() {
  const uint8_t digits[10][7] = {
    {1,1,1,0,1,1,1}, // 0
    {0,0,1,0,0,0,1}, // 1
    {0,1,1,1,1,1,0}, // 2
    {0,1,1,1,0,1,1}, // 3
    {1,0,1,1,0,0,1}, // 4
    {1,1,0,1,0,1,1}, // 5
    {1,1,0,1,1,1,1}, // 6
    {0,1,1,0,0,0,1}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
  };
  for (uint8_t i = 0; i < 10; i++) {
    memcpy(digitMap[i], digits[i], 7);
    digitChars[i] = '0' + i;
  }
  digitCount = 10;
}

void NeoSegments::setDigitColor(uint32_t color) {
  digitColor = color;
  layoutDirty = true;
}

void NeoSegments::registerSymbol(char symbol, uint8_t length, bool show) {
  if (symbolCount >= MAX_SYMBOLS) return;
  symbols[symbolCount++] = {symbol, length, show};
}

NeoSegments::Symbol* NeoSegments::findSymbol(char c) {
  for (uint8_t i = 0; i < symbolCount; i++) {
    if (symbols[i].character == c) return &symbols[i];
  }
  return nullptr;
}

uint8_t* NeoSegments::findDigitSegments(char c) {
  for (uint8_t i = 0; i < digitCount; i++) {
    if (digitChars[i] == c) return digitMap[i];
  }
  return nullptr;
}

void NeoSegments::setString(const char* str) {
  if (strcmp(lastDisplayed, str) == 0) return;
  strncpy(lastDisplayed, str, MAX_LAYOUT);
  lastDisplayed[MAX_LAYOUT] = '\0';  // Ensure null-termination
  calculateLayout(str);
layoutDirty = true;

  //drawLayout();
}


void NeoSegments::calculateLayout(const char* str) {
  layoutCount = 0;
  uint16_t pixelIndex = 0;

  for (uint8_t i = 0; str[i] != '\0' && layoutCount < MAX_LAYOUT; i++) {
    char c = str[i];
    if (findDigitSegments(c)) {
      layout[layoutCount++] = {true, c, pixelIndex};
      pixelIndex += segmentsPerDigit * pixelsPerSegment;
    } else if (findSymbol(c)) {
      layout[layoutCount++] = {false, c, pixelIndex};
      pixelIndex += findSymbol(c)->length;
    }
  }
}

void NeoSegments::drawLayout() {
  strip.clear();
  for (uint8_t i = 0; i < layoutCount; i++) {
    const Element& e = layout[i];
    if (e.isDigit) drawDigit(e.character, e.startIndex);
    else {
      Symbol* s = findSymbol(e.character);
      if (s) drawSymbol(*s, e.startIndex);
    }
  }
  strip.show();
}

void NeoSegments::drawDigit(char c, uint16_t startIndex) {
  uint8_t* segs = findDigitSegments(c);
  if (!segs) return;

  for (uint8_t s = 0; s < segmentsPerDigit; s++) {
    if (segs[s]) {
      uint16_t segStart = startIndex + s * pixelsPerSegment;
      strip.fill(digitColor, segStart, pixelsPerSegment);
    }
  }
}

void NeoSegments::drawSymbol(const Symbol& sym, uint16_t startIndex) {
  if (!sym.show) return;
  strip.fill(digitColor, startIndex, sym.length);
}

void NeoSegments::update() {
  if (layoutDirty) {
    drawLayout();
    layoutDirty = false;
  }
}

void NeoSegments::clear() {
  strip.clear();
  strip.show();
  layoutCount = 0;
  lastDisplayed[0] = '\0';
}

void NeoSegments::registerDigit(char c, const uint8_t segs[7]) {
  if (digitCount >= MAX_DIGITS) return; // Add a define if not already there
  digitChars[digitCount] = c;
  memcpy(digitMap[digitCount], segs, 7);
  digitCount++;
}

uint32_t NeoSegments::getDigitColor() const {
  return digitColor;
}
