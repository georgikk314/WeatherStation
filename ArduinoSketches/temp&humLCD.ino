//Interface the DHT11 Temp & Humidity sensor and display humidity and  temperature
//in Celsius on a 16x2 character LCD


#include  <LiquidCrystal.h>
#include  <DHT.h>;

 DHT dht(9 , DHT22);



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   //set Uno pins that are  connected to LCD, 4-bit

void setup() {
  
  analogWrite(6,20);
  lcd.begin(16,2);    //set  16 columns and 2 rows of 16x2 LCD
  dht.begin();

}

void loop() {
  float tempRead = dht.readTemperature();
  float HRead = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempRead);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(HRead);
  lcd.print("%");
  delay(5000);
  
}
