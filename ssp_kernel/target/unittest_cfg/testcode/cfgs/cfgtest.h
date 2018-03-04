/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�
 *  �����ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭�����
 *      ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ�����
 *      ��������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ����Ѽԥ�
 *      �˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ�����̵��
 *      �ڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻���
 *      �Ǥ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ���
 *        �𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»��
 *      ����⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ��ޤ���
 *      �ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���ͳ�˴��
 *      �����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ���
 *  ��TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū���Ф�
 *  ��Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ�����������
 *  �ˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ����
 *  ��ʤ���
 * 
 */

#ifndef _SAMPLE1_H_
#define _SAMPLE1_H_

#define TARGET_NAME "cfgtest"

#define STKSZ 10
#define EXINF1	(intptr_t)1
#define EXINF2	(intptr_t)2
#define EXINF3	(intptr_t)3
#define EXINF4	(intptr_t)4
#define EXINF5	(intptr_t)5
#define EXINF6	(intptr_t)6
#define EXINF7	(intptr_t)7
#define EXINF8	(intptr_t)8
#define EXINF9	(intptr_t)9
#define EXINF10	(intptr_t)10
#define EXINF11	(intptr_t)11
#define EXINF12	(intptr_t)12
#define EXINF13	(intptr_t)13
#define EXINF14	(intptr_t)14
#define EXINF15	(intptr_t)15
#define EXINF16	(intptr_t)16

#define CYCTIM1	100
#define CYCTIM2	100
#define CYCTIM3	100
#define CYCTIM4	100
#define CYCTIM5	100
#define CYCTIM6	100
#define CYCTIM7	100
#define CYCTIM8	100
#define CYCPHS1	5
#define CYCPHS2	5
#define CYCPHS3	5
#define CYCPHS4	5
#define CYCPHS5	5
#define CYCPHS6	5
#define CYCPHS7	5
#define CYCPHS8	5


#ifndef TOPPERS_MACRO_ONLY

/* TASK */
extern void task1(intptr_t exinf);
extern void task2(intptr_t exinf);
extern void task3(intptr_t exinf);
extern void task4(intptr_t exinf);
extern void task5(intptr_t exinf);
extern void task6(intptr_t exinf);
extern void task7(intptr_t exinf);
extern void task8(intptr_t exinf);
extern void task9(intptr_t exinf);
extern void task10(intptr_t exinf);
extern void task11(intptr_t exinf);
extern void task12(intptr_t exinf);
extern void task13(intptr_t exinf);
extern void task14(intptr_t exinf);
extern void task15(intptr_t exinf);
extern void task16(intptr_t exinf);

/* ATT_INI */
extern uint16_t test_bitmap_inirtn;

extern void inirtn_1(intptr_t exinf);
extern void inirtn_2(intptr_t exinf);
extern void inirtn_3(intptr_t exinf);
extern void inirtn_4(intptr_t exinf);
extern void inirtn_5(intptr_t exinf);
extern void inirtn_6(intptr_t exinf);
extern void inirtn_7(intptr_t exinf);
extern void inirtn_8(intptr_t exinf);

/* ATT_TER */
extern uint16_t test_bitmap_terrtn;

extern void terrtn_1(intptr_t exinf);
extern void terrtn_2(intptr_t exinf);
extern void terrtn_3(intptr_t exinf);
extern void terrtn_4(intptr_t exinf);
extern void terrtn_5(intptr_t exinf);
extern void terrtn_6(intptr_t exinf);
extern void terrtn_7(intptr_t exinf);
extern void terrtn_8(intptr_t exinf);

/* ATT_ISR */
extern void isr_15(intptr_t exinf);
extern void isr_15_1(intptr_t exinf);
extern void isr_15_2(intptr_t exinf);

/* DEF_INH */
extern void inthdr_15(void);


/* DEF_EXC */
extern void exchdr_2(intptr_t exinf);

/* CRE_ALM */
extern void almhdr1(intptr_t exinf);
extern void almhdr2(intptr_t exinf);
extern void almhdr3(intptr_t exinf);
extern void almhdr4(intptr_t exinf);
extern void almhdr5(intptr_t exinf);
extern void almhdr6(intptr_t exinf);
extern void almhdr7(intptr_t exinf);
extern void almhdr8(intptr_t exinf);
extern void almhdr9(intptr_t exinf);
extern void almhdr10(intptr_t exinf);
extern void almhdr11(intptr_t exinf);
extern void almhdr12(intptr_t exinf);
extern void almhdr13(intptr_t exinf);
extern void almhdr14(intptr_t exinf);
extern void almhdr15(intptr_t exinf);
extern void almhdr16(intptr_t exinf);

/* CRE_CYC */
extern void cychdr1(intptr_t exinf);
extern void cychdr2(intptr_t exinf);
extern void cychdr3(intptr_t exinf);
extern void cychdr4(intptr_t exinf);
extern void cychdr5(intptr_t exinf);
extern void cychdr6(intptr_t exinf);
extern void cychdr7(intptr_t exinf);
extern void cychdr8(intptr_t exinf);
extern void cychdr9(intptr_t exinf);
extern void cychdr10(intptr_t exinf);
extern void cychdr11(intptr_t exinf);
extern void cychdr12(intptr_t exinf);
extern void cychdr13(intptr_t exinf);
extern void cychdr14(intptr_t exinf);
extern void cychdr15(intptr_t exinf);
extern void cychdr16(intptr_t exinf);

/* DEF_ICS */
extern STK_T user_stack[];


#endif /* TOPPERS_MACRO_ONLY */
#endif
