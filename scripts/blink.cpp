#include <Arduino.h>

void setup() {
	pinMode(25, OUTPUT);
	pinMode(22, OUTPUT);
	Serial.begin(115200);
	delay(100);
}

void loop() {
	digitalWrite(25, HIGH);
	analogWrite(22, 50);
	Serial.println("Blink.");
	delay(500);
	digitalWrite(25, LOW);
	analogWrite(22, 10);
	delay(1000);
}
