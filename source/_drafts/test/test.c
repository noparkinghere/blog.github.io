#include <stdio.h>

int main(void)
{
	printf("hello world!\n");
}

//crc生成函数，并将crc存储在预先定于的数组中 
//调用方式crc16（指向数据的指针，需要校验的数据长度）
unsigned char CRC[2];//定义数组 
void crc16(unsigned char *ptr,unsigned int len) 
{ 
	unsigned long wcrc=0XFFFF;//预置16位crc寄存器，初值全部为1 
	unsigned char temp;//定义中间变量 
	int i=0,j=0;//定义计数 
	for(i=0;i<len;i++)//循环计算每个数据
	{ 
		temp=*ptr&0X00FF;//将八位数据与crc寄存器亦或 
		ptr++;//指针地址增加，指向下个数据 
		wcrc^=temp;//将数据存入crc寄存器 
		for(j=0;j<8;j++)//循环计算数据的 
		{ 
			if(wcrc&0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。
			{ 
				wcrc>>=1;//先将数据右移一位 
				wcrc^=0XA001;//与上面的多项式进行异或 
			}
			else//如果不是1，则直接移出 
			{ 
				wcrc>>=1;//直接移出
			}
		} 
	} 
		 temp=wcrc;//crc的值 
		 CRC[0]=wcrc;//crc的低八位 
		 CRC[1]=wcrc>>8;//crc的高八位 
}
