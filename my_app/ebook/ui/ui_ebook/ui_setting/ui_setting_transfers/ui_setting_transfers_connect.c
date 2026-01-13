#include "ui_setting_transfers_connect.h"

void ui_setting_transfers_connect_init(void){
    //获取传输界面的第一个儿子
    lv_obj_t *obj_son_0 = lv_obj_get_child(ui_setting_display->transfers, 0);

    lv_obj_t *connect_cue_label = lv_label_create(obj_son_0);
    lv_label_set_text(connect_cue_label, "请在手机打开\n“***小程序”\n“******app”\n探索设备\nEBook001\n进行连接");
    lv_obj_set_style_text_font(connect_cue_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(connect_cue_label,1, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(connect_cue_label, 6, LV_PART_MAIN);
    lv_obj_align(connect_cue_label, LV_ALIGN_TOP_MID, -6, 20);

    //创建提示语
    lv_obj_t *ui_tipLabel = lv_label_create(obj_son_0);
    lv_label_set_text(ui_tipLabel, "温馨提示:\n当手机和设备连接后\n用手机上可推送图书\n图片、固件升级!");
    lv_obj_set_style_text_font(ui_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_tipLabel,1, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui_tipLabel, 6, LV_PART_MAIN);
    lv_obj_align(ui_tipLabel, LV_ALIGN_TOP_MID, -6, 200);

}

