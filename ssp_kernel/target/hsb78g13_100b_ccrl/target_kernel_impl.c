/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2010-2011,2016 by Meika Sugimoto
 * 
 *  上記著作権者は，以下の (1)～(4) の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改変・
 *  再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作権
 *      表示，この利用条件および下記の無保証規定が，そのままの形でソース
 *      コード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使用
 *      できる形で再配布する場合には，再配布に伴うドキュメント（利用者マ
 *      ニュアルなど）に，上記の著作権表示，この利用条件および下記の無保
 *      証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使用
 *      できない形で再配布する場合には，次のいずれかの条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに報
 *        告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損害
 *      からも，上記著作権者およびTOPPERSプロジェクトを免責すること．また，
 *      本ソフトウェアのユーザまたはエンドユーザからのいかなる理由に基づ
 *      く請求からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者およ
 *  びTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的に対す
 *  る適合性も含めて，いかなる保証も行わない．また，本ソフトウェアの利用
 *  により直接的または間接的に生じたいかなる損害に関しても，その責任を負
 *  わない．
 * 
 */

/*
 *		ターゲット依存モジュール（ダミーターゲット用）
 */

#include <sil.h>
#include "kernel_impl.h"
#include "task.h"
#include "chip_serial.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_DSP_ENTER
#define LOG_DSP_ENTER(p_tcb)
#endif /* LOG_DSP_ENTER */

#ifndef LOG_DSP_LEAVE
#define LOG_DSP_LEAVE(p_tcb)
#endif /* LOG_DSP_LEAVE */

/* 低レベル出力のシリアルチャンネル */
#define SAU_CH_LOWLEVEL_LOG (0)


#ifndef USE_SOFTWARE_INITHOOK
/*
 *  ターゲット依存のソフトウェア初期化
 */
void software_init_hook(void)
{
}
#endif /* USE_SOFTWARE_INITHOOK */

#ifndef USE_HARDWARE_INITHOOK

/*
 *  ターゲット依存のソフトウェア初期化
 */
void hardware_init_hook(void)
{
	__far uint8_t * const cmc = (__far uint8_t * )0xFFFA0;
	__far uint8_t * const ckc = (__far uint8_t * )0xFFFA4;
	__far uint8_t * const csc = (__far uint8_t * )0xFFFA1;
	__far volatile uint8_t * const ostc = (__far volatile uint8_t * )0xFFFA2;
	__far uint8_t * const osts = (__far uint8_t * )0xFFFA3;
	
	/* 10MHz < fx <= 20MHzで外部発振設定 */
	*cmc = 0x51U;
	/* 最大時間の2^18/fxで発振安定待ち設定 */
	*osts = 0x07U;
	/* メインクロックの発振開始 */
	*csc = 0x00U;
	
	/* 発振安定待ち */
	while(*ostc != 0xFFU)
		;
	
	/* クロック切換え */
	*ckc = 0x10U;	
}
#endif /* USE_HARDWARE_INITHOOK */

/*
 *  システムログの低レベル出力のための文字出力
 */
void target_fput_log(char c)
{
	sau_log_output(SAU_CH_LOWLEVEL_LOG, c);
}

/*
 *  カーネルの終了処理の呼出し
 */
void
call_exit_kernel(void)
{
	/* 非タスクコンテキストに切り換える */
	/* exit_kernelに分岐する */
	while (true);
}



/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	__far uint8_t * const pm1 = (uint8_t __far *)0xFFF21;
	__far uint8_t * const p1 = (uint8_t __far *)0xFFF01;
	
	/* シリアルポートの端子初期化(P11:RXD0, P12:TXD0) */
   	sil_wrb_mem(pm1, sil_reb_mem(pm1) & ~0x02); 
	sil_wrb_mem(pm1, sil_reb_mem(pm1) & ~0x04); 
	sil_wrb_mem(p1, sil_reb_mem(p1) | 0x04); 
	
	/* 低レベル出力の初期化 */
	sau_init(SAU_CH_LOWLEVEL_LOG);
	
	/* チップ依存部の初期化 */
	chip_initialize();
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	while( 1 )
	{
		;
	}
}

/*
 *  アイドルループ
 */
void idle_loop(void)
{
	unlock_cpu();
	__nop();
	lock_cpu();
}
