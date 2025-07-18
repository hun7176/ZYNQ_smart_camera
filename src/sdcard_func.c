#include "common.h"

// SD card parameters
static FATFS fatfs;
static FIL fil;
static TCHAR *Path = "0:/";


static u32 data_size = 65280 * sizeof(u32);  // 4 bytes * 65280
static u32 NumBytesRead;


int get_sdcard_image(u32 *buffer, const char *filename) {
	NumBytesRead = 0;

	FRESULT Res;

	// Mount SD card
	Res = f_mount(&fatfs, Path, 0);
	if (Res != FR_OK) {
		xil_printf("mount_fail\n");
		return -1;
	}

	// Open file
	Res = f_open(&fil, filename, FA_READ);
	if (Res) {
		xil_printf("file_open_fail\n");
		return -1;
	}

	// Seek to start
	Res = f_lseek(&fil, 0);
	if (Res) {
		xil_printf("fseek_fail\n");
		return -1;
	}

	// Read data
	Res = f_read(&fil, buffer, data_size, &NumBytesRead);
	if (Res || NumBytesRead != data_size) {
		xil_printf("data_read_fail\n");
		return -1;
	}

	f_close(&fil);
	xil_printf("file_read_success\n");

	return 0;
}


int write_sdcard_image(u32 *buffer, int number) {
    FRESULT Res;
    UINT NumBytesWritten;
    char filename[32];

    sprintf(filename, "image%d.bin", number);

    Res = f_mount(&fatfs, Path, 0);
    if (Res != FR_OK) {
        xil_printf("mount_fail\n");
        return -1;
    }

    Res = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (Res != FR_OK) {
        xil_printf("file_open_fail\n");
        return -1;
    }

    Res = f_lseek(&fil, 0);
    if (Res != FR_OK) {
        xil_printf("fseek_fail\n");
        f_close(&fil);
        return -1;
    }

    Res = f_write(&fil, buffer, data_size, &NumBytesWritten);
    if (Res != FR_OK || NumBytesWritten != data_size) {
        xil_printf("data_write_fail\n");
        f_close(&fil);
        return -1;
    }

    f_close(&fil);
    xil_printf("file_write_success: %s\n", filename);
    return 0;
}
int read_sdcard_image(u32 *buffer, int number) {
    FRESULT Res;
    char filename[32];
    UINT NumBytesReadLocal;

    // 파일 이름 생성: image{number}.bin
    sprintf(filename, "image%d.bin", number);

    // SD 카드 마운트
    Res = f_mount(&fatfs, Path, 0);
    if (Res != FR_OK) {
        xil_printf("mount_fail\n");
        return -1;
    }

    // 파일 열기
    Res = f_open(&fil, filename, FA_READ);
    if (Res != FR_OK) {
        xil_printf("file_open_fail: %s\n", filename);
        return -1;
    }

    // 시작 위치로 이동
    Res = f_lseek(&fil, 0);
    if (Res != FR_OK) {
        xil_printf("fseek_fail\n");
        f_close(&fil);
        return -1;
    }

    // 파일에서 버퍼로 데이터 읽기
    Res = f_read(&fil, buffer, data_size, &NumBytesReadLocal);
    if (Res != FR_OK || NumBytesReadLocal != data_size) {
        xil_printf("data_read_fail\n");
        f_close(&fil);
        return -1;
    }

    f_close(&fil);
    xil_printf("file_read_success: %s\n", filename);
    return 0;
}

