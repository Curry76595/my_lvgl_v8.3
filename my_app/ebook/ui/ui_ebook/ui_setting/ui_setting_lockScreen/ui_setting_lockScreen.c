#include "ui_setting_lockScreen.h"


/**************************************************申明变量*********************************************/
#define UI_LOCKSCREEN_TIME_OPTION_NUM     4

static const char *lockScreen_time_options[UI_LOCKSCREEN_TIME_OPTION_NUM] = {
    "5分钟",
    "20分钟",
    "35分钟",
    "自动关闭"
};

static const char *Eng_lockScreen_time_options[UI_LOCKSCREEN_TIME_OPTION_NUM] = {
    "5 min",
    "20 min",
    "35 min",
    "Disable"
};


static int lock_time_selected_obj = 3; 
int exit_flag = 0;

lv_obj_t *lockTimeOption[UI_LOCKSCREEN_TIME_OPTION_NUM];

/**********************************************设置锁屏ui设计细节************************************************/
static void ui_lock_time_focus_option(lv_obj_t *obj, bool is_focus){
    if(is_focus){
        lv_obj_set_style_bg_color(obj, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(obj, 0), lv_color_white(), LV_PART_MAIN);
    }else{
        lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(lv_obj_get_child(obj, 0), lv_color_black(), LV_PART_MAIN);
    }
}


static void ui_clear_prv_selected_option(void){
    lv_obj_t *label = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 0);
    lv_obj_t *img = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 1);
    lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
    lv_obj_center(label);
}

static void ui_current_selected_option(void){
    lv_obj_t *label = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 0);
    lv_obj_t *img = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 1);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(img, &selected);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_LEFT_MID, 1, 0);
}

/*************************************************设置锁屏回调函数***************************************/
/**
 * @description: 锁屏时间聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_lockScreen_focus_event_cb(lv_event_t *e){
    lv_obj_t *lockTimeSelect = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *label = lv_obj_get_child(lockTimeSelect, 0);
    lv_obj_t *img = lv_obj_get_child(lockTimeSelect, 1);
    int option_index = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_lock_time_focus_option(lockTimeSelect, true);
        if(option_index == lock_time_selected_obj){
            lv_obj_clear_flag(lv_obj_get_child(lockTimeSelect, 1), LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(img, &selected);
            lv_obj_align_to(label, img, LV_ALIGN_OUT_LEFT_MID, 1, 0);
        }else{
            lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
            lv_obj_center(label);
        }
        
    }else if(code == LV_EVENT_DEFOCUSED){
        ui_lock_time_focus_option(lockTimeSelect, false);
        if(option_index == lock_time_selected_obj){
            lv_obj_clear_flag(lv_obj_get_child(lockTimeSelect, 1), LV_OBJ_FLAG_HIDDEN);
            lv_img_set_src(img, &selected_reverse);
            lv_obj_align_to(label, img, LV_ALIGN_OUT_LEFT_MID, 1, 0);
        }else{
            lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
            lv_obj_center(label);
        }
    }
}

/**
 * @description: 锁屏时间按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_lockScreen_key_event_cb(lv_event_t *e){
    lv_obj_t *label;
    lv_obj_t *img;
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
            case LV_KEY_ENTER://选定要选的选项
                switch (user_data){
                    case 0://5分钟
                        ui_clear_prv_selected_option();
                        lock_time_selected_obj = 0;
                        ui_current_selected_option();
                        break;
                    case 1://20分钟
                        ui_clear_prv_selected_option();
                        lock_time_selected_obj = 1;
                        ui_current_selected_option();
                        break; 
                    case 2://35分钟
                        ui_clear_prv_selected_option();
                        lock_time_selected_obj = 2;
                        ui_current_selected_option();
                        break;
                    case 3://自动关闭
                        ui_clear_prv_selected_option();
                        lock_time_selected_obj = 3;
                        ui_current_selected_option();
                    default:
                        break;    
                }
                break;
            case LV_KEY_ESC:
                lv_indev_set_group(indev_keypad,ui_setting_display->ui_menu_group);
                exit_flag = 1;
                break;
            default:
                break;
        }

    }

}

/**
 * @description: 设置组函数和回调函数
 * @param {lv_group_t} *group
 * @param {lv_obj_t} *obj
 * @param {int} user_data
 * @return {*}
 */
static void ui_set_lockScreen_group(lv_group_t *group, lv_obj_t *obj, int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_setting_lockScreen_focus_event_cb, LV_EVENT_FOCUSED,(void *)(intptr_t)user_data);
    lv_obj_add_event_cb(obj, ui_setting_lockScreen_focus_event_cb, LV_EVENT_DEFOCUSED,(void *)(intptr_t)user_data);
    lv_obj_add_event_cb(obj, ui_setting_lockScreen_key_event_cb, LV_EVENT_KEY,(void *)(intptr_t)user_data);
}

/****************************************************外部调用接口函数********************************************/
void ui_set_lock_screen_first_focus(void){
    ui_lock_time_focus_option(lockTimeOption[0], true); 
}
void ui_set_lcok_screen_default_option(void){
    //获取当前焦点对象
    lv_obj_t *focused_obj = lv_group_get_focused(lv_obj_get_group(lockTimeOption[lock_time_selected_obj]));
    lv_obj_t *label = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 0);
    lv_obj_t *img = lv_obj_get_child(lockTimeOption[lock_time_selected_obj], 1);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
    if(focused_obj == lockTimeOption[lock_time_selected_obj]){
        lv_img_set_src(img, &selected);
    }else{
        lv_img_set_src(img, &selected_reverse);
    }
    lv_obj_align_to(label, img, LV_ALIGN_OUT_LEFT_MID, 1, 0);
}

int get_lock_screen_exit_flag(void){
    return exit_flag;
}
/*************************************************设置锁屏界面初始化*********************************************/

void ui_setting_lockScreen_init(void){
    //1.标题
    lv_obj_t *ui_titleLabel = lv_label_create(ui_setting_display->lockScreen);
    if(English_version){
        lv_label_set_text(ui_titleLabel, "Time until automatic\n  shut-off during");
         lv_obj_set_style_text_letter_space(ui_titleLabel,0.8, LV_PART_MAIN);
    }else{
        lv_label_set_text(ui_titleLabel, "待机后自动关机时长");
        lv_obj_set_style_text_letter_space(ui_titleLabel,1, LV_PART_MAIN);
    }
    lv_obj_set_style_text_font(ui_titleLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_titleLabel, LV_ALIGN_TOP_MID, -3, 20);
   
    //2.创建一个存放选项的容器
    lv_obj_t *lockTime_container = lv_obj_create(ui_setting_display->lockScreen);
    lv_obj_remove_style_all(lockTime_container);
    lv_obj_set_size(lockTime_container, 120, 200);
    lv_obj_align(lockTime_container, LV_ALIGN_TOP_MID, 0, 60);
    
    //3.创建锁屏焦点组
    ui_setting_display->ui_lockScreen_group = lv_group_create();
    //4.设置容器的弹性布局
    lv_obj_set_flex_flow(lockTime_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(lockTime_container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    for(int i=0; i<UI_LOCKSCREEN_TIME_OPTION_NUM; i++){
        //4.1创建选项容器
        lockTimeOption[i] = lv_obj_create(lockTime_container);
        lv_obj_remove_style_all(lockTimeOption[i]);
        lv_obj_set_size(lockTimeOption[i], 100, 33);
        lv_obj_set_style_border_width(lockTimeOption[i], 1, LV_PART_MAIN);
        lv_obj_set_style_border_color(lockTimeOption[i], lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_radius(lockTimeOption[i], 10, LV_PART_MAIN);
        //4.2创建标签
        lv_obj_t *lockTimeLabel = lv_label_create(lockTimeOption[i]);
        if(English_version){
            lv_label_set_text(lockTimeLabel, Eng_lockScreen_time_options[i]);
        }else{
            lv_label_set_text(lockTimeLabel, lockScreen_time_options[i]);
        }
        lv_obj_set_style_text_font(lockTimeLabel,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(lockTimeLabel,1, LV_PART_MAIN);
        lv_obj_align(lockTimeLabel, LV_ALIGN_CENTER, 0, 0);
        //4.3创建图片
        lv_obj_t *img = lv_img_create(lockTimeOption[i]);
        lv_img_set_src(img, &selected);
        lv_obj_align(img, LV_ALIGN_RIGHT_MID, -4, 0);
        lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
        //4.4设置回调函数和焦点组
        ui_set_lockScreen_group(ui_setting_display->ui_lockScreen_group, lockTimeOption[i], i);
    }
}



