#include "ui_common.h"

static lv_style_t g_style_default;
lv_style_t g_ui_style_default;
lv_style_t g_ui_style_radius_20;

/**********************
 *   GLOBAL FUNCTIONS
**********************/
// 初始化背景样式
static void ui_default_style_init(void)
{
    lv_style_init(&g_style_default);
    lv_style_set_bg_color(&g_style_default, lv_color_white());
    lv_style_set_bg_opa(&g_style_default, LV_OPA_COVER);
    lv_style_set_radius(&g_style_default, 0);
    lv_style_set_border_width(&g_style_default, 0);
    lv_style_set_pad_all(&g_style_default, 0);
    lv_style_set_outline_width(&g_style_default, 0);
    lv_style_set_shadow_width(&g_style_default, 0);
    lv_style_set_text_color(&g_style_default, lv_color_black());
}
void ui_com_tip_style_init(void)
{
    lv_style_init(&g_ui_style_default);
    lv_style_set_border_width(&g_ui_style_default, 0);
    lv_style_set_radius(&g_ui_style_default, 0);
    lv_style_set_pad_all(&g_ui_style_default, 0);

    lv_style_init(&g_ui_style_radius_20);
    lv_style_set_border_width(&g_ui_style_radius_20, 0);
    lv_style_set_radius(&g_ui_style_radius_20, 20);
    lv_style_set_pad_all(&g_ui_style_radius_20, 0);
}
// 背景板
void ui_com_style_init(void)
{
    ui_default_style_init();
    ui_com_tip_style_init();
}

// 显示边框
void ui_com_border_show(lv_obj_t *obj)
{
    lv_obj_set_style_border_width(obj, 2, 0);
    lv_obj_set_style_border_color(obj, lv_color_black(), 0);
    lv_obj_set_style_border_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, 0);
}


// 背景板
lv_obj_t *ui_com_bg_cont_create(lv_obj_t * parent)
{
	lv_obj_t * container = lv_obj_create(parent);
    lv_obj_set_size(container, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE); /// Flags 禁止滚动
    lv_obj_set_style_bg_color(container, lv_color_white(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(container, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container,0,LV_PART_MAIN);
    lv_obj_set_style_pad_left(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(container,LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_text_color(container, lv_color_black(), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_align(container, LV_ALIGN_CENTER, 0, 0);

	return container;
}

// 文本
lv_obj_t *ui_com_label_create(lv_obj_t *parent)
{
	lv_obj_t *label = lv_label_create(parent);
    lv_obj_clear_flag(label, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(label, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(label,&Chinese_font_16,0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 使用默认style
    lv_obj_add_style(label, &g_style_default, LV_PART_MAIN);
    return label;
}

// 图片
lv_obj_t *ui_com_img_create(lv_obj_t *parent)
{
    lv_obj_t *img = lv_img_create(parent);
    lv_obj_clear_flag(img, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(img, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_size(img, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    // 使用 style
    lv_obj_add_style(img, &g_style_default, LV_PART_MAIN);
    return img;
}



