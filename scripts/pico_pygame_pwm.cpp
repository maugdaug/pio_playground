// #include <pico/stdlib.h>
#include <Arduino.h>
#include <Scheduler.h>

//////////////////////////////////////////////// PINS
// PWM
#define PIN_PWM_1A 18
#define PIN_PWM_1B 19
#define PIN_PWM_2A 20
#define PIN_PWM_2B 21
// Encoders
#define PIN_ENC_1A 12
#define PIN_ENC_1B 13
#define PIN_ENC_2A 10
#define PIN_ENC_2B 11

const uint8_t packet_size = 49;


////////////////////////////////////////////// Variables
// Received over FTDI
const uint8_t buffer_size = 256;
unsigned char buffer[buffer_size];
float RX_X = 0;
float RX_Y = 0;
float RX_Z = 0;
float RX_E = 0;
float RX_L2 = 0;
float RX_R2 = 0;

int PWM_1A = 0;
int PWM_2A = 0;

int ticks1 = 0;
int ticks2 = 0;
int debounce_time = 1;
uint32_t last_tick1_ms = 0;
uint32_t last_tick2_ms = 0;
uint32_t ticks1A = 0;
uint32_t ticks1B = 0;
uint32_t ticks2A = 0;
uint32_t ticks2B = 0;



void tick1A() {
    if(millis()-last_tick1_ms>debounce_time) {
        ticks1A++;
        if (digitalRead(PIN_ENC_1A)==HIGH) {
            if (digitalRead(PIN_ENC_1B)==HIGH) {
                ticks1--;
            }
            else ticks1++;
        }
        else {
            if (digitalRead(PIN_ENC_1B)==HIGH) {
                ticks1++;
            }
            else ticks1--;
        }
        last_tick1_ms = millis();
    }
    Serial.println(ticks1);
}

void tick1B() {
    if(millis()-last_tick1_ms>debounce_time) {
        ticks1B++;
        if (digitalRead(PIN_ENC_1B)==HIGH) {
            if (digitalRead(PIN_ENC_1A)==HIGH) {
                ticks1++;
            }
            else ticks1--;
        }
        else {
            if (digitalRead(PIN_ENC_1A)==HIGH) {
                ticks1--;
            }
            else ticks1++;
            
        }
        last_tick1_ms = millis();
    }
    Serial.println(ticks1);
}

void tick2A() {
    if(millis()-last_tick2_ms>debounce_time) {
        ticks2A++;
        if (digitalRead(PIN_ENC_2A)==HIGH) {
            if (digitalRead(PIN_ENC_2B)==HIGH) {
                ticks2--;
            }
            else ticks2++;
        }
        else {
            if (digitalRead(PIN_ENC_2B)==HIGH) {
                ticks2++;
            }
            else ticks2--;
        }
        last_tick2_ms = millis();
    }
    Serial.println(ticks2);
}

void tick2B() {
    if(millis()-last_tick2_ms>debounce_time) {
        ticks2B++;
        if (digitalRead(PIN_ENC_2B)==HIGH) {
            if (digitalRead(PIN_ENC_2A)==HIGH) {
                ticks2++;
            }
            else ticks2--;
        }
        else {
            if (digitalRead(PIN_ENC_2A)==HIGH) {
                ticks2--;
            }
            else ticks2++;
        }
        last_tick2_ms = millis();
    }
    Serial.println(ticks2);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    float numerator = (float)(x - in_min) * (out_max - out_min);
    float denominator = (float)in_max - (float)in_min;
    float output = numerator / denominator + out_min;

    return output;
}

int remap(float input) {
    int output;

    if(input < 0.0) {
        float math = mapfloat(input, -1.0, -0.2, -255.0, 0.0);
        output = constrain(math, -255, 0);
    }
    else {
        float math = mapfloat(input, 0.2, 1.0, 0.0, 255.0);
        output = constrain(math, 0, 255);
    }

    return output;
}

void actuate() {
    PWM_1A = remap(RX_X);
    PWM_2A = remap(RX_Y);

    if(PWM_1A < 0) {
        analogWrite(PIN_PWM_1A, abs(PWM_1A));
        analogWrite(PIN_PWM_1B, 0);
    }
    else {
        analogWrite(PIN_PWM_1A, 0);
        analogWrite(PIN_PWM_1B, abs(PWM_1A));
    }

    if(PWM_2A < 0) {
        analogWrite(PIN_PWM_2A, abs(PWM_2A));
        analogWrite(PIN_PWM_2B, 0);
    }
    else {
        analogWrite(PIN_PWM_2A, 0);
        analogWrite(PIN_PWM_2B, abs(PWM_2A));
    }

    // Serial.print("1A: ");
    // Serial.print(PWM_1A);
    // Serial.print("\t2A: ");
    // Serial.print(PWM_2A);
    // Serial.println();
}

void get_serial() {
    if(Serial1.available() >= packet_size) {
        // Serial.print(".");
        char nextbyte = (char)Serial1.read();
        // Serial.println(nextbyte);
        if(nextbyte == ',') {
            // Serial.println("=====================");
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_X, buffer, 4);
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_Y, buffer, 4);
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_Z, buffer, 4);
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_E, buffer, 4);
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_L2, buffer, 4);
            Serial1.readBytes(buffer, 4);
            memcpy(&RX_R2, buffer, 4);

            // RX_X = (float)RX_X;
            // RX_Y = (float)RX_Y;
            // RX_Z = (float)RX_Z;
            // RX_E = (float)RX_E;
            // RX_L2 = (float)RX_L2;
            // RX_R2 = (float)RX_R2;

            // Serial.print(RX_X);
            // Serial.print("\t");
            // Serial.print(RX_Y);
            // Serial.print("\t");
            // Serial.print(RX_Z);
            // Serial.print("\t");
            // Serial.print(RX_E);
            // Serial.print("\t");
            // Serial.print(RX_L2);
            // Serial.print("\t");
            // Serial.print(RX_R2);
            // Serial.println();

            actuate();
        }
        else {
            // Serial.print("Something is wrong. Serial buffer size: ");
            // Serial.println(Serial1.available());
            Serial1.read();
        }
    }
}

void home() {
    int loop_interval = 500;
    int loop_index = 1;
    bool homing = true;
    int prev_ticks1 = ticks1;
    int prev_ticks2 = ticks2;

    Serial.println("Homing...");
    
    analogWrite(PIN_PWM_1A, 0);
    analogWrite(PIN_PWM_1B, 255);
    analogWrite(PIN_PWM_2A, 0);
    analogWrite(PIN_PWM_2B, 0);

    int home_start_ms = millis();

    while(homing) {
        if(millis() - home_start_ms > loop_index * loop_interval) {
            loop_index++;

            // Serial.print(ticks1);
            // Serial.print("\t\t");
            // Serial.println(ticks2);

            if (ticks1 == prev_ticks1 && ticks2 == prev_ticks2) {
                Serial.println("Final:");
                Serial.print(ticks1);
                Serial.print("\t\t");
                Serial.println(ticks2);

                ticks1 = 0;
                ticks2 = 0;
                homing = false;
                Serial.println("Done homing.");
                analogWrite(PIN_PWM_1B, 0);
                analogWrite(PIN_PWM_2B, 0);

                // Serial.print("1A: ");
                // Serial.print(ticks1A);
                // Serial.print("\t1B: ");
                // Serial.print(ticks1B);
                // Serial.print("\t2A: ");
                // Serial.print(ticks2A);
                // Serial.print("\t2B: ");
                // Serial.println(ticks2B);
            }

            prev_ticks1 = ticks1;
            prev_ticks2 = ticks2;
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial1.begin(2000000);

    // pinMode(PIN_ENC_1A, INPUT_PULLUP);
    // pinMode(PIN_ENC_1B, INPUT_PULLUP);
    // pinMode(PIN_ENC_2A, INPUT_PULLUP);
    // pinMode(PIN_ENC_2B, INPUT_PULLUP);

    attachInterrupt(PIN_ENC_1A, tick1A, CHANGE);
    attachInterrupt(PIN_ENC_1B, tick1B, CHANGE);
    attachInterrupt(PIN_ENC_2A, tick2A, CHANGE);
    attachInterrupt(PIN_ENC_2B, tick2B, CHANGE);

    delay(10000);
    home();
}

void loop() {
    get_serial();
    // yield();
}

