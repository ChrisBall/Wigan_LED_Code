/* 
 *  connect your leds to pin 11
 *  connect your touchpad to pin A0
 */

#include <ADCTouch.h>
#include <FastLED.h>

#define NUM_LEDS 21   //how many LEDs are you using?
#define DATA_PIN 11   //what data pin is being used?

CRGB leds[NUM_LEDS];  // Define the array of leds

int ref0;   //used to keep track of the touchpad state

void setup() {
  Serial.begin(115200);  //begin serial over USB communication (for troubleshooting)
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); //initialise the LEDs
  ref0 = ADCTouch.read(A0, 500);   //initialise the touchpad (read the current state). We have to assume it's not being touched on startup.
}

void loop() {
  int value0 = ADCTouch.read(A0, 10);  //read the touch pad
  value0 -= ref0;       //remove offset (we got this value in setup)
  Serial.println(value0);  //print it (for troubleshooting)

  //Random colour "twinkling" effect
  for (int i = 0; i < NUM_LEDS; i++) {   //for all the leds
    if (random(100) == 0 && value0>3) {  //we generate a random number from 0-100. If it's 0, AND the touchpad is being touched
      leds[i] = CRGB(random(0,10+value0*8), random(10, 10+value0*8), random(10, 10+value0*8)); //set that LED to a random colour
    }
    leds[i].fadeToBlackBy(1);  //fade all the LEDs gradually.
  }
  FastLED.show();  //send the data to the LEDs
}
