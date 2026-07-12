#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


AudioInputI2S               i2s1;
AudioSynthWaveformSine      sinewave;
AudioAnalyzeFFT1024         fft1024;
AudioMixer4                 mixer1;
AudioConnection             patchCord1(i2s1, 0, mixer1, 0);
AudioConnection             patchCord3(i2s1, 1, mixer1, 1);
AudioConnection             patchCord5(mixer1, fft1024);
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

// #define LED_COUNT 104
#define LED_COUNT 10

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
float levels51[51];
int   shown51[12][51];


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
        levels51[0] =  fft1024.read(0,2);
        levels51[1] =  fft1024.read(2,3);
        levels51[2] =  fft1024.read(3,4);
        levels51[3] =  fft1024.read(4,5);
        levels51[4] =  fft1024.read(5,6);
        levels51[5] =  fft1024.read(6,7);
        levels51[6] =  fft1024.read(7,8);
        levels51[7] =  fft1024.read(8,9);
        levels51[8] =  fft1024.read(9,10);
        levels51[9] =  fft1024.read(10,11);

        levels51[10] =  fft1024.read(11,12);
        levels51[11] =  fft1024.read(12,13);
        levels51[12] =  fft1024.read(14,16);
        levels51[13] =  fft1024.read(16,18);
        levels51[14] =  fft1024.read(18,20);
        levels51[15] =  fft1024.read(20,22);
        levels51[16] =  fft1024.read(22,24);
        levels51[17] =  fft1024.read(24,26);
        levels51[18] =  fft1024.read(26,28);
        levels51[19] =  fft1024.read(28,31);

        levels51[20] =  fft1024.read(31,34);
        levels51[21] =  fft1024.read(34,37);
        levels51[22] =  fft1024.read(37,40);
        levels51[23] =  fft1024.read(40,43);
        levels51[24] =  fft1024.read(43,46);
        levels51[25] =  fft1024.read(46,50);
        levels51[26] =  fft1024.read(50,54);
        levels51[27] =  fft1024.read(54,58);
        levels51[28] =  fft1024.read(58,62);
        levels51[29] =  fft1024.read(62,66);

        levels51[30] =  fft1024.read(66,71);
        levels51[31] =  fft1024.read(71,76);
        levels51[32] =  fft1024.read(76,81);
        levels51[33] =  fft1024.read(81,86);
        levels51[34] =  fft1024.read(86,92);
        levels51[35] =  fft1024.read(92,98);
        levels51[36] =  fft1024.read(98,104);
        levels51[37] =  fft1024.read(104,111);
        levels51[38] =  fft1024.read(111,118);
        levels51[39] =  fft1024.read(118,126);

        levels51[40] =  fft1024.read(118,126);
        levels51[41] =  fft1024.read(126,135);
        levels51[42] =  fft1024.read(135,146);
        levels51[43] =  fft1024.read(146,159);
        levels51[44] =  fft1024.read(159,174);
        levels51[45] =  fft1024.read(174,191);
        levels51[46] =  fft1024.read(191,211);
        levels51[47] =  fft1024.read(211,234);
        levels51[48] =  fft1024.read(234,260);
        levels51[49] =  fft1024.read(260,323);
        levels51[50] =  fft1024.read(323,360);

        for (int i=0; i < 51; i++) {
            levels51[i] *= fft_gain;
        }

        // if you have the volume pot soldered to your audio shield
        // uncomment this line to make it adjust the full scale signal
        //scale = 8.0 + analogRead(A1) / 5.0;

        // for(int i=0;i<51;i++) {
        //     Serial.print(levels51[i]);
        //     Serial.print(" ");
// loop() function -- runs repeatedly as long as board is on ---------------
        // }
        // Serial.println();
    }
}


void test_display() {
    uint32_t time1 = micros();

    for (int i=0; i<51; i++) {
        for (int j=0; j<12; j++) {
            shown51[j][i] = 0;
        }
    }

    uint32_t time2 = micros();

    // switch case with ints
    for (int i=0; i<51; i++) {
        if (levels51[i]>12) {
            for (int j=0; j<12; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>11) {
            for (int j=0; j<11; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>10) {
            for (int j=0; j<10; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>9) {
            for (int j=0; j<9; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>8) {
            for (int j=0; j<8; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>7) {
            for (int j=0; j<7; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>6) {
            for (int j=0; j<6; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>5) {
            for (int j=0; j<5; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>4) {
            for (int j=0; j<4; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>3) {
            for (int j=0; j<3; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>2) {
            for (int j=0; j<2; j++) {
                shown51[j][i] = 1;
            }
        }
        else if (levels51[i]>1) {
            for (int j=0; j<1; j++) {
                shown51[j][i] = 1;
            }
        }
    }

    uint32_t time3 = micros();

    for (int i=10; i>=0; i--) {
        strip1.setPixelColor(i, strip1.Color(shown51[0][i]*50, 0, 0));
        strip2.setPixelColor(i, strip1.Color(shown51[1][i]*50, 0, 0));
        strip3.setPixelColor(i, strip1.Color(shown51[2][i]*50, 0, 0));
        strip4.setPixelColor(i, strip1.Color(shown51[3][i]*50, 0, 0));
        strip5.setPixelColor(i, strip1.Color(shown51[4][i]*50, 0, 0));
        strip6.setPixelColor(i, strip1.Color(shown51[5][i]*50, 0, 0));
        strip7.setPixelColor(i, strip1.Color(shown51[6][i]*50, 0, 0));
        strip8.setPixelColor(i, strip1.Color(shown51[7][i]*50, 0, 0));
        strip9.setPixelColor(i, strip1.Color(shown51[8][i]*50, 0, 0));
        strip10.setPixelColor(i, strip1.Color(shown51[9][i]*50, 0, 0));
        strip11.setPixelColor(i, strip1.Color(shown51[10][i]*50, 0, 0));
        strip12.setPixelColor(i, strip1.Color(shown51[11][i]*50, 0, 0));

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

        // Serial.print(shown51[0][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[1][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[2][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[3][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[4][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[5][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[6][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[7][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[8][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[9][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[10][i]*50);
        // Serial.print("\t");
        // Serial.print(shown51[11][i]*50);
        // Serial.println();

        // Serial.print(shown51[i][0]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][1]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][2]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][3]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][4]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][5]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][6]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][7]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][8]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][9]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][10]*50);
        // Serial.print("\t");
        // Serial.print(shown51[i][11]*50);
        // Serial.println();
    }

    uint32_t time4 = micros();

    Serial.print(time2 - time1);
    Serial.print("\t");
    Serial.print(time3 - time2);
    Serial.print("\t");
    Serial.print(time4 - time3);
    Serial.println();
    delay(100);
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

    // uint32_t time1 = millis();
    // rainbow(1);             // Flowing rainbow cycle along the whole strip
    handleFFT();

    // uint32_t time2 = millis();

    test_display();

    // Serial.print(time2 - time1);
    // Serial.print("\t");
    // Serial.println(millis() - time2);


    // for (int i=0; i<12; i++) {
    //     Serial.print(shown51[i][10]);
    //     Serial.print("\t");
    // }
    // Serial.println();
}

