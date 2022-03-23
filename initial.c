#include "mILI9325.h"
#include "mFONT.h"

extern  mDis_Color  ILI9325;
GPIO_InitTypeDef GPIO_InitStructure;

//Red Gray scale灰阶(65K)
const unsigned char RedGrayScale[]={
  0x00,0x00, 0x08,0x00, 0x10,0x00, 0x18,0x00, 0x20,0x00, 0x28,0x00, 0x30,0x00, 0x38,0x00,
  0x40,0x00, 0x48,0x00, 0x50,0x00, 0x58,0x00, 0x60,0x00, 0x68,0x00, 0x70,0x00, 0x78,0x00,
  0x80,0x00, 0x88,0x00, 0x90,0x00, 0x98,0x00, 0xA0,0x00, 0xA8,0x00, 0xB0,0x00, 0xB8,0x00,
  0xC0,0x00, 0xC8,0x00, 0xD0,0x00, 0xD8,0x00, 0xE0,0x00, 0xE8,0x00, 0xF0,0x00, 0xF8,0x00,
};
//Green Gray scale灰阶(65K)
const unsigned char  GreenGrayScale[]={
  0x00,0x00, 0x00,0x60, 0x00,0xA0, 0x00,0xE0, 0x01,0x00, 0x01,0x60, 0x01,0xA0, 0x01,0xE0,
  0x02,0x00, 0x02,0x60, 0x02,0xA0, 0x02,0xE0, 0x03,0x00, 0x03,0x60, 0x03,0xA0, 0x03,0xE0,
  0x04,0x00, 0x04,0x60, 0x04,0xA0, 0x04,0xE0, 0x05,0x00, 0x05,0x60, 0x05,0xA0, 0x05,0xE0,
  0x06,0x00, 0x06,0x60, 0x06,0xA0, 0x06,0xE0, 0x07,0x00, 0x07,0x60, 0x07,0xA0, 0x07,0xE0,
};

//Blue Gray scale灰阶(65K)
const unsigned char  BlueGrayScale[]={
  0x00,0x00, 0x00,0x01, 0x00,0x02, 0x00,0x03, 0x00,0x04, 0x00,0x05, 0x00,0x06, 0x00,0x07,
  0x00,0x08, 0x00,0x09, 0x00,0x0A, 0x00,0x0B, 0x00,0x0C, 0x00,0x0D, 0x00,0x0E, 0x00,0x0F,
  0x00,0x10, 0x00,0x11, 0x00,0x12, 0x00,0x13, 0x00,0x14, 0x00,0x15, 0x00,0x16, 0x00,0x17,
  0x00,0x18, 0x00,0x19, 0x00,0x1A, 0x00,0x1B, 0x00,0x1C, 0x00,0x1D, 0x00,0x1E, 0x00,0x1F,
};

//White Gray scale灰阶(65K)
const unsigned char  WhiteGrayScale[]={
  0x00,0x00, 0x08,0x61, 0x10,0xA2, 0x18,0xE3, 0x21,0x04, 0x29,0x65, 0x31,0xA6, 0x39,0xE7,
  0x42,0x08, 0x4A,0x69, 0x52,0xAA, 0x5A,0xEB, 0x63,0x0C, 0x6B,0x6D, 0x73,0xAE, 0x7B,0xEF,
  0x84,0x10, 0x8C,0x71, 0x94,0xB2, 0x9C,0xF3, 0xA5,0x14, 0xAD,0x75, 0xB5,0xB6, 0xBD,0xF7,
  0xC6,0x18, 0xCE,0x79, 0xD6,0xBA, 0xDE,0xFB, 0xE7,0x1C, 0xEF,0x7D, 0xF7,0xBE, 0xFF,0xFF,
};

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : 延时功能函数
* Input          : nCount 延时值( mS )
* Output         : None
* Return         : None
*******************************************************************************/
void  Delay_mS (uint16_t nCount){
  unsigned int  i;
  do{
    for(i=0; i<5000; i++);
  }
  while(nCount--);
}

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 延时功能函数
* Input          : nCount 延时值( uS )
* Output         : None
* Return         : None
*******************************************************************************/
void  Delay_uS (uint16_t nCount){
  unsigned int  i;
  do{
    for(i=0; i<5; i++);
  }while(nCount--);
}

/*******************************************************************************
* Function Name  : ILI9325_CtrlLinesConfig
* Description    : Configures LCD control lines in Output Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_Reset(void){
  //对TFT进行复位一次
  ILI9325_RESET_HIGH();
  Delay_mS(50);
  ILI9325_RESET_LOW();                               
  Delay_mS(100);
  ILI9325_RESET_HIGH();                    
  Delay_mS(50);
}

/*******************************************************************************
* Function Name  : ILI9325_CtrlLinesConfig 控制线配置
* Description    : Configures LCD control lines in Output Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_CtrlLinesConfig(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOE, ENABLE);
  
  /* Configure PD.7–PD.11 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_LCD_CS | GPIO_LCD_RS | GPIO_LCD_WR | GPIO_LCD_RD |
                                GPIO_LCD_PW ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_LCD_RESET;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /* Configure PE.00 -- PE.15 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : ILI9325_WriteIndex
* Description    : 寻址寄存器
* Input          : Index
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_WriteIndex(uint8_t Index) {
  //写索引寄存器
  ILI9325_RS_LOW();
  ILI9325_CS_LOW();
  ILI9325_RD_HIGH();
  GPIO_Write(GPIOD,Index);
  ILI9325_WR_LOW();
  ILI9325_WR_HIGH();
  ILI9325_CS_HIGH();
}

/*******************************************************************************
* Function Name  : ILI9325_WriteData
* Description    : 
* Input          : Data
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_WriteData(uint16_t Data) {
  ILI9325_RS_HIGH();
  ILI9325_CS_LOW();
  ILI9325_RD_HIGH();
  GPIO_Write(GPIOD,Data);
  ILI9325_WR_LOW();
  ILI9325_WR_HIGH();
  ILI9325_CS_HIGH();
}



/*******************************************************************************
* Function Name  : ILI9325_ReadData
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t ILI9325_ReadData(void) {
  unsigned short Data=0;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  ILI9325_CS_LOW();
  ILI9325_RS_HIGH();
  ILI9325_WR_HIGH();
  //丢掉第一次读出的不确定数
  ILI9325_RD_LOW();
  Data = GPIO_ReadInputData(GPIOD);
  ILI9325_RD_HIGH();
  
  ILI9325_RD_LOW();
  Data = GPIO_ReadInputData(GPIOD);
  ILI9325_RD_HIGH();
  
  ILI9325_CS_HIGH();
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  return Data;
}

/*******************************************************************************
* Function Name  : ILI9325_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
/*void ILI9325_WriteReg(unsigned char LCD_Reg, unsigned short LCD_RegValue) {
  //写索引寄存器
  ILI9325_WriteIndex(unsigned char LCD_Reg);
  //向所寻寄存器中写入值
  ILI9325_WriteData(unsigned short LCD_RegValue);
}*/

void ILI9325_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue) {
  //写索引寄存器
  ILI9325_RS_LOW();
  ILI9325_CS_LOW();
  ILI9325_RD_HIGH();
  GPIO_Write(GPIOD,LCD_Reg);
  ILI9325_WR_LOW();
  ILI9325_WR_HIGH();
  ILI9325_CS_HIGH();
  //向所寻寄存器中写入值
  ILI9325_RS_HIGH();
  ILI9325_CS_LOW();
  ILI9325_RD_HIGH();
  GPIO_Write(GPIOD,LCD_RegValue);
  ILI9325_WR_LOW();
  ILI9325_WR_HIGH();
  ILI9325_CS_HIGH();
}

/*******************************************************************************
* Function Name  : ILI9325_BackLight(
* Description    : LCD 背景灯状态设置.
* Input          : - State: 背景灯状态 ON 或者 OFF
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_BackLight(uint8_t State) {
  if(State == ON)
    ILI9325_PW_HIGH();
  else
    ILI9325_PW_LOW();
}

/*******************************************************************************
* Function Name  : ILI9325_WriteGRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_WriteGRAM(uint16_t RGB_Code) {
ILI9325_WriteReg(R22,RGB_Code);
}

/*******************************************************************************
* Function Name  : ILI9325_Init
* Description    : Initializes LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_Init(void) { 
  //Driver IC:ILI9325
  
  ILI9325_CtrlLinesConfig();  //TFT的系统接口配置（本TFT模块采用的是i80 16-bit System Bus）
  ILI9325_Reset();            //复位一次
  
  //ILI9325_WriteReg(0x00E3, 0x3008);
  //ILI9325_WriteReg(0x00E7, 0x0012);
  //ILI9325_WriteReg(0x00EF, 0x1231);
  ILI9325_WriteReg(0x00E5, 0x78F0);
  
  /*其中的SM位配合R96中的GS位，来决定图像刷新方向。本配置为从上到下
  SM GS=00从下到上  SM GS=01从上到下  SM GS=10 从右到左  SM GS=11 从左到右*/
  ILI9325_WriteReg(R1,  0x0100);//R1:驱动输出控制
  
  ILI9325_WriteReg(R2,  0x0700);//line inversion
  /*GRAM水平方向更新*/
  ILI9325_WriteReg(R3,  0x1018);//R3：数据进入模式设置 1030

  /*保持原图像大小*/
  ILI9325_WriteReg(R4,  0x0000);//R4：可将原图像缩小到1/2或1/4来显示
  
/*****************Display Control*******************/
  ILI9325_WriteReg(R8,  0x0202);//0207
  ILI9325_WriteReg(R9,  0x0000);
  ILI9325_WriteReg(R0A, 0x0000);
  ILI9325_WriteReg(R0C, 0x0000);
  ILI9325_WriteReg(R0D, 0x0000);
  ILI9325_WriteReg(R0F, 0x0000);
  
/***************Power Control*********************/  
  ILI9325_WriteReg(R10, 0x0000);
  ILI9325_WriteReg(R11, 0x0007);//0004
  ILI9325_WriteReg(R12, 0x0000);
  ILI9325_WriteReg(R13, 0x0000);
  ILI9325_WriteReg(R7,  0x0000);
  Delay_mS(200);
  ILI9325_WriteReg(R10, 0x1690);
  ILI9325_WriteReg(R11, 0x0227);//0224
  Delay_mS(50);
  ILI9325_WriteReg(R12, 0x009d);//001b
  Delay_mS(50);
  ILI9325_WriteReg(R13, 0x1900);//1100
  ILI9325_WriteReg(R29, 0x0025);//0008
  ILI9325_WriteReg(R2B, 0x000d);
  Delay_mS(50);
  
  //默认显示坐标（0，0)
  ILI9325_WriteReg(R20, 0x0000);
  ILI9325_WriteReg(R21, 0x0000);
  
/**************Gamma Control***********/  
  ILI9325_WriteReg(R30, 0x0007);
  ILI9325_WriteReg(R31, 0x0303);
  ILI9325_WriteReg(R32, 0x0003);
  ILI9325_WriteReg(R35, 0x0206);
  ILI9325_WriteReg(R36, 0x0008);
  ILI9325_WriteReg(R37, 0x0406);
  ILI9325_WriteReg(R38, 0x0304);
  ILI9325_WriteReg(R39, 0x0007);
  ILI9325_WriteReg(R3C, 0x0602);
  ILI9325_WriteReg(R3D, 0x0008);

/********Sets display window,默认为整个屏幕********/
  ILI9325_WriteReg(R50, 0x0000);
  ILI9325_WriteReg(R51, 0x00ee);
  ILI9325_WriteReg(R52, 0x0000);
  ILI9325_WriteReg(R53, 0x013f);

/*******Gate Scan Control*************************/  
  ILI9325_WriteReg(R60, 0xa700);
  ILI9325_WriteReg(R61, 0x0001);
  ILI9325_WriteReg(R6A, 0x0000);
/********Partial Image Display Position Control***/
  ILI9325_WriteReg(R80, 0x0000);
  ILI9325_WriteReg(R81, 0x0000);
  ILI9325_WriteReg(R82, 0x0000);
  ILI9325_WriteReg(R83, 0x0000);
  ILI9325_WriteReg(R84, 0x0000);
  ILI9325_WriteReg(R85, 0x0000);
/*******Panel Interface Control******************/ 
  ILI9325_WriteReg(R90, 0x0010);
  ILI9325_WriteReg(R92, 0x0600);
  
  ILI9325_WriteReg(R7,  0x0133);
  ILI9325_WriteReg(R0,  0x0022);
  
  ILI9325.TextColor = 0x0000;
  ILI9325.BackColor = 0x667F;
  ILI9325_FillSCR(ILI9325.BackColor);
  
  ILI9325_BackLight(ON);
}

/*******************************************************************************
* Function Name  : ILI9325_SetDisplayWindow
* Description    : 设置显示窗口
* Input          : - startx:  specifies the X buttom left position.
*                  - starty:  specifies the Y buttom left position.
*                  - endx:    display window width.
*                  - endy:    display window height.
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_SetDisplayWindow(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy) {
        // 顺转90度
  ILI9325_WriteReg(R50, starty);
  ILI9325_WriteReg(R51, endy);
  ILI9325_WriteReg(R52, 319-endx);
  ILI9325_WriteReg(R53, 319-startx);
  
  ILI9325_WriteReg(R20, endy);
  ILI9325_WriteReg(R21, 319-endx);
  
  /*// 逆转90度
  ILI9325_WriteReg(R50, 239-endy);
  ILI9325_WriteReg(R51, 239-starty);
  ILI9325_WriteReg(R52, startx);
  ILI9325_WriteReg(R53, endx);
  
  ILI9325_WriteReg(R20, 239-starty);
  ILI9325_WriteReg(R21, startx);
  */
}

/*******************************************************************************
* Function Name  : ILI9325_EnterSleep
* Description    : LCD 进入休眠模式
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_EnterSleep(void) {
  ILI9325_WriteReg(R7, 0x0131);
  Delay_mS(10);
  ILI9325_WriteReg(R7, 0x0130);
  Delay_mS(10);
  ILI9325_WriteReg(R7, 0x0000);
        
        ILI9325_WriteReg(R10, 0x0080);
  ILI9325_WriteReg(R11, 0x0000);
  ILI9325_WriteReg(R12, 0x0000);
  ILI9325_WriteReg(R13, 0x0000);
  Delay_mS(10);
  ILI9325_WriteReg(R10, 0x0082);
}

/*******************************************************************************
* Function Name  : ILI9325_ExitSleep
* Description    : LCD 退出休眠模式
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_ExitSleep(void) {
  ILI9325_WriteReg(R10, 0x0080);
  ILI9325_WriteReg(R11, 0x0000);
  ILI9325_WriteReg(R12, 0x0000);
  ILI9325_WriteReg(R13, 0x0000);
  Delay_mS(10);
  ILI9325_WriteReg(R10, 0x1490);
  ILI9325_WriteReg(R11, 0x0224);
  Delay_mS(10);
  ILI9325_WriteReg(R12, 0x001A);
  Delay_mS(10);
  ILI9325_WriteReg(R13, 0x1100);
  ILI9325_WriteReg(R29, 0x0011);
  Delay_mS(10);
  ILI9325_WriteReg(R7, 0x0133);
}

/*******************************************************************************
* Function Name  : ILI9325_SetPixel
* Description    : 在指定的 x,y 坐标描点
* Input          : -x: 指定描点坐标 x 值
*                  -y: 指定描点坐标 y 值
*                  -color: 描点颜色值
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_SetPixel(uint16_t x, uint16_t y, uint16_t color) {
        ILI9325_SetDisplayWindow(x,y,x,y);
        ILI9325_WriteGRAM(color);
}

/*******************************************************************************
* Function Name  : ILI9325_RectangleFill
* Description    : 显示窗口内以指定颜色局部填充
* Input          : -x: 指定起点坐标 x 值
*                  -y: 指定起点坐标 y 值
*                  -width: 指定填充宽度
*                  -hight: 指定填充高度
*                  -color: 指定填充颜色
* Output         : None
* Return         : None
*******************************************************************************/
void  ILI9325_RectangleFill(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, uint16_t color) {        
        uint16_t i,j;

        ILI9325_SetDisplayWindow(x, y, x+width-1, y+hight-1);

        for(i=0; i<width; i++) {   
                for(j=0; j<hight; j++) { 
                        ILI9325_WriteGRAM(color);
                }
        }
}

/*******************************************************************************
* Function Name  : ILI9325_FillSCR
* Description    : 显示窗口全部以指定颜色填充
* Input          : -color: 指定填充颜色
* Output         : None
* Return         : None
*******************************************************************************/
void  ILI9325_FillSCR(uint16_t color) {        
        uint16_t i,j;

        ILI9325_SetDisplayWindow(0, 0, 319, 239);

        for(i=0; i<320; i++) {   
                for(j=0; j<240; j++) { 
                        ILI9325_WriteGRAM(color);
                }
        }
}

/*******************************************************************************
* Function Name  : ILI9325_DrawBMP
* Description    : 图片显示
* Input          : -x: 指定起点坐标 x 值
*                  -y: 指定起点坐标 y 值
*                  -width: 指定图片宽度
*                  -hight: 指定图片高度
*                  -*pBmp: 图片数据指针
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawBMP(uint16_t x,uint16_t y,uint16_t width,uint16_t hight,const uint8_t *pBmp) {
        uint16_t i,j;
        uint16_t Data;

        ILI9325_SetDisplayWindow(x, y, x+width-1, y+hight-1);

        for(i=0; i<width; i++) {   
                for(j=0; j<hight; j++) { 
                        Data = (*pBmp++)<<8;
                        Data = Data | (*pBmp++);
      
      ILI9325_WriteGRAM(Data);
                }
        }
}



/*******************************************************************************
* Function Name  : ILI9325_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_SetCursor(uint16_t x, uint16_t y) {
  ILI9325_SetDisplayWindow(x, y, x, y);
  //ILI9325_WriteReg(R20, x);
  //ILI9325_WriteReg(R21, y);
}

/*******************************************************************************
* Function Name  : ILI9325_BGR2RGB
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
uint16_t ILI9325_BGR2RGB(uint16_t BGR_Code) {
  uint16_t  r, g, b;

  r = BGR_Code & 0x1f;
  g = (BGR_Code>>5)  & 0x3f;
  b = (BGR_Code>>11) & 0x1f;
  
  return( (r<<11) + (g<<5) + (b<<0) );
}

/*******************************************************************************
* Function Name  : ILI9325_ReadRegister
* Description    : Get the data of the appointed register.
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
uint16_t ILI9325_ReadRegister(uint16_t LCD_Reg) {
  //写索引寄存器
  ILI9325_WriteIndex(LCD_Reg);
  return(ILI9325_ReadData());
}

/*******************************************************************************
* Function Name  : CheckController
* Description    : 读取 LCD 标示字符串
* Input          : 
* Output         : 
* Return         : int 类型标示字符串代码
*******************************************************************************/
uint16_t CheckController(void) {
  return(ILI9325_ReadRegister(R0));
}

/*******************************************************************************
* Function Name  : ILI9325_GetPointRGB 获得指定像素点的颜色数据
* Description    : Get the color data of the appointed pixel.
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
uint16_t ILI9325_GetPointRGB(uint16_t x,uint16_t y) {
  //ILI9325_SetDisplayWindow(x, y, x, y);
  ILI9325_SetCursor(x,y);
  return(ILI9325_BGR2RGB(ILI9325_ReadRegister(R22)));
}

/*******************************************************************************
* Function Name  : ILI9325_ClearLine
* Description    : Clears the selected line.
* Input          : - Line: the Line to be cleared.
*                    This parameter can be one of the following values:
*                  - Linex: where x can be 0..19
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_ClearLine(uint8_t Line) {
  //ILI9325_DisplayStringLine(Line, "                    ");
}

/*******************************************************************************
* Function Name  : ILI9325_SetTextColor
* Description    : Sets the Text color.
* Input          : - Color: specifies the Text color code RGB(5-6-5).
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void ILI9325_SetTextColor(uint16_t Color) {
  ILI9325.TextColor = Color;
}

/*******************************************************************************
* Function Name  : ILI9325_SetBackColor
* Description    : Sets the Background color.
* Input          : - Color: specifies the Background color code RGB(5-6-5).
* Output         : - BackColor: Background color global variable used by
*                  LCD_DrawChar and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void ILI9325_SetBackColor(uint16_t Color) {
  ILI9325.BackColor = Color;
}

/******************************************************************
- 功能描述：将一个32位的变量dat转为字符串，比如把1234转为"1234"
- 参数说明：dat:带转的long型的变量
             str:指向字符数组的指针，转换后的字节串放在其中           
- 返回说明：无
******************************************************************/
void u32tostr(uint32_t dat,uint8_t *str) {
  int8_t temp[20];
  uint8_t i=0,j=0;
  i=0;
  while(dat){
    temp[i]=dat%10+0x30;
    i++;
    dat/=10;
  }
  j=i;
  for(i=0;i<j;i++) {
    str[i]=temp[j-i-1];
  }
  if(!i) {str[i++]='0';}
  str[i]=0;
}

/******************************************************************
- 功能描述：将一个字符串转为32位的变量，比如"1234"转为1234
- 参数说明：str:指向待转换的字符串           
- 返回说明：转换后的数值
******************************************************************/

unsigned long strtou32(unsigned char *str) {
  uint32_t  temp=0;
  uint32_t  fact=1;
  uint8_t   len=StrLength(str);
  uint8_t   i;
  for(i=len;i>0;i--) {
    temp+=((str[i-1]-0x30)*fact);
    fact*=10;
  }
  return temp;
}

/*******************************************************************************
* Function Name  : StrLength
* Description    : Returns length of string.
* Input          : - Str: Character Pointer.
* Output         : None
* Return         : String length.
*******************************************************************************/
static uint32_t StrLength(uint8_t *Str) {
  uint32_t Index = 0;

  /* Increment the Index unless the end of string */
  for(Index = 0; *Str != '\0'; Str++, Index++);

  return Index;
}

/*******************************************************************************
* Function Name  : ILI9325_DrawChar
* Description    : Draws a character on LCD.
* Input          : - Xpos: the Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Ypos: start column address.
*                  - c: pointer to the character data.
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawChar_8x16(uint16_t x, uint16_t y, uint8_t *c) {
  uint16_t  i=0,j=0,str=0;
  uint16_t  OffSet=0;
  
  OffSet = (*c - 32)*16;//寻找ASCII_Table[]中相应字符的点阵数据
          /*pAscii传过来的是该字符的ASCII码数字表示（参看ASCII表，有严格
          顺序表示），减32是因为第0~31号是控制字符，第32号为“空格”字符
          除以16是因为在ASCII_Table[]中的每个字符点阵为16个字节表示*/
  ILI9325_SetDisplayWindow(x, y, x+7, y+15);
  
  for(i=0;i<16;i++) {
    str = *(ascii_8x16 + OffSet + i);
    for(j=0;j<8;j++) {
      if(str & (0x80>>j)) {
        ILI9325_WriteGRAM(ILI9325.TextColor);
      }
      else {
        ILI9325_WriteGRAM(ILI9325.BackColor);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DisplayChar_8x16(uint16_t x, uint16_t y, uint8_t *Ascii) {
  while(*Ascii != 0){
    ILI9325_DrawChar_8x16(x,y,Ascii);
    x += 8;
    Ascii += 1;
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawChar_16x16(uint16_t x,uint16_t y,uint16_t Num){
  uint8_t   i=0,j=0;
  uint16_t  OffSet=0;
  uint16_t  str=0;
  
  OffSet = Num*32;//寻找ASCII_Table[]中相应字符的点阵数据
          /*pAscii传过来的是该字符的ASCII码数字表示（参看ASCII表，有严格
          顺序表示），减32是因为第0~31号是控制字符，第32号为“空格”字符
          除以16是因为在ASCII_Table[]中的每个字符点阵为16个字节表示*/
  ILI9325_SetDisplayWindow(x,y,x+15,y+15);
  
  for(i = 0; i < 16; i++){
    str = ((uint16_t)(*(china_16x16 + OffSet + i*2)<<8)+*(china_16x16 + OffSet + i*2+1));
    
    for(j=0;j<16;j++) {
      if(str & (0x8000>>j)) {
        ILI9325_WriteGRAM(ILI9325.TextColor);
      }
      else {
        ILI9325_WriteGRAM(ILI9325.BackColor);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DrawChar
* Description    : Draws a character on LCD.
* Input          : - Xpos: the Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Ypos: start column address.
*                  - c: pointer to the character data.
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawChar_16x24(uint16_t x, uint16_t y, uint8_t *c) {
  uint8_t   i=0,j=0;
  uint16_t  str=0;
  uint16_t  OffSet=0;
  
  OffSet = (*c - 32)*48;//寻找ASCII_Table[]中相应字符的点阵数据
          /*pAscii传过来的是该字符的ASCII码数字表示（参看ASCII表，有严格
          顺序表示），减32是因为第0~31号是控制字符，第32号为“空格”字符
          除以16是因为在ASCII_Table[]中的每个字符点阵为16个字节表示*/
  ILI9325_SetDisplayWindow(x, y, x+15, y+23);
  
  for(i=0;i<24;i++) {
    str = ((uint16_t)(*(ascii_16x24 + OffSet + i*2)<<8))+(*(ascii_16x24 + OffSet + i*2+1));
    
    for(j=0;j<16;j++) {
      if(str & (0x8000>>j)) {
        ILI9325_WriteGRAM(ILI9325.TextColor);
      }
      else {
        ILI9325_WriteGRAM(ILI9325.BackColor);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DisplayChar_16x24(uint16_t x, uint16_t y, uint8_t *Ascii) {
  while(*Ascii != 0){
    ILI9325_DrawChar_16x24(x,y,Ascii);
    x += 16;
    Ascii += 1;
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawChar_24x24(uint16_t x,uint16_t y,uint16_t Num){
  uint8_t   i=0,j=0;
  uint16_t  OffSet=0;
  uint32_t  str=0;
  
  OffSet = Num*72;//寻找ASCII_Table[]中相应字符的点阵数据
          /*pAscii传过来的是该字符的ASCII码数字表示（参看ASCII表，有严格
          顺序表示），减32是因为第0~31号是控制字符，第32号为“空格”字符
          除以16是因为在ASCII_Table[]中的每个字符点阵为16个字节表示*/
  ILI9325_SetDisplayWindow(x,y,x+23,y+23);
  
  for(i = 0; i < 24; i++){
    str = ((uint32_t)(*(china_24x24 + OffSet + i*3)<<16))+((uint16_t)(*(china_24x24 + OffSet + i*3+1)<<8))+(*(china_24x24 + OffSet + i*3+2));
    
    for(j=0;j<24;j++) {
      if(str & (0x00800000>>j)) {
        ILI9325_WriteGRAM(ILI9325.TextColor);
      }
      else {
        ILI9325_WriteGRAM(ILI9325.BackColor);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
******************************************************************************
void ILI9325_DisplayChar_24x24(uint16_t x, uint16_t y, uint8_t *Ascii) {
  while(*Ascii != 0){
    ILI9325_DrawChar_24x24(x,y,Ascii);
    x += 24;
    Ascii += 1;
  }
}
*/
/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DrawChar_24x48(uint16_t x,uint16_t y,uint8_t *c){
  unsigned char i=0,j=0;
  unsigned long str=0;
  unsigned short  OffSet=0;
  
  OffSet = (*c - 32)*144;//寻找ASCII_Table[]中相应字符的点阵数据
          /*pAscii传过来的是该字符的ASCII码数字表示（参看ASCII表，有严格
          顺序表示），减32是因为第0~31号是控制字符，第32号为“空格”字符
          除以16是因为在ASCII_Table[]中的每个字符点阵为16个字节表示*/
  ILI9325_SetDisplayWindow(x,y,x+23,y+47);
  
  for(i = 0; i < 48; i++){
    str = ((uint32_t)(*(ascii_24x48 + OffSet + i*3)<<16))+((uint16_t)(*(ascii_24x48 + OffSet + i*3+1)<<8))+(*(ascii_24x48 + OffSet + i*3+2));
    
    for(j=0;j<24;j++) {
      if(str & (0x00800000>>j)) {
        ILI9325_WriteGRAM(ILI9325.TextColor);
      }
      else {
        ILI9325_WriteGRAM(ILI9325.BackColor);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : ILI9325_DisplayChar
* Description    : Displays one character .
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..19
*                  - Column: start column address.
*                  - Ascii: character ascii code
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_DisplayChar_24x48(uint16_t x, uint16_t y, uint8_t *Ascii) {
  while(*Ascii != 0){
    ILI9325_DrawChar_24x48(x,y,Ascii);
    x += 24;
    Ascii += 1;
  }
}

/*******************************************************************************
* Function Name  : ILI9325_Bre_Line
* Description    : Bresenham 画线程序
* Input          : - x1: 指定的画线起点 x 坐标
*                  - y1: 指定的画线起点 y 坐标
*                  - x2: 指定的画线终点 x 坐标
*                  - y2: 指定的画线终点 y 坐标
*                  - color: 画线颜色
*                  - type:  类型
* Output         : None
* Return         : None
*******************************************************************************/
void ILI9325_Bre_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color,uint16_t type) {
  int16_t dx,dy,e,count = 0;
  dx=x2-x1;
  dy=y2-y1;
  
  if(dx>=0) {
    if(dy >= 0) {             // dy>=0
      if(dx>=dy) {            // 1/8 octant
        e=dy-dx/2;
        while(x1<=x2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            y1+=1;
            e-=dx;
          }
          x1+=1;
          e+=dy;
        }
      }
      else {                // 2/8 octant
        e=dx-dy/2;
        while(y1<=y2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            x1+=1;
            e-=dy;
          }
          y1+=1;
          e+=dx;
        }
      }
    }
    else {                // dy<0
      dy=-dy;             // dy=abs(dy)
      if(dx>=dy) {        // 8/8 octant
        e=dy-dx/2;
        while(x1<=x2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            y1-=1;
            e-=dx;
          }
          x1+=1;
          e+=dy;
        }
      }
      else {              // 7/8 octant
        e=dx-dy/2;
        while(y1>=y2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            x1+=1;
            e-=dy;
          }
          y1-=1;
          e+=dx;
        }
      }
    }
  }
  else {                //dx<0
    dx=-dx;             //dx=abs(dx)
    if(dy >= 0) {       // dy>=0
      if(dx>=dy) {      // 4/8 octant
        e=dy-dx/2;
        while(x1>=x2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            y1+=1;
            e-=dx;
          }
          x1-=1;
          e+=dy;
        }
      }
      else {            // 3/8 octant
        e=dx-dy/2;
        while(y1<=y2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            x1-=1;
            e-=dy;
          }
          y1+=1;
          e+=dx;
        }
      }
    }
    else {            // dy<0
      dy=-dy;         // dy=abs(dy)
      if(dx>=dy) {    // 5/8 octant
        e=dy-dx/2;
        while(x1>=x2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            y1-=1;
            e-=dx;
          }
          x1-=1;
          e+=dy;
        }
      }
      else {          // 6/8 octant
        e=dx-dy/2;
        while(y1>=y2) {
          count++;
          if(type != 0){
            if(count%2)
              ILI9325_SetPixel(x1,y1,ILI9325.BackColor);
            else
              ILI9325_SetPixel(x1,y1,color);
          }
          else
            ILI9325_SetPixel(x1,y1,color);
          
          if(e>0){
            x1-=1;
            e-=dy;
          }
          y1-=1;
          e+=dx;
        }
      }
    }
  }
}
