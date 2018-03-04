/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
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
 *  @(#) $Id: target_timer.c 1861 2010-07-25 07:40:55Z ertl-hiro $
 */

/*
 *		�����ޥɥ饤�С�Mac OS X�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sys/time.h>
#include "target_timer.h"

#ifndef TOPPERS_SUPPORT_OVRHDR

/*
 *		�����Х��ϥ�ɥ鵡ǽ�򥵥ݡ��Ȥ��ʤ����
 */

#if 0
/*
 *		���󥿡��Х륿���ޤ���������ޤȤ��ƻ��Ѥ�����ˡ
 *
 *  ���󥿡��Х륿���ޤ���������ޤȤ��ƻ��Ѥ���Τ���ľ�Ǥ��뤬������
 *  ��Mac OS X�Ǥϡ�SIGALRM���������ٱ䤹�뤳�Ȥ����뤿�ᤫ�������ޤ���
 *  �μ����˿ʤ���ˤ⤫����餺��SIGALRM��������sigpending�Ǹ��ФǤ���
 *  ����礬���롥����ˤ�ꡤ��ǽɾ���ѥ����ƥ����λ��Ȥ�������ư��
 *  ���ʤ����ᡤ���Υ����ɤϻ��Ѥ��Ƥ��ʤ���
 */

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK	cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	struct itimerval	val;

	/*
	 *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	 */
	assert(cyc <= MAX_CLOCK);
	val.it_interval.tv_sec = 0;
	val.it_interval.tv_usec = cyc;
	val.it_value = val.it_interval;
	setitimer(ITIMER_REAL, &val, NULL);
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	struct itimerval	val;

	/*
	 *  �����ޤ�ư�����ߤ��롥
	 */
	val.it_interval.tv_sec = 0;
	val.it_interval.tv_usec = 0;
	val.it_value = val.it_interval;
	setitimer(ITIMER_REAL, &val, NULL);
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
CLOCK
target_timer_get_current(void)
{
	struct itimerval	val;

	getitimer(ITIMER_REAL, &val);
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - val.it_value.tv_usec);
}

/*
 *  �����޳�����׵�Υ����å�
 */
bool_t
target_timer_probe_int(void)
{
	return(x_probe_int(INTNO_TIMER));
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
	i_begin_int(INTNO_TIMER);
	signal_time();					/* ������ƥ��å��ζ��� */
	i_end_int(INTNO_TIMER);
}

#else /* 0 */
/*
 *		���󥿡��Х륿���ޤ��󥷥�åȥ����ޤȤ��ƻ��Ѥ�����ˡ
 */

/*
 *  �����ޤ�ư���
 */
Inline void
itimer_start(void)
{
	CLOCK	cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	struct itimerval	val;

	/*
	 *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	 */
	assert(cyc <= MAX_CLOCK);
	val.it_interval.tv_sec = 0;
	val.it_interval.tv_usec = 0;
	val.it_value.tv_sec = 0;
	val.it_value.tv_usec = cyc;
	setitimer(ITIMER_REAL, &val, NULL);
}

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	itimer_start();
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	struct itimerval	val;

	/*
	 *  �����ޤ�ư�����ߤ��롥
	 */
	val.it_interval.tv_sec = 0;
	val.it_interval.tv_usec = 0;
	val.it_value = val.it_interval;
	setitimer(ITIMER_REAL, &val, NULL);
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
CLOCK
target_timer_get_current(void)
{
	struct itimerval	val;

	getitimer(ITIMER_REAL, &val);
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - val.it_value.tv_usec);
}

/*
 *  �����޳�����׵�Υ����å�
 */
bool_t
target_timer_probe_int(void)
{
	return(false);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
	i_begin_int(INTNO_TIMER);
	i_lock_cpu();
	itimer_start();
	i_unlock_cpu();
	signal_time();					/* ������ƥ��å��ζ��� */
	i_end_int(INTNO_TIMER);
}

#endif /* 0 */
#else /* TOPPERS_SUPPORT_OVRHDR */

/*
 *		�����Х��ϥ�ɥ鵡ǽ�򥵥ݡ��Ȥ�����
 *
 *  ������ƥ��å�����Τ���Υ����ޡʥƥ��å������ޡˤȥ����Х��ϥ�
 *  �ɥ鵡ǽ�Τ���Υ����ޡʥ����Х�󥿥��ޡˤ�1�ĤΥ��󥿡��Х륿��
 *  �ޤ�¿�Ų����Ƽ¸����Ƥ��롥������ˡ�ϡ��ƥ��å��μ���������뤿��
 *  �˿侩�Ǥ��ʤ������ޥ����������٤Υ����ޤ�1�Ĥ����ʤ������ߥ�졼����
 *  ��Ķ��ǥƥ��å������Τ�����礭������ǤϤʤ����ᡤ������ˡ�����
 *  ���Ƥ��롥
 */
#include "task.h"
#include "overrun.h"

static CLOCK	ticktimer_cyc;		/* �ƥ��å������ޤμ��� */

static bool_t	itimer_ticktimer;	/* ���󥿡��Х륿���ޤ�
											�ƥ��å������ޤ����ꤵ��Ƥ��� */
static CLOCK	ticktimer_left;		/* �ƥ��å������ޤλĤ���� */
static bool_t	ovrtimer_active;	/* �����Х�󥿥��ޤ�ͭ�� */
static OVRTIM	ovrtimer_left;		/* �����Х�󥿥��ޤλĤ���� */

#define CLOCK_TO_OVRTIM(clock)		((OVRTIM) clock)
#define OVRTIM_TO_CLOCK(ovrtim)		((CLOCK) ovrtim)

static const struct itimerval		itimerval_stop = {{ 0, 0 }, { 0, 0 }};

/*
 *  �����ޤ�ư���
 */
Inline void
itimer_start(void)
{
	struct itimerval	val;

	/*
	 *  �����ޤ����ꤷ�������ޤ�ư��򳫻Ϥ��롥
	 */
	if (!ovrtimer_active || CLOCK_TO_OVRTIM(ticktimer_left) <= ovrtimer_left) {
		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = ticktimer_left;
		itimer_ticktimer = true;
	}
	else {
		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = OVRTIM_TO_CLOCK(ovrtimer_left);
		itimer_ticktimer = false;
	}
	val.it_interval.tv_sec = 0;
	val.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &val, NULL);
}

/*
 *  �����ޤ�ư�����
 */
Inline void
itimer_stop(void)
{
	struct itimerval	val;
	CLOCK				left;

	/*
	 *  �����ޤ�ư�����ߤ������λ����λĤ���֤�left�˼��Ф����Ĥ�
	 *  ���֤�0�ˤʤäƤ����1���ɤߴ����롥���λ��ˡ����ץꥢ�������
	 *  ��ȯ���������ǽ�������롥
	 */
	setitimer(ITIMER_REAL, &itimerval_stop, &val);
	left = val.it_value.tv_usec;
	if (left == 0) {
		left = 1;
	}

	/*
	 *  �����ޤλĤ���֤��顤�ƥ��å������ޤȥ����Х�󥿥��ޤλĤ��
	 *  �֤����ꤷľ����
	 */
	if (itimer_ticktimer) {
		if (ovrtimer_active) {
			ovrtimer_left -= CLOCK_TO_OVRTIM(ticktimer_left - left);
		}
		ticktimer_left = left;
	}
	else {
		ticktimer_left -= (OVRTIM_TO_CLOCK(ovrtimer_left) - left);
		ovrtimer_left = CLOCK_TO_OVRTIM(left);
	}
}

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	ticktimer_cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	assert(ticktimer_cyc <= MAX_CLOCK);

	ticktimer_left = ticktimer_cyc;
	ovrtimer_active = false;
	itimer_start();
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	/*
	 *  �����ޤ�ư�����ߤ��롥
	 */
	setitimer(ITIMER_REAL, &itimerval_stop, NULL);
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
CLOCK
target_timer_get_current(void)
{
	struct itimerval	val;

	if (itimer_ticktimer) {
		getitimer(ITIMER_REAL, &val);
		if (val.it_value.tv_usec == 0) {
			return(0);
		}
		else {
			return(TO_CLOCK(TIC_NUME, TIC_DENO) - val.it_value.tv_usec);
		}
	}
	else {
		getitimer(ITIMER_REAL, &val);
		return(ticktimer_left - (OVRTIM_TO_CLOCK(ovrtimer_left)
												- val.it_value.tv_usec));
	}
}

/*
 *  �����޳�����׵�Υ����å�
 */
bool_t
target_timer_probe_int(void)
{
	struct itimerval	val;

	if (itimer_ticktimer) {
		getitimer(ITIMER_REAL, &val);
		return(val.it_value.tv_usec == 0);
	}
	else {
		return(false);
	}
}

/*
 *  �����Х�󥿥��ޤν��������
 *
 *  ɬ�פʽ����򤹤٤�target_timer_initialize�ǹԤäƤ���Τǡ��������
 *  �ϲ��⤷�ʤ���
 */
void
target_ovrtimer_initialize(intptr_t exinf)
{
}

/*
 *  �����Х�󥿥��ޤ���߽���
 *
 *  ɬ�פʽ����򤹤٤�target_timer_terminate�ǹԤäƤ���Τǡ��������
 *  �ϲ��⤷�ʤ���
 */
void
target_ovrtimer_terminate(intptr_t exinf)
{
}

/*
 *  �����Х�󥿥��ޤ�ư���
 */
void
target_ovrtimer_start(OVRTIM ovrtim)
{
	assert(!ovrtimer_active);
	itimer_stop();
	ovrtimer_active = true;
	ovrtimer_left = ovrtim;
	itimer_start();
}

/*
 *  �����Х�󥿥��ޤ����
 */
OVRTIM
target_ovrtimer_stop(void)
{
	struct itimerval	val;

	assert(ovrtimer_active);
	if (itimer_ticktimer) {
		getitimer(ITIMER_REAL, &val);
		ovrtimer_left -= CLOCK_TO_OVRTIM(ticktimer_left
												- val.it_value.tv_usec);
		if (ovrtimer_left == 0) {
			ovrtimer_left = 1;
		}
		ovrtimer_active = false;
	}
	else {
		itimer_stop();
		ovrtimer_active = false;
		itimer_start();
	}
	return(ovrtimer_left);
}

/*
 *  �����Х�󥿥��ޤθ����ͤ��ɽФ�
 */
OVRTIM
target_ovrtimer_get_current(void)
{
	struct itimerval	val;
	OVRTIM				ovrtimer_current;

	assert(ovrtimer_active);
	if (itimer_ticktimer) {
		getitimer(ITIMER_REAL, &val);
		ovrtimer_current = ovrtimer_left
					- CLOCK_TO_OVRTIM(ticktimer_left - val.it_value.tv_usec);
	}
	else {
		getitimer(ITIMER_REAL, &val);
		ovrtimer_current = CLOCK_TO_OVRTIM(val.it_value.tv_usec);
	}
	return(ovrtimer_current);
}

/*
 *  �����޳���ߥϥ�ɥ�
 *
 *  �����޳���ߥϥ�ɥ�����������ǡ�ovrtimer_stop���ƤӽФ���롥����
 *  �Х�󥿥��ޤ�ư��Ƥ������ˤϡ���������target_ovrtimer_stop��
 *  �ƤӽФ���롥���󥿡��Х륿���ޤ˥����Х�󥿥��ޤ����ꤵ��Ƥ���
 *  ���ˤϡ���������itimer_stop��itimer_start���ƤӽФ���ơ����󥿡�
 *  �Х륿���ޤ˥ƥ��å������ޤ����ꤵ�졤���󥿡��Х륿���ޤ�ư���
 *  ����롥�դˡ����󥿡��Х륿���ޤ˥ƥ��å������ޤ����ꤵ��Ƥ�����
 *  ��ˤϡ����󥿡��Х륿���ޤ���ߤ����ޤޤȤʤäƤ��롥
 */
void
target_timer_handler(void)
{
	struct itimerval			val;

	i_begin_int(INTNO_TIMER);
	i_lock_cpu();
	getitimer(ITIMER_REAL, &val);
	if (val.it_value.tv_usec == 0) {
		/*
		 *  ���󥿡��Х륿���ޤ���ߤ��Ƥ���Τϡ����󥿡��Х륿���ޤ�
		 *  �ƥ��å������ޤ����ꤵ��Ƥ������Ǥ��롥
		 */
		ticktimer_left = ticktimer_cyc;

		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = ticktimer_left;
		val.it_interval.tv_sec = 0;
		val.it_interval.tv_usec = 0;
		setitimer(ITIMER_REAL, &val, NULL);

		i_unlock_cpu();
		signal_time();				/* ������ƥ��å��ζ��� */
	}
	else {
		/*
		 *  ���󥿡��Х륿���ޤ�ư��Ƥ���Τϡ����󥿡��Х륿���ޤ�
		 *  �����Х�󥿥��ޤ����ꤵ��Ƥ������Ǥ��롥
		 */
		if (p_runtsk->leftotm == 1) {
			/*
			 *  ���ץꥢ������ߤǤʤ����ˡ������Х�󥿥��ޤ�ư��
			 *  �롥
			 */
			i_unlock_cpu();
			call_ovrhdr();			/* �����Х��ϥ�ɥ�ε�ư */
		}
		else {
			i_unlock_cpu();
		}
	}
	i_end_int(INTNO_TIMER);
}

#endif /* TOPPERS_SUPPORT_OVRHDR */
