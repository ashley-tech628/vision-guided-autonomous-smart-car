#ifndef _traffic_circle_h
#define _traffic_circle_h
#include "headfile.h"
#include "common.h"

void youhuandao();
void zuohuandao();
void left_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2);
void right_buxian(uint8 x1,uint8 y1,uint8 x2,uint8 y2);//右补线（环岛）
void left_buxian2(uint8 x1,uint8 y1,uint8 x2,uint8 y2);
void right_buxian2(uint8 x1,uint8 y1,uint8 x2,uint8 y2);//右补线（环岛）

void find_rightmiddle_point(uint8 start_point, uint8 end_point);
void find_rightup_point(uint8 start_point, uint8 end_point);
void find_leftmiddle_point(uint8 start_point, uint8 end_point);
void find_leftup_point(uint8 start_point, uint8 end_point);
extern uint8 huan_leijia;
extern uint8 youhuandao_flag_queding;
extern uint8 zuohuandao_flag_queding;
extern uint8 zuohuandao_flag ,zuohuandao_flag2,zuohuandao_flag3;
extern uint8 zuochu_flag ,zuochu_flag2;
extern uint8 youhuandao_flag ,youhuandao_flag2,youhuandao_flag3;
extern uint8 youchu_flag ,zuochu_flag;
extern uint8 line_you,line_zuo,n1,n2,n11,n22;
extern uint8 righty,lefty;
void find_rightup_point2(uint8 start_point, uint8 end_point);
void find_leftup_point2(uint8 start_point, uint8 end_point);
void find_rightup_point3(uint8 start_point, uint8 end_point);
extern  uint8 bianzhai;
extern  uint8 biankuan;
extern  uint8 guaidian;
extern uint8 youhuihuan_flag;
extern uint8  lefthuihuan_flag;
extern uint8 right_turn_middle[2];
extern uint8 left_turn_middle[2];
extern uint8 flag_find_huan_rightmiddle_point;
extern uint8 flag_find_huan_leftmiddle_point;
void zuo_huihuan();
#endif
