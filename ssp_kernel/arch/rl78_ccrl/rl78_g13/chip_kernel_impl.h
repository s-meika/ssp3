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

/* カーネル実装依存部(RL78/G13用) */

#ifndef TOPPERS_CHIP_KERNEL_IMPL_H
#define TOPPERS_CHIP_KERNEL_IMPL_H

/*
 *  割込み番号，割込みハンドラ番号の判定
 *
 *  0とINTNOの比較は意味がないため，警告回避のためコメントアウトしている
 */
#define	VALID_INTNO(intno)	(/* 0U <= (intno) && */ (intno) <= (INTNO)RL78_G13_INTNO_MAX)
#define VALID_INHNO(inhno)	VALID_INTNO((INTNO)(inhno))

/* カーネルのコア依存部のインクルード */
#include "prc_kernel_impl.h"

/*
 *  高分解能タイマのタイマ周期
 *
 *  タイマ周期が2^32の場合には，このマクロを定義しない．
 */
#define TCYC_HRTCNT		(65535)

/*
 *  高分解能タイマのカウント値の進み幅
 */
#define TSTEP_HRTCNT	(1U)

/*
 *  チップ依存部で使用できる割込み要求ラインの割込み属性
 */
#define TA_POSEDGE    ( 0x04 )
#define TA_NEGEDGE    ( 0x08 )


/*
 *  割込み機能の制御情報
 */

typedef struct
{
	volatile __far uint8_t* address;		/* アドレス */
	uint8_t				bitmask;			/* ビット位置 */
} RL78G13_INTREG_INFO;

typedef struct
{
	RL78G13_INTREG_INFO request;			/* 要求レジスタ */
	RL78G13_INTREG_INFO mask;				/* マスクレジスタ */
	RL78G13_INTREG_INFO pri1;				/* 優先度1 */
	RL78G13_INTREG_INFO pri2;				/* 優先度2 */
	RL78G13_INTREG_INFO extint_posedge;		/* 外部割り込み立ち上がりエッジ設定 */
	RL78G13_INTREG_INFO extint_negedge;	/* 外部割り込み立ち下がりエッジ設定 */
} RL78G13_INTCTL_INFO;


/* 割込み制御情報テーブル */
extern RL78G13_INTCTL_INFO const intctl_reg_table[RL78_G13_INTNO_MAX+1];


/* 割込みハンドラが定義済みかを格納する配列 */
extern const uint32_t _kernel_bitpat_cfgint[];

/*
 *  チップ依存部の初期化
 */
 extern void chip_initialize(void);

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，falseを返す．
 */
Inline void
disable_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far mask_reg = &intctl_reg_table[intno].mask;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(mask_reg->address) &= ~(mask_reg->bitmask);
}

/*
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline void
enable_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far mask_reg = &intctl_reg_table[intno].mask;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(mask_reg->address) |= mask_reg->bitmask;
}

/*
 *  割込み要求のクリア
 */
Inline void
clear_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far request_reg = &intctl_reg_table[intno].request;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(request_reg->address) &= ~(request_reg->bitmask);
}

/*
 *  割込み要求のチェック
 */
Inline bool_t
probe_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far request_reg = &intctl_reg_table[intno].request;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	return ((*(request_reg->address) &request_reg->bitmask) != 0);
}


/*
 *  割込み要求がクリアできる状態か？
 */
Inline bool_t check_intno_clear(INTNO intno)
{
	/* 常にクリアは可能 */
	return true;
}

/*
 * 割込み要求ラインが設定されているかのチェック
 */
Inline bool_t check_intno_cfg(INTNO intno)
{
	return (_kernel_bitpat_cfgint[(intno >> 5)] & (1U << (intno & 0x01FU))) != 0U;
}


/*
 *  割込みハンドラの設定
 *
 *  ベクトル番号inhnoの割込みハンドラの出入口処理の番地をint_entryに
 *  設定する．
 */
Inline void
define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  割込み要求ライン属性の設定
 */
Inline void
config_int(INTNO intno, ATR intatr, PRI intpri)
{
	const RL78G13_INTREG_INFO * __far pri_reg1 = &intctl_reg_table[intno].pri1;
	const RL78G13_INTREG_INFO * __far pri_reg2 = &intctl_reg_table[intno].pri2;
	const RL78G13_INTREG_INFO * __far ext_pos_reg = &intctl_reg_table[intno].extint_posedge;
	const RL78G13_INTREG_INFO * __far ext_neg_reg = &intctl_reg_table[intno].extint_negedge;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	/* 割込み優先度 */
	if(intpri == 1)
	{
		*(pri_reg1->address) |= pri_reg1->bitmask;
		*(pri_reg2->address) &= ~(pri_reg2->bitmask);
	}
	else if(intpri == 2)
	{
		*(pri_reg1->address) &= ~(pri_reg1->bitmask);
		*(pri_reg2->address) |= pri_reg2->bitmask;
	}
	else if(intpri == 3)
	{
		*(pri_reg1->address) |= pri_reg1->bitmask;
		*(pri_reg2->address) |= pri_reg2->bitmask;
	}
	else	/* 1 ～ 3以外 */
	{
		*(pri_reg1->address) &= ~(pri_reg1->bitmask);
		*(pri_reg2->address) &= ~(pri_reg2->bitmask);
	}
	
	/* 割込みエッジ */
	if((intatr & TA_POSEDGE) && ext_pos_reg)
	{
		*(ext_pos_reg->address) |= ext_pos_reg->bitmask;
	}
	if((intatr & TA_NEGEDGE) && ext_neg_reg)
	{
		*(ext_neg_reg->address) |= ext_neg_reg->bitmask;
	}
	
	
	/* 割込み許可 */
	if(intatr & TA_ENAINT)
	{
		enable_int(intno);
	}
	
}

/*
 *  割込みハンドラの入口で必要なIRC操作
 */
Inline void
i_begin_int(INTNO intno)
{
	/* 何もしない，割込み要求は自動クリア */
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 */
Inline void
i_end_int(INTNO intno)
{
	/* 何もしない */
}



#endif /* TOPPERS_CHIP_KERNEL_IMPL_H */
