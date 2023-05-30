#include "tm1638.h"
#include "utils/uartstdio.h"	  
# include <stdlib.h>
# include <string.h>
# include <math.h>
unsigned char const tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//�����0��F����ʾ
unsigned char const keytab[]={0x01,0x02,0x10,0x0f,0x11,0x12,0x00,0x00,0x03,0x04,0x0e,0x0d,0x13,0x14,0x00,0x00,0x05,0x06,0x0c,0x0b,0x15,0x16,0x00,0x00,0x07,0x08,0x0a,0x09,0x17,0x18,00};														

u8 key_tmp=0xff;

//TM1638 STB��PF2  CLK��PK2    DIO��PK0     NEW
void delay_tim(unsigned int tim)   //8us/unit
{
	unsigned int i;
	for(;tim>0;tim--)
	 for(i=0;i<28;i++);
}

//��������ʱ����
static Delay_1ms(int counter)
{
	int i,j;
	for(i=0;i<counter;i++)
		for(j = 0; j < 4000; j++);
}



void TM1638_GPIO_Configuration(void)
{		
	//PF2 ->STB	
	ROM_SysCtlPeripheralEnable(STB_PERIPH);	  // ʹ������GPIOF
	ROM_GPIOPinTypeGPIOOutput(STB_GPIO, STB_GPIO_PIN);	//PF2 ��Ϊ���
	STB_ONOFF(STB_GPIO_PIN);
	
	//PK2 ->CLK
  ROM_SysCtlPeripheralEnable(CLK_PERIPH);	  // ʹ������GPIOF
	ROM_GPIOPinTypeGPIOOutput(CLK_GPIO, CLK_GPIO_PIN);	//PK2 ��Ϊ���
	ROM_GPIOPinTypeGPIOOutput(DIO_GPIO, DIO_GPIO_PIN);	//PK0 ��Ϊ���	
	//DIO_OUT();	
	DIO_ONOFF(DIO_GPIO_PIN);
}

void DIO_OUT() //����TM1638DIO����Ϊ�������
{
  //PK0 ->DIO
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);	//PK0 ��Ϊ���
	ROM_GPIOPinTypeGPIOOutput(DIO_GPIO, DIO_GPIO_PIN);	//PK0 ��Ϊ���		
}

void DIO_IN()  //����TM1638DIO����Ϊ��������
{
	 //PK0 ->DIO
	 ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	 ROM_GPIOPinTypeGPIOInput(DIO_GPIO, DIO_GPIO_PIN);	//PK0 ��Ϊ����	
}

void TM1638_Write(unsigned char	DATA)			//д���ݺ���
{
   unsigned char i;
   DIO_OUT();
				
   for(i=0;i<8;i++)
   {
   	//GPIO_ResetBits(GPIOF,CLK_GPIO_PIN);
		 CLK_ONOFF(0);
	  if(DATA&0X01)
		{
	    //GPIO_SetBits(GPIOB,DIO_GPIO_PIN);
			DIO_ONOFF(DIO_GPIO_PIN);
		}
	  else 
		{
	    //GPIO_ResetBits(GPIOB,DIO_GPIO_PIN);
			DIO_ONOFF(0);
		}
	  DATA>>=1;
	  //GPIO_SetBits(GPIOF,CLK_GPIO_PIN);
		CLK_ONOFF(CLK_GPIO_PIN);
	  delay_tim(1);
   }
}

unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	delay_tim(1);
	for(i=0;i<8;i++)
	{
	  temp>>=1;
	 // GPIO_ResetBits(GPIOF,CLK_GPIO_PIN);
		CLK_ONOFF(0);
		delay_tim(10);
		//if(GPIO_ReadInputDataBit(GPIOB,DIO_GPIO_PIN) == Bit_SET)
		if(ROM_GPIOPinRead(DIO_GPIO, DIO_GPIO_PIN) != 0)
	    temp|=0x80;
	  //GPIO_SetBits(GPIOF,CLK_GPIO_PIN);
		CLK_ONOFF(CLK_GPIO_PIN);
		
		delay_tim(1);
	}
	DIO_OUT();

	return temp;
}

void Write_COM(unsigned char cmd)		//����������
{
  //GPIO_ResetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(0);
	TM1638_Write(cmd);
	//GPIO_SetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(STB_GPIO_PIN);
}

unsigned char c[4];
unsigned char Read_key(void)
{
	unsigned char i,key_value=0;
	unsigned char tmp_num[4]={0,0,0,0};
	int* key;
	unsigned char temp[1] = {0};
	
   //GPIO_ResetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(0);
	TM1638_Write(0x42);
	//Delay(1);
	Delay_1ms(1);
	/*for(i=0;i<200;i++)
	delay_tim(200);*/
	for(i=0;i<4;i++)
	{
		c[i]=TM1638_Read();
		
		temp[0] = c[i];
		temp[0] = temp[0] + '0';
		UARTprintf(temp);
		temp[0] = 0;		
		//delay_tim(10);
	}
	//GPIO_SetBits(GPIOF,STB_GPIO_PIN);				//4���ֽ����ݺϳ�һ���ֽ�
	STB_ONOFF(STB_GPIO_PIN);
	for(i=0;i<4;i++)
		{
			if(c[i]!=0)
				switch(c[i])
			{
				case 0x01:tmp_num[i]=i*8+1; break;
				case 0x10:tmp_num[i]=i*8+2; break;
				case 0x02:tmp_num[i]=i*8+3; break;
				case 0x20:tmp_num[i]=i*8+4; break;
				case 0x04:tmp_num[i]=i*8+5; break;
				case 0x40:tmp_num[i]=i*8+6; break;
				case 0x08:tmp_num[i]=i*8+7; break;
				case 0x80:tmp_num[i]=i*8+8; break;
				default : tmp_num[i]=0;break;
			}
		}
		key_value=tmp_num[0]+tmp_num[1]+tmp_num[2]+tmp_num[3];   
  return (key_value);
}


void Write_DATA(unsigned char add,unsigned char DATA)
{
    Write_COM(0x44);
   // GPIO_ResetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(0);
	TM1638_Write(0xc0|add);
	TM1638_Write(DATA);
	//GPIO_SetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(STB_GPIO_PIN);
}

void Write_oneLED(unsigned char num,unsigned char flag)	//��������һ��LED������numΪ��Ҫ���Ƶ�led��ţ�flagΪ0ʱϨ�𣬲�Ϊ0ʱ����
{
	Write_DATA(num,flag);
}
void Init_TM1638(void)
{	
	unsigned char i;
	
	TM1638_GPIO_Configuration();   //IO�ڳ�ʼ��

	Write_COM(0x8a);//������Ϊȫ���ȵ�4/16
	Write_COM(0x40);
	//GPIO_ResetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(0);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
	//GPIO_SetBits(GPIOF,STB_GPIO_PIN);
	STB_ONOFF(STB_GPIO_PIN);

	DIO_OUT();
}

/****************************************************************************
* ��    �ƣ�void TM1638Test(void)
* ��    �ܣ���ʾ���˵�
* ��ڲ�������
* ���ڲ�������
* ˵    ������LCD����ʾ8LED���Բ˵�
* ���÷�����TM1638Test();
****************************************************************************/

void TM1638Test(void)
{
	int index = 0;												// ��־λ����1 or ��2��
	int num1=0;														// ����һ
	int num2=0;														// ���ֶ�
	int pre_ans = 0;											// ��ǰanswer
	static char result1[10];							// ���һ�ַ���
	static char result2[10];							// ������ַ���
	char expression[100] = {0};						// �������ʽ
	char opt[1] = "w";										// ����λ
	char equals_symbol[1] = "=";					// ������������
	int cal_result=0;											// ������
	static char cal_str_result[10];				// ����ַ���
	u8 i,j;
	u8 keyDat;
//	u8 tempcount=0;
	u8 temp_key1=0x00;
	u8 temp_key2=0x00;
	u8 temp_key3=0x00;
	
	Init_TM1638();	
	

	for(i=0;i<16;i++)
	{
	  for(j=0;j<8;j++)
		{
			Write_DATA(j<<1,tab[i]); 
			delay_tim(1000);
		}
	}
	delay_tim(100);
	
	for(j=0;j<8;j++)
	  Write_DATA(j<<1,tab[0]); 

	for(i=0;i<16;i++)
	{ i++;
	  for(j=0;j<3;j++)
		{
			Write_oneLED(i,j);
			delay_tim(1000);
		}
	}
	
	//while(tempcount<24)
	//while(1)
	temp_key1=0x00;
	temp_key2=0x00;
	temp_key3=0x00;
	
	while((temp_key1!=0xff)||(temp_key2!=0xff)||(temp_key3!=0xff))
	//while(0)
	{
		keyDat=Read_key();
		
#if 1		
		keyDat=keytab[keyDat-1];
		if(keyDat<0x1f)
		{   	//printf("%c\n",keyDat);
					//for(j=0;j<8;j++)
			Write_DATA(2,tab[keyDat&0x0f]);
			Write_DATA(0,tab[(keyDat&0xf0)>>4]);
			if(keyDat!=key_tmp)
			{
			//tempcount++;
				key_tmp=keyDat;
			}
			switch (keyDat){
				case 0x01:
					if(index==0){														// ��־��1����
						num1 = num1 * 10 + 1;										// ��1�仯
						LCD_Clear(Black);												// ����
						sprintf(result1,"%d",num1);							// ��1��ӡ
						LCD_ShowString(120, 120, result1);			// ��ӡ����1
					}else{																	// ��־��2����
						num2 = num2 * 10 + 1;										//��2�仯
						LCD_Clear(Black);												// ����
						sprintf(result2,"%d",1);								// ��ӡ���2
						strcat(expression, result2);						// ƴ�ӱ��ʽ
						LCD_ShowString(120, 120, expression);		//չʾ������ʽ
					}
					
				break;
				case 0x02:
					if(index==0){
						num1 = num1 * 10 + 2;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 2;
						LCD_Clear(Black);
						sprintf(result2,"%d",2);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x03:
					if(index==0){
						num1 = num1 * 10 + 3;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 3;
						LCD_Clear(Black);
						sprintf(result2,"%d",3);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x04:
					if(index==0){
						num1 = num1 * 10 + 4;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 4;
						LCD_Clear(Black);
						sprintf(result2,"%d",4);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x05:
					if(index==0){
						num1 = num1 * 10 + 5;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 5;
						LCD_Clear(Black);
						sprintf(result2,"%d",5);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x06:
					if(index==0){
						num1 = num1 * 10 + 6;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 6;
						LCD_Clear(Black);
						sprintf(result2,"%d",6);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x07:
				if(index==0){
						num1 = num1 * 10 + 7;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 7;
						LCD_Clear(Black);
						sprintf(result2,"%d",7);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x08:
				if(index==0){
						num1 = num1 * 10 + 8;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 8;
						LCD_Clear(Black);
						sprintf(result2,"%d",8);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				//
				case 0x09:
				if(index==0){
						num1 = num1 * 10 + 9;
						LCD_Clear(Black);
						sprintf(result1,"%d",num1);
						LCD_ShowString(120, 120, result1);
					}else{
						num2 = num2 * 10 + 9;
						LCD_Clear(Black);
						sprintf(result2,"%d",9);
						strcat(expression, result2);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x0a:
					if(index==0){
						opt[0] = '+';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x0b:
					if(index==0){
						opt[0] = '-';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x0c:
					if(index==0){
						opt[0] = '*';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x0d:
					if(index==0){
						opt[0] = '/';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x0e:
					if(index==1){
						strcat(expression, equals_symbol);
						switch(opt[0]){
							case '+':
								cal_result = num1 + num2;
								break;
							case '-':
								cal_result = num1 - num2;
								break;
							case '*':
								cal_result = num1 * num2;
								break;
							case '/':
								cal_result = num1 / num2;
								break;
							case '%':
								cal_result = num1 % num2;
								break;
							case '^':
								cal_result = (int)pow((double)num1,(double)num2);
								break;
						}
						pre_ans = cal_result;
						sprintf(cal_str_result,"%d",cal_result);
						strcat(expression, cal_str_result);
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
						index = 0;
						num1=0;
						num2=0;
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}
				break;
				case 0x0f:
						index = 0;
						num1=0;
						num2=0;
						memset(expression,'\0',sizeof(expression));
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
				break;
				case 16:
					if(index==0){
							num1 = pre_ans;
							LCD_Clear(Black);
							sprintf(result1,"%d",num1);
							LCD_ShowString(120, 120, result1);
						}else{
							num2 = pre_ans;
							LCD_Clear(Black);
							sprintf(result2,"%d",pre_ans);
							strcat(expression, result2);
							LCD_ShowString(120, 120, expression);
						}
				break;
			//
				case 0x11:
				if(index==0){
						opt[0] = '%';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x12:
				if(index==0){
						opt[0] = '^';
						strcat(expression, result1);
						strcat(expression, opt);
						index = index + 1;
						LCD_Clear(Black);
						LCD_ShowString(120, 120, expression);
					}else{
						LCD_Clear(Black);
						LCD_ShowString(120, 120, "Error input!!");
					}
				break;
				case 0x13:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x04;
				break;
				case 0x14:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x08;
				break;
				case 0x15:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x10;
				break;
				case 0x16:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x20;
				break;
				case 0x17:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x40;
				break;
				case 0x18:
				LCD_Clear(Black);
				LCD_ShowString(120, 120, "Not available key!!");
				temp_key3=temp_key3|0x80;
				break;
				
								
				default:
				break;
			}
		}
#endif
	}

}