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

#ifndef LV_ATTRIBUTE_IMG_PIC_MODULE_BLE_STATUS
#define LV_ATTRIBUTE_IMG_PIC_MODULE_BLE_STATUS
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_PIC_MODULE_BLE_STATUS uint8_t pic_module_ble_status_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 
  0x06, 0x00, 
  0x07, 0x00, 
  0x07, 0x80, 
  0x06, 0xc0, 
  0x66, 0x60, 
  0x36, 0xc0, 
  0x1f, 0x80, 
  0x0f, 0x00, 
  0x0f, 0x00, 
  0x1f, 0x80, 
  0x36, 0xc0, 
  0x66, 0x60, 
  0x06, 0xc0, 
  0x07, 0x80, 
  0x07, 0x00, 
  0x06, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
};

const lv_img_dsc_t pic_module_ble_status = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 12,
  .header.h = 19,
  .data_size = 46,
  .data = pic_module_ble_status_map,
};
