#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"

#include "hardware/lcd.h"
#include "driverlib/uart.h"
#include "hardware/relay.h"
#include "hardware/PCF8574.h"
#include "hardware/bmp085.h"
#include "hardware/DC_motor.h"
#include "hardware/dht11.h"
#include "hardware/Dot_Matrix.h"
#include "hardware/step_motor.h"
#include "hardware/MMA7455.h"
#include "hardware/tm1638.h"
#include "hardware/key.h"
 
//enable uart interrupt
#define UART_BUFFERED
 
void Delay(unsigned int x)
{
    unsigned int j,t;
    while(x--){
        for(j=0;j<190;j++)
			    for(t=0;t<180;t++);
        }   
}

static uint8_t read_val = 0;

u8 play[4]  = {0x7E, 0x02, 0x0D, 0xEF};
u8 prev[4]  = {0x7E, 0x02, 0x02, 0xEF};
u8 next[4]  = {0x7E, 0x02, 0x01, 0xEF};
u8 pause[4] = {0x7E, 0x02, 0x0E, 0xEF};

u8 mode_U[5] = 			{0x7E, 0x03, 0x09, 0, 0xEF};
u8 mode_FLASH[5] =  {0x7E, 0x03, 0x09, 4, 0xEF}; 
u8 mode_TF[5] = 		{0x7E, 0x03, 0x09, 1, 0xEF};	

int main(void)
{
    tContext sContext;
    tRectangle sRect;
	
		uint32_t i = 0;
	
    FPUEnable();						
    FPULazyStackingEnable();

    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

		InitConsole(3);	  
		//UART2_Int_Config();	
	
		PCF8574_I2C_GPIO_Config();
		TM1638_GPIO_Configuration();   //IO�ڳ�ʼ��	

    lcd_init();	                  //��ʼ��LCD����

		PCF8574_Single_WriteI2C(PCF8574T_E, 0xe0);  //close DC motor[0][3]  close relay[5:7]

		LCD_Clear(Black);	
		LCD_DrawRectangle(0,5, 479, 271);
		LCD_DrawRectangle(5,18, 474, 266);
		LCD_ShowString(150, 6, "--TM4C123G Platform--");  // ʵ�鿪��ƽ̨
		LCD_ShowString(150,60, "STEP9: KEYPAD testing");	
		LCD_ShowString(50, 220, "Tips: Press the keypad and note of the information on the screen");					
		TM1638Test();

		LCD_ShowString(150, 6, "--TM4C123G Platform--");  // ʵ�鿪��ƽ̨
		LCD_ShowString(150,60, "Test Complete!");		
		while(1)	
		{				
			
		}
}