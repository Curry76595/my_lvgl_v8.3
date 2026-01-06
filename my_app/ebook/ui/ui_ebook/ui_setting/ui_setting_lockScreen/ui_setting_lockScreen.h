#ifndef UI_SETTING_LOCKSCREEN_H
#define UI_SETTING_LOCKSCREEN_H
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include "ui_ebook/ui_setting/ui_setting_main/ui_setting_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ui_setting_lockScreen_init(void);
void ui_set_lock_screen_first_focus(void);
void ui_set_lcok_screen_default_option(void);
int get_lock_screen_exit_flag(void);
#endif
