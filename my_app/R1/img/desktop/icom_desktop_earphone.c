#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_ICOM_DESKTOP_EARPHONE
#define LV_ATTRIBUTE_IMG_ICOM_DESKTOP_EARPHONE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ICOM_DESKTOP_EARPHONE uint8_t icom_desktop_earphone_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
  0x01, 0xf0, 0x00, 
  0x07, 0xfc, 0x00, 
  0x0e, 0x0e, 0x00, 
  0x1c, 0x07, 0x00, 
  0x10, 0x01, 0x00, 
  0x20, 0x00, 0x80, 
  0x20, 0x00, 0x80, 
  0x20, 0x00, 0x80, 
  0xe0, 0x00, 0xe0, 
  0xe0, 0x00, 0xe0, 
  0xe0, 0x00, 0xe0, 
  0xe0, 0x00, 0xe0, 
  0xe0, 0x00, 0xe0, 
  0xe0, 0x00, 0xe0, 
  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 
};

const lv_img_dsc_t icom_desktop_earphone = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 19,
  .header.h = 19,
  .data_size = 65,
  .data = icom_desktop_earphone_map,
};
