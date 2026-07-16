#include <FastLED.h>

#define NUM_LEDS 104

CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> led_array;

UISlider hueSlider("Hue", 128, 0, 255, 1);
UISlider saturationSlider("Saturation", 255, 0, 255, 1);
UISlider valueSlider("Value", 255, 0, 255, 1);
UICheckbox autoHue("Auto Hue", true);

// Group related HSV control UI elements using UIGroup template multi-argument constructor
UIGroup hsvControls("HSV Controls", hueSlider, saturationSlider, valueSlider, autoHue);

#define LED_PIN_1    34
#define LED_PIN_2    31
#define LED_PIN_3    32
#define LED_PIN_4    33
#define LED_PIN_5    29
#define LED_PIN_6    30
#define LED_PIN_7    37
#define LED_PIN_8    35
#define LED_PIN_9    36
#define LED_PIN_10    38
#define LED_PIN_11    39
#define LED_PIN_12    40

void setup() { 
    FastLED.addLeds<NEOPIXEL,LED_PIN_1>(leds, NUM_LEDS); 
}

void loop(){ 
  static uint8_t hue;
  for(int i = 0; i < NUM_LEDS/2; i++) {   
    // fade everything out
    led_array.fadeToBlackBy(40);

    // let's set an led value
    led_array[i] = CHSV(hue++,255,255);

    // now, let's first 20 leds to the top 20 leds, 
    led_array(NUM_LEDS/2,NUM_LEDS-1) = led_array(NUM_LEDS/2 - 1 ,0);
    // FastLED.delay(FASTLED_TESTING);
  }
}