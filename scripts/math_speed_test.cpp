#include <Arduino.h>

float levelsf[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
int levelsi[13];
int output[13][12];

void setup(){
    Serial.begin(115200);
    Serial.println("Setup done.");

    for (int i=0; i<13; i++) {
        levelsi[i] = levelsf[i];
    }
}

void loop() {
    // for (int i=0; i<13; i++) {
    //     Serial.print(levelsf[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();

    // for (int i=0; i<13; i++) {
    //     Serial.print(levelsi[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();

    for (int i=0; i<13; i++) {
        for (int j=0; j<12; j++) {
            output[i][j] = 0;
        }
    }

    uint32_t time1 = micros();

    for (int i=0; i<13; i++) {
        if (levelsi[i]>11) {
            for (int j=0; j<12; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>10) {
            for (int j=0; j<11; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>9) {
            for (int j=0; j<10; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>8) {
            for (int j=0; j<9; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>7) {
            for (int j=0; j<8; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>6) {
            for (int j=0; j<7; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>5) {
            for (int j=0; j<6; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>4) {
            for (int j=0; j<5; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>3) {
            for (int j=0; j<4; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>2) {
            for (int j=0; j<3; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>1) {
            for (int j=0; j<2; j++) {
                output[i][j] = 1;
            }
        }
        else if (levelsi[i]>0) {
            for (int j=0; j<1; j++) {
                output[i][j] = 1;
            }
        }
    }

    uint32_t time2 = micros();

    for (int i=0; i<13; i++) {
        Serial.print("i=");
        Serial.print(i);
        Serial.print("\tL=");
        Serial.print(levelsi[i]);
        Serial.print("\t");
    
        for (int j=0; j<12; j++) {
            Serial.print(output[i][j]);
            Serial.print("\t");
        }
        Serial.println();
    }
    Serial.print("Elapsed: ");
    Serial.println(time2 - time1);
    
    Serial.println();
    Serial.println();

    delay(1000);
}