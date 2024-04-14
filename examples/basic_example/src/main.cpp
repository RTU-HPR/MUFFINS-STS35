#include <Arduino.h>
#include <Wire.h>
#include <MUFFINS_STS35.h>

const int SENSOR_POWER_ENABLE_PIN = 17;
const int WIRE0_SCL = 1;
const int WIRE0_SDA = 0;

STS35 sts35;

STS35::Config sts35_config = {
  .wire = &Wire,
  .i2c_address = 0x4B
};

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1000);
  }

  pinMode(SENSOR_POWER_ENABLE_PIN, OUTPUT_12MA);
  digitalWrite(SENSOR_POWER_ENABLE_PIN, HIGH);

  if (Wire.setSCL(WIRE0_SCL) && Wire.setSDA(WIRE0_SDA))
  {
    Wire.begin();
  }

  if (!sts35.begin(sts35_config))
  {
    while(1)
    ;
  }
}

unsigned long read_time_start = 0;
unsigned long read_time_end = 0;

void loop()
{
  read_time_start = millis();
  sts35.read();
  read_time_end = millis();
  Serial.print("Temperature: ");
  Serial.print(sts35.data.temperature);
  Serial.print(" °C | Time: ");
  Serial.print(read_time_end - read_time_start);
  Serial.println(" ms");

  delay(100);
}