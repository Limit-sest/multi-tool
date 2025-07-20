#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <ctime>

RTC_DS3231 rtc;

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
  delay(1000);
}
