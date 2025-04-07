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
#include "iot_button.h"

#include "gui_guider.h"

static const char *TAG = "HexStep";

unit_hexstep_t hexstep_dev;

i2c_bus_handle_t i2c_handle;
i2c_bus_device_handle_t hexstep_dev_handle;

lv_ui guider_ui;

QueueHandle_t lv_command_queue;

button_handle_t btn_left = NULL;
button_handle_t btn_middle = NULL;
button_handle_t btn_right = NULL;

uint8_t btn_left_press_flag = 0;
uint8_t btn_middle_press_flag = 0;
uint8_t btn_right_press_flag = 0;

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
                case UNIT_HEXSTEP_REG_SENSITIVITY:
                    unit_hexstep_set_sensitivity(&hexstep_dev, data);
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
        // unit_hexstep_test_case_8(&hexstep_dev);
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
    uint8_t value, led_config, led_brightness, led_switch, rgb_config, rgb_brightness, r_value, g_value, b_value, sensitivity, address, version;
    int ret = 0;
    unit_hexstep_get_value(&hexstep_dev, &value);
    ret |= unit_hexstep_get_led_config(&hexstep_dev, &led_config);
    ret |= unit_hexstep_get_led_brightness(&hexstep_dev, &led_brightness);
    ret |= unit_hexstep_get_switch_state(&hexstep_dev, &led_switch);
    ret |= unit_hexstep_get_rgb_config(&hexstep_dev, &rgb_config);
    ret |= unit_hexstep_get_rgb_brightness(&hexstep_dev, &rgb_brightness);
    ret |= unit_hexstep_get_rgb(&hexstep_dev, &r_value, &g_value, &b_value);
    ret |= unit_hexstep_get_sensitivity(&hexstep_dev, &sensitivity);
    ret |= unit_hexstep_get_address(&hexstep_dev, &address);
    ret |= unit_hexstep_get_version(&hexstep_dev, &version);
    uint8_t last_value = value;
    uint8_t test_index = 0; // 0: 设备检测中 1: 设备测试完成 2: 准备开始测试 255: 测试中断
    while (1) 
    {
        // find device
        while (1)
        {
            ret = unit_hexstep_get_address(&hexstep_dev, &address);
            ret |= unit_hexstep_get_version(&hexstep_dev, &version);
            if (ret != 0)
            {
                ESP_LOGE(TAG, "获取地址或版本失败");
                bsp_display_lock(0);
                lv_obj_set_style_bg_color(guider_ui.screen_detect, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.screen_detect_label_detect, "设备检测中...\n\n设备地址：ERR\n\n固件版本：ERR\n\n请将设备插入PORT.A口");
                bsp_display_unlock();
                test_index = 0;
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            else
            if (test_index == 1)
            {
                bsp_display_lock(0);
                lv_obj_set_style_bg_color(guider_ui.screen_detect, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.screen_detect_label_detect, "设备测试完成\n\n请拔下设备更换待测设备");
                bsp_display_unlock();
            }
            else
            if (test_index == 255)
            {
                ESP_LOGI(TAG, "测试中断");
                bsp_display_lock(0);
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_detect, guider_ui.screen_detect_del, &guider_ui.screen_RGB_del, setup_scr_screen_detect, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
                bsp_display_unlock();
                test_index = 0;
            }
            else
            {
                char text[128];
                snprintf(text, sizeof(text), "设备连接成功\n\n设备地址：0x%02X\n\n固件版本：%d\n\n按右键开始测试", address, version);
                bsp_display_lock(0);
                lv_obj_set_style_bg_color(guider_ui.screen_detect, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.screen_detect_label_detect, text);
                bsp_display_unlock();
                test_index = 2;
            }
            if (test_index == 2 && (btn_middle_press_flag == 1 || btn_right_press_flag == 1))
            {
                ESP_LOGI(TAG, "开始测试");
                bsp_display_lock(0);
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_roll, guider_ui.screen_roll_del, &guider_ui.screen_detect_del, setup_scr_screen_roll, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
                bsp_display_unlock();
                break;
            }
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
        // roll test
        ESP_LOGI(TAG, "开始旋钮测试");
        uint8_t last_val = 0;
        uint8_t valid_val = 0; // 记录上一次有效计数的值
        uint8_t total_roll = 0;
        unit_hexstep_set_sensitivity(&hexstep_dev, 100);
        unit_hexstep_get_value(&hexstep_dev, &last_val);
        valid_val = last_val;

        while (1)
        {
            if (btn_left_press_flag == 1)
            {
                ESP_LOGI(TAG, "左键按下，退出测试");
                test_index = 255;
                esp_restart();
            }
            
            ret = unit_hexstep_get_value(&hexstep_dev, &value);
            if (ret != 0)
            {
                ESP_LOGE(TAG, "获取值失败");
                continue;
            }
            
            // 检测到有效递增（顺时针旋转一格）且值必须超过上次有效值
            if (((valid_val == 15 && value == 0) || (value == valid_val + 1)) && 
                (value != last_val)) // 确保与上次读取的值不同
            {
                total_roll++;
                ESP_LOGI(TAG, "检测到有效旋转: %d -> %d, 总计: %d/48", valid_val, value, total_roll);
                valid_val = value; // 更新有效值
                char text[8];
                snprintf(text, sizeof(text), "%d", valid_val);
                lv_label_set_text(guider_ui.screen_roll_label_1, text);
            }
            
            last_val = value; // 记录本次读取的值
            
            bsp_display_lock(0);
            lv_meter_set_indicator_value(guider_ui.screen_roll_meter_roll, guider_ui.screen_roll_meter_roll_scale_0_ndline_0, value);
            
            // 更新进度条，每次旋转增加2个单位
            lv_textprogress_set_value(guider_ui.screen_roll_textprogress_roll, total_roll * 2);
            
            // 检查是否完成三圈
            if (total_roll >= 48)
            {
                ESP_LOGI(TAG, "完成三圈旋转测试");
                lv_textprogress_set_value(guider_ui.screen_roll_textprogress_roll, 100);
                lv_obj_set_style_bg_color(guider_ui.screen_roll, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.screen_roll_label_roll, "旋钮测试完成\n按右键继续下一项测试");
                bsp_display_unlock();
                break;
            }
            
            bsp_display_unlock();
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
        while (1)
        {
            if (btn_right_press_flag == 1 || btn_middle_press_flag == 1)
            {
                bsp_display_lock(0);
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_led, guider_ui.screen_led_del, &guider_ui.screen_roll_del, setup_scr_screen_led, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
                bsp_display_unlock();
                break;
            }
            if (btn_left_press_flag == 1)
            {
                ESP_LOGI(TAG, "左键按下，退出测试");
                test_index = 255;
                esp_restart();
            }
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "开始数码管测试");
        unit_hexstep_set_led_config(&hexstep_dev, 0xFF);
        // led test
        while (1)
        {
            if (btn_left_press_flag == 1)
            {
                ESP_LOGI(TAG, "左键按下，退出测试");
                test_index = 255;
                esp_restart();
            }
            ret = unit_hexstep_get_value(&hexstep_dev, &value);
            if (ret != 0 || btn_left_press_flag == 1)
            {
                ESP_LOGE(TAG, "获取值失败");
                test_index = 255;
                continue;
            }
            bsp_display_lock(0);
            if (value == 8)
            {
                lv_label_set_text(guider_ui.screen_led_label_led_num, "8");
                lv_obj_set_style_bg_color(guider_ui.screen_led, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                led_brightness += 10;
                if (led_brightness > 200)
                {
                    led_brightness = 0;
                }
                lv_slider_set_value(guider_ui.screen_led_slider_led, led_brightness > 100 ? 200-led_brightness : led_brightness, LV_ANIM_OFF);
                lv_label_set_text(guider_ui.screen_led_label_led, "观察数码管亮度效果\n按右键继续下一项测试");
                if (btn_right_press_flag == 1)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_RGB, guider_ui.screen_RGB_del, &guider_ui.screen_led_del, setup_scr_screen_RGB, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
                    bsp_display_unlock();
                    break;
                }
            }
            else
            {
                char text[8];
                snprintf(text, sizeof(text), "%d", value);
                lv_label_set_text(guider_ui.screen_led_label_led_num, text);
                lv_obj_set_style_bg_color(guider_ui.screen_led, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.screen_led_label_led, "将数字旋转到8\n观察数码管亮度效果");
            }
            bsp_display_unlock();
            unit_hexstep_set_led_brightness(&hexstep_dev, led_brightness > 100 ? 200-led_brightness : led_brightness);
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "开始RGB测试");
        unit_hexstep_set_rgb_config(&hexstep_dev, 1);
        unit_hexstep_set_rgb_brightness(&hexstep_dev, 100);
        // rgb test
        uint8_t rgb_index = 0;
        uint8_t rgb_done = 0;
        uint8_t btn_middle_last_state = 0; // 记录中键上一次状态

        while (1)
        {
            if (btn_left_press_flag == 1)
            {
                ESP_LOGI(TAG, "左键按下，退出测试");
                test_index = 255;
                esp_restart();
            }
            
            switch (rgb_index)
            {
                case 0:
                    unit_hexstep_set_rgb(&hexstep_dev, 255, 0, 0);
                    bsp_display_lock(0);
                    lv_led_set_color(guider_ui.screen_RGB_led_RGB, lv_color_hex(0xff0000));
                    bsp_display_unlock();
                    break;
                case 1:
                    unit_hexstep_set_rgb(&hexstep_dev, 0, 255, 0);
                    bsp_display_lock(0);
                    lv_led_set_color(guider_ui.screen_RGB_led_RGB, lv_color_hex(0x00ff00));
                    bsp_display_unlock();
                    break;
                case 2:
                    unit_hexstep_set_rgb(&hexstep_dev, 0, 0, 255);
                    bsp_display_lock(0);
                    lv_led_set_color(guider_ui.screen_RGB_led_RGB, lv_color_hex(0x0000ff));
                    bsp_display_unlock();
                    break;
            }
            
            // 检测按键上升沿：之前未按下，现在按下
            if (btn_middle_press_flag == 1 && btn_middle_last_state == 0)
            {
                rgb_index++;
                if (rgb_index > 2)
                {
                    rgb_index = 0;
                    rgb_done = 1;
                    bsp_display_lock(0);
                    lv_obj_set_style_bg_color(guider_ui.screen_RGB, lv_color_hex(0x009600), LV_PART_MAIN|LV_STATE_DEFAULT);
                    lv_label_set_text(guider_ui.screen_RGB_label_RGB, "RGB测试完成，按右键结束测试\n按中间按键切换RGB颜色");
                    bsp_display_unlock();
                }
            }
            
            // 保存当前按键状态用于下次比较
            btn_middle_last_state = btn_middle_press_flag;
            
            if (rgb_done == 1 && btn_right_press_flag == 1)
            {
                test_index = 1;
                bsp_display_lock(0);
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_detect, guider_ui.screen_detect_del, &guider_ui.screen_RGB_del, setup_scr_screen_detect, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
                bsp_display_unlock();
                break;
            }
            
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // 10ms延时
    }
}

static void button_left_press_down_cb(void *arg, void *data)
{
    btn_left_press_flag = 1;
    ESP_LOGI(TAG, "左键按下");
}

static void button_left_press_up_cb(void *arg, void *data)
{
    btn_left_press_flag = 0;
    ESP_LOGI(TAG, "左键抬起");
}

static void button_middle_press_down_cb(void *arg, void *data)
{
    btn_middle_press_flag = 1;
    ESP_LOGI(TAG, "中键按下");
}

static void button_middle_press_up_cb(void *arg, void *data)
{
    btn_middle_press_flag = 0;
    ESP_LOGI(TAG, "中键抬起");
}

static void button_right_press_down_cb(void *arg, void *data)
{
    btn_right_press_flag = 1;
    ESP_LOGI(TAG, "右键按下");
}

static void button_right_press_up_cb(void *arg, void *data)
{
    btn_right_press_flag = 0;
    ESP_LOGI(TAG, "右键抬起");
}

static void button_init(void)
{
    button_config_t btn_left_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        .gpio_button_config = {
            .gpio_num = PORT_BUTTON_LEFT,
            .active_level = 0,
        },
    };
    
    button_config_t btn_middle_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        .gpio_button_config = {
            .gpio_num = PORT_BUTTON_MIDDLE,
            .active_level = 0,
        },
    };
    
    button_config_t btn_right_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        .gpio_button_config = {
            .gpio_num = PORT_BUTTON_RIGHT,
            .active_level = 0,
        },
    };
    
    btn_left = iot_button_create(&btn_left_cfg);
    btn_middle = iot_button_create(&btn_middle_cfg);
    btn_right = iot_button_create(&btn_right_cfg);
    
    iot_button_register_cb(btn_left, BUTTON_PRESS_DOWN, button_left_press_down_cb, NULL);
    iot_button_register_cb(btn_left, BUTTON_PRESS_UP, button_left_press_up_cb, NULL);
    
    iot_button_register_cb(btn_middle, BUTTON_PRESS_DOWN, button_middle_press_down_cb, NULL);
    iot_button_register_cb(btn_middle, BUTTON_PRESS_UP, button_middle_press_up_cb, NULL);
    
    iot_button_register_cb(btn_right, BUTTON_PRESS_DOWN, button_right_press_down_cb, NULL);
    iot_button_register_cb(btn_right, BUTTON_PRESS_UP, button_right_press_up_cb, NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "初始化Unit-HexStep");

    lv_command_queue = xQueueCreate(10, sizeof(uint16_t));
    if (lv_command_queue == NULL) {
        ESP_LOGE(TAG, "创建命令队列失败");
        return;
    }

    button_init();
    
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
    hexstep_dev_handle = i2c_bus_device_create(i2c_handle, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, 0);


    int ret = unit_hexstep_init(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, i2c_read_reg, i2c_write_reg);
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

    // unit_hexstep_set_sensitivity(&hexstep_dev, 100);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 1);
    
    // unit_hexstep_save_to_flash(&hexstep_dev, 2);

    // unit_hexstep_set_address(&hexstep_dev, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS);

    // unit_hexstep_set_default_config(&hexstep_dev);

    ESP_LOGI(TAG, "HexStep初始化完成");
    
    // xTaskCreate(hexstep_task, "hexstep_task", 4096, NULL, 10, NULL);
    xTaskCreate(guider_task, "guider_task", 10240, NULL, 10, NULL);
}

