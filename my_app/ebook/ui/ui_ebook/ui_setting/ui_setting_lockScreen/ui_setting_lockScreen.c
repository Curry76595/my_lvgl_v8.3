#include "ui_setting_lockScreen.h"


/**************************************************申明变量*********************************************/
#define UI_LOCKSCREEN_TIME_NUM     4
//选项状态枚举
typedef enum{
    OPTION_STATE_NORMAL = 0, //非聚焦状态
    OPTION_STATE_FOCUSED,    //聚焦状态
    OPTION_STATE_SELECTED    //选中状态
}option_state_t;

//选项图片资源-->[状态][选项索引]
static const lv_img_dsc_t *time_option_images[3][UI_LOCKSCREEN_TIME_NUM] = {
    {&minutes,&minutes,&minutes,&minutes},
    {&selected,&selected,&selected,&selected},
    {&new_selected,&new_selected,&new_selected,&new_selected}
};

//存储每个选项的当前状态,默认全部非聚焦状态
option_state_t option_states[UI_LOCKSCREEN_TIME_NUM] = {OPTION_STATE_NORMAL};
//存储每个选项的图片对象指针，默认全部为NULL
lv_obj_t *option_img_objs[UI_LOCKSCREEN_TIME_NUM] = {NULL};

/**********************************************设置锁屏ui设计细节************************************************/
/**
 * @description: 创建锁屏时间选项图像
 * @param {lv_obj_t} *parent
 * @param {int} index
 * @param {int} imgPos_x
 * @param {int} imgPos_y
 * @return {*}
 */
lv_obj_t *ui_create_optionImg(lv_obj_t *parent, int index, int imgPos_x, int imgPos_y){
    if(index <0 || index >= UI_LOCKSCREEN_TIME_NUM) return NULL;

    lv_obj_t *img = lv_img_create(parent);
    //初始显示非聚焦状态的图片
    const lv_img_dsc_t *img_src = time_option_images[OPTION_STATE_NORMAL][index];
    if(img_src != NULL){
        lv_img_set_src(img, img_src);
    }

    lv_obj_align(img, LV_ALIGN_TOP_MID, imgPos_x, imgPos_y);

    //使图片对象可以点击
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img, LV_OBJ_FLAG_SCROLLABLE);

    return img;      
}

/**
 * @description: 更新指定选项的图片显示
 * @param {int} index
 * @param {option_state_t} state
 * @return {*}
 */
static void ui_update_optionImg(int index, option_state_t state){
    if(index <0 || index >= UI_LOCKSCREEN_TIME_NUM) return;
    if(option_img_objs[index] == NULL) return;

    const lv_img_dsc_t *img_src = time_option_images[state][index];
    if(img_src != NULL){
        lv_img_set_src(option_img_objs[index], img_src);
    }
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
    int option_index = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        //聚焦时，如果当前不为选中状态，则显示聚焦图片
        if(option_states[option_index] != OPTION_STATE_SELECTED){
            ui_update_optionImg(option_index, OPTION_STATE_FOCUSED);
        }
    }else if(code == LV_EVENT_DEFOCUSED){
        //非聚焦时，如果当前不为选中状态，则显示非聚焦图片
        if(option_states[option_index] != OPTION_STATE_SELECTED){
            ui_update_optionImg(option_index, OPTION_STATE_NORMAL);
        }
    }
}

/**
 * @description: 锁屏时间按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_lockScreen_key_event_cb(lv_event_t *e){
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
                        if(option_states[user_data] != OPTION_STATE_SELECTED){
                            for(int i=0; i<UI_LOCKSCREEN_TIME_NUM; i++){
                                if(option_states[i] == OPTION_STATE_SELECTED){
                                    option_states[i] = OPTION_STATE_NORMAL;
                                    ui_update_optionImg(i, OPTION_STATE_NORMAL);
                                    break;
                                } 
                            }
                            option_states[user_data] = OPTION_STATE_SELECTED;
                            ui_update_optionImg(user_data, OPTION_STATE_SELECTED);
                        }
                        break;
                    case 1://20分钟
                        if(option_states[user_data] != OPTION_STATE_SELECTED){
                            for(int i=0; i<UI_LOCKSCREEN_TIME_NUM; i++){
                                if(option_states[i] == OPTION_STATE_SELECTED){
                                    option_states[i] = OPTION_STATE_NORMAL;
                                    ui_update_optionImg(i, OPTION_STATE_NORMAL);
                                    break;
                                } 
                            }
                            option_states[user_data] = OPTION_STATE_SELECTED;
                            ui_update_optionImg(user_data, OPTION_STATE_SELECTED);
                        }
                        
                       break; 
                    case 2://35分钟
                        if(option_states[user_data] != OPTION_STATE_SELECTED){
                            for(int i=0; i<UI_LOCKSCREEN_TIME_NUM; i++){
                                if(option_states[i] == OPTION_STATE_SELECTED){
                                    option_states[i] = OPTION_STATE_NORMAL;
                                    ui_update_optionImg(i, OPTION_STATE_NORMAL);
                                    break;
                                } 
                            }
                            option_states[user_data] = OPTION_STATE_SELECTED;
                            ui_update_optionImg(user_data, OPTION_STATE_SELECTED);
                        }
                        
                        break;
                    case 3://自动关闭
                        if(option_states[user_data] != OPTION_STATE_SELECTED){
                            for(int i=0; i<UI_LOCKSCREEN_TIME_NUM; i++){
                               if(option_states[i] == OPTION_STATE_SELECTED){
                                    option_states[i] = OPTION_STATE_NORMAL;
                                    ui_update_optionImg(i, OPTION_STATE_NORMAL);
                                    break;
                                } 
                            }
                            option_states[user_data] = OPTION_STATE_SELECTED;
                            ui_update_optionImg(user_data, OPTION_STATE_SELECTED);
                        }
                        break;
                    default:
                        break;    
                }
                break;
            case LV_KEY_ESC:
                 lv_indev_set_group(indev_keypad,ui_setting_display->ui_menu_group);
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
/************************************************外部调用接口*************************************************/
void set_lockScreen_firstOptionFocus(void){
    option_states[0] = OPTION_STATE_FOCUSED;
    ui_update_optionImg(0, OPTION_STATE_FOCUSED);
}

/*************************************************设置锁屏界面初始化*********************************************/

void ui_setting_lockScreen_init(void){
    //1.标题
    lv_obj_t *ui_titleLabel = lv_label_create(ui_setting_display->lockScreen);
    lv_label_set_text(ui_titleLabel, "待机后自动关机时长");
    lv_obj_set_style_text_font(ui_titleLabel,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_titleLabel,1, LV_PART_MAIN);
    lv_obj_align(ui_titleLabel, LV_ALIGN_TOP_MID, -3, 20);
    //2.创建焦点组
    ui_setting_display->ui_lockScreen_group = lv_group_create();
    //3.创建时间选项
    for(int i=0; i<UI_LOCKSCREEN_TIME_NUM; i++){
        option_img_objs[i] = ui_create_optionImg(ui_setting_display->lockScreen,i,0,50+i*48);
        ui_set_lockScreen_group(ui_setting_display->ui_lockScreen_group,option_img_objs[i],i);
    }
    //4.默认选中最后一个（暂定，后期要读写文件获取）
    option_states[3] = OPTION_STATE_SELECTED;
    ui_update_optionImg(3, OPTION_STATE_SELECTED);
}



