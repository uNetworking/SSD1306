#ifndef I2C_WRAPPER_H
#define I2C_WRAPPER_H

/* I2C wrapper for Arduino MCUs */

#include <Wire.h>

static inline void I2C_WRAPPER_init() {
  Wire.begin();
}

static inline void I2C_WRAPPER_beginTransmission(unsigned char address) {
  Wire.beginTransmission(address);
}

static inline void I2C_WRAPPER_write(unsigned char data) {
  Wire.write(data);
}

static inline void I2C_WRAPPER_endTransmission() {
  Wire.endTransmission();
}

#endif
