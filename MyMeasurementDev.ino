/*
  My Measurement device #1

  Measures temperature with 0.3 C accuracy, humidity
  and static pressure. Displays result on LCD screen.

  Future: Add SD card module for storage
  

*/

#include <LiquidCrystal.h>
#include <Adafruit_SHT31.h>
#include <SFE_BMP180.h>

// Define object LiquidCrystal
// Define object SHT31 sensor
// Define object BMP180 sensor
LiquidCrystal lcd(3, 2, 4, 5, 6, 7);
Adafruit_SHT31 sht31 = Adafruit_SHT31();
SFE_BMP180 pressure;

char status;
double T, P; 

void setup() {  
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Initializing");
  lcd.setCursor(0,1);
  lcd.print("device...");

  delay(500);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SHT31...");
  if (!sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    lcd.print(" fail!");
    while (1) delay(1);
  }
  lcd.print(" O.K.!");
  lcd.setCursor(0,1);
  lcd.print("BMP180...");
  if (!pressure.begin()) {
    lcd.print(" fail!!");
    while (1) delay(1);
  }
  lcd.print(" O.K.!");

}

void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  lcd.clear();
  lcd.setCursor(0,0);
   
  if (! isnan(t)) {  // check if 'is not a number'
    lcd.print(t); 
    lcd.print((char)223);
    lcd.print("C, ");
  } else { 
    lcd.print("Temp failed!");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    lcd.print(h);lcd.print(" %");
  } else { 
    lcd.print("Humidity failed!");
  }

  
  status = pressure.startTemperature();
  delay(status);
  pressure.getTemperature(T);
  status = pressure.startPressure(3);
  delay(status);
  status = pressure.getPressure(P,T);
  
  lcd.setCursor(0,1);
  lcd.print("P");
  lcd.print((char)161);
  lcd.print(" = ");
  lcd.print(P/10, 3);
  lcd.print(" kPa");
 
  delay(250);
}
