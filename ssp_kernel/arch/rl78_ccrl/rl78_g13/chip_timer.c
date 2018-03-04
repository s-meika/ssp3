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


#include "kernel_int.h"
#include <sil.h>
#include "target_timer.h"
#include "chip_timer.h"

/* 使用タイマ番号 */
#define TIMER_NO_MASTER		(HRT_TIMER_NO)
#define TIMER_NO_SLAVE		(HRT_TIMER_NO + 1)


/*
 *  レジスタアドレスの算出マクロ
 *
 *  ROM容量を減らすためにテーブル化せず，マクロで直接アドレス算出する
 */
#define PER0_ADDR			((uint8_t __far *)0xF00F0)	/* 周辺イネーブル・レジスタ 0 */
#define TPS0_ADDR			((uint16_t __far *)0xF01B6)	/* タイマ・クロック選択レジスタ0 */
#define TS0L_ADDR			((uint16_t __far *)0xF01B2)	/* タイマ・チャネル開始レジスタ0 */
#define TT0L_ADDR			((uint16_t __far *)0xF01B4)	/* タイマ・チャネル停止レジスタ0 */

/* タイマ・モードレジスタ0 */
#define TMR0x_ADDR(x)		((uint16_t __far *)0xF0190 + (x))
/* タイマ・データレジスタ */
#define TDR0x_ADDR(x)	( x < 2 )? ((uint16_t __far *)0xFFF18 + (x)) : ((uint16_t __far *)0xFFF64 + (x))
/* タイマ・カウンタレジスタ */
#define TCR0x_ADDR(x)		((uint16_t __far *)0xF0180 + (x))

/* 割込み要求フラグレジスタ */
#if ( TAU_NUMBER >= 0 ) && ( TAU_NUMBER <= 3 )
#define IFx					((uint8_t __far *)0xFFFE2)		/* IF1L */
#define IFx_bit				( 0x01U << ( TAU_NUMBER + 4 ) )
#elif ( TAU_NUMBER == 4 )
#define IFx					((uint8_t*) __far 0xFFFE3)		/* IF1H */
#define IFx_bit				( 0x01U << 7 ) )
#elif ( TAU_NUMBER >= 5 ) && ( TAU_NUMBER <=7 )
#define IFx					((uint8_t __far *)0xFFFD0)		/* IF2L */
#define IFx_bit				( 0x01U << ( TAU_NUMBER - 5 ) )
#else
#error TAU_NUMBER is allowed from 0 to 7.
#endif /* TAU_NUMBER */


/* カウントからμ秒への返還 */
#define COUNT2USEC( cnt )	( (cnt) )

/*
 *  高分解能タイマの初期化処理
 */
void chip_hrt_timer_initialize(intptr_t exinf)
{
	/* TAU0の有効化 */
	sil_wrb_mem( PER0_ADDR, sil_reb_mem( PER0_ADDR ) | 0x01U );

	/*
	 *  タイマクロックの設定
	 *
	 *  CK00    1MHz(32分周)
	 *  CK01    32MHz(デフォルト設定)
	 *  CK02    16MHz(デフォルト設定)
	 *  CK03    125kHz(デフォルト設定)
	 */
	sil_wrh_mem( TPS0_ADDR , 0x0005U );

	/* タイマ停止 */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );

	/* タイマ設定 */
	sil_wrh_mem( TDR0x_ADDR( TAU_NUMBER), TO_CLOCK(TIC_NUME, TIC_DENO) );
	sil_wrh_mem( TMR0x_ADDR( TAU_NUMBER) ,
				0x0000U   << 14U		/* CKS:CK00 */
				| 0x0000U << 12U		/* CCS:CKSで指定したクロック */
				| 0x0001U << 11U		/* MASTER:マスター動作 */
				| 0x0000U << 8U 		/* STS:ソフトウェアトリガ */
				| 0x0000U << 6U 		/* CIS:Don't care */
				| 0x0000U << 0U			/* MD:インターバル */
			);


	/* タイマ開始 */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );
}

/*
 *  高分解能タイマの終了処理
 */
void chip_hrt_timer_terminate(intptr_t exinf)
{
	/* タイマ停止 */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );
}

/*
 *  高分解能タイマへの割込みタイミングの設定
 */
void chip_hrt_set_event(HRTCNT hrtcnt)
{

}

/*
 *  高分解能タイマ割込みの要求
 */
void chip_hrt_raise_event(void)
{
	
}

/*
 *  高分解能タイマ割込みハンドラ
 */
void chip_hrt_handler(void)
{
}

