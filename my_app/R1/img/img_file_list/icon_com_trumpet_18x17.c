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

#ifndef LV_ATTRIBUTE_IMG_ICON_COM_TRUMPET_18X17
#define LV_ATTRIBUTE_IMG_ICON_COM_TRUMPET_18X17
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ICON_COM_TRUMPET_18X17 uint8_t icon_com_trumpet_18x17_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x40, 0x00, 
  0x00, 0xc2, 0x00, 
  0x01, 0x41, 0x00, 
  0x02, 0x40, 0x80, 
  0x04, 0x48, 0x80, 
  0x78, 0x44, 0x40, 
  0x40, 0x44, 0x40, 
  0x40, 0x44, 0x40, 
  0x40, 0x44, 0x40, 
  0x40, 0x44, 0x40, 
  0x40, 0x44, 0x40, 
  0x78, 0x44, 0x40, 
  0x04, 0x48, 0x80, 
  0x02, 0x40, 0x80, 
  0x01, 0x41, 0x00, 
  0x00, 0xc2, 0x00, 
  0x00, 0x40, 0x00, 
};

const lv_img_dsc_t icon_com_trumpet_18x17 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 18,
  .header.h = 17,
  .data_size = 59,
  .data = icon_com_trumpet_18x17_map,
};
