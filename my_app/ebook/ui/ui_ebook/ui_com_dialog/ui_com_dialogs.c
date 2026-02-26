#include "ui_com_dialogs.h"
#define UI_COM_DIALOG_LVGL_SWITCH  1
/**********************************************申明变量*********************************************/
static lv_obj_t *ui_dialog_container;//创建一个霸屏容器
static lv_obj_t *ui_dialog_content;//创建一个对话框内容容器
static lv_obj_t *ui_dialog_title;//创建一个对话框标题标签
static lv_obj_t *ui_confirm_container;//创建一个对话框确认容器
static lv_obj_t *confirm_btn[2];//创建一个对话框确认按钮
static lv_group_t *dialog_group;//创建当前焦点组
static lv_group_t *last_group;//创建上一个焦点组
static char *confirm_btn_text[2] = {"否","是"};
static lv_obj_t *ui_know_btn;//创建知道按钮

/**********************************************回调函数*********************************************/
/**
 * @description: 选项框选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_com_dialog_set_confirm_focus(lv_obj_t *obj, bool focus)
{
    lv_obj_t * child_obj = lv_obj_get_child(obj,0);
    if(child_obj == NULL) return;
    if(focus){//选中效果
        lv_obj_set_style_bg_color(obj, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_white(), LV_PART_MAIN);
    }
    else{//不选中效果
        lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_black(), LV_PART_MAIN);
    }
}


/**
 * @description: 选项框聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_com_dialog_focus_event_cb(lv_event_t *e){
    lv_obj_t *option = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
       ui_com_dialog_set_confirm_focus(option,true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
       ui_com_dialog_set_confirm_focus(option,false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_com_dialog_key_event_cb(lv_event_t *e){
    lv_group_t *current_group;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int user_data = (int)lv_event_get_user_data(e);
    printf("user_data:%d\n",user_data);
    if(lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN) || !lv_obj_is_valid(obj)){
        printf("HIDDEN or Invalid object\n");
        return;//如果当前对象是隐藏的或者是没建立的，则不处理事件，防止传输过程中被用户打断
    }
    lv_obj_t *focused_obj = lv_group_get_focused(lv_obj_get_group(obj));//获取当前聚焦对象
    
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
                    case 0://【否】
                        ui_com_dialogs_deinit();
                        break;
                    case 1://【是】
                        break;
                    case 2://【知道啦】
                        ui_com_dialogs_deinit();
                        break;    
                    case 3:
                        //传输失败，不做处理 
                        printf("Transmission failed, no action taken\n");
                        break;    
                }
                break;
            case LV_KEY_ESC:
                ui_com_dialogs_deinit();
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
static void ui_set_com_dialog_group(lv_group_t *group, lv_obj_t *obj, int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_com_dialog_focus_event_cb, LV_EVENT_FOCUSED,(void *)(intptr_t)user_data);
    lv_obj_add_event_cb(obj, ui_com_dialog_focus_event_cb, LV_EVENT_DEFOCUSED,(void *)(intptr_t)user_data);
    lv_obj_add_event_cb(obj, ui_com_dialog_key_event_cb, LV_EVENT_KEY,(void *)(intptr_t)user_data);
}


/*****************************************处理细节************************************************/
/**
 * @description:  选择 【否】【是】确认框，选择【知道啦】确认框，还是都不显示呢？
 * @param {int} select_index   0:【否】【是】确认框， 1:【知道啦】确认框，2：都不显示[用于处理传输失败]
 * @param {bool} fail_flag   true:传输失败， false:正在传输
 * @return {*}
 */ 
void select_confirm_content(int select_index, bool fail_flag){

    lv_obj_add_flag(confirm_btn[0], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(confirm_btn[1], LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_know_btn, LV_OBJ_FLAG_HIDDEN);
     switch(select_index){
        case 0:
            lv_group_focus_obj(confirm_btn[0]);
            ui_com_dialog_set_confirm_focus(confirm_btn[0], true);
            lv_obj_clear_flag(confirm_btn[0], LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(confirm_btn[1], LV_OBJ_FLAG_HIDDEN);
            break;
        case 1:
            lv_group_focus_obj(ui_know_btn);    
            ui_com_dialog_set_confirm_focus(ui_know_btn, true);
            lv_obj_clear_flag(ui_know_btn, LV_OBJ_FLAG_HIDDEN);
            break;
        case 2:
            if(fail_flag){
                //创建一个新对象，用于传输失败时退出
                lv_obj_t *fail_container = lv_obj_create(ui_dialog_container);
                lv_obj_set_size(fail_container, 1, 1);
                lv_obj_align(fail_container, LV_ALIGN_BOTTOM_MID, 0, 0);
                lv_obj_clear_flag(fail_container, LV_OBJ_FLAG_SCROLLABLE);
                lv_obj_add_flag(fail_container, LV_OBJ_FLAG_CLICKABLE);
                lv_obj_set_style_border_color(fail_container, lv_color_white(), LV_PART_MAIN);
                lv_obj_set_style_border_width(fail_container, 1, LV_PART_MAIN);
                ui_set_com_dialog_group(dialog_group,fail_container,3);
                lv_group_focus_obj(fail_container);
            }
            printf("<%s> hidden all\n", __func__);
            break;
     };
}

void set_content_text(const char *text){
    lv_label_set_text(ui_dialog_title,text);
}

/**********************************************初始化函数****************************************/
void ui_com_dialogs_init(void)
{

#if UI_COM_DIALOG_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif
    

    if(lv_obj_is_valid(ui_dialog_container)){
        printf("<%s> ui_main already created!", __func__);
        return;
    }

    last_group = lv_group_get_default();//先保留上一个焦点组
    dialog_group = lv_group_create();//创建当前焦点组
    lv_group_set_default(dialog_group);//设置当前的焦点组为默认组
    lv_indev_set_group(indev_keypad, dialog_group);

    //创建一个霸屏容器
    ui_dialog_container = lv_obj_create(lv_layer_top());
    lv_obj_clear_flag(ui_dialog_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_dialog_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(ui_dialog_container, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));

    //创建一个对话框内容容器
    ui_dialog_content = lv_obj_create(ui_dialog_container);
    lv_obj_set_size(ui_dialog_content, 200, 300);
    lv_obj_center(ui_dialog_content);
    lv_obj_set_style_border_color(ui_dialog_content, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_dialog_content, 1, LV_PART_MAIN);

    //创建一个对话框标题标签
    ui_dialog_title = lv_label_create(ui_dialog_content);
    lv_obj_set_width(ui_dialog_title, 198);
    lv_obj_align(ui_dialog_title, LV_ALIGN_TOP_MID, 0, 48);
    lv_obj_set_style_text_font(ui_dialog_title, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_dialog_title, 10, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_dialog_title, lv_color_black(), LV_PART_MAIN);
    char str[128] = "红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3红楼梦3";
    lv_label_set_text_fmt(ui_dialog_title, "嗨,侦测到图书\n%.50s...\n从你手机飞奔过来,\n已完成",str);
    lv_obj_set_style_text_align(ui_dialog_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    //创建一个对话框确认容器
    ui_confirm_container = lv_obj_create(ui_dialog_content);
    lv_obj_set_size(ui_confirm_container, 150, 60);
    lv_obj_align(ui_confirm_container, LV_ALIGN_BOTTOM_MID, 0, -25);
    lv_obj_set_style_border_color(ui_confirm_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_confirm_container, 1, LV_PART_MAIN);

    for(int i = 0; i < 2; i++){
        //创建选项容器
        confirm_btn[i] = lv_obj_create(ui_confirm_container);
        lv_obj_clear_flag(confirm_btn[i], LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_flag(confirm_btn[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_size(confirm_btn[i], 35, 30);
        lv_obj_align(confirm_btn[i], LV_ALIGN_LEFT_MID, 15+60*i, 0);
        lv_obj_set_style_border_color(confirm_btn[i], lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_border_width(confirm_btn[i], 1, LV_PART_MAIN);
        lv_obj_set_style_radius(confirm_btn[i], 5, LV_PART_MAIN);

        //创建选项标签
        lv_obj_t *label = lv_label_create(confirm_btn[i]);
        lv_obj_center(label);
        lv_label_set_text(label, confirm_btn_text[i]);
        lv_obj_set_style_text_font(label, &Chinese_font_16, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
        
        //设置组和回调函数
        ui_set_com_dialog_group(dialog_group,confirm_btn[i],i);
    }
    
    //创建知道选项
    ui_know_btn = lv_obj_create(ui_confirm_container);
    lv_obj_center(ui_know_btn);
    lv_obj_clear_flag(ui_know_btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_know_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(ui_know_btn, 70, 30);
    lv_obj_set_style_border_color(ui_know_btn, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_know_btn, 1, LV_PART_MAIN);

    //创建知道选项标签
    lv_obj_t *know_label = lv_label_create(ui_know_btn);
    lv_obj_center(know_label);
    lv_label_set_text(know_label, "知道啦");
    lv_obj_set_style_text_font(know_label, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(know_label, lv_color_black(), LV_PART_MAIN);
    //设置组和回调函数
    ui_set_com_dialog_group(dialog_group,ui_know_btn,2);

    select_confirm_content(1,true);
}


void ui_com_dialogs_deinit(void)
{
    if(dialog_group != NULL){
        lv_group_del(dialog_group);
        dialog_group = NULL;
    }

    if(ui_dialog_container != NULL){
        lv_obj_del(ui_dialog_container);
        ui_dialog_container = NULL;
    }
    
    if(last_group != NULL){
        lv_group_set_default(last_group);
        lv_indev_set_group(indev_keypad, last_group);
        last_group = NULL;
    }
}




