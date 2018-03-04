/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: target_timer.h 1724 2010-01-31 13:07:24Z ertl-hiro $
 */

/*
 *		�����ޥɥ饤�С�Mac OS X�ѡ�
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

#include <sil.h>
#include "macosx.h"
#ifndef TOPPERS_MACRO_ONLY
#include <sys/time.h>
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
#define INHNO_TIMER		SIGALRM				/* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER		SIGALRM				/* ������ֹ� */
#define INTPRI_TIMER	(TMAX_INTPRI - 1)	/* �����ͥ���� */
#define INTATR_TIMER	TA_EDGE				/* �����°�� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �������ͤ�����ɽ���η�
 */
typedef uint32_t	CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á��ޥ�������ñ�̤Ȥ��Ѵ�
 *
 *  Mac OS X�Ǥϡ����󥿡��Х륿���ޤ�1�ޥ���������˥�����ȥ��åפ��롥
 */
#define TIMER_CLOCK				1000U
#define TO_CLOCK(nume, deno)	((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define TO_USEC(clock)			((SYSUTM) clock)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK		((CLOCK) 999999U)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
extern void	target_timer_initialize(intptr_t exinf);

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
extern void	target_timer_terminate(intptr_t exinf);

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
extern CLOCK target_timer_get_current(void);

/*
 *  �����޳�����׵�Υ����å�
 */
extern bool_t target_timer_probe_int(void);

#ifdef TOPPERS_SUPPORT_OVRHDR

/*
 *  �����Х�󥿥��ޤν��������
 */
extern void target_ovrtimer_initialize(intptr_t exinf);

/*
 *  �����Х�󥿥��ޤ���߽���
 */
extern void target_ovrtimer_terminate(intptr_t exinf);

/*
 *  �����Х�󥿥��ޤ�ư���
 */
extern void target_ovrtimer_start(OVRTIM ovrtim);

/*
 *  �����Х�󥿥��ޤ����
 */
extern OVRTIM target_ovrtimer_stop(void);

/*
 *  �����Х�󥿥��ޤθ����ͤ��ɽФ�
 */
extern OVRTIM target_ovrtimer_get_current(void);

#endif /* TOPPERS_SUPPORT_OVRHDR */

/*
 *  �����޳���ߥϥ�ɥ�
 */
extern void	target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_TIMER_H */
