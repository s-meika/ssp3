/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2017 by Meika Sugimoto
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
 * タイムイベント通知
 */

#ifndef TOPPERS_TIME_EVENT_NOTIFY_H
#define TOPPERS_TIME_EVENT_NOTIFY_H

#include "kernel_impl.h"

/*
 * タイムイベント通知処理
 */


/* タイムイベントハンドラによる通知 */
Inline void tmevt_nfy_call_handler(TMEHDR tmevt_hdr, intptr_t exinf)
{
	(*tmevt_hdr)(exinf);
}

/* 変数の設定 */
Inline void tmevt_nfy_setvar(intptr_t *addr, intptr_t value)
{
	*addr = value;
}

/* 変数のインクリメント */
Inline void tmevt_nfy_incvar(intptr_t *addr)
{
	(void)loc_cpu();
	(*addr) += 1;
	(void)unl_cpu();
}

/* タスクの起動 */
Inline ER tmevt_nfy_acttsk(ID tskid)
{
	return act_tsk(tskid);
}

/* イベントフラグのセット */
Inline ER tmevt_nfy_setflg(ID flgid, FLGPTN flgptn)
{
	return set_flg(flgid, flgptn);
}

/* データキューへの送信 */
Inline ER tmevt_nfy_snddtq(ID dtqid, intptr_t data)
{
	return psnd_dtq(dtqid, data);
}



#endif /* TOPPERS_TIME_EVENT_NOTIFY_H */
