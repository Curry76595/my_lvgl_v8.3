#ifndef UI_TRANSFER_BOOK_MAIN_H
#define UI_TRANSFER_BOOK_MAIN_H

#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui_ebook/ui_transfer_book/ui_image/ui_image_main.h"
#include "ui_ebook/ui_transfer_book/ui_operation_notice/ui_operation_notice.h"
typedef struct ui_transfer_book_ts{
    lv_obj_t *main_page;//主页面
    lv_obj_t *last_group;//上一次焦点组
    lv_group_t *main_group;//主页面焦点组
}ui_transfer_book_t;

void app_ui_transfer_book_main_init(void);

#endif 