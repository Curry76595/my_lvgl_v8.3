#ifndef UI_IMAGE_MAIN_H
#define UI_IMAGE_MAIN_H

#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app_ui_image_main_init(void);

void app_ui_image_main_deinit(void);

typedef struct ui_image_display_ts{
    lv_obj_t *ui_image_list;    //图片列表
    lv_obj_t *ui_image_display; //图片显示区域
    lv_group_t *ui_image_list_group;
}ui_image_display_t;

extern ui_image_display_t *ui_image_display_list;
#endif
