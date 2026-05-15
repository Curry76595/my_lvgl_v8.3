#include "ui_ebook_auto.h"
#include "lv_drivers/sdl/sdl_common.h"
#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UI_EBOOK_MAIN_LVGL_SWTICH 1
lv_indev_t *indev_keypad;
int line_pos = 58;
#if UI_EBOOK_MAIN_LVGL_SWTICH
void ui_ebook_TipSentence_create(lv_obj_t *Parent, char *TEXT1, char *TEXT2, int Pos)
{
    lv_obj_t * Tip_One = lv_obj_create(Parent);
    lv_obj_set_size(Tip_One, 135, 23);
    lv_obj_set_style_pad_all(Tip_One, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(Tip_One, LV_ALIGN_TOP_MID, 0, Pos);
    //
    lv_obj_t * label_1 = lv_label_create(Tip_One);
    lv_obj_set_size(label_1, 64+2, 23);
    lv_obj_set_style_pad_all(label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(label_1, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_font(label_1,&Chinese_font_16,0);
    lv_obj_set_style_text_color(label_1,lv_color_black(),NULL);
    lv_label_set_text(label_1, TEXT1);
    //
    lv_obj_t *arrow = lv_img_create(Tip_One);
    lv_img_set_src(arrow, &thick_left_arrow);
    lv_obj_set_size(arrow, thick_left_arrow.header.w, thick_left_arrow.header.h);
    lv_obj_align_to(arrow, label_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    //
    lv_obj_t * label_2 = lv_label_create(Tip_One);
    lv_obj_set_size(label_2, 32+2, 23);
    lv_obj_set_style_pad_all(label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(label_2, arrow, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_text_font(label_2, &Chinese_font_16, 0);
    lv_obj_set_style_text_color(label_2, lv_color_black(), NULL);
    lv_label_set_text(label_2, TEXT2);
}

// 菜单选中效果
static void ui_ebook_main_set_menu_focus(lv_obj_t *obj, int focus_en)
{
    lv_obj_t * child_obj = lv_obj_get_child(obj,0);
    if(focus_en){
        lv_obj_set_style_bg_color(obj, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_white(), LV_PART_MAIN);
    }
    else{
        lv_obj_set_style_bg_color(obj, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN);
        lv_obj_set_style_text_color(child_obj, lv_color_black(), LV_PART_MAIN);
    }
}
// 聚焦非聚焦回调函数
static void ui_ebook_focus_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    // int id =lv_event_get_user_data(e);
    // log_info("ui_ebook_focus_event_cb date=[%d]",id);
    if (!(obj && lv_obj_is_valid(obj))){
        // log_error(">>> %s invalid obj <<<", __func__);
        return;
    }
    if (code == LV_EVENT_FOCUSED){
        // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){
        //     ui_ebook_main_set_container_focus(obj, 1);
        // }
        // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){
            ui_ebook_main_set_menu_focus(obj, 1);
        // }
        // else{
        //     ui_ebook_main_set_container_focus(obj, 1);
        // }
    }
    else if (code == LV_EVENT_DEFOCUSED){
        // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){
        //     ui_ebook_main_set_container_focus(obj, 0);
        // }
        // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){
            ui_ebook_main_set_menu_focus(obj, 0);
        // }
        // else{
        //     ui_ebook_main_set_container_focus(obj, 0);
        // }
    }
}

// 按键事件回调函数
static void ui_ebook_key_event_cb(lv_event_t *e)
{
    // log_info("ui_ebook_key_event_cb start");
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    // int user_data = (int)lv_event_get_user_data(e);
    lv_obj_t *focused_obj;
    if (code == LV_EVENT_KEY){
        uint32_t key = lv_event_get_key(e);
        switch (key){
            case LV_KEY_LEFT:
                // 处理向左键
                // log_info("Key LEFT pressed");
                // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){    //文件选择
                //     Select_Num--;
                //     if(Select_Num < 0)
                //         Select_Num = file_count_temp -1;
                //     lv_group_focus_prev(ui_ebook_control->group_list_focus);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_AUDIO){   //阅读切页
                //     EBOOK_Switch_Page(false);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){    //菜单界面
                //     if(ui_ebook_control->group_Menu_focus){
                        // lv_group_focus_prev(ui_ebook_control->group_Menu_focus);
                //     }
                // }
                //Select_File_Show(false);
                focused_obj = lv_group_get_focused(lv_obj_get_group(obj));
                if(focused_obj){
                  lv_group_t *current_group = lv_obj_get_group(focused_obj);
                  if(current_group){
                    lv_group_focus_prev(current_group);
                  }
                }
                break;

            case LV_KEY_RIGHT:
                // 处理向右键
                // log_info("Key RIGHT pressed");
                // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){    //文件选择
                //     Select_Num++;
                //     if(Select_Num > file_count_temp -1)
                //         Select_Num = 0;
                //     lv_group_focus_next(ui_ebook_control->group_list_focus);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_AUDIO){   //阅读切页
                //     EBOOK_Switch_Page(true);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){    //菜单界面
                //     if(ui_ebook_control->group_Menu_focus){
                        // lv_group_focus_next(ui_ebook_control->group_Menu_focus);
                //     }
                // }
                focused_obj = lv_group_get_focused(lv_obj_get_group(obj));
                if(focused_obj){
                  lv_group_t *current_group = lv_obj_get_group(focused_obj);
                  if(current_group){
                    lv_group_focus_next(current_group);
                  }
                }
                break;

            case LV_KEY_ENTER:
                // 处理确认键
                // log_info("Key ENTER pressed  selete_fileName = %s", file_list_ui[Select_Num].name);
                // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){    //选中文件或文件夹
                //     if(file_list_ui[Select_Num].type == E_FILE_TYPE_FOLDER){
                //         appEbook_startActionState(APP_EBOOK_ACTION_FILE_LIST, UI_FILE_LIST_REFRESH_SHOW, (void *)Select_Num);
                //     }
                //     else{
                //         log_info("Select_Num=%d 文件的文件夹是=%s", Select_Num, file_list_ui[Select_Num].folder);
                //         appEbook_startActionState(APP_EBOOK_ACTION_FILE_LIST, UI_FILE_LIST_REFRESH_CLICKED, (void *)Select_Num);
                //     }
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_AUDIO){   //从阅读界面到菜单界面
                //     ACTION_STATUS = APP_EBOOK_ACTION_MENU;
                //     ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_Menu_focus);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){    //菜单界面
                //     if(Menu_Num == 0){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_CATALOG;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_Menu_catalog_focus);
                //     }
                //     else if(Menu_Num == 1){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_BOOKMARKS;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_BookMarks_focus);
                //     }
                //     else if(Menu_Num == 2){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_PAGEJUMP;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_PageJump_focus);
                //     }
                //     else if(Menu_Num == 3){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_AUTO;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_Auto_focus);
                //     }
                //     else if(Menu_Num == 4){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_FONTSIZE;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_FontSize_focus);
                //     }
                //     else if(Menu_Num == 5){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_LINEHIGH;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_LineHigh_focus);
                //     }
                //     else if(Menu_Num == 6){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_SEARCHWORD;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_SearchWords_focus);
                //     }
                //     else if(Menu_Num == 7){
                //         ACTION_STATUS = APP_EBOOK_ACTION_MENU_DELETE;
                //         ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_Delete_focus);
                //     }
                // }
                break;

            case LV_KEY_ESC:
                // 处理退出键
                // log_info("Key ESC pressed ACTION_STATUS=%d", ACTION_STATUS);
                //appEbook_startActionState(APP_EBOOK_ACTION_LIST, UI_EBOOK_LIST_REFRESH_BACK, (void *)user_data);
                // if(ACTION_STATUS == APP_EBOOK_ACTION_FILE_LIST){    //退出电子书
                //     appEbook_startActionState(APP_EBOOK_ACTION_FILE_LIST, UI_FILE_LIST_REFRESH_EXIT, NULL);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_AUDIO){   //退出阅读界面
                //     appEbook_startActionState(APP_EBOOK_ACTION_AUDIO, UI_EBOOK_EXIT, NULL);
                // }
                // else if(ACTION_STATUS == APP_EBOOK_ACTION_MENU){    //退出菜单界面
                //     ACTION_STATUS = APP_EBOOK_ACTION_AUDIO;
                //     ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_list_focus);
                // }
                // else{
                //     ACTION_STATUS = APP_EBOOK_ACTION_MENU;
                //     ui_Focus_Group_Ctl(true, ui_ebook_control->menu, ui_ebook_control->group_Menu_focus);
                // }
                break;

            default:
                // log_info("Key code: %d", key);
                break;
        }
    }
    else if(code == LV_EVENT_CLICKED){
        // log_info("Clicked");
    }
    else if(code == LV_EVENT_PRESSED){
        // log_info("Pressed");
    }
    else if(code == LV_EVENT_RELEASED){
        // log_info("Released");
    }
}
// 状态栏中退出模块按键
lv_obj_t *ui_ebook_exit_create(lv_obj_t *parent) {
  // 退出键
  lv_obj_t *ui_exit = lv_obj_create(parent);
  lv_obj_set_size(ui_exit, 40, 26);
  lv_obj_align_to(ui_exit, parent, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_style_border_width(ui_exit, 0, 0);
  lv_obj_set_style_radius(ui_exit, 0, 0);
  lv_obj_set_style_pad_all(ui_exit, 0, 0);
  lv_obj_t *exit_img_temp =lv_img_create(ui_exit); // 一般不需要控制的控件都一次性创建
  lv_img_set_src(exit_img_temp, &icon_com_exit);
  lv_obj_set_size(exit_img_temp, icon_com_exit.header.w,
                  icon_com_exit.header.h);
  lv_obj_align_to(exit_img_temp, ui_exit, LV_ALIGN_TOP_LEFT, 5, 5);

  return ui_exit;
}
static void ui_common_bg_create(void) {
  ui_ebook_control->main_bg = lv_obj_create(lv_scr_act());
  lv_obj_set_size(ui_ebook_control->main_bg, 240, 360);
  lv_obj_set_style_pad_all(ui_ebook_control->main_bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // ui_ebook_status_list_create(ui_ebook_control->main_bg);//创建背景状态栏
  ui_ebook_control->exit_img =ui_ebook_exit_create(ui_ebook_control->main_bg); // 状态栏的返回按键按键
}

// 创建圆角长方形
lv_obj_t *create_rounded_rectangle(lv_obj_t *parent, lv_coord_t w, lv_coord_t h,lv_coord_t radius, lv_color_t bg_color,lv_color_t border_color,
                                   lv_coord_t border_width, bool Is_Btn) {
  lv_obj_t *rect = NULL;
  if (Is_Btn)
    rect = lv_btn_create(parent);
  else
    rect = lv_obj_create(parent);

  lv_obj_set_size(rect, w, h);
  lv_obj_set_style_radius(rect, radius, LV_PART_MAIN);
  lv_obj_set_style_bg_color(rect, bg_color, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(rect, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动

  lv_obj_add_flag(rect, LV_OBJ_FLAG_CLICKABLE);
  // 设置边框
  lv_obj_set_style_border_color(rect, border_color, LV_PART_MAIN);
  lv_obj_set_style_border_width(rect, border_width, LV_PART_MAIN);
  lv_obj_set_style_border_opa(rect, LV_OPA_COVER, LV_PART_MAIN);
  if (Is_Btn)
    lv_obj_set_style_bg_color(rect, lv_color_hex(0xCCCCCC),
                              LV_PART_MAIN | LV_STATE_PRESSED);

  return rect;
}

// 创建圆长方形里的内容
lv_obj_t *Rounded_create_content(lv_obj_t *img_rounded, char *text, int label_x,int label_y, lv_coord_t align_x,lv_coord_t align_y) {
  // uint8_t label1_width = lv_txt_get_width(text, strlen(text),
  // &Chinese_font_16, 0, LV_TEXT_FLAG_NONE); int size = label1_width + 60;
  // 不用动态长度了，处理麻烦
  lv_obj_t *label_1 = lv_label_create(img_rounded);
  lv_obj_set_size(label_1, label_x, label_y);
  lv_obj_set_style_border_opa(label_1, 0, LV_PART_MAIN);
  lv_obj_set_style_text_font(label_1, &Chinese_font_16, 0);
  lv_obj_set_style_text_color(label_1, lv_color_black(), LV_PART_MAIN);
  lv_label_set_text(label_1, text);
  lv_label_set_long_mode(label_1, LV_LABEL_LONG_DOT);
  lv_obj_align(label_1, LV_ALIGN_TOP_MID, align_x, align_y);

  return label_1;
}
void ui_ebook_main_group_set(lv_group_t *group, lv_obj_t *obj, int user_data) {
  lv_group_add_obj(group, obj);
  lv_obj_add_event_cb(obj, ui_ebook_focus_event_cb, LV_EVENT_FOCUSED, (void *)(uintptr_t)user_data);
  lv_obj_add_event_cb(obj, ui_ebook_focus_event_cb, LV_EVENT_DEFOCUSED, (void *)(uintptr_t)user_data);
  lv_obj_add_event_cb(obj, ui_ebook_key_event_cb, LV_EVENT_KEY, (void *)(uintptr_t)user_data);
//   lv_obj_add_event_cb(obj, ui_ebook_key_event_cb, LV_EVENT_CLICKED, (void*)user_data); 
//   lv_obj_add_event_cb(obj, ui_ebook_key_event_cb,LV_EVENT_PRESSED, (void *)user_data); 
//   lv_obj_add_event_cb(obj,ui_ebook_key_event_cb, LV_EVENT_RELEASED, (void *)user_data);
}

// 列表遍历显示--焦点组版本
static void ui_ebook_menu_focus_create(void) {
  char name_1[] = "目录";
  char name_2[] = "书签";
  char name_3[] = "跳转";
  char name_4[] = "自动";
  char name_5[] = "字号";
  char name_6[] = "字距";
  char name_7[] = "查词";
  char name_8[] = "删除";
  char *Menu_list_name[8] = {name_1, name_2, name_3, name_4,
                             name_5, name_6, name_7, name_8};
  for (int i = 0; i < MENU_NUM; i++) {
    ui_ebook_control->Menu_list[i] =
        create_rounded_rectangle(ui_ebook_control->menu, 50, 33, 10,
                                 lv_color_white(), lv_color_black(), 0, false);
    lv_obj_align(ui_ebook_control->Menu_list[i], LV_ALIGN_TOP_LEFT, 0,
                 i * 36 + 20);
    ui_ebook_control->Menu_Text[i] = Rounded_create_content(
        ui_ebook_control->Menu_list[i], Menu_list_name[i], 36, 18, 2, -8);
    // 添加到焦点组
    ui_ebook_main_group_set(ui_ebook_control->group_Menu_focus, ui_ebook_control->Menu_list[i], i);
  }

  if (ui_ebook_control->group_Menu_focus) {
    // 焦点设置
    lv_obj_set_style_bg_color(ui_ebook_control->Menu_list[0], lv_color_black(),
                              LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui_ebook_control->Menu_list[0], 255, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_ebook_control->Menu_Text[0],
                                lv_color_white(), LV_PART_MAIN);
    lv_group_focus_obj(ui_ebook_control->Menu_list[0]);
  }
}


#endif



void ui_ebook_main_init(void) {
#if UI_EBOOK_MAIN_LVGL_SWTICH
  // 分配内存
  if (ui_ebook_control == NULL) {
    ui_ebook_control = (ui_Control_t *)malloc(sizeof(ui_Control_t));
    if (ui_ebook_control == NULL) {
      return; // 内存分配失败
    }
    // 初始化结构体为零
    memset(ui_ebook_control, 0, sizeof(ui_Control_t));
  }
#endif
  scr_w = lv_disp_get_hor_res(NULL);
  scr_h = lv_disp_get_ver_res(NULL);

#if UI_EBOOK_MAIN_LVGL_SWTICH
  ui_common_bg_create();
  // 显示区域框
  ui_ebook_control->bg = lv_obj_create(ui_ebook_control->main_bg);
  lv_obj_set_size(ui_ebook_control->bg, scr_w, 330);
  lv_obj_set_style_pad_all(ui_ebook_control->bg, 0,
                           LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align(ui_ebook_control->bg, LV_ALIGN_TOP_LEFT, 0, 30 + 1); // 避免重叠


  // 创建菜单背景
  ui_ebook_control->group_Menu_focus = lv_group_create();
  int menu_h = scr_h - 30;
  ui_ebook_control->menu = lv_obj_create(ui_ebook_control->bg);
  lv_obj_set_size(ui_ebook_control->menu, scr_w, menu_h);
  lv_obj_set_style_pad_all(ui_ebook_control->menu, 0,
                           LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_align(ui_ebook_control->menu, LV_ALIGN_TOP_LEFT, 0, 1);
  lv_obj_add_flag(ui_ebook_control->menu, LV_OBJ_FLAG_HIDDEN);

  // 创建竖线
  ui_ebook_control->menu_line = lv_line_create(ui_ebook_control->main_bg); // 线基于大背景才可以精准对其ui设计
  static lv_point_t line_points[] = {
      {0, 0},  // 设置起始点的坐标
      {0, 330} // 设置结束点的坐标
  };
  lv_line_set_points(ui_ebook_control->menu_line, line_points, 2);
  lv_obj_set_pos(ui_ebook_control->menu_line, line_pos, 30);
  lv_obj_set_style_line_width(ui_ebook_control->menu_line, 2,LV_PART_MAIN); // 设置线的宽度
  lv_obj_set_style_line_color(ui_ebook_control->menu_line, lv_color_black(),
                              LV_PART_MAIN);
  lv_obj_set_style_line_opa(ui_ebook_control->menu_line, 255, LV_PART_MAIN);
  lv_obj_add_flag(ui_ebook_control->menu_line, LV_OBJ_FLAG_HIDDEN);

  // 创建左侧列表
  ui_ebook_menu_focus_create();

  static lv_indev_drv_t indev_drv_keypad;
  lv_indev_drv_init(&indev_drv_keypad);
  indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv_keypad.read_cb = sdl_keyboard_read;
  indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
//   lv_indev_set_group(indev_keypad, ui_ebook_control->group_Menu_focus);
  
   //创建菜单栏右侧每一项选项的框
    int show_width = scr_w - line_pos;
    //目录
    ui_ebook_control->group_Menu_catalog_focus = lv_group_create();
    ui_ebook_control->catelog = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->catelog, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->catelog, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->catelog, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->catelog,LV_OBJ_FLAG_HIDDEN);
    //书签
    ui_ebook_control->group_BookMarks_focus = lv_group_create();
    ui_ebook_control->bookmarks = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->bookmarks, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->bookmarks, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->bookmarks, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->bookmarks,LV_OBJ_FLAG_HIDDEN);
    //跳转
    ui_ebook_control->group_PageJump_focus = lv_group_create();
    ui_ebook_control->Page_Jump = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->Page_Jump, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->Page_Jump, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->Page_Jump, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->Page_Jump,LV_OBJ_FLAG_HIDDEN);
    //自动
    ui_ebook_control->group_Auto_focus = lv_group_create();
    ui_ebook_control->Auto = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->Auto, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->Auto, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->Auto, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->Auto,LV_OBJ_FLAG_HIDDEN);
    //字号
    ui_ebook_control->group_FontSize_focus = lv_group_create();
    ui_ebook_control->font_size = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->font_size, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->font_size, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->font_size, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->font_size,LV_OBJ_FLAG_HIDDEN);
    //字距
    ui_ebook_control->group_LineHigh_focus = lv_group_create();
    ui_ebook_control->Line_High = lv_obj_create(ui_ebook_control->menu);
    lv_obj_set_size(ui_ebook_control->Line_High, show_width, menu_h);
    lv_obj_set_style_pad_all(ui_ebook_control->Line_High, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_ebook_control->Line_High, LV_ALIGN_TOP_LEFT, line_pos-4, 0);
    lv_obj_add_flag(ui_ebook_control->Line_High,LV_OBJ_FLAG_HIDDEN);
 #endif 

 ui_ebook_menu_Auto_Init();
}


void  ui_ebook_menu_Auto_Init(void){
    //开启自动菜单栏右侧的容器
     lv_obj_clear_flag(ui_ebook_control->menu,LV_OBJ_FLAG_HIDDEN);
     lv_obj_clear_flag(ui_ebook_control->Auto,LV_OBJ_FLAG_HIDDEN);
     lv_obj_clear_flag(ui_ebook_control->menu_line,LV_OBJ_FLAG_HIDDEN);
     lv_indev_set_group(indev_keypad, ui_ebook_control->group_Auto_focus); 
    //1.创建标题
     lv_obj_t *label_title = lv_label_create(ui_ebook_control->Auto);
     lv_label_set_text(label_title,"请设置自动翻页时间\n请输入60秒内的数字");
     lv_obj_set_style_text_line_space(label_title, 6, LV_PART_MAIN);
     lv_obj_set_style_text_font(label_title,&Chinese_font_16,LV_STATE_DEFAULT);
     lv_obj_align(label_title,LV_ALIGN_TOP_MID,0,30);

    //2.创建输入框
    lv_obj_t *input_box = lv_textarea_create(ui_ebook_control->Auto);
    lv_obj_set_width(input_box, 36);
    lv_obj_align(input_box,LV_ALIGN_TOP_MID,-13,90);
    lv_textarea_set_text(input_box,"0");
    lv_obj_set_style_text_font(input_box,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_textarea_set_max_length(input_box,2);//最多2位数字(0-60)
    lv_textarea_set_accepted_chars(input_box,"0123456789");//只允许输入数字
    lv_textarea_set_one_line(input_box,true);
    lv_obj_set_style_border_color(input_box, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_width(input_box, 1, LV_PART_MAIN);

    //3.创建输入框左边和右边的标签
    lv_obj_t *label_left = lv_label_create(ui_ebook_control->Auto);
    lv_label_set_text(label_left,"自动");
    lv_obj_set_style_text_letter_space(label_left,2, LV_PART_MAIN);
    lv_obj_set_style_text_font(label_left,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(label_left, LV_ALIGN_TOP_LEFT,20,100);
    lv_obj_t *label_right = lv_label_create(ui_ebook_control->Auto);
    lv_label_set_text(label_right,"秒后翻页");
    lv_obj_set_style_text_letter_space(label_right,1, LV_PART_MAIN);
    lv_obj_set_style_text_font(label_right,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(label_right, LV_ALIGN_TOP_RIGHT,-13,100);

    //4.创建数字键盘
    lv_obj_t *number_Key[11];
    lv_obj_t *num_label[11]; 
    int btn_size = 25;
    int btn_gap = 2;
    int keypad_start_x = 20;
    int keypad_start_y = 140;
    char num_text[10][2]={"1","2","3","4","5","6","7","8","9","0"};
    for(int i=0;i<10;i++){
        int row = i/5;
        int col = i%5;
        //1.创建按钮外框
        number_Key[i] = create_rounded_rectangle(ui_ebook_control->Auto, btn_size, btn_size, 5, 
            lv_color_white(), lv_color_black(), 1, true);
        lv_obj_align(number_Key[i],LV_ALIGN_TOP_LEFT,keypad_start_x + col *(btn_size + btn_gap), keypad_start_y + row *(btn_size +btn_gap));   
        //2.创建按钮标签
        num_label[i] = Rounded_create_content(number_Key[i],num_text[i], 20, 18, 5, -8);
        ui_ebook_main_group_set(ui_ebook_control->group_Auto_focus,number_Key[i], i);

    }
    if(ui_ebook_control->group_Auto_focus){
        lv_obj_set_style_bg_color(number_Key[0],lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(number_Key[0],255, LV_PART_MAIN);
        lv_obj_set_style_text_color(num_label[0],lv_color_white() , LV_PART_MAIN);
        lv_group_focus_obj(number_Key[0]);
    }
    
    //4行提示句
    ui_ebook_TipSentence_create(ui_ebook_control->Auto, "左右上下", "选择", 210);
    ui_ebook_TipSentence_create(ui_ebook_control->Auto, "短确认键", "输入", 235);
    ui_ebook_TipSentence_create(ui_ebook_control->Auto, "短返回键", "退格", 260);
    ui_ebook_TipSentence_create(ui_ebook_control->Auto, "长返回键", "退出", 285);



}


