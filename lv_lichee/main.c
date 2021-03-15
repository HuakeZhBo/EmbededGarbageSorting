#include "lvgl/lvgl.h"
#include "lvgl/lv_drivers/fbdev.h"

#include <unistd.h>
#include <lichee.h>
#include <uart.h>

// display buffer size - not sure if this size is really needed
#define LV_BUF_SIZE 384000		// 800x480
// A static variable to store the display buffers
static lv_disp_buf_t disp_buf;
// Static buffer(s). The second buffer is optional
static lv_color_t lvbuf1[LV_BUF_SIZE];
static lv_color_t lvbuf2[LV_BUF_SIZE];
int count = 0;
int index1 = 0;
bool throw_finished = true;

char cata[11][30] = {
	"烟头","蔬菜","电池","蔬菜","碎砖","蔬菜","蔬菜","矿泉水瓶","碎砖","陶瓷","易拉罐"
};

char sort[4][16] = {
	"厨余垃圾","有害垃圾","可回收垃圾","其他垃圾"
};

char index_char[30][3] = {
	"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16",
	"17","18","19","20","21","22","23","24","25","26","27","28","29"
};

int main(void){


	uart1 = "/dev/ttyS1";
	uart2 = "/dev/ttyS2";
	memset(bufferk,0,16);
	memset(buffera,0,16);
	char servo[3];
	servo[1] = 0x0d;
	servo[2] = 0x0a;

	// LittlevGL init
	lv_init();

	//Linux frame buffer device init
	fbdev_init();

	// Initialize `disp_buf` with the display buffer(s)
	lv_disp_buf_init(&disp_buf, lvbuf1, lvbuf2, LV_BUF_SIZE);

	// Initialize and register a display driver
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.flush_cb = fbdev_flush;	// flushes the internal graphical buffer to the frame bufferls
	disp_drv.buffer = &disp_buf;		// set teh display buffere reference in the driver
	lv_disp_drv_register(&disp_drv);

	lichee();
	sleep(1);

	//打开串口1--k210
	while((fd1 = open(uart1, O_RDWR|O_NONBLOCK))<0);//非阻塞读方式
	set_opt(fd1, 115200, 8, 'N', 1);
	lv_label_set_text(debug_status,"识别打开成功");
	lv_refr_now(NULL);
	sleep(1);

	//打开串口2--Arduino
	while((fd2 = open(uart2, O_RDWR|O_NONBLOCK))<0);//非阻塞读方式
	set_opt(fd2, 115200, 8, 'N', 1);
	lv_label_set_text(debug_status,"舵机打开成功");
	lv_refr_now(NULL);
	sleep(1);

	// Handle LitlevGL tasks (tickless mode)
	while(1) {

                if(count == 0){
			lv_label_set_text(label_index,index_char[index1++]);
                        lv_label_set_text(debug_status,"请放入垃圾");
                        lv_refr_now(NULL);
                }
                else if(count == 6){
			write(fd1,"55\r\n",4);
			lv_label_set_text(debug_status,"识别中");
			lv_refr_now(NULL);
		}
		else if (count == 10)
		{
			while(read(fd1,bufferk,16)<0);
			switch (bufferk[0])
			{
			case '0':
				servo[0] = '4';
				lv_label_set_text(label_sort,sort[3]);
				break;
			case '1':
				servo[0] = '1';
				lv_label_set_text(label_sort,sort[0]);
				break;
			case '2':
				servo[0] = '2';
				lv_label_set_text(label_sort,sort[1]);
				break;
			case '3':
				servo[0] = '1';
				lv_label_set_text(label_sort,sort[0]);
				break;
			case '4':
				servo[0] = '4';
				lv_label_set_text(label_sort,sort[3]);
				break;
			case '5':
				servo[0] = '1';
				lv_label_set_text(label_sort,sort[0]);
				break;
			case '6':
				servo[0] = '1';
				lv_label_set_text(label_sort,sort[0]);
				break;
			case '7':
				servo[0] = '3';
				lv_label_set_text(label_sort,sort[2]);
				break;
			case '8':
				servo[0] = '4';
				lv_label_set_text(label_sort,sort[3]);
				break;
			case '9':
				servo[0] = '4';
				lv_label_set_text(label_sort,sort[3]);
				break;
			case 'a':
				servo[0] = '3';
				lv_label_set_text(label_sort,sort[2]);
				break;
			case 'z':
				return 0;
			default:
				break;
			}
			//lv_label_set_text(label_name,cata[(buffer[0]-0x30)]);
			lv_label_set_text(label_number,"1");
			lv_label_set_text(debug_status,"分类成功");
			write(fd2,servo,3);

			for(int m=0;m<10;m++)
				read(fd1,bufferk,16);
			memset(bufferk, 0, 16);
			lv_refr_now(NULL);
		}
		
		read(fd2,buffera,16);
		if((buffera[0]&0x01) == 0x01)
			lv_img_set_src(kitchen_img,&imgfull);
		else
			lv_img_set_src(kitchen_img,&kitchen);
		if((buffera[0]&0x02) == 0x02)
			lv_img_set_src(danger_img,&imgfull);
		else
			lv_img_set_src(danger_img,&danger);
		if((buffera[0]&0x04) == 0x04)
			lv_img_set_src(recycle_img,&imgfull);
		else
			lv_img_set_src(recycle_img,&recycle);
		if((buffera[0]&0x08) == 0x08)
			lv_img_set_src(other_img,&imgfull);
		else
			lv_img_set_src(other_img,&other);
		memset(buffera,0,16);
		lv_refr_now(NULL);

		if(count < 20)
			count ++;
		else
			count = 0;

		if(index1 == 20)
			break;

		sleep(1);
	}
	return 0;
}
