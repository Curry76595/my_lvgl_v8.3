#ifndef _UI_EBOOK_MAIN_H_
#define _UI_EBOOK_MAIN_H_

#include "lvgl/lvgl.h"

typedef struct ui_Control_tt
{
    //焦点组
    lv_group_t * group_list_focus;          //文件列表界面焦点组
    lv_group_t * group_Catalog_focus;       //初次进书本的目录界面焦点组
    lv_group_t * group_Menu_focus;          //菜单界面焦点组
    lv_group_t * group_Menu_catalog_focus;  //菜单的目录界面焦点组
    lv_group_t * group_BookMarks_focus;     //菜单的书签界面焦点组
    lv_group_t * group_PageJump_focus;      //菜单的跳转界面焦点组
    lv_group_t * group_Auto_focus;          //菜单的自动界面焦点组
    lv_group_t * group_FontSize_focus;      //菜单的字号界面焦点组
    lv_group_t * group_LineHigh_focus;      //菜单的字距界面焦点组
    lv_group_t * group_SearchWords_focus;   //菜单的查词界面焦点组
    lv_group_t * group_Delete_focus;        //菜单的删除界面焦点组
    //各个功能的主控件
    lv_obj_t * main_bg;                     //背景
    lv_obj_t * exit_img;                    //退出控件
    lv_obj_t * label_page;                  //页数
    lv_obj_t * label_content;               //阅读文本
    lv_obj_t * label_list;                  //文件列表
    lv_obj_t * bg;                          //除去状态栏的背景
    lv_obj_t * menu;                        //菜单
    lv_obj_t * menu_line;                   //菜单的竖线
    lv_obj_t * catelog;                     //菜单的目录
    lv_obj_t * bookmarks;                   //菜单的书签
    lv_obj_t * Page_Jump;                   //菜单的跳转
    lv_obj_t * Auto;                        //菜单的自动
    lv_obj_t * font_size;                   //菜单的字号
    lv_obj_t * Line_High;                   //菜单的字距
    lv_obj_t * Search_Words;                //菜单的查词
    lv_obj_t * Delete;                      //菜单的删除
    //要操作的子控件
    lv_obj_t * Font_Size[3];                //3个字号框
    lv_obj_t * Select_list[8];              //文件列表的8个文件框
    lv_obj_t * Book_Marks[8];               //书签的8个选项框
    lv_obj_t * Book_Catalog[8];             //目录的8个框
    lv_obj_t * Book_Catalog_Text[8];        //目录的8个框的文本框
    char * book_catalog_text[8];            //8个目录文本
    lv_obj_t * Menu_list[8];                //菜单的8个选项
    lv_obj_t * Menu_Text[8];                //菜单的8个选项的文本框
    lv_obj_t * Number_Key[10];              //10个数字的框
}ui_Control_t;
ui_Control_t * ui_ebook_control;

lv_coord_t scr_w;
lv_coord_t scr_h;


#endif
