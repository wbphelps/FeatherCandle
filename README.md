# FeatherCandle
Animated candle using Adafruit Feather and Adafruit CharliePlex FeatherWing 15x7 LED array

Clone of Adafruit/FirePendant, modified for the Feather.  Loops a canned animation sequence on the display.

Arduino sketch is comprised of 'FeatherCandle.ino' and 'data7x15.h' -- latter contains animation frames packed into PROGMEM array holding bounding rectangle + column-major pixel data for each frame (consumes most of the flash space on the ATmega328).

The 'frames.zip' archive contains the animation source PNG images and a python script, convert.py, which processes all the source images into the required data.h format. The PNG images were generated via Adobe Premiere and Photoshop from Free Stock Video by user 'dietolog' on Videezy.com.
