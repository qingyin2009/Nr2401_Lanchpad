/*************************************************************************************************
                                    无线程序模块头文件
*************************************************************************************************/
#ifndef WIRELESS_H
#define WIRELESS_H
//******************************************************************************
#include "..\Include\Vars.h"
//******************************************************************************
void SPI_Read_Data(uint8 Addr, uchar Rd_Data[], uint8 Len);
void SPI_Write_Data(uint8 Addr, uchar Wr_Data[], uint8 Len);
//******************************************************************************
#endif
/*************************************************************************************************
                                    结束无线程序头文件模块
*************************************************************************************************/