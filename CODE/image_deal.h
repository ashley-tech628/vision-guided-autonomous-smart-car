/*
 * image_deal.h
 *
 *  Created on: 2022年5月21日
 *      Author: admin
 */

#ifndef CODE_IMAGE_DEAL_H_
#define CODE_IMAGE_DEAL_H_


#include "common.h"  //uint8 whitenum=0;
void yuzhiget(void);
extern uint8 times2;
extern uint8 black_blocks ;
extern int qvlv_quanju;
extern   uint8 cursor;    //指向栈顶的游标
extern uint8 right_turn_down[2];
extern uint8 left_turn_down[2];
extern uint8 white_num_col_max;
extern uint8 left_turn_up[2];
extern uint8 findrightdownguai ;
extern uint8 findleftdownguai ;
extern uint8 white_num_col_line;
extern  float  k_left;
extern  float  k_right;
extern uint8 r_start;
extern uint8 l_start;
extern uint8 times;
extern float curvity_left,curvity_right;
extern uint8 xielv_1eft2;
extern uint8 xielv_right2;
extern uint8 Left_Line_New[70], Right_Line_New[70];
void twovaltrans(uint8 t1,uint8 t2,uint8 t3) ;
extern float k_center;
extern uint8 star_lineflag,star_lineflag2;
int32 range_protect2(int32 duty, int32 min, int32 max);//限幅保护

void Center_line_deal();//中线处理
void line_deal();
void Ostu(void);//大津
uint8 my_adapt_threshold(uint8 *image, uint16 col, uint16 row);
float Point_Weight(void);
void Left_Line_Repair(uint8 y, uint8 x);
void Right_Line_Repair(uint8 y, uint8 x);//右边界补线修正
uint8 range_protect(uint8 duty, uint8 min, uint8 max);
void Mid_Line_Repair(uint8 count);
void star_line_judg2();
extern uint8 guaidian;
extern uint8 white_num_col[188];
extern uint8 zuodiuxianshu;//左丢线数
extern uint8 zongdiuxianshu;//总丢线数
extern int Point_Mid,Point,Foresight;
extern uint8 left_huan_num,right_huan_num; //环岛变量
extern uint8 park_flag;//停车标志
extern uint8 left_line[70],right_line[70];//左边界右边界
extern uint8 sousuojieshuhang;//搜索结束行
extern uint8 youdiuxianshu;//右丢线数
extern uint8 zuodiuxianshu;//左丢线数
extern uint8 Left_Add[70], Right_Add[70],Left_Add_num,Right_Add_num;
extern int n;
extern int n111;
extern uint8 right_turn_up[2];
extern uint8  three_cross;
extern uint8   flag_shizi;
extern uint8 Left_Add2[70], Right_Add2[70];
extern uint8 three_cross1;
extern uint8 kk,bai_flag,hei_flag,baihei_flag,heibai_flag,width_heibai;
extern uint8  Right_Add[70];
extern uint8  Left_Add[70];

extern uint8 left_line[70],right_line[70];//左边界右边界
extern uint8 center[70],Width[70];
extern uint8 Right_Add_num,Left_Add_num;
extern uint8 white_num_col[188],white_num_col_line;


extern uint8 check_line;
unsigned int my_sqrt(int num);
void Cal_losttimes(int times);
void regression(int type, int startline, int endline);
void find_leftdown_point(uint8 start_point, uint8 end_point, uint8 RoadName);
void find_rightdown_point(uint8 start_point, uint8 end_point, uint8 RoadName);
char oppositeSigns(int x, int y);
void advanced_regression(int type, int startline1, int endline1, int startline2, int endline2);
void check_starting_line();
void SignalProcess_grayfine_fill(void);
extern uint8 xielv;
extern int8 huihuan_left;
extern int8 huihuan_right;
extern uint8 whitenum;
extern uint8 huihuan_num;
#endif /* CODE_IMAGE_DEAL_H_ */
