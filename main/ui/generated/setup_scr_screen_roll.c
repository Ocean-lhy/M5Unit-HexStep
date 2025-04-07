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



void setup_scr_screen_roll(lv_ui *ui)
{
    //Write codes screen_roll
    ui->screen_roll = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_roll, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_roll, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_roll, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_roll, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_roll, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_roll, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_roll_textprogress_roll
    ui->screen_roll_textprogress_roll = lv_textprogress_create(ui->screen_roll);
    lv_textprogress_set_range_value(ui->screen_roll_textprogress_roll, 0, 100, 0, 0);
    lv_textprogress_set_decimal(ui->screen_roll_textprogress_roll, 0);
    lv_textprogress_set_value(ui->screen_roll_textprogress_roll, 0);
    lv_obj_set_pos(ui->screen_roll_textprogress_roll, 104, 191);
    lv_obj_set_size(ui->screen_roll_textprogress_roll, 116, 32);

    //Write style for screen_roll_textprogress_roll, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_roll_textprogress_roll, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_roll_textprogress_roll, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_roll_textprogress_roll, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_roll_textprogress_roll, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_roll_textprogress_roll, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_roll_textprogress_roll, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_roll_textprogress_roll, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_roll_textprogress_roll, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_roll_textprogress_roll, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_roll_textprogress_roll, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_roll_textprogress_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_roll_textprogress_roll, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_roll_textprogress_roll, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_roll_textprogress_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_roll_textprogress_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_roll_textprogress_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_roll_label_roll
    ui->screen_roll_label_roll = lv_label_create(ui->screen_roll);
    lv_label_set_text(ui->screen_roll_label_roll, "旋钮测试\n顺时针旋转旋钮三圈");
    lv_label_set_long_mode(ui->screen_roll_label_roll, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_roll_label_roll, 68, 12);
    lv_obj_set_size(ui->screen_roll_label_roll, 190, 43);

    //Write style for screen_roll_label_roll, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_roll_label_roll, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_roll_label_roll, &lv_font_hei_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_roll_label_roll, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_roll_label_roll, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_roll_label_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_roll_meter_roll
    ui->screen_roll_meter_roll = lv_meter_create(ui->screen_roll);
    // add scale ui->screen_roll_meter_roll_scale_0
    ui->screen_roll_meter_roll_scale_0 = lv_meter_add_scale(ui->screen_roll_meter_roll);
    lv_meter_set_scale_ticks(ui->screen_roll_meter_roll, ui->screen_roll_meter_roll_scale_0, 16, 2, 8, lv_color_hex(0xff0000));
    lv_meter_set_scale_major_ticks(ui->screen_roll_meter_roll, ui->screen_roll_meter_roll_scale_0, 1, 2, 15, lv_color_hex(0x000000), 8);
    lv_meter_set_scale_range(ui->screen_roll_meter_roll, ui->screen_roll_meter_roll_scale_0, 0, 15, 336, 270);

    // add needle line for ui->screen_roll_meter_roll_scale_0.
    ui->screen_roll_meter_roll_scale_0_ndline_0 = lv_meter_add_needle_line(ui->screen_roll_meter_roll, ui->screen_roll_meter_roll_scale_0, 5, lv_color_hex(0x000000), -10);
    lv_meter_set_indicator_value(ui->screen_roll_meter_roll, ui->screen_roll_meter_roll_scale_0_ndline_0, 0);
    lv_obj_set_pos(ui->screen_roll_meter_roll, 85, 49);
    lv_obj_set_size(ui->screen_roll_meter_roll, 150, 150);

    //Write style for screen_roll_meter_roll, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_roll_meter_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_roll_meter_roll, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_roll_meter_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_roll_meter_roll, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_roll_meter_roll, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_roll_meter_roll, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_roll_meter_roll, 14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_roll_meter_roll, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_roll_meter_roll, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_roll_meter_roll, lv_color_hex(0xff0000), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_roll_meter_roll, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_roll_meter_roll, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for screen_roll_meter_roll, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_roll_meter_roll, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_roll_meter_roll, lv_color_hex(0x000000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_roll_meter_roll, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_roll_label_1
    ui->screen_roll_label_1 = lv_label_create(ui->screen_roll);
    lv_label_set_text(ui->screen_roll_label_1, "11");
    lv_label_set_long_mode(ui->screen_roll_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_roll_label_1, 6, 101);
    lv_obj_set_size(ui->screen_roll_label_1, 87, 48);

    //Write style for screen_roll_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_roll_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_roll_label_1, &lv_font_montserratMedium_43, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_roll_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_roll_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_roll_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_roll.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_roll);

    //Init events for screen.
    events_init_screen_roll(ui);
}
