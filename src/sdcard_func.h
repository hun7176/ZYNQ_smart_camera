#ifndef SRC_SDCARD_FUNC_H_
#define SRC_SDCARD_FUNC_H_


#include "xil_types.h"

#define IMG_WIDTH 240
#define IMG_HEIGHT 272
#define BUFFER_SIZE (IMG_WIDTH * IMG_HEIGHT)


int get_sdcard_image(u32 *buffer, const char *filename);
int write_sdcard_image(u32 *buffer, int number);
int read_sdcard_image(u32 *buffer, int number);

#endif
