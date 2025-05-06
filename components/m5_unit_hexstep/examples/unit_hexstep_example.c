#include <stdio.h>
#include "../include/unit_hexstep.h"

// 示例I2C读寄存器回调函数
static int example_i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    printf("读取设备地址: 0x%02X, 寄存器地址: 0x%02X, 长度: %d\n", dev_addr, reg_addr, len);
    
    // 在实际应用中，这里应该是真正的I2C读取操作
    // 这里仅为演示，填充一些示例数据
    if (data != NULL && len > 0) {
        for (int i = 0; i < len; i++) {
            data[i] = i + 1;  // 示例数据
        }
    }
    
    return 0;  // 返回0表示成功
}

// 示例I2C写寄存器回调函数
static int example_i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    printf("写入设备地址: 0x%02X, 寄存器地址: 0x%02X, 长度: %d, 数据: ", dev_addr, reg_addr, len);
    
    // 在实际应用中，这里应该是真正的I2C写入操作
    // 这里仅为演示，打印要写入的数据
    if (data != NULL && len > 0) {
        for (int i = 0; i < len; i++) {
            printf("0x%02X ", data[i]);
        }
    }
    printf("\n");
    
    return 0;  // 返回0表示成功
}

int main()
{
    int ret;
    unit_hexstep_t hexstep_dev;
    uint8_t version;
    uint8_t switch_state;
    
    printf("HexStep驱动示例开始\n");
    
    // 初始化HexStep设备
    ret = unit_hexstep_init(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, 
                           example_i2c_read_reg, example_i2c_write_reg);
    if (ret != 0) {
        printf("HexStep初始化失败\n");
        return -1;
    }
    
    printf("HexStep初始化成功\n");
    
    // 获取固件版本
    ret = unit_hexstep_get_version(&hexstep_dev, &version);
    if (ret == 0) {
        printf("固件版本: 0x%02X\n", version);
    } else {
        printf("获取固件版本失败\n");
    }
    
    // 设置LED配置
    ret = unit_hexstep_set_led_config(&hexstep_dev, 0x01);
    if (ret != 0) {
        printf("设置LED配置失败\n");
    }
    
    // 设置LED亮度
    ret = unit_hexstep_set_led_brightness(&hexstep_dev, 0x80);
    if (ret != 0) {
        printf("设置LED亮度失败\n");
    }
    
    // 获取开关状态
    ret = unit_hexstep_get_switch_state(&hexstep_dev, &switch_state);
    if (ret == 0) {
        printf("开关状态: 0x%02X\n", switch_state);
    } else {
        printf("获取开关状态失败\n");
    }
    
    // 设置RGB颜色
    ret = unit_hexstep_set_rgb(&hexstep_dev, 0xFF, 0x00, 0x00);  // 红色
    if (ret != 0) {
        printf("设置RGB颜色失败\n");
    }
    
    // 保存到Flash - 保存LED配置
    ret = unit_hexstep_save_to_flash(&hexstep_dev, 1);
    if (ret != 0) {
        printf("保存LED配置到Flash失败\n");
    }
    
    // 保存到Flash - 保存RGB配置
    ret = unit_hexstep_save_to_flash(&hexstep_dev, 2);
    if (ret != 0) {
        printf("保存RGB配置到Flash失败\n");
    }
    
    printf("HexStep驱动示例结束\n");
    
    return 0;
} 