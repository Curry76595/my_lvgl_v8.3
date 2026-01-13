#ifndef UI_SETTING_MAIN_H
#define UI_SETTING_MAIN_H
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui_ebook/ui_setting/ui_setting_about/ui_setting_about.h"
#include "ui_ebook/ui_setting/ui_setting_lockScreen/ui_setting_lockScreen.h"
#include "ui_ebook/ui_setting/ui_setting_storage/ui_setting_storage.h"
#include "ui_ebook/ui_setting/ui_setting_factory/ui_setting_factory_main.h"
#include "ui_ebook/ui_setting/ui_setting_transfers/ui_setting_transfers_main.h"
void app_ui_setting_main_init(void);

/**
 * @description: 定义设置界面内容显示容器（右下角方框，除了状态栏和菜单栏）
 * @return {*}
 */
typedef struct setting_display_ts{
    lv_obj_t *about;         //1.关于
    lv_obj_t *wifi;          //2.wifi
    lv_obj_t *transfers;     //3.传输
    lv_obj_t *update;        //4.更新
    lv_obj_t *storage;       //5.存储
    lv_obj_t *lockScreen;    //6.锁屏
    lv_obj_t *factory;       //7.恢复出厂设置

    lv_group_t *ui_menu_group;   //8.菜单聚焦组
    lv_group_t *ui_lockScreen_group; //9.锁屏聚焦组
    lv_group_t *ui_factory_start_recover_group;//10.出厂开始恢复聚焦组
    lv_group_t *ui_factory_recover_confirm_group;//11.恢复出厂聚焦组

}ui_setting_display_t;

extern ui_setting_display_t *ui_setting_display;

#endif
