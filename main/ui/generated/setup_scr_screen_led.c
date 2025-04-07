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



void setup_scr_screen_led(lv_ui *ui)
{
    //Write codes screen_led
    ui->screen_led = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_led, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_led, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_led, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_led, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_led, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_led, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_led_label_led
    ui->screen_led_label_led = lv_label_create(ui->screen_led);
    lv_label_set_text(ui->screen_led_label_led, "将数字旋转到8\n观察数码管亮度效果");
    lv_label_set_long_mode(ui->screen_led_label_led, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_led_label_led, 30, 95);
    lv_obj_set_size(ui->screen_led_label_led, 261, 46);

    //Write style for screen_led_label_led, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_led_label_led, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_led_label_led, &lv_font_hei_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_led_label_led, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_led_label_led, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_led_label_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_led_slider_led
    ui->screen_led_slider_led = lv_slider_create(ui->screen_led);
    lv_slider_set_range(ui->screen_led_slider_led, 0, 100);
    lv_slider_set_mode(ui->screen_led_slider_led, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->screen_led_slider_led, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_led_slider_led, 84, 169);
    lv_obj_set_size(ui->screen_led_slider_led, 160, 8);

    //Write style for screen_led_slider_led, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_led_slider_led, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_led_slider_led, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_led_slider_led, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_led_slider_led, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_led_slider_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_led_slider_led, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_led_slider_led, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_led_slider_led, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_led_slider_led, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_led_slider_led, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_led_slider_led, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_led_slider_led, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_led_slider_led, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_led_slider_led, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_led_slider_led, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_led_slider_led, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_led_label_led_num
    ui->screen_led_label_led_num = lv_label_create(ui->screen_led);
    lv_label_set_text(ui->screen_led_label_led_num, "8");
    lv_label_set_long_mode(ui->screen_led_label_led_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_led_label_led_num, 113, 42);
    lv_obj_set_size(ui->screen_led_label_led_num, 101, 43);

    //Write style for screen_led_label_led_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_led_label_led_num, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_led_label_led_num, &lv_font_montserratMedium_34, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_led_label_led_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_led_label_led_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_led_label_led_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_led.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_led);

    //Init events for screen.
    events_init_screen_led(ui);
}
