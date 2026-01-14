#include "ui_image_display.h"

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
                
                break;

            case LV_KEY_RIGHT:
                 
                break;
            case LV_KEY_ENTER:
                
                break;
            case LV_KEY_ESC:
                
                break;
            default:
                break;
        }

    }
}


void ui_image_display_init(void){
    lv_obj_t *ui_img = lv_img_create(ui_image_display_list->ui_image_display);
    lv_obj_set_size(ui_img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_img_set_src(ui_img, "D:/finish.jpg");
    lv_obj_center(ui_img);
    lv_obj_add_event_cb(ui_img, ui_image_display_key_event_cb, LV_EVENT_KEY, NULL);
}
    
    

