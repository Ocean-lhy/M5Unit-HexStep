#include <math.h>
#include "unit_hexstep.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/i2c_master.h"
#include "bsp/esp-bsp.h"
#include "i2c_bus.h"
#include "esp_random.h"
#define TAG "TEST_CASE"

void unit_hexstep_simple_demo(unit_hexstep_t *dev)
{
    static uint8_t value, last_value = 0;
    if (unit_hexstep_get_value(dev, &value) == 0 && value != last_value) 
    {
        ESP_LOGI(TAG, "旋钮编码器值: 0x%02X", value);
        last_value = value;
        switch (value & 0x0F) 
        {
            case 0:
                unit_hexstep_set_rgb(dev, 255, 0, 0); // 红色
                ESP_LOGI(TAG, "红色");
                break;
            case 1:
                unit_hexstep_set_rgb(dev, 0, 255, 0); // 绿色
                ESP_LOGI(TAG, "绿色");
                break;
            case 2:
                unit_hexstep_set_rgb(dev, 0, 0, 255); // 蓝色
                ESP_LOGI(TAG, "蓝色");
                break;
            case 3:
                unit_hexstep_set_rgb(dev, 255, 255, 0); // 黄色
                ESP_LOGI(TAG, "黄色");
                break;
            case 4:
                unit_hexstep_set_rgb(dev, 255, 0, 255); // 紫色
                ESP_LOGI(TAG, "紫色");
                break;
            case 5:
                unit_hexstep_set_rgb(dev, 0, 255, 255); // 青色
                ESP_LOGI(TAG, "青色");
                break;
            case 6:
                unit_hexstep_set_rgb(dev, 255, 128, 0); // 橙色
                ESP_LOGI(TAG, "橙色");
                break;
            default:
                unit_hexstep_set_rgb(dev, esp_random() % 256, esp_random() % 256, esp_random() % 256); // 随机颜色
                ESP_LOGI(TAG, "随机颜色");
                break;
        }
    }
}

void unit_hexstep_test_case_1(unit_hexstep_t *dev)
{
    uint8_t value, last_value = 0;
    unit_hexstep_set_sensitivity(dev, 100);
    while (1)
    {
        unit_hexstep_get_value(dev, &value);
        if (value != last_value)
        {
            ESP_LOGI(TAG, "value: 0x%02X\n", value);
            last_value = value;
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_2(unit_hexstep_t *dev)
{
    uint8_t led_config;
    while (1)
    {
        unit_hexstep_get_led_config(dev, &led_config);
        ESP_LOGI(TAG, "LED CONFIG: %02X\n", led_config);
        led_config = 0x00;
        unit_hexstep_set_led_config(dev, led_config);
        led_config = 0x00;
        unit_hexstep_get_led_config(dev, &led_config);
        ESP_LOGI(TAG, "set new led config, LED CONFIG: %02X\n", led_config);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        led_config = 0xFF;
        unit_hexstep_set_led_config(dev, led_config);
        led_config = 0xFF;
        unit_hexstep_get_led_config(dev, &led_config);
        ESP_LOGI(TAG, "set new led config, LED CONFIG: %02X\n", led_config);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_3(unit_hexstep_t *dev)
{
    uint8_t led_config;
    unit_hexstep_get_led_config(dev, &led_config);
    ESP_LOGI(TAG, "LED CONFIG: %02X\n", led_config);
    led_config = 0x0A;
    unit_hexstep_set_led_config(dev, led_config);
    led_config = 0x00;
    unit_hexstep_get_led_config(dev, &led_config);
    ESP_LOGI(TAG, "set new led config, LED CONFIG: %02X\n", led_config);
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_4(unit_hexstep_t *dev)
{
    while (1)
    {
        static uint8_t brightness = 0;
        brightness ++;
        if (brightness > 100) 
        {
            brightness = 0;
        }
        unit_hexstep_set_led_brightness(dev, brightness);
        uint8_t led_brightness;
        unit_hexstep_get_led_brightness(dev, &led_brightness);
        ESP_LOGI(TAG, "set new brightness, BRIGHTNESS: %d\n", led_brightness);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_5(unit_hexstep_t *dev)
{
    uint8_t current_direction, value, last_value = 0;
    unit_hexstep_get_switch_state(dev, &current_direction);
    ESP_LOGI(TAG, "current direction: %d\n", current_direction);
    while (1) 
    {
        unit_hexstep_get_value(dev, &value);
        if ((value == 0x0F || value == 0x00) && last_value != value)
        {
            current_direction = !current_direction;
            unit_hexstep_set_switch_state(dev, current_direction);
            current_direction = 2;
            unit_hexstep_get_switch_state(dev, &current_direction);
            ESP_LOGI(TAG, "set new direction, current direction: %d\n", current_direction);
        }
        last_value = value;
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_6(unit_hexstep_t *dev)
{
    uint8_t rgb_brightness, rgb_enable;
    unit_hexstep_get_rgb_brightness(dev, &rgb_brightness);
    ESP_LOGI(TAG, "RGB BRIGHTNESS: %d\n", rgb_brightness);
    unit_hexstep_get_rgb_config(dev, &rgb_enable);
    ESP_LOGI(TAG, "RGB ENABLE: %d\n", rgb_enable);
    unit_hexstep_set_rgb(dev, 255, 255, 255);
    while (1)
    {
        ESP_LOGI(TAG, "START");
        unit_hexstep_set_rgb_config(dev, 1);
        unit_hexstep_get_rgb_config(dev, &rgb_enable);
        ESP_LOGI(TAG, "RGB ENABLE: %d\n", rgb_enable);
        for (int i = 0; i < 100; i++)
        {
            unit_hexstep_set_rgb_brightness(dev, i);
            ESP_LOGI(TAG, "RGB BRIGHTNESS: %d\n", i);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        unit_hexstep_set_rgb_config(dev, 0);
        unit_hexstep_get_rgb_config(dev, &rgb_enable);
        ESP_LOGI(TAG, "RGB ENABLE: %d\n", rgb_enable);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        uint8_t rgb_value[3];
        unit_hexstep_get_rgb(dev, &rgb_value[0], &rgb_value[1], &rgb_value[2]);
        ESP_LOGI(TAG, "RGB VALUE: %d, %d, %d\n", rgb_value[0], rgb_value[1], rgb_value[2]);
    }
}

void unit_hexstep_test_case_7(unit_hexstep_t *dev)
{
    uint8_t rgb_value[3];
    unit_hexstep_set_rgb_config(dev, 1);
    unit_hexstep_set_rgb_brightness(dev, 100);
    unit_hexstep_get_rgb(dev, &rgb_value[0], &rgb_value[1], &rgb_value[2]);
    ESP_LOGI(TAG, "RGB VALUE: %d, %d, %d\n", rgb_value[0], rgb_value[1], rgb_value[2]);
    unit_hexstep_set_rgb(dev, 0, 0, 0);
    while (1)
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

        rgb_value[0] = (r + m) * 255;
        rgb_value[1] = (g + m) * 255; 
        rgb_value[2] = (b + m) * 255;

        unit_hexstep_set_rgb(dev, rgb_value[0], rgb_value[1], rgb_value[2]);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_8(unit_hexstep_t *dev)
{
    uint8_t sensitivity;
    while (1)
    {
        unit_hexstep_get_sensitivity(dev, &sensitivity);
        ESP_LOGI(TAG, "SENSITIVITY: %d\n", sensitivity);
        sensitivity = (esp_random() % 100) + 1; // 1-100
        unit_hexstep_set_sensitivity(dev, sensitivity);
        ESP_LOGI(TAG, "random sensitivity: %d\n", sensitivity);
        sensitivity = 0;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void unit_hexstep_test_case_9(unit_hexstep_t *dev)
{
    i2c_master_bus_handle_t bsp_i2c_handle;
    i2c_master_dev_handle_t aw9523_h;
    uint8_t data[2];
    uint8_t led_config, led_brightness, rgb_config, rgb_brightness, switch_state, sensitivity;
    
    i2c_master_get_bus_handle(BSP_I2C_NUM, &bsp_i2c_handle);
    const i2c_device_config_t aw9523_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0x58,
        .scl_speed_hz = CONFIG_BSP_I2C_CLK_SPEED_HZ,
    };
    i2c_master_bus_add_device(bsp_i2c_handle, &aw9523_config, &aw9523_h);
    data[0] = 0x02;
    data[1] = 0x00;
    i2c_master_transmit_receive(aw9523_h, &data[0], 1, &data[1], 1, 1000);
    ESP_LOGI(TAG, "data[1] = %d", data[1]);

    // random config

    led_config = esp_random() % 255;
    led_brightness = esp_random() % 100;
    rgb_config = esp_random() % 2;
    rgb_brightness = esp_random() % 100;
    switch_state = esp_random() % 2;
    sensitivity = esp_random() % 100;
    ESP_LOGI(TAG, "random config: led config: %d, led brightness: %d, rgb config: %d, rgb brightness: %d, switch state: %d, sensitivity: %d", led_config, led_brightness, rgb_config, rgb_brightness, switch_state, sensitivity);
    
    // set config
    ESP_LOGI(TAG, "set config");
    unit_hexstep_set_led_config(dev, led_config);
    unit_hexstep_set_led_brightness(dev, led_brightness);
    unit_hexstep_set_rgb_config(dev, rgb_config);
    unit_hexstep_set_rgb_brightness(dev, rgb_brightness);
    unit_hexstep_set_switch_state(dev, switch_state);
    unit_hexstep_set_sensitivity(dev, sensitivity);

    // check config
    ESP_LOGI(TAG, "check config");
    uint8_t temp;
    unit_hexstep_get_led_config(dev, &temp);
    if (temp != led_config)
    {
        ESP_LOGI(TAG, "led config error: %d, %d", temp, led_config);
    }
    unit_hexstep_get_led_brightness(dev, &temp);
    if (temp != led_brightness)
    {
        ESP_LOGI(TAG, "led brightness error: %d, %d", temp, led_brightness);
    }
    unit_hexstep_get_rgb_config(dev, &temp);
    if (temp != rgb_config)
    {
        ESP_LOGI(TAG, "rgb config error: %d, %d", temp, rgb_config);
    }
    unit_hexstep_get_rgb_brightness(dev, &temp);
    if (temp != rgb_brightness)
    {
        ESP_LOGI(TAG, "rgb brightness error: %d, %d", temp, rgb_brightness);
    }
    unit_hexstep_get_switch_state(dev, &temp);
    if (temp != switch_state)
    {
        ESP_LOGI(TAG, "switch state error: %d, %d", temp, switch_state);
    }
    unit_hexstep_get_sensitivity(dev, &temp);
    if (temp != sensitivity)
    {
        ESP_LOGI(TAG, "sensitivity error: %d, %d", temp, sensitivity);
    }
    
    // save config
    ESP_LOGI(TAG, "save config");
    unit_hexstep_save_to_flash(dev, 1);
    unit_hexstep_save_to_flash(dev, 2);
    

    // check config

    ESP_LOGI(TAG, "please power off and on the unit");
    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        
        ESP_LOGI(TAG, "read config");
        unit_hexstep_get_led_config(dev, &temp);
        ESP_LOGI(TAG, "led config: %d", temp);
        if (temp != led_config)
        {
            ESP_LOGI(TAG, "saved led config error: %d, %d", temp, led_config);
        }
        unit_hexstep_get_led_brightness(dev, &temp);
        ESP_LOGI(TAG, "led brightness: %d", temp);
        if (temp != led_brightness)
        {
            ESP_LOGI(TAG, "saved led brightness error: %d, %d", temp, led_brightness);
        }
        unit_hexstep_get_rgb_config(dev, &temp);
        ESP_LOGI(TAG, "rgb config: %d", temp);
        if (temp != rgb_config)
        {
            ESP_LOGI(TAG, "saved rgb config error: %d, %d", temp, rgb_config);
        }
        unit_hexstep_get_rgb_brightness(dev, &temp);
        ESP_LOGI(TAG, "rgb brightness: %d", temp);
        if (temp != rgb_brightness)
        {
            ESP_LOGI(TAG, "saved rgb brightness error: %d, %d", temp, rgb_brightness);
        }
        unit_hexstep_get_switch_state(dev, &temp);
        ESP_LOGI(TAG, "switch state: %d", temp);
        if (temp != switch_state)
        {
            ESP_LOGI(TAG, "saved switch state error: %d, %d", temp, switch_state);
        }
        unit_hexstep_get_sensitivity(dev, &temp);
        ESP_LOGI(TAG, "sensitivity: %d", temp);
        if (temp != sensitivity)
        {
            ESP_LOGI(TAG, "saved sensitivity error: %d, %d", temp, sensitivity);
        }
    }
}

void unit_hexstep_test_case_10(unit_hexstep_t *dev)
{
    uint8_t version;
    unit_hexstep_get_version(dev, &version);
    ESP_LOGI(TAG, "version: %d", version);
}

void unit_hexstep_test_case_11(unit_hexstep_t *dev, i2c_bus_handle_t i2c_handle)
{
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // 烧录的时候可能会跑到这里导致地址被改写
    uint8_t address;
    unit_hexstep_get_address(dev, &address);
    ESP_LOGI(TAG, "now address: %02X", address);
    address = (esp_random() % (0x77 - 0x08 + 1)) + 0x08;  // 0x08 - 0x77
    ESP_LOGI(TAG, "set address: %02X", address);
    unit_hexstep_set_address(dev, address);

    // search address
    i2c_bus_scan(i2c_handle, NULL, 1);
    i2c_bus_device_handle_t test_dev_handle = i2c_bus_device_create(i2c_handle, address, 0);
    

    // check address
    uint8_t temp;
    i2c_bus_read_bytes(test_dev_handle, UNIT_HEXSTEP_REG_ADDRESS, 1, &temp);
    if (temp == address)
    {
        ESP_LOGI(TAG, "find address: %02X", address);
    }
    else
    {
        ESP_LOGI(TAG, "not find address: %02X", address);
    }

    ESP_LOGI(TAG, "test case 11 passed");
    address = UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS;
    ESP_LOGI(TAG, "set default address: 0x%02X", address);
    i2c_bus_write_bytes(test_dev_handle, UNIT_HEXSTEP_REG_ADDRESS, 1, &address);

    i2c_bus_device_handle_t default_dev_handle = i2c_bus_device_create(i2c_handle, UNIT_HEXSTEP_DEFAULT_I2C_ADDRESS, 0);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    address = 0;
    while (1)
    {
        while (i2c_bus_read_bytes(default_dev_handle, UNIT_HEXSTEP_REG_ADDRESS, 1, &address) != 0)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "now address: 0x%02X", address);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// 压力测试，对每一个寄存器写入并校验
void unit_hexstep_test_case_press(unit_hexstep_t *dev)
{
    uint8_t get_value = 0;
    uint8_t set_led_config, get_led_config = 0;
    uint8_t set_led_brightness, get_led_brightness = 0;
    uint8_t set_rgb_config, get_rgb_config = 0;
    uint8_t set_rgb_brightness, get_rgb_brightness = 0;
    uint8_t set_rgb_value[3], get_rgb_value[3] = {0, 0, 0};
    uint8_t set_switch_state, get_switch_state = 0;
    uint8_t set_sensitivity, get_sensitivity = 0;
    uint8_t version, last_version = 0;
    while (1)
    {
        unit_hexstep_get_value(dev, &get_value); 
        
        set_led_config = esp_random() % 255;
        unit_hexstep_set_led_config(dev, set_led_config);
        unit_hexstep_get_led_config(dev, &get_led_config);
        if (get_led_config != set_led_config)
        {
            ESP_LOGI(TAG, "led config error: %d, %d", get_led_config, set_led_config);
        }

        set_led_brightness = esp_random() % 100 + 1;
        unit_hexstep_set_led_brightness(dev, set_led_brightness);
        unit_hexstep_get_led_brightness(dev, &get_led_brightness);
        if (get_led_brightness != set_led_brightness)
        {
            ESP_LOGI(TAG, "led brightness error: %d, %d", get_led_brightness, set_led_brightness);
        }

        // set_rgb_config = esp_random() % 2;
        // unit_hexstep_set_rgb_config(dev, set_rgb_config);
        // unit_hexstep_get_rgb_config(dev, &get_rgb_config);
        // if (get_rgb_config != set_rgb_config)
        // {
        //     ESP_LOGI(TAG, "rgb config error: %d, %d", get_rgb_config, set_rgb_config);
        // }

        set_rgb_brightness = esp_random() % 100;
        unit_hexstep_set_rgb_brightness(dev, set_rgb_brightness);
        unit_hexstep_get_rgb_brightness(dev, &get_rgb_brightness);
        if (get_rgb_brightness != set_rgb_brightness)
        {
            ESP_LOGI(TAG, "rgb brightness error: %d, %d", get_rgb_brightness, set_rgb_brightness);
        }

        set_rgb_value[0] = esp_random() % 255;
        set_rgb_value[1] = esp_random() % 255;
        set_rgb_value[2] = esp_random() % 255;
        unit_hexstep_set_rgb(dev, set_rgb_value[0], set_rgb_value[1], set_rgb_value[2]);
        unit_hexstep_get_rgb(dev, &get_rgb_value[0], &get_rgb_value[1], &get_rgb_value[2]);
        if (get_rgb_value[0] != set_rgb_value[0] || get_rgb_value[1] != set_rgb_value[1] || get_rgb_value[2] != set_rgb_value[2])
        {
            ESP_LOGI(TAG, "rgb value error: %d, %d, %d, %d, %d, %d", get_rgb_value[0], get_rgb_value[1], get_rgb_value[2], set_rgb_value[0], set_rgb_value[1], set_rgb_value[2]);
        }

        set_switch_state = esp_random() % 2;
        unit_hexstep_set_switch_state(dev, set_switch_state);
        unit_hexstep_get_switch_state(dev, &get_switch_state);
        if (get_switch_state != set_switch_state)
        {
            ESP_LOGI(TAG, "switch state error: %d, %d", get_switch_state, set_switch_state);
        }

        set_sensitivity = esp_random() % 100 + 1;
        unit_hexstep_set_sensitivity(dev, set_sensitivity);
        unit_hexstep_get_sensitivity(dev, &get_sensitivity);
        if (get_sensitivity != set_sensitivity)
        {
            ESP_LOGI(TAG, "sensitivity error: %d, %d", get_sensitivity, set_sensitivity);
        }

        unit_hexstep_get_version(dev, &version);
        if (version != last_version)
        {
            ESP_LOGI(TAG, "version error: %d, %d", version, last_version);
            last_version = version;
        }

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}