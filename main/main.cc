// ESP32 IO Expander MCP23017 I2C Driver Sample
// (C)2024 bekki.jp
#include <esp_log.h>
#include <freertos/FreeRTOS.h>

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
static const char *TAG = "MPC23017 Driver Sample";

#include "i2c_util.h"
#include "mcp23017.h"

/// I2Cポート番号
static constexpr i2c_port_t I2C_PORT_NO = I2C_NUM_0;
/// I2C SDA GPIO番号 (黄)
static constexpr gpio_num_t GPIO_I2C_SDA = GPIO_NUM_25; 
/// I2C SCL GPIO番号 (緑)
static constexpr gpio_num_t GPIO_I2C_SCL = GPIO_NUM_26;  
/// MCP23017 I2C クライアントアドレス
static constexpr uint8_t MCP23017_I2C_ADDRESS = 0x20;  

extern "C" void app_main() {
  ESP_LOGI(TAG, "Start");

  // I2C初期化
  I2CUtil::InitializeMaster(I2C_PORT_NO, GPIO_I2C_SDA, GPIO_I2C_SCL);

  // MCP23017設定・初期化
  MCP23017 mcp23017;

  // Input設定(内部プルアップ)
  mcp23017.SetInputOutput(MCP23017::GPIO_GROUP_A, 7, true);
  mcp23017.SetInputOutput(MCP23017::GPIO_GROUP_A, 6, true); 

  mcp23017.Setup(I2C_PORT_NO, MCP23017_I2C_ADDRESS);
  mcp23017.Clear();

  while (true) {
    // ESP_LOGI(TAG, "Port B0:%d B1:%d",
    // mcp23017.GetInputGpio(MCP23017::GPIO_GROUP_A, 7),
    // mcp23017.GetInputGpio(MCP23017::GPIO_GROUP_A, 6));

    mcp23017.SetOutputGpio(MCP23017::GPIO_GROUP_B, 0,
                     mcp23017.GetInputGpio(MCP23017::GPIO_GROUP_A, 7));
    mcp23017.SetOutputGpio(MCP23017::GPIO_GROUP_B, 1,
                     mcp23017.GetInputGpio(MCP23017::GPIO_GROUP_A, 6));

    TickType_t lastWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime, 10 / portTICK_PERIOD_MS);
  }
}

// EOF
