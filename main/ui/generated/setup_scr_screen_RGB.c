/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_RGB(lv_ui *ui)
{
    //Write codes screen_RGB
    ui->screen_RGB = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_RGB, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_RGB, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_RGB, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_RGB, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_RGB, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_RGB, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_RGB_label_RGB
    ui->screen_RGB_label_RGB = lv_label_create(ui->screen_RGB);
    lv_label_set_text(ui->screen_RGB_label_RGB, "RGB测试\n按中间按键切换RGB颜色");
    lv_label_set_long_mode(ui->screen_RGB_label_RGB, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_RGB_label_RGB, 4, 36);
    lv_obj_set_size(ui->screen_RGB_label_RGB, 315, 42);

    //Write style for screen_RGB_label_RGB, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_RGB_label_RGB, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_RGB_label_RGB, &lv_font_hei_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_RGB_label_RGB, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_RGB_label_RGB, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_RGB_label_RGB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_RGB_led_RGB
    ui->screen_RGB_led_RGB = lv_led_create(ui->screen_RGB);
    lv_led_set_brightness(ui->screen_RGB_led_RGB, 255);
    lv_led_set_color(ui->screen_RGB_led_RGB, lv_color_hex(0xff0000));
    lv_obj_set_pos(ui->screen_RGB_led_RGB, 114, 105);
    lv_obj_set_size(ui->screen_RGB_led_RGB, 100, 100);

    //The custom code of screen_RGB.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_RGB);

    //Init events for screen.
    events_init_screen_RGB(ui);
}
