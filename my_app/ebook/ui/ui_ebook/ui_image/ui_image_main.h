#ifndef UI_IMAGE_MAIN_H
#define UI_IMAGE_MAIN_H

#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ui_image_display_ts{
    lv_obj_t *ui_image_list;    //图片列表
    lv_obj_t *ui_image_display; //图片显示区域
    lv_group_t *ui_image_list_group; //图片列表焦点组
    lv_group_t *ui_image_display_group; //图片显示焦点组
    lv_group_t *ui_image_delete_group; //图片删除焦点组
}ui_image_display_t;

extern ui_image_display_t *ui_image_display_list;

void app_ui_image_main_init(void);
void app_ui_image_main_deinit(void);
void ui_image_select_interface(int select_index);
#endif
