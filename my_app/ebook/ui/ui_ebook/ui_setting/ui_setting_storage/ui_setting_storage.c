#include "ui_setting_storage.h"

lv_obj_t *ui_titleLabel;


void ui_setting_storage_init(void){
    //创建标题标签
    ui_titleLabel = lv_label_create(ui_setting_display->storage);
    lv_label_set_text(ui_titleLabel, "当前存储已使用80%");
    lv_obj_set_style_text_font(ui_titleLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_titleLabel,2, LV_PART_MAIN);
    lv_obj_align(ui_titleLabel, LV_ALIGN_TOP_MID, -5, 50);
    //创建进度条
    lv_obj_t *bar = lv_bar_create(ui_setting_display->storage);
    lv_obj_set_size(bar, 150, 13);
    lv_obj_set_style_radius(bar, 8, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 8, LV_PART_INDICATOR);
    lv_obj_set_style_border_width(bar, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(bar, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, -5, 90);
    lv_bar_set_range(bar, 0, 100);  //0-100
    lv_bar_set_value(bar, 80, LV_ANIM_OFF);  // 设置80%，无动画
    lv_obj_set_style_pad_all(bar, 2, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_INDICATOR);
    
    //创建提示语
    lv_obj_t *ui_tipLabel = lv_label_create(ui_setting_display->storage);
    lv_label_set_text(ui_tipLabel, "温馨提示:\n当存储使用超90%时\n请清理释放磁盘空间");
    lv_obj_set_style_text_font(ui_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_tipLabel,2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui_tipLabel, 4, LV_PART_MAIN);
    lv_obj_align(ui_tipLabel, LV_ALIGN_TOP_MID, -5, 150);
    

}

