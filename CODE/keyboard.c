/*
 * keyboard.c
 *
 *  Created on: 2022年5月20日
 *      Author: admin
 */


#include "headfile.h"
#include "keyboard.h"
#include "isr_config.h"
#include "isr.h"
uint32 write_buf;
uint8 huihuan_sd=320;
uint8 junsu=0;
uint8  caxie=0;
uint16  power;
uint16  line_number=0,line_number_previous=0;
extern uint16 expose_time;
extern uint8 ruku_zuobiao_hang;
extern uint8 ruku_zuobiao_lie;

uint8 dispagenum=0,dispagenum_last=0;  //显示内容
uint8 paraadjnum=9;      //参数调节项目
int8 contin=1;

uint8 c_l=2,c_r=2; //左大环2 左小环1 右小环1 右大环2
uint16 sd_fast=900;    //上限速度
uint16 clc_sd=700;   //入环岛速度
uint8 status;



//拨码开关状态变量
uint8 sw1_status;
uint8 sw2_status;

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;
uint8 key5_status = 1;

//上一次开关状态变量
uint8 key1_last_status = 1;
uint8 key2_last_status = 1;
uint8 key3_last_status = 1;
uint8 key4_last_status = 1;
uint8 key5_last_status = 1;

//开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;
uint8 key5_flag;
extern int8 th_y;

void prompt(void)
{
  static uint8 i;
  for(i=0;i<=9;i++)
         { if(i==paraadjnum)
             lcd_showstr(110,i,"*");
           else
             lcd_showstr(110,i," ");
         }
}
void dispage1(void) //第2面参数显示
{
  lcd_showstr(1,0, "Set:");  //设置速度档
  lcd_showstr(1,1, "dir:");
  lcd_showstr(1,2, "KP:");
  lcd_showstr(1,3, "KD:");
  lcd_showstr(1,4, "KT");
  lcd_showstr(1,5, "ckline:");
  lcd_showstr(1,6, "th_lu");
  lcd_showstr(1,7, "hui_r");
  lcd_showstr(1,8, "hui_l");
  lcd_showstr(1,9, "point");
}
void dispage2(void) //第2面参数显示
{
  lcd_showstr(1,0, "junsu:");  //设置速度档
  lcd_showstr(1,1, "huisd:");
  lcd_showstr(1,2, "chasu:");
  lcd_showstr(1,3, "KD:");
  lcd_showstr(1,4, "KT");
  lcd_showstr(1,5, "ckline:");
  lcd_showstr(1,6, "th_lu");
  lcd_showstr(1,7, "hui_r");
  lcd_showstr(1,8, "hui_l");
  lcd_showstr(1,9, "point");
}
void number1(void)
{
 lcd_showint8(75,0,Set);
lcd_showuint8(75,1,c_r);
lcd_showuint16(70,2,S_D5[Set][0]);
lcd_showuint16(70,3,S_D5[Set][2]);
lcd_showuint16(70,4,S_D5[Set][3]);
lcd_showuint8(75,5,check_line);//识别起跑线的行数
lcd_showuint8(75,6,xielv);
lcd_showint8(75,7,huihuan_right);
lcd_showint8(75,8,huihuan_left);
lcd_showuint8(75,9,zhongzhi);
}
void number2(void)
{
 lcd_showint8(75,0,junsu);
lcd_showuint8(75,1,huihuan_sd);
lcd_showint16(60,2,chasuxisu);
lcd_showuint16(70,3,S_D5[Set][2]);
lcd_showuint16(70,4,S_D5[Set][3]);
lcd_showuint8(75,5,check_line);//识别起跑线的行数
lcd_showuint8(75,6,xielv);
lcd_showint8(75,7,huihuan_right);
lcd_showint8(75,8,huihuan_left);
lcd_showuint8(75,9,zhongzhi);
}





//按键初始化
void keyboard_init(void)
{
    //拨码开关初始化
    gpio_init(SW1,GPI,1,PULLUP);
    gpio_init(SW2,GPI,1,PULLUP);
    gpio_init(KEY1,GPI,1,PULLUP);
    gpio_init(KEY2,GPI,1,PULLUP);
    gpio_init(KEY3,GPI,1,PULLUP);
    gpio_init(KEY4,GPI,1,PULLUP);
}
   // gpio_init(KEY5,GPI,0,PULLUP);


    //电池电压
   // adc_init(POWER_ADC_MOD,POWER_ADC_PIN);




  void  key_operate(void)//获取拨码开关状态
  {

        sw1_status = gpio_get(SW1);
        sw2_status = gpio_get(SW2);

        //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
        //保存按键状态
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;
        key5_last_status = key5_status;
        //读取当前按键状态
        key1_status = gpio_get(KEY1);
        key2_status = gpio_get(KEY2);
        key3_status = gpio_get(KEY3);
        key4_status = gpio_get(KEY4);
        //key5_status = gpio_get(KEY5);

        //检测到按键按下之后  并放开置位标志位
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;
        //if(key5_status && !key5_last_status)    key5_flag = 1;

        //标志位置位之后，可以使用标志位执行自己想要做的事件
        if(key1_flag)
        {
         key1_flag = 0;//使用按键之后，应该清除标志位
         // lcd_showuint16(70,4,1);
         key1_function();
         eeprom_erase_sector(EXAMPLE_EEPROM_SECTOR);
         flash_deal();
         systick_delay_ms(STM0, 20);

        }

        else if(key2_flag)
        {
            key2_flag = 0;//使用按键之后，应该清除标志位
            //lcd_showuint16(70,4,2);
         key2_function();

        }

        else if(key3_flag)
        {
            key3_flag = 0;//使用按键之后，应该清除标志位
            //lcd_showuint16(70,4,3);
         key3_function();
        }

        else if(key4_flag)
        {
         contin=1;
           key4_flag = 0;//使用按键之后，应该清除标志位
           //lcd_showuint16(70,4,4);
         key4_function();
        }


    }



void interface_display(void)
{

            key_operate();

       if(dispagenum==0) //显示第一页，图像显示及相关参数调节
       {
        lcd_displayimage032_zoom(mt9v03x_image[0], 188, 70, 128, 70);
        lcd_showstr(1,4, "left");
        lcd_showint16(70,4,left_num);
        lcd_showstr(1,5, "right");
        lcd_showint16(70,5,right_num);
        lcd_showstr(1,6, "AD_l:");
        lcd_showuint16(70,6,123);
        lcd_showstr(1,7, "AD_m:");
        lcd_showuint16(70,7,123);
        lcd_showstr(1,8, "po");
        lcd_showuint16(70,8,poer_flag);
        lcd_showstr(1,9, "ex_time");
        lcd_showuint16(70,9,expose_time);
        }
          else if(dispagenum==1) //显示小车控制参数及调节
       {

     lcd_displayimage032_zoom2(image_use[0], 188, 70, 128, 70);
     lcd_showstr(1,4,"lh");lcd_showuint8(20,4,left_huan_num);//left_huan_num
     lcd_showstr(1,5,"rh");lcd_showuint8(20,5,right_huan_num);//right_huan_num
     lcd_showstr(1,6,"zuo");lcd_showuint8(20,6,zuodiuxianshu);//zuodiuxianshu
     lcd_showstr(1,7,"you");lcd_showuint8(20,7,youdiuxianshu);//youdiuxianshu baihei_flag
     lcd_showstr(1,8 ,"LA");lcd_showuint8(20,8,Left_Add_num);
     lcd_showstr(1,9,"RA");lcd_showuint8(20,9,Right_Add_num);
     lcd_showstr(50,5,"w93");lcd_showuint16(70,5,sousuojieshuhang);
     lcd_showstr(50,6,"par");lcd_showuint8(80,6,park_flag);
     lcd_showstr(50,7,"star");lcd_showuint8(80,7, star_lineflag);
     lcd_showstr(50,8,"ri");lcd_showuint8(80,8,youhuihuan_flag);//white_num_col[93]
     lcd_showstr(50,9,"sd5");lcd_showuint16(70,9,S_D5_Duty);
    // lcd_showstr(50,9,"yhu");lcd_showint16(80,youhuihuan_flag);

        }
        else if(dispagenum==2) //显示小车控制参数及调节
       {
         number1();
         dispage1();
          prompt();
        }
        else if(dispagenum==3) //显示小车控制参数及调节
              {
                number2();
                dispage2();
                 prompt();
               }
}



void  key1_function(void)
{
    dispagenum_last=dispagenum;
    dispagenum++;
     // if(dispagenum==3)
    //      caxie=1;
      if(dispagenum>3)
      dispagenum=0;
      if(dispagenum_last==3&&dispagenum==0&&caxie)
      {
     //
      caxie=0;
      }
      lcd_clear(WHITE);
}

 void  key2_function(void)
 {
      if(dispagenum==0)  //参数显示
      {
            if(paraadjnum==9) //调节直道时舵机KP +
       {
          expose_time += 10;
          set_exposure_time(MT9V03X_COF_UART,expose_time);
       }
      }

                else  if(dispagenum==2)  //参数显示
            {

               if(paraadjnum==0)
               {
               Set+=1;
               if(Set>9)
                 Set=9;
               }
               else    if(paraadjnum==1) //调节直道时舵机KP +
              {
                   c_r+=1;
                if(c_r>2)
                    c_r=2;

              }
              else if(paraadjnum==2) //调节直道时舵机KD+
              {
                  S_D5[Set][0]+=1;
              }
              else if(paraadjnum==3) //调节小弯时舵机KP+
              {

                  S_D5[Set][2]+=5;
              }
              else if(paraadjnum==4) //调节小弯时舵机KD+
              {
                  S_D5[Set][3]+=5;
              }
              else if(paraadjnum==5) //调节大弯时舵机KP+
              {
                  check_line+=1;
              }
              else if(paraadjnum==6) //调节大弯时舵机KD+
              {
                  xielv+=1;
              }
              else if(paraadjnum==7) //调节大弯时舵机KD+
              {
                  huihuan_right+=1;
              }
              else if(paraadjnum==8) //调节大弯时舵机KD+
              {
                  huihuan_left+=1;
              }
              else if(paraadjnum==9) //调节大弯时舵机KD+
              {
                  zhongzhi+=1;
              }

           }
                else  if(dispagenum==3)  //参数显示
                            {

                               if(paraadjnum==0)
                               {
                               junsu+=1;
                               if(junsu>1)
                                   junsu=1;
                               }
                               else    if(paraadjnum==1) //调节直道时舵机KP +
                              {
                                   huihuan_sd+=10;
                                if(huihuan_sd>400)
                                    huihuan_sd=400;

                              }
                              else if(paraadjnum==2) //调节直道时舵机KD+
                              {
                                  chasuxisu+=5;
                              }
                              else if(paraadjnum==3) //调节小弯时舵机KP+
                              {

                                  S_D5[Set][2]+=1;
                              }
                              else if(paraadjnum==4) //调节小弯时舵机KD+
                              {
                                  S_D5[Set][3]+=1;
                              }
                              else if(paraadjnum==5) //调节大弯时舵机KP+
                              {
                                  check_line+=1;
                              }
                              else if(paraadjnum==6) //调节大弯时舵机KD+
                              {
                                  xielv+=1;
                              }
                              else if(paraadjnum==7) //调节大弯时舵机KD+
                              {
                                  huihuan_right+=1;
                              }
                              else if(paraadjnum==8) //调节大弯时舵机KD+
                              {
                                  huihuan_left+=1;
                              }
                              else if(paraadjnum==9) //调节大弯时舵机KD+
                              {
                                  zhongzhi+=1;
                              }

                           }

  }
 void  key3_function(void)
 {

               if(dispagenum==0)  //参数显示
                  {
                        if(paraadjnum==9) //调节直道时舵机KP +
                   {
                      expose_time-=10;
                      set_exposure_time(MT9V03X_COF_UART,expose_time);
                   }
                  }
            else  if(dispagenum==2)  //参数显示
           {
                       if(paraadjnum==0)
                              {
                              Set-=1;
                              if(Set<=0)
                                Set=0;
                              }
                              else    if(paraadjnum==1) //调节直道时舵机KP +
                             {
                                  c_r-=1;
                               if(c_r<=1)
                                   c_r=1;

                             }
                             else if(paraadjnum==2) //调节直道时舵机KD+
                             {
                                 S_D5[Set][0]-=1;
                                 if(S_D5[Set][0]<=1)S_D5[Set][0]=1;
                             }
                             else if(paraadjnum==3) //调节小弯时舵机KP+
                             {

                                 S_D5[Set][2]-=5;
                                 if(S_D5[Set][2]<=1)S_D5[Set][2]=1;
                             }
                             else if(paraadjnum==4) //调节小弯时舵机KD+
                             {
                                 S_D5[Set][3]-=5;
                                 if(S_D5[Set][3]<=1)S_D5[Set][3]=1;
                             }
                             else if(paraadjnum==5) //调节大弯时舵机KP+
                             {
                                 check_line-=1;
                             }
                             else if(paraadjnum==6) //调节大弯时舵机KD+
                             {
                                 xielv-=1;
                             }
                             else if(paraadjnum==7) //调节大弯时舵机KD+
                             {
                                 huihuan_right-=1;
                                 if(huihuan_right<=0)huihuan_right=0;
                             }
                             else if(paraadjnum==8) //调节大弯时舵机KD+
                             {
                                 huihuan_left-=1;
                                 if(huihuan_left<=0)huihuan_left=0;
                             }
                             else if(paraadjnum==9) //调节大弯时舵机KD+
                             {
                                 zhongzhi-=1;
                                 if(zhongzhi<70)zhongzhi=70;
                             }
           }
            else  if(dispagenum==3)  //参数显示
                       {
                                   if(paraadjnum==0)
                                          {
                                          junsu-=1;
                                          if(Set<=0)
                                              junsu=0;
                                          }
                                          else    if(paraadjnum==1) //调节直道时舵机KP +
                                         {
                                              huihuan_sd-=10;
                                           if(huihuan_sd<=300)
                                               huihuan_sd=300;

                                         }
                                         else if(paraadjnum==2) //调节直道时舵机KD+
                                         {
                                             chasuxisu-=5;
                                             if(chasuxisu<=0)chasuxisu=0;
                                         }
                                         else if(paraadjnum==3) //调节小弯时舵机KP+
                                         {

                                             S_D5[Set][2]-=5;
                                             if(S_D5[Set][2]<=1)S_D5[Set][2]=1;
                                         }
                                         else if(paraadjnum==4) //调节小弯时舵机KD+
                                         {
                                             S_D5[Set][3]-=1;
                                             if(S_D5[Set][3]<=1)S_D5[Set][3]=1;
                                         }
                                         else if(paraadjnum==5) //调节大弯时舵机KP+
                                         {
                                             check_line-=1;
                                         }
                                         else if(paraadjnum==6) //调节大弯时舵机KD+
                                         {
                                             xielv-=1;
                                         }
                                         else if(paraadjnum==7) //调节大弯时舵机KD+
                                         {
                                             huihuan_right-=1;
                                             if(huihuan_right<=0)huihuan_right=0;
                                         }
                                         else if(paraadjnum==8) //调节大弯时舵机KD+
                                         {
                                             huihuan_left-=1;
                                             if(huihuan_left<=0)huihuan_left=0;
                                         }
                                         else if(paraadjnum==9) //调节大弯时舵机KD+
                                         {
                                             zhongzhi-=1;
                                             if(zhongzhi<70)zhongzhi=70;
                                         }
                       }

  }

 void  key4_function(void)
 {
             if(dispagenum==0)
             {
                paraadjnum=9;
                prompt();
             }
            else if(dispagenum==2) //参数显示
            {   paraadjnum++;
                if(paraadjnum>9) paraadjnum=0;
                prompt();
            }
            else if(dispagenum==3) //参数显示
            {   paraadjnum++;
                if(paraadjnum>9) paraadjnum=0;
                prompt();
            }

   }

 void   flash_read2()
 {          chasuxisu =flash_read(EXAMPLE_EEPROM_SECTOR, 983, int16);
             huihuan_sd=flash_read(EXAMPLE_EEPROM_SECTOR, 984, uint8);
             junsu=flash_read(EXAMPLE_EEPROM_SECTOR, 985, uint8);
             expose_time=flash_read(EXAMPLE_EEPROM_SECTOR, 986, uint16);
             Set=flash_read(EXAMPLE_EEPROM_SECTOR, 987, uint8);
             c_r= flash_read(EXAMPLE_EEPROM_SECTOR, 988, uint8);
             S_D5[0][0]=flash_read(EXAMPLE_EEPROM_SECTOR,989, uint8);
             S_D5[0][2]=flash_read(EXAMPLE_EEPROM_SECTOR,990, uint8);
             S_D5[0][3]=flash_read(EXAMPLE_EEPROM_SECTOR,991, uint8);
             S_D5[1][0]=flash_read(EXAMPLE_EEPROM_SECTOR,992, uint8);
             S_D5[1][2]=flash_read(EXAMPLE_EEPROM_SECTOR,993, uint8);
             S_D5[1][3]=flash_read(EXAMPLE_EEPROM_SECTOR,994, uint8);
             S_D5[2][0]=flash_read(EXAMPLE_EEPROM_SECTOR,995, uint8);
             S_D5[2][2]=flash_read(EXAMPLE_EEPROM_SECTOR,996, uint8);
             S_D5[2][3]=flash_read(EXAMPLE_EEPROM_SECTOR,997, uint8);
             S_D5[3][0]=flash_read(EXAMPLE_EEPROM_SECTOR,998, uint8);
             S_D5[3][2]=flash_read(EXAMPLE_EEPROM_SECTOR,999, uint8);
             S_D5[3][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1000, uint8);
             S_D5[4][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1001, uint8);
             S_D5[4][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1002, uint8);
             S_D5[4][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1003, uint8);
             S_D5[5][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1004, uint8);
             S_D5[5][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1005, uint8);
             S_D5[5][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1006, uint8);
             S_D5[6][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1007, uint8);
             S_D5[6][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1008, uint8);
             S_D5[6][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1009, uint8);
             S_D5[7][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1010, uint8);
             S_D5[7][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1011, uint8);
             S_D5[7][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1012, uint8);
             S_D5[8][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1013, uint8);
             S_D5[8][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1014, uint8);
             S_D5[8][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1015, uint8);
             S_D5[9][0]=flash_read(EXAMPLE_EEPROM_SECTOR,1016, uint8);
             S_D5[9][2]=flash_read(EXAMPLE_EEPROM_SECTOR,1017, uint8);
             S_D5[9][3]=flash_read(EXAMPLE_EEPROM_SECTOR,1018, uint8);
             check_line=flash_read(EXAMPLE_EEPROM_SECTOR,1019, uint8);
             xielv=flash_read(EXAMPLE_EEPROM_SECTOR,1020, uint8);
             huihuan_right=flash_read(EXAMPLE_EEPROM_SECTOR,1021,uint8);
             huihuan_left =flash_read(EXAMPLE_EEPROM_SECTOR,1022,uint8);
             zhongzhi=flash_read(EXAMPLE_EEPROM_SECTOR,1023,uint8);


 }

 void   flash_deal()
 {

               write_buf= chasuxisu;
              eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 983, &chasuxisu);
            write_buf = huihuan_sd;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 984, &write_buf);
            write_buf = junsu;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 985, &write_buf);
            write_buf=expose_time;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 986, &write_buf);
            write_buf = Set;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 987, &write_buf);
            write_buf = c_r;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 988, &write_buf);

            write_buf =  S_D5[0][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 989, &write_buf);
            write_buf =  S_D5[0][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 990, &write_buf);
            write_buf =  S_D5[0][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 991, &write_buf);

            write_buf =  S_D5[1][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 992, &write_buf);
            write_buf =  S_D5[1][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 993, &write_buf);
            write_buf =  S_D5[1][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 994, &write_buf);

            write_buf =  S_D5[2][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 995, &write_buf);
            write_buf =  S_D5[2][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 996, &write_buf);
            write_buf =  S_D5[2][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 997, &write_buf);

            write_buf =  S_D5[3][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 998, &write_buf);
            write_buf =  S_D5[3][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 999, &write_buf);
            write_buf =  S_D5[3][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1000, &write_buf);

            write_buf =  S_D5[4][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1001, &write_buf);
            write_buf =  S_D5[4][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1002, &write_buf);
            write_buf =  S_D5[4][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1003, &write_buf);

            write_buf =  S_D5[5][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1004, &write_buf);
            write_buf =  S_D5[5][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1005, &write_buf);
            write_buf =  S_D5[5][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1006, &write_buf);

            write_buf =  S_D5[6][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1007, &write_buf);
            write_buf =  S_D5[6][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1008, &write_buf);
            write_buf =  S_D5[6][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1009, &write_buf);

            write_buf =  S_D5[7][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1010, &write_buf);
            write_buf =  S_D5[7][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1011, &write_buf);
            write_buf =  S_D5[7][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1012, &write_buf);

            write_buf =  S_D5[8][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1013, &write_buf);
            write_buf =  S_D5[8][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1014, &write_buf);
            write_buf =  S_D5[8][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1015, &write_buf);

            write_buf =  S_D5[9][0];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1016, &write_buf);
            write_buf =  S_D5[9][2];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1017, &write_buf);
            write_buf =  S_D5[9][3];
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1018, &write_buf);

            write_buf =  check_line;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1019, &write_buf);
            write_buf =  xielv;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1020, &write_buf);
            write_buf =  huihuan_right;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1021, &write_buf);
            write_buf =  huihuan_left;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1022, &write_buf);
            write_buf =  zhongzhi;
            eeprom_page_program(EXAMPLE_EEPROM_SECTOR, 1023, &write_buf);

 }


