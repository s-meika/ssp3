/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: target_config.h 2013 2010-12-31 12:47:36Z ertl-hiro $
 */

/*
 *		�������åȰ�¸�⥸�塼���Mac OS X�ѡ�
 *
 *  �����ͥ�Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  ɸ��Υ��󥯥롼�ɥե�����
 */
#ifndef TOPPERS_MACRO_ONLY
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �������åȥ����ƥ��OS��¸�����
 */
#include "macosx.h"

/*
 *  �������å�����Υ��֥�������°��
 */
#define TARGET_INHATR	TA_NONKERNEL	/* �����ͥ�������γ���� */

/*
 *  ���顼�����å���ˡ�λ���
 */
#define CHECK_STKSZ_ALIGN	4	/* �����å��������Υ��饤��ñ�� */
#define CHECK_FUNC_ALIGN	4	/* �ؿ��Υ��饤��ñ�� */
#define CHECK_FUNC_NONNULL		/* �ؿ�����NULL�����å� */
#define CHECK_STACK_ALIGN	4	/* �����å��ΰ�Υ��饤��ñ�� */
#define CHECK_STACK_NONNULL		/* �����å��ΰ����NULL�����å� */
#define CHECK_MPF_ALIGN		4	/* ����Ĺ����ס����ΰ�Υ��饤��ñ�� */
#define CHECK_MPF_NONNULL		/* ����Ĺ����ס����ΰ����NULL�����å� */
#define CHECK_MB_ALIGN		4	/* �����ΰ�Υ��饤��ñ�� */

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  �ȥ졼�����ޥ���Υǥե�������
 */
#ifndef LOG_INH_ENTER
#define LOG_INH_ENTER(inhno)
#endif /* LOG_INH_ENTER */

#ifndef LOG_INH_LEAVE
#define LOG_INH_LEAVE(inhno)
#endif /* LOG_INH_LEAVE */

#ifndef LOG_EXC_ENTER
#define LOG_EXC_ENTER(excno)
#endif /* LOG_EXC_ENTER */

#ifndef LOG_EXC_LEAVE
#define LOG_EXC_LEAVE(excno)
#endif /* LOG_EXC_LEAVE */

/*
 *  �������ƥ�����ʥץ��å��˰�¸�����
 */
#define DEFAULT_ISTKSZ			128	/* �����ʥ륹���å��Υ����� */

#if defined(__ppc__)

#define JMPBUF_PC				21			/* jmp_buf��Ǥ�PC�ΰ��� */
#define JMPBUF_SP				0			/* jmp_buf��Ǥ�SP�ΰ��� */
#define TASK_STACK_MERGIN		4U

#elif defined(__i386__)

#define JMPBUF_PC				12			/* jmp_buf��Ǥ�PC�ΰ��� */
#define JMPBUF_SP				9			/* jmp_buf��Ǥ�SP�ΰ��� */
#define TASK_STACK_MERGIN		4U 

#elif defined(__x86_64__)

#error architecture not supported
#define JMPBUF_PC				7			/* jmp_buf��Ǥ�PC�ΰ��� */
#define JMPBUF_SP				2			/* jmp_buf��Ǥ�SP�ΰ��� */
#define TASK_STACK_MERGIN		8U 

#else
#error architecture not supported
#endif


#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((istk) + (istksz)))

/* 
 *  ɸ��γ���ߴ�����ǽ�ν������Ԥ�ʤ���������
 */
//#define OMIT_INITIALIZE_INTERRUPT

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	jmp_buf		env;			/* ����ƥ����Ⱦ��� */
} TSKCTXB;

/*
 *  ����ߥϥ�ɥ������֥�å�
 *
 *  ɸ��γ���ߥϥ�ɥ������֥�å��ˡ������ͥ���٤��ɲä�����Ρ�
 */
typedef struct interrupt_handler_initialization_block {
	INHNO		inhno;			/* ����ߥϥ�ɥ��ֹ� */
	ATR			inhatr;			/* ����ߥϥ�ɥ�°�� */
	FP			int_entry;		/* ����ߥϥ�ɥ�ν��������������� */
	PRI			intpri;			/* �����ͥ���� */
} INHINIB;

/*
 *  ����ߥϥ�ɥ��ֹ�ο���kernel_cfg.c��
 */
extern const uint_t	tnum_inhno;

/*
 *  ����ߥϥ�ɥ������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const INHINIB	inhinib_table[];

/*
 *  �����ʥ륻�å����ޥ���
 */
#define sigequalset(set1, set2)		(*(set1) == *(set2))
#define sigassignset(set1, set2)	(*(set1) = *(set2))
#define sigjoinset(set1, set2)		(*(set1) |= *(set2))

/*
 *  �����ͥ���٥ޥ����ˤ�륷���ʥ�ޥ�����kernel_cfg.c��
 *
 *  �����ͥ���٥ޥ����ˤ�äƥޥ�������Ƥ������ߤȡ������°������
 *  �ꤵ��Ƥ��ʤ�����ߤ��б����륷���ʥ��ޥ������뤿��Υ����ʥ��
 *  �������ݻ�������������Υ���ǥå����ϡ������ͥ���٥ޥ��������
 *  ��ȿž������Ρ�
 *
 *  sigmask_table[0]�������°�������ꤵ��Ƥ��ʤ�����ߤ��б����륷��
 *                    �ʥ�Τߤ�ޥ������륷���ʥ�ޥ���
 *  sigmask_table[-TMIN_INTPRI]�������ͥ�����γ���ߤ��٤Ƥȡ������°
 *                    �������ꤵ��Ƥ��ʤ�����ߤ��б����륷���ʥ���
 *                    �������륷���ʥ�ޥ���
 *  sigmask_table[6]��NMI��SIGUSR2��������٤Ƥγ���ߤȡ������°������
 *                    �ꤵ��Ƥ��ʤ�����ߤ��б����륷���ʥ��ޥ�������
 *                    �����ʥ�ޥ���
 *  sigmask_table[7]��sigmask_table[6]��Ʊ����
 */
extern const sigset_t sigmask_table[8];

/*
 *  ����ƥ����Ȥλ���
 */
Inline bool_t
sense_context(void)
{
	stack_t	ss;

	sigaltstack(NULL, &ss);
	return((ss.ss_flags & SA_ONSTACK) != 0);
}

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 */
extern volatile bool_t		lock_flag;		/* CPU��å��ե饰��ɽ���ѿ� */
//extern volatile sigset_t	saved_sigmask;	/* �����ʥ�ޥ�������¸�����ѿ� */

/*
 *  �����ͥ���٥ޥ����¸��Τ�����ѿ�
 */
extern volatile PRI			ipm_value;		/* �����ͥ���٥ޥ�����ɽ���ѿ� */

/*
 *  ������׵�ػߥե饰�¸��Τ�����ѿ�
 */
extern volatile sigset_t	sigmask_disint;	/* ���̤˥ޥ������Ƥ��륷���ʥ� */

/*
 *  �����ɥ�롼��
 */
Inline void
idle_loop(void)
{
}

/*
 *  �����ʥ�ޥ���������
 *
 *  ���ߤξ��֡ʥ���ƥ����ȡ�CPU��å��ե饰�������ͥ���٥ޥ��������
 *  �߶ػߥե饰�ˤ򻲾Ȥ��ơ����ߤΥ����ʥ�ޥ�����saved_sigmask��Ŭ��
 *  ���ͤ����ꤹ�롥
 */
Inline void
set_sigmask(void)
{
}

/*
 *  CPU��å����֤ؤΰܹ�
 */
Inline void
x_lock_cpu(void)
{
	lock_flag = true;
}

#define t_lock_cpu()	x_lock_cpu()
#define i_lock_cpu()	x_lock_cpu()

/*
 *  CPU��å����֤β��
 */
Inline void
x_unlock_cpu(void)
{
//	assert(lock_flag);
	lock_flag = false;
}

#define t_unlock_cpu()	x_unlock_cpu()
#define i_unlock_cpu()	x_unlock_cpu()

/*
 *  CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
	return(lock_flag);
}

#define t_sense_lock()	x_sense_lock()
#define i_sense_lock()	x_sense_lock()

/*
 *  �����ͥ���٥ޥ���������
 */
Inline void
x_set_ipm(PRI intpri)
{
	ipm_value = intpri;
	set_sigmask();
}

#define t_set_ipm(intpri)	x_set_ipm(intpri)
#define i_set_ipm(intpri)	x_set_ipm(intpri)

/*
 *  �����ͥ���٥ޥ����λ���
 */
Inline PRI
x_get_ipm(void)
{
	return(ipm_value);
}

#define t_get_ipm()	x_get_ipm()
#define i_get_ipm()	x_get_ipm()

/*
 *  ������ֹ���ϰϤ�Ƚ��
 */
#define	VALID_INTNO(intno)	(1 <= (intno) && (intno) <= 30 \
								&& (intno) != SIGKILL && (intno) != SIGSTOP)
#define	VALID_INTNO_CREISR(intno)	VALID_INTNO(intno)
#define	VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)

/*
 *  ������׵�ػߥե饰�Υ��å�
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥻥åȤ��褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	return(true);
}

#define t_disable_int(intno)	x_disable_int(intno)
#define i_disable_int(intno)	x_disable_int(intno)

/*
 *  ������׵�ػߥե饰�Υ��ꥢ
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	return(true);
}

#define t_enable_int(intno)		x_enable_int(intno)
#define i_enable_int(intno)		x_enable_int(intno)

/*
 *  ������׵�Υ��ꥢ
 */
Inline void
x_clear_int(INTNO intno)
{
}

#define t_clear_int(intno)		x_clear_int(intno)
#define i_clear_int(intno)		x_clear_int(intno)

/*
 *  ������׵�Υ����å�
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	sigset_t	sigmask;

	sigpending(&sigmask);
	return(sigismember(&sigmask, intno));
}

#define t_probe_int(intno)		x_probe_int(intno)
#define i_probe_int(intno)		x_probe_int(intno)

#if 0  // �����֤Ȥ����Ѱդ��ƥ����å��롼������ɲä��뤿�ᤳ���ǤϾ�ά����
/*
 *  ����ߥϥ�ɥ��������ɬ�פ�IRC���
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
i_end_int(INTNO intno)
{
}
#endif

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå�
 *
 *  dispatch�ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ������������
 *  ��ƤӽФ��٤���Τǡ�����������ƥ����ȡ�CPU��å����֡��ǥ����ѥ�
 *  �����ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ���
 *  ����Фʤ�ʤ���
 */
extern void	dispatch(void);

/*
 *  �ǥ����ѥå����ư���
 *
 *  start_dispatch��return�˥ޥ���������뤳�Ȥǡ������ͥ�ν������λ
 *  ���sta_ker����main�˥꥿���󤵤��������ʥ륹���å����鸵�Υ����å�
 *  ���᤹��
 */
extern void start_dispatch();

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 *
 *  exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�����������ƥ�
 *  ���ȡ�CPU��å����֡��ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ��
 *  �٥ޥ�����������֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	exit_and_dispatch(void);

/*
 *  ����ߥϥ�ɥ�и�����
 */
extern void	ret_int(void);

/*
 *  CPU�㳰�ϥ�ɥ�и�����
 */
extern void	ret_exc(void);

/*
 *  �����ͥ�ν�λ�����θƽФ�
 *
 *  call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *  ����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *  ����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  ����������ƥ����Ȥν����
 *
 *  ���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥���λ���
 *  �ǥ����å��ΰ��ȤäƤϤʤ�ʤ���
 *
 *  activate_context�򡤥���饤��ؿ��ǤϤʤ��ޥ�������Ȥ��Ƥ���Τϡ�
 *  ���λ����Ǥ�TCB���������Ƥ��ʤ�����Ǥ��롥
 */
extern void	start_r(void);


/*
 *  ����ߥϥ�ɥ��ֹ��CPU�㳰�ϥ�ɥ��ֹ���ϰϤ�Ƚ��
 */
#define VALID_INHNO_DEFINH(inhno)		VALID_INTNO((INTNO)(inhno))
#define VALID_EXCNO_DEFEXC(excno)		VALID_INTNO((INTNO)(excno))

/*
 *  ����ߥϥ�ɥ������
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  CPU�㳰�ϥ�ɥ������
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
}

/*
 *  ����ߥϥ�ɥ�����������������ޥ���
 */
#define INT_ENTRY(inhno, inthdr)	_kernel_##inthdr##_##inhno

#define INTHDR_ENTRY(inhno, inhno_num, inthdr)					\
void _kernel_##inthdr##_##inhno(void)							\
{																\
	inthdr();			\
}

/*
 *  CPU�㳰�ϥ�ɥ�����������������ޥ���
 */
#define EXC_ENTRY(excno, exchdr)	_kernel_##exchdr##_##excno

#define EXCHDR_ENTRY(excno, excno_num, exchdr)							\
void _kernel_##exchdr##_##excno(void)			\
{																		\
		exchdr(excno);	\
}


/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void	target_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���
 */
extern void	target_exit(void) NoReturn;

/*
 *  ������׵�饤���°��������
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri);


#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ͥ�γ���դ�������ΰ�δ���
 *
 *  target_config.c�ˡ�TLSF�ʥ����ץ󥽡����Υ�������饤�֥��ˤ���
 *  ������������롼�����ޤ�Ƥ��롥
 */
#define OMIT_KMM_ALLOCONLY

#endif /* TOPPERS_TARGET_CONFIG_H */
