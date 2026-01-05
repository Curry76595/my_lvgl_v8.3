//
// Created by Administrator on 2024/12/28/028.
//
#if 1
#ifndef BCZ02_LOG_WRAPPER_H
#define BCZ02_LOG_WRAPPER_H
#define  ENABLE_LVGL_LOG 0
// 封装的日志宏

#if  ENABLE_LVGL_LOG
#define LOG_DEBUG_WRAPPER(format, ...) \
    LV_LOG_USER(format, ##__VA_ARGS__)

#define LOG_INFO_WRAPPER(format, ...) \
        LV_LOG_USER(format, ##__VA_ARGS__)

#define LOG_ERROR_WRAPPER(format, ...) \
        LV_LOG_ERROR(format, ##__VA_ARGS__)
#else
#define LOG_DEBUG_WRAPPER(format, ...) \
    log_debug("[%d:%s] " format, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_INFO_WRAPPER(format, ...) \
    log_info("[%d:%s] " format, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_ERROR_WRAPPER(format, ...) \
    log_error("[%d:%s] " format, __LINE__, __func__, ##__VA_ARGS__)
#endif

#endif //BCZ02_LOG_WRAPPER_H
#endif
