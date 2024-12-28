#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KeyPad_Int.h"
void main(void)
{
	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	s32 num1=0;
	s32 num2=0;
	u8 nf1=0;
	u8 nf2=0;
	u8 key;
	u8 flag=0;
	u8 clr=0;
	u8 n=0;
	u8 pro='+';
	while(1)
	{
		key=No_Key;
		key=KEYPAD_GetKey();
		if(key!=No_Key)
		{
			if((num1==0)&&(key=='-'))
			{
				if(clr==1)
				{
					LCD_Clear();
					clr=0;
				}
				if(flag==0)
				{
					LCD_WriteChar(key);
					nf1=1;
				}
			}
			else if((num2==0)&&(key=='-'))
			{
				if(flag==1)
				{
					LCD_WriteChar(key);
					nf2=1;
				}
			}
			else{;}
			if((key>='0')&&(key<='9'))
			{
				if(clr==1)
				{
					LCD_Clear();
					clr=0;
				}
				if(flag==0)
				{
					n=1;
					LCD_WriteChar(key);
					num1=(num1*10)+(key-'0');
				}
				else if(flag==1)
				{
					LCD_WriteChar(key);
					num2=(num2*10)+(key-'0');
				}
				else{;}
			}
			if(((key=='/')||(key=='-')||(key=='+')||(key=='*'))&&(n==1))
			{
				flag=1;
				n=0;
				pro=key;
				LCD_WriteChar(key);
			}
			if(key=='=')
			{
				LCD_WriteChar(key);
				flag=0;
				if(nf1==1)
				{
					num1=-num1;
				}
				if(nf2==1)
				{
					num2=-num2;
				}
				if(pro=='+')
				{
					LCD_WriteNumber(num1+num2);
				}
				else if(pro=='-')
				{
					LCD_WriteNumber(num1-num2);
				}
				else if(pro=='*')
				{
					LCD_WriteNumber(num1*num2);
				}
				else if(pro=='/')
				{
					if(num2==0)
					{
						LCD_SetCursor(1,0);
						LCD_WriteSrting("wrong input");
					}
					else
					{
						LCD_WriteNumber(num1/num2);
					}
				}
				else{;}
					num1=0;
					num2=0;
					nf1=0;
					nf2=0;
					clr=1;
			}
			if(key=='c')
			{
				LCD_Clear();
				clr=0;
				num1=0;
				num2=0;
				nf1=0;
				nf2=0;
			}
		}
	}
}