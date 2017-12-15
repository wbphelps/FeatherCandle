#include <Adafruit_IS31FL3731.h>
#include "data7x15.h"           // Flame animation data

// using the FeatherWing version
Adafruit_IS31FL3731_Wing leds = Adafruit_IS31FL3731_Wing();

uint8_t        page = 0;    // Front/back buffer control
const uint8_t *ptr  = anim; // Current pointer into animation data
const uint8_t  w    = 7;    // image width
const uint8_t  h    = 15;   // image height
uint8_t        img[w*h]; // Buffer for rendering image

void setup() {
//  Serial.begin(9600);
//  Serial.println("Feather Candle");

  if (! leds.begin()) {
//    Serial.println("IS31 not found");
    while (1);
  }
}

void loop() {
  uint8_t  a, x1, y1, x2, y2, x, y;

  // read NEXT frame.  Start by getting bounding rect for new frame:
  a = pgm_read_byte(ptr++);     // New frame X1/Y1
  if(a >= 0x90) {               // EOD marker? (valid X1 never exceeds 8)
    ptr = anim;                 // Reset animation data pointer to start
    a   = pgm_read_byte(ptr++); // and take first value
  }
  x1 = a >> 4;                  // X1 = high 4 bits
  y1 = a & 0x0F;                // Y1 = low 4 bits
  a  = pgm_read_byte(ptr++);    // New frame X2/Y2
  x2 = a >> 4;                  // X2 = high 4 bits
  y2 = a & 0x0F;                // Y2 = low 4 bits

  // Read rectangle of data from anim[] into portion of img[] buffer
  for(uint8_t y=y1; y<=y2; y++)
    for(uint8_t x=x1; x<=x2; x++) { 
      img[y*w + x] = pgm_read_byte(ptr++);
  }

  page ^= 1; // Flip front/back buffer index
  leds.setFrame(page);

  int i = 0;
  for (uint8_t x=0; x<h; x++) {
    for (uint8_t y=0; y<w; y++) {
      leds.drawPixel(x, y, img[i++]);  
    }
  }

  leds.displayFrame(page);
}
