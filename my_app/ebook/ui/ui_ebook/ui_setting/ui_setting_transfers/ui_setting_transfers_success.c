#include "ui_setting_transfers_success.h"

void ui_setting_transfers_success_init(void){

     //获取传输界面的第二个儿子
    lv_obj_t *obj_son_1 = lv_obj_get_child(ui_setting_display->transfers, 1);

    lv_obj_t *success_cue_label = lv_label_create(obj_son_1);
    lv_label_set_text(success_cue_label, "恭喜,设备连接成功!");
    lv_obj_set_style_text_font(success_cue_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(success_cue_label,1, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(success_cue_label, 6, LV_PART_MAIN);
    lv_obj_align(success_cue_label, LV_ALIGN_TOP_MID, -6, 100);

    //创建提示语
    lv_obj_t *ui_tipLabel = lv_label_create(obj_son_1);
    lv_label_set_text(ui_tipLabel, "请在手机上推送图书\n图片或固件升级!");
    lv_obj_set_style_text_font(ui_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_tipLabel,1, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui_tipLabel, 6, LV_PART_MAIN);
    lv_obj_align(ui_tipLabel, LV_ALIGN_TOP_MID, -6, 200);


}
