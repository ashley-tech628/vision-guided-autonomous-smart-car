/*
 * control.h
 *
 *  Created on: 2022年5月21日
 *      Author: admin
 */

#ifndef CODE_CONTROL_H_
#define CODE_CONTROL_H_


#include "headfile.h"
#include "common.h"
void speed_select();
int duojipid(float error);//舵机打角（返回值是整形）
void saidaoleixing(void);
void proess(void);
void star_line_judg();
void parkcar();//倒车入库;
void GetMotorPulse(void);
void SpeedControl(void);//速度控制
void chasu(float x);
void dianjiqudong(int speed1,int speed2);
void read_1Ms_pulse(void);//脉冲数读取10ms    去学校测试几ms合适
void Direction_Control(float err);
void speed_get();
void ruku_handle(void);
extern int16 SPEED_CONTROL_P , SPEED_CONTROL_I ;//60  30报命程序 65干净赛道 heibai_flag
extern  int chasuzuo;//差速左
extern int chasuyou;//差速右
extern uint8 leijia_flag;//编码器累加标志
extern int8 Set;
extern int left_num,right_num,LeftOut,RightOut,left_zheng_ma,right_zheng_ma,left_fan_ma,right_fan_ma;
extern int left_leijia,right_leijia;
extern int left_leijia2,right_leijia2;
extern int Set_Speed;
extern uint8 stop;
extern int32 angle2;
extern int g_fCarSpeed;//小车实际速度
extern uint8 po;
extern uint8 poer_flag;
#define MOTOR1_A   ATOM0_CH5_P02_5  //定义4电机正转PWM引脚
#define MOTOR1_B   ATOM0_CH5_P02_5
#define MOTOR2_A   ATOM0_CH5_P02_5   //定义2电机正转PWM引脚  左轮
#define MOTOR2_B   ATOM0_CH5_P02_5   //定义2电机反转PWM引脚
#define S_MOTOR_PIN   ATOM0_CH5_P02_5       //定义舵机引脚
#define stree_max  905  //zuo
#define stree_min 695   //you
#define stree_center 795   //中    4830
extern int S_D5_Duty,S_D5_Duty2;
extern uint8 left_whitenum,right_whitenum;
extern int8 speed_yingshe;
extern  int Set_Speed2,Set_Speed1;
extern uint8 zhongzhi;
extern uint8 zhidao_juli;
extern int chasuxisu;  //电机差速系数
extern const uint8 left[70];
extern const uint8 right[70];
extern int jiasu_part;
extern uint8 ruku_zuobiao_hang;
extern uint8 ruku_zuobiao_lie;

extern int you_speed;
extern int zuo_speed;
#endif /* CODE_CONTROL_H_ */
