#include "ui_setting_main.h"
#define UI_MAIN_LVGL_SWITCH 1    // 0: 关闭LVGL的键盘驱动 1: 开启LVGL的键盘驱动

/***********************************************************申明变量*****************************************************/
//创建菜单标题标签
lv_obj_t *ui_title;
#define UI_SETTING_MENU_NUM 5
//创建菜单列表
char * ui_menuName[UI_SETTING_MENU_NUM] = {"锁屏","存储","出厂","关于","更新"};
//创建标题文本内容
char *ui_titleName[UI_SETTING_MENU_NUM] = {
    "设置-锁屏关机", 
    "设置-存储空间",
     "设置-恢复出厂",
     "设置-关于",
     "设置-固件更新",
};
char *ui_Eng_titleName[UI_SETTING_MENU_NUM] = {
    "Screen lock & Power off",
    "Storage",
    "Factory Reset",
    "About",
};
static const lv_img_dsc_t *English_menu_option[UI_SETTING_MENU_NUM][2] = {
    {&de_lockscreen,&lockscreen},
    {&de_storage,&storage},
    {&de_factory,&factory},
    {&de_about,&about},
};

ui_setting_display_t *ui_setting_display;
lv_obj_t *ui_container;//创建一个霸屏容器
/***************************************************内存申请释放************************************************/
//申请内存
static void ui_setting_malloc(void){
    if(ui_setting_display == NULL){
        ui_setting_display = (ui_setting_display_t *)malloc(sizeof(ui_setting_display_t));
        if(ui_setting_display == NULL) return;
        memset(ui_setting_display, 0, sizeof(ui_setting_display_t));
    }

}

//释放内存
static void ui_setting_free(void){
    if(ui_setting_display != NULL){
        free(ui_setting_display);
        ui_setting_display = NULL;
    }
}

/**************************************************设置模块ui设计细节************************************************/
/**
 * @description: 设置菜单内容选择
 * @return {*}
 */
static void ui_setting_menu_content_select(int menu_index){
        lv_obj_add_flag(ui_setting_display->about, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_setting_display->storage, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_setting_display->lockScreen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_setting_display->factory, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_setting_display->update, LV_OBJ_FLAG_HIDDEN);
        switch(menu_index){
            case 0:
                lv_obj_clear_flag(ui_setting_display->lockScreen, LV_OBJ_FLAG_HIDDEN);
                break;
            case 1:
                lv_obj_clear_flag(ui_setting_display->storage, LV_OBJ_FLAG_HIDDEN);
                break;
            case 2:
                lv_obj_clear_flag(ui_setting_display->factory, LV_OBJ_FLAG_HIDDEN);
                break;
            case 3:
                lv_obj_clear_flag(ui_setting_display->about, LV_OBJ_FLAG_HIDDEN);
                break;  
            case 4:
                lv_obj_clear_flag(ui_setting_display->update, LV_OBJ_FLAG_HIDDEN);
                break;
            default:
                break;    
        }
}

/**
 * @description: 设置英文菜单的图片显示
 * @param {lv_obj_t} *img_container
 * @param {int} index
 * @param {int} state  0-非聚焦； 1-聚焦
 * @return {*}
 */
static void set_img_to_content(lv_obj_t *img_container,int index,int state){
    lv_obj_t *img = lv_img_create(img_container);
    lv_obj_center(img);
    lv_img_set_src(img, English_menu_option[index][state]);
}

/**
 * @description: 菜单选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_setting_set_menu_focus(lv_obj_t *obj, bool focus, int index)
{

    if(English_version){
        if(focus){
            set_img_to_content(obj,index,1);
        }else{
            set_img_to_content(obj,index,0);
        }
    }
    else{
        lv_obj_t * child_obj = lv_obj_get_child(obj,0);
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
    
}

/**
 * @description: 创建圆角矩形容器
 * @return {*}
 */
static lv_obj_t *create_rounded_rectangle(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,lv_coord_t radius, lv_color_t bg_color,
    lv_color_t border_color,lv_coord_t border_width, bool Is_Btn) {
    lv_obj_t *rect = NULL;
    if (Is_Btn)
        rect = lv_btn_create(parent);
    else
        rect = lv_obj_create(parent);

    lv_obj_set_size(rect, w, h);
    lv_obj_set_style_radius(rect, radius, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rect, bg_color, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(rect, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
    lv_obj_add_flag(rect, LV_OBJ_FLAG_CLICKABLE);
    // 设置边框
    lv_obj_set_style_border_color(rect, border_color, LV_PART_MAIN);
    lv_obj_set_style_border_width(rect, border_width, LV_PART_MAIN);
    lv_obj_set_style_border_opa(rect, LV_OPA_COVER, LV_PART_MAIN);
    if (Is_Btn)
        lv_obj_set_style_bg_color(rect, lv_color_hex(0xCCCCCC), LV_PART_MAIN | LV_STATE_PRESSED);
    return rect;
}

/**
 * @description: 创建容器里的文本
 * @return {*}
 */
static lv_obj_t *Rounded_create_content(lv_obj_t *img_rounded, char *text, int label_x,int label_y, lv_coord_t align_x,lv_coord_t align_y) {
    lv_obj_t *label_text = lv_label_create(img_rounded);
    lv_obj_set_size(label_text, label_x, label_y);
    lv_obj_set_style_border_opa(label_text, 0, LV_PART_MAIN);
    lv_obj_set_style_text_font(label_text, &Chinese_font_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_text, lv_color_black(), LV_PART_MAIN);
    lv_label_set_text(label_text, text);
    lv_label_set_long_mode(label_text, LV_LABEL_LONG_DOT);
    lv_obj_align(label_text, LV_ALIGN_TOP_MID, align_x, align_y);
    return label_text;
}




/*************************************************设置模块回调函数**********************************************/

/**
 * @description: 菜单聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_focus_event_cb(lv_event_t *e){
    lv_obj_t *menu_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_setting_set_menu_focus(menu_obj,true,user_data);
        if(English_version){
            lv_label_set_text_fmt(ui_title, ui_Eng_titleName[user_data],0);
            lv_obj_set_style_text_letter_space(ui_title, 1, LV_PART_MAIN);
        }else{
            lv_label_set_text_fmt(ui_title, ui_titleName[user_data],0);
        }
        switch(user_data){
            case 0:
            ui_set_lcok_screen_default_option();//先初始化好默认选择项
            ui_setting_menu_content_select(0);
            break;
            case 1:
            ui_setting_menu_content_select(1);
            break;
            case 2:
            ui_setting_menu_content_select(2);
            break;
            case 3:
            ui_setting_menu_content_select(3);
            break;
            case 4:
            ui_setting_menu_content_select(4);
            break;
        }
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_setting_set_menu_focus(menu_obj, false,user_data);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_menu_key_event_cb(lv_event_t *e){
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
                switch (user_data){
                    case 0:
                        lv_indev_set_group(indev_keypad,ui_setting_display->ui_lockScreen_group);
                        if(!get_lock_screen_exit_flag())ui_set_lock_screen_first_focus();
                        break;
                    case 1:
                        break;
                    case 2:
                        lv_indev_set_group(indev_keypad,ui_setting_display->ui_factory_start_recover_group);
                        lv_group_focus_obj(lv_obj_get_child(lv_obj_get_child(ui_setting_display->factory, 0),0));
                        break;            
                    default:
                        break;    
                }
                break;
            case LV_KEY_ESC:
                // set_lock_screen_exit_flag();
                // appSetting_startActionState(APP_SETTING_ACTION_MENU, UI_SETTING_MENU_REFRESH_EXIT, NULL);
                break;
            default:
                break;
        }

    }
}
/**************************************************封装回调函数***********************************************/
/**
 * @description: 设置组函数和回调函数
 * @param {lv_obj_t} *obj
 * @return {*}
 */
static void ui_setting_menu_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_setting_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_setting_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_setting_menu_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}

/*************************************************设置界面总初始化*********************************************/

static void ui_setting_main_init(void){
#if UI_MAIN_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif
    //1.申请菜单容器内存
    ui_setting_malloc();
    //2.创建背景容器
    ui_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_container, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_clear_flag(ui_container, LV_OBJ_FLAG_SCROLLABLE);   
    //3.创建标题-退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_container);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_container, LV_ALIGN_TOP_LEFT, -6, -8);
    lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_width(ui_exit, 0, 0);
    lv_obj_set_style_radius(ui_exit, 0, 0);
    lv_obj_set_style_pad_all(ui_exit, 0, 0);
    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align_to(ui_exit_img, ui_exit, LV_ALIGN_TOP_LEFT, 0, 0);
    //4.创建标题-显示标签
    ui_title = lv_label_create(ui_container);
    if(English_version){
        lv_label_set_text(ui_title, ui_Eng_titleName[0]);
        lv_obj_set_style_text_letter_space(ui_title, 1, LV_PART_MAIN);
    }
    else{
        lv_label_set_text(ui_title, ui_titleName[0]);
        lv_obj_set_style_text_letter_space(ui_title,2, LV_PART_MAIN);
    }
    
    lv_obj_set_style_text_font(ui_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_title, LV_ALIGN_TOP_LEFT, 10, -8);
    //5.创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_container);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);
    //6.创建菜单容器
    lv_obj_t *ui_menu_container = lv_obj_create(ui_container);
    lv_obj_set_size(ui_menu_container, 63, 340);
    lv_obj_set_pos(ui_menu_container,-15,21);
    //6.创建菜单列表
    lv_obj_t *ui_menu_list[UI_SETTING_MENU_NUM];
    lv_obj_t *ui_menu_list_label[UI_SETTING_MENU_NUM];
    //7.1创建菜单聚焦组
    ui_setting_display->ui_menu_group = lv_group_create();
    lv_indev_set_group(indev_keypad,ui_setting_display->ui_menu_group);
    for(int i=0;i<UI_SETTING_MENU_NUM;i++){
        if(English_version){
           ui_menu_list[i] = create_rounded_rectangle(ui_menu_container, 37, 33, 10, lv_color_white(), lv_color_white(), 0, false);
           set_img_to_content(ui_menu_list[i],i,0);
        }else{
            ui_menu_list[i] = create_rounded_rectangle(ui_menu_container,53,35,10,lv_color_white(),lv_color_white(),0,false);
            ui_menu_list_label[i] = Rounded_create_content(ui_menu_list[i], ui_menuName[i], 32, 18, 0, -6);
        }
        lv_obj_align(ui_menu_list[i], LV_ALIGN_TOP_MID,0, 25+i*48);
        //设置组的聚焦和回调
        ui_setting_menu_group_set(ui_setting_display->ui_menu_group,ui_menu_list[i],i);
    }
    //7.2初始化聚焦第一个【锁屏】
    ui_setting_set_menu_focus(ui_menu_list[0],true,0);
    //8.创建菜单分割线
    lv_obj_t *ui_menu_line = lv_line_create(ui_container);
    static lv_point_t menu_line_points[] = {{47,21},{47,360}};
    lv_line_set_points(ui_menu_line,menu_line_points,2);
    lv_obj_set_style_line_width(ui_menu_line, 1, LV_PART_MAIN);

    /***********************************************9创建菜单内容界面**************************************************/
    //9.1关于界面
    ui_setting_display->about = lv_obj_create(ui_container);
    lv_obj_set_size(ui_setting_display->about, 190, 323);
    lv_obj_align(ui_setting_display->about,LV_ALIGN_BOTTOM_RIGHT, 28, 15);
    //9.2存储界面
    ui_setting_display->storage = lv_obj_create(ui_container);
    lv_obj_set_size(ui_setting_display->storage, 190, 323);
    lv_obj_align(ui_setting_display->storage,LV_ALIGN_BOTTOM_RIGHT, 28, 15);
    //9.3锁屏界面
    ui_setting_display->lockScreen = lv_obj_create(ui_container);
    lv_obj_set_size(ui_setting_display->lockScreen, 190, 323);
    lv_obj_align(ui_setting_display->lockScreen,LV_ALIGN_BOTTOM_RIGHT, 28, 15);
    //9.4出厂界面
    ui_setting_display->factory = lv_obj_create(ui_container);
    lv_obj_set_size(ui_setting_display->factory, 190, 323);
    lv_obj_align(ui_setting_display->factory,LV_ALIGN_BOTTOM_RIGHT, 28, 15);
    //9.5更新界面
    ui_setting_display->update = lv_obj_create(ui_container);
    lv_obj_set_size(ui_setting_display->update, 190, 323);
    lv_obj_align(ui_setting_display->update,LV_ALIGN_BOTTOM_RIGHT, 28, 15);
   
    /***************************************************end********************************************************/
    
    /************************************************初始化菜单内容**********************************************/
    ui_setting_about_init();//关于
    ui_setting_storage_init();//存储
    ui_setting_lockScreen_init();//锁屏
    ui_setting_factory_main_init();//出厂
    /***************************************************end****************************************************/
    
    //默认展示第一个菜单【锁屏】
     ui_setting_menu_content_select(0);
}

static void ui_setting_main_deinit(void){
    printf("ui_setting_main_deinit");
    if(ui_setting_display != NULL){
        if(ui_setting_display->ui_menu_group != NULL){
            lv_group_del(ui_setting_display->ui_menu_group);
            ui_setting_display->ui_menu_group = NULL;
        }
        if(ui_setting_display->ui_lockScreen_group != NULL){
            lv_group_del(ui_setting_display->ui_lockScreen_group);
            ui_setting_display->ui_lockScreen_group = NULL;
        }
        if(ui_setting_display->ui_factory_start_recover_group != NULL){
            lv_group_del(ui_setting_display->ui_factory_start_recover_group);
            ui_setting_display->ui_factory_start_recover_group = NULL;
        }
        if(ui_setting_display->ui_factory_recover_confirm_group != NULL){
            lv_group_del(ui_setting_display->ui_factory_recover_confirm_group);
            ui_setting_display->ui_factory_recover_confirm_group = NULL;
        }
    }
    if(ui_container != NULL){
        lv_obj_del(ui_container);
        ui_container = NULL;
    }
    ui_setting_free();//释放内存
    printf("ui_setting_main_deinit end");
}

/*************************************************APP 状态机调用函数*********************************************/
void app_ui_setting_main_init(void){
    // LVGL_TASK_LOCK();
    ui_setting_main_init();
    // LVGL_TASK_UNLOCK();
}

void app_ui_setting_main_deinit(void){
    // LVGL_TASK_LOCK();
    ui_setting_main_deinit();
    // LVGL_TASK_UNLOCK();
}

