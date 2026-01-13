/**
 * @file option_image_state_example.h
 * @description: 选项图片状态管理示例头文件
 */

#ifndef OPTION_IMAGE_STATE_EXAMPLE_H
#define OPTION_IMAGE_STATE_EXAMPLE_H

#include "lvgl/lvgl.h"

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
lv_obj_t *create_option_image(lv_obj_t *parent, int option_index, int x, int y);

/**
 * @description: 手动设置选项状态
 * @param {int} option_index - 选项索引
 * @param {option_state_t} state - 目标状态
 * @return {*}
 */
void set_option_state(int option_index, option_state_t state);

/**
 * @description: 获取选项当前状态
 * @param {int} option_index - 选项索引
 * @return {option_state_t} 当前状态
 */
option_state_t get_option_state(int option_index);

#endif /* OPTION_IMAGE_STATE_EXAMPLE_H */



