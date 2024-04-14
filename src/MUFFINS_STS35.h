#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <MUFFINS_Component_Base.h>
#include <ClosedCube_I2C.h>
#include <ClosedCube_STS35.h>

class STS35 : public Component_Base
{
public:
  struct Config
  {
    TwoWire *wire;
    int i2c_address;
  };

  struct Data
  {
    float temperature;
  } data;

private:
  ClosedCube::Sensor::STS35 _sts35;
  Config _config;

public:
  /**
   * @brief Construct a new STS35 sensor instance
   */
  STS35(String component_name = "STS35", void (*info_function)(String) = nullptr, void (*error_function)(String) = nullptr);

  /**
   * @brief Destroys the STS35 sensor instance.
   */
  ~STS35();

  bool begin(const Config &config);

  bool read();
};
