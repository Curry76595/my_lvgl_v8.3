#include "ui_transfer_book_main.h"
#define UI_TRANSFER_BOOK_MAIN_LVGL_SWITCH 1
/*********************************************申明变量******************************************************/
#define UI_TRANSFER_MENU_NUM 3

ui_transfer_book_t *ui_transfer_book_list;
lv_obj_t *ui_transfer_title;
char *ui_transfer_menu_name[UI_TRANSFER_MENU_NUM] = {"传书操作说明","自带预览图片","我的传图"};
lv_obj_t *ui_transfer_menu_container[UI_TRANSFER_MENU_NUM];//创建菜单容器

/***********************************************内存申请*******************************/
//申请内存
static void ui_transfer_book_malloc(void){
    if(ui_transfer_book_list == NULL){
        ui_transfer_book_list = (ui_transfer_book_t *)malloc(sizeof(ui_transfer_book_t));
        if(ui_transfer_book_list == NULL) return;
        memset(ui_transfer_book_list,0,sizeof(ui_transfer_book_t));
    }
}

//释放内存
static void ui_transfer_free(void){
    if(ui_transfer_book_list != NULL){
        free(ui_transfer_book_list);
        ui_transfer_book_list = NULL;
    }
}


/***************************************************UI设置细节**************************************************/
/**
 * @description: 菜单选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_transfer_set_menu_focus(lv_obj_t *obj, bool focus)
{
    if(focus){//选中效果
        lv_obj_set_style_border_color(obj, lv_color_black(), LV_PART_MAIN);
    }
    else{//不选中效果
        lv_obj_set_style_border_color(obj, lv_color_white(), LV_PART_MAIN);
    }
}

/*************************************************传书模块回调函数**********************************************/

/**
 * @description: 菜单聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_transfer_focus_event_cb(lv_event_t *e){
    lv_obj_t *transfer_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_transfer_set_menu_focus(transfer_obj, true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_transfer_set_menu_focus(transfer_obj, false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_transfer_key_event_cb(lv_event_t *e){
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
                    ui_operation_notice_init();
                    break;
                    case 2:
                    ui_image_main_init();
                    break;
                }
                break;
            case LV_KEY_ESC:
                // appTransferBook_startActionState(APP_TRANSFER_BOOK_ACTION_MENU, UI_TRANSFER_BOOK_REFRESH_EXIT, NULL);
                break; 
            default:
                break;
        }

    }

}

/*********************************************封装回调函数**************************************************/
static void ui_transfer_menu_group_set(lv_group_t *group, lv_obj_t *obj, int user_data){
    lv_group_add_obj(group, obj);
     lv_obj_add_event_cb(obj, ui_transfer_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_transfer_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_transfer_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}
/********************************************初始化函数*****************************************************/
static void ui_transfer_book_main_init(void){
#if UI_TRANSFER_BOOK_MAIN_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif

    //申请内存
    ui_transfer_book_malloc();

    //创建主页面
    ui_transfer_book_list->main_page = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_transfer_book_list->main_page, 240, 360);
    lv_obj_clear_flag(ui_transfer_book_list->main_page, LV_OBJ_FLAG_SCROLLABLE);

    //创建标题-退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_transfer_book_list->main_page);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_transfer_book_list->main_page, LV_ALIGN_TOP_LEFT, -6, -8);
    lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_width(ui_exit, 0, 0);
    lv_obj_set_style_radius(ui_exit, 0, 0);
    lv_obj_set_style_pad_all(ui_exit, 0, 0);
    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align_to(ui_exit_img, ui_exit, LV_ALIGN_TOP_LEFT, 0, 0);

    //创建标题-显示标签
    ui_transfer_title = lv_label_create(ui_transfer_book_list->main_page);
    lv_label_set_text(ui_transfer_title, "传书");
    lv_obj_set_style_text_font(ui_transfer_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_transfer_title,2, LV_PART_MAIN);
    lv_obj_align(ui_transfer_title, LV_ALIGN_TOP_LEFT, 10, -8);

    //创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_transfer_book_list->main_page);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);

    //创建新的焦点组
    ui_transfer_book_list->last_group = lv_group_get_default();//先保留上一个焦点组
    ui_transfer_book_list->main_group = lv_group_create();//创建当前焦点组
    lv_group_set_default(ui_transfer_book_list->main_group);//设置当前的焦点组为默认组
    lv_indev_set_group(indev_keypad, ui_transfer_book_list->main_group);
    
    
    //创建菜单列表显示容器
    lv_obj_t *display_menu_container = lv_obj_create(ui_transfer_book_list->main_page);
    lv_obj_clear_flag(display_menu_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(display_menu_container, LV_ALIGN_TOP_MID, 0, 23);
    lv_obj_set_style_border_color(display_menu_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(display_menu_container, 1, LV_PART_MAIN);
    lv_obj_set_size(display_menu_container, 235, 335);
    for(int i = 0; i < UI_TRANSFER_MENU_NUM; i++){
        ui_transfer_menu_container[i] = lv_obj_create(display_menu_container);
        lv_obj_add_flag(ui_transfer_menu_container[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(ui_transfer_menu_container[i], LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(ui_transfer_menu_container[i], 223, 45);
        lv_obj_align(ui_transfer_menu_container[i], LV_ALIGN_TOP_MID, -1, -10+i*53);
        lv_obj_set_style_radius(ui_transfer_menu_container[i], 10, LV_PART_MAIN);
        lv_obj_set_style_border_color(ui_transfer_menu_container[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(ui_transfer_menu_container[i], 1, LV_PART_MAIN);

        //创建图片显示的图案
        lv_obj_t *image_name_img = lv_img_create(ui_transfer_menu_container[i]);
        if(i != 0){
            lv_img_set_src(image_name_img, &picture);
            lv_obj_set_size(image_name_img, picture.header.w, picture.header.h);
        }else{
            lv_img_set_src(image_name_img, &txt);
            lv_obj_set_size(image_name_img, txt.header.w, txt.header.h);
        }
        lv_obj_align(image_name_img, LV_ALIGN_LEFT_MID, 0, 0);
        //创建图片显示的文本
        lv_obj_t *image_name_label = lv_label_create(ui_transfer_menu_container[i]);
        lv_label_set_text(image_name_label, ui_transfer_menu_name[i]);
        lv_obj_set_style_text_font(image_name_label,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(image_name_label,2, LV_PART_MAIN);
        lv_obj_align_to(image_name_label, image_name_img,LV_ALIGN_OUT_RIGHT_MID, 10, 0);

        //添加到焦点组
        ui_transfer_menu_group_set(ui_transfer_book_list->main_group, ui_transfer_menu_container[i], i);
    }

    lv_group_focus_obj(ui_transfer_menu_container[0]);

}

/*************************************************APP 状态机调用函数*********************************************/

void app_ui_transfer_book_main_init(void){
    // LVGL_TASK_LOCK(); 
    ui_transfer_book_main_init();
    // LVGL_TASK_UNLOCK();
}

void app_ui_transfer_book_main_deinit(void){
    // LVGL_TASK_LOCK(); 
    if(ui_transfer_book_list != NULL){
        if(ui_transfer_book_list->last_group != NULL){
            lv_group_set_default(ui_transfer_book_list->last_group);
            lv_indev_set_group(indev_keypad, lv_group_get_default());
            ui_transfer_book_list->last_group = NULL;
        }
        if(ui_transfer_book_list->main_group != NULL){
            lv_group_del(ui_transfer_book_list->main_group);
            ui_transfer_book_list->main_group = NULL;
        }
        if(ui_transfer_book_list->main_page != NULL){
            lv_obj_del(ui_transfer_book_list->main_page);
            ui_transfer_book_list->main_page = NULL;
        }
    }
    ui_transfer_free();//释放内存
    // LVGL_TASK_UNLOCK();
}

