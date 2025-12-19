#include <SPI.h>

volatile char receivedData;
volatile bool dataReady = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(MISO, OUTPUT); 
  
  SPCR |= _BV(SPE); 
  
  SPCR |= _BV(SPIE); 
  
  Serial.println("R3 Slave Ready");
}

ISR(SPI_STC_vect) {
  receivedData = SPDR;
  dataReady = true;
}

void loop() {
  if (dataReady) {
    Serial.print("Received: ");
    Serial.println(receivedData); 
    dataReady = false;
  }
}