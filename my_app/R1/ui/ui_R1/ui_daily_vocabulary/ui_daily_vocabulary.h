#ifndef UI_DAILY_VOCABULARY_H
#define UI_DAILY_VOCABULARY_H
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"

typedef struct{
    lv_obj_t *main;
    lv_obj_t *top_bar;
    lv_obj_t *content;

    lv_obj_t *title_label;
    lv_obj_t *name_label;
    lv_obj_t *phonetic_label;
    lv_obj_t *meaning_title_label;
    lv_obj_t *meaning_label;
    lv_obj_t *example_title_label;
    lv_obj_t *example_label;
}ui_daily_vocabulary_t;

void ui_daily_vocabulary_init(void);
void ui_daily_vocabulary_deinit(void);
#endif 
