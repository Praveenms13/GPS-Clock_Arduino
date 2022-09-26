#include <LiquidCrystal.h> 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
static const int RXPin = 0, TXPin = 1 ;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  Serial.begin(9600);
  ss.begin(GPSBaud);
} 
void loop()
{ 
 while (ss.available() > 0) 
 {
  gps.encode(ss.read());
  if (gps.location.isUpdated())
  {
   Serial.print(" Latitude= "); 
   Serial.print(gps.location.lat(), 6);
   Serial.print('\n');
   Serial.print(" Longitude= "); 
   Serial.print(gps.location.lng(), 6);
   Serial.print('\n');
   Serial.print(" ALTITUDE: ");
   Serial.print(gps.altitude.meters(), 6);
   Serial.print('\n');
   Serial.print(" DATE: ");
   Serial.print(gps.date.month());
   Serial.print(F("/"));
   Serial.print(gps.date.day());
   Serial.print(F("/"));
   Serial.print(gps.date.year());
   Serial.print('\n');
   Serial.print(" TIME: ");
   Serial.print(gps.time.hour());
   Serial.print(F(":"));
   Serial.print(gps.time.minute());
   Serial.print(F(":"));
   Serial.print(gps.time.second());
   Serial.print('\n');
   Serial.print(" SPEED: ");
   Serial.print(gps.speed.kmph());
   Serial.print(" kmph");
   Serial.print('\n');
   Serial.print('\n');
  }
 }
 lcd.setCursor(0, 0);
 lcd.print("TIME:");
 lcd.print(gps.time.hour());
 lcd.print(":");
 lcd.print(gps.time.minute());
 lcd.print(":");
 lcd.print(gps.time.second());
 lcd.setCursor(0, 1);
 lcd.print("DATE:");
 lcd.print(gps.date.day());
 lcd.print(".");
 lcd.print(gps.date.month());
 lcd.print(".");
 lcd.print(gps.date.year());
}
