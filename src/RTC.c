#include "common.h"
#define IIC_SLAVE_ADDR  0x51
#define IIC_SCLK_RATE   100000

int write_time_to_rtc(RTC_Time* time)
{
    XIicPs Iic;
    XIicPs_Config *Config;
    u8 SendBuffer[4];
    int Status;

    Config = XIicPs_LookupConfig(XPAR_XIICPS_0_DEVICE_ID);
    if (Config == NULL) return XST_FAILURE;

    Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

    SendBuffer[0] = 0x02; // 시작 레지스터 (초)
    SendBuffer[1] = ((time->sec / 10) << 4) | (time->sec % 10);
    SendBuffer[2] = ((time->min / 10) << 4) | (time->min % 10);
    SendBuffer[3] = ((time->hour / 10) << 4) | (time->hour % 10);

    Status = XIicPs_MasterSendPolled(&Iic, SendBuffer, 4, IIC_SLAVE_ADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    while (XIicPs_BusIsBusy(&Iic)) { /* Wait */ }

    return XST_SUCCESS;
}



int read_time_from_rtc(RTC_Time* time)
{
    XIicPs Iic;
    XIicPs_Config *Config;
    u8 SendBuffer = 0x02;
    u8 RecvBuffer[3];
    int Status;

    Config = XIicPs_LookupConfig(XPAR_XIICPS_0_DEVICE_ID);
    if (Config == NULL) {
        return XST_FAILURE;
    }

    Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

    Status = XIicPs_MasterSendPolled(&Iic, &SendBuffer, 1, IIC_SLAVE_ADDR);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    while (XIicPs_BusIsBusy(&Iic)) {
        /* Wait */
    }

    Status = XIicPs_MasterRecvPolled(&Iic, RecvBuffer, 3, IIC_SLAVE_ADDR);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    time->sec  = ((RecvBuffer[0] >> 4) * 10) + (RecvBuffer[0] & 0x0F); // 0x02
    time->min  = ((RecvBuffer[1] >> 4) * 10) + (RecvBuffer[1] & 0x0F); // 0x03
    time->hour = ((RecvBuffer[2] >> 4) * 10) + (RecvBuffer[2] & 0x0F); // 0x04


    return XST_SUCCESS;
}
