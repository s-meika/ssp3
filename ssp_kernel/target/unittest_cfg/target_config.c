/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  @(#) $Id: target_config.c 1967 2010-11-20 07:33:44Z ertl-hiro $
 */

/*
 *		�������åȰ�¸�⥸�塼���Mac OS X�ѡ�
 */

#include "kernel_impl.h"
#include "task.h"

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 */
volatile bool_t		lock_flag;		/* CPU��å��ե饰��ɽ���ѿ� */

void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
}


/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	/*
	 *  �ץ����ν�λ����
	 */
	exit(0);
}

/*
 *  �����ͥ�ν�λ�����θƽФ�
 */
void
call_exit_kernel(void)
{
	while (true);
}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	/*
	 *  CPU��å��ե饰�¸��Τ�����ѿ��ν����
	 */
	lock_flag = true;
}

void start_dispatch()
{
}

/*
 *  �����ͥ���٥ޥ����¸��Τ�����ѿ�
 */
volatile PRI		ipm_value;		/* �����ͥ���٥ޥ�����ɽ���ѿ� */

#if 0
/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_DSP_ENTER
#define LOG_DSP_ENTER(p_tcb)
#endif /* LOG_DSP_ENTER */

#ifndef LOG_DSP_LEAVE
#define LOG_DSP_LEAVE(p_tcb)
#endif /* LOG_DSP_LEAVE */

/*
 *  TMIN_INTPRI���ϰϤΥ����å�
 */
#if (TMIN_INTPRI > -1) || (-6 > TMIN_INTPRI)
#error TMIN_INTPRI out of range.
#endif /* (TMIN_INTPRI > -1) || (-6 > TMIN_INTPRI) */

/*
 *  ����ߥ�å���CPU��å��ؤΰܹԤǥޥ������륷���ʥ���ݻ������ѿ�
 */
sigset_t	sigmask_intlock;	/* ����ߥ�å��ǥޥ������륷���ʥ� */
sigset_t	sigmask_cpulock;	/* CPU��å��ǥޥ������륷���ʥ� */

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 */
volatile bool_t		lock_flag;		/* CPU��å��ե饰��ɽ���ѿ� */
volatile sigset_t	saved_sigmask;	/* �����ʥ�ޥ�������¸�����ѿ� */


/*
 *  �ǥ����ѥå������Τγ�����Ԥ���Ǥ��뤳�Ȥ򼨤��ѿ�
 */
static bool_t	dispatcher_idle;	/* ������Ԥ���Ǥ��� */

/*
 *  �ǥ����ѥå�������
 *
 *  LOG_DSP_ENTER��LOG_DSP_LEAVE��dispatcher�����줺�������ƤӽФ�
 *  �ؿ���¦������Ƥ�����ͳ�ϼ����̤ꡥLOG_DSP_ENTER�ϡ��ǥ����ѥå���
 *  ư��ϻ���main����ƤФ줿���ˤˤϡ��ƤӽФ��ƤϤʤ�ʤ����ᡤ
 *  dispatcher������뤳�Ȥ��Ǥ��ʤ���LOG_DSP_LEAVE�ϡ��ڴ�����Υ�����
 *  �Υ����å��ǸƤӽФ��ʤ���Фʤ�ʤ����ᡤ_longjmp��¹Ԥ�����˸�
 *  �ӽФ�ɬ�פ����ꡤdispatcher��ƤӽФ��ؿ���¦������ʤ���Фʤ��
 *  ����
 */
static void
dispatcher(void)
{
	sigset_t	sigmask;

	while ((p_runtsk = p_schedtsk) == NULL) {
		/*
		 *  CPU��å����֤�����������򤹤롥sigmask�ˤϡ�CPU��å���
		 *  �֤˰ܹԤ������Υ����ʥ�ޥ�������Ф���
		 */
		lock_flag = false;
		sigassignset(&sigmask, &saved_sigmask);
		do {
			/*
			 *  ������Ԥ��δ֤�ȯ����������ߥϥ�ɥ�Ǥ�SIGUSR2��
			 *  raise���ʤ��褦�ˡ�dispatcher_idle��true�ˤ��롥
			 */
			dispatcher_idle = true;
			sigsuspend(&sigmask);			/* ������Ԥ� */
			dispatcher_idle = false;
		} while (!reqflg);
		reqflg = false;

		/*
		 *  CPU��å����֤��᤹��������Ԥ��δ֤˼¹Ԥ�������ߥϥ�ɥ�
		 *  �ˤ�ꡤsaved_sigmask�Ͻ񤭴�����ǽ�������뤿�ᡤ�����ͤ�
		 *  �᤹ɬ�פ����롥
		 */
		sigassignset(&saved_sigmask, &sigmask);
		lock_flag = true;
	}
	_longjmp(p_runtsk->tskctxb.env, 1);
}

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå�
 */
void
dispatch(void)
{
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_stop();					/* �����Х�󥿥��ޤ���� */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	if (_setjmp(p_runtsk->tskctxb.env) == 0) {
		LOG_DSP_ENTER(p_runtsk);
		dispatcher();
		assert(0);
	}
	LOG_DSP_LEAVE(p_runtsk);
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* �����Х�󥿥��ޤ�ư��� */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	calltex();
}

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå��ʥ����ʥ�ϥ�ɥ��ѡ�
 */
static void
dispatch_handler(int sig, struct __siginfo *p_info, void *p_ctx)
{
#ifdef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  �����Х��ϥ�ɥ鵡ǽ�򥵥ݡ��Ȥ�����ˤϡ�dispatch_handler
	 *  ��ɬ����ư����롥�ǥ����ѥå���ɬ�פʤ����ˤϡ������Х���
	 *  ��ɥ��ư��ϤΤߤ�Ԥ���
	 */
	if (!(!dispatcher_idle && reqflg)) {
		ovrtimer_start();				/* �����Х�󥿥��ޤ�ư��� */
		return;
	}
	reqflg = false;
#endif /* TOPPERS_SUPPORT_OVRHDR */

	/*
	 *  �����ʥ�ϥ�ɥ�μ¹Գ������Υ����ʥ�ޥ�����saved_sigmask����
	 *  ������CPU��å����֤˰ܹԤ��롥
	 */
	sigassignset(&saved_sigmask, &(((ucontext_t *) p_ctx)->uc_sigmask));
	lock_flag = true;

	if (dspflg && p_runtsk != p_schedtsk) {
		if (_setjmp(p_runtsk->tskctxb.env) == 0) {
			LOG_DSP_ENTER(p_runtsk);
			dispatcher();
			assert(0);
		}
		LOG_DSP_LEAVE(p_runtsk);
	}
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* �����Х�󥿥��ޤ�ư��� */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	calltex();

	/*
	 *  �����ʥ�ϥ�ɥ餫��Υ꥿�����Υ����ʥ�ޥ�����saved_sigmask
	 *  �ˤʤ�褦�����ꤷ��CPU��å����֤������롥
	 */
	lock_flag = false;
	sigassignset(&(((ucontext_t *) p_ctx)->uc_sigmask), &saved_sigmask);
}

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 */
void
exit_and_dispatch(void)
{
	LOG_DSP_ENTER(p_runtsk);
	dispatcher();
	assert(0);
}

/*
 *  ����ߥϥ�ɥ�и�����
 *
 *  ����ߥϥ�ɥ���Ǥϡ������ͥ�����γ���ߤ�ػߤ��Ƥ��뤿�ᡤ�и�
 *  �����ǳ���ߤ�ػߤ���ɬ�פϤʤ���
 */
void
ret_int(void)
{
#ifndef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  �ǥ����ѥå���ε�ư���׵᤹�롥
	 *
	 *  reqflg������å�����ľ��˳���ߤ����äƤ⡤���ä�¦�γ���ߤ�
	 *  �������ǥ����ѥå���ε�ư���׵᤹�뤿�ᡤreqflg������å�����
	 *  ���˳���ߤ�ػߤ���ɬ�פ��ʤ���
	 */
	if (!dispatcher_idle && reqflg) {
		reqflg = false;
		raise(SIGUSR2);
	}
#else /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 *  �����Х��ϥ�ɥ鵡ǽ�򥵥ݡ��Ȥ�����ˤϡ������Х�󥿥���
	 *  ��ư��Ϥ��뤿��ˡ�dispatch_handler��ɬ����ư���롥
	 */
	raise(SIGUSR2);
#endif /* TOPPERS_SUPPORT_OVRHDR */
}

/*
 *  CPU�㳰�ϥ�ɥ�и�����
 */
void
ret_exc(void)
{
#ifndef TOPPERS_SUPPORT_OVRHDR
	/*
	 *  �ǥ����ѥå���ε�ư���׵᤹�롥
	 *
	 *  reqflg������å�����ľ��˳���ߤ����äƤ⡤���ä�¦�γ���ߤ�
	 *  �������ǥ����ѥå���ε�ư���׵᤹�뤿�ᡤreqflg������å�����
	 *  ���˳���ߤ�ػߤ���ɬ�פ��ʤ���
	 */
	if (!dispatcher_idle && reqflg) {
		reqflg = false;
		raise(SIGUSR2);
	}
#else /* TOPPERS_SUPPORT_OVRHDR */
	/*
	 *  �����Х��ϥ�ɥ鵡ǽ�򥵥ݡ��Ȥ�����ˤϡ������Х�󥿥���
	 *  ��ư��Ϥ��뤿��ˡ�dispatch_handler��ɬ����ư���롥
	 */
	raise(SIGUSR2);
#endif /* TOPPERS_SUPPORT_OVRHDR */
}

/*
 *  �����ͥ�ν�λ�����θƽФ�
 */
void
call_exit_kernel(void)
{
	sigset_t			sigmask;
	struct sigaction	sigact;

	/*
	 *  SIGUSR2�Υ����ʥ�ϥ�ɥ��exit_kernel����Ͽ
	 */
	sigact.sa_handler = (void (*)(int)) exit_kernel;
	sigact.sa_flags = SA_ONSTACK;
	sigemptyset(&(sigact.sa_mask));
	sigaction(SIGUSR2, &sigact, NULL);

	/*
	 *  SIGUSR2�Υޥ�������
	 */
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR2);
	sigprocmask(SIG_UNBLOCK, &sigmask, NULL);

	/*
	 *  exit_kernel�θƽФ�
	 */
	raise(SIGUSR2);
	assert(0);
	while (true);
}

/*
 *  ���������ϻ�����
 */
void
start_r(void)
{
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_start();					/* �����Х�󥿥��ޤ�ư��� */
#endif /* TOPPERS_SUPPORT_OVRHDR */
	t_unlock_cpu();
	(*(p_runtsk->p_tinib->task))(p_runtsk->p_tinib->exinf);
	(void) ext_tsk();
	assert(0);
}


/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char c)
{
	write(STDERR_FILENO, &c, 1);
}

/*
 *  ����ߴ�����ǽ�ν����
 */
void
initialize_interrupt(void)
{
	uint_t			i;
	const INHINIB	*p_inhinib;

	for (p_inhinib = inhinib_table, i = 0; i < tnum_inhno; p_inhinib++, i++) {
		x_define_inh(p_inhinib->inhno, p_inhinib->int_entry,
												p_inhinib->intpri);
	}
}

/*
 *  �ᥤ��ؿ�
 */
int
main()
{
	sigset_t			sigmask;
	stack_t				ss;
	struct sigaction	sigact;

	/*
	 *  SIGUSR2�ʳ��Τ��٤ƤΥ����ʥ��ޥ���
	 */
	sigfillset(&sigmask);
	sigdelset(&sigmask, SIGUSR2);
	sigprocmask(SIG_BLOCK, &sigmask, NULL);

	/*
	 *  �����ʥ륹���å����󥿥�������ƥ������ѤΥ����å��ˤ�����
	 */
	ss.ss_sp = (char *)(istk);
	ss.ss_size = (int)(istksz);
	ss.ss_flags = 0;
	sigaltstack(&ss, NULL);

	/*
	 *  SIGUSR2�Υ����ʥ�ϥ�ɥ��sta_ker����Ͽ
	 */
	sigact.sa_handler = (void (*)(int)) sta_ker;
	sigact.sa_flags = SA_ONSTACK;
	sigemptyset(&(sigact.sa_mask));
	sigaction(SIGUSR2, &sigact, NULL);

	/*
	 *  sta_ker�θƽФ�
	 */
	raise(SIGUSR2);

	/*
	 *  �ǥ����ѥå����ư���
	 *
	 *  target_initialize�ǡ�lock_flag��true�ˡ�ipm_value��TIPM_ENAALL
	 *  �˽�������Ƥ��뤿�ᡤset_sigmask��ƤӽФ��ƥ����ʥ�ޥ�����
	 *  saved_sigmask�����ꤹ�뤳�Ȥǡ�CPU��å����֡��ʥ�ǥ��Ρ˳�
	 *  ����ͥ���٥ޥ�����TIPM_ENAALL�ξ��֤ˤʤ롥
	 *
	 *  �ޤ���initialize_task��disdsp��false�˽�������Ƥ��뤿�ᡤ�ǥ�
	 *  ���ѥå����ľ��֤ˤʤäƤ��롥
	 */
	set_sigmask();
	dispatcher();
	assert(0);
	return(0);
}

/*
 *  �����ͥ�γ���դ�������ΰ�δ���
 *
 *  TLSF�ʥ����ץ󥽡����Υ�������饤�֥��ˤ��Ѥ��Ƽ¸���
 */
#ifdef TOPPERS_SUPPORT_DYNAMIC_CRE

#include "tlsf.h"

static bool_t	tlsf_initialized = false;

void
initialize_kmm(void)
{
	if (init_memory_pool(kmmsz, kmm) >= 0) {
		tlsf_initialized = true;
	}
}

void *
kernel_malloc(SIZE size)
{
	if (tlsf_initialized) {
		return(malloc_ex(size, kmm));
	}
	else {
		return(NULL);
	}
}

void
kernel_free(void *ptr)
{
	if (tlsf_initialized) {
		free_ex(ptr, kmm);
	}
}
#endif /* TOPPERS_SUPPORT_DYNAMIC_CRE */

#endif
