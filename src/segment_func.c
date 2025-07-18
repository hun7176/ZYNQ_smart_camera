#include "common.h"


void Segment_Upper(u16 number)
{
    u32 SegReg = SEVEN_SEG_mReadReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0);
    u32 upper = 0;

    // 고정 문자 S, P, F
    upper |= (13 & 0xF) << (4 * 4);  // 자리 4 (index 4): S
    upper |= (12 & 0xF) << (5 * 4);  // 자리 5: P
    upper |= (11 & 0xF) << (6 * 4);  // 자리 6: F

    // 입력된 number는 0~9로 가정하고, 자리 7에 표시 (맨 왼쪽)
    upper |= (number & 0xF) << (7 * 4);

    // 상위 4자리만 갱신
    SegReg &= 0x0000FFFF;  // 하위 4자리 유지
    SegReg |= upper;

    SEVEN_SEG_mWriteReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0, SegReg);
}




void Segment_Lower(u16 number)
{
    u32 SegReg = SEVEN_SEG_mReadReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0);
    u32 lower = 0;
    int i;

    for (i = 0; i < 4; i++) {
        u8 digit = number % 10;
        lower |= (digit & 0xF) << (i * 4);
        number /= 10;
    }

    SegReg &= 0xFFFF0000;  // 상위 4자리 유지, 하위 4자리 clear
    SegReg |= lower;

    SEVEN_SEG_mWriteReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0, SegReg);
}

void Segment_AllDash(void)
{
    u32 SegReg = 0;
    for (int i = 0; i < 8; i++) {
        SegReg |= (0xA << (i * 4));
    }

    SEVEN_SEG_mWriteReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0, SegReg);
}
