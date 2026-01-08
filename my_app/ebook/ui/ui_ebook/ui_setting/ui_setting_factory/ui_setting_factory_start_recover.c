#include "ui_setting_factory_start_recover.h"

/************************************************ui界面设计细节************************************************/
/**
 * @description: 开始选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_setting_set_start_recover_focus(lv_obj_t *obj, bool focus)
{
    lv_obj_t * child_obj = lv_obj_get_child(obj,0);
    if(focus){//选中效果
        lv_obj_set_style_bg_color(obj, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_white(), LV_PART_MAIN);
    }
    else{//不选中效果
        lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_black(), LV_PART_MAIN);
    }
}


/****************************************************回调函数*****************************************************/

/**
 * @description: 聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_factory_start_recover_focus_event_cb(lv_event_t *e){
    lv_obj_t *start_recover_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_setting_set_start_recover_focus(start_recover_obj,true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_setting_set_start_recover_focus(start_recover_obj,false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_factory_start_recover_key_event_cb(lv_event_t *e){
    lv_group_t *current_group;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *focused_obj = lv_group_get_focused(lv_obj_get_group(obj));//获取当前聚焦对象
    int user_data = (int)lv_event_get_user_data(e);
    if(focused_obj){//获取当前聚焦对象的组
        current_group = lv_obj_get_group(focused_obj);
    }
    if(code == LV_EVENT_KEY){
        uint32_t KEY = lv_event_get_key(e);
        switch(KEY){
            case LV_KEY_LEFT:
                if(current_group) lv_group_focus_prev(current_group);
                break;
            case LV_KEY_RIGHT:
                if(current_group) lv_group_focus_next(current_group);
                break;
            case LV_KEY_ENTER:
                lv_indev_set_group(indev_keypad,ui_setting_display->ui_factory_recover_confirm_group);
                ui_setting_factory_content_select(1);
                break;
            case LV_KEY_ESC:
                //退出之前先清除聚焦状态
                lv_obj_t *focus_obj = lv_obj_get_child(lv_obj_get_child(ui_setting_display->factory, 0),0);
                lv_obj_clear_flag(focus_obj, LV_STATE_FOCUSED);
                ui_setting_set_start_recover_focus(focus_obj,false);
                lv_indev_set_group(indev_keypad,ui_setting_display->ui_menu_group);
                break;
            default:
                break;
        }

    }

}

/**
 * @description: 设置组函数和回调函数
 * @param {lv_obj_t} *obj
 * @return {*}
 */
static void ui_setting_factory_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_setting_factory_start_recover_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_setting_factory_start_recover_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_setting_factory_start_recover_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}


/*************************************************开始恢复界面初始化*********************************************/
void ui_setting_factory_start_recover_init(void){
    //获取恢复出厂界面的第一个儿子
    lv_obj_t *obj_son_0 = lv_obj_get_child(ui_setting_display->factory, 0);
    //创建开始恢复容器
    lv_obj_t *start_recover_container = lv_obj_create(obj_son_0);
    //设为的聚焦两个重要标志位
    lv_obj_add_flag(start_recover_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(start_recover_container, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
    //设置开始恢复容器的大小和样式
    lv_obj_set_size(start_recover_container, 89, 32);
    lv_obj_set_style_border_width(start_recover_container, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(start_recover_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_radius(start_recover_container, 10, LV_PART_MAIN);
    lv_obj_align(start_recover_container, LV_ALIGN_TOP_MID, 0, 80);
    //创建开始恢复容器里的标签
    lv_obj_t *label_text = lv_label_create(start_recover_container);
    lv_label_set_text(label_text, "开始恢复");
    lv_obj_set_style_text_font(label_text,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(label_text,2, LV_PART_MAIN);
    lv_obj_center(label_text);
   
    //创建开始恢复容器的焦点组
    ui_setting_display->ui_factory_start_recover_group = lv_group_create();

    //设置开始恢复容器的焦点组和回调函数
    ui_setting_factory_group_set(ui_setting_display->ui_factory_start_recover_group,start_recover_container,0);
    // lv_group_focus_obj(start_recover_container);

    //创建提示语
    lv_obj_t *ui_tipLabel = lv_label_create(obj_son_0);
    lv_label_set_text(ui_tipLabel, "温馨提示:\n操作后会恢复到出厂\n前配置,个人使用记录\n将会丢失,须谨慎!");
    lv_obj_set_style_text_font(ui_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_tipLabel,1, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui_tipLabel, 6, LV_PART_MAIN);
    lv_obj_align(ui_tipLabel, LV_ALIGN_TOP_MID, -6, 170);

}



