/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改変・
 *  再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作権
 *      表示，この利用条件および下記の無保証規定が，そのままの形でソース
 *      コード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使用
 *      できる形で再配布する場合には，再配布に伴うドキュメント（利用者マ
 *      ニュアルなど）に，上記の著作権表示，この利用条件および下記の無保
 *      証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使用
 *      できない形で再配布する場合には，次のいずれかの条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに報
 *        告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損害
 *      からも，上記著作権者およびTOPPERSプロジェクトを免責すること．また，
 *      本ソフトウェアのユーザまたはエンドユーザからのいかなる理由に基づ
 *      く請求からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者およ
 *  びTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的に対す
 *  る適合性も含めて，いかなる保証も行わない．また，本ソフトウェアの利用
 *  により直接的または間接的に生じたいかなる損害に関しても，その責任を負
 *  わない．
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
