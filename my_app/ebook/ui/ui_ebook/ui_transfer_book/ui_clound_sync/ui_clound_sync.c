#include "ui_clound_sync.h"

ui_clound_sync_t *ui_clound_sync_list;

/************************************************内存申请释放*************************************************/
//申请内存
static void ui_clound_sync_malloc(void){
    if(ui_clound_sync_list == NULL){
        ui_clound_sync_list = (ui_clound_sync_t *)malloc(sizeof(ui_clound_sync_t));
        if(ui_clound_sync_list == NULL) return;
        memset(ui_clound_sync_list, 0, sizeof(ui_clound_sync_t));
    }
}



//释放内存
static void ui_clound_sync_free(void){
    if(ui_clound_sync_list != NULL){
        free(ui_clound_sync_list);
        ui_clound_sync_list = NULL;
    }
}

/*************************************************回调函数*******************************************/
static void ui_clound_sync_key_event_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_KEY){
        uint32_t key = lv_event_get_key(e);
        if(key == LV_KEY_ESC){
            printf("<%s> LV_KEY_ESC\n",__func__);
            ui_clound_sync_deinit();
        }
    }
}

void ui_clound_sync_init(void){

    //申请内存
    ui_clound_sync_malloc();

    //先获取默认焦点组
    ui_clound_sync_list->last_group = lv_group_get_default();
    //新建焦点组
    ui_clound_sync_list->clound_group = lv_group_create();
    lv_group_set_default(ui_clound_sync_list->clound_group); //设置新的焦点组为默认焦点组
    lv_indev_set_group(indev_keypad, lv_group_get_default());

    //创建一个霸屏容器
    ui_clound_sync_list->ui_clound_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_clound_sync_list->ui_clound_container, 240, 360);
    lv_obj_clear_flag(ui_clound_sync_list->ui_clound_container, LV_OBJ_FLAG_SCROLLABLE);

    //退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_clound_sync_list->ui_clound_container);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_clound_sync_list->ui_clound_container, LV_ALIGN_TOP_LEFT, -6, -8);
    lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_width(ui_exit, 0, 0);
    lv_obj_set_style_radius(ui_exit, 0, 0);
    lv_obj_set_style_pad_all(ui_exit, 0, 0);
    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align_to(ui_exit_img, ui_exit, LV_ALIGN_TOP_LEFT, 0, 0);

    //创建标题
    lv_obj_t *ui_clound_title = lv_label_create(ui_clound_sync_list->ui_clound_container);
    lv_label_set_text(ui_clound_title, "云同步下载列表");
    lv_obj_set_style_text_letter_space(ui_clound_title,2, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_clound_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_clound_title, LV_ALIGN_TOP_LEFT, 10, -8);

    //创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_clound_sync_list->ui_clound_container);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);

    //创建内容显示容器
    lv_obj_t *content_display_container = lv_obj_create(ui_clound_sync_list->ui_clound_container);
    lv_obj_set_size(content_display_container, 235, 320);
    lv_obj_add_flag(content_display_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(content_display_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(content_display_container, LV_ALIGN_TOP_MID, 0, 23);
    lv_obj_set_style_border_color(content_display_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_display_container, 1, LV_PART_MAIN);
    lv_group_add_obj(ui_clound_sync_list->clound_group , content_display_container);
    lv_obj_add_event_cb(content_display_container,ui_clound_sync_key_event_cb,LV_EVENT_KEY,NULL);
    
}


void ui_clound_sync_deinit(void){
    if(ui_clound_sync_list != NULL){
        if(ui_clound_sync_list->clound_group != NULL){
            lv_group_del(ui_clound_sync_list->clound_group);
            ui_clound_sync_list->clound_group = NULL;
        }
        if(ui_clound_sync_list->ui_clound_container != NULL){
            lv_obj_del(ui_clound_sync_list->ui_clound_container);
            ui_clound_sync_list->ui_clound_container = NULL;
        }
        if(ui_clound_sync_list->last_group != NULL){
            lv_group_set_default(ui_clound_sync_list->last_group);
            lv_indev_set_group(indev_keypad, lv_group_get_default());
            ui_clound_sync_list->last_group = NULL;
        }
    }
    ui_clound_sync_free();//释放内存
}

