#include "ui_test_wifi.h"
#define UI_TRANSFER_BOOK_MAIN_LVGL_SWITCH 1
struct _ui_factory_test_wifi_ctrl
{
    lv_obj_t *cont_main;
    lv_group_t *group_focus;
    lv_group_t *last_group;
    lv_obj_t *wifi_status;
    lv_obj_t *wifi_ssid;
    lv_obj_t *wifi_pwd;
    lv_obj_t *net_time;
    lv_obj_t *sd8563b_rtc;
    lv_obj_t *wifi_rssi;
    int finish_status;
    int return_flag;
};

static struct _ui_factory_test_wifi_ctrl ui_ctl;

static lv_style_t menu_label_style;
static lv_style_t bg_style;
static lv_style_t list_lab_style;


// ====================================== 样式初始化 ====================================== //
static void ui_bg_style_init(void)
{
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_color_white());
    lv_style_set_pad_all(&bg_style, 0);
    lv_style_set_border_width(&bg_style, 0);
    lv_style_set_radius(&bg_style, 0);
}

// 菜单Label样式
static void ui_menu_label_style_init(void)
{
    lv_style_init(&menu_label_style);
    lv_style_set_text_font(&menu_label_style, &Chinese_font_16);
    lv_style_set_text_color(&menu_label_style, lv_color_black());
    lv_style_set_text_align(&menu_label_style, LV_ALIGN_CENTER);
}

static void ui_list_label_style_init(void)
{
    lv_style_init(&list_lab_style);
    lv_style_set_text_font(&list_lab_style, &Chinese_font_16);
    lv_style_set_text_color(&list_lab_style, lv_color_black());
    lv_style_set_text_line_space(&list_lab_style, 0);
}

static void ui_factory_test_wifi_event_cb(lv_event_t *event)
{
    int evt_code = lv_event_get_code(event);
    lv_obj_t *target_obj = lv_event_get_target(event);
    static int draw_cnt = 0;

    if (evt_code == LV_EVENT_KEY)
    {
        int key = lv_event_get_key(event);
        //  printf("> key val : %d \n",key);
        switch (key)
        {
            case LV_KEY_RIGHT:
            {
                printf("%s LV_KEY_RIGHT \n",__func__);

                break;
            }
            case LV_KEY_LEFT:
            {
                printf("%s LV_KEY_LEFT \n",__func__);
                break;
            }
            case LV_KEY_ENTER:
            {

                break;
            }
            case LV_KEY_ESC:
            {
                printf("%s LV_KEY_ESC \n",__func__);
                // app_Factory_startActionState(APP_FACTORY_ACTION_EXIT_TO_MANUAL_TEST, 0, NULL);
                ui_factory_test_wifi_deinit();
                break;
            }

            default:
                break;
        }
    }
}
void ui_factory_test_wifi_init(void){
#if UI_TRANSFER_BOOK_MAIN_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif    
    // lv样式初始化
    ui_bg_style_init();
    ui_menu_label_style_init();
    ui_list_label_style_init();

    memset(&ui_ctl, 0, sizeof(struct _ui_factory_test_wifi_ctrl));
    ui_ctl.last_group = lv_group_get_default();
    ui_ctl.group_focus = lv_group_create();
    lv_group_set_default(ui_ctl.group_focus);
    lv_indev_set_group(indev_keypad, lv_group_get_default());

    // 主背景
    ui_ctl.cont_main = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_ctl.cont_main, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_add_style(ui_ctl.cont_main, &bg_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_ctl.cont_main, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(ui_ctl.cont_main, ui_factory_test_wifi_event_cb, LV_EVENT_KEY, NULL);

     // 设置焦点组
    lv_group_add_obj(lv_group_get_default(), ui_ctl.cont_main);

     // 顶部
    lv_obj_t *title = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(title, &menu_label_style, 0);
    lv_label_set_text(title, "WIFI配网测试");
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 8);

    // 横线
    lv_obj_t *top_line = lv_obj_create(ui_ctl.cont_main);
    lv_obj_set_size(top_line, lv_disp_get_hor_res(NULL), 1);
    lv_obj_add_style(top_line, &bg_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(top_line, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(top_line, LV_OPA_100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(top_line, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(top_line, LV_ALIGN_TOP_LEFT, 0, 27);

    ui_ctl.wifi_status = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.wifi_status, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.wifi_status, "WIFI状态: 未连接");
    lv_obj_align_to(ui_ctl.wifi_status, top_line, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);

    ui_ctl.wifi_ssid = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.wifi_ssid, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.wifi_ssid, "WIFI名称: NULL");
    lv_obj_align_to(ui_ctl.wifi_ssid, ui_ctl.wifi_status, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    ui_ctl.wifi_pwd = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.wifi_pwd, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.wifi_pwd, "WIFI密码: NULL");
    lv_obj_align_to(ui_ctl.wifi_pwd, ui_ctl.wifi_ssid, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    ui_ctl.wifi_rssi = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.wifi_rssi, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.wifi_rssi, "WIFI_rssi: x dbm");
    lv_obj_align_to(ui_ctl.wifi_rssi,  ui_ctl.wifi_pwd, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);


    ui_ctl.net_time = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.net_time, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.net_time, "RTC时间: XXXX-XX-XX  XX:XX");
    lv_obj_align_to(ui_ctl.net_time,  ui_ctl.wifi_rssi, LV_ALIGN_OUT_BOTTOM_MID, 0, 60);


    ui_ctl.sd8563b_rtc = lv_label_create(ui_ctl.cont_main);
    lv_obj_add_style(ui_ctl.sd8563b_rtc, &list_lab_style, 0);
    lv_label_set_text(ui_ctl.sd8563b_rtc, "sd8563b_RTC:离线");
    lv_obj_align_to(ui_ctl.sd8563b_rtc, ui_ctl.net_time, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    
}


void ui_factory_test_wifi_deinit(void){
    // 删除ui
    if (ui_ctl.cont_main)
    {
        lv_obj_del(ui_ctl.cont_main);
        ui_ctl.cont_main = NULL;
    }
    if (ui_ctl.group_focus)
    {
        lv_group_del(ui_ctl.group_focus);
        ui_ctl.group_focus = NULL;
    }
    if (ui_ctl.last_group)
    {
        lv_group_set_default(ui_ctl.last_group);
        lv_indev_set_group(indev_keypad, lv_group_get_default());
        ui_ctl.last_group = NULL;
    }

    lv_style_reset(&bg_style);
    lv_style_reset(&menu_label_style);
    lv_style_reset(&list_lab_style);
}