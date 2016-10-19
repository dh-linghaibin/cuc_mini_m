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

#include "Com.h"
#include "Delay.h"
#include "Time.h"

/*��������*/
static com_data com_data_one;

void ComInit(void) {
    PD_DDR &= ~BIT(6);//TX
    PD_CR1 |= BIT(6); 
    PD_CR2 &= ~BIT(6);

    PD_DDR |= BIT(5);//RX
    PD_CR1 |= BIT(5); 
    PD_CR2 |= BIT(5);

    UART1_CR1=0x00;
    UART1_CR2=0x00;
    UART1_CR3=0x00; 
    UART1_BRR2=0x02;//02 0a
    UART1_BRR1=0x68;//68 08
    UART1_CR2=0x2c;//������գ����ͣ��������ж�
}
/**********************************************��������***************************************************** 
* ��������: void ComSend(u8 cmd, u8 dat1,u8 dat2,u8 dat3) 
* �������: u8 cmd, u8 dat1,u8 dat2,u8 dat3 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
void ComSend(u8 num, u8 *dat) { 
    DelayMs(10);
    for(u8 i = 0;i < num;i++) {
        while((UART1_SR & 0x80) == 0x00);
        UART1_DR = dat[i];
    }
}
/**********************************************��������***************************************************** 
* ��������: u8 ComGetFlag(void) 
* �������: void 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetFlag(void) { 
    return com_data_one.rs_ok;
}

/**********************************************��������***************************************************** 
* ��������: u8 ComGetDate(u8 cmd) 
* �������: u8 cmd 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetDate(u8 cmd) { 
    return com_data_one.data[cmd];
}
/**********************************************��������***************************************************** 
* ��������: void ComSetFlag(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
void ComSetFlag(u8 cmd) { 
    com_data_one.rs_ok = 0x00;
}
/**********************************************��������***************************************************** 
* ��������: u8 ComCheck(void) 
* �������: void 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
u8 ComCheck(void) { 
    u16 num = 0;
    for(u8 i = 1;i < 4;i++) {
        num += com_data_one.data[i];
    }
    if(com_data_one.data[5] == (u8)num) {
        if(com_data_one.data[6] == (u8)(num>>8)) {
            return 0x01;
        } else {
            return 0x00;
        }
    } else {
        return 0x00;
    }
}


#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{
    u8 data;
    data = UART1_DR;
    /*�ȴ����ݽ������*/
    while((UART1_SR & 0x80) == 0x00);
    /*��ֹ������ͷ֡��ͻ*/
    
    
    if(com_data_one.rs_flag == 0x00) {
        switch( data ) {
        case 0x08://���յ�λ��
            com_data_one.data[com_data_one.rs_flag] = data;
            com_data_one.rs_flag = 1;
            break;
        case 0x06://����
            com_data_one.rs_flag = 0;
            com_data_one.data[com_data_one.rs_flag] = data;
            com_data_one.rs_ok = 0x01;
        case 10://����
            com_data_one.rs_flag = 0;
            com_data_one.data[com_data_one.rs_flag] = data;
            com_data_one.rs_ok = 0x01;
            break;
        case 11://����
            com_data_one.rs_flag = 0;
            com_data_one.data[com_data_one.rs_flag] = data;
            com_data_one.rs_ok = 0x01;
            break;
        default:
            break;
        }
    } else {
        com_data_one.data[com_data_one.rs_flag] = data;
        if(com_data_one.rs_flag < 2) {
            com_data_one.rs_flag++;
        } else {
            com_data_one.rs_flag = 0;
            com_data_one.rs_ok = 0x01;
        }
    }    
    return;
}




