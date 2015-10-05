// Copyright 2013, bechter.com - All Rights Reserved
#include <Arduino.h>
#include <OneWire.h>
#include <DS2438.h>

// define the Arduino digital I/O pin to be used for the 1-Wire network here
const uint8_t ONE_WIRE_PIN = 13;

// define the 1-Wire address of the DS2423 counter here (lsb first)
uint8_t DS2438_address[] = { 0x26, 0x40, 0x7F, 0xE1, 0x01, 0x00, 0x00, 0x7B };


OneWire ow(ONE_WIRE_PIN);
DS2438 ds2438(&ow, DS2438_address);

void setup() {
    Serial.begin(9600);
    ds2438.begin();
}

void loop() {
    ds2438.update();
    if (ds2438.isError()) {
        Serial.println("Error reading from DS2438 device");
    } else {
        Serial.print("Temperature = ");
        Serial.print(ds2438.getTemperature(), 1);
        Serial.print("C, Channel A = ");
        Serial.print(ds2438.getVoltage(DS2438_CHA), 1);
        Serial.print("v, Channel B = ");
        Serial.print(ds2438.getVoltage(DS2438_CHB), 1);
        Serial.println("v.");
    }
    delay(1500);
}
