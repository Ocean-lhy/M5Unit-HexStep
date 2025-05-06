/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "unit_hexstep.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

extern QueueHandle_t lv_command_queue;

static void screen_slider_led_config_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_led_config);
        char text[32];
        snprintf(text, sizeof(text), "led sleep  %ds", value);
        lv_label_set_text(guider_ui.screen_label_led_config, text);
        printf("screen_slider_led_config_event_handler: %d\n", value);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_led_config);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_LED_CONFIG;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        break;
    }
    default:
        break;
    }
}

static void screen_slider_led_brightness_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_led_brightness);
        char text[32];
        snprintf(text, sizeof(text), "brightness %d%%", value);
        lv_label_set_text(guider_ui.screen_label_led_brightness, text);
        printf("screen_slider_led_brightness_event_handler: %d\n", value);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_led_brightness);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_LED_BRIGHTNESS;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        break;
    }
    default:
        break;
    }
}

static void screen_sw_reversal_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        uint8_t status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        uint16_t command = ((uint8_t)status << 8) | UNIT_HEXSTEP_REG_SWITCH;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_sw_reversal_event_handler: %d\n", status);
        break;
    }
    default:
        break;
    }
}

static void screen_sw_rgb_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        uint8_t status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        uint16_t command = ((uint8_t)status << 8) | UNIT_HEXSTEP_REG_RGB_CONFIG;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_sw_rgb_event_handler: %d\n", status);
        break;
    }
    default:
        break;
    }
}

static void screen_slider_rgb_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_rgb);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_RGB_BRIGHTNESS;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_slider_rgb_event_handler: %d\n", value);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_save_led_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        uint16_t command = ((uint8_t)1 << 8) | UNIT_HEXSTEP_REG_SAVE_FLASH;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_btn_save_led_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_save_rgb_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        uint16_t command = ((uint8_t)2 << 8) | UNIT_HEXSTEP_REG_SAVE_FLASH;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_btn_save_rgb_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

static void screen_slider_R_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_R);
        char text[32];
        snprintf(text, sizeof(text), "R: %d", value);
        lv_label_set_text(guider_ui.screen_label_R, text);
        printf("screen_slider_R_event_handler: %d\n", value);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_R);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_R_VALUE;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_slider_R_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

static void screen_slider_G_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_G);
        char text[32];
        snprintf(text, sizeof(text), "G: %d", value);
        lv_label_set_text(guider_ui.screen_label_G, text);
        printf("screen_slider_G_event_handler: %d\n", value);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_G);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_G_VALUE;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_slider_G_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

static void screen_slider_B_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_B);
        char text[32];
        snprintf(text, sizeof(text), "B: %d", value);
        lv_label_set_text(guider_ui.screen_label_B, text);
        printf("screen_slider_B_event_handler: %d\n", value);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        int value = lv_slider_get_value(guider_ui.screen_slider_B);
        uint16_t command = ((uint8_t)value << 8) | UNIT_HEXSTEP_REG_B_VALUE;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_slider_B_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_rgb_demo_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        lv_slider_set_value(guider_ui.screen_slider_rgb, 100, LV_ANIM_OFF);
        lv_obj_add_state(guider_ui.screen_slider_rgb, LV_STATE_CHECKED);
        uint16_t command = ((uint8_t)3 << 8) | UNIT_HEXSTEP_REG_RGB_DEMO;
        xQueueSend(lv_command_queue, &command, portMAX_DELAY);
        printf("screen_btn_rgb_demo_event_handler: %d\n", command);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_slider_led_config, screen_slider_led_config_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_slider_led_brightness, screen_slider_led_brightness_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_sw_reversal, screen_sw_reversal_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_sw_rgb, screen_sw_rgb_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_slider_rgb, screen_slider_rgb_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_save_led, screen_btn_save_led_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_save_rgb, screen_btn_save_rgb_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_slider_R, screen_slider_R_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_slider_G, screen_slider_G_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_slider_B, screen_slider_B_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_rgb_demo, screen_btn_rgb_demo_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
