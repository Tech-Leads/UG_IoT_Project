#include <dht.h>
#include <LiquidCrystal.h>

int RS=A5, E=A4, D4=A3, D5=A2, D6=A1, D7=A0;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

#define datapin 8
int sub_pump = 10;

dht DHT;
void setup() {
  
pinMode(8,INPUT);
pinMode(sub_pump,OUTPUT);
Serial.begin(9600);  

}

void loop() {
 int readData = DHT.read11(datapin);
  float t = DHT.temperature;
  float h = DHT.humidity;
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("\t Humidity = ");
  Serial.print(h);
  Serial.println(" %");
  delay(2000);    

 

}
