#include <Arduino.h>

//////////////////////////////////////////////// PINS
// PWM
#define PIN_PWM_1A 1
#define PIN_PWM_1B 2
#define PIN_PWM_2A 3
#define PIN_PWM_2B 4
// Encoders
#define PIN_ENC_1A 5
#define PIN_ENC_1B 6
#define PIN_ENC_2A 7
#define PIN_ENC_2B 8

const uint8_t packet_size = 5;


////////////////////////////////////////////// Variables
// Received over FTDI
const uint8_t buffer_size = 5;
unsigned char buffer[buffer_size];
float RX_X = 0;
float RX_Y = 0;
float RX_Z = 0;
float RX_E = 0;
float RX_L2 = 0;
float RX_R2 = 0;

void setup() {
    Serial.begin(115200);
    Serial1.begin(2000000);


}

void loop() {
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

            Serial.print(RX_X);
            Serial.print("\t");
            Serial.print(RX_Y);
            Serial.print("\t");
            Serial.print(RX_Z);
            Serial.print("\t");
            Serial.print(RX_E);
            Serial.print("\t");
            Serial.print(RX_L2);
            Serial.print("\t");
            Serial.print(RX_R2);
            Serial.println();
        }
        else {
            Serial.print("Something is wrong. Serial buffer size: ");
            Serial.println(Serial1.available());
            Serial1.read();
        }
    }
}