#include "common.h"
#include <arm_neon.h>
#include <stdint.h>

#define WIDTH 240   // 480픽셀 / 2픽셀 packed
#define HEIGHT 272

typedef uint32_t u32;



u32* edge_filter(u32 *buffer) {
    static u32 new_buffer[65280];
    int gray, sumGray, r, g, b;
    u32 buff0, buff1, pre_buff, pos_buff;
    int mask[3][3] = {
        {-2, -2, -2},
        {-2, 16, -2},
        {-2, -2, -2}
    };

    for (int i = 1; i < 271; i++) {
        for (int j = 1; j < 239; j++) {
            // 픽셀1 (하위 16bit)
            sumGray = 0;
            for (int id = i-1; id <= i+1; id++) {
                buff0=buffer[id*240+j];
                pre_buff=buffer[id*240+j-1];
                r = (buff0 >> 11) & 0x1F;
                g = (buff0 >> 5) & 0x3F;
                b = buff0 & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[id-i+1][1];
                r = (buff0 >> 27) & 0x1F;
                g = (buff0 >> 21) & 0x3F;
                b = (buff0 >> 16) & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[id-i+1][2];
                r = (pre_buff >> 27) & 0x1F;
                g = (pre_buff >> 21) & 0x3F;
                b = (pre_buff >> 16) & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[id-i+1][0];

            }
            if (sumGray < 0) sumGray = 0;
            if (sumGray > 63) sumGray = 63;
            int gray5_1 = sumGray * 31 / 63;
            int data1 = (gray5_1 << 11) | (sumGray << 5) | gray5_1;

            // 픽셀2 (상위 16bit)
            sumGray = 0;
            for (int di = i-1; di <= i+1; di++) {
                buff1=buffer[di*240+j];
                pos_buff=buffer[di*240+j+1];
                r = (buff1 >> 11) & 0x1F;
                g = (buff1 >> 5) & 0x3F;
                b = buff1 & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[di-i+1][0];
                r = (buff1 >> 27) & 0x1F;
                g = (buff1 >> 21) & 0x3F;
                b = (buff1 >> 16) & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[di-i+1][1];
                r = (pos_buff >> 11) & 0x1F;
                g = (pos_buff >> 5) & 0x3F;
                b = (pos_buff >> 0) & 0x1F;
                gray = (3*r + 6*g + b) / 10;
                sumGray += gray * mask[di-i+1][2];

            }
            if (sumGray < 0) sumGray = 0;
            if (sumGray > 63) sumGray = 63;
            int gray5_2 = sumGray * 31 / 63;
            int data2 = (gray5_2 << 11) | (sumGray << 5) | gray5_2;

            // 합쳐서 packed 저장 (상위 픽셀 << 16 | 하위 픽셀)
            new_buffer[j + 240*i] = (data2 << 16) | data1;
        }
    }
    return new_buffer;
}



u32* blur_filter(u32 *buffer)
{
    static u32 new_buffer[65280];
    int RD, GD, BD;
    int Data1, Data2;
    int R1, G1, B1, R2, G2, B2;
    u32 pix0, pix1, pre_pix, pos_pix;
    for (int i = 1; i < 271; i++) {
        for (int j = 1; j < 239; j++) {
            // 픽셀1 (하위 16bit)
            RD = GD = BD = 0;

            for (int id = i - 1; id <= i + 1; id++) {
                pix0=buffer[id*240+j];
                pre_pix=buffer[id*240+j-1];
                RD += (pix0 >> 27) & 0x1F;
                GD += (pix0 >> 21) & 0x3F;
                BD += (pix0 >> 16) & 0x1F;

                RD += (pix0 >> 11) & 0x1F;
                GD += (pix0 >> 5) & 0x3F;
                BD += pix0 & 0x1F;

                RD += (pre_pix >> 27) & 0x1F;
                GD += (pre_pix >> 21) & 0x3F;
                BD += (pre_pix >> 16) & 0x1F;
            }
            R1 = RD / 9;
            G1 = GD / 9;
            B1 = BD / 9;
            Data1 = (R1 << 11) | (G1 << 5) | B1;

            // 픽셀2 (상위 16bit)
            RD = GD = BD = 0;
            for (int id = i - 1; id <= i + 1; id++) {
            	pix1=buffer[id*240+j];
            	pos_pix=buffer[id*240+j+1];
                RD += (pix1 >> 27) & 0x1F;
                GD += (pix1 >> 21) & 0x3F;
                BD += (pix1 >> 16) & 0x1F;

                RD += (pix1 >> 11) & 0x1F;
                GD += (pix1 >> 5) & 0x3F;
                BD += pix1 & 0x1F;

                RD += (pos_pix >> 11) & 0x1F;
                GD += (pos_pix >> 5) & 0x3F;
                BD += (pos_pix >> 0) & 0x1F;

            }
            R2 = RD / 9;
            G2 = GD / 9;
            B2 = BD / 9;
            Data2 = (R2 << 11) | (G2 << 5) | B2;

            // 픽셀2(상위) + 픽셀1(하위)로 packed 저장
            new_buffer[j + 240 * i] = (Data2 << 16) | Data1;
        }
    }

    return new_buffer;
}


u32* blur_filter_simd(u32 *buffer) {
    static u32 new_buffer[WIDTH * HEIGHT];

    // 1픽셀 평균 블러 대신 2x2 평균 필터 적용 (간단히 오른쪽, 아래 픽셀 포함)
    // 4 uint32씩 = 8픽셀 단위 처리 (가로 240 픽셀 -> 120 uint32 요소)
    for (int y = 0; y < HEIGHT - 1; y++) {
        for (int x = 0; x < WIDTH - 4; x += 4) {
            // 현재 행, 다음 행에서 4 uint32씩 로드 (총 16 픽셀)
            uint32x4_t row0 = vld1q_u32(&buffer[y * WIDTH + x]);
            uint32x4_t row1 = vld1q_u32(&buffer[(y + 1) * WIDTH + x]);

            // 픽셀 2개씩이므로 4 uint32 = 8 픽셀
            // uint16x8_t 타입으로 변환해 16비트 단위로 픽셀 분리
            uint16x8_t pix0 = vreinterpretq_u16_u32(row0);
            uint16x8_t pix1 = vreinterpretq_u16_u32(row1);

            // 각 픽셀 채널 분리용 마스크
            uint16x8_t mask_R = vdupq_n_u16(0xF800);
            uint16x8_t mask_G = vdupq_n_u16(0x07E0);
            uint16x8_t mask_B = vdupq_n_u16(0x001F);

            // R,G,B 채널 분리 (row0)
            uint16x8_t R0 = vshrq_n_u16(vandq_u16(pix0, mask_R), 11);
            uint16x8_t G0 = vshrq_n_u16(vandq_u16(pix0, mask_G), 5);
            uint16x8_t B0 = vandq_u16(pix0, mask_B);

            // R,G,B 채널 분리 (row1)
            uint16x8_t R1 = vshrq_n_u16(vandq_u16(pix1, mask_R), 11);
            uint16x8_t G1 = vshrq_n_u16(vandq_u16(pix1, mask_G), 5);
            uint16x8_t B1 = vandq_u16(pix1, mask_B);

            // 2x2 평균을 위해 각 채널 더하기 (row0 + row1)
            uint16x8_t R_sum = vaddq_u16(R0, R1);
            uint16x8_t G_sum = vaddq_u16(G0, G1);
            uint16x8_t B_sum = vaddq_u16(B0, B1);

            // 오른쪽으로 한 픽셀씩 시프트해서 인접 픽셀 더하기
            // uint16x8_t vextq_u16(uint16x8_t a, uint16x8_t b, int n);
            uint16x8_t R_right = vextq_u16(R_sum, R_sum, 1);
            uint16x8_t G_right = vextq_u16(G_sum, G_sum, 1);
            uint16x8_t B_right = vextq_u16(B_sum, B_sum, 1);

            uint16x8_t R_avg = vrshrq_n_u16(vaddq_u16(R_sum, R_right), 2); // (R0 + R1 + R_right) / 4
            uint16x8_t G_avg = vrshrq_n_u16(vaddq_u16(G_sum, G_right), 2);
            uint16x8_t B_avg = vrshrq_n_u16(vaddq_u16(B_sum, B_right), 2);

            // RGB565 다시 조합
            uint16x8_t out_pix = vorrq_u16(
                vorrq_u16(vshlq_n_u16(R_avg, 11), vshlq_n_u16(G_avg, 5)),
                B_avg
            );

            // 16비트 픽셀 8개 -> 4 uint32로 재변환 후 저장
            uint32x4_t out32 = vreinterpretq_u32_u16(out_pix);

            vst1q_u32(&new_buffer[y * WIDTH + x], out32);
        }
    }

    return new_buffer;
}


u32* emboss_filter(u32 *buffer) {
    static u32 new_buffer[65280];
    int width = 240;
    int height = 272;

    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            int idx = y * width + x;
            int prev_idx = (y - 1) * width + (x - 1);
            // -------------------
            // 1) 픽셀1 (하위 16bit)
            // -------------------
            u16 pixel1 = buffer[idx] & 0xFFFF;
            u16 prev_pixel1 = buffer[prev_idx] >> 16;

            u8 r = (pixel1 >> 11) & 0x1F;
            u8 g = (pixel1 >> 5) & 0x3F;
            u8 b = pixel1 & 0x1F;
            u8 gray = (r * 8 + g * 4 + b * 8) / 3;

            u8 pr = (prev_pixel1 >> 11) & 0x1F;
            u8 pg = (prev_pixel1 >> 5) & 0x3F;
            u8 pb = prev_pixel1 & 0x1F;
            u8 prev_gray = (pr * 8 + pg * 4 + pb * 8) / 3;

            int diff = (int)gray - (int)prev_gray + 128;
            if (diff < 0) diff = 0;
            if (diff > 255) diff = 255;

            u8 r_out1 = diff >> 3; // 5bit
            u8 g_out1 = diff >> 2; // 6bit
            u8 b_out1 = diff >> 3; // 5bit
            u16 data1 = (r_out1 << 11) | (g_out1 << 5) | b_out1;

            // -------------------
            // 2) 픽셀2 (상위 16bit)
            // -------------------
            prev_idx = (y - 1) * width + x;
            u16 pixel2 = buffer[idx] >> 16;
            u16 prev_pixel2 = buffer[prev_idx] & 0xFFFF;

            r = (pixel2 >> 11) & 0x1F;
            g = (pixel2 >> 5) & 0x3F;
            b = pixel2 & 0x1F;
            gray = (r * 8 + g * 4 + b * 8) / 3;

            pr = (prev_pixel2 >> 11) & 0x1F;
            pg = (prev_pixel2 >> 5) & 0x3F;
            pb = prev_pixel2 & 0x1F;
            prev_gray = (pr * 8 + pg * 4 + pb * 8) / 3;

            diff = (int)gray - (int)prev_gray + 128;
            if (diff < 0) diff = 0;
            if (diff > 255) diff = 255;

            u8 r_out2 = diff >> 3; // 5bit
            u8 g_out2 = diff >> 2; // 6bit
            u8 b_out2 = diff >> 3; // 5bit
            u16 data2 = (r_out2 << 11) | (g_out2 << 5) | b_out2;

            // 두 픽셀을 하나의 u32에 packed
            new_buffer[idx] = (data2 << 16) | data1;
        }
    }

    return new_buffer;
}



u32* negative_filter(u32 *buffer) {
	static u32 new_buffer[65280];
    for (int i = 0; i < 65280; i++) {
        u16 pixel = buffer[i] & 0xFFFF;  // RGB565 기준
        u8 r1 = (pixel >> 11) & 0x1F;
        u8 g1 = (pixel >> 5) & 0x3F;
        u8 b1 = pixel & 0x1F;
        r1 = 31 - r1;
        g1 = 63 - g1;
        b1 = 31 - b1;

        u16 pixel2 = buffer[i] >> 16;
        u8 r2 = (pixel2 >> 11) & 0x1F;
        u8 g2 = (pixel2 >> 5) & 0x3F;
        u8 b2 = pixel2 & 0x1F;

        r2 = 31 - r2;
        g2 = 63 - g2;
        b2 = 31 - b2;

        new_buffer[i] = (r2 << 27) | (g2 << 21) | (b2 << 16) | (r1 << 11) | (g1 << 5) | b1;
    }
    return new_buffer;
}

