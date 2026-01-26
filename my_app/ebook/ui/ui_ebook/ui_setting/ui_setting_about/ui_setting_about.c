#include "ui_setting_about.h"
#include "string.h"
#define  SETTING_LIST_NUM 4
char *list_name[SETTING_LIST_NUM] = {
    "型号:",
    "SN:",
    "MAC:",
    "版本:",
};
char *list_value[SETTING_LIST_NUM] = {

    "Pocket-S1",

    "123456789012345678901234567",

    "12:34:56:78:90:12",

    "PKS1-101_V1.0.7_CS",

};
void ui_setting_about_init(void){
   
  
    //1.标题
    lv_obj_t *ui_titleLabel = lv_label_create(ui_setting_display->about);
    lv_label_set_text(ui_titleLabel, "本机信息");
    lv_obj_set_style_text_font(ui_titleLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_titleLabel,2, LV_PART_MAIN);
    lv_obj_align(ui_titleLabel, LV_ALIGN_TOP_MID, -3, 20);
    

    lv_obj_t *container = lv_obj_create(ui_setting_display->about);
    lv_obj_align(container, LV_ALIGN_TOP_MID, -5, 45);
    lv_obj_set_size(container, 160, 220);
    lv_obj_set_style_border_color(container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 1, LV_PART_MAIN);
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);

     //4.设置容器的弹性布局
    lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    
    for(int i=0; i < SETTING_LIST_NUM; i++){
        lv_obj_t *list_container = lv_obj_create(container);
        lv_obj_set_size(list_container, 155, 55);
        lv_obj_set_style_border_color(list_container, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(list_container, 1, LV_PART_MAIN);
        lv_obj_clear_flag(list_container, LV_OBJ_FLAG_SCROLLABLE);

        lv_obj_t *label_1 = lv_label_create(list_container);
        lv_label_set_text(label_1, list_name[i]);
        lv_obj_set_style_text_font(label_1,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(label_1,2, LV_PART_MAIN);
        lv_obj_align(label_1, LV_ALIGN_LEFT_MID, 0, 0);

        lv_obj_t *label_2 = lv_label_create(list_container);
        lv_label_set_text(label_2, list_value[i]);
        lv_obj_set_width(label_2, 90);
        lv_label_set_long_mode(label_2, LV_LABEL_LONG_WRAP);
        lv_obj_set_style_text_font(label_2,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(label_2,2, LV_PART_MAIN);
        lv_obj_align_to(label_2, label_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    }
}


