/*---------------------------------------------------------------------
                          驺吾图传工具函数
													
【平    台】RT1064
【编    写】满心欢喜
【联系方式】QQ：320388825 微信：LHD0617_
【最后更新】2022.03.16
【编译平台】MDK 5.28.0
【功    能】驺吾图传工具函数
【注意事项】本程序只供学习使用，未经作者许可，不得用于其它任何用途。
---------------------------------------------------------------------*/
/*包含头文件*/
#include "ZW_Tools.h"

/************************************************************
												 驺吾图传
								
【函数名称】ZW_Send_Image
【功    能】图像发送函数
【参    数】ZW_Image二值化图像数组（0或非0）的二值化图像
【返 回 值】无
【实    例】ZW_Send_Image(Image);
【注意事项】①只能传入二值化图像（0或非0）
						②.h文件中宏定义尺寸必须与上位机所填写的尺寸对应否则无法使用
						③该函数将会对图像进行重新编码再向上位机发送

************************************************************/

void ZW_Send_Image(ZW_uint8* ZW_Image)
{
	ZW_uint8 ZW_data;
	ZW_uint16 ZW_i;
	ZW_uint8 ZW_j;

	for(ZW_i = 0; ZW_i < ZW_ImgSize_H*ZW_ImgSize_W; ZW_i += 8)
	{
		ZW_data = 0;
		for(ZW_j = 0; ZW_j < 8; ZW_j++)
		{
			if(*(ZW_Image + ZW_i + ZW_j))		ZW_data |= 0x01 << (7-ZW_j);
		}
		ZW_Putchar(ZW_data);
	}
}

/************************************************************
												 驺吾图传
								
【函数名称】ZW_Send_Boundary
【功    能】发送边界函数
【参    数】ZW_Left_Boundary, ZW_Right_Boundary左右边界一维坐标数组（由上至下）
【返 回 值】无
【实    例】ZW_Send_Boundary(left_Boundary, right_Boundary);
【注意事项】①边界数组长度必须与图像高度一直。
						②每行左右边界有且仅有一个坐标点
						③左右边界必须同时传入，不可单独传输一个边界
						④最大传输字节数小于1430Byte
						传输字节数计算方法：
						图像尺寸(长乘宽)/8结尾若不足一个字节算作一个字节 + 边界信息由一个Byte存储两条边界就是2*ZW_ImgSize_H
						⑤在图像传输结束后立即传输边界信息
						⑥此函数非必须调用，若不使用此函数则仅传输图像

************************************************************/
void ZW_Send_Boundary(ZW_uint8* ZW_Left_Boundary, ZW_uint8* ZW_Right_Boundary)
{
	ZW_uint8 ZW_data;
	ZW_uint8 ZW_i,ZW_j;
	if(ZW_Left_Boundary != ZW_NULL && ZW_Right_Boundary != ZW_NULL)
	{
		for(ZW_i = 0; ZW_i < ZW_ImgSize_H; ZW_i++)
		{
			ZW_Putchar(*(ZW_Left_Boundary + ZW_i));
		}
		for(ZW_i = 0; ZW_i < ZW_ImgSize_H; ZW_i++)
		{
			ZW_Putchar(*(ZW_Right_Boundary + ZW_i));
		}
	}
}

