#include "ui_cloud_sync.h"

/*************************************************声明变量************************************************/
#define PAGE_DISPAY_TASK_NUM 3
int cloud_current_page = 1;
int cloud_total_page = 2;
ui_cloud_sync_t *ui_cloud_sync_list;
lv_obj_t *ui_cloud_title_page;//云任务显示页数
lv_obj_t *content_display_container;//内容显示容器
lv_obj_t *ui_connect_status_cue_label;//云同步状态提示语
char cloud_page_txBuf[32] = {0};//云任务页数显示内容

char task_space_buf[32] = {0};



//每个任务 = 数据 + ui
typedef struct{
    cloud_task_data_t data;//任务数据结构
    ui_cloud_task_t ui;//任务UI控件
}cloud_task_item_t;

static const char *g_status_text[] = {
    "等待中",
    "下载中",
    "已完成"
};

static cloud_task_item_t *g_tasks = NULL;//任务列表
int g_task_count = 4;//实际任务数，运行时赋值

/************************************************内存申请释放*************************************************/
//申请内存
static void ui_cloud_sync_malloc(void){
    if(ui_cloud_sync_list == NULL){
        ui_cloud_sync_list = (ui_cloud_sync_t *)malloc(sizeof(ui_cloud_sync_t));
        if(ui_cloud_sync_list == NULL) return;
        memset(ui_cloud_sync_list, 0, sizeof(ui_cloud_sync_t));
    }
}



//释放内存
static void ui_cloud_sync_free(void){
    if(ui_cloud_sync_list != NULL){
        free(ui_cloud_sync_list);
        ui_cloud_sync_list = NULL;
    }
}

//按任务数分配内存
static int cloud_task_calloc(int count){
    if(count <=0) return -1;
    //先释放旧内存（支持重复进入页面）
    if(g_tasks != NULL){
        free(g_tasks);
        g_tasks = NULL;
    }

    g_tasks = (cloud_task_item_t *)calloc((size_t)count, sizeof(cloud_task_item_t));

    if(g_tasks == NULL){
        g_task_count = 0;
        return -1;
    }

    g_task_count = count;
    return 0;

}

//释放任务内存
static void cloud_task_free(void){

    if(g_tasks != NULL){
        free(g_tasks);
        g_tasks = NULL;
    }
    g_task_count = 0;
    cloud_current_page = 1;
    cloud_total_page = 1;
}



/**************************************************UI细节函数***********************************************/

static void cloud_task_reset(cloud_task_data_t *task){
    if(task == NULL) return;

    memset(task, 0, sizeof(cloud_task_data_t));

    task->status = TASK_STATUS_WAITING;
    task->type = TASK_TYPE_UNKNOWN;
}

static void ui_cloud_refresh_page(void){
    if (g_tasks == NULL) return;
    snprintf(cloud_page_txBuf, sizeof(cloud_page_txBuf), "%d/%d", cloud_current_page, cloud_total_page);
    lv_label_set_text(ui_cloud_title_page, cloud_page_txBuf);
    for(int i= 0; i< g_task_count; i++){
        lv_obj_add_flag(g_tasks[i].ui.card, LV_OBJ_FLAG_HIDDEN);
    }
    int start_index = cloud_current_page * 3 - 3;
    int end_index = cloud_current_page * 3;
    if(end_index > g_task_count) end_index = g_task_count;
    for(int i = start_index; i < end_index; i++){
        lv_obj_clear_flag(g_tasks[i].ui.card, LV_OBJ_FLAG_HIDDEN);                                       //显示任务卡片
        lv_label_set_text(g_tasks[i].ui.task_name, g_tasks[i].data.task_name);                        //1.任务名称
        lv_bar_set_value(g_tasks[i].ui.progress_bar, g_tasks[i].data.progress, LV_ANIM_OFF);   //2.1 进度条值
        lv_label_set_text_fmt(g_tasks[i].ui.progress_value, "%d%%",g_tasks[i].data.progress);          //2.2 进度值
        lv_label_set_text(g_tasks[i].ui.progress_status, g_status_text[g_tasks[i].data.status]);      //3.占用大小
        snprintf(task_space_buf, sizeof(task_space_buf), "%.3f MB", g_tasks[i].data.task_space);
        lv_label_set_text(g_tasks[i].ui.task_space, task_space_buf);                                  //4.任务占用大小
        if(g_tasks[i].data.type == TASK_TYPE_IMAGE) lv_img_set_src(g_tasks[i].ui.img, &JPG);           //5.显示类型
        else lv_img_set_src(g_tasks[i].ui.img, &txt);
    }
}

static void cloud_tasks_set_demo_data(void)
{
    if (g_tasks == NULL) return;
    snprintf(g_tasks[0].data.task_name, sizeof(g_tasks[0].data.task_name), "任务1");//1. 任务名称
    g_tasks[0].data.progress = 36;                                                  //2. 进度值
    g_tasks[0].data.task_space = 4.2;                                               //3. 任务占用大小
    g_tasks[0].data.status = TASK_STATUS_DOWNLOADING;                               //4. 任务状态
    g_tasks[0].data.type = TASK_TYPE_IMAGE;                                         //5. 任务类型

    snprintf(g_tasks[1].data.task_name, sizeof(g_tasks[1].data.task_name), "任务2");
    g_tasks[1].data.progress = 36;
    g_tasks[1].data.task_space = 1.2;
    g_tasks[1].data.status = TASK_STATUS_WAITING;
    g_tasks[1].data.type = TASK_TYPE_IMAGE;

    snprintf(g_tasks[2].data.task_name, sizeof(g_tasks[2].data.task_name), "任务3");
    g_tasks[2].data.progress = 66;
    g_tasks[2].data.task_space = 6.2;
    g_tasks[2].data.status = TASK_STATUS_WAITING;
    g_tasks[2].data.type = TASK_TYPE_IMAGE;

    snprintf(g_tasks[3].data.task_name, sizeof(g_tasks[3].data.task_name), "任务4");
    g_tasks[3].data.progress = 80;
    g_tasks[3].data.task_space = 3.2;
    g_tasks[3].data.status = TASK_STATUS_DOWNLOADING;
    g_tasks[3].data.type = TASK_TYPE_IMAGE;

    snprintf(g_tasks[4].data.task_name, sizeof(g_tasks[4].data.task_name), "任务5");
    g_tasks[4].data.progress = 60;
    g_tasks[4].data.task_space = 11.2;
    g_tasks[4].data.status = TASK_STATUS_WAITING;
    g_tasks[4].data.type = TASK_TYPE_IMAGE;

}

void ui_creat_cloud_task_card(void){
    lv_obj_clear_flag(ui_cloud_title_page, LV_OBJ_FLAG_HIDDEN);//显示页数
    cloud_current_page = 1;//设置当前页数为1
    int ret = cloud_task_calloc(g_task_count);//给任务卡片申请内存
    printf("<%s> ret:%d\n", __func__, ret);
    //计算总页数
    if(g_task_count % PAGE_DISPAY_TASK_NUM == 0) {
        cloud_total_page = g_task_count / PAGE_DISPAY_TASK_NUM;
    }else{
        cloud_total_page = g_task_count / PAGE_DISPAY_TASK_NUM + 1;
    }
    if(cloud_total_page == 0) cloud_total_page = 1;
    for(int i = 0; i < g_task_count; i++){
        cloud_task_item_t *task = &g_tasks[i];
        cloud_task_reset(&g_tasks[i].data);//任务数据参数初始化
        task->ui.card = lv_obj_create(content_display_container);
        lv_obj_add_flag(task->ui.card, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(task->ui.card, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(task->ui.card, 225, 88);
        lv_obj_set_style_radius(task->ui.card, 6, LV_PART_MAIN);
        lv_obj_set_style_border_color(task->ui.card, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_border_width(task->ui.card, 1, LV_PART_MAIN);

        //图片容器
        task->ui.img_container = lv_obj_create(task->ui.card );
        lv_obj_clear_flag(task->ui.img_container, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(task->ui.img_container, 30, 30);
        lv_obj_align(task->ui.img_container, LV_ALIGN_TOP_LEFT, -10,0 );
        lv_obj_set_style_border_color(task->ui.img_container, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(task->ui.img_container, 1, LV_PART_MAIN); 

        //图片
        task->ui.img = lv_img_create(task->ui.img_container);
        lv_img_set_src(task->ui.img, &txt);
        lv_obj_set_size(task->ui.img, txt.header.w, txt.header.h);
        lv_obj_align(task->ui.img, LV_ALIGN_CENTER, 0, 0);

        //进度框整体容器
        task->ui.progress_container = lv_obj_create(task->ui.card);
        lv_obj_clear_flag(task->ui.progress_container, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(task->ui.progress_container, 185, 50);
        lv_obj_align(task->ui.progress_container, LV_ALIGN_TOP_RIGHT, 10,-10 );
        lv_obj_set_style_border_color(task->ui.progress_container, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(task->ui.progress_container, 1, LV_PART_MAIN); 

        //进度文本容器
        task->ui.progress_content_container = lv_obj_create(task->ui.progress_container);
        lv_obj_clear_flag(task->ui.progress_content_container, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_size(task->ui.progress_content_container, 180, 32);
        lv_obj_align(task->ui.progress_content_container, LV_ALIGN_CENTER, 0,-8 );
        lv_obj_set_style_border_color(task->ui.progress_content_container, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_border_width(task->ui.progress_content_container, 1, LV_PART_MAIN);  

        //1.进度值
        task->ui.progress_value = lv_label_create(task->ui.progress_content_container);
        lv_label_set_text_fmt(task->ui.progress_value, "%d%%",task->data.progress);
        lv_obj_set_style_text_font(task->ui.progress_value,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(task->ui.progress_value,1, LV_PART_MAIN);
        lv_obj_align(task->ui.progress_value, LV_ALIGN_LEFT_MID, -5, 0);

        //2.进度状态
        task->ui.progress_status = lv_label_create(task->ui.progress_content_container);
        lv_label_set_text(task->ui.progress_status, g_status_text[task->data.status]);
        lv_obj_set_style_text_font(task->ui.progress_status,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(task->ui.progress_status,0, LV_PART_MAIN);
        lv_obj_align(task->ui.progress_status, LV_ALIGN_CENTER, -15, 0);

        //3.任务占用大小
        task->ui.task_space = lv_label_create(task->ui.progress_content_container);
        snprintf(task_space_buf, sizeof(task_space_buf), "%.3f MB", task->data.task_space);
        lv_label_set_text(task->ui.task_space, task_space_buf);
        lv_obj_set_style_text_font(task->ui.task_space,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(task->ui.task_space,-1, LV_PART_MAIN);
        lv_obj_align(task->ui.task_space, LV_ALIGN_RIGHT_MID, 10, 0);

        //进度条
        task->ui.progress_bar = lv_bar_create(task->ui.progress_container);
        lv_obj_set_size(task->ui.progress_bar, 170, 7);
        lv_obj_align(task->ui.progress_bar, LV_ALIGN_CENTER, 0, 12);
        lv_bar_set_range(task->ui.progress_bar, 0, 100);
        lv_bar_set_value(task->ui.progress_bar, task->data.progress, LV_ANIM_OFF); 

        lv_obj_set_style_bg_color(task->ui.progress_bar, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(task->ui.progress_bar, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_color(task->ui.progress_bar, lv_color_black(), LV_PART_INDICATOR);
        lv_obj_set_style_bg_opa(task->ui.progress_bar, LV_OPA_COVER, LV_PART_INDICATOR);
        lv_obj_set_style_border_width(task->ui.progress_bar, 1, LV_PART_MAIN);
        lv_obj_set_style_border_color(task->ui.progress_bar, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_radius(task->ui.progress_bar, 2, LV_PART_MAIN);

        //任务名称
        task->ui.task_name = lv_label_create(task->ui.card );
        lv_label_set_text(task->ui.task_name , task->data.task_name);
        lv_obj_set_style_text_font(task->ui.task_name ,&Chinese_font_16,LV_STATE_DEFAULT);
        lv_obj_set_style_text_letter_space(task->ui.task_name ,1, LV_PART_MAIN);
        lv_obj_align(task->ui.task_name , LV_ALIGN_BOTTOM_LEFT, 0, 3);
    }
    ui_cloud_refresh_page();//刷新界面

}

void ui_cloud_refresh_interface_display(void){
    
}
/*************************************************回调函数*******************************************/
static void ui_cloud_sync_key_event_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_KEY){
        uint32_t key = lv_event_get_key(e);
        switch(key){
            case LV_KEY_ESC:
                printf("<%s> LV_KEY_ESC\n",__func__);
                ui_cloud_sync_deinit();
                break;
            case LV_KEY_LEFT:
                printf("<%s> LV_KEY_LEFT\n",__func__);
                cloud_current_page--;
                if(cloud_current_page < 1) cloud_current_page = cloud_total_page;
                ui_cloud_refresh_page();
                break;
            case LV_KEY_RIGHT:
                printf("<%s> LV_KEY_RIGHT\n",__func__);
                cloud_current_page++;
                if(cloud_current_page > cloud_total_page) cloud_current_page = 1;
                ui_cloud_refresh_page();
                break;
            default:
                break;
        }
    }
}

void ui_cloud_sync_init(void){

    //申请内存
    ui_cloud_sync_malloc();

    //先获取默认焦点组
    ui_cloud_sync_list->last_group = lv_group_get_default();
    //新建焦点组
    ui_cloud_sync_list->cloud_group = lv_group_create();
    lv_group_set_default(ui_cloud_sync_list->cloud_group); //设置新的焦点组为默认焦点组
    lv_indev_set_group(indev_keypad, lv_group_get_default());

    //创建一个霸屏容器
    ui_cloud_sync_list->ui_cloud_container = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui_cloud_sync_list->ui_cloud_container, 240, 360);
    lv_obj_clear_flag(ui_cloud_sync_list->ui_cloud_container, LV_OBJ_FLAG_SCROLLABLE);

    //退出图片
    lv_obj_t *ui_exit = lv_obj_create(ui_cloud_sync_list->ui_cloud_container);
    lv_obj_set_size(ui_exit, 40, 20);
    lv_obj_align_to(ui_exit, ui_cloud_sync_list->ui_cloud_container, LV_ALIGN_TOP_LEFT, -6, -8);
    lv_obj_clear_flag(ui_exit, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(ui_exit, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_border_width(ui_exit, 0, 0);
    lv_obj_set_style_radius(ui_exit, 0, 0);
    lv_obj_set_style_pad_all(ui_exit, 0, 0);
    lv_obj_t *ui_exit_img = lv_img_create(ui_exit);
    lv_img_set_src(ui_exit_img, &icon_com_exit);
    lv_obj_set_size(ui_exit_img, icon_com_exit.header.w, icon_com_exit.header.h);
    lv_obj_align_to(ui_exit_img, ui_exit, LV_ALIGN_TOP_LEFT, 0, 0);

    //创建标题
    lv_obj_t *ui_clound_title = lv_label_create(ui_cloud_sync_list->ui_cloud_container);
    lv_label_set_text(ui_clound_title, "云同步下载列表");
    lv_obj_set_style_text_letter_space(ui_clound_title,2, LV_PART_MAIN);
    lv_obj_set_style_text_font(ui_clound_title,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_align(ui_clound_title, LV_ALIGN_TOP_LEFT, 10, -8);

    //创建页数
    snprintf(cloud_page_txBuf, sizeof(cloud_page_txBuf), "%d/%d", cloud_current_page, cloud_total_page);
    ui_cloud_title_page = lv_label_create(ui_cloud_sync_list->ui_cloud_container);
    lv_label_set_text(ui_cloud_title_page, cloud_page_txBuf);
    lv_obj_set_style_text_font(ui_cloud_title_page,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_cloud_title_page,2, LV_PART_MAIN);
    lv_obj_align(ui_cloud_title_page, LV_ALIGN_TOP_RIGHT, 0, -8);
    lv_obj_add_flag(ui_cloud_title_page, LV_OBJ_FLAG_HIDDEN);//默认隐藏页数

    //创建分割横线
    lv_obj_t *ui_title_line = lv_line_create(ui_cloud_sync_list->ui_cloud_container);
    static lv_point_t title_line_points[] ={{0,20},{240,20}};
    lv_line_set_points(ui_title_line,title_line_points,2);
    lv_obj_set_style_line_width(ui_title_line, 1, LV_PART_MAIN);
    lv_obj_set_pos(ui_title_line,-15,0);

    //创建内容显示容器
    content_display_container = lv_obj_create(ui_cloud_sync_list->ui_cloud_container);
    lv_obj_set_size(content_display_container, 235, 320);
    lv_obj_add_flag(content_display_container, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(content_display_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(content_display_container, LV_ALIGN_TOP_MID, 0, 23);
    lv_obj_set_style_border_color(content_display_container, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(content_display_container, 1, LV_PART_MAIN);
    lv_group_add_obj(ui_cloud_sync_list->cloud_group , content_display_container);
    lv_obj_add_event_cb(content_display_container,ui_cloud_sync_key_event_cb,LV_EVENT_KEY,NULL);

    // 设置容器的弹性布局
    lv_obj_set_flex_flow(content_display_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(content_display_container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    ui_connect_status_cue_label = lv_label_create(content_display_container);
    lv_obj_set_width(ui_connect_status_cue_label, 150);
    lv_obj_align(ui_connect_status_cue_label, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_text_font(ui_connect_status_cue_label,&Chinese_font_16,LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_connect_status_cue_label,2, LV_PART_MAIN);
    lv_obj_set_style_text_line_space(ui_connect_status_cue_label,10, LV_PART_MAIN);
    lv_label_set_text(ui_connect_status_cue_label, "正在获取云同步\n下载列表");
    lv_obj_set_style_text_align(ui_connect_status_cue_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    // lv_obj_add_flag(ui_connect_status_cue_label, LV_OBJ_FLAG_HIDDEN);
 
}


void ui_cloud_sync_deinit(void){
    if(ui_cloud_sync_list != NULL){
        if(ui_cloud_sync_list->cloud_group != NULL){
            lv_group_del(ui_cloud_sync_list->cloud_group);
            ui_cloud_sync_list->cloud_group = NULL;
        }
        if(ui_cloud_sync_list->ui_cloud_container != NULL){
            lv_obj_del(ui_cloud_sync_list->ui_cloud_container);
            ui_cloud_sync_list->ui_cloud_container = NULL;
        }
        if(ui_cloud_sync_list->last_group != NULL){
            lv_group_set_default(ui_cloud_sync_list->last_group);
            lv_indev_set_group(indev_keypad, lv_group_get_default());
            ui_cloud_sync_list->last_group = NULL;
        }
    }
    cloud_task_free();//释放内存
    ui_cloud_sync_free();//释放内存
}

