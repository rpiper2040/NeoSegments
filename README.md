# NeoSegments

**NeoSegments** is a lightweight Arduino extension library built on top of Adafruit NeoPixel for controlling **NeoPixel** strips as if they were a seven-segment display. It allows you to easily display digits and symbols on a NeoPixel strip, giving you the flexibility to create custom numeric displays, timers, clocks, or other projects requiring segmented displays.

## Features
- Control a NeoPixel strip like a seven-segment display.
- Customizable colors.
- Supports up to **32 elements** (digits or symbols) in the display layout.
- Register custom symbols and characters to display.
- Works with any NeoPixel-compatible LED strip.


## Hardware Layout

Each digit is built from 7 segments (groups of NeoPixels), laid out similar to a classic seven-segment display.
Data flows from the MCU into the first segment (1), and continues through the others in order.
 ```
           222
         1     3
         1     3
   IN -> 1     3
           444
         5     7 -> OUT
         5     7 
         5     7
           666
```
![Hardware Diagram](https://github.com/rpiper2040/NeoSegments/blob/357352562298e80c602e7452cf131e54e2bf7460/NeoSegment_hardware.png)



## Dependencies
This library depends on the [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel), which must be installed separately.

## Installation

1. **Via Arduino Library Manager:**

   - Open the Arduino IDE.
   - Go to **Sketch** → **Include Library** → **Manage Libraries**.
   - In the Library Manager, search for **NeoSegments**.
   - Click **Install**.

2. **Manual Installation:**

   - Download or clone this repository.
   - Copy the entire `NeoSegments` folder into your Arduino libraries folder. This is usually located in:
     - **Windows**: `Documents/Arduino/libraries/`
     - **macOS/Linux**: `~/Documents/Arduino/libraries/`
   - Restart the Arduino IDE to use the library.

3. **Install Adafruit NeoPixel Library:**
   - In the Arduino IDE, go to **Sketch** → **Include Library** → **Manage Libraries**.
   - Search for **Adafruit NeoPixel** and install it.

## Usage

Here is an example sketch that demonstrates how to use the **NeoSegments** library:

### Example

```cpp
#include "NeoSegments.h"

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
```
### Functions

- `NeoSegments(Adafruit_NeoPixel& strip, uint8_t pixelsPerSegment, uint8_t segmentsPerDigit = 7)`  
  Initializes the display.
- `begin()`  
  Starts the LED strip and builds the digit map.
- `setString(const char* str)`  
  Queues up a new string to display.
- `update()`  
  Sends data to the LED strip; call this each loop.
- `setDigitColor(uint32_t color)`  
  Changes the color of all digits.
- `clear()`  
  Clears the display.
- `registerSymbol(char symbol, uint8_t length, bool show = true)`  
  Defines a custom symbol length.
- `registerDigit(char c, const uint8_t segs[7])`  
  Adds a custom 7-segment pattern.

## License

This library is licensed under the [MIT License](LICENSE).  
It uses the [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel), which is also licensed under the MIT License.

## Contributions

If you'd like to contribute to this library, feel free to open an issue or submit a pull request. Please make sure to follow the coding standards and include tests for any new features or bug fixes.

## Acknowledgments
- Thanks to the team at [Adafruit](https://www.adafruit.com/) for the **Adafruit NeoPixel Library**.
- Thanks to [Arduino](https://www.arduino.cc/) for providing the platform for makers and developers.
