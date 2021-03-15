#include "lvgl/lvgl.h"

lv_style_t style;
lv_obj_t* scr;


lv_obj_t* label_index;
lv_obj_t* label_name;
lv_obj_t* label_number;
lv_obj_t* label_sort;

lv_obj_t* kitchen_img;
lv_obj_t* other_img;
lv_obj_t* recycle_img;
lv_obj_t* danger_img;

lv_obj_t* debug_status;

LV_FONT_DECLARE(stkaiti);
LV_IMG_DECLARE(wallpaper);
LV_IMG_DECLARE(realtime);
LV_IMG_DECLARE(danger);
LV_IMG_DECLARE(kitchen);
LV_IMG_DECLARE(recycle);
LV_IMG_DECLARE(other);
LV_IMG_DECLARE(imgfull);


void lichee();
