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

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_detect_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_roll, guider_ui.screen_roll_del, &guider_ui.screen_detect_del, setup_scr_screen_roll, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_detect (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_detect, screen_detect_event_handler, LV_EVENT_ALL, ui);
}

static void screen_roll_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_led, guider_ui.screen_led_del, &guider_ui.screen_roll_del, setup_scr_screen_led, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_roll (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_roll, screen_roll_event_handler, LV_EVENT_ALL, ui);
}

static void screen_led_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_RGB, guider_ui.screen_RGB_del, &guider_ui.screen_led_del, setup_scr_screen_RGB, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_led (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_led, screen_led_event_handler, LV_EVENT_ALL, ui);
}

static void screen_RGB_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_KEY:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_detect, guider_ui.screen_detect_del, &guider_ui.screen_RGB_del, setup_scr_screen_detect, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_RGB (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_RGB, screen_RGB_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
