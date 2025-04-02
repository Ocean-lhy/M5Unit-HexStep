#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "bsp/esp-bsp.h"
#include "esp_log.h"
#include "unit_hexstep.h"
#include "i2c_bus.h"

static const char *TAG = "HexStep";

#define PORT_NUM I2C_NUM_0
#define PORT_SCL 1
#define PORT_SDA 2
#define PORT_FREQ 400000

unit_hexstep_t hexstep_dev;

i2c_bus_handle_t i2c_handle;
i2c_bus_device_handle_t hexstep_dev_handle;

static int i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    int ret = i2c_bus_read_bytes(hexstep_dev_handle, reg_addr, len, data);
    return ret;
}

static int i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    int ret = i2c_bus_write_bytes(hexstep_dev_handle, reg_addr, len, data);
    return ret;
}

static void hexstep_task(void *arg)
{
    uint8_t value, last_value = 0;
    
    while (1) {
        if (unit_hexstep_get_value(&hexstep_dev, &value) == 0 && value != last_value) 
        {
            ESP_LOGI(TAG, "旋钮编码器值: 0x%02X", value);
            last_value = value;
            switch (value & 0x0F) {
                case 0:
                    unit_hexstep_set_rgb(&hexstep_dev, 255, 0, 0); // 红色
                    ESP_LOGI(TAG, "红色");
                    break;
                case 1:
                    unit_hexstep_set_rgb(&hexstep_dev, 0, 255, 0); // 绿色
                    ESP_LOGI(TAG, "绿色");
                    break;
                case 2:
                    unit_hexstep_set_rgb(&hexstep_dev, 0, 0, 255); // 蓝色
                    ESP_LOGI(TAG, "蓝色");
                    break;
                case 3:
                    unit_hexstep_set_rgb(&hexstep_dev, 255, 255, 0); // 黄色
                    ESP_LOGI(TAG, "黄色");
                    break;
                case 4:
                    unit_hexstep_set_rgb(&hexstep_dev, 255, 0, 255); // 紫色
                    ESP_LOGI(TAG, "紫色");
                    break;
                case 5:
                    unit_hexstep_set_rgb(&hexstep_dev, 0, 255, 255); // 青色
                    ESP_LOGI(TAG, "青色");
                    break;
                case 6:
                    unit_hexstep_set_rgb(&hexstep_dev, 255, 128, 0); // 橙色
                    ESP_LOGI(TAG, "橙色");
                    break;
                default:
                    unit_hexstep_set_rgb(&hexstep_dev, rand() % 256, rand() % 256, rand() % 256); // 随机颜色
                    ESP_LOGI(TAG, "随机颜色");
                    break;
            }
        }
        
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 100ms延时
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "初始化Unit-HexStep");

    bsp_i2c_init();

    bsp_display_start();
    bsp_display_lock(0);
    bsp_display_backlight_on();
    bsp_display_unlock();

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PORT_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = PORT_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = PORT_FREQ,
    };
    i2c_handle = i2c_bus_create(PORT_NUM, &conf);
    i2c_bus_scan(i2c_handle, NULL, 1);
    hexstep_dev_handle = i2c_bus_device_create(i2c_handle, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, 0);


    int ret = unit_hexstep_init(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, i2c_read_reg, i2c_write_reg);
    if (ret != 0) {
        ESP_LOGE(TAG, "HexStep初始化失败");
        return;
    }
    
    ESP_LOGI(TAG, "配置HexStep设备");
    
    // unit_hexstep_set_led_config(&hexstep_dev, 0xFE);
    
    // unit_hexstep_set_led_brightness(&hexstep_dev, 50);
    
    // unit_hexstep_set_rgb_config(&hexstep_dev, 1);
    
    // unit_hexstep_set_rgb_brightness(&hexstep_dev, 50);
    
    // unit_hexstep_set_rgb(&hexstep_dev, 0, 0, 0);

    // unit_hexstep_set_sensitivity(&hexstep_dev, 100);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 1);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 2);
    
    xTaskCreate(hexstep_task, "hexstep_task", 4096, NULL, 10, NULL);
    
    ESP_LOGI(TAG, "HexStep初始化完成");
}

