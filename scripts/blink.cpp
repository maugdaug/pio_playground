#include <Arduino.h>

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(115200);
}

void loop() {
	digitalWrite(13, HIGH);
	Serial.println("On.");
	delay(1000);
	digitalWrite(13, LOW);
	Serial.println("Off.");
	delay(1000);
}
