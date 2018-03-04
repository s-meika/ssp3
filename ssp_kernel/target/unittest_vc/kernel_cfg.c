/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#ifndef TOPPERS_EMPTY_LABEL
#define TOPPERS_EMPTY_LABEL(x,y) x y[0]
#endif

/*
 *  Include Directives (#include)
 */

#include "stubtask.h"

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

const uint_t _kernel_init_rdypmap = 0x0010;

const intptr_t	_kernel_tinib_exinf[TNUM_TSKID]     = {(intptr_t)(1),(intptr_t)(2),(intptr_t)(3),(intptr_t)(4)};
const TASK    	_kernel_tinib_task[TNUM_TSKID]      = {(task1),(task2),(task3),(task4)};
const uint_t  	_kernel_tinib_epriority[TNUM_TSKID] = {INT_PRIORITY(1),INT_PRIORITY(2),INT_PRIORITY(2),INT_PRIORITY(4)};

uint_t _kernel_intnest;

/* Task Stack Sizse Estimate: 

Call calc_stksz (argv = TASK4, StackSize[TASK4]=100)
	higher_pri_tsklist[TASK4] = TASK1,TASK2,TASK3
	Call calc_stksz (argv = TASK1, StackSize[TASK1]=100)
		higher_pri_tsklist[TASK1] = 
		higher_pri_stkszlist[TASK1] = 0
		DONE(stksz_list[TASK1] = 100)
	Call calc_stksz (argv = TASK2, StackSize[TASK2]=100)
		higher_pri_tsklist[TASK2] = TASK1
		Call calc_stksz (argv = TASK1, StackSize[TASK1]=100)
			SKIP(stksz_list[TASK1] = 100)
		higher_pri_stkszlist[TASK2] = 100
		DONE(stksz_list[TASK2] = 200)
	Call calc_stksz (argv = TASK3, StackSize[TASK3]=100)
		higher_pri_tsklist[TASK3] = TASK1
		Call calc_stksz (argv = TASK1, StackSize[TASK1]=100)
			SKIP(stksz_list[TASK1] = 100)
		higher_pri_stkszlist[TASK3] = 100
		DONE(stksz_list[TASK3] = 200)
	higher_pri_stkszlist[TASK4] = 100,200,200
	DONE(stksz_list[TASK4] = 200,300,300)
Estimated Task Stack Size List = 200,300,300
Maximum Task Stack Size = 300
*/ 


/*
 *  Interrupt Management Functions
 */


#define TNUM_INHNO	2
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

const INHNO _kernel_inhinib_inhno[TNUM_INHNO] = { 0 , 4 };
const ATR _kernel_inhinib_inhatr[TNUM_INHNO] = { TA_NULL , TA_ENAINT };
const FP _kernel_inhinib_entry[TNUM_INHNO] = { (FP)int_handler_0 , (FP)int_handler_4 };


#define TNUM_INTNO	1
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTNO _kernel_intinib_intno[TNUM_INTNO] = { 0 };
const ATR _kernel_intinib_intatr[TNUM_INTNO] = { TA_NULL };
const PRI _kernel_intinib_intpri[TNUM_INTNO] = { -1 };

/*
 *  CPU Exception Handler
 */

extern void exc_handler_0(void *excinf);
extern void exc_handler_1(void *excinf);

#define TNUM_EXCNO	2
const uint_t _kernel_tnum_excno = TNUM_EXCNO;

const EXCNO _kernel_excinib_excno[TNUM_EXCNO] = { 0 , 1 };
const ATR _kernel_excinib_excatr[TNUM_EXCNO] = { TA_NULL , TA_NULL };
const FP _kernel_excinib_entry[TNUM_EXCNO] = { (FP)exc_handler_0 , (FP)exc_handler_1 };


extern void cychdr1(intptr_t exinf);
extern void cychdr2(intptr_t exinf);

#define TNUM_CYCID	(2)

const ID _kernel_tmax_cycid = TNUM_CYCID;

/* 周期ハンドラ属性 */
const uint16_t _kernel_cycinib_cycact =  0x1;

/* 周期ハンドラアドレス */
const CYCHDR _kernel_cycinib_cychdr[TNUM_CYCID] = { cychdr1 , cychdr2 };

/* 周期ハンドラ周期 */
const RELTIM _kernel_cycinib_cyctim[TNUM_CYCID] = { 10 , 5 };

/* 周期ハンドラ位相 */
const RELTIM _kernel_cycinib_cycphs[TNUM_CYCID] = { 1 , 2 };

/* 周期ハンドラ拡張情報 */
const intptr_t _kernel_cycinib_exinf[TNUM_CYCID] = { 1 , 6 };

/* 周期ハンドラ動作状態 */
uint16_t _kernel_cyccb_cycact;

/* 周期ハンドラの次回起動時刻 */
EVTTIM _kernel_cyccb_evttim[TNUM_CYCID];

#define TNUM_TMEVT	(10)

/* 周期ハンドラのタイムイベントIDオフセット */
const uint_t _kernel_cycevtid_offset = 0;

/* タイムイベントブロックのサイズ */
const uint_t _kernel_tnum_tmevt_queue = TNUM_TMEVT;

/* タイムイベントキュー */
QUEUE _kernel_tmevt_queue[TNUM_TMEVT+1];

/* タイムイベントキュー */
EVTTIM _kernel_tmevt_time[TNUM_TMEVT];

/* タイムイベントのコールバック */
CBACK _kernel_tmevt_callback[TNUM_TMEVT];

/* タイムイベントコールバックの引数 */
uintptr_t _kernel_tmevt_arg[TNUM_TMEVT];


#define TNUM_ALMID	(2)

/* アラームハンドラのタイムイベントIDオフセット */
const uint_t _kernel_almevtid_offset = 2;

/* アラームIDの最大値 */
const ID _kernel_tmax_almid = 2;

extern void almhdr1(intptr_t exinf);
extern void almhdr2(intptr_t exinf);

/* アラームハンドラ先頭番地 */
const ALMHDR _kernel_alminib_almhdr[TNUM_ALMID] = 
{
	almhdr1 , almhdr2
};

/* アラームハンドラ拡張情報 */
const intptr_t _kernel_alminib_exinf[TNUM_ALMID] = { 1 , 2 };

/* アラームハンドラ状態 */
uint16_t _kernel_almcb_almact;


/* イベントフラグ */

#define TNUM_FLGID	(3)

/* イベントフラグIDの最大値 */
const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

/* イベントフラグ属性 */
const ATR _kernel_flginib_atr[TNUM_FLGID] = { TA_NULL , TA_NULL , TA_CLR};

/* イベントフラグ初期値 */
const FLGPTN _kernel_flginib_iflgptn[TNUM_FLGID] = { 0xAAAAAAAA , 0x55555555 , 0x12345678 };

/*
 *  イベントフラグ管理ブロック
 */

/* イベントフラグ現在パターン */
FLGPTN _kernel_flgcb_flgptn[TNUM_FLGID];


/* データキュー */

#define TNUM_DTQID	(2)

/*
 *  データキュー初期化ブロック
 */

intptr_t _kernel_dataqueue_0[3];
intptr_t _kernel_dataqueue_1[5];

const ATR _kernel_dtqinib_atr[TNUM_DTQID] = { TA_NULL , TA_NULL };		/* データキュー属性 */
intptr_t* const _kernel_dtqinib_data[TNUM_DTQID]
 = { _kernel_dataqueue_0 , _kernel_dataqueue_1 };	/* データ格納領域の先頭番地 */
const uint8_t _kernel_dtqinib_size[TNUM_DTQID] = { 3 , 5 };	/* データキューの容量 */

/*
 *  データキュー管理ブロック
 */
uint8_t _kernel_dtqcb_count[TNUM_DTQID];			/* データキューに格納されているデータの数 */
uint8_t _kernel_dtqcb_head[TNUM_DTQID];				/* 最初のデータの格納場所 */
uint8_t _kernel_dtqcb_tail[TNUM_DTQID];				/* 最後のデータの格納場所の次 */


/*
 *  データキューIDの最大値（kernel_cfg.c）
 */
const ID	_kernel_tmax_dtqid = TNUM_DTQID;


/*
 *  Stack Area for System
 */

#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ
static STK_T          		_kernel_stack[COUNT_STK_T(TOPPERS_ISTKSZ+TOPPERS_TSTKSZ)];
#define TOPPERS_STK   		_kernel_stack
#define TOPPERS_STKSZ		ROUND_STK_T(TOPPERS_ISTKSZ+TOPPERS_TSTKSZ)


const SIZE		_kernel_stksz = TOPPERS_STKSZ;
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
	_kernel_initialize_task();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
}

/*
 *  Target-dependent Definitions
 */

const bool_t _kernel_bitpat_cfgint[64] =
{
	true, 
	false, 
	false, 
	false, 
	true, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false, 
	false
};

