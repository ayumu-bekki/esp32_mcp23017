#ifndef I2C_UTIL_H_
#define I2C_UTIL_H_
// ESP32 Epoch Clock
// (C)2021 bekki.jp
// Utilities

// Include ----------------------
#include <driver/gpio.h>
#include <driver/i2c.h>

namespace I2CUtil {

void InitializeMaster(const i2c_port_t port, const gpio_num_t sdaPin,
                      const gpio_num_t sclPin);

}  // namespace I2CUtil

#endif  // I2C_UTIL_H_

// EOF
