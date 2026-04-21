#ifndef UI_CLOUND_SYNC_H
#define UI_CLOUND_SYNC_H


#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ui_clound_sync_ts{
    lv_obj_t *ui_clound_container;//霸屏容器
    lv_group_t *last_group;//上一个焦点组
    lv_group_t *clound_group;//云同步焦点组
}ui_clound_sync_t;

void ui_clound_sync_init(void);
void ui_clound_sync_deinit(void);
#endif
