/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Menu.c
*
* 文件标识：V
* 摘    要：菜单内核
*
*
* 当前版本：V1.0
* 作    者：lhb Steven
* 完成日期：2016/3/17
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Menu.h"
#include "Tm1650.h"
#include "Com.h"
/*
功能+1：自动推书
功能+2：工制转英制
功能+6：调节刀深浅
功能+7：调结压纸时间
功能+8：调节尺寸补偿
功能+10：最小尺寸
功能+11：最大尺寸
功能+14：老化测试
功能+下：进入刀切微调界面
*/
/*
确认键：输入确认，保存，推书
记忆键：调出数据   -------------------按下记忆键可调出数据，并进入自动模式，单次按下M键释放反色后可修改M值（0-100）组 直接按 后可修改M值（0-100组），直接按数字选择组数，或按上下键切换组数
推书键：选择推书模式/复位
清楚键：修改清楚尺寸
模式键：模式切换键 -------------------按模式键可以切换
上下键：前进，后退/选择键
1   键：数字键
功能键：功能键
推书键：按下复位键马上释放后程序自动推纸，如果按下时间超过2秒钟，程序则进行推纸器复位
*/

typedef enum {
    best_arrive = 4900,//最大位置
    COM_SETP = 0x01,
    COM_MODE = 0X02,//发送当前模式
    COM_PUSH_BOOK = 0x03,//是否推书
    COM_STP_RST = 0X04,//推纸电机复位
    COM_SIU_DATA = 0x05,//等分数据
    COM_OLD = 0X07,//老化模式
    COM_STRENGTH = 0x08,//设置电机力度
}menudata;

typedef struct menu{
    u8 mode;//模式
    u16 setp_position;//步进电机位置
    u8 del_flag;//删除键位置
    u8 number_flag;//操作第几位
    u8 number_bit[4];//千位 
    u8 com_data[10];//数据
}menu;

menu menu_m;
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 菜单参数初始化  
* 作    者: by lhb_steven
* 日    期: 2016/3/17
************************************************************************************************************/ 
void MenuInit(void) { 
    menu_m.setp_position = 1234;
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuShow(u8 mode) 
* 输入参数: u8 mode 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/10/17
************************************************************************************************************/ 
void MenuShow(u8 mode) { 
    switch( mode ) {
    case 0://显示状态
        Tm1650Show(menu_m.setp_position/1000,
                   menu_m.setp_position/100%10,
                   menu_m.setp_position/10%10,
                   menu_m.setp_position%10,1);
        break;
    case 1://等待输入状态
        Tm1650Show(11,11,11,11,1);
        break;
    case 2://已经有输入状态
        
        break;
    default:
        break;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuSetNum(u8 num) 
* 输入参数: u8 num 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/10/17
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
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuModeSet(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/10/17
************************************************************************************************************/ 
void MenuModeSet(u8 cmd) { 
    switch( cmd ) {
    case 23://上-按下
        menu_m.com_data[0] = 0x02;
        ComSend(1,menu_m.com_data);
        break;
    case 3://上-松开
        menu_m.com_data[0] = 0x03;
        ComSend(1,menu_m.com_data);
        ComSend(1,menu_m.com_data);
        break;
    case 22://下-按下
        menu_m.com_data[0] = 0x04;
        ComSend(1,menu_m.com_data);
        break;
    case 2://下-松开
        menu_m.com_data[0] = 0x05;
        ComSend(1,menu_m.com_data);
        ComSend(1,menu_m.com_data);
        break;
    case 1://zero
        menu_m.com_data[0] = 0x06;
        ComSend(1,menu_m.com_data);
        break;
    case 7://del
        //发送蜂鸣器
        menu_m.com_data[0] = 0x01;
        ComSend(1,menu_m.com_data);
        
        if(menu_m.mode == 0) {
            switch( menu_m.del_flag ) {
            case 0://显示状态
                menu_m.del_flag = 1;
                break;
            case 1://等待输入状态
                menu_m.del_flag = 0;
                break;
            case 2://已经有输入状态
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
        //发送蜂鸣器
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
                    if(position < 500) {//发送数据保护
                        menu_m.number_flag = 0;
                        menu_m.del_flag = 1;
                        MenuShow(menu_m.del_flag);
                        break;
                    } else if(position > 4500) {//发送数据保护
                        menu_m.number_flag = 0;
                        menu_m.del_flag = 1;
                        MenuShow(menu_m.del_flag);
                        break;
                    }
                    menu_m.number_flag = 0;
                    menu_m.del_flag = 0;
                    //发送位置
                    menu_m.com_data[0] = 0x08;
                    menu_m.com_data[1] = (u8)position;
                    menu_m.com_data[2] = (u8)(position >> 8);
                    ComSend(3,menu_m.com_data);
                }
            } else if(menu_m.del_flag == 1) {
                //发送蜂鸣器
            } else {
                //发送推书
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

/**********************************************函数定义***************************************************** 
* 函数名称: void MenuAsk(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/10/17
************************************************************************************************************/ 
void MenuAsk(void) { 
    if(1 == ComGetFlag()) {
        ComSetFlag(0);
        switch( ComGetDate(0) ) {
        case 0x06://回零
            menu_m.mode = 1;
            Tm1650Show(11,11,11,11,0);
            break;
        case 0x08://显示位置
            menu_m.mode = 0;
            menu_m.setp_position = ComGetDate(1);
            menu_m.setp_position |= (u16)(ComGetDate(2) << 8);
            Tm1650Show(menu_m.setp_position/1000,
                   menu_m.setp_position/100%10,
                   menu_m.setp_position/10%10,
                   menu_m.setp_position%10,1);
            break;
        case 10://错误
            menu_m.mode = 1;
            Tm1650Show(12,11,11,1,0);
            break;
        case 11://错误
            menu_m.mode = 1;
            Tm1650Show(12,11,11,2,0);
            break;
        default:
            break;
        }
    }
}



