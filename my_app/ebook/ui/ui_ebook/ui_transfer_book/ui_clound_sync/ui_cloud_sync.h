#ifndef UI_CLOUD_SYNC_H
#define UI_CLOUD_SYNC_H


#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdlib.h>
#include <string.h>

typedef struct ui_cloud_sync_ts{
    lv_obj_t *ui_cloud_container;//霸屏容器
    lv_group_t *last_group;//上一个焦点组
    lv_group_t *cloud_group;//云同步焦点组
}ui_cloud_sync_t;



//任务状态
typedef enum{
    TASK_STATUS_WAITING = 0,
    TASK_STATUS_DOWNLOADING,
    TASK_STATUS_DOWN,
}task_status_t;

//任务类型
typedef enum{
    TASK_TYPE_UNKNOWN = 0,
    TASK_TYPE_IMAGE,
    TASK_TYPE_BOOK,
    TASK_TYPE_OTA,
}task_type_t;

//任务数据结构
typedef struct{
    char task_name[64];  //任务名
    int progress;        //0~100
    float task_space;     //占用大小
    task_status_t status;//状态
    task_type_t type;//类型
}cloud_task_data_t;


//单个任务对应的ui控件
typedef struct{
    lv_obj_t *card;                         //任务卡片
    lv_obj_t *img_container;                //图片容器
    lv_obj_t *img;                          //图片
    lv_obj_t *progress_container;           //进度整体容器
    lv_obj_t *progress_content_container;   //进度文本容器
    lv_obj_t *progress_value;               //进度值
    lv_obj_t *progress_status;              //进度状态
    lv_obj_t *task_space;                   //任务占用大小
    lv_obj_t *task_name;                    //任务名称
    lv_obj_t *progress_bar;                 //进度条
}ui_cloud_task_t;

void ui_cloud_sync_init(void);
void ui_cloud_sync_deinit(void);
#endif
