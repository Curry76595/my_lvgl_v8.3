/**
 * @file option_image_usage_example.c
 * @description: 选项图片状态管理使用示例
 */

#include "option_image_state_example.h"
#include "lvgl/lvgl.h"

// 假设你已经将12张图片转换为C数组并声明了它们
// 示例：使用LVGL在线工具转换图片后，会生成类似这样的代码
/*
// 非聚焦状态图片
LV_IMG_DECLARE(img_option0_normal);
LV_IMG_DECLARE(img_option1_normal);
LV_IMG_DECLARE(img_option2_normal);
LV_IMG_DECLARE(img_option3_normal);

// 聚焦状态图片
LV_IMG_DECLARE(img_option0_focused);
LV_IMG_DECLARE(img_option1_focused);
LV_IMG_DECLARE(img_option2_focused);
LV_IMG_DECLARE(img_option3_focused);

// 选中状态图片
LV_IMG_DECLARE(img_option0_selected);
LV_IMG_DECLARE(img_option1_selected);
LV_IMG_DECLARE(img_option2_selected);
LV_IMG_DECLARE(img_option3_selected);
*/

/**
 * @description: 初始化选项图片数组
 * 注意：你需要在 option_image_state_example.c 中修改 option_images 数组，
 * 将 NULL 替换为实际的图片变量地址
 * 
 * 例如在 option_image_state_example.c 中：
 * static const lv_img_dsc_t *option_images[3][OPTION_COUNT] = {
 *     {&img_option0_normal, &img_option1_normal, &img_option2_normal, &img_option3_normal},
 *     {&img_option0_focused, &img_option1_focused, &img_option2_focused, &img_option3_focused},
 *     {&img_option0_selected, &img_option1_selected, &img_option2_selected, &img_option3_selected}
 * };
 */
void init_option_images_example(void)
{
    // 这个函数只是示例说明，实际初始化在 option_image_state_example.c 中完成
}

/**
 * @description: 创建选项界面示例
 * @param {lv_obj_t} *parent - 父对象
 * @return {*}
 */
void create_options_ui_example(lv_obj_t *parent)
{
    // 创建4个选项图片，横向排列
    int start_x = 50;
    int start_y = 100;
    int spacing = 100;  // 选项之间的间距
    
    for (int i = 0; i < 4; i++) {
        lv_obj_t *option_img = create_option_image(
            parent, 
            i, 
            start_x + i * spacing, 
            start_y
        );
        
        // 将选项添加到焦点组（如果需要键盘导航）
        // lv_group_add_obj(your_group, option_img);
    }
}

/**
 * @description: 使用示例 - 在main函数或UI初始化函数中调用
 */
void usage_example(void)
{
    lv_obj_t *screen = lv_scr_act();
    
    // 创建选项界面
    create_options_ui_example(screen);
    
    // 如果需要手动设置某个选项的状态，可以这样：
    // set_option_state(0, OPTION_STATE_SELECTED);  // 将选项0设置为选中状态
    // set_option_state(1, OPTION_STATE_FOCUSED);   // 将选项1设置为聚焦状态
    
    // 如果需要查询某个选项的状态，可以这样：
    // option_state_t state = get_option_state(0);
    // if (state == OPTION_STATE_SELECTED) {
    //     // 选项0已被选中
    // }
}



