#include "ui_setting_factory_main.h"
#include "ui_setting_factory_start_recover.h"
#include "ui_setting_factory_recover_confirm.h"
#include "ui_setting_factory_cue.h"

/**
 * @description: 出厂界面选择
 * @param {int} content_index
 * @return {*}
 */
void ui_setting_factory_content_select(int content_index){
       lv_obj_t *obj = ui_setting_display->factory;
       lv_obj_t *obj_son_0 = lv_obj_get_child(obj, 0);
       lv_obj_t *obj_son_1 = lv_obj_get_child(obj, 1);
       lv_obj_t *obj_son_2 = lv_obj_get_child(obj, 2);
       lv_obj_add_flag(obj_son_0, LV_OBJ_FLAG_HIDDEN);
       lv_obj_add_flag(obj_son_1, LV_OBJ_FLAG_HIDDEN);
       lv_obj_add_flag(obj_son_2, LV_OBJ_FLAG_HIDDEN);
       switch(content_index){
            case 0:
                lv_obj_clear_flag(obj_son_0, LV_OBJ_FLAG_HIDDEN);
                break;
            case 1:
                lv_obj_clear_flag(obj_son_1, LV_OBJ_FLAG_HIDDEN);
                break;
            case 2:
                lv_obj_clear_flag(obj_son_2, LV_OBJ_FLAG_HIDDEN);
                break;
            default:
                break;
        }
}


void ui_setting_factory_main_init(void){
    //创建开始恢复容器
    lv_obj_t *ui_factory_start = lv_obj_create(ui_setting_display->factory);
    lv_obj_remove_style_all(ui_factory_start);
    lv_obj_set_size(ui_factory_start, 190, 323);
    lv_obj_align(ui_factory_start, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui_factory_start, LV_OBJ_FLAG_HIDDEN);//默认隐藏

    //创建确认恢复容器
    lv_obj_t *ui_factory_confirm = lv_obj_create(ui_setting_display->factory);
    lv_obj_remove_style_all(ui_factory_confirm);
    lv_obj_set_size(ui_factory_confirm, 190, 323);
    lv_obj_align(ui_factory_confirm, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui_factory_confirm, LV_OBJ_FLAG_HIDDEN);//默认隐藏

    //创建提示语容器
    lv_obj_t *ui_factory_cue = lv_obj_create(ui_setting_display->factory);
    lv_obj_remove_style_all(ui_factory_cue);
    lv_obj_set_size(ui_factory_cue, 190, 323);
    lv_obj_align(ui_factory_cue, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(ui_factory_cue, LV_OBJ_FLAG_HIDDEN);//默认隐藏
 
    ui_setting_factory_start_recover_init();//开始恢复
    ui_setting_factory_recover_confirm_init();//确认恢复
    ui_setting_factory_cue_init();//恢复勿退出提示语
    //默认选择开始恢复界面
    ui_setting_factory_content_select(0);
    
}

