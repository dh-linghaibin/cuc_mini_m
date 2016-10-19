/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Tm1650.h
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/24
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#ifndef __TM1650_H
#define __TM1650_H

#include "Type.h"

// ------ Public constants --------------------------------

#define DEFAULT_SETTING 0x48
#define NORMAL_DISPLAY	0x01

// From left to right order
#define DISPLAY_POINT	0x80
#define FIRST_POSITON	0x68
#define SECOND_POSITION 0x6A
#define THIRD_POSITION  0x6C
#define FOURTH_POSITON  0x6E

/**********************************************函数定义***************************************************** 
* 函数名称:  Tm165() 
* 输入参数:  
* 返回参数:   
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void TM1650_Init(void);
/*---------------------------------------------------------------*-
 * TM1650_Display()
 * 
 * Display the number on the specified postion or Send
 * initialization commands.
-*---------------------------------------------------------------*/
void TM1650_Send(u8 CMD, u8 DATA);
/**********************************************函数定义***************************************************** 
* 函数名称: void Tm1650(u8 num1, u8 num2,u8 pos) 
* 输入参数: u8 num1, u8 num2,u8 pos 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void Tm1650Show(u8 num1, u8 num2, u8 unm3, u8 unm4, u8 pos);

#endif


