#include "ui_image_display.h"


/*********************************************申明变量*********************************************/
lv_obj_t *ui_img;

/*********************************************按键事件回调函数*********************************************/
/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_image_display_key_event_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_KEY){
        uint32_t KEY = lv_event_get_key(e);
        switch(KEY){
            case LV_KEY_LEFT:
                lv_img_set_src(ui_img, "D:/speak.jpg");
                break;

            case LV_KEY_RIGHT:
                lv_img_set_src(ui_img, "D:/finish.jpg");
                break;
            case LV_KEY_ENTER:
                printf("CLICK enter_key pressed\n");
                //显示删除弹框并改变输入焦点组
                lv_obj_clear_flag(lv_obj_get_child(ui_image_display_list->ui_image_display, 1), LV_OBJ_FLAG_HIDDEN);
                lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_delete_group);
                //显示设置壁纸弹框并改变输入焦点组
                // lv_obj_clear_flag(lv_obj_get_child(ui_image_display_list->ui_image_display, 2), LV_OBJ_FLAG_HIDDEN);
                // lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_set_wallpaper_group);
                break;
            case LV_KEY_ESC:
                printf("ESC key pressed\n");
                ui_image_select_interface(0);
                break;
            default:
                break;
        }

    }
    else if(code == LV_EVENT_LONG_PRESSED){
       
        printf("LONG_PRESSED enter_key pressed\n");
        
    }
    
}

/**********************************************初始化函数***********************************************/
void ui_image_display_init(void){
    //创建图片显示焦点组
    ui_image_display_list->ui_image_display_group = lv_group_create();
    lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_display_group);
    //创建图片显示界面
    ui_img = lv_img_create(ui_image_display_list->ui_image_display);
    lv_obj_clear_flag(ui_img, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(ui_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(ui_img, "D:/finish.jpg");
    lv_obj_center(ui_img);
    //设置图片显示界面焦点组和回调函数
    lv_group_add_obj(ui_image_display_list->ui_image_display_group, ui_img);
    lv_group_focus_obj(ui_img);
    lv_obj_add_event_cb(ui_img, ui_image_display_key_event_cb, LV_EVENT_KEY, NULL);
}
    
    

