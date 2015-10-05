//#include <Arduino.h>  
#include <OneWire.h>        //include the OneWire library

#define DS2413_ONEWIRE_PIN  (13)

//command shortcuts
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF

// define the 1-Wire addresses of the DS2413 GPIOs here
uint8_t DS2413_address1[8] = { 0x3A, 0x45, 0x22, 0x27, 0x00, 0x00, 0x00, 0x8C };       //device #1

// define the Arduino digital I/O pin to be used for the 1-Wire network here
OneWire oneWire(DS2413_ONEWIRE_PIN);

void setup(void) 
{
  Serial.begin(9600);  
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


void loop(void) 
{
  /* Write */
  write(0x1, DS2413_address1);
  delay(2000);
  write(0x2, DS2413_address1);
  delay(2000);

  Serial.println("Finished cycle");       //finished flashing cycle
}

