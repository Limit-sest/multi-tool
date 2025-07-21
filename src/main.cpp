#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <ctime>
#include <QMC5883LCompass.h>
#include <MPU6500_WE.h>

RTC_DS3231 rtc;
QMC5883LCompass compass;
MPU6500_WE mpu = MPU6500_WE();

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

  if (!mpu.init())
  {
    Serial.println("Can't find mpu");
  }

  // mpu calibration
  Serial.println("place mpu flat and don't move it");
  delay(1000);
  mpu.autoOffsets();
  Serial.println("calibrated!");
}

void loop()
{
  DateTime now = rtc.now();
  char timeBuffer[25];
  sprintf(timeBuffer, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(),
          now.month(),
          now.day(),
          now.hour(),
          now.minute(),
          now.second());

  int azimuth = compass.getAzimuth();
  char direction[3];

  xyzFloat gValue = mpu.getGValues();
  xyzFloat gyr = mpu.getGyrValues();
  float temp = mpu.getTemperature();
  float resultantG = mpu.getResultantG(gValue);

  Serial.print("Time & date: ");
  Serial.println(timeBuffer);
  // Time & date: 2025-07-21 15:04:05

  Serial.print("Compass: ");
  Serial.print(azimuth);
  Serial.print("° (");
  Serial.print(direction[0]);
  Serial.print(direction[1]);
  Serial.print(direction[2]);
  Serial.println(")");
  // Compass: 90° (E)

  Serial.print("Acceleration (in g, x y z): ");
  Serial.print(gValue.x);
  Serial.print(" ");
  Serial.print(gValue.y);
  Serial.print(" ");
  Serial.println(gValue.z);
  // Acceleration (in g, x y z): 0.12 0.03 0.98

  Serial.println("Gyroscope data in degrees/s (x y z): ");
  Serial.print(gyr.x);
  Serial.print(" ");
  Serial.print(gyr.y);
  Serial.print(" ");
  Serial.println(gyr.z);
  // Gyroscope data in degrees/s (x y z): 0.5 -02 0.1

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");
  // Temperature: 27°C

  Serial.println("********************************************");

  delay(1000);
}
