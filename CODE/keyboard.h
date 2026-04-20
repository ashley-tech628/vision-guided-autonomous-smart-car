/*
 * keyboard.h
 *
 *  Created on: 2022年5月20日
 *      Author: admin
 */

#ifndef CODE_KEYBOARD_H_
#define CODE_KEYBOARD_H_

#include "common.h"
//定义按键引脚
#define KEY1    P22_0  //  0 1 2 3 ke
#define KEY2    P22_1  //
#define KEY3    P22_2  //ke
#define KEY4    P22_3   //P33_7  ke
//#define KEY5    P10_9
//定义拨码开关引脚
#define SW1     P33_12
#define SW2     P33_13


#define EXAMPLE_EEPROM_SECTOR        (11)

void prompt(void);
void keyboard_init(void);

void  key_operate(void);
void  key1_function(void);
void  key2_function(void);
void  key3_function(void);
void  key4_function(void);
void interface_display(void);
void dispage2(void);
/*
void dispage3(void);
void dispage4(void);
void number1(void);
void number2(void);
void battery(void);
*/
extern uint8 c_l,c_r;
extern uint16 sd_fast;
extern uint16 clc_sd;
extern int8 contin;
extern uint8 junsu;
extern uint8 huihuan_sd;
void   flash_deal();
void   flash_read2();

#endif /* CODE_KEYBOARD_H_ */
