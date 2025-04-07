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



void setup_scr_screen_detect(lv_ui *ui)
{
    //Write codes screen_detect
    ui->screen_detect = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_detect, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_detect, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_detect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_detect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_detect, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_detect, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_detect_label_detect
    ui->screen_detect_label_detect = lv_label_create(ui->screen_detect);
    lv_label_set_text(ui->screen_detect_label_detect, "设备检测中...\n\n设备地址：ERR\n\n固件版本：ERR\n\n请将设备插入PORT.A口");
    lv_label_set_long_mode(ui->screen_detect_label_detect, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_detect_label_detect, 37, 28);
    lv_obj_set_size(ui->screen_detect_label_detect, 237, 166);

    //Write style for screen_detect_label_detect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_detect_label_detect, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_detect_label_detect, &lv_font_hei_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_detect_label_detect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_detect_label_detect, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_detect_label_detect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_detect_label_1
    ui->screen_detect_label_1 = lv_label_create(ui->screen_detect);
    lv_label_set_text(ui->screen_detect_label_1, "RGB测试完成，按右键结束测试观察数码管亮度效果按右键继续下一项测试设备连接成功设备地址：0x固件版本按任意键开始测试请拔下设备更换待设备");
    lv_label_set_long_mode(ui->screen_detect_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_detect_label_1, 423, 97);
    lv_obj_set_size(ui->screen_detect_label_1, 200, 146);

    //Write style for screen_detect_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_detect_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_detect_label_1, &lv_font_hei_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_detect_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_detect_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_detect_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_detect.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_detect);

    //Init events for screen.
    events_init_screen_detect(ui);
}
