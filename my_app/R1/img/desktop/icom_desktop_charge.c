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

#ifndef LV_ATTRIBUTE_IMG_ICOM_DESKTOP_CHARGE
#define LV_ATTRIBUTE_IMG_ICOM_DESKTOP_CHARGE
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_ICOM_DESKTOP_CHARGE uint8_t icom_desktop_charge_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
  0x08, 0x00, 
  0x08, 0x00, 
  0x18, 0x00, 
  0x18, 0x00, 
  0x38, 0x00, 
  0x3f, 0x00, 
  0x3f, 0x00, 
  0x3e, 0x00, 
  0x0e, 0x00, 
  0x0c, 0x00, 
  0x0c, 0x00, 
  0x08, 0x00, 
  0x08, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
};

const lv_img_dsc_t icom_desktop_charge = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 9,
  .header.h = 19,
  .data_size = 46,
  .data = icom_desktop_charge_map,
};
