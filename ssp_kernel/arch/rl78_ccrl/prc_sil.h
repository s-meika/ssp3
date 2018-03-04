/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
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
 *		sil.hのターゲット依存部（RL78用）
 */

#ifndef TOPPERS_PRC_SIL_H
#define TOPPERS_PRC_SIL_H

#ifndef TOPPERS_MACRO_ONLY

#include <builtin.h>
#include "prc_sil.h"

/*
 *  全割込みロック状態の制御
 */
#define SIL_PRE_LOC		bool_t int_enable
#define SIL_LOC_INT()	\
	int_enable = ( __get_psw() & 0x80U != 0U )? true : false
#define SIL_UNL_INT()	\
	if( int_enable )	\
	{					\
		__EI();			\
	}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  プロセッサのエンディアン定義
 *    RL78はリトルエンディアン
 */
#define SIL_ENDIAN_LITTLE			/* リトルエンディアン */

#define TOPPERS_OMIT_SIL_ACCESS
/*
 *  8ビット単位の読出し／書込み
 */

Inline uint8_t
sil_reb_mem(const uint8_t __far *mem)
{
	uint8_t	data;

	data = *((const volatile __far uint8_t *) mem);
	return(data);
}

Inline void
sil_wrb_mem(uint8_t __far *mem, uint8_t data)
{
	*((volatile uint8_t *) mem) = data;
}

/*
 *  16ビット単位の読出し／書込み
 */

 Inline uint16_t
sil_reh_mem(const __far uint16_t *mem)
{
	uint16_t	data;

	data = *((const volatile uint16_t *) mem);
	return(data);
}

Inline void
sil_wrh_mem(uint16_t __far *mem, uint16_t data)
{
	*((volatile uint16_t *) mem) = data;
}

/*
 *  32ビット単位の読出し／書込み
 */

Inline uint32_t
sil_rew_mem(const __far uint32_t *mem)
{
	uint32_t	data;

	data = *((const volatile uint32_t *) mem);
	return(data);
}

Inline void
sil_wrw_mem(uint32_t __far *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = data;
}
#endif /* TOPPERS_PRC_SIL_H */
