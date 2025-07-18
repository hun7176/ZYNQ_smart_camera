/*
 * common.h
 *
 *  Created on: 2025. 5. 5.
 *      Author: seungH
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "xil_exception.h"
#include "xparameters.h"
#include "xscugic.h"
#include "pushbutton.h"
#include "my_interrupt.h"
#include "my_textlcd.h"
#include "textlcd.h"

#include "xil_io.h"
#include "xil_printf.h"
#include "ov7670_camera.h"
#include "image_func.h"

#include "sdcard_func.h"
#include "ff.h"

#include "seven_seg.h"
#include "segment_func.h"
#include "my_filter.h"

#include "xiicps.h"
#include "xil_types.h"

#define BRAM_BASEADDR XPAR_OV7670_CAMERA_0_S00_AXI_BASEADDR
#define IMG_WIDTH 480
#define IMG_HEIGHT 272
#define IMG_PIXELS (IMG_WIDTH * IMG_HEIGHT)


extern volatile int stream_en;
extern picture_count;
extern u32 buffer[65280];
extern u32 filtered_buffer[65280];
extern status;
extern main_menu_status;
extern read_picture_number;

extern volatile int filter_select;
extern int filter_num;



typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} RTC_Time;

extern RTC_Time t;




#endif /* SRC_COMMON_H_ */
