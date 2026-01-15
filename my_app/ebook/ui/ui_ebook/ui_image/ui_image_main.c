#include "ui_image_main.h"
#include "ui_image_list.h"
#include "ui_image_display.h"
#include "ui_image_delete.h"
#define UI_IMAGE_MAIN_LVGL_SWITCH 1    // 0: 关闭LVGL的键盘驱动 1: 开启LVGL的键盘驱动

/******************************************************声明变量****************************************************/
ui_image_display_t *ui_image_display_list;

/***************************************************内存申请释放************************************************/
//申请内存
static void ui_image_malloc(void){
    if(ui_image_display_list == NULL){
        ui_image_display_list = (ui_image_display_t *)malloc(sizeof(ui_image_display_t));
        if(ui_image_display_list == NULL) return;
        memset(ui_image_display_list, 0, sizeof(ui_image_display_t));
    }

}

//释放内存
static void ui_image_free(void){
    if(ui_image_display_list != NULL){
        free(ui_image_display_list);
        ui_image_display_list = NULL;
    }
}

/********************************************外部接口函数******************************************/
void ui_image_select_interface(int select_index){
    lv_obj_add_flag(ui_image_display_list->ui_image_list, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_image_display_list->ui_image_display, LV_OBJ_FLAG_HIDDEN);
    
    switch (select_index){
        case 0:
            lv_obj_clear_flag(ui_image_display_list->ui_image_list, LV_OBJ_FLAG_HIDDEN);
            lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_list_group);
            lv_group_focus_obj(lv_obj_get_child(ui_image_display_list->ui_image_list, 2));
            break;
        case 1:
            lv_obj_clear_flag(ui_image_display_list->ui_image_display, LV_OBJ_FLAG_HIDDEN);   
            lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_display_group);
            lv_group_focus_obj(lv_obj_get_child(ui_image_display_list->ui_image_display, 0));
            break;
    }
}


/****************************************************初始化函数*****************************************************/
static void ui_image_main_init(void){
#if UI_IMAGE_MAIN_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif
   
    //申请内存
    ui_image_malloc();

    //创建图库显示列表
    ui_image_display_list->ui_image_list = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_image_display_list->ui_image_list, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_clear_flag(ui_image_display_list->ui_image_list, LV_OBJ_FLAG_SCROLLABLE);   
    lv_obj_add_flag(ui_image_display_list->ui_image_list, LV_OBJ_FLAG_HIDDEN);
    //创建图库显示界面
    ui_image_display_list->ui_image_display = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_image_display_list->ui_image_display, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_clear_flag(ui_image_display_list->ui_image_display, LV_OBJ_FLAG_SCROLLABLE);  
    lv_obj_add_flag(ui_image_display_list->ui_image_display, LV_OBJ_FLAG_HIDDEN);

    ui_image_list_init();//初始化图库列表

    ui_image_display_init();//初始化图库显示界面

    ui_image_delete_init();//初始化图库删除界面
    
    ui_image_select_interface(0);//选择图库列表界面
}


static void  ui_image_main_deinit(void){
    printf("ui_image_main_deinit");
    if(ui_image_display_list != NULL){
        if(ui_image_display_list->ui_image_list != NULL){
            lv_obj_del(ui_image_display_list->ui_image_list);
            ui_image_display_list->ui_image_list = NULL;
        }

        if(ui_image_display_list->ui_image_display != NULL){
            lv_obj_del(ui_image_display_list->ui_image_display);
            ui_image_display_list->ui_image_display = NULL;
        }

        if(ui_image_display_list->ui_image_display_group != NULL){
            lv_group_del(ui_image_display_list->ui_image_display_group);
            ui_image_display_list->ui_image_display_group = NULL;
        }

        if(ui_image_display_list->ui_image_list_group != NULL){
            lv_group_del(ui_image_display_list->ui_image_list_group);
            ui_image_display_list->ui_image_list_group = NULL;
        }

        if(ui_image_display_list->ui_image_delete_group != NULL){
            lv_group_del(ui_image_display_list->ui_image_delete_group);
            ui_image_display_list->ui_image_delete_group = NULL;
        }
    }
    ui_image_free();//释放内存
    printf("ui_image_main_deinit end");
}

/*************************************************APP 状态机调用函数*********************************************/
void app_ui_image_main_init(void){
    // LVGL_TASK_LOCK();
    ui_image_main_init();
    // LVGL_TASK_UNLOCK();
}

void app_ui_image_main_deinit(void){
    // LVGL_TASK_LOCK();
    ui_image_main_deinit();
    // LVGL_TASK_UNLOCK();
}

