
#include <Arduino.h>
#include <OneWire.h>
#include <DS2438.h>

// define the Arduino digital I/O pin to be used for the 1-Wire network here
const uint8_t ONE_WIRE_PIN = 13;

// define the 1-Wire addresses of the DS2413 GPIOs here,, then // define the 1-Wire address of the DS2423 counter here (lsb first)
uint8_t DS2413_address1[8] = { 




0x3A, 0xC2, 0x53, 0x28, 0x00, 0x00, 0x00, 0xD9
};

uint8_t DS2438_address[8] = { 





0x26, 0xBE, 0xC3, 0xD1, 0x01, 0x00, 0x00, 0x3C
};



//command shortcuts
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF


OneWire oneWire(ONE_WIRE_PIN);
DS2438 ds2438(&oneWire, DS2438_address);

void setup() {
    Serial.begin(9600);
    ds2438.begin();
}

void loop() 
{
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
  //delay(1500);

  /* Write */
  write(0x1, DS2413_address1);
  delay(2000);
  write(0x2, DS2413_address1);
  delay(2000);

  Serial.println("Finished cycle");       //finished flashing cycle
}


int write(uint8_t state, uint8_t addr[8])
{
  oneWire.reset();
  oneWire.select(addr);
  oneWire.write(DS2413_ACCESS_WRITE);
  oneWire.write(state);
  oneWire.write(~state);                    //Invert data and resend   
  oneWire.reset();
}
