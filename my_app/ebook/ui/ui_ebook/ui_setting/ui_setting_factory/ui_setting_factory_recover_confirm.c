#include "ui_setting_factory_recover_confirm.h"

/***************************************申明变量*********************************/
lv_obj_t *start_confirm_container[2];
char *start_confirm_text[2] = {"否", "是"};
char *Eng_start_confirm_text[2] = {"No", "Yes"};

/************************************************ui界面设计细节************************************************/
/**
 * @description: 选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_setting_set_recover_confirm_focus(lv_obj_t *obj, bool focus)
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
static void ui_setting_factory_recover_confirm_focus_event_cb(lv_event_t *e){
    lv_obj_t *start_recover_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_setting_set_recover_confirm_focus(start_recover_obj,true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_setting_set_recover_confirm_focus(start_recover_obj,false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_factory_recover_confirm_key_event_cb(lv_event_t *e){
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
                switch(user_data){
                    case 0:
                        lv_indev_set_group(indev_keypad,ui_setting_display->ui_factory_start_recover_group);
                        ui_setting_factory_content_select(0);
                        break;
                    case 1:
                        ui_setting_factory_content_select(2);
                        break;    
                }
                
                break;
            case LV_KEY_ESC:
                lv_indev_set_group(indev_keypad,ui_setting_display->ui_factory_start_recover_group);
                ui_setting_factory_content_select(0);
                
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
static void ui_setting_factory_recover_confirm_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_setting_factory_recover_confirm_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_setting_factory_recover_confirm_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_setting_factory_recover_confirm_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}


/****************************************************初始化函数*****************************************************/

void ui_setting_factory_recover_confirm_init(void){
    //获取恢复出厂界面的第二个儿子
    lv_obj_t *obj_son_1 = lv_obj_get_child(ui_setting_display->factory, 1);
    
    //创建确认恢复提示语
    lv_obj_t *ui_confirm_tipLabel = lv_label_create(obj_son_1);
    if(English_version){
        lv_label_set_text(ui_confirm_tipLabel, "  Confirm whether\nto restore factory\n  settings?");
        lv_obj_align(ui_confirm_tipLabel, LV_ALIGN_TOP_MID, -6, 40);
    }else{
        lv_label_set_text(ui_confirm_tipLabel, "确定要操作恢复出厂?");
        lv_obj_align(ui_confirm_tipLabel, LV_ALIGN_TOP_MID, -6, 70);
    }
    lv_obj_set_style_text_font(ui_confirm_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_confirm_tipLabel,1, LV_PART_MAIN);
    

    //创建确认焦点组
    ui_setting_display->ui_factory_recover_confirm_group = lv_group_create();
    //创建确认选项容器
    for(int i = 0; i < 2; i++){
        start_confirm_container[i] = lv_obj_create(obj_son_1);
        //设为聚焦的两个重要标志位
        lv_obj_add_flag(start_confirm_container[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(start_confirm_container[i], LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
        //设置开始恢复容器的大小和样式
        lv_obj_set_size(start_confirm_container[i], 40, 32);
        lv_obj_set_style_border_width(start_confirm_container[i], 1, LV_PART_MAIN);
        lv_obj_set_style_border_color(start_confirm_container[i], lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_radius(start_confirm_container[i], 10, LV_PART_MAIN);
        lv_obj_align(start_confirm_container[i], LV_ALIGN_TOP_MID, -35+i*60, 110);
        //创建开始恢复容器里的标签
        lv_obj_t *label_text = lv_label_create(start_confirm_container[i]);
        if(English_version){
            lv_label_set_text(label_text, Eng_start_confirm_text[i]);
        }else{
            lv_label_set_text(label_text, start_confirm_text[i]);
        }
        lv_obj_set_style_text_font(label_text,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_center(label_text);
        
        //设置组和回调函数
        ui_setting_factory_recover_confirm_group_set(ui_setting_display->ui_factory_recover_confirm_group,start_confirm_container[i],i);
    }

    //创建提示语
    lv_obj_t *ui_tipLabel = lv_label_create(obj_son_1);
    if(English_version){
        lv_label_set_text(ui_tipLabel, "This operation will\nrestore the device to\nits factory settings.\nPersonal usage\nrecords will be lost.\nProceed with caution!");
        lv_obj_set_style_text_letter_space(ui_tipLabel,0, LV_PART_MAIN);
    }else{
        lv_label_set_text(ui_tipLabel, "温馨提示:\n操作后会恢复到出厂\n前配置,个人使用记录\n将会丢失,须谨慎!");
        lv_obj_set_style_text_letter_space(ui_tipLabel,1, LV_PART_MAIN);
    }
    lv_obj_set_style_text_font(ui_tipLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_tipLabel, 6, LV_PART_MAIN);
    lv_obj_align(ui_tipLabel, LV_ALIGN_TOP_MID, -6, 160);

    //默认聚焦【否】
    lv_group_focus_obj(start_confirm_container[0]);
    ui_setting_set_recover_confirm_focus(start_confirm_container[0],true);
}

