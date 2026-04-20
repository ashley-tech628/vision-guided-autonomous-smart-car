/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "ZW_Tools.h"
#include "swj.h"
#pragma section all "cpu0_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。
//ctrl shift  + 字体变大     ctrl  - 字体变小

uint8 image_deal[35][188];
uint8 uart_buff;

int core0_main(void)
{
	get_clk();//获取时钟频率  务必保留
	//用户在此处调用各种初始化函数等
	gtm_pwm_init(ATOM1_CH1_P33_9, 50,stree_center);

	/***电机初始化***/
    //电机：
    //1 DRV8701 电机1：PWM-21.5 DIR-21.4         电机2：PWM-21.3 DIR-21.2
    //2 Hip4082
	    gpio_init(P21_2, GPO, 0, PUSHPULL);
	    gtm_pwm_init(ATOM0_CH1_P21_3, 14000, 0);
	    gpio_init(P21_5, GPO, 0, PUSHPULL);
	    gtm_pwm_init(ATOM0_CH2_P21_4, 14000, 0); //ATOM0_CH3_P21_5
  // dianjiqudong(2000,2000);
 // while(1);
	  //  flash_read2();//读入参数
    //目前的库采集总钻风 图像最后一列为固定的黑色
	//这是由于单片机造成的，不是摄像头的问题
	mt9v03x_init();    //初始化摄像头
	seekfree_wireless_init();

	lcd_init();	//初始化IPS屏幕
    lcd_showstr(0, 0, "SEEKFREE MT9V03x");
    lcd_showstr(0, 1, "Initializing...");

	//如果屏幕没有任何显示，请检查屏幕接线

	//电机舵机初始化
  // if(flash_check(EXAMPLE_EEPROM_SECTOR, 0) || flash_check(EXAMPLE_EEPROM_SECTOR, 1) || flash_check(EXAMPLE_EEPROM_SECTOR, 2) || flash_check(EXAMPLE_EEPROM_SECTOR, 988))
  //    {
 //  eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR);
    //   }
 // flash_deal();  // 首次写数据
  systick_delay_ms(STM0, 20); //等待擦写完成
    flash_read2();
	//舵机：PWM-33.9
	//B车300Hz C车50Hz
	//PWM范围 2450-4150

	//C车50Hz
	//gtm_pwm_init(ATOM1_CH1_P33_9, 50,1200);   //750  250   1250

	//编码器初始化
	gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);
	gpt12_init(GPT12_T6, GPT12_T6INA_P20_3, GPT12_T6EUDA_P20_0);

	//按键，拨码开关初始化
	keyboard_init();
	IncPID_Init(&MOTOR_PID);
    IncPID_Init(&MOTOR2_PID);
	adc_init(ADC_0,ADC0_CH8_A8);//GPIOMODE_enum
    pit_interrupt_ms(CCU6_0, PIT_CH0, 10);
    pit_interrupt_ms(CCU6_0, PIT_CH1, 20);





    //检查当前页是否有数据，如果有数据则需要擦除整个扇区，


    //等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();
	//注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo
    //注意 从V1.1.6版本之后  printf打印的信息从串口输出具体可以学习库例程6-Printf_Demo


	while (TRUE)
	{
	 //  sendimg_binary(image_use[0],188,70,1);
        //用户在此处编写任务代码
	   interface_display();

////
//	       for (int i = 0; i < 70; i+=2)
//	     {
//	               for (int j = 0; j < 188; j+=1)
//	               image_deal[i/2][j] =image_use[i][j];
//
//	       }
// //  seekfree_sendimg_03x(UART_2, image_deal[0],94, 35);
////
////
//	  ZW_Send_Image(image_deal);
	 ///  uart_putchar(WIRELESS_UART, '2');
	//    uart_putchar(WIRELESS_UART, '1');
	//   zuodiuxianshu= flash_read(EXAMPLE_EEPROM_SECTOR, 1, uint32);
	 //  lcd_showstr(1,6,"ee");lcd_showuint8(70,6,zuodiuxianshu);//left_huan_num
	}
}








#pragma section all restore


