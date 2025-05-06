# M5Unit-HexStep 驱动组件

这是一个用于M5Unit-HexStep设备的驱动组件，通过I2C协议实现通信。

## 特性

- 使用回调函数机制实现I2C通信，适配不同平台
- 在通信前检查回调函数是否正常初始化
- 支持LED控制、开关状态读取、RGB颜色设置等功能
- 支持配置保存到Flash

## 文件结构

```
components/m5_unit_hexstep/
├── include/
│   └── unit_hexstep.h      # 头文件，包含接口定义和常量
├── src/
│   └── unit_hexstep.c      # 源文件，实现驱动功能
└── examples/
    └── unit_hexstep_example.c  # 使用示例
```

## 使用方法

### 1. 初始化

首先需要定义读写寄存器的回调函数，然后初始化设备：

```c
// 定义I2C读写回调函数
int my_i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);
int my_i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

// 定义设备句柄
unit_hexstep_t hexstep_dev;

// 初始化设备
int ret = unit_hexstep_init(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, 
                           my_i2c_read_reg, my_i2c_write_reg);
if (ret != 0) {
    // 初始化失败处理
}
```

### 2. 基本功能

```c
// 设置LED配置
unit_hexstep_set_led_config(&hexstep_dev, config);

// 设置LED亮度
unit_hexstep_set_led_brightness(&hexstep_dev, brightness);

// 获取开关状态
uint8_t state;
unit_hexstep_get_switch_state(&hexstep_dev, &state);

// 设置RGB颜色
unit_hexstep_set_rgb(&hexstep_dev, r, g, b);

// 保存配置到Flash
unit_hexstep_save_to_flash(&hexstep_dev);

// 获取固件版本
uint8_t version;
unit_hexstep_get_version(&hexstep_dev, &version);
```

## 回调函数实现示例

以下是回调函数实现的示例（需根据实际平台进行适配）：

```c
// ESP32平台I2C读寄存器实现示例
int esp32_i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // 发送寄存器地址
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    
    // 读取数据
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
    if (len > 1) {
        i2c_master_read(cmd, data, len - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data + len - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    
    return (ret == ESP_OK) ? 0 : -1;
}

// ESP32平台I2C写寄存器实现示例
int esp32_i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    
    return (ret == ESP_OK) ? 0 : -1;
}
```

## 注意事项

- 使用前必须先初始化设备并设置有效的回调函数
- 所有通信函数都会在执行前检查回调函数是否已正确初始化
- 回调函数需要根据实际使用的硬件平台和I2C驱动进行适配 