/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 * ターゲット依存部モジュール（Windowsテスト環境用）
 *
 * カーネルのターゲット依存部のインクルードファイル．kernel_impl.hのター
 * ゲット依存部の位置付けとなす．
 */

/*
 *  トレースログに関する設定
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  デフォルトの非タスクコンテキスト用のスタック領域の定義
 *  8byte単位で取得される． 
 */
#define DEFAULT_ISTKSZ			(0x1000/8U)		/* 4KByte */
/*
 *  非タスクコンテキスト用のスタック初期値
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((istk) + (istksz)))


/*
 *  微少時間待ちのための定義（本来はSILのターゲット依存部）
 */
#define SIL_DLY_TIM1    162
#define SIL_DLY_TIM2    100

#define TIC_NUME		1

#ifndef TOPPERS_MACRO_ONLY

/*
 *  TOPPERS標準割込み処理モデルの実現
 */

/*
 *  CPUロックフラグ実現のための変数
 * 
 *  これらの変数は，CPUロック状態の時のみ書き換えてもよいとする．
 *  インライン関数中で，アクセスの順序が変化しないよう，volatile を指定． 
 */
extern volatile bool_t  lock_flag;    /* CPUロックフラグの値を保持する変数 */
extern volatile uint32_t saved_iipm;  /* 割込み優先度をマスクする変数 */

extern uint_t intnest;

/*
 *  コンテキストの参照
 *
 */
Inline bool_t
sense_context(void)
{
	return (intnest > 0);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  割込み優先度マスクの外部表現と内部表現の変換
 */
#define EXT_IPM(iipm)   (-(iipm))		/* 内部表現を外部表現に */
#define INT_IPM(ipm)    (-(ipm))		/* 外部表現を内部表現に */

/*
 *  CPUロック状態での割込み優先度マスク
 */
#define TIPM_LOCK    TMIN_INTPRI

/*
 *  CPUロック状態での割込み優先度マスクの内部表現
 *
 *  TIPM_LOCKは，CPUロック状態でのBASEPRIの値．カーネル管理外のものを
 *  除くすべての割込みをマスクする値に定義する．  
 */
#define IIPM_LOCK    INT_IPM(TIPM_LOCK)

/*
 *  TIPM_ENAALL（割込み優先度マスク全解除）の内部表現
 *
 *  BASEPRIに '0' を設定することで，全割込みを許可する．
 */
#define IIPM_ENAALL  (0)


#ifndef TOPPERS_MACRO_ONLY


/*
 *  CPUロック状態への移行
 */
Inline void
x_lock_cpu(void)
{
	lock_flag = true;
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPUロック状態の解除
 */
Inline void
x_unlock_cpu(void)
{
	lock_flag = false;
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  CPUロック状態の参照
 */
Inline bool_t
x_sense_lock(void)
{
	return(lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()

/*
 * （モデル上の）割込み優先度マスクの設定
 *
 *  CPUロックフラグがクリアされている時は，ハードウェアの割込み優先度マ
 *  スクを設定する．CPUロックフラグがセットされている時は，saved_iipm
 *  を設定し，さらに，ハードウェアの割込み優先度マスクを，設定しようと
 *  した（モデル上の）割込み優先度マスクとTIPM_LOCKの高い方に設定する．
 */
Inline void
x_set_ipm(PRI intpri)
{
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 *  割込み番号・割込みハンドラ番号
 *
 *  割込みハンドラ番号(inhno)と割込み番号(intno)は，割り込み発生時に
 *  EPSRに設定される例外番号とする． 
 */

/*
 *  割込み番号の範囲の判定
 */
#define VALID_INTNO(intno)           ((TMIN_INTNO <= (intno)) && ((intno) <= TMAX_INTNO))
#define VALID_INTNO_DISINT(intno)    VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)    VALID_INTNO(intno)

/*
 *  割込みハンドラの設定
 *
 *  ベクトル番号inhnoの割込みハンドラの起動番地int_entryに設定する．割込み
 *  ハンドラテーブル
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  割込みハンドラの出入口処理の生成マクロ
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) extern void inthdr(void);

/*
 *  割込み要求禁止フラグ
 */

/*
 *  割込み属性が設定されているかを判別するための変数（kernel_cfg.c）
 */
extern const bool_t	bitpat_cfgint[];

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．  
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	return bitpat_cfgint[intno];
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *  割込み要求禁止フラグの解除
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	return bitpat_cfgint[intno];

}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *  割込み要求ラインの属性の設定
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  割込みハンドラ入口で必要なIRC操作
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  CPU例外ハンドラ関係
 */ 

/*
 *  CPU例外ハンドラ番号
 */
#define VALID_EXCNO_DEFEXC(excno)    (TMIN_EXCNO <= (excno) && (excno) <= TMAX_EXCNO)

/*
 *  CPU例外ハンドラの許可
 */
extern void enable_exc(EXCNO excno);

/*
 *  CPU例外ハンドラの禁止
 */
extern void disable_exc(EXCNO excno);

/*
 *  CPU例外ハンドラの設定
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
}

/*
 *  CPU例外ハンドラの入口処理の生成マクロ
 */
#define EXC_ENTRY(excno, exchdr)    exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr) extern void exchdr(void *p_excinf);

/*
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，割込みロック状態でなく，CPUロック状態でなく，（モ
 *  デル上の）割込み優先度マスク全解除状態である時にtrue，そうでない時
 *  にfalseを返す（CPU例外がカーネル管理外の割込み処理中で発生した場合
 *  にもfalseを返す）．
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return false;
}

/*
 *  CPU例外の発生した時のコンテキストと割込み／CPUロック状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，割込みロック状態でなく，CPUロック状態でない時に
 *  true，そうでない時にfalseを返す（CPU例外がカーネル管理外の割込み処
 *  理中で発生した場合にもfalseを返す）．
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
	return false;
}

/*
 *  CPU例外エントリ（prc_support.S）
 */
extern void exc_entry(void);

/*
 *  割込みエントリ（prc_support.S）
 */
extern void int_entry(void);

/*
 *  プロセッサ依存の初期化
 */
extern void prc_initialize(void);

/*
 *  プロセッサ依存の終了時処理
 */
extern void prc_terminate(void);

/* アイドルループの処理 */
#define idle_loop()						\
	{									\
		static volatile int count = 0;	\
		if(count++ >= 1u)				\
		{								\
			break;						\
		}								\
	}									\

/*
 *  カーネルの終了処理の呼出し
 *
 *  call_exit_kernelは，カーネルの終了時に呼び出すべきもので，非タスク
 *  コンテキストに切り換えて，カーネルの終了処理（exit_kernel）を呼び出
 *  す．
 */
extern void call_exit_kernel(void);

/*
 *  atexitの処理とデストラクタの実行
 */
Inline void
call_atexit(void)
{
	extern void    software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}
}

/*
 * 登録されていない例外が発生すると呼び出される
 */
extern void default_exc_handler(void *p_excinf);

/*
 * 未登録の割込みが発生した場合に呼び出される
 */
extern void default_int_handler(void *p_excinf);

/*
 *  ターゲットシステム依存の初期化
 */
extern void	target_initialize(void);

/*
 *  ディスパッチ開始時処理
 */
extern void start_dispatch(void) NoReturn;

/*
 *  ターゲットシステムの終了
 *
 *  システムを終了する時に使う．
 */
extern void	target_exit(void);

#endif /* TOPPERS_MACRO_ONLY */


#endif /* TOPPERS_TARGET_CONFIG_H */
