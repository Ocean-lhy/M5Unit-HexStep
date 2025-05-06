#ifndef UNIT_HEXSTEP_H
#define UNIT_HEXSTEP_H

#include <stdint.h>
#include <stdbool.h>
#include "i2c_bus.h"
#define UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS 0x48

#define UNIT_HEXSTEP_REG_VALUE          0x00
#define UNIT_HEXSTEP_REG_LED_CONFIG     0x10
#define UNIT_HEXSTEP_REG_LED_BRIGHTNESS 0x20
#define UNIT_HEXSTEP_REG_SWITCH         0x30
#define UNIT_HEXSTEP_REG_RGB_CONFIG     0x40
#define UNIT_HEXSTEP_REG_RGB_BRIGHTNESS 0x41
#define UNIT_HEXSTEP_REG_RGB_VALUE      0x50
#define UNIT_HEXSTEP_REG_R_VALUE        0x50
#define UNIT_HEXSTEP_REG_G_VALUE        0x51
#define UNIT_HEXSTEP_REG_B_VALUE        0x52
#define UNIT_HEXSTEP_REG_SAVE_FLASH     0xF0
#define UNIT_HEXSTEP_REG_VERSION        0xFE
#define UNIT_HEXSTEP_REG_ADDRESS        0xFF

#define UNIT_HEXSTEP_REG_RGB_DEMO       0x70

// 回调函数类型定义
typedef int (*unit_hexstep_read_reg_cb_t)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);
typedef int (*unit_hexstep_write_reg_cb_t)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);

// 驱动配置结构体
typedef struct {
    uint8_t dev_addr;                        // 设备I2C地址
    unit_hexstep_read_reg_cb_t read_reg_cb;  // 读寄存器回调函数
    unit_hexstep_write_reg_cb_t write_reg_cb; // 写寄存器回调函数
} unit_hexstep_t;

// 函数声明
int unit_hexstep_init(unit_hexstep_t *dev, uint8_t dev_addr, 
                     unit_hexstep_read_reg_cb_t read_reg_cb,
                     unit_hexstep_write_reg_cb_t write_reg_cb);


// 功能函数
int unit_hexstep_get_value(unit_hexstep_t *dev, uint8_t *value);

int unit_hexstep_set_led_config(unit_hexstep_t *dev, uint8_t config);
int unit_hexstep_get_led_config(unit_hexstep_t *dev, uint8_t *config);
int unit_hexstep_set_led_brightness(unit_hexstep_t *dev, uint8_t brightness);
int unit_hexstep_get_led_brightness(unit_hexstep_t *dev, uint8_t *brightness);

int unit_hexstep_set_switch_state(unit_hexstep_t *dev, uint8_t state);
int unit_hexstep_get_switch_state(unit_hexstep_t *dev, uint8_t *state);

int unit_hexstep_set_rgb_config(unit_hexstep_t *dev, uint8_t config);
int unit_hexstep_get_rgb_config(unit_hexstep_t *dev, uint8_t *config);
int unit_hexstep_set_rgb_brightness(unit_hexstep_t *dev, uint8_t brightness);
int unit_hexstep_get_rgb_brightness(unit_hexstep_t *dev, uint8_t *brightness);
int unit_hexstep_set_rgb(unit_hexstep_t *dev, uint8_t r, uint8_t g, uint8_t b);
int unit_hexstep_get_rgb(unit_hexstep_t *dev, uint8_t *r, uint8_t *g, uint8_t *b);
int unit_hexstep_set_r_value(unit_hexstep_t *dev, uint8_t r);
int unit_hexstep_set_g_value(unit_hexstep_t *dev, uint8_t g);
int unit_hexstep_set_b_value(unit_hexstep_t *dev, uint8_t b);

int unit_hexstep_save_to_flash(unit_hexstep_t *dev, uint8_t save);
int unit_hexstep_get_version(unit_hexstep_t *dev, uint8_t *version);

int unit_hexstep_get_address(unit_hexstep_t *dev, uint8_t *address);
int unit_hexstep_set_address(unit_hexstep_t *dev, uint8_t address);

int unit_hexstep_set_default_config(unit_hexstep_t *dev);

void unit_hexstep_test_case_1(unit_hexstep_t *dev);
void unit_hexstep_test_case_2(unit_hexstep_t *dev);
void unit_hexstep_test_case_3(unit_hexstep_t *dev);
void unit_hexstep_test_case_4(unit_hexstep_t *dev);
void unit_hexstep_test_case_5(unit_hexstep_t *dev);
void unit_hexstep_test_case_6(unit_hexstep_t *dev);
void unit_hexstep_test_case_7(unit_hexstep_t *dev);
void unit_hexstep_test_case_8(unit_hexstep_t *dev);
void unit_hexstep_test_case_9(unit_hexstep_t *dev);
void unit_hexstep_test_case_10(unit_hexstep_t *dev);
void unit_hexstep_test_case_11(unit_hexstep_t *dev, i2c_bus_handle_t i2c_handle);
void unit_hexstep_test_case_press(unit_hexstep_t *dev);

void unit_hexstep_simple_demo(unit_hexstep_t *dev);

#endif
