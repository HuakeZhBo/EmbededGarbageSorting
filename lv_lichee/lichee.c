#include <lichee.h>

void lichee(){

	scr = lv_scr_act();

	// background image
	lv_obj_t* bg_img = lv_img_create(scr, NULL);
	lv_img_set_src(bg_img, &wallpaper);
	lv_img_set_auto_size(bg_img,true);
	lv_obj_align(bg_img, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_obj_set_style_local_image_opa(bg_img,LV_IMG_PART_MAIN,LV_STATE_DEFAULT,LV_OPA_60);

	// title
	lv_style_init(&style);
	lv_style_set_text_font(&style,LV_STATE_DEFAULT,&stkaiti);
	lv_obj_t * title = lv_label_create(scr, NULL);
	lv_style_list_t * list = lv_obj_get_style_list(title, LV_LABEL_PART_MAIN);
	_lv_style_list_add_style(list, &style);
	lv_obj_refresh_style(title, LV_STYLE_PROP_ALL);
	lv_obj_align(title,NULL,LV_ALIGN_IN_TOP_MID,-108,12);
	lv_label_set_text(title, " 生活垃圾智能分类 ");
	lv_label_set_align(title,LV_LABEL_ALIGN_CENTER);
	lv_obj_set_style_local_bg_opa(title,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_OPA_40);
	lv_obj_set_style_local_bg_color(title,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_BLUE);
	lv_obj_set_style_local_radius(title,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,90);

	// realtime image
	lv_obj_t* realtime_img = lv_img_create(scr,NULL);
	lv_img_set_src(realtime_img,&realtime);
	lv_obj_set_pos(realtime_img,100,70);

	// head label
	lv_obj_t* label_head = lv_label_create(scr,title);
	lv_obj_align(label_head,realtime_img,LV_ALIGN_OUT_RIGHT_TOP,60,0);
	lv_label_set_text(label_head," 序号: \n\n 分类: \n\n 数量: \n\n 状态: ");
	lv_obj_set_style_local_radius(label_head,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,30);
	lv_obj_set_style_local_bg_color(label_head,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,LV_COLOR_LIME);

	// index label
	label_index = lv_label_create(scr,label_head);
	lv_label_set_long_mode(label_index,LV_LABEL_LONG_BREAK);
	lv_obj_set_width(label_index,180);
	lv_obj_align(label_index,label_head,LV_ALIGN_OUT_RIGHT_TOP,6,0);
	lv_label_set_text(label_index,"0");

	// name label
	// label_name = lv_label_create(scr,label_index);
	// lv_obj_align(label_name,label_head,LV_ALIGN_OUT_RIGHT_TOP,6,70);
	// lv_label_set_text(label_name,"###");

	// sort laber
	label_sort = lv_label_create(scr,label_index);
	lv_obj_align(label_sort,label_head,LV_ALIGN_OUT_RIGHT_TOP,6,70);
	lv_label_set_text(label_sort,"###");

	// number label
	label_number = lv_label_create(scr,label_index);
	lv_obj_align(label_number,label_head,LV_ALIGN_OUT_RIGHT_TOP,6,140);
	lv_label_set_text(label_number,"0");

	// status label
	debug_status = lv_label_create(scr,label_head);
	lv_obj_align(debug_status,label_head,LV_ALIGN_OUT_RIGHT_TOP,6,210);
	lv_label_set_long_mode(debug_status,LV_LABEL_LONG_EXPAND);
	lv_label_set_text(debug_status,"lvgl ok!");

	// bin picture
	kitchen_img = lv_img_create(scr,NULL);
	lv_img_set_src(kitchen_img,&kitchen);
	lv_obj_align(kitchen_img,scr,LV_ALIGN_IN_BOTTOM_LEFT,50,-25);
	
	danger_img = lv_img_create(scr,NULL);
	lv_img_set_src(danger_img,&danger);
	lv_obj_align(danger_img,scr,LV_ALIGN_IN_BOTTOM_LEFT,250,-25);

	recycle_img = lv_img_create(scr,NULL);
	lv_img_set_src(recycle_img,&recycle);
	lv_obj_align(recycle_img,scr,LV_ALIGN_IN_BOTTOM_LEFT,450,-25);

	other_img = lv_img_create(scr,NULL);
	lv_img_set_src(other_img,&other);
	lv_obj_align(other_img,scr,LV_ALIGN_IN_BOTTOM_LEFT,650,-25);


	lv_refr_now(NULL);

	// lv_task_create(bgk_anim, 5000, LV_TASK_PRIO_LOW, NULL);//创建任务 500ms一次

}
