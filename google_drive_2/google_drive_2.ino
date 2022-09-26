#include <LiquidCrystal.h> 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
static const int RXPin = 0, TXPin = 1 ;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial SoftSerial(RXPin, TXPin);
byte last_second;
char Time[]  = "TIME:00:00:00";
char Date[]  = "DATE:00/00/2000";

void setup(void) 
{
  SoftSerial.begin(9600);
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(Time);                
  lcd.setCursor(0, 1);
  lcd.print(Date);                           
}

void loop() 
{
  while (SoftSerial.available() > 0) 
  {
   if (gps.encode(SoftSerial.read())) 
    {
      if (gps.time.isValid()) 
      {
        Time[5]  = gps.time.hour()   / 10 + 48;
        Time[6]  = gps.time.hour()   % 10 + 48;
        Time[8]  = gps.time.minute() / 10 + 48;
        Time[9]  = gps.time.minute() % 10 + 48;
        Time[11] = gps.time.second() / 10 + 48;
        Time[12] = gps.time.second() % 10 + 48;
      }
      if (gps.date.isValid()) 
      {
        Date[5]  = gps.date.day()    / 10 + 48;
        Date[6]  = gps.date.day()    % 10 + 48;
        Date[8]  = gps.date.month()  / 10 + 48;
        Date[9]  = gps.date.month()  % 10 + 48;
        Date[13] =(gps.date.year()   / 10) % 10 + 48;
        Date[14] = gps.date.year()   % 10 + 48;
      }
      if(last_second != gps.time.second()) 
      {
        last_second = gps.time.second();
        lcd.setCursor(0, 0);
        lcd.print(Time);                       
        lcd.setCursor(0, 1);
        lcd.print(Date); 
      }

    }

  }

}
