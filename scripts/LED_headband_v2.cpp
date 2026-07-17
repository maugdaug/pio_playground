#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


AudioInputI2S               i2s1;
AudioOutputI2S              i2s2; 
AudioSynthWaveformSine      sinewave;
AudioAnalyzeFFT1024         fft1024;
AudioMixer4                 mixer1;
AudioConnection             patchCord1(i2s1, 0, mixer1, 0);
AudioConnection             patchCord3(i2s1, 1, mixer1, 1);
AudioConnection             patchCord5(mixer1, fft1024);
AudioConnection             patchCord6(mixer1, 0, i2s2, 0);
AudioConnection             patchCord4(mixer1, 0, i2s2, 1);
AudioControlSGTL5000        audioShield;


// const int myInput = AUDIO_INPUT_LINEIN;
int step = 1000;
const int myInput = AUDIO_INPUT_MIC;
uint8_t brightness = 5;

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

#define LED_COUNT 104

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(LED_COUNT, LED_PIN_5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(LED_COUNT, LED_PIN_6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7(LED_COUNT, LED_PIN_7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8(LED_COUNT, LED_PIN_8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9(LED_COUNT, LED_PIN_9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10(LED_COUNT, LED_PIN_10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11(LED_COUNT, LED_PIN_11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip12(LED_COUNT, LED_PIN_12, NEO_GRB + NEO_KHZ800);

float fft_gain = 10;
float scale = 60.0;
float levels26[26];
int   on_off_array[12][26];


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip1.numPixels(); i++) { // For each pixel in strip...
    uint32_t time1 = micros();

    strip1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.setPixelColor(i, color);
    strip3.setPixelColor(i, color);
    strip4.setPixelColor(i, color);
    strip5.setPixelColor(i, color);
    strip6.setPixelColor(i, color);
    strip7.setPixelColor(i, color);
    strip8.setPixelColor(i, color);
    strip9.setPixelColor(i, color);
    strip10.setPixelColor(i, color);
    strip11.setPixelColor(i, color);
    strip12.setPixelColor(i, color);

    strip1.show();                          //  Update strip to match
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
    strip12.show();

    uint32_t time2 = micros();
    
    Serial.println(time2 - time1);

    // delay(wait);                           //  Pause for a moment
  }
}


void rainbow(int wait) {
    

    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
        uint32_t time1 = micros();

        strip1.rainbow(firstPixelHue);
        strip2.rainbow(firstPixelHue + 2 * step);
        strip3.rainbow(firstPixelHue + 3 * step);
        strip4.rainbow(firstPixelHue + 4 * step);
        strip5.rainbow(firstPixelHue + 5 * step);
        strip6.rainbow(firstPixelHue + 6 * step);
        strip7.rainbow(firstPixelHue + 7 * step);
        strip8.rainbow(firstPixelHue + 8 * step);
        strip9.rainbow(firstPixelHue + 9 * step);
        strip10.rainbow(firstPixelHue + 10 * step);
        strip11.rainbow(firstPixelHue + 11 * step);
        strip12.rainbow(firstPixelHue + 12 * step);

        strip1.show();                          //  Update strip to match
        strip2.show();
        strip3.show();
        strip4.show();
        strip5.show();
        strip6.show();
        strip7.show();
        strip8.show();
        strip9.show();
        strip10.show();
        strip11.show();
        strip12.show();
        // delay(wait);  // Pause for a moment

        uint32_t time2 = micros();
    
        Serial.println(time2 - time1);
    }

    
}


void handleFFT() {
    if (fft1024.available()) {
        levels26[0] =  fft1024.read(0,2);
        levels26[1] =  fft1024.read(2,2);
        levels26[2] =  fft1024.read(3,3);
        levels26[3] =  fft1024.read(4,4);
        levels26[4] =  fft1024.read(5,5);
        levels26[5] =  fft1024.read(6,6);
        levels26[6] =  fft1024.read(7,7);
        levels26[7] =  fft1024.read(8,9);
        levels26[8] =  fft1024.read(10,11);
        levels26[9] =  fft1024.read(12,14);

        levels26[10] =  fft1024.read(15,17);
        levels26[11] =  fft1024.read(18,21);
        levels26[12] =  fft1024.read(22,25);
        levels26[13] =  fft1024.read(26,30);
        levels26[14] =  fft1024.read(31,35);
        levels26[15] =  fft1024.read(36,42);
        levels26[16] =  fft1024.read(43,51);
        levels26[17] =  fft1024.read(52,63);
        levels26[18] =  fft1024.read(64,78);
        levels26[19] =  fft1024.read(79,98);

        levels26[20] =  fft1024.read(99,122);
        levels26[21] =  fft1024.read(123,148);
        levels26[22] =  fft1024.read(149,178);
        levels26[23] =  fft1024.read(179,224);
        levels26[24] =  fft1024.read(225,284);
        levels26[25] =  fft1024.read(285,355);

        for (int i=0; i < 26; i++) {
            levels26[i] -= 0.1;
            if (levels26[i]<0) levels26[i]=0;
            levels26[i] *= fft_gain;
            // levels26[i] = log(5*levels26[i]+1);
            levels26[i] = pow(levels26[i],1.6);
        }

        // if you have the volume pot soldered to your audio shield
        // uncomment this line to make it adjust the full scale signal
        //scale = 8.0 + analogRead(A1) / 5.0;

        // for(int i=0;i<26;i++) {
        //     Serial.print(levels26[i]);
        //     Serial.print(" ");
// loop() function -- runs repeatedly as long as board is on ---------------
        // }
        // Serial.println();
    }
}


void handleOnOffArray() {
    for (int i=0; i<26; i++) {
        for (int j=0; j<12; j++) {
            on_off_array[j][i] = 0;
        }
    }

    // switch case with ints
    for (int i=0; i<26; i++) {
        if (levels26[i]>12) {
            for (int j=0; j<12; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>11) {
            for (int j=0; j<11; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>10) {
            for (int j=0; j<10; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>9) {
            for (int j=0; j<9; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>8) {
            for (int j=0; j<8; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>7) {
            for (int j=0; j<7; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>6) {
            for (int j=0; j<6; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>5) {
            for (int j=0; j<5; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>4) {
            for (int j=0; j<4; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>3) {
            for (int j=0; j<3; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>2) {
            for (int j=0; j<2; j++) {
                on_off_array[j][i] = 1;
            }
        }
        else if (levels26[i]>1) {
            for (int j=0; j<1; j++) {
                on_off_array[j][i] = 1;
            }
        }
    }
}

void printOnOffArray() {
    Serial.print("\n\t0");
    for (int n=1; n<3; n++) {
        Serial.print(" . . . . . . . . . ");
        Serial.print(n);
    }
    Serial.println();

    for (int j=11; j>=0; j--) {
        Serial.print(j);
        Serial.print("\t");

        for (int i=0; i<26; i++) {
            Serial.print(on_off_array[j][i]);
            Serial.print(" ");
        }
        Serial.println();
    }

    delay(50);
}


void test_display() {
    // uint32_t time1 = micros();

    for (int i=0; i<=25; i++) {
        strip1.setPixelColor(i, strip1.Color(on_off_array[0][25-i]*50, 0, 0));
        strip2.setPixelColor(i, strip1.Color(on_off_array[1][25-i]*50, 0, 0));
        strip3.setPixelColor(i, strip1.Color(on_off_array[2][25-i]*50, 0, 0));
        strip4.setPixelColor(i, strip1.Color(on_off_array[3][25-i]*50, 0, 0));
        strip5.setPixelColor(i, strip1.Color(on_off_array[4][25-i]*50, 0, 0));
        strip6.setPixelColor(i, strip1.Color(on_off_array[5][25-i]*50, 0, 0));
        strip7.setPixelColor(i, strip1.Color(on_off_array[6][25-i]*50, 0, 0));
        strip8.setPixelColor(i, strip1.Color(on_off_array[7][25-i]*50, 0, 0));
        strip9.setPixelColor(i, strip1.Color(on_off_array[8][25-i]*50, 0, 0));
        strip10.setPixelColor(i, strip1.Color(on_off_array[9][25-i]*50, 0, 0));
        strip11.setPixelColor(i, strip1.Color(on_off_array[10][25-i]*50, 0, 0));
        strip12.setPixelColor(i, strip1.Color(on_off_array[11][25-i]*50, 0, 0));

        strip1.setPixelColor(26+i, strip1.Color(on_off_array[0][i]*50, 0, 0));
        strip2.setPixelColor(26+i, strip1.Color(on_off_array[1][i]*50, 0, 0));
        strip3.setPixelColor(26+i, strip1.Color(on_off_array[2][i]*50, 0, 0));
        strip4.setPixelColor(26+i, strip1.Color(on_off_array[3][i]*50, 0, 0));
        strip5.setPixelColor(26+i, strip1.Color(on_off_array[4][i]*50, 0, 0));
        strip6.setPixelColor(26+i, strip1.Color(on_off_array[5][i]*50, 0, 0));
        strip7.setPixelColor(26+i, strip1.Color(on_off_array[6][i]*50, 0, 0));
        strip8.setPixelColor(26+i, strip1.Color(on_off_array[7][i]*50, 0, 0));
        strip9.setPixelColor(26+i, strip1.Color(on_off_array[8][i]*50, 0, 0));
        strip10.setPixelColor(26+i, strip1.Color(on_off_array[9][i]*50, 0, 0));
        strip11.setPixelColor(26+i, strip1.Color(on_off_array[10][i]*50, 0, 0));
        strip12.setPixelColor(26+i, strip1.Color(on_off_array[11][i]*50, 0, 0));

        strip1.setPixelColor(52+i, strip1.Color(on_off_array[0][25-i]*50, 0, 0));
        strip2.setPixelColor(52+i, strip1.Color(on_off_array[1][25-i]*50, 0, 0));
        strip3.setPixelColor(52+i, strip1.Color(on_off_array[2][25-i]*50, 0, 0));
        strip4.setPixelColor(52+i, strip1.Color(on_off_array[3][25-i]*50, 0, 0));
        strip5.setPixelColor(52+i, strip1.Color(on_off_array[4][25-i]*50, 0, 0));
        strip6.setPixelColor(52+i, strip1.Color(on_off_array[5][25-i]*50, 0, 0));
        strip7.setPixelColor(52+i, strip1.Color(on_off_array[6][25-i]*50, 0, 0));
        strip8.setPixelColor(52+i, strip1.Color(on_off_array[7][25-i]*50, 0, 0));
        strip9.setPixelColor(52+i, strip1.Color(on_off_array[8][25-i]*50, 0, 0));
        strip10.setPixelColor(52+i, strip1.Color(on_off_array[9][25-i]*50, 0, 0));
        strip11.setPixelColor(52+i, strip1.Color(on_off_array[10][25-i]*50, 0, 0));
        strip12.setPixelColor(52+i, strip1.Color(on_off_array[11][25-i]*50, 0, 0));

        strip1.setPixelColor(78+i, strip1.Color(on_off_array[0][i]*50, 0, 0));
        strip2.setPixelColor(78+i, strip1.Color(on_off_array[1][i]*50, 0, 0));
        strip3.setPixelColor(78+i, strip1.Color(on_off_array[2][i]*50, 0, 0));
        strip4.setPixelColor(78+i, strip1.Color(on_off_array[3][i]*50, 0, 0));
        strip5.setPixelColor(78+i, strip1.Color(on_off_array[4][i]*50, 0, 0));
        strip6.setPixelColor(78+i, strip1.Color(on_off_array[5][i]*50, 0, 0));
        strip7.setPixelColor(78+i, strip1.Color(on_off_array[6][i]*50, 0, 0));
        strip8.setPixelColor(78+i, strip1.Color(on_off_array[7][i]*50, 0, 0));
        strip9.setPixelColor(78+i, strip1.Color(on_off_array[8][i]*50, 0, 0));
        strip10.setPixelColor(78+i, strip1.Color(on_off_array[9][i]*50, 0, 0));
        strip11.setPixelColor(78+i, strip1.Color(on_off_array[10][i]*50, 0, 0));
        strip12.setPixelColor(78+i, strip1.Color(on_off_array[11][i]*50, 0, 0));


        // strip1.setPixelColor(51-i, strip1.Color(on_off_array[0][i]*50, 0, 0));
        // strip2.setPixelColor(51-i, strip1.Color(on_off_array[1][i]*50, 0, 0));
        // strip3.setPixelColor(51-i, strip1.Color(on_off_array[2][i]*50, 0, 0));
        // strip4.setPixelColor(51-i, strip1.Color(on_off_array[3][i]*50, 0, 0));
        // strip5.setPixelColor(51-i, strip1.Color(on_off_array[4][i]*50, 0, 0));
        // strip6.setPixelColor(51-i, strip1.Color(on_off_array[5][i]*50, 0, 0));
        // strip7.setPixelColor(51-i, strip1.Color(on_off_array[6][i]*50, 0, 0));
        // strip8.setPixelColor(51-i, strip1.Color(on_off_array[7][i]*50, 0, 0));
        // strip9.setPixelColor(51-i, strip1.Color(on_off_array[8][i]*50, 0, 0));
        // strip10.setPixelColor(51-i, strip1.Color(on_off_array[9][i]*50, 0, 0));
        // strip11.setPixelColor(51-i, strip1.Color(on_off_array[10][i]*50, 0, 0));
        // strip12.setPixelColor(51-i, strip1.Color(on_off_array[11][i]*50, 0, 0));

        // strip1.setPixelColor(52+i, strip1.Color(on_off_array[0][i]*50, 0, 0));
        // strip2.setPixelColor(52+i, strip1.Color(on_off_array[1][i]*50, 0, 0));
        // strip3.setPixelColor(52+i, strip1.Color(on_off_array[2][i]*50, 0, 0));
        // strip4.setPixelColor(52+i, strip1.Color(on_off_array[3][i]*50, 0, 0));
        // strip5.setPixelColor(52+i, strip1.Color(on_off_array[4][i]*50, 0, 0));
        // strip6.setPixelColor(52+i, strip1.Color(on_off_array[5][i]*50, 0, 0));
        // strip7.setPixelColor(52+i, strip1.Color(on_off_array[6][i]*50, 0, 0));
        // strip8.setPixelColor(52+i, strip1.Color(on_off_array[7][i]*50, 0, 0));
        // strip9.setPixelColor(52+i, strip1.Color(on_off_array[8][i]*50, 0, 0));
        // strip10.setPixelColor(52+i, strip1.Color(on_off_array[9][i]*50, 0, 0));
        // strip11.setPixelColor(52+i, strip1.Color(on_off_array[10][i]*50, 0, 0));
        // strip12.setPixelColor(52+i, strip1.Color(on_off_array[11][i]*50, 0, 0));

        // strip1.setPixelColor(103-i, strip1.Color(on_off_array[0][i]*50, 0, 0));
        // strip2.setPixelColor(103-i, strip1.Color(on_off_array[1][i]*50, 0, 0));
        // strip3.setPixelColor(103-i, strip1.Color(on_off_array[2][i]*50, 0, 0));
        // strip4.setPixelColor(103-i, strip1.Color(on_off_array[3][i]*50, 0, 0));
        // strip5.setPixelColor(103-i, strip1.Color(on_off_array[4][i]*50, 0, 0));
        // strip6.setPixelColor(103-i, strip1.Color(on_off_array[5][i]*50, 0, 0));
        // strip7.setPixelColor(103-i, strip1.Color(on_off_array[6][i]*50, 0, 0));
        // strip8.setPixelColor(103-i, strip1.Color(on_off_array[7][i]*50, 0, 0));
        // strip9.setPixelColor(103-i, strip1.Color(on_off_array[8][i]*50, 0, 0));
        // strip10.setPixelColor(103-i, strip1.Color(on_off_array[9][i]*50, 0, 0));
        // strip11.setPixelColor(103-i, strip1.Color(on_off_array[10][i]*50, 0, 0));
        // strip12.setPixelColor(103-i, strip1.Color(on_off_array[11][i]*50, 0, 0));
    }


    strip1.show();   
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
    strip12.show();

    // uint32_t time2 = micros();

    // Serial.print(time2 - time1);
    // Serial.println();
    // delay(100);
}

void LEDsOff() {
    for (int i=104; i>=0; i--) {
        strip1.setPixelColor(i, strip1.Color(0, 0, 0));
        strip2.setPixelColor(i, strip1.Color(0, 0, 0));
        strip3.setPixelColor(i, strip1.Color(0, 0, 0));
        strip4.setPixelColor(i, strip1.Color(0, 0, 0));
        strip5.setPixelColor(i, strip1.Color(0, 0, 0));
        strip6.setPixelColor(i, strip1.Color(0, 0, 0));
        strip7.setPixelColor(i, strip1.Color(0, 0, 0));
        strip8.setPixelColor(i, strip1.Color(0, 0, 0));
        strip9.setPixelColor(i, strip1.Color(0, 0, 0));
        strip10.setPixelColor(i, strip1.Color(0, 0, 0));
        strip11.setPixelColor(i, strip1.Color(0, 0, 0));
        strip12.setPixelColor(i, strip1.Color(0, 0, 0));
    }

    strip1.show();   
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();
    strip11.show();
    strip12.show();
}


void setup() {
    Serial.begin(115200);

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(12);

    // Enable the audio shield and set the output volume.
    audioShield.enable();
    audioShield.inputSelect(myInput);
    audioShield.volume(0.5);

    // Configure the window algorithm to use
    fft1024.windowFunction(AudioWindowHanning1024);

      // configure the mixer to equally add left & right
    mixer1.gain(0, 0.5);
    mixer1.gain(1, 0.5);

    strip1.begin();                          //  Update strip to match
    strip2.begin();
    strip3.begin();
    strip4.begin();
    strip5.begin();
    strip6.begin();
    strip7.begin();
    strip8.begin();
    strip9.begin();
    strip10.begin();
    strip11.begin();
    strip12.begin();

    delay(100);
    void LEDsOff();

    strip2.setBrightness(brightness);
    strip1.setBrightness(brightness);                          //  Update strip to match
    strip3.setBrightness(brightness);
    strip4.setBrightness(brightness);
    strip5.setBrightness(brightness);
    strip6.setBrightness(brightness);
    strip7.setBrightness(brightness);
    strip8.setBrightness(brightness);
    strip9.setBrightness(brightness);
    strip10.setBrightness(brightness);
    strip11.setBrightness(brightness);
    strip12.setBrightness(brightness);
}



void loop() {
//   colorWipe(strip1.Color(255,   0,   0), 50); // Red
//   colorWipe(strip1.Color(  0, 255,   0), 50); // Green
//   colorWipe(strip1.Color(  0,   0, 255), 50); // Blue
    uint32_t time1 = micros();

    rainbow(1);             // Flowing rainbow cycle along the whole strip
    handleFFT();
    handleOnOffArray();
    printOnOffArray();
    // test_display();

    uint32_t time2 = micros();
    Serial.println(time2-time1);
}

