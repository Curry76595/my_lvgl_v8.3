#include "ui_setting_factory_cue.h"



void ui_setting_factory_cue_init(void){
    //获取恢复出厂界面的第三个儿子
    lv_obj_t *obj_son_2 = lv_obj_get_child(ui_setting_display->factory, 2);

    //创建恢复勿退出提示语
    lv_obj_t *ui_confirm_tipLabel = lv_label_create(obj_son_2);
    if(English_version){
        lv_label_set_text(ui_confirm_tipLabel, "Factory reset\n  completed.\nPlease wait for\nthe device to\n  restart!");
        lv_obj_set_style_text_letter_space(ui_confirm_tipLabel,1, LV_PART_MAIN);
        lv_obj_align(ui_confirm_tipLabel, LV_ALIGN_TOP_MID, -6, 80);
    }else{
         lv_label_set_text(ui_confirm_tipLabel, "恢复出厂完成\n请等待重启!");
         lv_obj_set_style_text_letter_space(ui_confirm_tipLabel,3, LV_PART_MAIN);
         lv_obj_align(ui_confirm_tipLabel, LV_ALIGN_TOP_MID, -6, 100);
    }
    lv_obj_set_style_text_font(ui_confirm_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_confirm_tipLabel,15, LV_PART_MAIN);
    
}

