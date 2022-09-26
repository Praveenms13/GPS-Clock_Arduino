#include <TinyGPS++.h>
#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
static const int RXPin = 0, TXPin = 1 ;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  ss.begin(9600);
  analogWrite(6,Contrast);
  lcd.begin(16,2);
  lcd.print("GPS CLK:");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
  ss.begin(GPSBaud);
  smartDelay(0);
}
void loop()
{
  printDateTime(gps.date, gps.time);
  Serial.println(" ");
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
    gps.encode(ss.read());
  }while(millis() - start<ms);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if(!d.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  if(!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
    lcd.setCursor(0, 0);
    lcd.print("DATE:");
    lcd.print(gps.date.day());
    lcd.print(".");
    lcd.print(gps.date.month());
    lcd.print(".");
    lcd.print(gps.date.year());
    Serial.print(t.hour());
    Serial.print(":");
    Serial.print(t.minute());
    Serial.print(":");
    Serial.print(t.second());
    lcd.setCursor(0, 1);
    lcd.print("GPS CLK:");
    int Hour=t.hour()+5;
    if(Hour>23)
    {
      Hour-=24;
    }
    int Minute=t.minute()+30;
    if(Minute>59)
    {
      Minute-=60;
      Hour+=1;
    }
    lcd.print(Hour);
    lcd.print(":");
    lcd.print(Minute);
    lcd.print(":");
    lcd.print(t.second());
  }
  smartDelay(0);
}
