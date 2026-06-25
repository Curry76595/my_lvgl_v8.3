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

#ifndef LV_ATTRIBUTE_IMG_ICON_COM_KEYBOARD_UPPER
#define LV_ATTRIBUTE_IMG_ICON_COM_KEYBOARD_UPPER
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ICON_COM_KEYBOARD_UPPER uint8_t icon_com_keyboard_upper_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x80, 0x00, 
  0x01, 0x40, 0x00, 
  0x02, 0x20, 0x00, 
  0x04, 0x10, 0x00, 
  0x08, 0x08, 0x00, 
  0x10, 0x04, 0x00, 
  0x20, 0x02, 0x00, 
  0x40, 0x01, 0x00, 
  0xf0, 0x07, 0x80, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x10, 0x04, 0x00, 
  0x1f, 0xfc, 0x00, 
};

const lv_img_dsc_t icon_com_keyboard_upper = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 17,
  .header.h = 19,
  .data_size = 65,
  .data = icon_com_keyboard_upper_map,
};
