#include "common.h"


void Segment_Upper(u16 number)
{
    u32 SegReg = SEVEN_SEG_mReadReg(XPAR_SEVEN_SEG_0_S00_AXI_BASEADDR, 0);
    u32 upper = 0;

    // ���� ���� S, P, F
    upper |= (13 & 0xF) << (4 * 4);  // �ڸ� 4 (index 4): S
    upper |= (12 & 0xF) << (5 * 4);  // �ڸ� 5: P
    upper |= (11 & 0xF) << (6 * 4);  // �ڸ� 6: F

    // �Էµ� number�� 0~9�� �����ϰ�, �ڸ� 7�� ǥ�� (�� ����)
    upper |= (number & 0xF) << (7 * 4);

    // ���� 4�ڸ��� ����
    SegReg &= 0x0000FFFF;  // ���� 4�ڸ� ����
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

    SegReg &= 0xFFFF0000;  // ���� 4�ڸ� ����, ���� 4�ڸ� clear
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
