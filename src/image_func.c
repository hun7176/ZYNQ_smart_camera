#include "common.h"


// RGB565 색상 정의
#define BLACK_RGB565    0x0000
#define WHITE_RGB565    0xFFFF

#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   272
#define WATERMARK_START_ROW (SCREEN_HEIGHT - 20)  // 252행부터
#define WATERMARK_END_ROW   SCREEN_HEIGHT         // 272행까지
#define WATERMARK_HEIGHT    20

// 간단한 3x5 비트맵 폰트 (숫자 0-9, 콜론, 슬래시)
static const unsigned char font_3x5[][5] = {
    {0b111, 0b101, 0b101, 0b101, 0b111}, // 0
    {0b010, 0b110, 0b010, 0b010, 0b111}, // 1
    {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
    {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
    {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
    {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
    {0b111, 0b001, 0b001, 0b001, 0b001}, // 7
    {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
    {0b111, 0b101, 0b111, 0b001, 0b111}, // 9
    {0b000, 0b010, 0b000, 0b010, 0b000}, // :
    {0b001, 0b001, 0b010, 0b100, 0b100}  // /
};




void generate_initial_image(u32 *buffer) {
    // RGB565 색 정의
    const u16 colors[8] = {
        0xFFFF, // 흰색
        0xFFE0, // 노랑
        0x07FF, // 시안
        0x07E0, // 초록
        0xF81F, // 마젠타
        0xF800, // 빨강
        0x001F, // 파랑
        0x0000  // 검정
    };

    int width = 240;
    int height = 272;
    int bar_width = width / 8;  // 30

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            int bar_idx1 = x / bar_width;
            int bar_idx2 = (x + 1) / bar_width;

            u16 pixel1 = colors[bar_idx1];
            u16 pixel2 = colors[bar_idx2];

            int idx = (y * (width / 2)) + (x / 2);
            buffer[idx] = (pixel2 << 16) | pixel1;
        }
    }
}



void display_image(u32 *src_buffer) {
    int Data, R, G, B;

    for (int i = 0; i < 272; i++) {
        for (int j = 0; j < 240; j++) {
            // 1픽셀
            Data = src_buffer[j + 240 * i] & 0x0000FFFF;
            R = (Data >> 11) & 0x1F;
            G = Data & 0x07E0;
            B = Data & 0x001F;
            Data = (B << 11) | G | R;
            Xil_Out32(XPAR_TFTLCD_0_S00_AXI_BASEADDR + (2 * j + 480 * i) * 4, Data);

            // 2픽셀
            Data = src_buffer[j + 240 * i] >> 16;
            R = (Data >> 11) & 0x1F;
            G = Data & 0x07E0;
            B = Data & 0x001F;
            Data = (B << 11) | G | R;
            Xil_Out32(XPAR_TFTLCD_0_S00_AXI_BASEADDR + (1 + 2 * j + 480 * i) * 4, Data);
        }
    }
}
void get_image(u32 *buffer){
    for (int i = 0; i < 65280; i++) {
        u16 pixel1 = (u16)(OV7670_CAMERA_mReadReg(BRAM_BASEADDR, i * 8) & 0xFFFF);
        u16 pixel2 = (u16)(OV7670_CAMERA_mReadReg(BRAM_BASEADDR, i * 8 + 4) & 0xFFFF);
        buffer[i] = (pixel2 << 16) | pixel1;
    }
}







void set_pixel(u32 *buffer, int x, int y, u16 color) {
    x = SCREEN_WIDTH - 1 - x;
    y = SCREEN_HEIGHT - 1 - y;

    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        int pixel_index = y * SCREEN_WIDTH + x;
        int word_index = pixel_index / 2;
        int is_upper = pixel_index % 2;
        if (is_upper) {
            buffer[word_index] = (buffer[word_index] & 0x0000FFFF) | ((u32)color << 16);
        } else {
            buffer[word_index] = (buffer[word_index] & 0xFFFF0000) | color;
        }
    }
}

// 확대된 문자 그리기 함수 (2배 확대)
void draw_char(u32 *buffer, int start_x, int start_y, int char_index) {
    if (char_index < 0 || char_index > 11) return;

    for (int row = 0; row < 5; row++) {
        unsigned char line = font_3x5[char_index][row];
        for (int col = 0; col < 3; col++) {
            if (line & (1 << (2 - col))) {
                for (int dy = 0; dy < 2; dy++) {
                    for (int dx = 0; dx < 2; dx++) {
                        set_pixel(buffer, start_x + col * 2 + dx, start_y + row * 2 + dy, WHITE_RGB565);
                    }
                }
            }
        }
    }
}

// 숫자 그리기 (확대된 글꼴에 맞춰 간격 조정)
void draw_number(u32 *buffer, int *x, int y, int num, int digits) {
    if (digits == 2) {
        draw_char(buffer, *x, y, num / 10);
        *x += 7;
        draw_char(buffer, *x, y, num % 10);
        *x += 7;
    } else if (digits == 4) {
        draw_char(buffer, *x, y, (num / 1000) % 10);
        *x += 7;
        draw_char(buffer, *x, y, (num / 100) % 10);
        *x += 7;
        draw_char(buffer, *x, y, (num / 10) % 10);
        *x += 7;
        draw_char(buffer, *x, y, num % 10);
        *x += 7;
    }
}
void draw_water_mark(u32 *buffer) {
    for (int y = WATERMARK_START_ROW; y < WATERMARK_END_ROW; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            set_pixel(buffer, x, y, BLACK_RGB565);
        }
    }

    int start_x = 5;
    int current_y = WATERMARK_START_ROW + 2;
    int x = start_x;

    // 연도 출력
    draw_number(buffer, &x, current_y, t.year, 4);
    draw_char(buffer, x, current_y, 11); // /
    x += 7;

    // 월, 일 출력
    draw_number(buffer, &x, current_y, t.month, 2);
    draw_char(buffer, x, current_y, 11); // /
    x += 7;
    draw_number(buffer, &x, current_y, t.day, 2);
    x += 10;

    // 시:분:초 출력
    draw_number(buffer, &x, current_y, t.hour, 2);
    draw_char(buffer, x, current_y, 10); // :
    x += 7;
    draw_number(buffer, &x, current_y, t.min, 2);
    draw_char(buffer, x, current_y, 10); // :
    x += 7;
    draw_number(buffer, &x, current_y, t.sec, 2);
}
void draw_number_center(u32 *buffer, int number){
    if (number < 0 || number > 9) return;

    const unsigned char *font = font_3x5[number];
    int font_w = 3;
    int font_h = 5;

    int scale = 10;  // 크기 확대 (기존 6 → 10)

    int draw_w = font_w * scale;
    int draw_h = font_h * scale;

    int screen_w = 240;
    int screen_h = 272;

    int x_offset = (screen_w - draw_w) / 2;
    int y_offset = (screen_h - draw_h) / 2;

    u32 overlay_color = 0xFFFF;  // 흰색 (RGB565 형식 기준: 0xFFFF = R,G,B 모두 최대)

    for (int fy = 0; fy < font_h; fy++) {
        int reversed_fy = font_h - 1 - fy;  // 상하 반전

        for (int fx = 0; fx < font_w; fx++) {
            int reversed_fx = font_w - 1 - fx;  // 좌우 반전

            if ((font[reversed_fy] >> (2 - reversed_fx)) & 0x1) {
                for (int dy = 0; dy < scale; dy++) {
                    for (int dx = 0; dx < scale; dx++) {
                        int px = x_offset + fx * scale + dx;
                        int py = y_offset + fy * scale + dy;
                        int idx = py * screen_w + px;

                        if (idx >= 0 && idx < 65280) {
                            buffer[idx] = overlay_color;
                        }
                    }
                }
            }
        }
    }
}
