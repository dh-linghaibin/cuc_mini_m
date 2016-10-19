/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�Menu.c
*
* �ļ���ʶ��V
* ժ    Ҫ���˵��ں�
*
*
* ��ǰ�汾��V1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/17
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Menu.h"
#include "Tm1650.h"
#include "Com.h"
/*
����+1���Զ�����
����+2������תӢ��
����+6�����ڵ���ǳ
����+7������ѹֽʱ��
����+8�����ڳߴ粹��
����+10����С�ߴ�
����+11�����ߴ�
����+14���ϻ�����
����+�£����뵶��΢������
*/
/*
ȷ�ϼ�������ȷ�ϣ����棬����
���������������   -------------------���¼�����ɵ������ݣ��������Զ�ģʽ�����ΰ���M���ͷŷ�ɫ����޸�Mֵ��0-100���� ֱ�Ӱ� ����޸�Mֵ��0-100�飩��ֱ�Ӱ�����ѡ�������������¼��л�����
�������ѡ������ģʽ/��λ
��������޸�����ߴ�
ģʽ����ģʽ�л��� -------------------��ģʽ�������л�
���¼���ǰ��������/ѡ���
1   �������ּ�
���ܼ������ܼ�
����������¸�λ�������ͷź�����Զ���ֽ���������ʱ�䳬��2���ӣ������������ֽ����λ
*/

typedef enum {
    best_arrive = 4900,//���λ��
    COM_SETP = 0x01,
    COM_MODE = 0X02,//���͵�ǰģʽ
    COM_PUSH_BOOK = 0x03,//�Ƿ�����
    COM_STP_RST = 0X04,//��ֽ�����λ
    COM_SIU_DATA = 0x05,//�ȷ�����
    COM_OLD = 0X07,//�ϻ�ģʽ
    COM_STRENGTH = 0x08,//���õ������
}menudata;

typedef struct menu{
    u8 mode;//ģʽ
    u16 setp_position;//�������λ��
    u8 del_flag;//ɾ����λ��
    u8 number_flag;//�����ڼ�λ
    u8 number_bit[4];//ǧλ 
    u8 com_data[10];//����
}menu;

menu menu_m;
/**********************************************��������***************************************************** 
* ��������: void MenuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �˵�������ʼ��  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/17
************************************************************************************************************/ 
void MenuInit(void) { 
    menu_m.setp_position = 1234;
}
/**********************************************��������***************************************************** 
* ��������: void MenuShow(u8 mode) 
* �������: u8 mode 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/10/17
************************************************************************************************************/ 
void MenuShow(u8 mode) { 
    switch( mode ) {
    case 0://��ʾ״̬
        Tm1650Show(menu_m.setp_position/1000,
                   menu_m.setp_position/100%10,
                   menu_m.setp_position/10%10,
                   menu_m.setp_position%10,1);
        break;
    case 1://�ȴ�����״̬
        Tm1650Show(11,11,11,11,1);
        break;
    case 2://�Ѿ�������״̬
        
        break;
    default:
        break;
    }
}
/**********************************************��������***************************************************** 
* ��������: void MenuSetNum(u8 num) 
* �������: u8 num 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/10/17
************************************************************************************************************/ 
void MenuSetNum(u8 num) {
  menu_m.com_data[0] = 0x01;
  ComSend(1,menu_m.com_data);
  if(menu_m.del_flag != 0) {
        menu_m.del_flag = 2;
        menu_m.number_bit[menu_m.number_flag] = num;
        switch(menu_m.number_flag) {
        case 0:
          menu_m.number_flag = 1;
          Tm1650Show(menu_m.number_bit[0],
                       11,
                       11,
                       11,1);
          break;
        case 1:
          menu_m.number_flag = 2;
          Tm1650Show(menu_m.number_bit[0],
                     menu_m.number_bit[1],
                       11,
                       11,1);
          break;
        case 2:
          menu_m.number_flag = 3;
          Tm1650Show(menu_m.number_bit[0],
                     menu_m.number_bit[1],
                     menu_m.number_bit[2],
                       11,1);
          break;
        case 3:
          menu_m.number_flag = 4;
          Tm1650Show(menu_m.number_bit[0],
                     menu_m.number_bit[1],
                     menu_m.number_bit[2],
                     menu_m.number_bit[3],1);
          break;
        }
    }
}
/**********************************************��������***************************************************** 
* ��������: void MenuModeSet(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/10/17
************************************************************************************************************/ 
void MenuModeSet(u8 cmd) { 
    switch( cmd ) {
    case 23://��-����
        menu_m.com_data[0] = 0x02;
        ComSend(1,menu_m.com_data);
        break;
    case 3://��-�ɿ�
        menu_m.com_data[0] = 0x03;
        ComSend(1,menu_m.com_data);
        ComSend(1,menu_m.com_data);
        break;
    case 22://��-����
        menu_m.com_data[0] = 0x04;
        ComSend(1,menu_m.com_data);
        break;
    case 2://��-�ɿ�
        menu_m.com_data[0] = 0x05;
        ComSend(1,menu_m.com_data);
        ComSend(1,menu_m.com_data);
        break;
    case 1://zero
        menu_m.com_data[0] = 0x06;
        ComSend(1,menu_m.com_data);
        break;
    case 7://del
        //���ͷ�����
        menu_m.com_data[0] = 0x01;
        ComSend(1,menu_m.com_data);
        
        if(menu_m.mode == 0) {
            switch( menu_m.del_flag ) {
            case 0://��ʾ״̬
                menu_m.del_flag = 1;
                break;
            case 1://�ȴ�����״̬
                menu_m.del_flag = 0;
                break;
            case 2://�Ѿ�������״̬
                menu_m.del_flag = 1;
                break;
            default:
                break;
            }
            MenuShow(menu_m.del_flag);
            menu_m.number_flag = 0;
        }    
        break;
    case 4://start
        //���ͷ�����
        menu_m.com_data[0] = 0x01;
        ComSend(1,menu_m.com_data);
        
        if(menu_m.mode == 0) {
            if(menu_m.del_flag == 2) {
                if(menu_m.number_flag == 4) {
                    u16 position = 0;
                    position = menu_m.number_bit[0]*1000;
                    position += menu_m.number_bit[1]*100;
                    position += menu_m.number_bit[2]*10;
                    position += menu_m.number_bit[3];
                    if(position < 500) {//�������ݱ���
                        menu_m.number_flag = 0;
                        menu_m.del_flag = 1;
                        MenuShow(menu_m.del_flag);
                        break;
                    } else if(position > 4500) {//�������ݱ���
                        menu_m.number_flag = 0;
                        menu_m.del_flag = 1;
                        MenuShow(menu_m.del_flag);
                        break;
                    }
                    menu_m.number_flag = 0;
                    menu_m.del_flag = 0;
                    //����λ��
                    menu_m.com_data[0] = 0x08;
                    menu_m.com_data[1] = (u8)position;
                    menu_m.com_data[2] = (u8)(position >> 8);
                    ComSend(3,menu_m.com_data);
                }
            } else if(menu_m.del_flag == 1) {
                //���ͷ�����
            } else {
                //��������
                menu_m.com_data[0] = 0x07;
                ComSend(1,menu_m.com_data);
            }
        } 
        break;
    case 5://0
        MenuSetNum(0);
        break;
    case 15://1
        MenuSetNum(1);
        break;
    case 14://2
        MenuSetNum(2);
        break;
    case 13://3
        MenuSetNum(3);
        break;
    case 12://4
        MenuSetNum(4);
        break;
    case 11://5
        MenuSetNum(5);
        break;
    case 10://6
        MenuSetNum(6);
        break;
    case 9://7
        MenuSetNum(7);
        break;
    case 8://8
        MenuSetNum(8);
        break;
    case 6://9
        MenuSetNum(9);
        break;
    default:
        break;
    }
}

/**********************************************��������***************************************************** 
* ��������: void MenuAsk(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/10/17
************************************************************************************************************/ 
void MenuAsk(void) { 
    if(1 == ComGetFlag()) {
        ComSetFlag(0);
        switch( ComGetDate(0) ) {
        case 0x06://����
            menu_m.mode = 1;
            Tm1650Show(11,11,11,11,0);
            break;
        case 0x08://��ʾλ��
            menu_m.mode = 0;
            menu_m.setp_position = ComGetDate(1);
            menu_m.setp_position |= (u16)(ComGetDate(2) << 8);
            Tm1650Show(menu_m.setp_position/1000,
                   menu_m.setp_position/100%10,
                   menu_m.setp_position/10%10,
                   menu_m.setp_position%10,1);
            break;
        case 10://����
            menu_m.mode = 1;
            Tm1650Show(12,11,11,1,0);
            break;
        case 11://����
            menu_m.mode = 1;
            Tm1650Show(12,11,11,2,0);
            break;
        default:
            break;
        }
    }
}



