/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：Ntc.c
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
#include "Ntc.h"

//===============================================
// 换算温度表
// 测温范围为：[0℃,100℃]
// 测温电阻为: 10KΩ
// 5V电压的10位AD模拟数值
//===============================================
static const u16 TempH_Tab[] = 
{ /*
    241,246,250,255,260,265,270,275,280,285,  // 0.0°~  4.5°
    290,295,300,305,311,316,321,326,332,337,  // 5.0°~   9.5°
    343,348,354,359,365,370,376,381,387,393,  // 10.0°~  14.5°
    398,404,410,415,421,427,432,438,444,450,  // 15.0°~  19.5°	
    455,461,467,472,478,484,489,495,501,506,  // 20.0°~  24.5°	
    512,518,523,529,534,540,545,551,556,561,  // 25.0°~  29.5°	
    567,573,578,583,589,594,599,604,609,615,  // 30.0°~  34.5°	
    620,625,630,635,640,645,649,654,659,664,  // 35.0°~  39.5°
    669,673,678,682,687,691,696,700,705,709,  // 40.0°~  44.5°
    713,718,722,726,730,734,738,742,746,750,  // 45.0°~  49.5°	
    754,757,761,765,768,772,776,779,783,786,  // 50.0°~  54.5°
    790,793,796,799,803,806,809,812,815,818,  // 55.0°~  59.5°							  
    821,824,827,830,833,835,838,841,844,846,  // 60.0°~  64.5°
    849,851,854,856,859,861,864,866,868,870,  // 65.0°~  69.5°
    873,875,877,879,881,883,885,887,889,891,  // 70.0°~  74.5°
    893,895,897,899,901,903,904,906,908,909,  // 75.0°~  79.5°
    911,913,914,916,918,919,921,922,924,925,  // 80.0°~  84.5°
    926,928,929,931,932,933,934,936,937,938,  // 85.0°~  89.5°
    939,941,942,943,944,945,946,948,949,950,  // 90.0°~  94.5°
    951,952,953,954,955,956,957,958,958,959,  // 95.0°~  99.5°
    960                                       // 100.0°
    */
    15419,15719,16022,16328,16638,16950,17265,17582,17903,18226,// 0.0°~  4.5°
    18552,18880,19211,19544,19880,20217,20557,20899,21243,21589,// 5.0°~   9.5°
    21937,22286,22637,22990,23344,23700,24057,24415,24774,25134,// 10.0°~  14.5°
    25495,25857,26220,26583,26947,27311,27676,28041,28406,28772,// 15.0°~  19.5°
    29137,29502,29867,30231,30596,30959,31322,31685,32047,32407,// 20.0°~  24.5°	
    32768,33126,33484,33841,34197,34551,34904,35255,35605,35953,// 25.0°~  29.5°
    36299,36644,36987,37328,37667,38004,38339,38672,39003,39332,// 30.0°~  34.5°
    39658,39982,40303,40623,40940,41254,41566,41875,42182,42486,// 35.0°~  39.5°
    42787,43086,43382,43676,43966,44254,44539,44822,45101,45378,// 40.0°~  44.5°
    45652,45923,46191,46456,46719,46978,47235,47489,47740,47988,// 45.0°~  49.5°
    48234,48476,48716,48952,49186,49417,49646,49871,50094,50314,// 50.0°~  54.5°
    50531,50746,50957,51166,51373,51576,51777,51975,52171,52364,// 55.0°~  59.5°	
    52554,52742,52928,53110,53290,53468,53644,53816,53987,54155,// 60.0°~  64.5°
    54321,54484,54645,54804,54961,55115,55267,55417,55565,55710,// 65.0°~  69.5°
    55853,55995,56134,56272,56407,56540,56671,56800,56928,57053,// 70.0°~  74.5°
    57176,57298,57418,57536,57653,57767,57880,57991,58101,58209,// 75.0°~  79.5°
    58315,58420,58522,58624,58724,58822,58919,59014,59108,59201,// 80.0°~  84.5°
    59292,59381,59470,59557,59642,59727,59809,59891,59971,60051,// 85.0°~  89.5°
    60129,60206,60281,60356,60429,60501,60572,60642,60711,60779,// 90.0°~  94.5°
    60846,60912,60976,61040,61103,61165,61226,61286,61345,61403,// 95.0°~  99.5°
    61460,// 100.0°
};
//===============================================
// 换算温度表
// 测温范围为：[0℃,-30℃]
// 测温电阻为: 10KΩ
// 5V电压的10位AD模拟数值
//===============================================
static const u16 TempL_Tab[] = 
{ 
    /*
    241,236,232,227,223,218,214,209,205,201,  //  0.0°~  -4.5°
    197,193,189,185,181,177,173,169,165,162,  // -5.0°~  -9.5°
    158,154,151,148,144,141,137,134,131,128,  // -10.0°~  -14.5°
    125,122,119,116,113,110,108,105,102,100,  // -15.0°~  -19.5°	
    97, 95, 93, 91, 89, 87, 85, 83, 81, 79,  // -20.0°~ -24.5°
    77, 75, 73, 71, 70, 68, 66, 64, 62, 60,  // -25.0°~ -29.5°
    59, 58                                    // -30.0,-30.5°
    */
    15419,15122,14828,14537,14250,13966,13685,13408,13134,12863,//  0.0°~  -4.5°
    12596,12332,12072,11816,11562,11313,11067,10824,10585,10350,// -5.0°~  -9.5°
    10118, 9890, 9665, 9444,9227, 9013,  8803, 8596, 8392, 8193, // -10.0°~  -14.5
    7996,  7804, 7614, 7428,7246, 7067,  6891, 6719, 6550, 6384,6221, // -15.0°~  -19.5°
};
/**********************************************函数定义***************************************************** 
* 函数名称: void NtcInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
void NtcInit(void) { 
    PB_DDR_DDR7 = 0;
    PB_CR1_C17 = 0;
    PB_CR2_C27 = 0;
    
    PF_DDR_DDR0 = 0;
    PF_CR1_C10 = 0;
    PF_CR2_C20 = 0;
    
    PF_DDR_DDR3= 0;
    PF_CR1_C13 = 0;
    PF_CR2_C23 = 0;
    
    PF_DDR_DDR4 = 0;
    PF_CR1_C14 = 0;
    PF_CR2_C24 = 0;
    
    PF_DDR_DDR5 = 0;
    PF_CR1_C15 = 0;
    PF_CR2_C25 = 0;
    
    PF_DDR_DDR6 = 0;
    PF_CR1_C16 = 0;
    PF_CR2_C26 = 0;
    
    ADC_CSR &= ~BIT(6);
	ADC_CSR &= ~BIT(4);
    ADC_CR1 |= 0x70;
	ADC_CR1 |= BIT(1);
	ADC_CR2 |= BIT(1);
	ADC_TDRL = 0x01;
}

u16 NtcJud(u16 dat,u8 f)  // 获得温度数据 ；
{
    u8 k;
    u16  tmp,buf;
    k = 0;
    tmp = 0;
    while(1)
    {
        if(f==1) // 检索正温度
        {
            if(dat>=TempH_Tab[k]&&dat<=TempH_Tab[k+1])	 
            {
                buf = TempH_Tab[k+1]-TempH_Tab[k];	
                tmp = ((dat-TempH_Tab[k])*5)/buf;	
                tmp += (k/2)*10+(k%2)*5;
                break;
            }
            if(k>200)
            {
                break;
            }
        }
        else // 检索负温度
        {
            if(dat<=TempL_Tab[k]&&dat>=TempL_Tab[k+1])	 
            {
                buf = TempL_Tab[k]-TempL_Tab[k+1];	
                tmp = ((TempL_Tab[k]-dat)*5)/buf;	
                tmp += (k/2)*10+(k%2)*5;
                break;
            }		
            if(k>60)
            {
                break;
            }
        }
        k++;
    }
    return  tmp;
}
/**********************************************函数定义***************************************************** 
* 函数名称: u16 NtcGet(u8 chx) 
* 输入参数: u8 chx 
* 返回参数: u16  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
u16 NtcGet(u8 chx) { 
    u16 ad_value;
    u8 i,h = 0,l = 0;
    ADC_CSR = chx;
    ADC_CR1 = 0x01; // CR1 寄存器的最低位置1，使能ADC 转换
    for(i=0;i<100;i++); // 延时一段时间，至少7uS，保证ADC 模块的上电完成
    ADC_CR1 = ADC_CR1 | 0x01; // 再次将CR1 寄存器的最低位置1
    // 使能ADC 转换
    while((ADC_CSR & 0x80) == 0); // 等待ADC 结束
    h = ADC_DRH;
    l = ADC_DRL;
    ad_value = (h<<8) + l;
    return ad_value;
}
/**********************************************函数定义***************************************************** 
* 函数名称: float NtcGetTemp(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: float  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/23
************************************************************************************************************/ 
u16 NtcGetTemp(u8 cmd) { 
    u16 ad = 0;
    u16 temp = 0;
    switch( cmd ) {
    case 0:
        ad = NtcGet(7);
        break;
    case 1:
        ad = NtcGet(10);
        break;
    case 2:
        ad = NtcGet(11);
        break;
    case 3:
        ad = NtcGet(14);
        break;
    case 4:
        ad = NtcGet(13);
        break;
    case 5:
        ad = NtcGet(12);
        break;    
    default:
        break;
    }
    if(ad<=6221) // -30°以下
    {
        temp = 0;
    }
    else if(ad<15419)  // -30°~ 0°
    {
        temp = NtcJud(ad,0); // 温度转换 ；
        temp = 0;
    }
    else if(ad<=61460)  // 0°~ 99.5°
    {
        temp = NtcJud(ad,1); // 温度转换 ；
        temp = temp/10;
    }
    else  // 100°以上
    {
      temp = 99;		
    }
    return temp;

}