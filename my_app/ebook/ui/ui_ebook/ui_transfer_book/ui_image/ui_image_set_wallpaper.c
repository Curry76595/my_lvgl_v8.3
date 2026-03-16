#include "ui_image_set_wallpaper.h"

lv_obj_t *set_wallpaper_container[2];//确认按钮容器
char *set_wallpaper_confirm_text[2] = {"否", "是"};
char *set_Eng_wallpaper_confirm_text[2] = {"No", "Yes"};

/************************************************ui界面设计细节************************************************/
/**
 * @description: 选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_image_set_wallpaper_confirm_focus(lv_obj_t *obj, bool focus)
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

/**********************************************回调函数**********************************************/
/**
 * @description: 聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_image_set_wallpaper_confirm_focus_event_cb(lv_event_t *e){
    lv_obj_t *obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_image_set_wallpaper_confirm_focus(obj,true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_image_set_wallpaper_confirm_focus(obj,false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_image_set_wallpaper_confirm_key_event_cb(lv_event_t *e){
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
                        //隐藏弹窗,切换焦点组到图片显示的焦点组
                        lv_obj_add_flag(lv_obj_get_child(ui_image_display_list->ui_image_display, 2), LV_OBJ_FLAG_HIDDEN);
                        lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_display_group);
                        break;
                    case 1:
                        
                        break;    
                }
                
                break;
            case LV_KEY_ESC:
                //隐藏弹窗,切换焦点组到图片显示的焦点组
                lv_obj_add_flag(lv_obj_get_child(ui_image_display_list->ui_image_display, 2), LV_OBJ_FLAG_HIDDEN);
                lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_display_group);
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
static void ui_image_set_wallpaper_confirm_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_image_set_wallpaper_confirm_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_image_set_wallpaper_confirm_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_image_set_wallpaper_confirm_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}


/***************************************************初始化函数********************************************/
void ui_image_set_wallpaper_init(void){
      //1.创建一个弹窗容器
    lv_obj_t *pop_up = lv_obj_create(ui_image_display_list->ui_image_display);
    lv_obj_set_size(pop_up, 190, 120);
    lv_obj_set_style_border_color(pop_up, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(pop_up, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(pop_up, 10, LV_PART_MAIN);
    lv_obj_center(pop_up);

    //2.创建删除提示语
    lv_obj_t *set_wallpaper_cue = lv_label_create(pop_up);
    if(English_version){
        lv_label_set_text(set_wallpaper_cue, "  Set the current\nphoto as wallpaper?");
        lv_obj_set_style_text_letter_space(set_wallpaper_cue,0, LV_PART_MAIN);
    }else{
        lv_label_set_text(set_wallpaper_cue, "要把当前图设为壁纸?");
        lv_obj_set_style_text_letter_space(set_wallpaper_cue,1, LV_PART_MAIN);
    }
    lv_obj_set_style_text_font(set_wallpaper_cue,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(set_wallpaper_cue, LV_ALIGN_TOP_MID, 0, 5);
    
    //3.创建一个焦点组
    ui_image_display_list->ui_image_set_wallpaper_group = lv_group_create();
     //4.创建两个确认容器
    for(int i = 0; i < 2; i++){
        set_wallpaper_container[i] = lv_obj_create(pop_up);
        //设为聚焦的两个重要标志位
        lv_obj_add_flag(set_wallpaper_container[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(set_wallpaper_container[i], LV_OBJ_FLAG_SCROLLABLE); 
        //设置按钮容器的大小和样式
        lv_obj_set_size(set_wallpaper_container[i], 40, 32);
        lv_obj_set_style_border_color(set_wallpaper_container[i], lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_border_width(set_wallpaper_container[i], 1, LV_PART_MAIN);
        lv_obj_set_style_radius(set_wallpaper_container[i], 10, LV_PART_MAIN);
        lv_obj_align(set_wallpaper_container[i], LV_ALIGN_TOP_MID, -38+i*80, 50);
        //创建按钮容器里的标签
        lv_obj_t *label_text = lv_label_create(set_wallpaper_container[i]);
        if(English_version){
            lv_label_set_text(label_text, set_Eng_wallpaper_confirm_text[i]);
        }else{
            lv_label_set_text(label_text, set_wallpaper_confirm_text[i]);
        }
        lv_obj_set_style_text_font(label_text,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_center(label_text);
        
        ui_image_set_wallpaper_confirm_group_set(ui_image_display_list->ui_image_set_wallpaper_group,set_wallpaper_container[i],i);
    }
    //5.默认聚焦第一个【否】
    lv_group_focus_obj(set_wallpaper_container[0]);
    lv_obj_add_flag(pop_up, LV_OBJ_FLAG_HIDDEN);//默认隐藏弹窗
    

    //6.创建一个设置壁纸成功的提示语
    lv_obj_t *pop_up_wallpaper_success = lv_obj_create(ui_image_display_list->ui_image_display);
    lv_obj_clear_flag(pop_up_wallpaper_success, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(pop_up_wallpaper_success, 150, 60);
    lv_obj_set_style_border_color(pop_up_wallpaper_success, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_color(pop_up_wallpaper_success, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(pop_up_wallpaper_success, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(pop_up_wallpaper_success, 10, LV_PART_MAIN);
    lv_obj_center(pop_up_wallpaper_success);

    //7.创建设置成功提示语
    lv_obj_t *set_wallpaper_cue_success = lv_label_create(pop_up_wallpaper_success);
    if(English_version){
        lv_label_set_text(set_wallpaper_cue_success, "Wallpaper set\nsuccessfully");
    }else{
        lv_label_set_text(set_wallpaper_cue_success, "壁纸设置成功");
    }
    lv_obj_set_style_text_font(set_wallpaper_cue_success,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(set_wallpaper_cue_success,2, LV_PART_MAIN);
    lv_obj_set_style_text_color(set_wallpaper_cue_success, lv_color_white(), LV_PART_MAIN);
    lv_obj_center(set_wallpaper_cue_success);
    lv_obj_add_flag(pop_up_wallpaper_success, LV_OBJ_FLAG_HIDDEN);//默认隐藏设置成功提示语

}

