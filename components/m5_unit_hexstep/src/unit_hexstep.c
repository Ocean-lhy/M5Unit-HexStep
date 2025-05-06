#include "../include/unit_hexstep.h"
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
// 基本读写功能
static int unit_hexstep_read_reg(unit_hexstep_t *dev, uint8_t reg_addr, uint8_t *data, uint8_t len);
static int unit_hexstep_write_reg(unit_hexstep_t *dev, uint8_t reg_addr, uint8_t *data, uint8_t len);

// 打印寄存器值
void unit_hexstep_print_reg(unit_hexstep_t *dev)
{
    ESP_LOGI("HEXSTEP", "---------------------------");
    uint8_t value = 0;
    unit_hexstep_get_value(dev, &value);
    ESP_LOGI("HEXSTEP", "旋钮编码器值: 0x%02X", value);
    uint8_t led_config = 0;
    unit_hexstep_get_led_config(dev, &led_config);
    ESP_LOGI("HEXSTEP", "LED 延时: %d秒", led_config);
    uint8_t led_brightness = 0;
    unit_hexstep_get_led_brightness(dev, &led_brightness);
    ESP_LOGI("HEXSTEP", "LED 亮度: %d", led_brightness);
    uint8_t switch_state = 0;
    unit_hexstep_get_switch_state(dev, &switch_state);
    ESP_LOGI("HEXSTEP", "旋转方向: %s", switch_state == 0 ? "顺时针" : "逆时针");
    uint8_t rgb_config = 0;
    unit_hexstep_get_rgb_config(dev, &rgb_config);
    ESP_LOGI("HEXSTEP", "RGB配置: %s", rgb_config == 0 ? "关闭" : "开启");
    uint8_t rgb_brightness = 0;
    unit_hexstep_get_rgb_brightness(dev, &rgb_brightness);
    ESP_LOGI("HEXSTEP", "RGB 亮度: %d", rgb_brightness);
    uint8_t r = 0, g = 0, b = 0;
    unit_hexstep_get_rgb(dev, &r, &g, &b);
    ESP_LOGI("HEXSTEP", "RGB 值: R=%d, G=%d, B=%d", r, g, b);
    uint8_t version = 0;
    unit_hexstep_get_version(dev, &version);
    ESP_LOGI("HEXSTEP", "版本号: 0x%02X", version);
    uint8_t address = 0;
    unit_hexstep_get_address(dev, &address);
    ESP_LOGI("HEXSTEP", "设备地址: 0x%02X", address);
    
    ESP_LOGI("HEXSTEP", "---------------------------");
}
/**
 * @brief 初始化HexStep驱动
 * 
 * @param dev HexStep设备句柄
 * @param dev_addr 设备I2C地址
 * @param read_reg_cb 读寄存器回调函数
 * @param write_reg_cb 写寄存器回调函数
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_init(unit_hexstep_t *dev, uint8_t dev_addr, 
                     unit_hexstep_read_reg_cb_t read_reg_cb,
                     unit_hexstep_write_reg_cb_t write_reg_cb)
{
    if (dev == NULL || read_reg_cb == NULL || write_reg_cb == NULL) {
        return -1;
    }

    memset(dev, 0, sizeof(unit_hexstep_t));
    dev->dev_addr = dev_addr;
    dev->read_reg_cb = read_reg_cb;
    dev->write_reg_cb = write_reg_cb;
    unit_hexstep_print_reg(dev);
    return 0;
}

/**
 * @brief 检查回调函数是否已初始化
 * 
 * @param dev HexStep设备句柄
 * @return int 0-已初始化，非0-未初始化
 */
static int unit_hexstep_check_callbacks(unit_hexstep_t *dev)
{
    if (dev == NULL || dev->read_reg_cb == NULL || dev->write_reg_cb == NULL) {
        return -1;
    }
    return 0;
}

/**
 * @brief 读取寄存器
 * 
 * @param dev HexStep设备句柄
 * @param reg_addr 寄存器地址
 * @param data 数据缓冲区
 * @param len 数据长度
 * @return int 0-成功，非0-失败
 */
static int unit_hexstep_read_reg(unit_hexstep_t *dev, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    if (unit_hexstep_check_callbacks(dev) != 0 || data == NULL) {
        return -1;
    }
    
    return dev->read_reg_cb(dev->dev_addr, reg_addr, data, len);
}

/**
 * @brief 写入寄存器
 * 
 * @param dev HexStep设备句柄
 * @param reg_addr 寄存器地址
 * @param data 数据缓冲区
 * @param len 数据长度
 * @return int 0-成功，非0-失败
 */
static int unit_hexstep_write_reg(unit_hexstep_t *dev, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    if (unit_hexstep_check_callbacks(dev) != 0 || data == NULL) {
        return -1;
    }
    
    return dev->write_reg_cb(dev->dev_addr, reg_addr, data, len);
}

/**
 * @brief 获取旋钮编码器值
 * 
 * @param dev HexStep设备句柄
 * @param value 0x0-0xF
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_get_value(unit_hexstep_t *dev, uint8_t *value)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_VALUE, value, 1);
}

/**
 * @brief 设置LED配置
 * 
 * @param dev HexStep设备句柄
 * @param config LED配置 0x01-0xFE数码管息屏时间，单位秒；0x00数码管常灭；0xFF数码管常亮
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_set_led_config(unit_hexstep_t *dev, uint8_t config)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_LED_CONFIG, &config, 1);
}
int unit_hexstep_get_led_config(unit_hexstep_t *dev, uint8_t *config)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_LED_CONFIG, config, 1);
}
/**
 * @brief 设置LED亮度
 * 
 * @param dev HexStep设备句柄
 * @param brightness LED亮度 0-100
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_set_led_brightness(unit_hexstep_t *dev, uint8_t brightness)
{
    if (brightness > 100) brightness = 100;
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_LED_BRIGHTNESS, &brightness, 1);
}
int unit_hexstep_get_led_brightness(unit_hexstep_t *dev, uint8_t *brightness)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_LED_BRIGHTNESS, brightness, 1);
}

/**
 * @brief 设置旋钮方向
 * 
 * @param dev HexStep设备句柄
 * @param state 开关状态0-顺时针，1-逆时针
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_get_switch_state(unit_hexstep_t *dev, uint8_t *state)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_SWITCH, state, 1);
}
int unit_hexstep_set_switch_state(unit_hexstep_t *dev, uint8_t state)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_SWITCH, &state, 1);
}

/**
 * @brief 设置RGB配置
 * 
 * @param dev HexStep设备句柄
 * @param config RGB配置 0-关闭，1-开启
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_set_rgb_config(unit_hexstep_t *dev, uint8_t config)
{
    int ret = unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_RGB_CONFIG, &config, 1);
    return ret;
}
int unit_hexstep_get_rgb_config(unit_hexstep_t *dev, uint8_t *config)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_RGB_CONFIG, config, 1);
}
/**
 * @brief 设置RGB亮度
 * 
 * @param dev HexStep设备句柄
 * @param brightness RGB亮度 0-100
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_set_rgb_brightness(unit_hexstep_t *dev, uint8_t brightness)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_RGB_BRIGHTNESS, &brightness, 1);
}
int unit_hexstep_get_rgb_brightness(unit_hexstep_t *dev, uint8_t *brightness)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_RGB_BRIGHTNESS, brightness, 1);
}
/**
 * @brief 设置RGB值
 * 
 * @param dev HexStep设备句柄
 * @param r 红色值
 * @param g 绿色值
 * @param b 蓝色值
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_set_rgb(unit_hexstep_t *dev, uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t rgb[3] = {r, g, b};
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_RGB_VALUE, rgb, 3);
}
int unit_hexstep_get_rgb(unit_hexstep_t *dev, uint8_t *r, uint8_t *g, uint8_t *b)
{
    uint8_t rgb[3];
    int ret = unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_RGB_VALUE, rgb, 3);
    if (ret != 0) {
        return ret;
    }
    *r = rgb[0];
    *g = rgb[1];
    *b = rgb[2];
    return 0;
}
int unit_hexstep_set_r_value(unit_hexstep_t *dev, uint8_t r)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_R_VALUE, &r, 1);
}
int unit_hexstep_set_g_value(unit_hexstep_t *dev, uint8_t g)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_G_VALUE, &g, 1);
}
int unit_hexstep_set_b_value(unit_hexstep_t *dev, uint8_t b)
{
    return unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_B_VALUE, &b, 1);
}

/**
 * @brief 保存配置到Flash
 * 
 * @param dev HexStep设备句柄
 * @param save 1-保存LED配置，2-保存RGB配置
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_save_to_flash(unit_hexstep_t *dev, uint8_t save)
{
    int ret = unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_SAVE_FLASH, &save, 1);
    vTaskDelay(100); // 等待保存完成
    return ret;
}

/**
 * @brief 获取固件版本
 * 
 * @param dev HexStep设备句柄
 * @param version 版本号缓冲区
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_get_version(unit_hexstep_t *dev, uint8_t *version)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_VERSION, version, 1);
}

/**
 * @brief 获取设备地址
 * 
 * @param dev HexStep设备句柄
 * @param address 地址缓冲区
 * @return int 0-成功，非0-失败
 */
int unit_hexstep_get_address(unit_hexstep_t *dev, uint8_t *address)
{
    return unit_hexstep_read_reg(dev, UNIT_HEXSTEP_REG_ADDRESS, address, 1);
}
int unit_hexstep_set_address(unit_hexstep_t *dev, uint8_t address)
{
    int ret = unit_hexstep_write_reg(dev, UNIT_HEXSTEP_REG_ADDRESS, &address, 1);
    vTaskDelay(200); // 等待保存完成
    return ret;
}

int unit_hexstep_set_default_config(unit_hexstep_t *dev)
{
    unit_hexstep_set_led_config(dev, 0xFE);
    unit_hexstep_set_led_brightness(dev, 50);
    unit_hexstep_set_switch_state(dev, 1);
    unit_hexstep_set_rgb_config(dev, 1);
    unit_hexstep_set_rgb_brightness(dev, 50);
    unit_hexstep_set_rgb(dev, 0, 0, 0);
    unit_hexstep_save_to_flash(dev, 1);
    unit_hexstep_save_to_flash(dev, 2);
    unit_hexstep_set_address(dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS);
    esp_restart();
    return 0;
}