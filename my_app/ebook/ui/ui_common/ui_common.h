#ifndef _UI_COMMON_H_
#define _UI_COMMON_H_


#include "lvgl/lvgl.h"

#define English_version  1 // 1 英文； 0 中文
extern lv_indev_t *indev_keypad;
LV_FONT_DECLARE(lv_font_CN_ExtraLight_20)
LV_FONT_DECLARE(lv_font_unifont_16)
LV_FONT_DECLARE(lv_font_unicode_gbk_24)
// LV_FONT_DECLARE(lv_font_Bold_24)

LV_IMG_DECLARE(icon_cursor);
LV_IMG_DECLARE(icon_plus);
LV_IMG_DECLARE(icon_search_del);
LV_IMG_DECLARE(icon_horn);
LV_IMG_DECLARE(icon_file);
LV_IMG_DECLARE(icon_com_exit);
LV_IMG_DECLARE(pic_module_bat_full);
LV_IMG_DECLARE(pic_module_charge_status);
LV_IMG_DECLARE(pic_module_ble_status);
LV_IMG_DECLARE(pic_module_earphonr_status);
LV_IMG_DECLARE(pic_module_wifi_status);

LV_IMG_DECLARE(icon_com_file_list_folder);
LV_IMG_DECLARE(icon_com_file_list_music);
LV_IMG_DECLARE(icon_com_file_list_txt);
LV_IMG_DECLARE(icon_com_file_list_unknown);
LV_IMG_DECLARE(thick_left_arrow);
LV_IMG_DECLARE(spell_yes);
LV_IMG_DECLARE(selected);
LV_IMG_DECLARE(minutes);
LV_IMG_DECLARE(new_selected);
LV_IMG_DECLARE(selected_reverse);
LV_IMG_DECLARE(BMP);
LV_IMG_DECLARE(txt);
LV_IMG_DECLARE(picture);
LV_IMG_DECLARE(QRCode);
LV_IMG_DECLARE(de_about);
LV_IMG_DECLARE(about);
LV_IMG_DECLARE(de_lockscreen);
LV_IMG_DECLARE(lockscreen);
LV_IMG_DECLARE(de_storage);
LV_IMG_DECLARE(storage);
LV_IMG_DECLARE(de_factory);
LV_IMG_DECLARE(factory);
#if 0
#define     Chinese_font_16         lv_font_unifont_16
#define     Chinese_font_20         lv_font_CN_ExtraLight_20
#define     Chinese_font_24         lv_font_unicode_gbk_24
#define     Chinese_font_Bold_24    lv_font_unifont_16
#else
#define     Chinese_font_16         lv_font_unifont_16
#define     Chinese_font_20         lv_font_unifont_16
#define     Chinese_font_24         lv_font_unifont_16
#define     Chinese_font_Bold_24    lv_font_unifont_16
#endif


// 初始化背景样式
void ui_com_style_init(void);
void ui_com_border_show(lv_obj_t *obj);
lv_obj_t *ui_com_bg_cont_create(lv_obj_t *parent);
lv_obj_t *ui_com_label_create(lv_obj_t *parent);
lv_obj_t *ui_com_img_create(lv_obj_t *parent);

#endif // _UI_COMMON_H_

