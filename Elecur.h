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
* ������ڣ�2016/8/24
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#ifndef __ELECUR_H
#define __ELECUR_H

#include "Type.h"

/**********************************************��������***************************************************** 
* ��������: void ElecurInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
void ElecurInit(void);
/**********************************************��������***************************************************** 
* ��������: u16 ElecurGet(u8 chx) 
* �������: u8 chx 
* ���ز���: u16  
* ��    ��: ��ȡ����  
* ��    ��: by lhb_steven
* ��    ��: 2016/8/24
************************************************************************************************************/ 
u16 ElecurGet(u8 chx);

#endif

