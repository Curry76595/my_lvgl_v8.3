#include "ui_com_dialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**********************
 *      HEADERS
 **********************/
#define USE_LVGL_SIMULATOR 1

#ifndef CONFIG_RELEASE_ENABLE
#define LOG_TAG "[UI_COM_DIALOG_Q1]"
#endif
// #include "debug.h"

#if !USE_LVGL_SIMULATOR
#include "sys_update.h"
#include "event/device_event.h"
#endif
// #include "ui_common.h"
// #include "ui_com_dialog.h"

/**********************
 *      MACROS
 **********************/

// LV_IMG_DECLARE(icon_family_record_upload_decor);

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
    E_ID_EXIT = 0,
    E_ID_OK,
    E_ID_CANCEL,
    E_ID_MAIN,
} E_COM_DIALOG_Q1_ID;

/**********************
 *  GOBAL VARIABLES
 **********************/
extern lv_style_t g_ui_style_default;
static E_COM_DIALOG_Q1_EVENT g_dialog_event = E_COM_DIALOG_Q1_EVENT_NONE; // 用于记录对话框事件

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void ui_com_dialog_hide(void);
static void ui_com_dialog_event_cb(lv_event_t *evt);
static void ui_com_dialog_group_del(void);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *ui_main = NULL;           // 主控件
static lv_obj_t *label_dialog_tips = NULL; // 对话框内容
static lv_group_t *last_group = NULL;
static lv_group_t *group_focus = NULL;
static lv_obj_t *btn_exit = NULL;   // 退出按钮
static lv_obj_t *btn_ok = NULL;     // 确认按钮
static lv_obj_t *btn_cancle = NULL; // 确认按钮

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void ui_com_dialog_event_cb(lv_event_t *evt)
{
    lv_event_code_t evt_code = lv_event_get_code(evt);
    lv_obj_t *target_obj = lv_event_get_target(evt);
    E_COM_DIALOG_Q1_ID index = (E_COM_DIALOG_Q1_ID)lv_event_get_user_data(evt);

    printf("<%s> event: %d, index: %d\n", __func__, evt_code, index);

    if (evt_code == LV_EVENT_KEY)
    {
        int key = lv_event_get_key(evt);
        //  printf("> key val : %d \n",key);
        switch (key)
        {
        case LV_KEY_RIGHT:
        {
            printf("%s LV_KEY_RIGHT \n", __func__);

            break;
        }
        case LV_KEY_LEFT:
        {
            printf("%s LV_KEY_LEFT \n", __func__);

            break;
        }

        case LV_KEY_ENTER:
        {
            printf("%s LV_KEY_ENTER \n", __func__);
            // lv_obj_t *obj =  lv_event_get_target(event);
            break;
        }

        case LV_KEY_ESC:
        {
            printf("%s LV_KEY_BACKSPACE \n", __func__);
            ui_com_dialog_group_del();
            ui_com_dialog_hide();
            break;
        }

        default:
            break;
        }
    }

    if (evt_code == LV_EVENT_CLICKED)
    {
        switch (index)
        {
        case E_ID_EXIT:
        {
            printf(">>> E_ID_EXIT \n");
            lv_obj_add_flag(ui_main, LV_OBJ_FLAG_HIDDEN);
            break;
        }
        case E_ID_OK:
        {
            printf(">>> E_ID_OK \n");
            lv_obj_add_flag(ui_main, LV_OBJ_FLAG_HIDDEN);
#if !USE_LVGL_SIMULATOR
            struct device_event eve;
            eve.arg = "com_dialog";
            if (g_dialog_event == E_COM_DIALOG_Q1_EVENT_UPDATE)
            {
                eve.event = DEVICE_EVENT_USER_UPDATE_START; // 特殊处理
            }
            else
            {
                eve.event = DEVICE_EVENT_USER_DIALOG_OK;
            }
            eve.value = g_dialog_event;
            device_event_notify(DEVICE_EVENT_FROM_USER, &eve);
#endif
            break;
        }
        case E_ID_CANCEL:
        {
            printf(">>> E_ID_CANCEL \n");
            lv_obj_add_flag(ui_main, LV_OBJ_FLAG_HIDDEN);
            break;
        }
        default:
            printf(">>> should never happend! \n");
            break;
        }
    }
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void ui_com_dialog_create(void)
{
    printf("<%s>", __func__);

    if (lv_obj_is_valid(ui_main))
    {
        printf("<%s> ui_main already created!", __func__);
        return;
    }

    lv_label_t *label = NULL;
    // 主界面
    // ui_main = lv_obj_create(lv_scr_act());
    ui_main = lv_obj_create(lv_layer_top()); // 顶层图层，避免被其他界面覆盖
    lv_obj_set_size(ui_main, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_add_style(ui_main, &g_ui_style_default, 0);
    lv_obj_clear_flag(ui_main, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(ui_main, LV_ALIGN_TOP_LEFT, 0, 0);
    // lv_obj_add_flag(ui_main, LV_OBJ_FLAG_HIDDEN); // 初始隐藏主界面，之后用 show() hide() 控制显隐
    lv_obj_set_style_bg_opa(ui_main, LV_OPA_0, 0); // 保持背景透明
    lv_obj_add_event_cb(ui_main, ui_com_dialog_event_cb, LV_EVENT_KEY, (void *)E_ID_MAIN);

    // 对话框内容
    label_dialog_tips = lv_label_create(ui_main);
    lv_obj_set_size(label_dialog_tips, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_add_style(label_dialog_tips, &g_ui_style_default, 0);
    lv_obj_set_style_text_align(label_dialog_tips, LV_TEXT_ALIGN_LEFT, 0);
    lv_label_set_long_mode(label_dialog_tips, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(label_dialog_tips, &Chinese_font_16, 0);
    lv_label_set_text(label_dialog_tips, "注意! 注意!\n启动固件升级!\n已完成 66%!");
    lv_obj_align(label_dialog_tips, LV_ALIGN_CENTER, 0, 0);

    // lv_obj_set_style_border_color(label_dialog_tips, lv_color_black(), 0);
    // lv_obj_set_style_border_width(label_dialog_tips, 2, 0);

    // 按键
    // 确认按钮
    btn_ok = lv_obj_create(ui_main);
    lv_obj_clear_flag(btn_ok, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(btn_ok, 40, 32);
    lv_obj_add_style(btn_ok, &g_ui_style_default, 0);
    lv_obj_set_style_radius(btn_ok, 5, 0);
    lv_obj_set_style_bg_color(btn_ok, lv_color_white(), 0);
    lv_obj_set_style_radius(btn_ok, 5, 0);
    lv_obj_add_event_cb(btn_ok, ui_com_dialog_event_cb, LV_EVENT_KEY, (void *)E_ID_OK);
    // 设置边框
    lv_obj_set_style_border_color(btn_ok, lv_color_black(), 0);
    lv_obj_set_style_border_width(btn_ok, 1, 0);
    label = lv_label_create(btn_ok);
    lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label, &Chinese_font_16, 0);
    lv_obj_set_style_text_color(label, lv_color_black(), 0);
    lv_label_set_text(label, "是");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align_to(btn_ok, label_dialog_tips, LV_ALIGN_OUT_BOTTOM_MID, 35, 0);

    // 取消按钮
    btn_cancle = lv_obj_create(ui_main);
    lv_obj_clear_flag(btn_cancle, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(btn_cancle, 40, 32);
    lv_obj_add_style(btn_cancle, &g_ui_style_default, 0);
    lv_obj_set_style_radius(btn_cancle, 5, 0);
    lv_obj_set_style_bg_color(btn_cancle, lv_color_black(), 0);
    lv_obj_set_style_radius(btn_cancle, 5, 0);
    lv_obj_add_event_cb(btn_cancle, ui_com_dialog_event_cb, LV_EVENT_KEY, (void *)E_ID_CANCEL);
    lv_obj_set_style_border_color(btn_cancle, lv_color_black(), 0);
    lv_obj_set_style_border_width(btn_cancle, 1, 0);
    label = lv_label_create(btn_cancle);
    lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label, &Chinese_font_16, 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "否");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align_to(btn_cancle, label_dialog_tips, LV_ALIGN_OUT_BOTTOM_MID, -35, 0);

    lv_obj_align(label_dialog_tips, LV_ALIGN_CENTER, 0, -40);

}

// 隐藏所有对话框
static void ui_com_dialog_hide(void)
{
    printf("<%s>", __func__);

    if (!lv_obj_is_valid(ui_main))
    {
        printf("<%s> ui_main is NULL! creating.. ", __func__);
        ui_com_dialog_create();
        if (!lv_obj_is_valid(ui_main))
        {
            printf("<%s> ui_main is NULL! create failed!", __func__);
            return;
        }
    }
    lv_obj_add_flag(label_dialog_tips, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_ok, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_cancle, LV_OBJ_FLAG_HIDDEN);
    // 隐藏对话框
    lv_obj_add_flag(ui_main, LV_OBJ_FLAG_HIDDEN);
}

// 删除组
static void ui_com_dialog_group_del(void)
{
    printf("<%s>", __func__);

    if (group_focus)
    {
        lv_group_del(group_focus);
        group_focus = NULL;
    }
    if (last_group)
    {
        lv_group_set_default(last_group);
        lv_indev_set_group(indev_keypad, lv_group_get_default());
        last_group = NULL;
    }
}

// ===================================== 公共弹窗功能使能 - start ===================================== //
void ui_com_dialog_show_tips(char *tips_text)
{
    printf("<%s>", __func__);

    if (!lv_obj_is_valid(ui_main))
    {
        printf("<%s> ui_main is NULL! creating.. ", __func__);
        ui_com_dialog_create();
        if (!lv_obj_is_valid(ui_main))
        {
            printf("<%s> ui_main is NULL! create failed!", __func__);
            return;
        }
    }
    last_group = lv_group_get_default();
    group_focus = lv_group_create();
    // 设置提示文本
    if (tips_text && strlen(tips_text) > 0)
    {
        lv_obj_set_size(label_dialog_tips, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_clear_flag(label_dialog_tips, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(label_dialog_tips, tips_text);
        lv_obj_align(label_dialog_tips, LV_ALIGN_CENTER, 0, 0);
        // 设置文本居中对齐
        lv_obj_set_style_text_align(label_dialog_tips, LV_TEXT_ALIGN_CENTER, 0);
    }
    lv_group_add_obj(group_focus, ui_main);
    lv_group_set_default(group_focus);
    lv_indev_set_group(indev_keypad, lv_group_get_default());
    // 显示对话框
    lv_obj_clear_flag(ui_main, LV_OBJ_FLAG_HIDDEN);
}
