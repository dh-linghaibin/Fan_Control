/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/25
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#ifndef __MENU_H
#define __MENU_H

#include "Type.h"

typedef struct menu {
    u8 mode;//工作模式
    u8 temp_arr;//使用第几组温度计
    u8 temp[6];//温度1
    u8 tempSet[6];//设置温度点
    u8 fan_error;//故障点击数量
    u8 cur_time;//电流检测时间
    u16 cur_get[7];//获取电流
    u16 show_time;//数码管保持时间
    u16 show_bit;//数码管显示位
}menu;
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuInit(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuTempSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 温度处理函数  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuTempSer(void);
/**********************************************函数定义***************************************************** 
* 函数名称: void MenuComSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void MenuComSer(void);

#endif


