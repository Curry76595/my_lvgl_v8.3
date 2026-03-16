#include "ui_image_list.h"
/******************************************************声明变量****************************************************/
#define UI_IMAGE_NUM     6   //每页显示的图片数量
char text_buf[64]  = {0};//定义存储标题的字符串
lv_obj_t *ui_image_title;//定义一个全局的标题
int current_page = 1;
int total_page = 3;
char *img_name_text[] = {
    "001.BMP",
    "002.BMP",
    "003.BMP",
    "004.BMP",
};
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define IMG_NAME_TEXT_COUNT  ARRAY_SIZE(img_name_text)  //获取数组元素个数

int image_container_num = UI_IMAGE_NUM;


lv_obj_t *image_name_list[UI_IMAGE_NUM];//图片显示列表
/***************************************************UI设置细节**************************************************/
/**
 * @description: 图片选中效果函数
 * @param {lv_obj_t} *obj
 * @param {int} focus_en
 * @return {*}
 */
static void ui_image_set_menu_focus(lv_obj_t *obj, bool focus)
{
    if(focus){//选中效果
        lv_obj_set_style_border_color(obj, lv_color_black(), LV_PART_MAIN);
    }
    else{//不选中效果
        lv_obj_set_style_border_color(obj, lv_color_white(), LV_PART_MAIN);
    }
}

static void ui_image_refresh_pre_page_display_image(void){
    lv_obj_t *label;
    int image_idex = current_page * UI_IMAGE_NUM - 1;
    for(int i = 0; i< image_container_num; i++){
        lv_obj_set_style_border_color(image_name_list[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_add_flag(image_name_list[i], LV_OBJ_FLAG_HIDDEN);//全部先隐藏掉，之后再来倒数开启，实现立马聚焦上一页的最后一张图片
    }
    for(int i = image_container_num - 1; i >= 0; i--){
        lv_obj_clear_flag(image_name_list[i], LV_OBJ_FLAG_HIDDEN);
        label = lv_obj_get_child(image_name_list[i], 1);
        lv_label_set_text(label, img_name_text[image_idex--]);
    }
}

/**
 * @description: 刷新下一页显示的图片
 * @return {*}
 */
static void ui_image_refresh_next_page_display_image(void){
    lv_obj_t *label;
    for(int i = 0; i< image_container_num; i++){//清除所有选中效果，避免切页的时候有些容器显示黑框
        lv_obj_set_style_border_color(image_name_list[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_add_flag(image_name_list[i], LV_OBJ_FLAG_HIDDEN);//全部先隐藏掉，之后要多少显示多少
    }
    int display_img_num = (IMG_NAME_TEXT_COUNT - (current_page - 1) * UI_IMAGE_NUM)>6 ? 6 : IMG_NAME_TEXT_COUNT - (current_page - 1) * UI_IMAGE_NUM;
    for(int i = 0; i < display_img_num; i++){
        lv_obj_clear_flag(image_name_list[i], LV_OBJ_FLAG_HIDDEN);
        label = lv_obj_get_child(image_name_list[i], 1);
        lv_label_set_text(label, img_name_text[(current_page - 1) * UI_IMAGE_NUM + i]);
    }
    //当当前对象被隐藏掉时，即将切换到下一个聚焦对象时，会立马聚焦到第一个被去除隐藏状态的对象上，而不是重头开始！！！
}

/*************************************************设置模块回调函数**********************************************/

/**
 * @description: 图片聚焦事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_image_focus_event_cb(lv_event_t *e){
    lv_obj_t *image_obj = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED){
        ui_image_set_menu_focus(image_obj, true);
    }
    else if(code == LV_EVENT_DEFOCUSED){
        ui_image_set_menu_focus(image_obj, false);
    }
}

/**
 * @description: 按键事件回调函数
 * @param {lv_event_t} *e
 * @return {*}
 */
static void ui_image_key_event_cb(lv_event_t *e){
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
                printf("LV_KEY_LEFT\n");
                switch(user_data){
                    case 0:
                        //直接切换到最后一页
                        current_page = total_page;
                        snprintf(text_buf, sizeof(text_buf), "图库 %d/%d", current_page, total_page);
                        lv_label_set_text_fmt(ui_image_title, text_buf);
                        ui_image_refresh_next_page_display_image();
                        break;
                    case 1:
                        if(current_page > 1){
                            current_page--;
                            snprintf(text_buf, sizeof(text_buf), "图库 %d/%d", current_page, total_page);
                            lv_label_set_text_fmt(ui_image_title, text_buf);
                            ui_image_refresh_pre_page_display_image();
                        }
                        break;
                }
                if(current_group) lv_group_focus_prev(current_group);
                break;

            case LV_KEY_RIGHT:
                 printf("LV_KEY_RIGHT\n");
                switch(user_data){
                    case IMG_NAME_TEXT_COUNT % UI_IMAGE_NUM://处于最后一页的最后一张照片时
                        if(current_page == total_page){
                            //直接切换到第一页
                            current_page = 1;
                            snprintf(text_buf, sizeof(text_buf), "图库 %d/%d", current_page, total_page);
                            lv_label_set_text_fmt(ui_image_title, text_buf);
                            ui_image_refresh_next_page_display_image();
                        }
                        break;
                    case UI_IMAGE_NUM://每一页的最后一张图片切到下一页特殊处理
                        if(current_page < total_page){
                            current_page++;
                            snprintf(text_buf, sizeof(text_buf), "图库 %d/%d", current_page, total_page);
                            lv_label_set_text_fmt(ui_image_title, text_buf);
                            ui_image_refresh_next_page_display_image();
                        }
                        break;
                }
                if(current_group ) lv_group_focus_next(current_group);
                break;
            case LV_KEY_ENTER:
                switch(user_data){
                    case 0:
                        break;
                    default:
                        ui_image_select_interface(1);
                        break;    
                }  
                
                break;
            case LV_KEY_ESC:
                 ui_image_main_deinit();//反初始化，释放内存，返回到传书主界面
                break;
            default:
                break;
        }

    }
}


/**************************************************封装回调函数***********************************************/
/**
 * @description: 设置组函数和回调函数
 * @param {lv_obj_t} *obj
 * @return {*}
 */
static void ui_image_menu_group_set(lv_group_t *group,lv_obj_t *obj,int user_data){
    lv_group_add_obj(group, obj);
    lv_obj_add_event_cb(obj, ui_image_focus_event_cb,LV_EVENT_FOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj, ui_image_focus_event_cb,LV_EVENT_DEFOCUSED , (void *)user_data);
    lv_obj_add_event_cb(obj,ui_image_key_event_cb,LV_EVENT_KEY, (void *)user_data);
}
/****************************************************初始化函数*****************************************************/
void ui_image_list_init(void){
    total_page = (IMG_NAME_TEXT_COUNT % UI_IMAGE_NUM == 0 ? IMG_NAME_TEXT_COUNT / UI_IMAGE_NUM : IMG_NAME_TEXT_COUNT / UI_IMAGE_NUM + 1);
     //创建标题-退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_image_display_list->ui_image_list);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_image_display_list->ui_image_list, LV_ALIGN_TOP_LEFT, -6, -8);
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
    lv_obj_t *ui_image_title_container = lv_obj_create(ui_image_display_list->ui_image_list);
    lv_obj_clear_flag(ui_image_title_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_image_title_container, 218, 30);
    lv_obj_align_to(ui_image_title_container, ui_exit, LV_ALIGN_OUT_RIGHT_MID, -30, 0);
    lv_obj_set_style_border_color(ui_image_title_container, lv_color_white(), LV_PART_MAIN);

    lv_label_t *ui_image_title_prefix = lv_label_create(ui_image_title_container);
    if(English_version){
        lv_label_set_text(ui_image_title_prefix, "Transfer My Photo");
        lv_obj_set_style_text_letter_space(ui_image_title_prefix,1, LV_PART_MAIN);
    }else{
        lv_label_set_text(ui_image_title_prefix, "我的传图");
        lv_obj_set_style_text_letter_space(ui_image_title_prefix,2, LV_PART_MAIN);
    }
    lv_obj_set_style_text_font(ui_image_title_prefix,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_image_title_prefix, LV_ALIGN_LEFT_MID, -10, 0);

    snprintf(text_buf, sizeof(text_buf), "%d/%d", current_page, total_page);
    ui_image_title = lv_label_create(ui_image_title_container);
    lv_label_set_text(ui_image_title, text_buf);
    lv_obj_set_style_text_font(ui_image_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_image_title,2, LV_PART_MAIN);
    lv_obj_align(ui_image_title, LV_ALIGN_RIGHT_MID, 6, 0);

    //创建焦点组
    ui_image_display_list->ui_image_list_group = lv_group_create();
    lv_indev_set_group(indev_keypad,ui_image_display_list->ui_image_list_group);
    // //创建手机传图容器
    // lv_obj_t *ui_phone_transfer_container = lv_obj_create(ui_image_display_list->ui_image_list);
    // lv_obj_add_flag(ui_phone_transfer_container, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_clear_flag(ui_phone_transfer_container, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_size(ui_phone_transfer_container, 80, 26);
    // lv_obj_set_style_border_width(ui_phone_transfer_container, 1, LV_PART_MAIN);
    // lv_obj_set_style_border_color(ui_phone_transfer_container, lv_color_black(), LV_PART_MAIN);
    // lv_obj_align(ui_phone_transfer_container, LV_ALIGN_TOP_RIGHT, 0, -9);
    
    // //创建手机传图标签
    // lv_obj_t *ui_phone_transfer_text = lv_label_create(ui_phone_transfer_container);
    // lv_label_set_text(ui_phone_transfer_text, "手机传图");
    // lv_obj_set_style_text_font(ui_phone_transfer_text,&Chinese_font_16,LV_STATE_DEFAULT);
    // lv_obj_set_style_text_letter_space(ui_phone_transfer_text,2, LV_PART_MAIN);
    // lv_obj_align(ui_phone_transfer_text, LV_ALIGN_CENTER, 0, 0);
    // //手机传图的坐标索引从0开始，图片索引从1开始
    // ui_image_menu_group_set(ui_image_display_list->ui_image_list_group,ui_phone_transfer_container,0);
    //创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_image_display_list->ui_image_list);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);
    
    //创建显示图片容器
    lv_obj_t *display_image_container = lv_obj_create(ui_image_display_list->ui_image_list);
    lv_obj_clear_flag(display_image_container, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_width(display_image_container, 1, LV_PART_MAIN);
    // lv_obj_set_style_border_color(display_image_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_align(display_image_container, LV_ALIGN_TOP_MID, 0, 23);
    lv_obj_set_size(display_image_container, 235, 335);
    
   
    if(IMG_NAME_TEXT_COUNT < UI_IMAGE_NUM) image_container_num = IMG_NAME_TEXT_COUNT;
    //创建图片文件名显示
    for(int i = 0; i < image_container_num; i++){
        //创建一张图片显示的容器
        image_name_list[i] = lv_obj_create(display_image_container);
        lv_obj_add_flag(image_name_list[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(image_name_list[i], LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(image_name_list[i], 223, 45);
        lv_obj_align(image_name_list[i], LV_ALIGN_TOP_MID, -1, -10+i*53);
        lv_obj_set_style_radius(image_name_list[i], 10, LV_PART_MAIN);
        lv_obj_set_style_border_color(image_name_list[i], lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(image_name_list[i], 1, LV_PART_MAIN);
        //创建图片显示的图案
        lv_obj_t *image_name_img = lv_img_create(image_name_list[i]);
        lv_img_set_src(image_name_img, &BMP);
        lv_obj_set_size(image_name_img, BMP.header.w, BMP.header.h);
        lv_obj_align(image_name_img, LV_ALIGN_LEFT_MID, 0, 0);
        //创建图片显示的文本
        lv_obj_t *image_name_label = lv_label_create(image_name_list[i]);
        lv_label_set_text(image_name_label, img_name_text[i]);
        lv_obj_set_style_text_font(image_name_label,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(image_name_label,2, LV_PART_MAIN);
        lv_obj_align_to(image_name_label, image_name_img,LV_ALIGN_OUT_RIGHT_MID, 10, 0);
        //创建图片显示的焦点组
        ui_image_menu_group_set(ui_image_display_list->ui_image_list_group,image_name_list[i],i+1);
    }

}
