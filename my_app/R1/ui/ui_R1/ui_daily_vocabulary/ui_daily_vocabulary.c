#include "ui_daily_vocabulary.h"

static ui_daily_vocabulary_t g_daily_vocab_ui;

static void ui_daily_vocabulary_create_top(lv_obj_t *parent){
    lv_obj_t *title;

    g_daily_vocab_ui.top_bar = ui_com_bg_cont_create(parent);
    lv_obj_set_size(g_daily_vocab_ui.top_bar, lv_disp_get_hor_res(NULL), 40);
    lv_obj_align(g_daily_vocab_ui.top_bar, LV_ALIGN_TOP_MID, 0, 0);

    title = lv_label_create(g_daily_vocab_ui.top_bar);
    lv_label_set_text(title, "每日单词");
    lv_obj_set_style_text_font(title, &Chinese_font_16, 0);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 10, 0);

    //后续再补充 wifi bat charge等


}


static lv_obj_t *ui_daily_label_create(lv_obj_t *parent, const char *text, const lv_font_t *font){
    lv_obj_t *label = lv_label_create(parent);

    lv_label_set_text(label, text ? text : "");
    lv_obj_set_style_text_font(label, font, 0);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, lv_disp_get_hor_res(NULL) - 24);

    return label;
}

void ui_daily_vocabulary_init(void){
    lv_coord_t width = lv_disp_get_hor_res(NULL);
    lv_coord_t height = lv_disp_get_ver_res(NULL);
    // if(!word) return;

    ui_daily_vocabulary_deinit();

    g_daily_vocab_ui.main = ui_com_bg_cont_create(lv_scr_act());
    lv_obj_set_size(g_daily_vocab_ui.main, width, height);
    lv_obj_align(g_daily_vocab_ui.main, LV_ALIGN_CENTER, 0, 0);
    
    //创建顶部条
    ui_daily_vocabulary_create_top(g_daily_vocab_ui.main);

    g_daily_vocab_ui.content = ui_com_bg_cont_create(g_daily_vocab_ui.main);
    lv_obj_set_size(g_daily_vocab_ui.content, width, height - 40);
    lv_obj_align(g_daily_vocab_ui.content, LV_ALIGN_TOP_MID, 0, 40);

    g_daily_vocab_ui.name_label = ui_daily_label_create(g_daily_vocab_ui.content, "brilliance", &lv_font_aliPuHui_36);
    lv_obj_set_style_text_align(g_daily_vocab_ui.name_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(g_daily_vocab_ui.name_label, LV_ALIGN_TOP_MID, 0, 55);

    g_daily_vocab_ui.phonetic_label = ui_daily_label_create(g_daily_vocab_ui.content, "[ˈfæntəsi]", &lv_font_misans_normal_phonetic_30);
    lv_obj_set_style_text_align(g_daily_vocab_ui.phonetic_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align_to(g_daily_vocab_ui.phonetic_label, g_daily_vocab_ui.name_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    g_daily_vocab_ui.meaning_title_label = ui_daily_label_create(g_daily_vocab_ui.content, "释义：", &lv_font_aliPuHui_36);
    lv_obj_align(g_daily_vocab_ui.meaning_title_label, LV_ALIGN_TOP_LEFT, 10, 160);

    g_daily_vocab_ui.meaning_label = ui_daily_label_create(g_daily_vocab_ui.content, "光辉；【光】辉度；漂亮；(名声)煊赫\n亮度；才华；辉煌", &lv_font_aliPuHui_36);
    lv_obj_align_to(g_daily_vocab_ui.meaning_label, g_daily_vocab_ui.meaning_title_label ,LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);

    g_daily_vocab_ui.example_title_label = ui_daily_label_create(g_daily_vocab_ui.content, "例句：", &lv_font_aliPuHui_36);
    lv_obj_align_to(g_daily_vocab_ui.example_title_label, g_daily_vocab_ui.meaning_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 28);

    g_daily_vocab_ui.example_label = ui_daily_label_create(g_daily_vocab_ui.content, "The brilliance of the stars is what makes the night so beautiful.", &lv_font_aliPuHui_36);
    lv_obj_align_to(g_daily_vocab_ui.example_label, g_daily_vocab_ui.example_title_label, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);
}

void ui_daily_vocabulary_deinit(void){
    if(g_daily_vocab_ui.main && lv_obj_is_valid(g_daily_vocab_ui.main)) lv_obj_del(g_daily_vocab_ui.main);
    memset(&g_daily_vocab_ui, 0, sizeof(g_daily_vocab_ui));
    
}