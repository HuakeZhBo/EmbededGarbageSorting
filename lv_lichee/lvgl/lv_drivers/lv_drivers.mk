CSRCS += fbdev.c


DEPPATH += --dep-path $(LVGL_DIR)/lv_drivers
VPATH += :$(LVGL_DIR)/lv_drivers

CFLAGS += "-I$(LVGL_DIR)/lv_drivers"

