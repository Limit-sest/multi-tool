#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <ctime>
#include <QMC5883LCompass.h>

RTC_DS3231 rtc;
QMC5883LCompass compass;

void setup()
{
  Wire.begin();
  Serial.begin(9600); // for communicating with pc

  if (!rtc.begin())
  {
    Serial.println("Can't find rtc");
    while (1)
      ;
  }

  compass.init();
}

void loop()
{
  DateTime now = rtc.now();
  char buffer[25];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(),
          now.month(),
          now.day(),
          now.hour(),
          now.minute(),
          now.second());
  Serial.println(buffer);

  int azimuth = compass.getAzimuth();
  char direction[3];
  Serial.print(" Azimuth: ");
  Serial.print(azimuth);
  Serial.print(" Direction: ");
  Serial.print(direction[0]);
  Serial.print(direction[1]);
  Serial.print(direction[2]);
  Serial.println();

  delay(1000);
}
