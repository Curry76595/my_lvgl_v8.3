#include "ui_setting_about.h"

void ui_setting_about_init(void){
   
    //1.标题
    lv_obj_t *ui_titleLabel = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_titleLabel, "本机信息");
    lv_obj_set_style_text_font(ui_titleLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_titleLabel,2, LV_PART_MAIN);
    lv_obj_align(ui_titleLabel, LV_ALIGN_TOP_MID, -3, 20);
    //2.型号
    lv_obj_t *ui_modelNumber = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_modelNumber, "型号：******");
    lv_obj_set_style_text_font(ui_modelNumber, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_modelNumber, 2, LV_PART_MAIN);
    lv_obj_align(ui_modelNumber, LV_ALIGN_TOP_LEFT, -3, 55);
    //3.1 SN
    lv_obj_t *ui_SN = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_SN, "SN:");
    lv_obj_set_style_text_font(ui_SN, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_SN, 6, LV_PART_MAIN);
    lv_obj_align(ui_SN, LV_ALIGN_TOP_LEFT, -3, 90);
    //3.2 SN_TEXT
    lv_obj_t *ui_SN_text = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_SN_text,"D801551215");
    lv_obj_set_style_text_font(ui_SN_text, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_SN_text, 1, LV_PART_MAIN);
    lv_obj_align(ui_SN_text, LV_ALIGN_TOP_LEFT, 40, 90);
    //4.1 版本
    lv_obj_t *ui_version = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_version, "版本:");
    lv_obj_set_style_text_font(ui_version, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_version, 2, LV_PART_MAIN);
    lv_obj_align(ui_version, LV_ALIGN_TOP_LEFT, -3, 125);
    //4.2 版本_TEXT
    lv_obj_t *ui_version_text = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_version_text, "V0.0.3 2");
    lv_obj_set_style_text_font(ui_version_text, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_version_text, 1, LV_PART_MAIN);
    lv_obj_align(ui_version_text, LV_ALIGN_TOP_LEFT, 46, 125);
}

