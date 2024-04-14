#include <MUFFINS_STS35.h>

STS35::STS35(String component_name, void (*info_function)(String), void (*error_function)(String)) : Component_Base(component_name, info_function, error_function)
{
  return;
}

STS35::~STS35()
{
  return;
}

bool STS35::begin(const Config &config)
{
  _config = config;
  _sts35 = ClosedCube::Sensor::STS35(_config.wire);
  _sts35.address(_config.i2c_address);
  _sts35.setRepeatability(ClosedCube::Sensor::STS35_Repeatability::STS35_REPEATABILITY_MEDIUM); // LOW and MEDIUM take 6 ms to read, but HIGH takes 13 ms. There is no need to use HIGH repeatability.

  // There is no begin function in the ClosedCube_STS35 library
  // To check if the sensor is connected, we can read the temperature
  float test = _sts35.readTemperature();
  if (test > 100.00 || test < -100.0 || test == 0.00)
  {
    error("Failed to initialize!");
    return false;
  }
  
  info("Initialized successfully!");
  set_initialized(true);

  return true;
}

bool STS35::read()
{
  if (!initialized())
  {
    return false;
  }

  data.temperature = _sts35.readTemperature();
  return true;
}