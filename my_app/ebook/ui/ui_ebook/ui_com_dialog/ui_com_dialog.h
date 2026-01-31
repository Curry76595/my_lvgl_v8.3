#ifndef UI_COM_DIALOG_H
#define UI_COM_DIALOG_H
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "ui_common/ui_common.h"




#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    E_COM_DIALOG_Q1_EVENT_NONE = 0,
    E_COM_DIALOG_Q1_EVENT_UPDATE,         // 更新
    E_COM_DIALOG_Q1_EVENT_DEL_WIFI,       // 删除已连接的WiFi
    E_COM_DIALOG_Q1_EVENT_DEL_AUDIO_FILE, // 删除列表中的音频文件
    E_COM_DIALOG_Q1_EVENT_RESET_FACTORY,  // 恢复出厂设置
} E_COM_DIALOG_Q1_EVENT;

void ui_com_dialog_q1_create(void);                                                                         // 创建对话框
void ui_com_dialog_show_tips(char *tips_text);                                                              // 显示提示对话框 
#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
