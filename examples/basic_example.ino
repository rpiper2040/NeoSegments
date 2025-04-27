//https://wokwi.com/projects/429396736826836993

#include <NeoSegments.h>

#define DATA_PIN 11
#define PIXELS_PER_SEGMENT 6
#define NUMBER_OF_SEGMENTS 6
#define SYMBOL_PIXELS 6
#define NUM_PIXELS (PIXELS_PER_SEGMENT * 7 * NUMBER_OF_SEGMENTS) + SYMBOL_PIXELS  //

Adafruit_NeoPixel strip(NUM_PIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);
NeoSegments segs(strip, PIXELS_PER_SEGMENT);

void setup() {
 Serial.begin(9600);


segs.begin();

// Register two colons for HH:MM:SS format
segs.registerSymbol(':', 2, true);  // colon
segs.registerSymbol(';', 2, false); // hidden colon 
  const uint8_t N_segments[7] = {1,1,1,0,1,0,1};
  const uint8_t E_segments[7] = {1,1,0,1,1,1,0}; 
  const uint8_t O_segments[7] = {1,1,1,0,1,1,1};
  const uint8_t S_segments[7] = {1,1,0,1,0,1,1}; 
  const uint8_t G_segments[7] = {1,1,0,0,1,1,1}; 
  segs.registerDigit('N', N_segments);
  segs.registerDigit('E', E_segments);
  segs.registerDigit('O', O_segments);
  segs.registerDigit('S', S_segments);
  segs.registerDigit('G', G_segments);
}



void loop() {
segs.setDigitColor(strip.Color(255, 0, 0));  
segs.setString("12;34;56");
Serial.println(("set to 12 34 56 in red"));
segs.update();
delay(3000);
segs.setString("56:78:90");
segs.setDigitColor(strip.Color(0, 255, 0));  
Serial.println(("set to 56:78:90 in green"));
segs.update();
delay(3000);
segs.setString("NE;OS;EG");
segs.setDigitColor(strip.Color(0, 0, 255));  
Serial.println(("set to NEOSEG in blue"));
segs.update();
delay(3000);
}
