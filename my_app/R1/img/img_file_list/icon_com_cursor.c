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

#ifndef LV_ATTRIBUTE_IMG_ICON_COM_CURSOR
#define LV_ATTRIBUTE_IMG_ICON_COM_CURSOR
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ICON_COM_CURSOR uint8_t icon_com_cursor_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x80, 0x00, 
  0xc0, 0x00, 
  0xf0, 0x00, 
  0xf8, 0x00, 
  0xfe, 0x00, 
  0xff, 0x00, 
  0xff, 0xc0, 
  0xff, 0x00, 
  0xfe, 0x00, 
  0xf8, 0x00, 
  0xf0, 0x00, 
  0xc0, 0x00, 
  0x80, 0x00, 
};

const lv_img_dsc_t icon_com_cursor = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 10,
  .header.h = 13,
  .data_size = 34,
  .data = icon_com_cursor_map,
};
