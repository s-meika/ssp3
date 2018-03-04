/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2017 by Meika Sugimoto
 *
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 */

#include "kernel_impl.h"

/*
 *  �����ͥ�Υץ��å���¸����RL78/G13�ѡ�
 */


/* �������׵�ե饰���쥸���� */
#define IF0L_ADDR ((volatile __far uint8_t *)0xFFFE0)
#define IF0H_ADDR ((volatile __far uint8_t *)0xFFFE1)
#define IF1L_ADDR ((volatile __far uint8_t *)0xFFFE2)
#define IF1H_ADDR ((volatile __far uint8_t *)0xFFFE3)
#define IF2L_ADDR ((volatile __far uint8_t *)0xFFFD0)
#define IF2H_ADDR ((volatile __far uint8_t *)0xFFFD1)
#define IF3L_ADDR ((volatile __far uint8_t *)0xFFFD2)

/* �����ߥޥ������ե饰���쥸���� */
#define MK0L_ADDR ((volatile __far uint8_t *)0xFFFE4)
#define MK0H_ADDR ((volatile __far uint8_t *)0xFFFE5)
#define MK1L_ADDR ((volatile __far uint8_t *)0xFFFE6)
#define MK1H_ADDR ((volatile __far uint8_t *)0xFFFE5)
#define MK2L_ADDR ((volatile __far uint8_t *)0xFFFD4)
#define MK2H_ADDR ((volatile __far uint8_t *)0xFFFD5)
#define MK3L_ADDR ((volatile __far uint8_t *)0xFFFD6)

/* ͥ���̻���ե饰���쥸���� */
#define PR00L_ADDR ((volatile __far uint8_t *)0xFFFE8)
#define PR10L_ADDR ((volatile __far uint8_t *)0xFFFEC)
#define PR00H_ADDR ((volatile __far uint8_t *)0xFFFE9)
#define PR10H_ADDR ((volatile __far uint8_t *)0xFFFED)
#define PR01L_ADDR ((volatile __far uint8_t *)0xFFFEA)
#define PR11L_ADDR ((volatile __far uint8_t *)0xFFFEE)
#define PR01H_ADDR ((volatile __far uint8_t *)0xFFFEB)
#define PR11H_ADDR ((volatile __far uint8_t *)0xFFFEF)
#define PR02L_ADDR ((volatile __far uint8_t *)0xFFFD8)
#define PR12L_ADDR ((volatile __far uint8_t *)0xFFFDC)
#define PR02H_ADDR ((volatile __far uint8_t *)0xFFFD9)
#define PR12H_ADDR ((volatile __far uint8_t *)0xFFFDD)
#define PR03L_ADDR ((volatile __far uint8_t *)0xFFFDA)
#define PR13L_ADDR ((volatile __far uint8_t *)0xFFFDE)

/* ����������Ω���夬�ꥨ�å����ĥ쥸���� */
#define EGP0_ADDR ((volatile __far uint8_t *)0xFFF38)
#define EGP1_ADDR ((volatile __far uint8_t *)0xFFF3A)
#define EGN0_ADDR ((volatile __far uint8_t *)0xFFF39)
#define EGN1_ADDR ((volatile __far uint8_t *)0xFFF3B)



/* ������������ơ��֥� */
RL78G13_INTCTL_INFO const intctl_reg_table[RL78_G13_INTNO_MAX+1] = 
{
	/* 00:WDT */
	{
		{ IF0L_ADDR, 1U  << 0 },
		{ MK0L_ADDR, 1U  << 0 },
		{ PR00L_ADDR, 1U << 0 },
		{ PR10L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 01:INTLVL */
	{
		{ IF0L_ADDR, 1U  << 1 },
		{ MK0L_ADDR, 1U  << 1 },
		{ PR00L_ADDR, 1U << 1 },
		{ PR10L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 02:INT0 */
	{
		{ IF0L_ADDR, 1U  << 2 },
		{ MK0L_ADDR, 1U  << 2 },
		{ PR00L_ADDR, 1U << 2 },
		{ PR10L_ADDR, 1U << 2 },
		{ EGP0_ADDR, 1U  << 0 },
		{ EGN0_ADDR, 1U  << 0 }
	},
	/* 03:INT1 */
	{
		{ IF0L_ADDR, 1U  << 3 },
		{ MK0L_ADDR, 1U  << 3 },
		{ PR00L_ADDR, 1U << 3 },
		{ PR10L_ADDR, 1U << 3 },
		{ EGP0_ADDR, 1U  << 1 },
		{ EGN0_ADDR, 1U  << 1 }
	},
	/* 04:INT2 */
	{
		{ IF0L_ADDR, 1U  << 4 },
		{ MK0L_ADDR, 1U  << 4 },
		{ PR00L_ADDR, 1U << 4 },
		{ PR10L_ADDR, 1U << 4 },
		{ EGP0_ADDR, 1U  << 2 },
		{ EGN0_ADDR, 1U  << 2 }
	},
	/* 05:INT3 */
	{
		{ IF0L_ADDR, 1U  << 5 },
		{ MK0L_ADDR, 1U  << 5 },
		{ PR00L_ADDR, 1U << 5 },
		{ PR10L_ADDR, 1U << 5 },
		{ EGP0_ADDR, 1U  << 3 },
		{ EGN0_ADDR, 1U  << 3 }
	},
	/* 06::INT4 */
	{
		{ IF0L_ADDR, 1U  << 6 },
		{ MK0L_ADDR, 1U  << 6 },
		{ PR00L_ADDR, 1U << 6 },
		{ PR10L_ADDR, 1U << 6 },
		{ EGP0_ADDR, 1U  << 4 },
		{ EGN0_ADDR, 1U  << 4 }
	},
	/* 07:INT5 */
	{
		{ IF0L_ADDR, 1U  << 7 },
		{ MK0L_ADDR, 1U  << 7 },
		{ PR00L_ADDR, 1U << 7 },
		{ PR10L_ADDR, 1U << 7 },
		{ EGP0_ADDR, 1U  << 5 },
		{ EGN0_ADDR, 1U  << 5 }
	},
	/* 08:UART2 TX */
	{
		{ IF0H_ADDR, 1U  << 0 },
		{ MK0H_ADDR, 1U  << 0 },
		{ PR00H_ADDR, 1U << 0 },
		{ PR10H_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 09:UART2 RX */
	{
		{ IF0H_ADDR, 1U  << 1 },
		{ MK0H_ADDR, 1U  << 1 },
		{ PR00H_ADDR, 1U << 1 },
		{ PR10H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 10:UART2 ERROR or TIMER 11 */
	{
		{ IF0H_ADDR, 1U  << 2 },
		{ MK0H_ADDR, 1U  << 2 },
		{ PR00H_ADDR, 1U << 2 },
		{ PR10H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 11:DMA0 */
	{
		{ IF0H_ADDR, 1U  << 3 },
		{ MK0H_ADDR, 1U  << 3 },
		{ PR00H_ADDR, 1U << 3 },
		{ PR10H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 12:DMA1 */
	{
		{ IF0H_ADDR, 1U  << 4 },
		{ MK0H_ADDR, 1U  << 4 },
		{ PR00H_ADDR, 1U << 4 },
		{ PR10H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 13:UART0 TX */
	{
		{ IF0H_ADDR, 1U  << 5 },
		{ MK0H_ADDR, 1U  << 5 },
		{ PR00H_ADDR, 1U << 5 },
		{ PR10H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 14:UART0 RX */
	{
		{ IF0H_ADDR, 1U  << 6 },
		{ MK0H_ADDR, 1U  << 6 },
		{ PR00H_ADDR, 1U << 6 },
		{ PR10H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 15:UART0 ERROR or TIMER 01 */
	{
		{ IF0H_ADDR, 1U  << 7 },
		{ MK0H_ADDR, 1U  << 7 },
		{ PR00H_ADDR, 1U << 7 },
		{ PR10H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 16:UART1 TX */
	{
		{ IF1L_ADDR, 1U  << 0 },
		{ MK1L_ADDR, 1U  << 0 },
		{ PR01L_ADDR, 1U << 0 },
		{ PR10L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 17:UART1 RX */
	{
		{ IF1L_ADDR, 1U  << 1 },
		{ MK1L_ADDR, 1U  << 1 },
		{ PR01L_ADDR, 1U << 1 },
		{ PR10L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 18:UART1 ERROR or TIMER 03 */
	{
		{ IF1L_ADDR, 1U  << 2 },
		{ MK1L_ADDR, 1U  << 2 },
		{ PR01L_ADDR, 1U << 2 },
		{ PR10L_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 19:IICA0 */
	{
		{ IF1L_ADDR, 1U  << 3 },
		{ MK1L_ADDR, 1U  << 3 },
		{ PR01L_ADDR, 1U << 3 },
		{ PR10L_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 20:������00 */
	{
		{ IF1L_ADDR, 1U  << 4 },
		{ MK1L_ADDR, 1U  << 4 },
		{ PR01L_ADDR, 1U << 4 },
		{ PR10L_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 21:������01 */
	{
		{ IF1L_ADDR, 1U  << 5 },
		{ MK1L_ADDR, 1U  << 5 },
		{ PR01L_ADDR, 1U << 5 },
		{ PR10L_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 22:������02 */
	{
		{ IF1L_ADDR, 1U  << 6 },
		{ MK1L_ADDR, 1U  << 6 },
		{ PR01L_ADDR, 1U << 6 },
		{ PR10L_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 23:������03 */
	{
		{ IF1L_ADDR, 1U  << 7 },
		{ MK1L_ADDR, 1U  << 7 },
		{ PR01L_ADDR, 1U << 7 },
		{ PR10L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 24:AD�Ѵ���λ */
	{
		{ IF1H_ADDR, 1U  << 0 },
		{ MK1H_ADDR, 1U  << 0 },
		{ PR01H_ADDR, 1U << 0 },
		{ PR10H_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 25:RTC */
	{
		{ IF1H_ADDR, 1U  << 1 },
		{ MK1H_ADDR, 1U  << 1 },
		{ PR01H_ADDR, 1U << 1 },
		{ PR10H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 26:12bit ���󥿡��Х륿���� */
	{
		{ IF1H_ADDR, 1U  << 2 },
		{ MK1H_ADDR, 1U  << 2 },
		{ PR01H_ADDR, 1U << 2 },
		{ PR10H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 27:�����꥿���� */
	{
		{ IF1H_ADDR, 1U  << 3 },
		{ MK1H_ADDR, 1U  << 3 },
		{ PR01H_ADDR, 1U << 3 },
		{ PR10H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 28:UART30 TX */
	{
		{ IF1H_ADDR, 1U  << 4 },
		{ MK1H_ADDR, 1U  << 4 },
		{ PR01H_ADDR, 1U << 4 },
		{ PR10H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 29:UART30 RX */
	{
		{ IF1H_ADDR, 1U  << 5 },
		{ MK1H_ADDR, 1U  << 5 },
		{ PR01H_ADDR, 1U << 5 },
		{ PR10H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 30:UART30 ERROR or TIMER 13 */
	{
		{ IF1H_ADDR, 1U  << 6 },
		{ MK1H_ADDR, 1U  << 6 },
		{ PR01H_ADDR, 1U << 6 },
		{ PR10H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 31:������04 */
	{
		{ IF1H_ADDR, 1U  << 7 },
		{ MK0H_ADDR, 1U  << 7 },
		{ PR01H_ADDR, 1U << 7 },
		{ PR10H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 32:������05 */
	{
		{ IF2L_ADDR, 1U  << 0 },
		{ MK2L_ADDR, 1U  << 0 },
		{ PR02L_ADDR, 1U << 0 },
		{ PR12L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 33:������06 */
	{
		{ IF2L_ADDR, 1U  << 1 },
		{ MK2L_ADDR, 1U  << 1 },
		{ PR02L_ADDR, 1U << 1 },
		{ PR12L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 34:������07 */
	{
		{ IF2L_ADDR, 1U  << 2 },
		{ MK2L_ADDR, 1U  << 2 },
		{ PR02L_ADDR, 1U << 2 },
		{ PR12L_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 35:INT6 */
	{
		{ IF2L_ADDR, 1U  << 3 },
		{ MK2L_ADDR, 1U  << 3 },
		{ PR02L_ADDR, 1U << 3 },
		{ PR12L_ADDR, 1U << 3 },
		{ EGP0_ADDR, 1U  << 6 },
		{ EGN0_ADDR, 1U  << 6 }
	},
	/* 36:INT7 */
	{
		{ IF2L_ADDR, 1U  << 4 },
		{ MK2L_ADDR, 1U  << 4 },
		{ PR02L_ADDR, 1U << 4 },
		{ PR12L_ADDR, 1U << 4 },
		{ EGP0_ADDR, 1U  << 7 },
		{ EGN0_ADDR, 1U  << 7 }
	},
	/* 37:INT8 */
	{
		{ IF2L_ADDR, 1U  << 5 },
		{ MK2L_ADDR, 1U  << 5 },
		{ PR02L_ADDR, 1U << 5 },
		{ PR12L_ADDR, 1U << 5 },
		{ EGP1_ADDR, 1U  << 0 },
		{ EGN1_ADDR, 1U  << 0 }
	},
	/* 38:INT9 */
	{
		{ IF2L_ADDR, 1U  << 6 },
		{ MK2L_ADDR, 1U  << 6 },
		{ PR02L_ADDR, 1U << 6 },
		{ PR12L_ADDR, 1U << 6 },
		{ EGP1_ADDR, 1U  << 1 },
		{ EGN1_ADDR, 1U  << 1 }
	},
	/* 39:INT10 */
	{
		{ IF2L_ADDR, 1U  << 7 },
		{ MK2L_ADDR, 1U  << 7 },
		{ PR02L_ADDR, 1U << 7 },
		{ PR12L_ADDR, 1U << 7 },
		{ EGP1_ADDR, 1U  << 2 },
		{ EGN1_ADDR, 1U  << 2 }
	},
	/* 40:INT11 */
	{
		{ IF2H_ADDR, 1U  << 0 },
		{ MK2H_ADDR, 1U  << 0 },
		{ PR02H_ADDR, 1U << 0 },
		{ PR12H_ADDR, 1U << 0 },
		{ EGP1_ADDR, 1U  << 3 },
		{ EGN1_ADDR, 1U  << 3 }
	},
	/* 41:������10 */
	{
		{ IF2H_ADDR, 1U  << 1 },
		{ MK2H_ADDR, 1U  << 1 },
		{ PR02H_ADDR, 1U << 1 },
		{ PR12H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 42:������11 */
	{
		{ IF2H_ADDR, 1U  << 2 },
		{ MK2H_ADDR, 1U  << 2 },
		{ PR02H_ADDR, 1U << 2 },
		{ PR12H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 43:������12 */
	{
		{ IF2H_ADDR, 1U  << 3 },
		{ MK2H_ADDR, 1U  << 3 },
		{ PR02H_ADDR, 1U << 3 },
		{ PR12H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 44:������13 or UART3 ERROR */
	{
		{ IF2H_ADDR, 1U  << 4 },
		{ MK2H_ADDR, 1U  << 4 },
		{ PR02H_ADDR, 1U << 4 },
		{ PR12H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 45:������λ�����±黻�����С��ե� */
	{
		{ IF2H_ADDR, 1U  << 5 },
		{ MK2H_ADDR, 1U  << 5 },
		{ PR02H_ADDR, 1U << 5 },
		{ PR12H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 46:IICA1	 */
	{
		{ IF2H_ADDR, 1U  << 6 },
		{ MK2H_ADDR, 1U  << 6 },
		{ PR02H_ADDR, 1U << 6 },
		{ PR12H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 47:ͽ�� */
	{
		{ IF2H_ADDR, 1U  << 7 },
		{ MK2H_ADDR, 1U  << 7 },
		{ PR02H_ADDR, 1U << 7 },
		{ PR12H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 48:DMA2 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 49:DMA3 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 50:������14 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 51:������15 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 52:������16 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 53:������17 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	}
};

/*
 *  ���åװ�¸���ν���� 
 */
void chip_initialize(void)
{
	/* �ץ��å���¸�ν���� */
	prc_initialize();
}

