/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�Tm1650.h
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/8/24
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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

/**********************************************��������***************************************************** 
* ��������:  Tm165() 
* �������:  
* ���ز���:   
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void TM1650_Init(void);
/*---------------------------------------------------------------*-
 * TM1650_Display()
 * 
 * Display the number on the specified postion or Send
 * initialization commands.
-*---------------------------------------------------------------*/
void TM1650_Send(u8 CMD, u8 DATA);
/**********************************************��������***************************************************** 
* ��������: void Tm1650(u8 num1, u8 num2,u8 pos) 
* �������: u8 num1, u8 num2,u8 pos 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void Tm1650Show(u8 num1, u8 num2, u8 unm3, u8 unm4, u8 pos);

#endif


