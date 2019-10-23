  #include "DHT.h"
  #include <LiquidCrystal_I2C.h>
  #include <RH_ASK.h> 
  #include <SPI.h>

  const int en =2, rw = 1, rs = 0, d4 = 4, d5 = 5,  d6 = 6,  d7 = 7, bl = 3;
  const int i2c_addr = 0x3F;
  LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

float hum;    // Stores humidity value in percent
float temp;
  #define DHTPIN 8
  #define DHTTYPE DHT11
  int moisture = A0;
  int sub_pump = 7;
  int air_in = 6;
  int air_out = 5;
  //transmitter 12

String str_humid;
String str_temp;
String str_out;
RH_ASK rf_driver;
  
  DHT dht(DHTPIN, DHTTYPE);
  void setup() {
  rf_driver.init();
  dht.begin();
  lcd.begin(16,2);  
  pinMode(8,INPUT_PULLUP);
  pinMode(sub_pump,OUTPUT);
  pinMode(air_in,OUTPUT);
  pinMode(air_out,OUTPUT);
  pinMode(moisture,INPUT_PULLUP);
  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print("TECH LEADS GHANA");
  delay(5000);
  lcd.clear();  

}

void loop() {
  delay(2000);
  moisture=analogRead(A0);
  //int readData = DHT.read11(datapin);
   temp= dht.readTemperature();
   hum = dht.readHumidity();
  Serial.print("Temperature = ");
  Serial.print(str_temp);
  Serial.print(" *C ");
  Serial.print("\t Humidity = ");
  Serial.print(str_humid);
  Serial.print(" %");
  Serial.print("\t Moisture = ");
  Serial.println(moisture);
  delay(2000);    

  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Hum = ");
  lcd.print(hum);
  lcd.print("% ");



   str_humid = String(hum);
   str_temp = String(temp);

   
    str_out = str_humid + "," + str_temp;
    static char *msg = str_out.c_str();
    
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
  

      //Moisture
  if (moisture >= 300){
    digitalWrite(sub_pump, HIGH);
    }
  else{
    digitalWrite(sub_pump,LOW); 
  }

  // Fan
  if (temp >= 30){
    digitalWrite(air_out,HIGH);
    delay(10000);
    digitalWrite(air_in,HIGH);
    delay(10000);
  }
  else{
    digitalWrite(air_out,LOW);
    digitalWrite(air_in,LOW);
  }
} 
