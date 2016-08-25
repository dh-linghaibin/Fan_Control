/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Fan,c
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/8/23
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Fan.h"
#include "Delay.h"
#include "Elecur.h"

#define FAN_0   PI_ODR_ODR0 /*风扇1*/
#define FAN_1   PG_ODR_ODR4 
#define FAN_2   PG_ODR_ODR3
#define FAN_3   PG_ODR_ODR2
#define FAN_4   PG_ODR_ODR1
#define FAN_5   PG_ODR_ODR0
#define FAN_6   PC_ODR_ODR7
#define FAN_7   PC_ODR_ODR6
#define FAN_8   PC_ODR_ODR5
#define FAN_9   PC_ODR_ODR4
#define FAN_10   PC_ODR_ODR3
#define FAN_11   PC_ODR_ODR2
#define FAN_12   PC_ODR_ODR1
#define FAN_13   PE_ODR_ODR5
#define FAN_14   PE_ODR_ODR6
#define FAN_15   PE_ODR_ODR7
#define FAN_16   PA_ODR_ODR6
#define FAN_17   PD_ODR_ODR7
#define FAN_18   PD_ODR_ODR6
#define FAN_19   PD_ODR_ODR5
#define FAN_20   PD_ODR_ODR4
#define FAN_21   PD_ODR_ODR3
#define FAN_22   PD_ODR_ODR2
#define FAN_23   PD_ODR_ODR0
#define FAN_24   PE_ODR_ODR0
#define FAN_25   PE_ODR_ODR3
#define FAN_26   PE_ODR_ODR4
#define FAN_27   PG_ODR_ODR7
/*风扇结构体*/
static fan fan_Arr[28];
static u8 huai[28];
static u8 huai_arr[28];
static u16 cur_all[7];//七组电流值
//#define GPBCON  (*(volatile unsigned int *)0x5029)
//
//const unsigned int fan_gpio_adr[28] = {
//0x5028,
//};

/**********************************************函数定义***************************************************** 
* 函数名称: void FanInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanInit(void) { 
    PI_DDR_DDR0 = 1;
    PI_CR1_C10 = 1;
    PI_CR2_C20 = 1;
    
    PG_DDR_DDR4 = 1;
    PG_CR1_C14 = 1;
    PG_CR2_C24 = 1;
    
    PG_DDR_DDR3 = 1;
    PG_CR1_C13 = 1;
    PG_CR2_C23 = 1;
    
    PG_DDR_DDR2 = 1;
    PG_CR1_C12 = 1;
    PG_CR2_C22 = 1;
    
    PG_DDR_DDR1 = 1;
    PG_CR1_C11 = 1;
    PG_CR2_C21 = 1;
    
    PG_DDR_DDR0 = 1;
    PG_CR1_C10 = 1;
    PG_CR2_C20 = 1;
    
    PC_DDR_DDR7 = 1;
    PC_CR1_C17 = 1;
    PC_CR2_C27 = 1;
    
    PC_DDR_DDR6 = 1;
    PC_CR1_C16 = 1;
    PC_CR2_C26 = 1;
    
    PC_DDR_DDR5 = 1;
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 1;
    
    PC_DDR_DDR4 = 1;
    PC_CR1_C14 = 1;
    PC_CR2_C24 = 1;
    
    PC_DDR_DDR3 = 1;
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 1;
    
    PC_DDR_DDR2 = 1;
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 1;
    
    PC_DDR_DDR1 = 1;
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 1;
    
    PE_DDR_DDR5 = 1;
    PE_CR1_C15 = 1;
    PE_CR2_C25 = 1;
    
    PE_DDR_DDR6 = 1;
    PE_CR1_C16 = 1;
    PE_CR2_C26 = 1;
    
    PE_DDR_DDR7 = 1;
    PE_CR1_C17 = 1;
    PE_CR2_C27 = 1;
    
    PA_DDR_DDR6 = 1;
    PA_CR1_C16 = 1;
    PA_CR2_C26 = 1;
    
    PD_DDR_DDR7 = 1;
    PD_CR1_C17 = 1;
    PD_CR2_C27 = 1;
    
    PD_DDR_DDR6 = 1;
    PD_CR1_C16 = 1;
    PD_CR2_C26 = 1;
    
    PD_DDR_DDR5 = 1;
    PD_CR1_C15 = 1;
    PD_CR2_C25 = 1;
    
    PD_DDR_DDR4 = 1;
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 1;
    
    PD_DDR_DDR3 = 1;
    PD_CR1_C13 = 1;
    PD_CR2_C23 = 1;
    
    PD_DDR_DDR2 = 1;
    PD_CR1_C12 = 1;
    PD_CR2_C22 = 1;
    
    PD_DDR_DDR0 = 1;
    PD_CR1_C10 = 1;
    PD_CR2_C20 = 1;
    
    PE_DDR_DDR0 = 1;
    PE_CR1_C10 = 1;
    PE_CR2_C20 = 1;
    
    PE_DDR_DDR3 = 1;
    PE_CR1_C13 = 1;
    PE_CR2_C23 = 1;
    
    PE_DDR_DDR4 = 1;
    PE_CR1_C14 = 1;
    PE_CR2_C24 = 1;
    
    PG_DDR_DDR7 = 1;
    PG_CR1_C17 = 1;
    PG_CR2_C27 = 1;
        
    for(u8 i = 0; i < 28;i++) {
        FanSelect(i,0);
    }
    
    for(u8 i = 0; i < 28;i++) {
        fan_Arr[i].speed = 0x00;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelect(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 测试  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSelect(u8 cmd ,u8 dr) {
    switch( cmd ) {
    case 0:
        FAN_0 = dr;
        break;
    case 1:
        FAN_1 = dr;
        break;
    case 2:
        FAN_2 = dr;
        break;
    case 3:
        FAN_3 = dr;
        break;
    case 4:
        FAN_4 = dr;
        break;
    case 5:
        FAN_5 = dr;
        break;
    case 6:
        FAN_6 = dr;
        break;
    case 7:
        FAN_7 = dr;
        break;
    case 8:
        FAN_8 = dr;
        break;
    case 9:
        FAN_9 = dr;
        break;
    case 10:
        FAN_10 = dr;
        break;
    case 11:
        FAN_11 = dr;
        break;
    case 12:
        FAN_12 = dr;
        break;
    case 13:
        FAN_13 = dr;
        break;
    case 14:
        FAN_14 = dr;
        break;
    case 15:
        FAN_15 = dr;
        break;
    case 16:
        FAN_16 = dr;
        break;
    case 17:
        FAN_17 = dr;
        break;
    case 18:
        FAN_18 = dr;
        break;
    case 19:
        FAN_19 = dr;
        break;
    case 20:
        FAN_20 = dr;
        break;
    case 21:
        FAN_21 = dr;
        break;
    case 22:
        FAN_22 = dr;
        break;
    case 23:
        FAN_23 = dr;
        break;
    case 24:
        FAN_24 = dr;
        break;
    case 25:
        FAN_25 = dr;
        break;
    case 26:
        FAN_26 = dr;
        break;
    case 27:
        FAN_27 = dr;
        break;
    default:
        break;
    }
    

}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSetSer(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇控制服务函数  
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void FanSetSer(void) { 
    static u8 fan_count = 0;
    /*总周期计数*/
    if(fan_count < 250) {
        fan_count++;
    } else {
        fan_count = 0;
    }
    /*风扇*/
    for(u8 i = 0;i < 28;i++) {
        if(fan_count < fan_Arr[i].speed) {
            if(fan_Arr[i].dr == 0) {
                fan_Arr[i].dr = 1;
                FanSelect(i,1);
            }
        } else {
            if(fan_Arr[i].dr == 1) {
                fan_Arr[i].dr = 0;
                FanSelect(i,0);
            }
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSpeedSet(u8 chx, u8 speed) 
* 输入参数: u8 chx, u8 speed 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
void FanSpeedSet(u8 chx, u8 speed) { 
    if(huai[chx] == 1) {
        fan_Arr[chx].speed = speed;
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanAllSet(u8 mode) 
* 输入参数: u8 mode 
* 返回参数: void  
* 功    能: mode 0:全部关闭 1：全部打开 2：半流  
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
void FanAllSet(u8 mode) { 
    if(mode == 0) {
        for(u8 i = 0; i < 28;i++) {
            fan_Arr[i].speed = 0x00;
        }
    } else if(mode == 1) {
        for(u8 i = 0; i < 28;i++) {
            if(huai[i] == 1) {
                fan_Arr[i].speed = 0xff;
            }
        }
    } else if(mode == 2) {
        for(u8 i = 0; i < 28;i++) {
            if(huai[i] == 1) {
                fan_Arr[i].speed = 0x7f;
            }
        }
    }
}
/**********************************************函数定义***************************************************** 
* 函数名称: void FanSelfInspection(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能: 风扇自检  
* 作    者: by lhb_steven
* 日    期: 2016/8/24
************************************************************************************************************/ 
u8 FanSelfInspection(void) { 
    u16 spec[7][7];
    u8 fazhi_num = 0;//故障数量
    u8 haha = 0;
    for(u8 h = 0;h < 28;h++) {
        huai_arr[h] = 0x00;
    }
    for(u8 h = 0;h < 7;h++) {
        cur_all[h] = 0x00;
    }
    for(u8 i = 0; i < 28;i++) {
        fan_Arr[i].speed = 0;
    }
    DelayMs(500);
    for(u8 a_i = 0;a_i < 4;a_i++) {
        for(u8 i = 0; i < 28;i++) {
            fan_Arr[i].speed = 0;
        }
        DelayMs(100);
        switch( a_i ) {
        case 0:
            fan_Arr[0].speed = 255;
            fan_Arr[4].speed = 255;
            fan_Arr[8].speed = 255;
            fan_Arr[12].speed = 255;
            fan_Arr[16].speed = 255;
            fan_Arr[20].speed = 255;
            fan_Arr[24].speed = 255;
            DelayMs(10);
            break;
        case 1:
            fan_Arr[1].speed = 255;
            fan_Arr[5].speed = 255;
            fan_Arr[9].speed = 255;
            fan_Arr[13].speed = 255;
            fan_Arr[17].speed = 255;
            fan_Arr[21].speed = 255;
            fan_Arr[25].speed = 255;
            DelayMs(10);
            break;
        case 2:
            fan_Arr[2].speed = 255;
            fan_Arr[6].speed = 255;
            fan_Arr[10].speed = 255;
            fan_Arr[14].speed = 255;
            fan_Arr[18].speed = 255;
            fan_Arr[22].speed = 255;
            fan_Arr[26].speed = 255;
            DelayMs(10);
            break;
        case 3:
            fan_Arr[3].speed = 255;
            fan_Arr[7].speed = 255;
            fan_Arr[11].speed = 255;
            fan_Arr[15].speed = 255;
            fan_Arr[19].speed = 255;
            fan_Arr[23].speed = 255;
            fan_Arr[27].speed = 255;
            DelayMs(10);
            break;
        default:
            break;
        }
        for(u8 j = 0;j < 6;j++) {
            DelayMs(50);
            for(u8 nj = 0;nj < 7;nj++) {
                spec[nj][j] = ElecurGet(nj);
            }
        }
        //查询风扇情况
        for(u8 x = 0;x < 7;x++) {
            u16 fazhi = 0;
            if(spec[x][0] > 7000) {
                fazhi = 3000;
            } else if(spec[x][0] > 5000) {
                fazhi = 500;
            } else if(spec[x][0] > 4000) { 
                fazhi = 350;
            } else if(spec[x][0] > 2200) { 
                fazhi = 350;
            } else {
                fazhi = 10000;
            }
            if(spec[x][0] > spec[x][5]) {
                if( (spec[x][0] - spec[x][5]) > fazhi) {
                    huai[a_i+(x*4)] = 1;
                    //cur_all[x] += spec[x][5];
                } else {
                    //错误
                    huai[a_i+(x*4)] = 0;
                    huai_arr[fazhi_num] = ((a_i+(x*4))+1);
                    fazhi_num++;
                }
            } else {
                //错误
                huai[a_i+(x*4)] = 0;
                huai_arr[fazhi_num] = ((a_i+(x*4))+1);
                fazhi_num++;
            }
            haha++;
        }
    }
    //记录电流
    FanAllSet(1);
    DelayMs(150);
    for(u8 nj = 0;nj < 7;nj++) {
        cur_all[nj] = ElecurGet(nj);
    }
    //关闭所有风扇
    for(u8 i = 0; i < 28;i++) {
        fan_Arr[i].speed = 0;
    }
    return fazhi_num;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u8 FanErrorNum(u8 num) 
* 输入参数: u8 num 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u8 FanErrorNum(u8 num) { 
    return huai_arr[num];
}
/**********************************************函数定义***************************************************** 
* 函数名称: u16 FanGetAllcur(u8 num) 
* 输入参数: u8 num 
* 返回参数: u16  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/25
************************************************************************************************************/ 
u16 FanGetAllcur(u8 num) { 
    return cur_all[num];
}














