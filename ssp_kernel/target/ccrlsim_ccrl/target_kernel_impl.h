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

/*
 *		カーネルのターゲット依存部（CCRLシミュレータ用）
 *
 *  カーネルのターゲット依存部のヘッダファイル．kernel_impl.hのターゲッ
 *  ト依存部の位置付けとなる．
 */

#ifndef TOPPERS_TARGET_KERNEL_IMPL_H
#define TOPPERS_TARGET_KERNEL_IMPL_H

#include <kernel.h>

/*
 *  エラーチェック方法の指定
 */
#define CHECK_STKSZ_ALIGN	2	/* スタックサイズのアライン単位 */
#define CHECK_INTPTR_ALIGN	4	/* intptr_t型の変数のアライン単位 */
#define CHECK_INTPTR_NONNULL	/* intptr_t型の変数の非NULLチェック */
#define CHECK_FUNC_ALIGN	2	/* 関数のアライン単位 */
#define CHECK_FUNC_NONNULL		/* 関数の非NULLチェック */
#define CHECK_STACK_ALIGN	2	/* スタック領域のアライン単位 */
#define CHECK_STACK_NONNULL		/* スタック領域の非NULLチェック */
#define CHECK_MPF_ALIGN		4	/* 固定長メモリプール領域のアライン単位 */
#define CHECK_MPF_NONNULL		/* 固定長メモリプール領域の非NULLチェック */
#define CHECK_MB_ALIGN		4	/* 管理領域のアライン単位 */

/*
 *  トレースログに関する設定
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "arch/tracelog/trace_log.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  トレースログマクロのデフォルト定義
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
 *  非タスクコンテキスト用スタックのデフォルトのサイズ
 */
#define DEFAULT_ISTKSZ			2048

#ifndef TOPPERS_MACRO_ONLY



/*
 *  割込みを受け付けるための遅延処理
 */
Inline void
delay_for_interrupt(void)
{
}


/*
 *  オーバランハンドラ停止のためのマクロ
 */
#ifdef TOPPERS_SUPPORT_OVRHDR
#define OVRTIMER_STOP()	{				\
			lock_cpu();					\
			_kernel_ovrtimer_stop();	\
			unlock_cpu();				\
		}
#else /* TOPPERS_SUPPORT_OVRHDR */
#define OVRTIMER_STOP()
#endif /* TOPPERS_SUPPORT_OVRHDR */



/*
 *  ターゲットシステム依存の初期化
 */
extern void	target_initialize(void);

/*
 *  ターゲットシステムの終了
 *
 *  システムを終了する時に使う．
 */
extern void	target_exit(void) NoReturn;

/* チップ依存のカーネル依存部のインクルード */
#include "chip_kernel_impl.h"

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_KERNEL_IMPL_H */
