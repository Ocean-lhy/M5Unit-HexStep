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

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_tabview;
	lv_obj_t *screen_tabview_tab_1;
	lv_obj_t *screen_tabview_tab_2;
	lv_obj_t *screen_tabview_tab_3;
	lv_obj_t *screen_label_addr;
	lv_obj_t *screen_label_version;
	lv_obj_t *screen_meter_1;
	lv_meter_scale_t *screen_meter_1_scale_0;
	lv_meter_indicator_t *screen_meter_1_scale_0_ndline_0;
	lv_meter_indicator_t *screen_meter_1_scale_0_arc_0;
	lv_meter_indicator_t *screen_meter_1_scale_0_scaleline_0;
	lv_obj_t *screen_label_value;
	lv_obj_t *screen_label_revert;
	lv_obj_t *screen_sw_reversal;
	lv_obj_t *screen_btn_save_led;
	lv_obj_t *screen_btn_save_led_label;
	lv_obj_t *screen_btn_save_rgb;
	lv_obj_t *screen_btn_save_rgb_label;
	lv_obj_t *screen_label_value_2;
	lv_obj_t *screen_slider_led_config;
	lv_obj_t *screen_label_led_config;
	lv_obj_t *screen_label_led_brightness;
	lv_obj_t *screen_slider_led_brightness;
	lv_obj_t *screen_label_R;
	lv_obj_t *screen_label_G;
	lv_obj_t *screen_label_B;
	lv_obj_t *screen_slider_R;
	lv_obj_t *screen_slider_G;
	lv_obj_t *screen_slider_B;
	lv_obj_t *screen_sw_rgb;
	lv_obj_t *screen_slider_rgb;
	lv_obj_t *screen_label_RGB;
	lv_obj_t *screen_btn_rgb_demo;
	lv_obj_t *screen_btn_rgb_demo_label;
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


void setup_scr_screen(lv_ui *ui);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)


#ifdef __cplusplus
}
#endif
#endif
