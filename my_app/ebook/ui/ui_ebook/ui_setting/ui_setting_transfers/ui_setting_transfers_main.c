#include "ui_setting_transfers_main.h"
#include "ui_setting_transfers_connect.h"
#include "ui_setting_transfers_success.h"
/**
 * @description: 传输界面选择
 * @param {int} content_index
 * @return {*}
 */
void ui_setting_transfers_content_select(int content_index){
    lv_obj_t *obj = ui_setting_display->transfers;
    lv_obj_t *obj_son_0 = lv_obj_get_child(obj, 0);
    lv_obj_t *obj_son_1 = lv_obj_get_child(obj, 1);
    lv_obj_add_flag(obj_son_0, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_son_1, LV_OBJ_FLAG_HIDDEN);
    switch(content_index){
        case 0:
            lv_obj_clear_flag(obj_son_0, LV_OBJ_FLAG_HIDDEN);
            break;
        case 1:
            lv_obj_clear_flag(obj_son_1, LV_OBJ_FLAG_HIDDEN);
            break;
        default:
            break;
    }
}


void ui_setting_transfers_main_init(int content_index){

    //创建连接提示语容器
    lv_obj_t *ui_transfers_connect_cue = lv_obj_create(ui_setting_display->transfers);
    lv_obj_remove_style_all(ui_transfers_connect_cue);
    lv_obj_set_size(ui_transfers_connect_cue, 190, 323);
    lv_obj_align(ui_transfers_connect_cue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui_transfers_connect_cue, LV_OBJ_FLAG_HIDDEN);//默认隐藏

    //创建成功提示语容器
    lv_obj_t *ui_transfers_success_cue = lv_obj_create(ui_setting_display->transfers);
    lv_obj_remove_style_all(ui_transfers_success_cue);
    lv_obj_set_size(ui_transfers_success_cue, 190, 323);
    lv_obj_align(ui_transfers_success_cue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui_transfers_success_cue, LV_OBJ_FLAG_HIDDEN);//默认隐藏
 
 
    ui_setting_transfers_connect_init();//连接提示语
    ui_setting_transfers_success_init();//成功提示语

    //默认选择开始恢复界面
    ui_setting_transfers_content_select(content_index);
}

