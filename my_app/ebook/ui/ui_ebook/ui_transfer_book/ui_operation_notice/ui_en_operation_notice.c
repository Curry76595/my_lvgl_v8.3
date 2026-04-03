#include "ui_en_operation_notice.h"
#include <string.h>


/*******************************************申明变量*******************************************/
lv_obj_t *ui_en_operation_notice_container;
lv_group_t *last_en_group;
lv_group_t *ui_en_operation_notice_group;

static void ui_en_operation_notice_key_event_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_KEY){
        uint32_t key = lv_event_get_key(e);
        if(key == LV_KEY_ESC){
            printf("<%s> LV_KEY_ESC\n",__func__);
            ui_en_operation_notice_deinit();
        }
    }
}


void ui_en_operation_notice_init(void){

    last_en_group = lv_group_get_default();
    //新建焦点组
    ui_en_operation_notice_group = lv_group_create();
    lv_group_set_default(ui_en_operation_notice_group);
    lv_indev_set_group(indev_keypad, lv_group_get_default());
    //创建一个霸屏容器
    ui_en_operation_notice_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_en_operation_notice_container, 240, 360);
    lv_obj_clear_flag(ui_en_operation_notice_container, LV_OBJ_FLAG_SCROLLABLE);

    //创建标题-退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_en_operation_notice_container);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_en_operation_notice_container, LV_ALIGN_TOP_LEFT, -6, -8);
    lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_width(ui_exit, 0, 0);
    lv_obj_set_style_radius(ui_exit, 0, 0);
    lv_obj_set_style_pad_all(ui_exit, 0, 0);
    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align_to(ui_exit_img, ui_exit, LV_ALIGN_TOP_LEFT, 0, 0);

    //创建标题-显示标签
    lv_obj_t *ui_transfer_title = lv_label_create(ui_en_operation_notice_container);
    lv_label_set_text(ui_transfer_title, "Transfer Instructions");
    lv_obj_set_style_text_letter_space(ui_transfer_title,1, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_transfer_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_transfer_title, LV_ALIGN_TOP_LEFT, 10, -8);

    //创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_en_operation_notice_container);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);
    
    //创建内容显示容器
    lv_obj_t *content_display_container = lv_obj_create(ui_en_operation_notice_container);
    lv_obj_set_size(content_display_container, 235, 320);
    lv_obj_add_flag(content_display_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(content_display_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(content_display_container, LV_ALIGN_TOP_MID, 0, 23);
    lv_obj_set_style_border_color(content_display_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_display_container, 1, LV_PART_MAIN);
    lv_group_add_obj(ui_en_operation_notice_group, content_display_container);
    lv_obj_add_event_cb(content_display_container,ui_en_operation_notice_key_event_cb,LV_EVENT_KEY,NULL);

    lv_obj_t *content_label_container_1 = lv_obj_create(content_display_container);
    lv_obj_set_size(content_label_container_1,140 , 80);
    lv_obj_clear_flag(content_label_container_1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(content_label_container_1, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_label_container_1, 1, LV_PART_MAIN);
    lv_obj_align(content_label_container_1, LV_ALIGN_TOP_LEFT, -9, 0);    

    lv_obj_t *content_label_1 = lv_label_create(content_label_container_1);
    lv_label_set_text(content_label_1, "1.Scan QR code\n to download and\n install the app.");
    lv_obj_set_style_text_letter_space(content_label_1,0, LV_PART_MAIN);
    lv_obj_set_style_text_font(content_label_1,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(content_label_1, LV_ALIGN_TOP_LEFT, -9, -8);

    //创建图片显示容器
    lv_obj_t *content_img_container = lv_obj_create(content_display_container);
    lv_obj_set_size(content_img_container, 85, 105);
    lv_obj_clear_flag(content_img_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(content_img_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_img_container, 1, LV_PART_MAIN);
    lv_obj_align_to(content_img_container, content_label_container_1, LV_ALIGN_OUT_RIGHT_MID, 0, -5);

    // lv_obj_t *img = lv_img_create(content_img_container);
    // lv_obj_center(img);
    // lv_img_set_src(img, &QRCode);

    char *text = "vtd30:GG:47:EE:22:53:B7";
    lv_obj_t *qr = lv_qrcode_create(content_img_container, 80, lv_color_black(), lv_color_white());
    lv_qrcode_update(qr, text, strlen(text));
    lv_obj_center(qr);


    lv_obj_t *content_label_container_2 = lv_obj_create(content_display_container);
    lv_obj_set_size(content_label_container_2, 230, 220);
    lv_obj_clear_flag(content_label_container_2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(content_label_container_2, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_label_container_2, 1, LV_PART_MAIN);
    lv_obj_align_to(content_label_container_2, content_label_container_1, LV_ALIGN_OUT_BOTTOM_MID,43, 0);


    lv_obj_t *content_label_2 = lv_label_create(content_label_container_2);
    lv_label_set_text(content_label_2, "2.Open the app once installed.");
    lv_obj_set_style_text_font(content_label_2,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(content_label_2,-1, LV_PART_MAIN);
    lv_obj_align(content_label_2, LV_ALIGN_TOP_LEFT, -6, 0);

    lv_obj_t *content_label_3 = lv_label_create(content_label_container_2);
    lv_label_set_text(content_label_3, "3.Log in,connect to “Pocket-S1”\n via BLE in device list.");
    lv_obj_set_style_text_font(content_label_3,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(content_label_3,-1, LV_PART_MAIN);
    lv_obj_align_to(content_label_3, content_label_2,LV_ALIGN_OUT_BOTTOM_MID, 3, 25);



    lv_obj_t *content_label_4 = lv_label_create(content_label_container_2);
    lv_label_set_text(content_label_4, "Tip: Once connected,you\ncan transfer books and\nimages from your phone\nto the device.");
    lv_obj_set_style_text_font(content_label_4,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(content_label_4,0, LV_PART_MAIN);
    lv_obj_align_to(content_label_4, content_label_3,LV_ALIGN_OUT_BOTTOM_MID, -4, 30);
}


void ui_en_operation_notice_deinit(void){

    if(ui_en_operation_notice_group != NULL){
        lv_group_del(ui_en_operation_notice_group);
        ui_en_operation_notice_group = NULL;
    }
    
    if(ui_en_operation_notice_container != NULL){
        lv_obj_del(ui_en_operation_notice_container);
        ui_en_operation_notice_container = NULL;
    }
    if(last_en_group != NULL){
        lv_group_set_default(last_en_group);
        lv_indev_set_group(indev_keypad, lv_group_get_default());
        last_en_group = NULL;
    }
}