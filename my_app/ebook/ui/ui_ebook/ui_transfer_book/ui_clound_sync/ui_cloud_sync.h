#ifndef UI_CLOUD_SYNC_H
#define UI_CLOUD_SYNC_H


#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdlib.h>
#include <string.h>

typedef struct ui_cloud_sync_ts{
    lv_obj_t *ui_cloud_container;//霸屏容器
    lv_group_t *last_group;//上一个焦点组
    lv_group_t *cloud_group;//云同步焦点组
}ui_cloud_sync_t;

void ui_cloud_sync_init(void);
void ui_cloud_sync_deinit(void);
#endif
