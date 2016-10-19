/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�buntu.h
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��v1.1
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/14
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "buntu.h"
#include "Delay.h"
#include "Time.h"

#define BU_X1 PD_ODR_ODR4
#define BU_X2 PD_ODR_ODR3
#define BU_X3 PD_ODR_ODR2  
#define BU_X4 PC_ODR_ODR7

#define BU_Y1 PC_IDR_IDR6
#define BU_Y2 PC_IDR_IDR5
#define BU_Y3 PC_IDR_IDR4
#define BU_Y4 PC_IDR_IDR3


#define BU_DE_Q 10000
#define BU_DE_H 500

#define BU_EN 1

/**********************************************��������***************************************************** 
* ��������: void BuntuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ������ʼ��  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/14
************************************************************************************************************/ 
void BuntuInit(void) {     
    PD_DDR_DDR4 = 1;
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 0;
    
    PD_DDR_DDR3 = 1;
    PD_CR1_C13 = 1;
    PD_CR2_C23 = 0;
    
    PD_DDR_DDR2 = 1;
    PD_CR1_C12 = 1;
    PD_CR2_C22 = 0;
    
    PC_DDR_DDR7 = 1;
    PC_CR1_C17 = 1;
    PC_CR2_C27 = 0;
    
    //----------------------------------
    PC_DDR_DDR6 = 0;
    PC_CR1_C16 = 0;
    PC_CR2_C26 = 0;
    
    PC_DDR_DDR5 = 0;
    PC_CR1_C15 = 0;
    PC_CR2_C25 = 0;
    
    PC_DDR_DDR4 = 0;
    PC_CR1_C14 = 0;
    PC_CR2_C24 = 0;
    
    PC_DDR_DDR3 = 0;
    PC_CR1_C13 = 0;
    PC_CR2_C23 = 0;
    
    BU_X1 = 0;
    BU_X2 = 0;
    BU_X3 = 0;
    BU_X4 = 0;
}
/**********************************************��������***************************************************** 
* ��������: BuntuSetX static u8(u8 num) 
* �������: u8 num 
* ���ز���: BuntuSetX  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/7/11
************************************************************************************************************/ 
static void BuntuSetX(u8 num) { 
    switch(num) {
        case 0:
            BU_X4 = 0;
            BU_X1 = 1;
        break;
        case 1:
            BU_X1 = 0;
            BU_X2 = 1;
        break;
        case 2:
            BU_X2 = 0;
            BU_X3 = 1;
        break;
        case 3:
            BU_X3 = 0;
            BU_X4 = 1;
        break;
        default:
            BU_X1 = 0;
            BU_X2 = 0;
            BU_X3 = 0;
            BU_X4 = 0;
            break;
    }
}
/**********************************************��������***************************************************** 
* ��������: static u8 BuntuRedx(u8 num) 
* �������: u8 num 
* ���ز���: static u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/10/17
************************************************************************************************************/ 
static u8 BuntuRedx(u8 num) {
    u8 dr  = 0;
    switch( num ) {
    case 0:
        dr = BU_Y1;
        break;
    case 1:
        dr = BU_Y2;
        break;
    case 2:
        dr = BU_Y3;
        break;
    case 3:
        dr = BU_Y4;
        break;
    default:
        dr = 0;
        break;
    }
    return dr;
}
            
u8 buntu_bit[25];
u8 buntu_bit_h[25];
/**********************************************��������***************************************************** 
* ��������: u8 BuntuRead(void) 
* �������: void 
* ���ز���: u8  
* ��    ��: ��ȡ����״̬  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/14
************************************************************************************************************/ 
u8 BuntuRead(void) { 
    static u16 bun_count[25];
    for(u8 i = 0;i < 4;i++ ) {
        u8 bit = 0;
        bit = i*4;
        BuntuSetX(i);
        
        for(u8 x = 0;x < 4;x++) {
            if(BU_EN == BuntuRedx(x)) {
                if(bun_count[x+bit] < BU_DE_Q) {
                    bun_count[x+bit]++;
                    if(bun_count[x+bit] == BU_DE_H) {
                        //buntu_bit[x+bit] = 1;
                        switch( (x+bit) ) {
                        case 3:
                            return 23; 
                            break;
                        case 2:
                            return 22;
                            break;
                        default:
                            break;
                        } 
                    }
                }
            } else {
                if(bun_count[x+bit] > BU_DE_H) {
                    bun_count[x+bit] = 0;
                    return (x+bit);
                }
                bun_count[x+bit] = 0;
            }
        }
    }
    return 0x30;
}


