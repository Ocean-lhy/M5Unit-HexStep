/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "lv_textprogress.h"

typedef struct
{
  
	lv_obj_t *screen_detect;
	bool screen_detect_del;
	lv_obj_t *screen_detect_label_detect;
	lv_obj_t *screen_detect_label_1;
	lv_obj_t *screen_roll;
	bool screen_roll_del;
	lv_obj_t *screen_roll_textprogress_roll;
	lv_obj_t *screen_roll_label_roll;
	lv_obj_t *screen_roll_meter_roll;
	lv_meter_scale_t *screen_roll_meter_roll_scale_0;
	lv_meter_indicator_t *screen_roll_meter_roll_scale_0_ndline_0;
	lv_obj_t *screen_roll_label_1;
	lv_obj_t *screen_led;
	bool screen_led_del;
	lv_obj_t *screen_led_label_led;
	lv_obj_t *screen_led_slider_led;
	lv_obj_t *screen_led_label_led_num;
	lv_obj_t *screen_RGB;
	bool screen_RGB_del;
	lv_obj_t *screen_RGB_label_RGB;
	lv_obj_t *screen_RGB_led_RGB;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_detect(lv_ui *ui);
void setup_scr_screen_roll(lv_ui *ui);
void setup_scr_screen_led(lv_ui *ui);
void setup_scr_screen_RGB(lv_ui *ui);

LV_FONT_DECLARE(lv_font_hei_20)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_43)
LV_FONT_DECLARE(lv_font_montserratMedium_34)


#ifdef __cplusplus
}
#endif
#endif
