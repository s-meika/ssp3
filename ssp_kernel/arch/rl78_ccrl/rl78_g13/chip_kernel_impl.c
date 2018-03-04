/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2017 by Meika Sugimoto
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
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

#include "kernel_impl.h"

/*
 *  カーネルのプロセッサ依存部（RL78/G13用）
 */


/* 割り込み要求フラグ・レジスタ */
#define IF0L_ADDR ((volatile __far uint8_t *)0xFFFE0)
#define IF0H_ADDR ((volatile __far uint8_t *)0xFFFE1)
#define IF1L_ADDR ((volatile __far uint8_t *)0xFFFE2)
#define IF1H_ADDR ((volatile __far uint8_t *)0xFFFE3)
#define IF2L_ADDR ((volatile __far uint8_t *)0xFFFD0)
#define IF2H_ADDR ((volatile __far uint8_t *)0xFFFD1)
#define IF3L_ADDR ((volatile __far uint8_t *)0xFFFD2)

/* 割り込みマスク・フラグ・レジスタ */
#define MK0L_ADDR ((volatile __far uint8_t *)0xFFFE4)
#define MK0H_ADDR ((volatile __far uint8_t *)0xFFFE5)
#define MK1L_ADDR ((volatile __far uint8_t *)0xFFFE6)
#define MK1H_ADDR ((volatile __far uint8_t *)0xFFFE5)
#define MK2L_ADDR ((volatile __far uint8_t *)0xFFFD4)
#define MK2H_ADDR ((volatile __far uint8_t *)0xFFFD5)
#define MK3L_ADDR ((volatile __far uint8_t *)0xFFFD6)

/* 優先順位指定フラグ・レジスタ */
#define PR00L_ADDR ((volatile __far uint8_t *)0xFFFE8)
#define PR10L_ADDR ((volatile __far uint8_t *)0xFFFEC)
#define PR00H_ADDR ((volatile __far uint8_t *)0xFFFE9)
#define PR10H_ADDR ((volatile __far uint8_t *)0xFFFED)
#define PR01L_ADDR ((volatile __far uint8_t *)0xFFFEA)
#define PR11L_ADDR ((volatile __far uint8_t *)0xFFFEE)
#define PR01H_ADDR ((volatile __far uint8_t *)0xFFFEB)
#define PR11H_ADDR ((volatile __far uint8_t *)0xFFFEF)
#define PR02L_ADDR ((volatile __far uint8_t *)0xFFFD8)
#define PR12L_ADDR ((volatile __far uint8_t *)0xFFFDC)
#define PR02H_ADDR ((volatile __far uint8_t *)0xFFFD9)
#define PR12H_ADDR ((volatile __far uint8_t *)0xFFFDD)
#define PR03L_ADDR ((volatile __far uint8_t *)0xFFFDA)
#define PR13L_ADDR ((volatile __far uint8_t *)0xFFFDE)

/* 外部割り込み立ち上がりエッジ許可レジスタ */
#define EGP0_ADDR ((volatile __far uint8_t *)0xFFF38)
#define EGP1_ADDR ((volatile __far uint8_t *)0xFFF3A)
#define EGN0_ADDR ((volatile __far uint8_t *)0xFFF39)
#define EGN1_ADDR ((volatile __far uint8_t *)0xFFF3B)



/* 割込み制御情報テーブル */
RL78G13_INTCTL_INFO const intctl_reg_table[RL78_G13_INTNO_MAX+1] = 
{
	/* 00:WDT */
	{
		{ IF0L_ADDR, 1U  << 0 },
		{ MK0L_ADDR, 1U  << 0 },
		{ PR00L_ADDR, 1U << 0 },
		{ PR10L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 01:INTLVL */
	{
		{ IF0L_ADDR, 1U  << 1 },
		{ MK0L_ADDR, 1U  << 1 },
		{ PR00L_ADDR, 1U << 1 },
		{ PR10L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 02:INT0 */
	{
		{ IF0L_ADDR, 1U  << 2 },
		{ MK0L_ADDR, 1U  << 2 },
		{ PR00L_ADDR, 1U << 2 },
		{ PR10L_ADDR, 1U << 2 },
		{ EGP0_ADDR, 1U  << 0 },
		{ EGN0_ADDR, 1U  << 0 }
	},
	/* 03:INT1 */
	{
		{ IF0L_ADDR, 1U  << 3 },
		{ MK0L_ADDR, 1U  << 3 },
		{ PR00L_ADDR, 1U << 3 },
		{ PR10L_ADDR, 1U << 3 },
		{ EGP0_ADDR, 1U  << 1 },
		{ EGN0_ADDR, 1U  << 1 }
	},
	/* 04:INT2 */
	{
		{ IF0L_ADDR, 1U  << 4 },
		{ MK0L_ADDR, 1U  << 4 },
		{ PR00L_ADDR, 1U << 4 },
		{ PR10L_ADDR, 1U << 4 },
		{ EGP0_ADDR, 1U  << 2 },
		{ EGN0_ADDR, 1U  << 2 }
	},
	/* 05:INT3 */
	{
		{ IF0L_ADDR, 1U  << 5 },
		{ MK0L_ADDR, 1U  << 5 },
		{ PR00L_ADDR, 1U << 5 },
		{ PR10L_ADDR, 1U << 5 },
		{ EGP0_ADDR, 1U  << 3 },
		{ EGN0_ADDR, 1U  << 3 }
	},
	/* 06::INT4 */
	{
		{ IF0L_ADDR, 1U  << 6 },
		{ MK0L_ADDR, 1U  << 6 },
		{ PR00L_ADDR, 1U << 6 },
		{ PR10L_ADDR, 1U << 6 },
		{ EGP0_ADDR, 1U  << 4 },
		{ EGN0_ADDR, 1U  << 4 }
	},
	/* 07:INT5 */
	{
		{ IF0L_ADDR, 1U  << 7 },
		{ MK0L_ADDR, 1U  << 7 },
		{ PR00L_ADDR, 1U << 7 },
		{ PR10L_ADDR, 1U << 7 },
		{ EGP0_ADDR, 1U  << 5 },
		{ EGN0_ADDR, 1U  << 5 }
	},
	/* 08:UART2 TX */
	{
		{ IF0H_ADDR, 1U  << 0 },
		{ MK0H_ADDR, 1U  << 0 },
		{ PR00H_ADDR, 1U << 0 },
		{ PR10H_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 09:UART2 RX */
	{
		{ IF0H_ADDR, 1U  << 1 },
		{ MK0H_ADDR, 1U  << 1 },
		{ PR00H_ADDR, 1U << 1 },
		{ PR10H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 10:UART2 ERROR or TIMER 11 */
	{
		{ IF0H_ADDR, 1U  << 2 },
		{ MK0H_ADDR, 1U  << 2 },
		{ PR00H_ADDR, 1U << 2 },
		{ PR10H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 11:DMA0 */
	{
		{ IF0H_ADDR, 1U  << 3 },
		{ MK0H_ADDR, 1U  << 3 },
		{ PR00H_ADDR, 1U << 3 },
		{ PR10H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 12:DMA1 */
	{
		{ IF0H_ADDR, 1U  << 4 },
		{ MK0H_ADDR, 1U  << 4 },
		{ PR00H_ADDR, 1U << 4 },
		{ PR10H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 13:UART0 TX */
	{
		{ IF0H_ADDR, 1U  << 5 },
		{ MK0H_ADDR, 1U  << 5 },
		{ PR00H_ADDR, 1U << 5 },
		{ PR10H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 14:UART0 RX */
	{
		{ IF0H_ADDR, 1U  << 6 },
		{ MK0H_ADDR, 1U  << 6 },
		{ PR00H_ADDR, 1U << 6 },
		{ PR10H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 15:UART0 ERROR or TIMER 01 */
	{
		{ IF0H_ADDR, 1U  << 7 },
		{ MK0H_ADDR, 1U  << 7 },
		{ PR00H_ADDR, 1U << 7 },
		{ PR10H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 16:UART1 TX */
	{
		{ IF1L_ADDR, 1U  << 0 },
		{ MK1L_ADDR, 1U  << 0 },
		{ PR01L_ADDR, 1U << 0 },
		{ PR10L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 17:UART1 RX */
	{
		{ IF1L_ADDR, 1U  << 1 },
		{ MK1L_ADDR, 1U  << 1 },
		{ PR01L_ADDR, 1U << 1 },
		{ PR10L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 18:UART1 ERROR or TIMER 03 */
	{
		{ IF1L_ADDR, 1U  << 2 },
		{ MK1L_ADDR, 1U  << 2 },
		{ PR01L_ADDR, 1U << 2 },
		{ PR10L_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 19:IICA0 */
	{
		{ IF1L_ADDR, 1U  << 3 },
		{ MK1L_ADDR, 1U  << 3 },
		{ PR01L_ADDR, 1U << 3 },
		{ PR10L_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 20:タイマ00 */
	{
		{ IF1L_ADDR, 1U  << 4 },
		{ MK1L_ADDR, 1U  << 4 },
		{ PR01L_ADDR, 1U << 4 },
		{ PR10L_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 21:タイマ01 */
	{
		{ IF1L_ADDR, 1U  << 5 },
		{ MK1L_ADDR, 1U  << 5 },
		{ PR01L_ADDR, 1U << 5 },
		{ PR10L_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 22:タイマ02 */
	{
		{ IF1L_ADDR, 1U  << 6 },
		{ MK1L_ADDR, 1U  << 6 },
		{ PR01L_ADDR, 1U << 6 },
		{ PR10L_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 23:タイマ03 */
	{
		{ IF1L_ADDR, 1U  << 7 },
		{ MK1L_ADDR, 1U  << 7 },
		{ PR01L_ADDR, 1U << 7 },
		{ PR10L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 24:AD変換終了 */
	{
		{ IF1H_ADDR, 1U  << 0 },
		{ MK1H_ADDR, 1U  << 0 },
		{ PR01H_ADDR, 1U << 0 },
		{ PR10H_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 25:RTC */
	{
		{ IF1H_ADDR, 1U  << 1 },
		{ MK1H_ADDR, 1U  << 1 },
		{ PR01H_ADDR, 1U << 1 },
		{ PR10H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 26:12bit インターバルタイマ */
	{
		{ IF1H_ADDR, 1U  << 2 },
		{ MK1H_ADDR, 1U  << 2 },
		{ PR01H_ADDR, 1U << 2 },
		{ PR10H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 27:キーリターン */
	{
		{ IF1H_ADDR, 1U  << 3 },
		{ MK1H_ADDR, 1U  << 3 },
		{ PR01H_ADDR, 1U << 3 },
		{ PR10H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 28:UART30 TX */
	{
		{ IF1H_ADDR, 1U  << 4 },
		{ MK1H_ADDR, 1U  << 4 },
		{ PR01H_ADDR, 1U << 4 },
		{ PR10H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 29:UART30 RX */
	{
		{ IF1H_ADDR, 1U  << 5 },
		{ MK1H_ADDR, 1U  << 5 },
		{ PR01H_ADDR, 1U << 5 },
		{ PR10H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 30:UART30 ERROR or TIMER 13 */
	{
		{ IF1H_ADDR, 1U  << 6 },
		{ MK1H_ADDR, 1U  << 6 },
		{ PR01H_ADDR, 1U << 6 },
		{ PR10H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 31:タイマ04 */
	{
		{ IF1H_ADDR, 1U  << 7 },
		{ MK0H_ADDR, 1U  << 7 },
		{ PR01H_ADDR, 1U << 7 },
		{ PR10H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 32:タイマ05 */
	{
		{ IF2L_ADDR, 1U  << 0 },
		{ MK2L_ADDR, 1U  << 0 },
		{ PR02L_ADDR, 1U << 0 },
		{ PR12L_ADDR, 1U << 0 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 33:タイマ06 */
	{
		{ IF2L_ADDR, 1U  << 1 },
		{ MK2L_ADDR, 1U  << 1 },
		{ PR02L_ADDR, 1U << 1 },
		{ PR12L_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 34:タイマ07 */
	{
		{ IF2L_ADDR, 1U  << 2 },
		{ MK2L_ADDR, 1U  << 2 },
		{ PR02L_ADDR, 1U << 2 },
		{ PR12L_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 35:INT6 */
	{
		{ IF2L_ADDR, 1U  << 3 },
		{ MK2L_ADDR, 1U  << 3 },
		{ PR02L_ADDR, 1U << 3 },
		{ PR12L_ADDR, 1U << 3 },
		{ EGP0_ADDR, 1U  << 6 },
		{ EGN0_ADDR, 1U  << 6 }
	},
	/* 36:INT7 */
	{
		{ IF2L_ADDR, 1U  << 4 },
		{ MK2L_ADDR, 1U  << 4 },
		{ PR02L_ADDR, 1U << 4 },
		{ PR12L_ADDR, 1U << 4 },
		{ EGP0_ADDR, 1U  << 7 },
		{ EGN0_ADDR, 1U  << 7 }
	},
	/* 37:INT8 */
	{
		{ IF2L_ADDR, 1U  << 5 },
		{ MK2L_ADDR, 1U  << 5 },
		{ PR02L_ADDR, 1U << 5 },
		{ PR12L_ADDR, 1U << 5 },
		{ EGP1_ADDR, 1U  << 0 },
		{ EGN1_ADDR, 1U  << 0 }
	},
	/* 38:INT9 */
	{
		{ IF2L_ADDR, 1U  << 6 },
		{ MK2L_ADDR, 1U  << 6 },
		{ PR02L_ADDR, 1U << 6 },
		{ PR12L_ADDR, 1U << 6 },
		{ EGP1_ADDR, 1U  << 1 },
		{ EGN1_ADDR, 1U  << 1 }
	},
	/* 39:INT10 */
	{
		{ IF2L_ADDR, 1U  << 7 },
		{ MK2L_ADDR, 1U  << 7 },
		{ PR02L_ADDR, 1U << 7 },
		{ PR12L_ADDR, 1U << 7 },
		{ EGP1_ADDR, 1U  << 2 },
		{ EGN1_ADDR, 1U  << 2 }
	},
	/* 40:INT11 */
	{
		{ IF2H_ADDR, 1U  << 0 },
		{ MK2H_ADDR, 1U  << 0 },
		{ PR02H_ADDR, 1U << 0 },
		{ PR12H_ADDR, 1U << 0 },
		{ EGP1_ADDR, 1U  << 3 },
		{ EGN1_ADDR, 1U  << 3 }
	},
	/* 41:タイマ10 */
	{
		{ IF2H_ADDR, 1U  << 1 },
		{ MK2H_ADDR, 1U  << 1 },
		{ PR02H_ADDR, 1U << 1 },
		{ PR12H_ADDR, 1U << 1 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 42:タイマ11 */
	{
		{ IF2H_ADDR, 1U  << 2 },
		{ MK2H_ADDR, 1U  << 2 },
		{ PR02H_ADDR, 1U << 2 },
		{ PR12H_ADDR, 1U << 2 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 43:タイマ12 */
	{
		{ IF2H_ADDR, 1U  << 3 },
		{ MK2H_ADDR, 1U  << 3 },
		{ PR02H_ADDR, 1U << 3 },
		{ PR12H_ADDR, 1U << 3 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 44:タイマ13 or UART3 ERROR */
	{
		{ IF2H_ADDR, 1U  << 4 },
		{ MK2H_ADDR, 1U  << 4 },
		{ PR02H_ADDR, 1U << 4 },
		{ PR12H_ADDR, 1U << 4 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 45:除算終了，積和演算オーバーフロー */
	{
		{ IF2H_ADDR, 1U  << 5 },
		{ MK2H_ADDR, 1U  << 5 },
		{ PR02H_ADDR, 1U << 5 },
		{ PR12H_ADDR, 1U << 5 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 46:IICA1	 */
	{
		{ IF2H_ADDR, 1U  << 6 },
		{ MK2H_ADDR, 1U  << 6 },
		{ PR02H_ADDR, 1U << 6 },
		{ PR12H_ADDR, 1U << 6 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 47:予約 */
	{
		{ IF2H_ADDR, 1U  << 7 },
		{ MK2H_ADDR, 1U  << 7 },
		{ PR02H_ADDR, 1U << 7 },
		{ PR12H_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 48:DMA2 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 49:DMA3 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 50:タイマ14 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 51:タイマ15 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 52:タイマ16 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	},
	/* 53:タイマ17 */
	{
		{ IF3L_ADDR, 1U  << 7 },
		{ MK3L_ADDR, 1U  << 7 },
		{ PR03L_ADDR, 1U << 7 },
		{ PR13L_ADDR, 1U << 7 },
		{ NULL, 0U },
		{ NULL, 0U }
	}
};

/*
 *  チップ依存部の初期化 
 */
void chip_initialize(void)
{
	/* プロセッサ依存の初期化 */
	prc_initialize();
}

