/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/7/11
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/

#include "Type.h"
#include "Sys.h"
#include "Time.h"
#include "buntu.h"
#include "Materal.h"
#include "menu.h"
#include "Com.h"
#include "Eeprom.h"
#include "Tm1650.h"


int main( void ) {
    SysInit();//system
    EeepromInit();
    BuntuInit();// 
    ComInit();
    TM1650_Init();
    MenuInit();
    INTEN
    while(1) {
        MenuModeSet(BuntuRead());
        MenuAsk();
    }
}
