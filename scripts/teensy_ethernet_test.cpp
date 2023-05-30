#include <Arduino.h>
#include <NativeEthernet.h>

byte mac[] = {
    0xDE, 0xAD, 0xEF, 0xFE, 0xED
};

IPAddress ip(10, 0, 0, 122);

EthernetClient client;

void setup() {
    Serial.begin(115200);
    Ethernet.begin(mac, ip);

    delay(5000);

    if (Ethernet.hardwareStatus() == EthernetNoHardware)
}

void loop() {
    Serial.println("Hi.");
    delay(1000);
}