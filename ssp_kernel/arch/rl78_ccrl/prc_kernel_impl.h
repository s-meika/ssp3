/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2017 by Meika Sugimoto
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 */

#ifndef PRC_KERNEL_IMPL_H
#define PRC_KERNEL_IMPL_H

#include "builtin.h"

/*
 *  CPU例外ハンドラ番号の範囲の判定
 */
#define VALID_EXCNO(excno)	(void)0

/*
 *  非タスクコンテキスト用のスタック初期値
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((istk) + (istksz)))

/* 全割込み解除時の割込みレベルマスク */
#define IIPM_ENAALL   ( 0U )

/*
 *  割込みハンドラの入口処理の生成マクロ
 */

extern void _kernel_interrupt(const uint16_t inhno, void (*inthdr)(void));
#define INT_ENTRY(inhno, inthdr)	inthdr
#define INTHDR_ENTRY(inhno, intno, inthdr)

/*
 *  CPU例外ハンドラの入口処理の生成マクロ
 */
#define EXC_ENTRY(excno, exchdr)	exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr)	\
	Asm("\tPUSH AX");	\
	Asm("\tPUSH BC");	\
	Asm("\tPUSH DE");	\
	Asm("\tPUSH HL");	\
	Asm("\tPUSH ES");	\
	Asm("\tPUSH CS");	\
	Asm("\tMOV X, #" ## inhno);	\
	Asm("\tMOVW BC, !!_" ## inthdr);	\
	Asm("\tMOVW ES, HIGHW(, _" ## inthdr ## ")");	\
	Asm("\tBR !!__kernel_int_entry");

#define ISP_MASK	(0x06U)
	
/* 状態管理用変数 */
extern bool_t	lock_flag;
extern PRI		saved_iipm;
extern uint8_t	intnest;


/*
 *  プロセッサ依存部の初期化
 */
extern void prc_initialize(void);

/*
 *  コンテキストの参照
 */
Inline bool_t
sense_context(void)
{
	return (intnest > 0U);
}

/*
 *  CPUロック状態への遷移
 */
Inline void
lock_cpu(void)
{
	unsigned char current_psw;
	
	__DI();
	
	current_psw = __get_psw();
	
	saved_iipm = (current_psw & ISP_MASK) >> 0x1U;
	
	__set_psw(current_psw & ~ISP_MASK | (TIPM_LOCK << 1U));

	lock_flag = true;
	
	__EI();
}

/*
 *  CPUロック状態への移行（ディスパッチできる状態）
 */
#define lock_cpu_dsp()		lock_cpu()

/*
 *  CPUロック状態の解除
 */
Inline void
unlock_cpu(void)
{
	unsigned char current_psw;
	
	__DI();
	
	current_psw = __get_psw();
	lock_flag = false;
	
	__set_psw(current_psw & ~ISP_MASK | (saved_iipm << 1U));

	__EI();
}

/*
 *  CPUロック状態の解除（ディスパッチできる状態）
 */
#define unlock_cpu_dsp()	unlock_cpu()

/*
 *  CPUロック状態の参照
 */
Inline bool_t
sense_lock(void)
{
	return lock_flag;
}

/*
 *  割込み優先度マスクの設定
 */
Inline void
t_set_ipm(PRI intpri)
{
	if(lock_flag)
	{
		saved_iipm = intpri;
	}
	else
	{
		unsigned char current_psw = __get_psw();
		__set_psw(current_psw & ~0x06U | (intpri << 1U));
	}
}

/*
 *  割込み優先度マスクの参照
 */
Inline PRI
t_get_ipm(void)
{
	PRI ipm;
	
	if(lock_flag)
	{
		ipm = saved_iipm;
	}
	else
	{
		unsigned char current_psw = __get_psw();
		ipm = (current_psw >> 0x1U) & 0x03U;
	}

	return ipm;
}

/*
 *  ディスパッチャの動作開始
 */
extern void start_dispatch(void);





/*
 *  最高優先順位タスクへのディスパッチ
 */
extern void	dispatch(void);

/*
 *  非タスクコンテキストからのディスパッチ要求
 */
#define request_dispatch()

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
extern void	exit_and_dispatch(void);


/*
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル内のクリティカルセクショ
 *  ンの実行中でなく，全割込みロック状態でなく，CPUロック状態でなく，カー
 *  ネル管理外の割込みハンドラ実行中でなく，カーネル管理外のCPU例外ハン
 *  ドラ実行中でなく，タスクコンテキストであり，割込み優先度マスクが全
 *  解除である時にtrue，そうでない時にfalseを返す．
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(true);
}

/*
 *  割込みハンドラ出入口処理
 */
Inline void
int_handler_entry(void)
{
}

/*
 *  CPU例外ハンドラ出入口処理
 */
Inline void
exc_handler_entry(void)
{
}

/*
 *  CPU例外ハンドラの設定
 *
 *  ベクトル番号excnoのCPU例外ハンドラの出入口処理の番地をexc_entryに設
 *  定する．
 */
Inline void
define_exc(EXCNO excno, FP exc_entry)
{
	/* CPU例外はサポートしない */
}

/*
 *  アイドルループ
 */
extern void idle_loop(void);


/*
 *  カーネルの終了処理の呼出し
 */
extern void call_exit_kernel(void) NoReturn;



#endif /* PRC_KERNEL_IMPL_H */
