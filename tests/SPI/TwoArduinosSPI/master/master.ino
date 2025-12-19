#include <SPI.h>

void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH); 
}

void loop() {
  char msg[] = "Hello";
  
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE0));
  digitalWrite(10, LOW); 
  
  for (int i = 0; i < 5; i++) {
    SPI.transfer(msg[i]);
    delay(20); 
  }
  
  digitalWrite(10, HIGH);
  SPI.endTransaction();
  
  Serial.println("Data sent");
  delay(1000);
}