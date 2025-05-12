#include <stdio.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "bsp/esp-bsp.h"
#include "esp_log.h"
#include "unit_hexstep.h"
#include "i2c_bus.h"
#include "config.h"

#include "gui_guider.h"

static const char *TAG = "HexStep";

unit_hexstep_t hexstep_dev;

i2c_bus_handle_t i2c_handle;
i2c_bus_device_handle_t hexstep_dev_handle;

lv_ui guider_ui;

QueueHandle_t lv_command_queue;

static int i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    int ret = 1;
    for (int i = 0; i < 3; i++) // retry 3 times
    {
        ret = i2c_bus_read_bytes(hexstep_dev_handle, reg_addr, len, data);
        // ESP_LOGI(TAG, "读取寄存器: 0x%02X, 数据: 0x%02X\n", reg_addr, data[0]);
        if (ret == 0)
        {
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    return ret;
}

static int i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    int ret = 1;
    for (int i = 0; i < 3; i++) // retry 3 times
    {
        ret = i2c_bus_write_bytes(hexstep_dev_handle, reg_addr, len, data);
        // ESP_LOGI(TAG, "写入寄存器: 0x%02X, 数据: 0x%02X\n", reg_addr, data[0]);
        if (ret == 0)
        {
            break;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    return ret;
}

void unit_hexstep_command_handler(void *arg)
{
    uint16_t command;
    uint8_t rgb_demo_flag = 0;
    while (1) {
        if (rgb_demo_flag == 1) 
        {
            // RGB彩虹渐变效果
            static uint8_t hue = 0;
            float h = hue / 255.0f;
            hue++;

            // HSV转RGB
            float s = 1.0f;
            float v = 1.0f;
            float c = v * s;
            float x = c * (1 - fabsf(fmodf(h * 6, 2) - 1));
            float m = v - c;

            float r, g, b;
            if(h < 1.0f/6) {
                r = c; g = x; b = 0;
            } else if(h < 2.0f/6) {
                r = x; g = c; b = 0;
            } else if(h < 3.0f/6) {
                r = 0; g = c; b = x;
            } else if(h < 4.0f/6) {
                r = 0; g = x; b = c;
            } else if(h < 5.0f/6) {
                r = x; g = 0; b = c;
            } else {
                r = c; g = 0; b = x;
            }

            uint8_t rgb_value[3];
            rgb_value[0] = (r + m) * 255;
            rgb_value[1] = (g + m) * 255; 
            rgb_value[2] = (b + m) * 255;

            unit_hexstep_set_rgb(&hexstep_dev, rgb_value[0], rgb_value[1], rgb_value[2]);
        }
        if (xQueueReceive(lv_command_queue, &command, 10) == pdPASS) 
        {
            ESP_LOGI(TAG, "收到命令: 0x%02X", command);
            uint8_t reg_addr = command & 0xFF;
            uint8_t data = (command >> 8) & 0xFF;
            if (reg_addr == UNIT_HEXSTEP_REG_RGB_DEMO)
            {
                rgb_demo_flag = 1;
                ESP_LOGI(TAG, "RGB演示模式");
                continue;
            }
            switch (reg_addr)
            {
                case UNIT_HEXSTEP_REG_LED_CONFIG:
                    unit_hexstep_set_led_config(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_LED_BRIGHTNESS:
                    unit_hexstep_set_led_brightness(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_SWITCH:
                    unit_hexstep_set_switch_state(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_RGB_CONFIG:
                    unit_hexstep_set_rgb_config(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_RGB_BRIGHTNESS:
                    unit_hexstep_set_rgb_brightness(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_R_VALUE:
                    rgb_demo_flag = 0;
                    unit_hexstep_set_r_value(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_G_VALUE:
                    rgb_demo_flag = 0;
                    unit_hexstep_set_g_value(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_B_VALUE:
                    rgb_demo_flag = 0;
                    unit_hexstep_set_b_value(&hexstep_dev, data);
                    break;
                case UNIT_HEXSTEP_REG_SAVE_FLASH:
                    unit_hexstep_save_to_flash(&hexstep_dev, data);
                    break;
                default:
                    ESP_LOGE(TAG, "无效命令: 0x%02X", reg_addr);
                    break;
            }
        }
    }
}

static void hexstep_task(void *arg)
{
    while (1) {
        // unit_hexstep_test_case_1(&hexstep_dev);
        // unit_hexstep_test_case_2(&hexstep_dev);
        // unit_hexstep_test_case_3(&hexstep_dev);
        // unit_hexstep_test_case_4(&hexstep_dev);
        // unit_hexstep_test_case_5(&hexstep_dev);
        // unit_hexstep_test_case_6(&hexstep_dev);
        // unit_hexstep_test_case_7(&hexstep_dev);
        // unit_hexstep_test_case_9(&hexstep_dev);
        // unit_hexstep_test_case_10(&hexstep_dev);
        // unit_hexstep_test_case_11(&hexstep_dev, i2c_handle);
        // unit_hexstep_test_case_press(&hexstep_dev);
        // unit_hexstep_simple_demo(&hexstep_dev);
        unit_hexstep_command_handler(NULL);
        vTaskDelay(10 / portTICK_PERIOD_MS); // 10ms延时
    }
}

static void guider_task(void *arg)
{
    uint8_t value, led_config, led_brightness, led_switch, rgb_config, rgb_brightness, r_value, g_value, b_value, address, version;
    int ret = unit_hexstep_get_value(&hexstep_dev, &value);
    ret |= unit_hexstep_get_led_config(&hexstep_dev, &led_config);
    ret |= unit_hexstep_get_led_brightness(&hexstep_dev, &led_brightness);
    ret |= unit_hexstep_get_switch_state(&hexstep_dev, &led_switch);
    ret |= unit_hexstep_get_rgb_config(&hexstep_dev, &rgb_config);
    ret |= unit_hexstep_get_rgb_brightness(&hexstep_dev, &rgb_brightness);
    ret |= unit_hexstep_get_rgb(&hexstep_dev, &r_value, &g_value, &b_value);
    ret |= unit_hexstep_get_address(&hexstep_dev, &address);
    ret |= unit_hexstep_get_version(&hexstep_dev, &version);
    bsp_display_lock(0);
    lv_obj_clear_flag(guider_ui.screen, LV_OBJ_FLAG_SCROLLABLE);
    // update data
    if (ret != 0) 
    {
        lv_label_set_text(guider_ui.screen_label_value, "ERR");
    }
    else
    {
        char text[32] = {0};
        snprintf(text, sizeof(text), "%01X", value);
        lv_label_set_text(guider_ui.screen_label_value, text);
        lv_meter_set_indicator_value(guider_ui.screen_meter_1, guider_ui.screen_meter_1_scale_0_ndline_0, led_switch ? value : 16-value);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "led sleep %ds", led_config);
        lv_label_set_text(guider_ui.screen_label_led_config, text);
        lv_slider_set_value(guider_ui.screen_slider_led_config, led_config, LV_ANIM_OFF);
        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "brightness %d%%", led_brightness);
        lv_label_set_text(guider_ui.screen_label_led_brightness, text);
        lv_slider_set_value(guider_ui.screen_slider_led_brightness, led_brightness, LV_ANIM_OFF);

        if (led_switch == 1)
        {
            lv_obj_add_state(guider_ui.screen_sw_reversal, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_flag(guider_ui.screen_sw_reversal, LV_STATE_CHECKED);
        }

        if (rgb_config == 1)
        {
            lv_obj_add_state(guider_ui.screen_sw_rgb, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_flag(guider_ui.screen_sw_rgb, LV_STATE_CHECKED);
        }

        lv_slider_set_value(guider_ui.screen_slider_rgb, rgb_brightness, LV_ANIM_OFF);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "R: %d", r_value);
        lv_label_set_text(guider_ui.screen_label_R, text);
        lv_slider_set_value(guider_ui.screen_slider_R, r_value, LV_ANIM_OFF);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "G: %d", g_value);
        lv_label_set_text(guider_ui.screen_label_G, text);
        lv_slider_set_value(guider_ui.screen_slider_G, g_value, LV_ANIM_OFF);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "B: %d", b_value);
        lv_label_set_text(guider_ui.screen_label_B, text);
        lv_slider_set_value(guider_ui.screen_slider_B, b_value, LV_ANIM_OFF);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "addr: 0x%02X", address);
        lv_label_set_text(guider_ui.screen_label_addr, text);

        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "version: %02X", version);
        lv_label_set_text(guider_ui.screen_label_version, text);
    }
    bsp_display_unlock();
    uint8_t last_value = value;
    while (1) 
    {
        unit_hexstep_get_value(&hexstep_dev, &value);
        unit_hexstep_get_switch_state(&hexstep_dev, &led_switch);
        if (last_value != value)
        {
            bsp_display_lock(0);
            char text[32] = {0};
            snprintf(text, sizeof(text), "%01X", value);
            lv_label_set_text(guider_ui.screen_label_value, text);
            lv_label_set_text(guider_ui.screen_label_value_2, text);
            lv_meter_set_indicator_value(guider_ui.screen_meter_1, guider_ui.screen_meter_1_scale_0_ndline_0, led_switch ? value : 16-value);
            last_value = value;
            bsp_display_unlock();
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "初始化Unit-HexStep");

    lv_command_queue = xQueueCreate(10, sizeof(uint16_t));
    if (lv_command_queue == NULL) {
        ESP_LOGE(TAG, "创建命令队列失败");
        return;
    }

    bsp_i2c_init();

    bsp_display_start();
    bsp_display_lock(0);
    bsp_display_backlight_on();

    setup_ui(&guider_ui);

    bsp_display_unlock();

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PORT_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = PORT_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = PORT_FREQ,
    };
    i2c_handle = i2c_bus_create(PORT_NUM, &conf);
    uint8_t address = 0;
    i2c_bus_scan(i2c_handle, &address, 1);
    hexstep_dev_handle = i2c_bus_device_create(i2c_handle, address, 0);


    int ret = unit_hexstep_init(&hexstep_dev, address, i2c_read_reg, i2c_write_reg);
    if (ret != 0) {
        ESP_LOGE(TAG, "HexStep初始化失败");
        return;
    }
    
    ESP_LOGI(TAG, "配置HexStep设备");
    
    // unit_hexstep_set_led_config(&hexstep_dev, 0xFE);
    
    // unit_hexstep_set_led_brightness(&hexstep_dev, 50);
    
    // unit_hexstep_set_rgb_config(&hexstep_dev, 0);
    
    // unit_hexstep_set_rgb_brightness(&hexstep_dev, 50);
    
    // unit_hexstep_set_rgb(&hexstep_dev, 0, 0, 0);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 1);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 2);

    // unit_hexstep_set_address(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS);

    // unit_hexstep_set_default_config(&hexstep_dev);

    ESP_LOGI(TAG, "HexStep初始化完成");
    
    xTaskCreate(hexstep_task, "hexstep_task", 4096, NULL, 10, NULL);
    xTaskCreate(guider_task, "guider_task", 4096, NULL, 10, NULL);
}

