/*************************************************************************************************
                                    无线驱动模块
*************************************************************************************************/
    #include "..\Include\Vars.h"
    #include "..\Include\Wireless.h"
    #include "..\Include\Timer.h" 
/*******************************************************************************/
#define SCK0  P2OUT &= ~BIT1
#define SCK1  P2OUT |= BIT1

#define CE0  P2OUT &= ~BIT0
#define CE1  P2OUT |= BIT0

#define CSN0  P1OUT &= ~BIT5
#define CSN1  P1OUT |= BIT5

#define MO0  P1OUT &= ~BIT4
#define MO1  P1OUT |= BIT4

#define MI_IN  P2OUT & BIT3

#define R_REGISTER	0x00
#define W_REGISTER	0x20

static uchar SPI_WR_Byte(uchar Wr_Data);	//读写一个字节
/*******************************************************************************\
名称：WR_Delay(void)
作用：读写延时
参数：无
描述：无
\*******************************************************************************/
void WR_Delay(void)
{
  uchar i = 20;
  while (--i >0);
}

/*******************************************************************************\
名称：SPI_WR_Byte(uint8 Wr_Data)
作用：SPI读写一个字节
参数：无
描述：无
\*******************************************************************************/
static uchar SPI_WR_Byte(uchar Wr_Data)
{
  uchar i,Rd_Data = 0;
  
  SCK0;
  for (i=0; i<8; i++)
  {
    if (Wr_Data & 0x80)
    {
      MO1;
    }
    else
    {
       MO0;
    }
    WR_Delay();
    SCK1;
    if (MI_IN)
    {
       Rd_Data |= 0x01;
    }
    Rd_Data <<= 1;
    Wr_Data <<= 1;
    WR_Delay();
    SCK0;
  }
  _NOP();
  return(Rd_Data);
}

/*******************************************************************************\
名称：SPI_WRITE_Data(uint8 Addr, uint8 Wr_Data, uint8 Len)
作用：SPI写N个字节
参数：数组地址，长度
描述：无
\*******************************************************************************/
void SPI_Write_Data(uint8 Addr, uchar Wr_Data[], uint8 Len)
{ 
  uint8 i;
  
  CE1;
  CSN0;
  SPI_WR_Byte((Addr & 0x1F) | W_REGISTER); 
  
  for (i=0; i<Len; i++)
  {
	SPI_WR_Byte(Wr_Data[i]);  
  }
  
  CSN1;
  CE0;
}

/*******************************************************************************\
名称：SPI_Read_Data(uint8 Addr, uint8 Wr_Data, uint8 Len)
作用：SPI读N个字节
参数：数组地址，长度
描述：无
\*******************************************************************************/
void SPI_Read_Data(uint8 Addr, uchar Rd_Data[], uint8 Len)
{ 
  uint8 i;
  
  CE1;
  CSN0;
  
  SPI_WR_Byte((Addr & 0x1F) | R_REGISTER); 
  
  for (i=0; i<Len; i++)
  {
	Rd_Data[i] = SPI_WR_Byte(0);  
  }
  
  CSN1;
  CE0;
}


/*************************************************************************************************
                                    结束无线程序模块
*************************************************************************************************/