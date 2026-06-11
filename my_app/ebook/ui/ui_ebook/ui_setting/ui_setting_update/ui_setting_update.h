#ifndef UI_SETTING_UPDATE_H
#define UI_SETTING_UPDATE_H


#include "ui_ebook/ui_setting/ui_setting_main/ui_setting_main.h"
#include "ui_ebook/ui_transfer_book/ui_clound_sync/ui_cloud_sync.h"

typedef struct{
    lv_obj_t *ui_update_label;
    lv_obj_t *ui_download_container;
    lv_obj_t *ui_download_confirm_container;
    lv_group_t *ui_last_group;//上一个聚焦的组
} ui_setting_update_t;

//OTA包对应的ui控件
typedef struct{
    lv_obj_t *card;                               //任务卡片
    lv_obj_t *progress_container;                 //进度整体容器
    lv_obj_t *progress_content_container;         //进度文本容器
    lv_obj_t *progress_value;                     //进度值
    lv_obj_t *progress_status;                    //进度状态
    lv_obj_t *task_space;                         //任务占用大小
    lv_obj_t *task_name;                          //任务名称
    lv_obj_t *progress_bar;                       //进度条
}ui_update_task_t;

//OTA包数据结构
typedef struct{
    char task_name[64];                          //任务名
    int progress;                                //0~100
    float task_space;                           //占用大小
    task_status_t status;                       //状态
    task_type_t type;                           //类型
}update_task_data_t;

static const char *update_status_text[] = {
    "等待中",
    "下载中",
    "解析中",
    "已完成",
    "失败",
    "空间不够"
};

void ui_setting_update_init(void);
void ui_create_update_task_card(void);
void ui_destory_update_task_card(void);
extern ui_setting_update_t ui_setting_update;


#endif

