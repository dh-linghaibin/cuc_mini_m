/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�time,c
*
* �ļ���ʶ��ds
* ժ    Ҫ����ʱ������������
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/18
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Time.h"

void TimerInit(void) {

}

static u16 sec_flag = 0;

u16 TimerGetSec(void) {
    return sec_flag;
}

void TimerSetSec(u8 data) {
    sec_flag = data;
}




