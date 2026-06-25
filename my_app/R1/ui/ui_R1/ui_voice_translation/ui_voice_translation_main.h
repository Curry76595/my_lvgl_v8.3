#ifndef UI_VOICE_TRANSLATION_MAIN_H
#define UI_VOICE_TRANSLATION_MAIN_H
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"
#include <stdlib.h>
#include <string.h>

#define VT_MAX_RECORDS   20
#define VT_TEXT_MAX_LEN  256
#define VT_PAGE_MAX      30
#define VT_BUBBLE_MAX_W  380
#define VT_BUBBLE_MIN_W  80
#define VT_BUBBLE_PAD_X  10
#define VT_BUBBLE_PAD_Y  10
#define VT_BUBBLE_LABEL_MAX_W   (VT_BUBBLE_MAX_W - VT_BUBBLE_PAD_X * 2)

#define VT_PAGE_ITEM_MAX  50
#define VT_TEXT_LINE_MAX  32

typedef enum{
    VT_LAYER_IDLE = 0,    //请按住下面图标说话
    VT_LAYER_LISTENING,   //聆听中
    VT_LAYER_TRANSLATING, //正在翻译
    VT_LAYER_FAILED,      //翻译失败
    VT_LAYER_CHAT,        //聊天层
}vt_layer_t;

typedef struct{
    char source[VT_TEXT_MAX_LEN];
    char translated[VT_TEXT_MAX_LEN];
}vt_chat_record_t;


typedef struct{
    int record_index;
    int is_source;
    int start_line;
    int line_count;
    int has_prev;
    int has_next;
}vt_page_item_t;

typedef struct{
    vt_page_item_t items[VT_PAGE_ITEM_MAX];
    int item_count;
}vt_page_info_t;

typedef struct{
    lv_obj_t *ui_img_container;              //图标容器
    lv_obj_t *ui_img;                        //图标显示
    lv_obj_t *ui_cue_label;                  //提示语
    lv_obj_t *ui_top_con;                    //顶部容器
    lv_obj_t *ui_voice_page;                 //页数显示
    lv_obj_t *com_layer;                     //通用层  
    lv_obj_t *chat_layer;                    //聊天层

    vt_page_info_t pages[VT_PAGE_MAX];        //翻译页信息 
    vt_layer_t layer;                         //当前层
    vt_chat_record_t records[VT_MAX_RECORDS];  //聊天记录

    const lv_img_dsc_t *source_avatar;        //右边冒泡图标接口
    const lv_img_dsc_t *translated_avatar;    //左边冒泡图标接口

    int record_count;                          //聊天记录数量
    int page_count;                            //总页数
    int cur_page;                              //当前页数  索引从0开始

}vt_ui_ctx_t;

typedef struct ui_voice_translation_ts{
    lv_obj_t *ui_voice_translation_container;//霸屏容器
    vt_ui_ctx_t ui_ctx;   //业务显示句柄
    lv_group_t *last_group;//上一个焦点组
    lv_group_t *voice_translation_group;//语音翻译焦点组
}ui_voice_translation_t;

void ui_voice_translation_init(void);
void ui_voice_translation_deinit(void);
#endif
