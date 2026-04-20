/*
 * control.c
 *
 *  Created on: 2022年5月21日
 *      Author: admin
 */

#include "headfile.h"
#include "isr.h"
uint8 ruku_zuobiao_hang_jubu=0;
uint8 ruku_zuobiao_hang=0;
uint8 ruku_zuobiao_lie=0;
uint8 zhidao_juli=0;
uint8 chujie=0;
int chasuxisu=280;  //电机差速系数
float angle=0;
uint8 po=0;
int Max_Speed = 9500;
extern uint8 left_huan_num,right_huan_num;
extern uint8 sousuojieshuhang;//搜索结束行
uint8 cnt=0;
float K1 =0.3;//k1为加速度计计算出角度占的比例，越大越受速度影响，小了动态效果不好,改为3和7 计算速度快
float Accel_Y,Gyro_Y,Accel_X,Accel_Z;
float K2 =0.027;
uint8 s=0,stop=0,poer_flag2=0,poer_flag=0,poer2=0;
uint8 left_whitenum=0,right_whitenum=0;int8 speed_yingshe=0;
uint8 car_gogogo=0;
/***编码器相关变量***/
int left_num,right_num,LeftOut,RightOut,left_zheng_ma=0,right_zheng_ma=0,left_fan_ma,right_fan_ma;
int32   MOTOR_Duty=0;
int S_D5_Duty,S_D5_Duty2;
int chasuzuo=0;//差速左
int chasuyou=0;//差速右
int32 angle2=0;
float x,j;//舵机打脚
int32 Target_Speed1=0,Target_Speed2=0;
float piancha;//舵机偏差   通过摄像头中线处理得到
int8 Set=3;
int8 lock_flag=0;
float g_fSpeedControlOutNew=10000;   //pid算出的速度
float g_fSpeedControlIntegral;   //pid速度积分部分
float Real_speed=0;//现实生活中的速度
int g_nRightMotorPulseSigma;//右边总脉冲
int g_nLeftMotorPulseSigma;//左边总脉冲
uint8 leijia_flag=0,leijia_flag2=0;//编码器累加标志
int left_leijia=0,right_leijia=0;
int left_leijia2=0,right_leijia2=0,right_leijia_por=0,tingche_leijia_por=0;
int g_fCarSpeed=0;//小车实际速度

uint8 zhongzhi=93;
int tingche_flag=0,tingche_flag2=1;//停车标志
int stop_flag=0;//驱动断电标志


int Set_Speed1=370;
int Set_Speed2=300;
int you_speed=0;
int zuo_speed=0;
int jiasu_part=0;

const uint8 left[70]={
 93,93,93,93,93,92,92,92,92,92
,91,91,91,91,91,90,90,90,90,89
,89,89,89,88,88,88,88,87,87,87
,87,87,86,86,86,86,86,85,85,85
,85,84,84,84,84,83,83,83,83,83
,82,82,82,82,81,81,81,81,80,80
,80,80,80,79,79,79,79,78,78,78
};
const uint8 right[70]
                  ={
93,93,93,93,93,100,101,101,101,102,
102,102,103,103,103,103,104,104,104,105,
105,105,105,106,106,106,107,107,107,108,
108,108,108,109,109,109,109,110,110,110,
110,111,111,111,111,111,112,112,112,112,
113,113,113,113,114,114,114,114,115,115,
115,115,116,116,116,116,117,117,117,117
};






void proess()//处理流程
    {
          Ostu();
          //my_adapt_threshold(uint8 *image, uint16 col, uint16 row)
    //SignalProcess_grayfine_fill();
          if(car_gogogo==0)
         {

           leijia_flag2=1;
          if(c_r==2)//zuo出库
           pwm_duty(ATOM1_CH1_P33_9,stree_max-10);
        else if(c_r==1) //zuo出库
          pwm_duty(ATOM1_CH1_P33_9,stree_min+10);
          dianjiqudong(6000,6000);
          }

         if(car_gogogo)
          {

            po=adc_mean_filter(ADC_0, ADC0_CH8_A8, ADC_12BIT, 2);

                 if(po<=100)
                {
                 poer++;
                if(poer>=3)
                 {
                 time11=0;
                 poer_flag=1;
                uart_putchar(WIRELESS_UART, '9');
                         uart_putchar(WIRELESS_UART, '1');
                         uart_putchar(WIRELESS_UART, ' ');

                 }
                if(poer>10)poer=10;
                }
                else
                 poer=0;
             if(poer_flag)
             {
                 leijia_flag2=1;

         //       three_cross=0;
                star_lineflag=0;
                right_huan_num=0;
                left_huan_num=0;
            }

                  if(!poer_flag&&sousuojieshuhang<16)
                    check_starting_line();


                   if(star_lineflag)
                   {
                   three_cross=0;
                   right_huan_num=0;
                   left_huan_num=0;
                   }
              if(star_lineflag&&park_flag!=2&&time5>=30)//50
              {
                  star_lineflag=0;
                  uart_putchar(WIRELESS_UART, '5');
                  uart_putchar(WIRELESS_UART, '5');
                  uart_putchar(WIRELESS_UART, ' ');
                  time5=0;
                  time6=0;
                  time7=0;
                 park_flag++;



                if(park_flag>=2){park_flag=2; }
              }

                if((park_flag==0||park_flag==1))
                 {

                     Center_line_deal();
                     you_huihuan();
                     zuo_huihuan();
                     youhuandao();
                     zuohuandao();
                     speed_get();
                     Mid_Line_Repair(sousuojieshuhang);
//                    if(time5<=30)
//                    Point= center [10]+center[12]+center[14] /3;
//                    else
                    Point=Point_Weight();
                    S_D5_Duty = PlacePID_Control(&S_D5_PID, zhongzhi, Point);

                    //S_D5_Duty=Turn_Ctl_fuzzy(Point);
                    if(chujie==0)
                    pwm_duty(ATOM1_CH1_P33_9, S_D5_Duty);


                   if(sousuojieshuhang>65&&speed_yingshe<5)
                   {
                       chujie=1;
                   }


                 }

                  else  if(park_flag==2)
                  {

                       ruku_handle();





                      if(c_r==2&&tingche_flag==1)
                      {
                      pwm_duty(ATOM1_CH1_P33_9,stree_max-5);//右进库
                      }
                      else   if(c_r==1&&tingche_flag==1)
                      {
                      pwm_duty(ATOM1_CH1_P33_9,stree_min+5);//左进库
                      }

                  }


             if(time>1000)
             {time=1000;}

             if(time1>1000)
             {time1=1000;}

             if(time11>1000)
             {time11=1000;}

             if(time2>1000)
             {time2=1000;}

             if(time22>1000)
             {time22=1000;}

             if(time3>1000)
             {time3=1000;}

             if(time4>1000)
             {time4=1000;}
             if(time5>2000)
             {time5=2000;}
          }

   }
void GetMotorPulse(void)//编码器脉冲100ms计算一次
        {
        g_nRightMotorPulseSigma  =  right_zheng_ma - right_fan_ma ;
        g_nLeftMotorPulseSigma  =  left_zheng_ma - left_fan_ma;
        right_zheng_ma=0;
        right_fan_ma=0;
        left_zheng_ma=0;
        left_fan_ma=0;
    }

void SpeedControl(void)//速度控制
    {
    //if(right_huan_num==0&&left_huan_num==0)
    S_D5_Duty2=(S_D5_Duty-stree_center)*chasuxisu/100;   //x为差速系数/100
/***停车部分***/
    if(S_D5_Duty2>230)
        S_D5_Duty2=230;
    else if(S_D5_Duty2<=-230)
        S_D5_Duty2=-230;

      if(c_r==2&&tingche_flag==1)
      {
      S_D5_Duty2=250;Set_Speed2=500;
      if(tingche_flag2==1)
          {S_D5_Duty2=250;Set_Speed2=0;}
         if(right_num<20||left_num<20)
         {
        S_D5_Duty2=0;Set_Speed2=0;
         }
      }
      else  if(c_r==1&&tingche_flag==1)
      {
      S_D5_Duty2=-250;Set_Speed2=500;//左进库
      if(tingche_flag2==1)
       {S_D5_Duty2=-250;Set_Speed2=0;}
        if(right_num<20||left_num<20)
          {
         S_D5_Duty2=0;Set_Speed2=0;
          }
      }
       /***停车部分结束***/

    if(S_D5_Duty2>=10)
    {
    you_speed=Set_Speed2;//Set_Speed2
    zuo_speed=Set_Speed2-S_D5_Duty2;
    }
    else
    {
    zuo_speed=Set_Speed2;
    you_speed=Set_Speed2+S_D5_Duty2;
    }


    Target_Speed1 = PID_Cascade(&MOTOR_PID,left_num,zuo_speed);//speed_setSet_Speed2//S_D5_Duty2
    Target_Speed2 = PID_Cascade2(&MOTOR2_PID,right_num,you_speed);//S_D5_DutyS_D5_Duty2//S_D5_Duty2
    //Target_Speed1+=PID_Realize(&MOTOR_PID,(left_num+right_num)/2, Set_Speed2);

    if(Target_Speed1>Max_Speed)Target_Speed1=Max_Speed;
    else if(Target_Speed1<-Max_Speed)Target_Speed1=-Max_Speed;

    if(Target_Speed2>Max_Speed)Target_Speed2=Max_Speed;
    else if(Target_Speed2<-Max_Speed)Target_Speed2=-Max_Speed;

                      dianjiqudong(Target_Speed1,Target_Speed2);

    }




void chasu(float x)//过弯差速    去学校更差速系数chasuxisu  越小差速越明显 最小为1
    {
      if(x>0)
      {
        chasuzuo=MOTOR_Duty*x/chasuxisu;//-
        chasuyou=-0.9*MOTOR_Duty*x/chasuxisu;//+
      }
      else
      {
        chasuyou=MOTOR_Duty*(-x)/chasuxisu;///////+
        chasuzuo=-0.9*MOTOR_Duty*(-x)/chasuxisu;//////-
      }

    }



void dianjiqudong(int speed1,int speed2)//电机驱动函数     去学校修改正反和y1  y2
    {
      if(speed1>=0)
      {
          gpio_set(P21_2, 1);
         pwm_duty(ATOM0_CH1_P21_3,speed1+580);


      }
      else if(speed1<0)
        {
            gpio_set(P21_2, 0);
           pwm_duty(ATOM0_CH1_P21_3,abs(speed1-580));
        }
      if(speed2>=0)
          {

          gpio_set(P21_5, 1);
           pwm_duty(ATOM0_CH2_P21_4,speed2+650);
          }
          else if(speed2<0)
            {
             gpio_set(P21_5, 0);
             pwm_duty(ATOM0_CH2_P21_4,abs(speed2-650));
            }

    }
void read_1Ms_pulse(void)//脉冲数读取10ms    去学校测试几ms合适
    {
       right_num=gpt12_get(GPT12_T6); //保存脉冲计数器计算值右

       left_num=-gpt12_get(GPT12_T4);


        if(leijia_flag2==1)   //和倒库时计算距离
       {

         right_leijia2+=right_num;
          if(right_leijia2>4500)
          {
          car_gogogo=1;
          time=0;
          }
       }
               if(poer_flag)
                {
                    right_leijia_por+=right_num;
                     if(right_leijia_por>18500)
                              {
                             poer_flag=0;
                               right_leijia_por=0;
                               leijia_flag2=0;
                              }
                }
                else
                    right_leijia_por=0;

                         if(tingche_flag)
                          {
                              tingche_leijia_por+=right_num;
                               if(tingche_leijia_por>9000)
                                {
                                   tingche_flag2=1;
                                   uart_putchar(WIRELESS_UART, 'o');
                                    uart_putchar(WIRELESS_UART, 'k');
                                // right_leijia_por=0;
                              //   leijia_flag2=0;
                                }
                          }
                          else
                              tingche_leijia_por=0;




          if(g_fSpeedControlOutNew>=0)   //判断正反(正) 0
          {
            right_zheng_ma= right_zheng_ma+right_num;
          }
         else             //   (反)
           {
            right_fan_ma=right_fan_ma+right_num;
           }

          gpt12_clear(GPT12_T6);
          gpt12_clear(GPT12_T4);
    }


//float icm_angle(int16 icm_acc_x, int16 icm_acc_z, int16 icm_gyro_y) //获取陀螺仪角度  用不到
//{
//
//
//
//      Gyro_Y=icm_gyro_y;
//      Accel_X=icm_acc_x;
//      Accel_Z=icm_acc_z;
//
//                        if(Gyro_Y>32768)  Gyro_Y-=65536;                       //数据类型转换  也可通过short强制类型转换
//                        if(Accel_X>32768) Accel_X-=65536;                      //数据类型转换
//                        if(Accel_Z>32768) Accel_Z-=65536;                      //数据类型转换
//
//                        Accel_Y=atan2(Accel_X,Accel_Z)*180/3.14159265;                 //加速度计计算倾角
//                        Gyro_Y=Gyro_Y/16.4;    //Angle = gyro * dt   dt是采样时间越短积分值越准确
//
//                        angle2 = K1 * Accel_Y+ (1-K1) * (angle2 + Gyro_Y * K2);
//
//
//}

void speed_get()
{


    int y=0;
    left_whitenum=0;
    right_whitenum=0;

//
//    if(Set==0)Set_Speed1=350;
//  else if(Set==1)Set_Speed1=360;
//  else if(Set==2)Set_Speed1=370;
//  else if(Set==3)Set_Speed1=380;
//  else if(Set==4)Set_Speed1=390;
//  else if(Set==5)Set_Speed1=400;
//  else if(Set==6)Set_Speed1=410;
//  else if(Set==7)Set_Speed1=420;
// else if(Set==8)Set_Speed1=430;
//  else if(Set==9)Set_Speed1=440;

    if(Set==0)Set_Speed1=510;
  else if(Set==1)Set_Speed1=520;
  else if(Set==2)Set_Speed1=560;
  else if(Set==3)Set_Speed1=570;
  else if(Set==4)Set_Speed1=580;
  else if(Set==5)Set_Speed1=590;
  else if(Set==6)Set_Speed1=600;
  else if(Set==7)Set_Speed1=610;
  else if(Set==8)Set_Speed1=620;
  else if(Set==9)Set_Speed1=630;





    for(y=69;y>=0;y--)
    {
      if(image_use[y][left[y]]==0)
      {
        break;
      }
      else
      {
      left_whitenum++;
      }
    }
    for(int y=69;y>=0;y--)
   {
    if(image_use[y][right[y]]==0)
     {
       break;
     }
     else
     {
     right_whitenum++;
     }
   }

    if(left_whitenum<right_whitenum)
        speed_yingshe=left_whitenum;
    else
        speed_yingshe=right_whitenum;
//    if(speed_yingshe-30>=0)
//        speed_yingshe=speed_yingshe-30;
//    else
//        speed_yingshe=0;
   //zhidao_juli= 0.0139*speed_yingshe*speed_yingshe-1.4392*speed_yi ngshe+64.5775;//二次拟合
   // speed_yingshe=whitenum;
   // if(speed_yingshe<=30)speed_yingshe=30;
    zhidao_juli=0.001*(float)speed_yingshe*speed_yingshe*speed_yingshe -0.0603*(float)speed_yingshe*speed_yingshe+1.6174 *(float)speed_yingshe-2.9669;
    if(zhidao_juli<=1)zhidao_juli=1;
    jiasu_part=0.0020854*zhidao_juli*zhidao_juli;
    if(chujie==1||tingche_flag)
    {
        Set_Speed2=0;
    }
    else
    {
                    if(junsu==0)
                    {
                        if(left_huan_num==1
           ||right_huan_num==1||left_huan_num==2
               ||right_huan_num==2
               ||left_huan_num==3
                           ||right_huan_num==3)
           Set_Speed2=Set_Speed1-Set_Speed1*0.15;

       else   if(three_cross1||three_cross)
       {     //if(Set_Speed1<=530)
             Set_Speed2=Set_Speed1-Set_Speed1*0.25;
             //else  Set_Speed2=530;
       }
       else   if(poer_flag)//(||star_lineflag&&park_flag==1)
                   Set_Speed2=Set_Speed1-Set_Speed1*0.45;
                   //Set_Speed2=Set_Speed1-Set_Speed1*0.50;
       else  if(lefthuihuan_flag==1||youhuihuan_flag==1)
          Set_Speed2=Set_Speed1-Set_Speed1*0.1;
       else  if(lefthuihuan_flag==2||youhuihuan_flag==2)
                                      Set_Speed2=Set_Speed1-Set_Speed1*0.15;
       else
                        Set_Speed2=Set_Speed1+jiasu_part;
                    }
                    else
                    {
                        if(left_huan_num==1
                                ||right_huan_num==1||left_huan_num==2
                                    ||right_huan_num==2
                                    ||left_huan_num==3
                                                ||right_huan_num==3)
                                Set_Speed2=Set_Speed1-Set_Speed1*0.1;
                             //   else   if (zuodiuxianshu>15&&youdiuxianshu>15&&zhidao_juli<50)
                             //   Set_Speed2=Set_Speed1-Set_Speed1*0.7;
                            else   if(three_cross1||three_cross)
                            {     //if(Set_Speed1<=530)
                                  Set_Speed2=Set_Speed1-Set_Speed1*0.25;
                                  //else  Set_Speed2=530;
                            }
                            else   if(poer_flag)//(||star_lineflag&&park_flag==1)
                                        Set_Speed2=Set_Speed1-Set_Speed1*0.45;
                                        //Set_Speed2=Set_Speed1-Set_Speed1*0.50;
                            else  if(lefthuihuan_flag==1||youhuihuan_flag==1)
                               Set_Speed2=Set_Speed1-Set_Speed1*0.1;
                            else  if(lefthuihuan_flag==2||youhuihuan_flag==2)
                                   Set_Speed2=Set_Speed1-Set_Speed1*0.15;
                    //            else  if(lefthuihuan_flag==1||youhuihuan_flag==1)
                    //            {  //if(Set_Speed2<=500)
                    //                Set_Speed2=Set_Speed1-Set_Speed1*0.25;
                    //              // else    Set_Speed2=500;
                    //
                    //            }
                        else
                        Set_Speed2=Set_Speed1;
                    }
    //   8           5                      3*比例
    }
}




void ruku_handle()
{
    uint8 ruku_lie=8;



    for(int i=67;i>=5;i--)
    {
    if(image_use[i][ruku_lie]==0&&image_use[i-1][ruku_lie]==0&&image_use[i-2][ruku_lie]==0&&image_use[i+1][ruku_lie]==255&&image_use[i+2][ruku_lie]==255)
    {
        ruku_zuobiao_hang_jubu=i;
    break;
    }}

    if(ruku_zuobiao_hang_jubu)
    {
    for(int i=ruku_lie;i<170;i+=2)
    {
    if(image_use[ruku_zuobiao_hang_jubu+1][i]==255&&image_use[ruku_zuobiao_hang_jubu+2][i]==255&&image_use[ruku_zuobiao_hang_jubu-1][i]==255&&image_use[ruku_zuobiao_hang_jubu-2][i]==255&&image_use[ruku_zuobiao_hang_jubu][i+1]==255&&image_use[ruku_zuobiao_hang_jubu][i+2]==255)
    {
    ruku_zuobiao_lie=i-3;
    break;
    }}}


    for(int i=ruku_zuobiao_hang_jubu-3;i<70;i++)
    {
        if(image_use[i][ruku_zuobiao_lie]==0&&image_use[i+1][ruku_zuobiao_lie]==255&&image_use[i+2][ruku_zuobiao_lie]==255)
        {
            ruku_zuobiao_hang=i;
            break;
        }
    }


 if(ruku_zuobiao_lie&&ruku_zuobiao_hang&&ruku_zuobiao_hang>25)
  tingche_flag=1;
}


//left_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2);

//right_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2);
