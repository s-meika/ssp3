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
 *		シリアルドライバのターゲット依存部（RL78/G13用）
 *
 *		本ドライバの使用時はSAU0/1が周辺イネーブルレジスタ0(PER0)で有効化されていることを前提とする
 */
 
#ifndef TOPPERS_CHIP_SERIAL_H
#define TOPPERS_CHIP_SERIAL_H

#include "kernel_impl.h"

#define TNUM_UART_CH	(4)

#ifndef TOPPERS_MACRO_ONLY
typedef struct
{
	__far uint16_t *SMR_tx;
	__far uint16_t *SMR_rx;
	__far uint16_t *SCR_tx;
	__far uint16_t *SCR_rx;
	__far uint16_t *SDR_tx;
	__far uint16_t *SDR_rx;
	__far uint16_t *SIR;
	__far uint16_t *SSR_tx;
	__far uint16_t *SSR_rx;
	__far uint8_t  *SPS;
	__far uint16_t *SS;
	__far uint16_t *ST;
	__far uint16_t *SOE;
	__far uint16_t *SO;
} SAU_REGADDRS;

/*
 *  シリアルポートの管理ブロック
 */
typedef struct sio_port_control_block {
	ID port;
	const SAU_REGADDRS *regaddrs;
	intptr_t exinf;
} SIOPCB;


/*
 *  UARTの初期化
 */
void sau_init(uint_t ch);

/*
 *  低レベル1文字出力
 */
extern void sau_log_output(uint_t ch, char c);


#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CHIP_SERIAL_H */
