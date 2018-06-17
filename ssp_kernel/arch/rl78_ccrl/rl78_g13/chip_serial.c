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
 *  シリアルI/Oデバイス（SIO）ドライバ(RL78/G13用)
 */

#include "kernel_impl.h"
#include "target_serial.h"
#include "chip_serial.h"
#include <sil.h>


#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

#define PER0_ADDR			((uint8_t __far *)0xF00F0)	/* 周辺イネーブル・レジスタ 0 */
#define NFEN0_ADDR			((uint16_t __far *)0xF0070)	/* ノイズ・フィルタ許可レジスタ 0 */

/*
 *  UARTとSAUのユニット，チャネルの関係は以下の通り
 *
 *  UART0 : SAU0 , 送信:チャネル0 , 受信:チャネル1
 *  UART1 : SAU0 , 送信:チャネル2 , 受信:チャネル3
 *  UART2 : SAU1 , 送信:チャネル0 , 受信:チャネル1
 *  UART3 : SAU1 , 送信:チャネル2 , 受信:チャネル3
 */
/*
 *  UARTチャネル毎のレジスタアドレス定義
 *
 *  SAUのレジスタはSFR領域上に点在しており，単純な演算で
 *  レジスタアドレスを算出できないことから，テーブルから読み出す方式を採用した
 */
const SAU_REGADDRS sau_register_address_table[TNUM_UART_CH] =
{
	/* ID : 1 */
	{
		(__far uint16_t *)0xF0110 ,		/* SMR_tx */
		(__far uint16_t *)0xF0112 ,		/* SMR_rx */
		(__far uint16_t *)0xF0118 ,		/* SCR_tx */
		(__far uint16_t *)0xF011A ,		/* SCR_rx */
		(__far uint16_t *)0xFFF10 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF12 ,		/* SDR_rx */
		(__far uint16_t *)0xF0108 ,		/* SIR */
		(__far uint16_t *)0xF0100 ,		/* SSR_tx */
		(__far uint16_t *)0xF0102 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0126 ,		/* SPS */
		(__far uint16_t *)0xF0122 ,		/* SS  */
		(__far uint16_t *)0xF0124 ,		/* ST  */
		(__far uint16_t *)0xF012A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 2 */
	{
		(__far uint16_t *)0xF0114 ,		/* SMR_tx */
		(__far uint16_t *)0xF0116 ,		/* SMR_rx */
		(__far uint16_t *)0xF011C ,		/* SCR_tx */
		(__far uint16_t *)0xF011E ,		/* SCR_rx */
		(__far uint16_t *)0xFFF44 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF46 ,		/* SDR_rx */
		(__far uint16_t *)0xF010C ,		/* SIR */
		(__far uint16_t *)0xF0104 ,		/* SSR_tx */
		(__far uint16_t *)0xF0106 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0126 ,		/* SPS */
		(__far uint16_t *)0xF0122 ,		/* SS  */
		(__far uint16_t *)0xF0124 ,		/* ST  */
		(__far uint16_t *)0xF012A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 3 */
	{
		(__far uint16_t *)0xF0150 ,		/* SMR_tx */
		(__far uint16_t *)0xF0152 ,		/* SMR_rx */
		(__far uint16_t *)0xF0158 ,		/* SCR_tx */
		(__far uint16_t *)0xF015A ,		/* SCR_rx */
		(__far uint16_t *)0xFFF48 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF4A ,		/* SDR_rx */
		(__far uint16_t *)0xF0148 ,		/* SIR */
		(__far uint16_t *)0xF0140 ,		/* SSR_tx */
		(__far uint16_t *)0xF0142 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0166 ,		/* SPS */
		(__far uint16_t *)0xF0162 ,		/* SS  */
		(__far uint16_t *)0xF0164 ,		/* ST  */
		(__far uint16_t *)0xF016A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	} ,
	/* ID : 4 */
	{
		(__far uint16_t *)0xF0154 ,		/* SMR_tx */
		(__far uint16_t *)0xF0156 ,		/* SMR_rx */
		(__far uint16_t *)0xF015C ,		/* SCR_tx */
		(__far uint16_t *)0xF015E ,		/* SCR_rx */
		(__far uint16_t *)0xFFF14 ,		/* SDR_tx */
		(__far uint16_t *)0xFFF16 ,		/* SDR_rx */
		(__far uint16_t *)0xF014C ,		/* SIR */
		(__far uint16_t *)0xF0144 ,		/* SSR_tx */
		(__far uint16_t *)0xF0146 ,		/* SSR_rx */
		(__far uint8_t  *)0xF0166 ,		/* SPS */
		(__far uint16_t *)0xF0162 ,		/* SS  */
		(__far uint16_t *)0xF0164 ,		/* ST  */
		(__far uint16_t *)0xF016A ,		/* SOE */
		(__far uint16_t *)0xF0128  		/* SO */
	}
};

const uint8_t bitpos_of_ch_tx[TNUM_UART_CH] = { 0U , 2U , 0U , 2U };
const uint8_t bitpos_of_ch_rx[TNUM_UART_CH] = { 1U , 3U , 1U , 3U };
/*
 * シリアルI/Oポート管理ブロックエリア
 */
SIOPCB siopcb_table[TNUM_PORT];

/*
 * チャンネル初期化済みフラグ
 *
 * bss初期化で全てfalseになることを想定している
 */
bool_t sio_initialized[TNUM_PORT - 1];


Inline bool_t  sio_putready(SIOPCB* siopcb)
{
	const uint16_t ssr_bfe_bit = (0x1U << 5U);
	
	return (sil_reh_mem(siopcb->regaddrs->SSR_tx) & ssr_bfe_bit) == 0 ? true : false;
}

Inline bool_t sio_getready(SIOPCB* siopcb)
{
	const uint16_t ssr_bfe_bit = (0x1U << 5U);
	
	return (sil_reh_mem(siopcb->regaddrs->SSR_rx) & ssr_bfe_bit) == 0 ? true : false;
}

/*
 *  UARTの初期化
 *
 *  低レベル出力の初期化でターゲット依存部が使用できるように外部公開する
 */
void sau_init(uint_t ch)
{
	const SAU_REGADDRS *sau_regaddrs = &sau_register_address_table[ch];
	
	/* 初期化済みの場合はすぐにリターン */
	if(sio_initialized[ch] == true)
	{
		return ;
	}
	
	/* SAUの有効化 */
	sil_wrb_mem( PER0_ADDR, sil_reb_mem( PER0_ADDR ) | 0x04U );
	
	/* SAUの動作停止(SCR,SOE,ST) */
	sil_wrh_mem(sau_regaddrs->ST , ~(0x0005U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) & ~(0x0005U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);

	/* 使用クロック設定 */
	sil_wrb_mem(sau_regaddrs->SPS ,
		sil_reb_mem(sau_regaddrs->SPS) & ~(0x0F << SELECT_SPSm * 4) | (PRS_VALUE << SELECT_SPSm * 4));
	
	/* 送信側チャネルモード設定 */
	sil_wrh_mem(sau_regaddrs->SMR_tx ,
		  (1U << 0U)           /* MD0   : バッファ空きで割込み信号発生  */
		| (1U << 1U)           /* MD1,2 : UARTモード */
		| (0U << 6U)           /* SIS   : レベル反転しない */
		| (0U << 8U)           /* STS   : ソフトウェアトリガ */
		| (0U << 14U)          /* CCS   : 転送クロックはCKSビットで選択 */
		| (SIO_CLOCK << 15U)   /* CKS  :  */
		);	
		
	/* 送信側通信動作設定 */
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		  (1U << 7U)           /* DIR   : MSBファースト */
		| (1U << 4U)           /* SLC   : ストップビットなし */
		| (1U << 2U)           /* Reserved */
		| (3U << 0U)           /* DLS   : 8bit長 */
		);
	
	/* 受信側チャネルモード設定 */
	sil_wrh_mem(sau_regaddrs->SMR_rx ,
		  (0U << 0U)           /* MD0   : 転送完了で割込み信号発生  */
		| (1U << 1U)           /* MD1,2 : UARTモード */
		| (0U << 6U)           /* SIS   : レベル反転しない */
		| (0U << 8U)           /* STS   : ソフトウェアトリガ */
		| (0U << 14U)          /* CCS   : 転送クロックはCKSビットで選択 */
		| (SIO_CLOCK << 15U)   /* CKS   :  */
		);

	/* 受信側通信動作設定 */
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		  (1U << 7U)           /* DIR   : MSBファースト */
		| (1U << 4U)           /* SLC   : ストップビットなし */
		| (1U << 2U)           /* Reserved */
		| (3U << 0U)           /* DLS   : 8bit長 */
		);

	/* 受信フィルタ設定 */
	sil_wrh_mem(NFEN0_ADDR, (1U << (ch * 2U)));
	
	/* 通信速度設定，上位8bitのみを設定 */
	sil_wrb_mem((__far  uint8_t*)((uint32_t)sau_regaddrs->SDR_tx + 1) , COMM_CLOCK_VALUE << 1);
	sil_wrb_mem((__far  uint8_t*)((uint32_t)sau_regaddrs->SDR_rx + 1) , COMM_CLOCK_VALUE << 1);
	
	
	/* SAUの動作開始 */
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_tx) | 0x8000U);
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) | 0x4000U);
	sil_wrh_mem(sau_regaddrs->SO , 
		sil_reh_mem(sau_regaddrs->SO) | (1U << ch));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) | (0x0005U << bitpos_of_ch_tx[ch]));
	sil_wrh_mem(sau_regaddrs->SS , (0x0003U << bitpos_of_ch_tx[ch]));
	
	/* 割込み許可 */
	clr_int(INTNO_SIO_TX);
	clr_int(INTNO_SIO_RX);
	ena_int(INTNO_SIO_TX);
	ena_int(INTNO_SIO_RX);
	
	sio_initialized[ch] = true;
}



/*
 *  ターゲットのシリアル初期化
 */
void sau_term(uint_t ch)
{
	const SAU_REGADDRS *sau_regaddrs = &sau_register_address_table[ch];

	/* SAUの無効化(SCR,SOE,ST) */
	sil_wrh_mem(sau_regaddrs->ST , ~(0x0003U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SOE , 
		sil_reh_mem(sau_regaddrs->SOE) & ~(0x0003U << ((ch % 2) * 2)));
	sil_wrh_mem(sau_regaddrs->SCR_tx , 
		sil_reh_mem(sau_regaddrs->SCR_tx) & ~0xC000U);	/* 送信禁止 */
	sil_wrh_mem(sau_regaddrs->SCR_rx , 
		sil_reh_mem(sau_regaddrs->SCR_rx) & ~0xC000U);	/* 受信禁止 */
	
	sio_initialized[ch] = false;	
}

/*
 *  ターゲットのシリアル終了
 */
void target_usart_term(ID uart_id)
{
	/* USARTの無効化 */
	sau_term(uart_id);
	
	/* 割込み禁止 */
	(void)dis_int(INTNO_SIO_TX);
	(void)dis_int(INTNO_SIO_RX);
	/* 割込み要因クリア */
	(void)clr_int(INTNO_SIO_TX);
	(void)clr_int(INTNO_SIO_RX);

}

/*
 *  SIO初期化
 */
void sio_initialize(intptr_t exinf)
{
	int i;

	for (i = 0; i < TNUM_PORT; i++) {
		siopcb_table[i].port = i;
		siopcb_table[i].regaddrs = &sau_register_address_table[i];
		siopcb_table[i].exinf = 0;
	}
}

/*
 *  シリアルオープン
 */
SIOPCB *sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB* siopcb;

	if (siopid > TNUM_PORT) {
		return NULL;
	}
	
	siopcb = GET_SIOPCB(siopid);
	siopcb->exinf = exinf;
	siopcb->port = siopid;

	sau_init(INDEX_PORT(siopid));
	
	return siopcb;
}

/*
 *  シリアルクローズ
 */
void sio_cls_por(SIOPCB *p_siopcb)
{
	sau_term(INDEX_PORT(p_siopcb->port));
}

/*
 *  割込みハンドラ
 */
void sio_isr_tx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_putready(siopcb)) {
		sio_irdy_snd(siopcb->exinf);
	}
}

void sio_isr_rx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);

	if (sio_getready(siopcb)) {
		sio_irdy_rcv(siopcb->exinf);
	}
}

/*
 *  1文字送信
 */
bool_t sio_snd_chr(SIOPCB *siopcb, char c)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	bool_t ret = false;
	
	if (sio_putready(siopcb)) {
		sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
		ret = true;
	}

	return ret;
}

/*
 *  1文字受信
 */
int_t sio_rcv_chr(SIOPCB *siopcb)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	int_t c = -1;

	if (sio_getready(siopcb)) {
		c = (int)sil_reb_mem((uint8_t __far *)sau_regaddrs->SDR_rx);
	}

	return c;
}

/*
 *  コールバックの許可
 */
void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		/* 送信チャネルを動作許可 */
		//sil_wrh_mem(sau_regaddrs->SS , 1U << bitpos_of_ch_tx[INDEX_PORT(siopcb->port)]);	
		break;
	case SIO_RDY_RCV:
		/* 受信チャネルを動作許可 */
		//sil_wrh_mem(sau_regaddrs->SS , 1U << bitpos_of_ch_rx[INDEX_PORT(siopcb->port)]);
		break;
	default:
		break;
	}
}

/* 
 *  コールバックの禁止
 */
void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	//const SAU_REGADDRS *sau_regaddrs = siopcb->regaddrs;
	
	switch (cbrtn) {
	case SIO_RDY_SND:
		/* 送信チャネルを動作禁止 */
		//sil_wrh_mem(sau_regaddrs->ST , 1U << bitpos_of_ch_tx[INDEX_PORT(siopcb->port)]);	
		break;
	case SIO_RDY_RCV:
		/* 受信チャネルを動作禁止 */
		//sil_wrh_mem(sau_regaddrs->ST , 1U << bitpos_of_ch_rx[INDEX_PORT(siopcb->port)]);
		break;
	default:
		break;
	}
}

/*
 *  1文字出力（ポーリングでの出力）
 */
void sio_pol_snd_chr(char c, ID siopid)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb_table[INDEX_PORT(siopid)].regaddrs;
	
	while((sil_reh_mem(sau_regaddrs->SSR_tx) & (0x1U << 5)) != 0 )
		;
	
	sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
}

/*
 *  低レベル1文字出力
 */
void sau_log_output(uint_t ch, char c)
{
	const SAU_REGADDRS *sau_regaddrs = siopcb_table[ch].regaddrs;
	
	while((sil_reh_mem(sau_regaddrs->SSR_tx) & (0x1U << 5)) != 0 )
		;
	
	sil_wrb_mem((uint8_t __far *)sau_regaddrs->SDR_tx, (uint8_t)c);
}
 
