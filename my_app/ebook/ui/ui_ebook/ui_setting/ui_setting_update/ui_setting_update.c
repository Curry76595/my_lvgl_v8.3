#include "ui_setting_update.h"

/**************************************************声明变量**************************************** */
    
ui_setting_update_t ui_setting_update = {0};
char *ui_update_btn_label[2] = {"否","是"};

typedef struct{
    update_task_data_t data;//任务数据结构
    ui_update_task_t ui;//任务UI控件
}update_task_item_t;

update_task_item_t *update_task = NULL;
char ota_space_buf[32] = {0};

/************************************************内存申请释放*************************************************/
//申请内存
static int update_task_calloc(int count){
    if(count <= 0) return -1;
    if(update_task != NULL){
        free(update_task);
        update_task = NULL;
    }
    update_task = (update_task_item_t *)calloc((size_t)count, sizeof(update_task_item_t));
    if(update_task == NULL){
        return -1;
    }
    return 0;
}

//释放内存
static void update_task_free(void){
    if(update_task != NULL){
        free(update_task);
        update_task = NULL;
    }
}

/************************************************ui界面设计细节************************************************/
/**
 * @description: 选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_setting_set_download_update_focus(lv_obj_t *obj, bool focus)
{
    lv_obj_t * child_obj = lv_obj_get_child(obj,0);
    if(focus){//选中效果
        lv_obj_set_style_bg_color(obj, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_white(), LV_PART_MAIN);
    }
    else{//不选中效果
        lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_black(), LV_PART_MAIN);
    }
}




/*****************************************回调函数******************************************/
/**
 * @description: 聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_download_update_focus_event_cb(lv_event_t *e){
    lv_obj_t *download_update_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_setting_set_download_update_focus(download_update_obj,true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_setting_set_download_update_focus(download_update_obj,false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_setting_download_update_key_event_cb(lv_event_t *e){
    lv_group_t *current_group;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *focused_obj = lv_group_get_focused(lv_obj_get_group(obj));//获取当前聚焦对象
    int user_data = (int)lv_event_get_user_data(e);
    if(focused_obj){//获取当前聚焦对象的组
        current_group = lv_obj_get_group(focused_obj);
    }
    if(code == LV_EVENT_KEY){
        uint32_t KEY = lv_event_get_key(e);
        switch(KEY){
            case LV_KEY_LEFT:
                if(current_group) lv_group_focus_prev(current_group);
                break;
            case LV_KEY_RIGHT:
                if(current_group) lv_group_focus_next(current_group);
                break;
            case LV_KEY_ENTER:
                switch(user_data){
                    case 0:
                        lv_obj_clear_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_add_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        lv_group_focus_obj(lv_obj_get_child(ui_setting_update.ui_download_confirm_container, 1));
                        break;
                    case 1:
                        lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_clear_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        lv_group_focus_obj(ui_setting_update.ui_download_container);
                        break;   
                    case 2:
                        //TODO:执行下载更新操作
                        lv_obj_add_flag(ui_setting_update.ui_update_label, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_add_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        ui_create_update_task_card();
                        break;     
                }
                break;
            case LV_KEY_ESC:
                switch(user_data){
                    case 0:
                        //退出之前先清除聚焦状态
                        lv_obj_clear_flag(obj, LV_STATE_FOCUSED);
                        ui_setting_set_download_update_focus(obj,false);
                        if(ui_setting_update.ui_last_group){
                            lv_group_set_default(ui_setting_update.ui_last_group);
                            ui_setting_update.ui_last_group = NULL;
                            lv_indev_set_group(indev_keypad,lv_group_get_default());
                        }   
                        break;
                    case 1:
                        lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_clear_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        lv_group_focus_obj(ui_setting_update.ui_download_container);
                        break;
                    case 2:
                        lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_clear_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        lv_group_focus_obj(ui_setting_update.ui_download_container);
                        break;    
                    case 3:
                        lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);
                        lv_obj_clear_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_HIDDEN);
                        lv_group_focus_obj(ui_setting_update.ui_download_container);
                        ui_destory_update_task_card();
                        break;   
                }
                break;
            default:
                break;
        }

    }

}

/**
 * @description: 设置组函数和回调函数
 * @param {lv_obj_t} *obj
 * @return {*}
 */
static void ui_setting_download_update_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_setting_download_update_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_setting_download_update_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_setting_download_update_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}


/**
 * @description: 创建任务卡片
 * @return {*}
 */
void ui_create_update_task_card(void){
    //申请内存
    int ret = update_task_calloc(1);
    printf("<%s> update_task_calloc ret:%d\n", __func__, ret);
    update_task_item_t *task = &update_task[0];

    //任务卡片
    task->ui.card = lv_obj_create(ui_setting_display->update);
    lv_obj_add_flag(task->ui.card, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(task->ui.card, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(task->ui.card, 168, 88);
    lv_obj_set_style_radius(task->ui.card, 6, LV_PART_MAIN);
    lv_obj_set_style_border_color(task->ui.card, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_line_dash_width(task->ui.card, 1, LV_PART_MAIN);
    lv_obj_set_style_line_dash_gap(task->ui.card, 4, LV_PART_MAIN);
    lv_obj_set_style_border_width(task->ui.card, 1, LV_PART_MAIN);
    lv_obj_align(task->ui.card, LV_ALIGN_CENTER, -7, -15);

    lv_group_add_obj(ui_setting_display->ui_update_group, task->ui.card);
    lv_obj_add_event_cb(task->ui.card,ui_setting_download_update_key_event_cb,LV_EVENT_KEY, (int *)3);
    lv_group_focus_obj(task->ui.card);

    //进度整体容器
    task->ui.progress_container = lv_obj_create(task->ui.card);
    lv_obj_clear_flag(task->ui.progress_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(task->ui.progress_container, 167, 50);
    lv_obj_align(task->ui.progress_container, LV_ALIGN_TOP_MID, 0,-10 );
    lv_obj_set_style_border_color(task->ui.progress_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(task->ui.progress_container, 1, LV_PART_MAIN); 

    //进度文本容器
    task->ui.progress_content_container = lv_obj_create(task->ui.progress_container);
    lv_obj_clear_flag(task->ui.progress_content_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(task->ui.progress_content_container, 167, 32);
    lv_obj_align(task->ui.progress_content_container, LV_ALIGN_CENTER, 0,-8 );
    lv_obj_set_style_border_color(task->ui.progress_content_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(task->ui.progress_content_container, 1, LV_PART_MAIN);  

    //1.进度值
    task->ui.progress_value = lv_label_create(task->ui.progress_content_container);
    lv_label_set_text_fmt(task->ui.progress_value, "%d%%",100);
    lv_obj_set_style_text_font(task->ui.progress_value,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(task->ui.progress_value,0, LV_PART_MAIN);
    lv_obj_align(task->ui.progress_value, LV_ALIGN_LEFT_MID, -13, 0);

    //2.进度状态
    task->ui.progress_status = lv_label_create(task->ui.progress_content_container);
    lv_label_set_text(task->ui.progress_status, update_status_text[5]);
    lv_obj_set_style_text_font(task->ui.progress_status,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(task->ui.progress_status,-1, LV_PART_MAIN);
    lv_obj_align(task->ui.progress_status, LV_ALIGN_CENTER, -10, 0);

    //3.任务占用大小
    task->ui.task_space = lv_label_create(task->ui.progress_content_container);
    snprintf(ota_space_buf, sizeof(ota_space_buf), "%.2f MB", 10.23);
    lv_label_set_text(task->ui.task_space, ota_space_buf);
    lv_obj_set_style_text_font(task->ui.task_space,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(task->ui.task_space,-1, LV_PART_MAIN);
    lv_obj_align(task->ui.task_space, LV_ALIGN_RIGHT_MID, 12, 0);


    //进度条
    task->ui.progress_bar = lv_bar_create(task->ui.progress_container);
    lv_obj_set_size(task->ui.progress_bar, 158, 7);
    lv_obj_align(task->ui.progress_bar, LV_ALIGN_CENTER, 0, 15);
    lv_bar_set_range(task->ui.progress_bar, 0, 100);
    lv_bar_set_value(task->ui.progress_bar, task->data.progress, LV_ANIM_OFF); 

    lv_obj_set_style_bg_color(task->ui.progress_bar, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(task->ui.progress_bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(task->ui.progress_bar, lv_color_black(), LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(task->ui.progress_bar, LV_OPA_COVER, LV_PART_INDICATOR);
    lv_obj_set_style_border_width(task->ui.progress_bar, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(task->ui.progress_bar, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_radius(task->ui.progress_bar, 2, LV_PART_MAIN);

    //任务名称
    task->ui.task_name = lv_label_create(task->ui.card );
    lv_label_set_text(task->ui.task_name , "PKS1-V104");
    lv_obj_set_style_text_font(task->ui.task_name ,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(task->ui.task_name ,2, LV_PART_MAIN);
    lv_obj_align(task->ui.task_name , LV_ALIGN_BOTTOM_MID, 0, 3);



}


/**
 * @description: 销毁任务卡片
 * @return {*}
 */
void ui_destory_update_task_card(void){
    if(update_task == NULL) return;
    update_task_item_t *task = &update_task[0];
    lv_obj_del(task->ui.card);
    free(update_task);
    update_task = NULL;
}


void ui_setting_update_init(void){
    ui_setting_update.ui_update_label = lv_label_create(ui_setting_display->update);
    lv_label_set_text(ui_setting_update.ui_update_label, "检测发现新版本!");
    lv_obj_align(ui_setting_update.ui_update_label, LV_ALIGN_CENTER, 0, -50);
    lv_obj_set_style_text_font(ui_setting_update.ui_update_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_setting_update.ui_update_label, 8, LV_PART_MAIN);
    
    ui_setting_update.ui_download_container = lv_obj_create(ui_setting_display->update);
    lv_obj_set_size(ui_setting_update.ui_download_container, 100, 30);
    lv_obj_align_to(ui_setting_update.ui_download_container, ui_setting_update.ui_update_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
    lv_obj_clear_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_setting_update.ui_download_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_color(ui_setting_update.ui_download_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_setting_update.ui_download_container, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(ui_setting_update.ui_download_container, 8, LV_PART_MAIN);


    lv_obj_t *ui_download_label = lv_label_create(ui_setting_update.ui_download_container);
    lv_label_set_text(ui_download_label, "下载更新");
    lv_obj_set_style_text_font(ui_download_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_download_label, 2, LV_PART_MAIN);
    lv_obj_center(ui_download_label);

    //创建下载更新容器的焦点组
    ui_setting_display->ui_update_group = lv_group_create();
    ui_setting_download_update_group_set(ui_setting_display->ui_update_group, ui_setting_update.ui_download_container, 0);

    ui_setting_update.ui_download_confirm_container = lv_obj_create(ui_setting_display->update);
    lv_obj_set_size(ui_setting_update.ui_download_confirm_container, 150, 100);
    lv_obj_clear_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(ui_setting_update.ui_download_confirm_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(ui_setting_update.ui_download_confirm_container, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(ui_setting_update.ui_download_confirm_container, 8, LV_PART_MAIN);
    lv_obj_align(ui_setting_update.ui_download_confirm_container, LV_ALIGN_CENTER, -6, -20);

    lv_obj_t *confirm_label = lv_label_create(ui_setting_update.ui_download_confirm_container);
    lv_label_set_text(confirm_label, "是否更新版本?");
    lv_obj_set_style_text_font(confirm_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(confirm_label, 2, LV_PART_MAIN);
    lv_obj_align(confirm_label, LV_ALIGN_TOP_MID, 0, 0);


    for(int i = 0; i < 2; i++){
        lv_obj_t *ui_btn = lv_obj_create(ui_setting_update.ui_download_confirm_container);
        lv_obj_set_size(ui_btn, 35, 30);
        lv_obj_clear_flag(ui_btn, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_flag(ui_btn, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_border_color(ui_btn, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_border_width(ui_btn, 1, LV_PART_MAIN);
        lv_obj_set_style_radius(ui_btn, 8, LV_PART_MAIN);
        lv_obj_align(ui_btn, LV_ALIGN_BOTTOM_LEFT, 15 + i * 63, 0);

        lv_obj_t *btn_label = lv_label_create(ui_btn);
        lv_label_set_text(btn_label, ui_update_btn_label[i]);
        lv_obj_set_style_text_font(btn_label,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_center(btn_label);

        ui_setting_download_update_group_set(ui_setting_display->ui_update_group, ui_btn, i + 1);
    }
    lv_obj_add_flag(ui_setting_update.ui_download_confirm_container, LV_OBJ_FLAG_HIDDEN);


}


