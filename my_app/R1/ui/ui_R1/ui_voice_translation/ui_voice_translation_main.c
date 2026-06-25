#include "ui_voice_translation_main.h"
#define UI_VOICE_TRANSLATION_LVGL_SWITCH    1  //lvgl开关
ui_voice_translation_t *ui_voice_translation = NULL;
lv_indev_t *indev_keypad;
#define UI_VOICE_TRANSLATION_FONT  &lv_font_aliPuHui_36
/************************************************内存申请释放*************************************************/
//申请内存
static void ui_voice_translation_malloc(void){
    if(ui_voice_translation == NULL){
        ui_voice_translation = (ui_voice_translation_t *)malloc(sizeof(ui_voice_translation_t));
        if(ui_voice_translation == NULL) return;
        memset(ui_voice_translation, 0, sizeof(ui_voice_translation_t));
    }
}

//释放内存
static void ui_voice_translation_free(void){
    if(ui_voice_translation != NULL){
        free(ui_voice_translation);
        ui_voice_translation = NULL;
    }
}
/***************************************************end***********************************************/

/*************************************************测试文本***********************************/
char *source_text[] = {
    "今天天气怎么样",
    "为什么端午节会有赛龙舟这种习俗呢？",
    "为什么每年的高考英语作文都是李华呢？",
    "健康的乞丐也比生病的国王开心",
    "今天睡地板，明天当老板",
    "为什么最迷人的最危险，为什么爱会让人变残缺，为什么那么痛，还敢拿胸口再挡锐利伤悲"
};

char *translation_text[] = {
    "What's the weather like today?",
    "Why is dragon boat racing a custom during the Dragon Boat Festival?",
    "Why does Li Hua appear in the English writing section of the national college entrance examination every year?",
    "A healthy beggar is happier than a sick king.",
    "Sleep on the floor today, own a business tomorrow.",
    "Why are the most enchanting ones the most dangerous?Why does love leave people broken and incomplete?Why, amid all this agony,do I still bare my chest to bear sharp sorrows again?",
};


/***************************************************工具函数*********************************************/

static int vt_utf8_next(const char *s, int pos)
{
    unsigned char c = (unsigned char)s[pos];
    if(c < 0x80) return pos + 1;
    if((c & 0xE0) == 0xC0) return pos + 2;
    if((c & 0xF0) == 0xE0) return pos + 3;
    if((c & 0xF8) == 0xF0) return pos + 4;
    return pos + 1;
}

static void vt_copy_line_range(char *dst,int dst_size,const char *src,int line_start[],int line_end[],int start_line,int line_count)
{
    int start = line_start[start_line];
    int end = line_end[start_line + line_count - 1];
    int len = end - start;
    if(len >= dst_size) len = dst_size - 1;
    memcpy(dst, src + start, len);
    dst[len] = '\0';
}

static int vt_split_text_lines(const char *text, int line_start[], int line_end[])
{
    const lv_font_t *font = UI_VOICE_TRANSLATION_FONT;
    int text_len = strlen(text);
    int line_cnt = 0;
    int pos = 0;
    while(pos < text_len && line_cnt < VT_TEXT_LINE_MAX) {
        int start = pos;
        int last_fit = pos;
        int p = pos;
        while(p < text_len) {
            int next = vt_utf8_next(text, p);
            int len = next - start;
            char buf[VT_TEXT_MAX_LEN];
            if(len >= VT_TEXT_MAX_LEN) break;
            memcpy(buf, text + start, len);
            buf[len] = '\0';
            lv_point_t size;
            lv_txt_get_size(&size, buf, font, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
            if(size.x > VT_BUBBLE_LABEL_MAX_W) {
                break;
            }
            last_fit = next;
            p = next;
        }
        if(last_fit == start) {
            last_fit = vt_utf8_next(text, start);
        }
        line_start[line_cnt] = start;
        line_end[line_cnt] = last_fit;
        line_cnt++;
        pos = last_fit;
    }
    return line_cnt;
}

/*************************************************ui细节函数*****************************************/


/**
 * @description: 创建一个公共层（空闲、聆听、翻译、失败 共用）
 * @param {lv_obj_t} *layer
 * @return {*}
 */
static void ui_voice_create_com_layer(void){
    lv_coord_t width = lv_disp_get_hor_res(NULL);
    ui_voice_translation->ui_ctx.com_layer = ui_com_bg_cont_create(ui_voice_translation->ui_voice_translation_container);
    lv_obj_align_to(ui_voice_translation->ui_ctx.com_layer,  ui_voice_translation->ui_ctx.ui_top_con, LV_ALIGN_OUT_BOTTOM_MID, 3, 0);
    lv_obj_set_size(ui_voice_translation->ui_ctx.com_layer, width - 8, 638);
    lv_obj_set_style_border_width(ui_voice_translation->ui_ctx.com_layer, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_voice_translation->ui_ctx.com_layer, lv_color_white(), LV_PART_MAIN);

    //图标容器
    ui_voice_translation->ui_ctx.ui_img_container = ui_com_bg_cont_create(ui_voice_translation->ui_ctx.com_layer);
    lv_obj_set_size(ui_voice_translation->ui_ctx.ui_img_container, icon_ai_talk_listening.header.w + 5, icon_ai_talk_listening.header.h + 5);
    lv_obj_set_style_border_width(ui_voice_translation->ui_ctx.ui_img_container, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_voice_translation->ui_ctx.ui_img_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(ui_voice_translation->ui_ctx.ui_img_container, LV_ALIGN_TOP_MID, 0, 166);

    //图标
    ui_voice_translation->ui_ctx.ui_img = lv_img_create(ui_voice_translation->ui_ctx.ui_img_container);
    lv_obj_center(ui_voice_translation->ui_ctx.ui_img);
    lv_obj_add_flag(ui_voice_translation->ui_ctx.ui_img_container, LV_OBJ_FLAG_HIDDEN);

    //提示语
    ui_voice_translation->ui_ctx.ui_cue_label = lv_label_create(ui_voice_translation->ui_ctx.com_layer);
    lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "请按住下面录音图标开始说话");
    lv_obj_set_style_text_font(ui_voice_translation->ui_ctx.ui_cue_label, &EX_Chinese_font_36, LV_STATE_DEFAULT);
    lv_obj_align(ui_voice_translation->ui_ctx.ui_cue_label,LV_ALIGN_TOP_MID, 0, 260);

}

/**
 * @description: 刷新空闲层
 * @return {*}
 */
static void ui_voice_refresh_idle_layer(void){
    lv_obj_add_flag(ui_voice_translation->ui_ctx.ui_img_container, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "请按住下面录音图标开始说话");
}

/**
 * @description: 刷新聆听层
 * @param {int} data 0:汉语 1:英语
 * @return {*}
 */
static void ui_voice_refresh_listening_layer(int data){
    lv_obj_clear_flag(ui_voice_translation->ui_ctx.ui_img_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(ui_voice_translation->ui_ctx.ui_img, &icon_ai_talk_listening);
    switch(data){
        case 0:
            lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "聆听中,请说中文...");
            break;
        case 1:
            lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "聆听中,请说英文...");
            break;    
    }
}

/**
 * @description: 刷新翻译层
 * @return {*}
 */
static void ui_voice_refresh_translating_layer(void){
    lv_obj_clear_flag(ui_voice_translation->ui_ctx.ui_img_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(ui_voice_translation->ui_ctx.ui_img, &icon_ai_talk_thinking);
    lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "翻译中...");
}

/**
 * @description: 刷新翻译失败层
 * @return {*}
 */
static void ui_voice_refresh_failed_layer(void){
    lv_obj_clear_flag(ui_voice_translation->ui_ctx.ui_img_container, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_src(ui_voice_translation->ui_ctx.ui_img, &icon_translate_failed);
    lv_label_set_text(ui_voice_translation->ui_ctx.ui_cue_label, "翻译失败");
}



/**
 * @description: 创建聊天层
 * @return {*}
 */
static void ui_voice_create_char_layer(void){
    lv_coord_t width = lv_disp_get_hor_res(NULL);
    ui_voice_translation->ui_ctx.chat_layer = ui_com_bg_cont_create(ui_voice_translation->ui_voice_translation_container);
    lv_obj_align_to(ui_voice_translation->ui_ctx.chat_layer,  ui_voice_translation->ui_ctx.ui_top_con, LV_ALIGN_OUT_BOTTOM_MID, 3, 0);
    lv_obj_set_size(ui_voice_translation->ui_ctx.chat_layer, width - 8, 638);
    lv_obj_set_style_border_width(ui_voice_translation->ui_ctx.chat_layer, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_voice_translation->ui_ctx.chat_layer, lv_color_white(), LV_PART_MAIN);
}



/**
 * @description: 添加冒泡函数
 * @param {lv_obj_t} *parent
 * @param {char} *text
 * @param {int} is_source
 * @param {int} y
 * @return {*}
 */
static lv_obj_t *vt_add_bubble(lv_obj_t *parent, const char *text, int is_source, int y, int start_line, int line_count,
                                int has_prev, int has_next){
    const lv_font_t *font = UI_VOICE_TRANSLATION_FONT;
    int line_start[VT_TEXT_LINE_MAX];
    int line_end[VT_TEXT_LINE_MAX];
    vt_split_text_lines(text, line_start, line_end);
    char show_text[VT_TEXT_MAX_LEN];
    vt_copy_line_range(show_text, sizeof(show_text), text, line_start, line_end, start_line, line_count);

    lv_point_t txt_size;
    lv_txt_get_size(&txt_size, show_text, font, 0, 0,
                     VT_BUBBLE_LABEL_MAX_W, LV_TEXT_FLAG_NONE);
    lv_coord_t label_w = txt_size.x;        
    
    if(label_w < VT_BUBBLE_MIN_W - VT_BUBBLE_PAD_X * 2){
        label_w = VT_BUBBLE_MIN_W - VT_BUBBLE_PAD_X * 2;
    }

    if(label_w > VT_BUBBLE_LABEL_MAX_W){
        label_w = VT_BUBBLE_LABEL_MAX_W;
    }

    lv_coord_t bubble_w = label_w + VT_BUBBLE_PAD_X * 2;
    lv_coord_t bubble_h = line_count * font->line_height + VT_BUBBLE_PAD_Y * 2;

    lv_obj_t *bubble = lv_obj_create(parent);
    lv_obj_set_size(bubble, bubble_w, bubble_h);
    lv_obj_set_style_radius(bubble, 12, LV_PART_MAIN);
    lv_obj_set_style_border_width(bubble, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(bubble, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_pad_all(bubble, 10, LV_PART_MAIN);
    lv_obj_clear_flag(bubble, LV_OBJ_FLAG_SCROLLABLE);

    if(has_next){
        lv_obj_set_style_border_side(bubble, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_TOP, LV_PART_MAIN);
    }

    if(has_prev){
        lv_obj_set_style_border_side(bubble, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    }

    if(is_source) lv_obj_align(bubble, LV_ALIGN_TOP_RIGHT, -55, y);
    else lv_obj_align(bubble, LV_ALIGN_TOP_LEFT, 55, y);

    lv_obj_t *label = lv_label_create(bubble);
    lv_label_set_text(label,show_text);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label, label_w);
    lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);//文本内容向左对齐

    if(is_source)
        lv_obj_align(label, LV_ALIGN_TOP_RIGHT, 0, 0);
    else
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);

    return bubble;

}

/**
 * @description: 添加头像函数
 * @param {lv_obj_t} *parent
 * @param {int} is_source
 * @param {int} y
 * @return {*}
 */
static void vt_add_avatar(lv_obj_t *parent, int is_source, int y){
    const lv_img_dsc_t *img_src = is_source ? 
    ui_voice_translation->ui_ctx.source_avatar : 
    ui_voice_translation->ui_ctx.translated_avatar;

    if(img_src == NULL) return;

    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, img_src);

    if(is_source) lv_obj_align(img, LV_ALIGN_TOP_RIGHT, -5, y);
    else lv_obj_align(img, LV_ALIGN_TOP_LEFT, 5, y);
}

/**
 * @description: 获取文本高度
 * @param {char} *text
 * @return {*}
 */
static int vt_calc_text_height(const char *text){
    const lv_font_t *font = UI_VOICE_TRANSLATION_FONT;
    lv_point_t txt_size;
    lv_txt_get_size(&txt_size, text, font, 0, 0, 
                    VT_BUBBLE_LABEL_MAX_W, LV_TEXT_FLAG_NONE);
    return txt_size.y + VT_BUBBLE_PAD_Y * 2;                
}


/**
 * @description: 分页函数
 * @return {*}
 */
static void vt_add_text_to_pages(int *page, int *y, int max_h, int record_index,
                                int is_source, const char *text, int gap_after){
    const lv_font_t *font = UI_VOICE_TRANSLATION_FONT;
    int line_start[VT_TEXT_LINE_MAX];
    int line_end[VT_TEXT_LINE_MAX];
    int total_lines = vt_split_text_lines(text, line_start, line_end);
    int cur_line = 0;

    while(cur_line < total_lines && *page < VT_PAGE_MAX){
        int remain_h = max_h - *y;
        int can_lines = (remain_h - VT_BUBBLE_PAD_Y * 2) / font->line_height;

        if(can_lines <= 0){
            (*page)++;
            if(*page >= VT_PAGE_MAX) return;

            ui_voice_translation->ui_ctx.pages[*page].item_count = 0;
            *y = 16;
            continue;
        }

        int left_lines = total_lines - cur_line;
        int show_lines = left_lines;

        if(show_lines > can_lines){
            show_lines = can_lines;
        }

        vt_page_info_t *page_info = &ui_voice_translation->ui_ctx.pages[*page];

        if(page_info->item_count >= VT_PAGE_ITEM_MAX) return;

        vt_page_item_t *item = &page_info->items[page_info->item_count++];
        item->record_index = record_index;
        item->is_source = is_source;
        item->start_line = cur_line;
        item->line_count = show_lines;
        item->has_prev = cur_line > 0;
        item->has_next = (cur_line + show_lines) < total_lines;

        *y += show_lines * font->line_height + VT_BUBBLE_PAD_Y *2;

        cur_line += show_lines;

        if(cur_line < total_lines){
            (*page)++;
            if(*page >= VT_PAGE_MAX) return;
            ui_voice_translation->ui_ctx.pages[*page].item_count = 0;
            *y = 16;
        }else{
            *y += gap_after;
        }
    }
}

/**
 * @description: 创建聊天界面
 * @return {*}
 */
void ui_voice_translation_build_pages(void){
    int y = 16;
    int page = 0;
    lv_obj_update_layout(ui_voice_translation->ui_ctx.chat_layer);
    int max_h = lv_obj_get_height(ui_voice_translation->ui_ctx.chat_layer);
    printf("max_h: %d\n", max_h);

    memset(ui_voice_translation->ui_ctx.pages, 0, sizeof(ui_voice_translation->ui_ctx.pages));

    for(int i = 0; i < ui_voice_translation->ui_ctx.record_count; i++){
        vt_add_text_to_pages(&page, &y, max_h, i, 1, ui_voice_translation->ui_ctx.records[i].source, 18);
        vt_add_text_to_pages(&page, &y, max_h, i, 0, ui_voice_translation->ui_ctx.records[i].translated, 36);
    }
    ui_voice_translation->ui_ctx.page_count = page + 1;
}


/**
 * @description: 渲染当前页面
 * @return {*}
 */
void ui_voice_translation_render_page(void){
    lv_obj_clean(ui_voice_translation->ui_ctx.chat_layer);

    vt_page_info_t *page_info = &ui_voice_translation->ui_ctx.pages[ui_voice_translation->ui_ctx.cur_page];

    int y = 16;

    for(int i = 0; i < page_info->item_count; i++){
        vt_page_item_t *item = &page_info->items[i];
        vt_chat_record_t *rec = &ui_voice_translation->ui_ctx.records[item->record_index];

        const char *text = item->is_source ? rec->source : rec->translated;

        if(!item->has_prev){
            vt_add_avatar(ui_voice_translation->ui_ctx.chat_layer, item->is_source, y);
        }

        lv_obj_t *bubble = vt_add_bubble(ui_voice_translation->ui_ctx.chat_layer, text, item->is_source, y, 
                                     item->start_line, item->line_count, item->has_prev, item->has_next);

        lv_obj_update_layout(bubble);
        y += lv_obj_get_height(bubble);    
        
        if(item->has_next) y += 0;
        else y += item->is_source ? 18 : 36;
    }

    lv_label_set_text_fmt(ui_voice_translation->ui_ctx.ui_voice_page, "%d/%d",
                             ui_voice_translation->ui_ctx.cur_page + 1, ui_voice_translation->ui_ctx.page_count);
}


void ui_voice_translation_add_record(const char *source, const char *translated){
    if(!source || !translated) return;
    if(ui_voice_translation->ui_ctx.record_count >= VT_MAX_RECORDS){
        memmove(&ui_voice_translation->ui_ctx.records[0],
                &ui_voice_translation->ui_ctx.records[1],
                sizeof(vt_chat_record_t) * (VT_MAX_RECORDS - 1));
        ui_voice_translation->ui_ctx.record_count = VT_MAX_RECORDS - 1;
    }

    vt_chat_record_t *rec = &ui_voice_translation->ui_ctx.records[ui_voice_translation->ui_ctx.record_count++];
    strncpy(rec->source, source, VT_TEXT_MAX_LEN - 1);
    strncpy(rec->translated, translated, VT_TEXT_MAX_LEN -1);

    rec->source[VT_TEXT_MAX_LEN - 1] = '\0';
    rec->translated[VT_TEXT_MAX_LEN - 1] = '\0';

    ui_voice_translation_build_pages();
    ui_voice_translation->ui_ctx.cur_page = ui_voice_translation->ui_ctx.page_count - 1;
    ui_voice_translation_render_page();
}

/**     
 * @description: 用于刷新当前处于哪种状态
 * @param {vt_layer_t} layer
 * @param {int} data  0:说汉语 1:说英语
 * @return {*}
 */ 
void ui_voice_translation_show_layer(vt_layer_t layer, int data){
    lv_obj_add_flag(ui_voice_translation->ui_ctx.com_layer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_voice_translation->ui_ctx.chat_layer, LV_OBJ_FLAG_HIDDEN);
    ui_voice_translation->ui_ctx.layer = layer;
    switch(layer){
        case VT_LAYER_IDLE:
            lv_obj_clear_flag(ui_voice_translation->ui_ctx.com_layer, LV_OBJ_FLAG_HIDDEN);
            ui_voice_refresh_idle_layer();
            break;
        case VT_LAYER_LISTENING:
            lv_obj_clear_flag(ui_voice_translation->ui_ctx.com_layer, LV_OBJ_FLAG_HIDDEN);
            ui_voice_refresh_listening_layer(data);
            break;    
        case VT_LAYER_TRANSLATING:
            lv_obj_clear_flag(ui_voice_translation->ui_ctx.com_layer, LV_OBJ_FLAG_HIDDEN);
            ui_voice_refresh_translating_layer();
            break;
        case VT_LAYER_FAILED:
            lv_obj_clear_flag(ui_voice_translation->ui_ctx.com_layer, LV_OBJ_FLAG_HIDDEN);
            ui_voice_refresh_failed_layer();
            break; 
        case VT_LAYER_CHAT:
            lv_obj_clear_flag(ui_voice_translation->ui_ctx.chat_layer, LV_OBJ_FLAG_HIDDEN);
            break;           
    }
}


/***************************************************end***********************************************/

/*************************************************回调函数**********************************************/

static void ui_voice_translation_exit_clicked_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        // appVoiceTranslation_startActionState(APP_VOICE_TRANSLATION_ACTION_MENU, UI_VOICE_TRANSLATION_REFRESH_EXIT, NULL);
        printf("ui_voice_translation_exit_clicked_cb\n");
    }
}

static void ui_voice_catalog_clicked_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        // appVoiceTranslation_startActionState(APP_TRANSFER_BOOK_ACTION_MENU, UI_TRANSFER_BOOK_OPEN_CLOUD_SYNC, NULL);
        printf("ui_voice_catalog_clicked_cb\n");
    }
}


static void ui_voice_speaking_touch_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    int user_data = (int)lv_event_get_user_data(e);
    if(code == LV_EVENT_LONG_PRESSED){
        printf("ui_voice_speaking_press_cb");
        switch(user_data){
            case 0://汉语
                printf("ui_voice_speaking_press_cb 0\n");
                ui_voice_translation_show_layer(VT_LAYER_LISTENING,0);
                // appVoiceTranslation_startActionState(APP_VOICE_TRANSLATION_ACTION_MENU, UI_VOICE_TRANSLATION_REREESH_START_RECORDER, NULL);
                break;
            case 1://英语
                printf("ui_voice_speaking_press_cb 1\n");
                ui_voice_translation_show_layer(VT_LAYER_LISTENING,1);
                break;
        }
    }
    if(code == LV_EVENT_RELEASED){
        printf("ui_voice_speaking_release_cb\n");
        switch(user_data){
            case 0://汉语
                printf("ui_voice_speaking_release_cb 0\n");
                ui_voice_translation_show_layer(VT_LAYER_TRANSLATING,0);
                // appVoiceTranslation_startActionState(APP_VOICE_TRANSLATION_ACTION_MENU, UI_VOICE_TRANSLATION_REREESH_FINISH_RECORDER, NULL);
                break;
            case 1://英语
                printf("ui_voice_speaking_release_cb 1\n");
                ui_voice_translation_show_layer(VT_LAYER_TRANSLATING,1);
                break;    
        }
    }
}
/*************************************************end***********************************************/





void ui_voice_translation_init(void){
#if UI_VOICE_TRANSLATION_LVGL_SWITCH  //键盘驱动控制开关
    static lv_indev_drv_t indev_drv_keypad;
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = sdl_keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);
#endif    
    //申请内存
    ui_voice_translation_malloc();

    ui_voice_translation->ui_ctx.source_avatar = &icon_ai_talk_user_logo;
    ui_voice_translation->ui_ctx.translated_avatar = &icon_ai_talk_robot_logo;

    //创建主页面
    lv_coord_t width = lv_disp_get_hor_res(NULL);
    lv_coord_t height = lv_disp_get_ver_res(NULL);
    lv_coord_t top_height = 75;// (height >= 400) ? 75 : 50;
    lv_coord_t menu_item_h = 100;
    lv_coord_t menu_item_w = width - 20;

    //先获取默认焦点组
    ui_voice_translation->last_group = lv_group_get_default();
    //新建焦点组
    ui_voice_translation->voice_translation_group = lv_group_create();
    lv_group_set_default(ui_voice_translation->voice_translation_group); //设置新的焦点组为默认焦点组
    lv_indev_set_group(indev_keypad, lv_group_get_default());

    //创建一个霸屏容器
    ui_voice_translation->ui_voice_translation_container = ui_com_bg_cont_create(lv_scr_act());

    ui_voice_translation->ui_ctx.ui_top_con = ui_com_bg_cont_create(ui_voice_translation->ui_voice_translation_container);
    lv_obj_set_size( ui_voice_translation->ui_ctx.ui_top_con, width, top_height);
    lv_obj_align( ui_voice_translation->ui_ctx.ui_top_con, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_border_width( ui_voice_translation->ui_ctx.ui_top_con, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color( ui_voice_translation->ui_ctx.ui_top_con, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_side( ui_voice_translation->ui_ctx.ui_top_con, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);

    lv_obj_t *ui_exit = ui_com_bg_cont_create( ui_voice_translation->ui_ctx.ui_top_con);
	lv_obj_set_size(ui_exit, icon_com_exit.header.w + 40, top_height);
    lv_obj_align(ui_exit, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_exit, ui_voice_translation_exit_clicked_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align(ui_exit_img, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t *set_catalog = ui_com_bg_cont_create( ui_voice_translation->ui_ctx.ui_top_con);
    lv_obj_set_size(set_catalog, catalog.header.w + 40, top_height);
    lv_obj_align(set_catalog, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_flag(set_catalog, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_color(set_catalog, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(set_catalog, 1, LV_PART_MAIN);
    lv_obj_add_event_cb(set_catalog, ui_voice_catalog_clicked_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *set_catalog_img = lv_img_create(set_catalog);
    lv_img_set_src(set_catalog_img, &catalog);
    lv_obj_set_size(set_catalog_img, catalog.header.w, catalog.header.h);
    lv_obj_align(set_catalog_img, LV_ALIGN_CENTER, 0, 0);

    //创建标题
    lv_obj_t *ui_voice_title = lv_label_create( ui_voice_translation->ui_ctx.ui_top_con);
    lv_label_set_text(ui_voice_title, "语音翻译");
    lv_obj_set_style_text_letter_space(ui_voice_title,2, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_voice_title,&EX_Chinese_font_36,LV_STATE_DEFAULT);
    lv_obj_align_to(ui_voice_title, ui_exit, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_obj_add_flag(ui_voice_title, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_voice_title, ui_voice_translation_exit_clicked_cb, LV_EVENT_CLICKED, NULL);

    ui_voice_translation->ui_ctx.ui_voice_page = lv_label_create(ui_voice_translation->ui_ctx.ui_top_con);
    lv_label_set_text(ui_voice_translation->ui_ctx.ui_voice_page, "1/4");
    lv_obj_set_style_text_letter_space(ui_voice_translation->ui_ctx.ui_voice_page,2, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_voice_translation->ui_ctx.ui_voice_page,&EX_Chinese_font_36,LV_STATE_DEFAULT);
    lv_obj_align_to(ui_voice_translation->ui_ctx.ui_voice_page, ui_voice_title, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_add_flag(ui_voice_translation->ui_ctx.ui_voice_page, LV_OBJ_FLAG_CLICKABLE);

    //底部说话整体容器
    lv_obj_t *ui_speak_container = ui_com_bg_cont_create(ui_voice_translation->ui_voice_translation_container);
    lv_obj_set_size(ui_speak_container, width, 78);
    lv_obj_align(ui_speak_container, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(ui_speak_container, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_speak_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_side(ui_speak_container, LV_BORDER_SIDE_TOP, LV_PART_MAIN);

    //底部汉语说话容器
    lv_obj_t *ui_speak_Chinese_container = ui_com_bg_cont_create(ui_speak_container);
    lv_obj_set_size(ui_speak_Chinese_container, width / 2, 78);
    lv_obj_align(ui_speak_Chinese_container, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_border_width(ui_speak_Chinese_container, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_speak_Chinese_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_side(ui_speak_Chinese_container, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN);

    lv_obj_t *ui_speak_chinese_img = lv_img_create(ui_speak_Chinese_container);
    lv_img_set_src(ui_speak_chinese_img, &speaking);
    lv_obj_set_size(ui_speak_chinese_img, speaking.header.w, speaking.header.h);
    lv_obj_align(ui_speak_chinese_img, LV_ALIGN_LEFT_MID, 50, 0);

    lv_obj_t *ui_speak_chinese_label = lv_label_create(ui_speak_Chinese_container);
    lv_label_set_text(ui_speak_chinese_label, "说汉语");
    lv_obj_set_style_text_font(ui_speak_chinese_label,&EX_Chinese_font_36,LV_STATE_DEFAULT);
    lv_obj_align(ui_speak_chinese_label, LV_ALIGN_RIGHT_MID, -60, 0);

    //添加长按事件
    lv_obj_add_flag(ui_speak_Chinese_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_speak_Chinese_container, ui_voice_speaking_touch_cb, LV_EVENT_LONG_PRESSED, (void *)0);
    lv_obj_add_event_cb(ui_speak_Chinese_container, ui_voice_speaking_touch_cb, LV_EVENT_RELEASED, (void *)0);


    //底部英语说话容器
    lv_obj_t *ui_speak_English_container = ui_com_bg_cont_create(ui_speak_container);
    lv_obj_set_size(ui_speak_English_container, width / 2, 78);
    lv_obj_align(ui_speak_English_container, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_border_width(ui_speak_English_container, 3, LV_PART_MAIN);
    lv_obj_set_style_border_color(ui_speak_English_container, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_border_side(ui_speak_English_container, LV_BORDER_SIDE_LEFT, LV_PART_MAIN);

    lv_obj_t *ui_speak_english_img = lv_img_create(ui_speak_English_container);
    lv_img_set_src(ui_speak_english_img, &speaking);
    lv_obj_set_size(ui_speak_english_img, speaking.header.w, speaking.header.h);
    lv_obj_align(ui_speak_english_img, LV_ALIGN_LEFT_MID, 50, 0);

    lv_obj_t *ui_speak_english_label = lv_label_create(ui_speak_English_container);
    lv_label_set_text(ui_speak_english_label, "说英语");
    lv_obj_set_style_text_font(ui_speak_english_label,&EX_Chinese_font_36,LV_STATE_DEFAULT);
    lv_obj_align(ui_speak_english_label, LV_ALIGN_RIGHT_MID, -60, 0);


    //添加长按事件
    lv_obj_add_flag(ui_speak_English_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_speak_English_container, ui_voice_speaking_touch_cb, LV_EVENT_LONG_PRESSED, (void *)1);
    lv_obj_add_event_cb(ui_speak_English_container, ui_voice_speaking_touch_cb, LV_EVENT_RELEASED, (void *)1);

    //创建业务层
    ui_voice_create_com_layer();
    //创建聊天层
    ui_voice_create_char_layer();
    ui_voice_translation_show_layer(VT_LAYER_CHAT, 0);//初始化为空闲状态

    ui_voice_translation->ui_ctx.record_count = 6;

    for(int i = 0; i < ui_voice_translation->ui_ctx.record_count; i++){
        vt_chat_record_t *rec = &ui_voice_translation->ui_ctx.records[i];
        strncpy(rec->source, source_text[i], VT_TEXT_MAX_LEN - 1);
        strncpy(rec->translated, translation_text[i], VT_TEXT_MAX_LEN - 1);
        rec->source[VT_TEXT_MAX_LEN - 1] ='\0';
        rec->translated[VT_TEXT_MAX_LEN - 1] ='\0';
    }
    ui_voice_translation_build_pages();
    // ui_voice_translation->ui_ctx.cur_page = ui_voice_translation->ui_ctx.page_count - 1;
    ui_voice_translation->ui_ctx.cur_page = 2;
    ui_voice_translation_render_page();

}

void ui_voice_translation_deinit(void){
    if(ui_voice_translation != NULL){
        if(ui_voice_translation->voice_translation_group != NULL){
            lv_group_del(ui_voice_translation->voice_translation_group);
            ui_voice_translation->voice_translation_group = NULL;
        }
        if(ui_voice_translation->ui_voice_translation_container != NULL){
            lv_obj_del(ui_voice_translation->ui_voice_translation_container);
            ui_voice_translation->ui_voice_translation_container = NULL;
        }
        if(ui_voice_translation->last_group != NULL){
            lv_group_set_default(ui_voice_translation->last_group);
            lv_indev_set_group(indev_keypad, lv_group_get_default());
            ui_voice_translation->last_group = NULL;
        }
    }
    //释放内存
    ui_voice_translation_free();
}

