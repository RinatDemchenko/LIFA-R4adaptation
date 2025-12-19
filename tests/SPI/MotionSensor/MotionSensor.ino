#include <SPI.h>

const int CS_PIN = 10;
SPISettings settings(1000000, MSBFIRST, SPI_MODE3); 
const byte CTRL_REG1 = 0x20;
const byte OUT_X = 0x29;
const byte OUT_Y = 0x2B;
const byte OUT_Z = 0x2D;

void setup() {
  Serial.begin(9600);
  while (!Serial); 

  SPI.begin();
  
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); 

  delay(100);
  
  writeRegister(CTRL_REG1, 0x47);
  
  Serial.println("LIS35DE Init complete.");
}

void loop() {

  int8_t x = readRegister(OUT_X);
  int8_t y = readRegister(OUT_Y);
  int8_t z = readRegister(OUT_Z);

  Serial.print("X:");
  Serial.print(x);
  Serial.print(" Y:");
  Serial.print(y);
  Serial.print(" Z:");
  Serial.println(z);

  delay(100); 
}

void writeRegister(byte reg, byte value) {
  SPI.beginTransaction(settings);
  digitalWrite(CS_PIN, LOW); 
  SPI.transfer(reg);        
  SPI.transfer(value);       
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();           
}

int8_t readRegister(byte reg) {
  byte addressByte = reg | 0x80; 
  SPI.beginTransaction(settings);
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(addressByte);     
  byte result = SPI.transfer(0x00); 
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();           
  return (int8_t)result; 
}