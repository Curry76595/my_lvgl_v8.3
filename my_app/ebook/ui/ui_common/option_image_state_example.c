/**
 * @file option_image_state_example.c
 * @description: 选项图片状态管理示例
 * 说明：12张图片，3组（非聚焦、聚焦、选中），每组4张
 */

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define OPTION_COUNT 4  // 选项数量

/**********************
 *      TYPEDEFS
 **********************/
// 选项状态枚举
typedef enum {
    OPTION_STATE_NORMAL = 0,    // 非聚焦状态
    OPTION_STATE_FOCUSED,       // 聚焦状态
    OPTION_STATE_SELECTED       // 选中状态
} option_state_t;

/**********************
 *  STATIC VARIABLES
 **********************/
// 假设你已经声明了12张图片，格式如下：
// LV_IMG_DECLARE(img_option0_normal);
// LV_IMG_DECLARE(img_option1_normal);
// LV_IMG_DECLARE(img_option2_normal);
// LV_IMG_DECLARE(img_option3_normal);
// LV_IMG_DECLARE(img_option0_focused);
// LV_IMG_DECLARE(img_option1_focused);
// LV_IMG_DECLARE(img_option2_focused);
// LV_IMG_DECLARE(img_option3_focused);
// LV_IMG_DECLARE(img_option0_selected);
// LV_IMG_DECLARE(img_option1_selected);
// LV_IMG_DECLARE(img_option2_selected);
// LV_IMG_DECLARE(img_option3_selected);

// 图片资源二维数组：[状态][选项索引]
// 你需要将上面的图片变量填入这个数组
static const lv_img_dsc_t *option_images[3][OPTION_COUNT] = {
    // 非聚焦状态
    {
        NULL, // &img_option0_normal,
        NULL, // &img_option1_normal,
        NULL, // &img_option2_normal,
        NULL, // &img_option3_normal,
    },
    // 聚焦状态
    {
        NULL, // &img_option0_focused,
        NULL, // &img_option1_focused,
        NULL, // &img_option2_focused,
        NULL, // &img_option3_focused,
    },
    // 选中状态
    {
        NULL, // &img_option0_selected,
        NULL, // &img_option1_selected,
        NULL, // &img_option2_selected,
        NULL, // &img_option3_selected,
    }
};

// 存储每个选项的当前状态
static option_state_t option_states[OPTION_COUNT] = {OPTION_STATE_NORMAL};

// 存储每个选项的图片对象指针
static lv_obj_t *option_img_objs[OPTION_COUNT] = {NULL};

/**********************
 *  STATIC FUNCTIONS
 **********************/

/**
 * @description: 更新指定选项的图片显示
 * @param {int} option_index - 选项索引 (0-3)
 * @param {option_state_t} state - 新状态
 * @return {*}
 */
static void update_option_image(int option_index, option_state_t state)
{
    if (option_index < 0 || option_index >= OPTION_COUNT) {
        return;
    }
    
    if (option_img_objs[option_index] == NULL) {
        return;
    }
    
    const lv_img_dsc_t *img_src = option_images[state][option_index];
    if (img_src != NULL) {
        lv_img_set_src(option_img_objs[option_index], img_src);
        option_states[option_index] = state;
    }
}

/**
 * @description: 聚焦事件回调
 * @param {lv_event_t} *e
 * @return {*}
 */
static void option_focus_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int *option_index = (int *)lv_event_get_user_data(e);
    
    if (option_index == NULL) return;
    
    if (code == LV_EVENT_FOCUSED) {
        // 聚焦时，如果当前不是选中状态，则显示聚焦图片
        if (option_states[*option_index] != OPTION_STATE_SELECTED) {
            update_option_image(*option_index, OPTION_STATE_FOCUSED);
        }
    }
    else if (code == LV_EVENT_DEFOCUSED) {
        // 失去聚焦时，如果当前不是选中状态，则显示非聚焦图片
        if (option_states[*option_index] != OPTION_STATE_SELECTED) {
            update_option_image(*option_index, OPTION_STATE_NORMAL);
        }
    }
}

/**
 * @description: 点击事件回调（用于切换选中状态）
 * @param {lv_event_t} *e
 * @return {*}
 */
static void option_click_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED) return;
    
    lv_obj_t *obj = lv_event_get_target(e);
    int *option_index = (int *)lv_event_get_user_data(e);
    
    if (option_index == NULL) return;
    
    // 切换选中状态
    if (option_states[*option_index] == OPTION_STATE_SELECTED) {
        // 如果已选中，则取消选中（根据是否有聚焦来决定显示聚焦还是非聚焦）
        if (lv_obj_has_state(obj, LV_STATE_FOCUSED)) {
            update_option_image(*option_index, OPTION_STATE_FOCUSED);
        } else {
            update_option_image(*option_index, OPTION_STATE_NORMAL);
        }
    } else {
        // 如果未选中，则设置为选中
        update_option_image(*option_index, OPTION_STATE_SELECTED);
    }
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @description: 创建选项图片对象
 * @param {lv_obj_t} *parent - 父对象
 * @param {int} option_index - 选项索引 (0-3)
 * @param {int} x - X坐标
 * @param {int} y - Y坐标
 * @return {lv_obj_t*} 创建的图片对象
 */
lv_obj_t *create_option_image(lv_obj_t *parent, int option_index, int x, int y)
{
    if (option_index < 0 || option_index >= OPTION_COUNT) {
        return NULL;
    }
    
    // 创建图片对象
    lv_obj_t *img = lv_img_create(parent);
    lv_obj_set_pos(img, x, y);
    
    // 初始显示非聚焦状态
    const lv_img_dsc_t *img_src = option_images[OPTION_STATE_NORMAL][option_index];
    if (img_src != NULL) {
        lv_img_set_src(img, img_src);
    }
    
    // 保存图片对象指针
    option_img_objs[option_index] = img;
    option_states[option_index] = OPTION_STATE_NORMAL;
    
    // 为图片对象分配用户数据（存储选项索引）
    int *user_data = (int *)malloc(sizeof(int));
    *user_data = option_index;
    lv_obj_set_user_data(img, user_data);
    
    // 注册事件回调
    lv_obj_add_event_cb(img, option_focus_event_cb, LV_EVENT_FOCUSED, user_data);
    lv_obj_add_event_cb(img, option_focus_event_cb, LV_EVENT_DEFOCUSED, user_data);
    lv_obj_add_event_cb(img, option_click_event_cb, LV_EVENT_CLICKED, user_data);
    
    // 使图片对象可以聚焦
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_SCROLLABLE);
    
    return img;
}

/**
 * @description: 手动设置选项状态（可选，用于外部控制）
 * @param {int} option_index - 选项索引
 * @param {option_state_t} state - 目标状态
 * @return {*}
 */
void set_option_state(int option_index, option_state_t state)
{
    update_option_image(option_index, state);
}

/**
 * @description: 获取选项当前状态
 * @param {int} option_index - 选项索引
 * @return {option_state_t} 当前状态
 */
option_state_t get_option_state(int option_index)
{
    if (option_index < 0 || option_index >= OPTION_COUNT) {
        return OPTION_STATE_NORMAL;
    }
    return option_states[option_index];
}






