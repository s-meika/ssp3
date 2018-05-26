/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#ifndef TOPPERS_EMPTY_LABEL
#define TOPPERS_EMPTY_LABEL(x,y) x y[0]
#endif

/*
 *  Include Directives
 */

#include "sample1.h"
#include "target_timer.h"
#include "chip_timer.h"
#include "target_syssvc.h"
#include "target_timer.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/banner.h"
#include "syssvc/syslog.h"
#include "syssvc/logtask.h"

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

const ATR	_kernel_tinib_tskatr[TNUM_TSKID] = {(TA_ACT),(TA_ACT),(TA_NULL),(TA_NULL),(TA_NULL),(TA_NULL)};
const uint_t	_kernel_init_rdypmap = 3U;
const intptr_t	_kernel_tinib_exinf[TNUM_TSKID] = {(intptr_t)(0),(intptr_t)(LOGTASK_PORTID),(intptr_t)(0),(intptr_t)(1),(intptr_t)(2),(intptr_t)(3)};
const TASK	_kernel_tinib_task[TNUM_TSKID] = {(init_task),(logtask_main),(main_task),(task),(task),(task)};
const uint_t	_kernel_tinib_epriority[TNUM_TSKID] = {INT_PRIORITY(1),INT_PRIORITY(2),INT_PRIORITY(3),INT_PRIORITY(4),INT_PRIORITY(5),INT_PRIORITY(5)};
/*
 * Configuration result of task priority:
 * 	INIT_TASK:	IPRI = 1, EXEPRI = 1
 * 	LOGTASK:	IPRI = 2, EXEPRI = 2
 * 	MAIN_TASK:	IPRI = 3, EXEPRI = 3
 * 	TASK1:	IPRI = 4, EXEPRI = 4
 * 	TASK2:	IPRI = 5, EXEPRI = 5
 * 	TASK3:	IPRI = 6, EXEPRI = 5
 */

/* 
 * Task Stack Size Estimation:
 * 	Calculation Start (Task ID = TASK3, StackSize = STACK_SIZE)
 * 	Task list with higher priority than TASK3 = (TASK1),(MAIN_TASK),(LOGTASK),(INIT_TASK)
 * 		Calculation Start (Task ID = TASK1, StackSize = STACK_SIZE)
 * 		Task list with higher priority than TASK1 = (MAIN_TASK),(LOGTASK),(INIT_TASK)
 * 			Calculation Start (Task ID = MAIN_TASK, StackSize = STACK_SIZE)
 * 			Task list with higher priority than MAIN_TASK = (LOGTASK),(INIT_TASK)
 * 				Calculation Start (Task ID = LOGTASK, StackSize = LOGTASK_STACK_SIZE)
 * 				Task list with higher priority than LOGTASK = (INIT_TASK)
 * 					Calculation Start (Task ID = INIT_TASK, StackSize = STACK_SIZE)
 * 					Task list with higher priority than INIT_TASK = 
 * 					higher_pri_maxstksz[INIT_TASK] = 0
 * 					DONE(stksz[INIT_TASK] = 256)
 * 				higher_pri_maxstksz[LOGTASK] = 256
 * 				DONE(stksz[LOGTASK] = 512)
 * 				Calculation Start (Task ID = INIT_TASK, StackSize = STACK_SIZE)
 * 				SKIP(max_stksz[INIT_TASK] = 256)
 * 			higher_pri_maxstksz[MAIN_TASK] = 512
 * 			DONE(stksz[MAIN_TASK] = 768)
 * 			Calculation Start (Task ID = LOGTASK, StackSize = LOGTASK_STACK_SIZE)
 * 			SKIP(max_stksz[LOGTASK] = 512)
 * 			Calculation Start (Task ID = INIT_TASK, StackSize = STACK_SIZE)
 * 			SKIP(max_stksz[INIT_TASK] = 256)
 * 		higher_pri_maxstksz[TASK1] = 768
 * 		DONE(stksz[TASK1] = 1024)
 * 		Calculation Start (Task ID = MAIN_TASK, StackSize = STACK_SIZE)
 * 		SKIP(max_stksz[MAIN_TASK] = 768)
 * 		Calculation Start (Task ID = LOGTASK, StackSize = LOGTASK_STACK_SIZE)
 * 		SKIP(max_stksz[LOGTASK] = 512)
 * 		Calculation Start (Task ID = INIT_TASK, StackSize = STACK_SIZE)
 * 		SKIP(max_stksz[INIT_TASK] = 256)
 * 	higher_pri_maxstksz[TASK3] = 1024
 * 	DONE(stksz[TASK3] = 1280)
 * 	Calculation Start (Task ID = TASK2, StackSize = STACK_SIZE)
 * 	Task list with higher priority than TASK2 = (TASK1),(MAIN_TASK),(LOGTASK),(INIT_TASK)
 * 		Calculation Start (Task ID = TASK1, StackSize = STACK_SIZE)
 * 		SKIP(max_stksz[TASK1] = 1024)
 * 		Calculation Start (Task ID = MAIN_TASK, StackSize = STACK_SIZE)
 * 		SKIP(max_stksz[MAIN_TASK] = 768)
 * 		Calculation Start (Task ID = LOGTASK, StackSize = LOGTASK_STACK_SIZE)
 * 		SKIP(max_stksz[LOGTASK] = 512)
 * 		Calculation Start (Task ID = INIT_TASK, StackSize = STACK_SIZE)
 * 		SKIP(max_stksz[INIT_TASK] = 256)
 * 	higher_pri_maxstksz[TASK2] = 1024
 * 	DONE(stksz[TASK2] = 1280)
 * List of Estimated Total Stack Sizes of Tasks = [1280, 1280]
 * Estimated Maximum Total Stack Size of Tasks = 1280
 */
#define TOPPERS_TSTKSZ          (1280)


/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const ATR, _kernel_flginib_atr);
TOPPERS_EMPTY_LABEL(const FLGPTN, _kernel_flginib_iflgptn);
TOPPERS_EMPTY_LABEL(FLGPTN, _kernel_flgcb_flgptn);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

TOPPERS_EMPTY_LABEL(const ATR, _kernel_dtqinib_atr);
TOPPERS_EMPTY_LABEL(intptr_t * const, _kernel_dtqinib_data);
TOPPERS_EMPTY_LABEL(const uint8_t, _kernel_dtqinib_size);
TOPPERS_EMPTY_LABEL(uint8_t, _kernel_dtqcb_count);
TOPPERS_EMPTY_LABEL(uint8_t, _kernel_dtqcb_head);
TOPPERS_EMPTY_LABEL(uint8_t, _kernel_dtqcb_tail);

/*
 *  Cyclic Notification Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

static void
_kernel_nfyhdr_LOCCYC(void)
{
	tmevt_nfy_call_handler((TMEHDR)cychdr_act_logtsk, LOGTASK);
}

const uint16_t	_kernel_cycinib_cycact = 1;
const NFYHDR	_kernel_cycinib_nfyhdr[TNUM_CYCID] = {(_kernel_nfyhdr_LOCCYC)};
const RELTIM	_kernel_cycinib_cyctim[TNUM_CYCID] = {(LOGTASK_INTERVAL)};
const RELTIM	_kernel_cycinib_cycphs[TNUM_CYCID] = {(LOGTASK_INTERVAL)};
EVTTIM	_kernel_cyccb_evttim[TNUM_CYCID];
const uint_t _kernel_cycevtid_offset = 0;

uint16_t	_kernel_cyccb_cycact;

/*
 *  Alarm Notification Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

TOPPERS_EMPTY_LABEL(const NFYHDR, _kernel_alminib_almhdr);
const uint_t _kernel_almevtid_offset = 1;

uint16_t	_kernel_almcb_almact;

/*
 *  Time Event Management Functions
 */


#define TNUM_TMEVT 1

const uint_t _kernel_tnum_tmevt_queue = TNUM_TMEVT;

QUEUE _kernel_tmevt_queue[TNUM_TMEVT+1];
EVTTIM _kernel_tmevt_time[TNUM_TMEVT];
CBACK _kernel_tmevt_callback[TNUM_TMEVT];
uintptr_t _kernel_tmevt_arg[TNUM_TMEVT];


/*
 *  Interrupt Management Functions
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

void
_kernel_inthdr_16(void)
{
	i_begin_int(16);
	LOG_ISR_ENTER(16);
	((ISR)(sio_isr_tx))((intptr_t)(SIO_PORTID));
	LOG_ISR_LEAVE(16);
	i_end_int(16);
}

void
_kernel_inthdr_17(void)
{
	i_begin_int(17);
	LOG_ISR_ENTER(17);
	((ISR)(sio_isr_rx))((intptr_t)(SIO_PORTID));
	LOG_ISR_LEAVE(17);
	i_end_int(17);
}

#define TNUM_INHNO	3
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_HRT, 32, chip_hrt_handler)
INTHDR_ENTRY(16, 16, _kernel_inthdr_16)
INTHDR_ENTRY(17, 17, _kernel_inthdr_17)

const INHNO	_kernel_inhinib_inhno[TNUM_INHNO] = {(INHNO_HRT),(16),(17)};
const ATR	_kernel_inhinib_inhatr[TNUM_INHNO] = {(TA_NULL),(TA_NULL),(TA_NULL)};
const FP	_kernel_inhinib_entry[TNUM_INHNO] = {(FP)(INT_ENTRY(INHNO_HRT, chip_hrt_handler)),(FP)(INT_ENTRY(16, _kernel_inthdr_16)),(FP)(INT_ENTRY(17, _kernel_inthdr_17))};

#define TNUM_INTNO	3
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTNO _kernel_intinib_intno[TNUM_INTNO] = {(INTNO_HRT),(INTNO_SIO_TX),(INTNO_SIO_RX)};
const ATR _kernel_intinib_intatr[TNUM_INTNO] = {(TA_ENAINT|INTATR_HRT),(INTATR_SIO),(INTATR_SIO)};
const PRI _kernel_intinib_intpri[TNUM_INTNO] = {(INTPRI_HRT),(INTPRI_SIO),(INTPRI_SIO)};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Stack Area for Non-task Context
 */

#define TOPPERS_ISTKSZ	(INTERRUPT_STACKSIZE)

/*
 *  Stack Area for System
 */

static STK_T _kernel_stack[COUNT_STK_T(ALL_STACKSIZE)];
#define TOPPERS_STK          (_kernel_stack)
#define TOPPERS_STKSZ        (ROUND_STK_T(ALL_STACKSIZE))

const size_t	_kernel_stksz = TOPPERS_STKSZ;
STK_T *const	_kernel_stk = TOPPERS_STK;

#ifdef TOPPERS_ISTKPT
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_STK, TOPPERS_STKSZ);
#endif /* TOPPERS_ISTKPT */

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_time_event();
	_kernel_initialize_task();
	_kernel_initialize_cyclic();
	_kernel_initialize_interrupt();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(chip_hrt_timer_initialize))((intptr_t)(0));
	((INIRTN)(sio_initialize))((intptr_t)(0));
	((INIRTN)(serial_initialize))((intptr_t)(0));
	((INIRTN)(print_banner))((intptr_t)(0));
	((INIRTN)(syslog_initialize))((intptr_t)(0));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(logtask_terminate))((intptr_t)(0));
	((TERRTN)(serial_terminate))((intptr_t)(0));
	((TERRTN)(chip_hrt_timer_terminate))((intptr_t)(0));
}

const uint32_t _kernel_bitpat_cfgint[2] = {
	UINT32_C(0x00030000),
	UINT32_C(0x00000001),
};

#ifndef TARGET_COPYRIGHT
#define TARGET_COPYRIGHT
#endif /* TARGET_COPYRIGHT */

#ifndef TARGET_NAME
#define TARGET_NAME
#endif /* TARGET_NAME */

const char banner[] = "\n" "TOPPERS/SSP Kernel " "3.0.0 " \
		" for " TARGET_NAME " (" __DATE__ " , " __TIME__ ")\n" \
		"Copyright (C) 2010,2017 by Meika Sugimoto\n" \
		"Copyright (C) 2010 by Naoki Saito\n"	\
		"            Nagoya Municipal Industrial Research Institute, JAPAN\n" \
		TARGET_COPYRIGHT "\n";
const int32_t banner_size = sizeof(banner) / sizeof(banner[0]);
