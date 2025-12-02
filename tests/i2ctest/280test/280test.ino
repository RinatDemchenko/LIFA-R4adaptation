#include <Wire.h>

void setup() {
  Serial.begin(9600);
  
  Wire.begin(); // Запускаем I2C
  
  // --- МАГИЯ ЗДЕСЬ ---
  // Принудительно включаем внутренние подтягивающие резисторы
  // Делать это нужно СТРОГО ПОСЛЕ Wire.begin()
  pinMode(SDA, INPUT_PULLUP);
  pinMode(SCL, INPUT_PULLUP);
  // -------------------
  
  // Дополнительно: снижаем скорость I2C до минимума (10 кГц вместо 100 кГц).
  // Слабым внутренним резисторам трудно работать на высокой скорости.
  Wire.setClock(10000); 
}

void loop() {
  Serial.print("Testing... ");
  
  Wire.beginTransmission(0x48);
  byte error = Wire.endTransmission();
  
  Serial.print("Error code: ");
  Serial.println(error);
  
  if (error == 0) Serial.println("-> SUCCESS! (Успех)");
  else if (error == 2) Serial.println("-> NACK (Шина работает, но вторая плата не отвечает)");
  else if (error == 4) Serial.println("-> OTHER (Всё ещё проблема с линией/физикой)");
  
  delay(1000);
}