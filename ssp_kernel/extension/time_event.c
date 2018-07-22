/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2016 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  $Id: time_event.c 532 2016-01-15 14:48:04Z ertl-hiro $
 */

/*
 *		タイムイベント管理モジュール
 */

#include "kernel_impl.h"
#include "time_event.h"
#include "queue.h"

/*
 *  TSTEP_HRTCNTの範囲チェック
 */
#if TSTEP_HRTCNT > 4000U
#error TSTEP_HRTCNT is too large.
#endif /* TSTEP_HRTCNT > 4000U */

/*
 *  HRTCNT_BOUNDの範囲チェック
 */
#if HRTCNT_BOUND >= 4294000000U
#error HRTCNT_BOUND is too large.
#endif /* HRTCNT_BOUND >= 4294000000U */

#ifdef TCYC_HRTCNT
#if HRTCNT_BOUND >= TCYC_HRTCNT
#error HRTCNT_BOUND is too large.
#endif /* HRTCNT_BOUND >= TCYC_HRTCNT */
#endif /* TCYC_HRTCNT */

/*
 *  タイムイベントキューのキューヘッダ
 *
 *  タイムイベントキューブロックの終端に確保する．
 */
#define TMEVT_HEAD()	(tmevt_queue[tnum_tmevt_queue])
#define TMEVT_NULL		((QUEIDX)tnum_tmevt_queue)

/*
 *  タイムイベントヒープ中の先頭のノードの情報
 */
#define top_evttim		(0)
										/* 先頭のタイムイベントの発生時刻 */

/*
 *  イベント時刻の前後関係の判定［ASPD1009］
 *
 *  イベント時刻は，boundary_evttimからの相対値で比較する．すなわち，
 *  boundary_evttimを最も早い時刻，boundary_evttim−1が最も遅い時刻とみ
 *  なして比較する．
 */
#define EVTTIM_ADVANCE(t)	((t) - boundary_evttim)
#define EVTTIM_LT(t1, t2)	(EVTTIM_ADVANCE(t1) < EVTTIM_ADVANCE(t2))
#define EVTTIM_LE(t1, t2)	(EVTTIM_ADVANCE(t1) <= EVTTIM_ADVANCE(t2))

#ifdef TOPPERS_tmeini

/*
 *  境界イベント時刻［ASPD1008］
 */
EVTTIM	boundary_evttim;

/*
 *  最後に現在時刻を算出した時点でのイベント時刻［ASPD1012］
 */
EVTTIM	current_evttim;

/*
 *  最後に現在時刻を算出した時点での高分解能タイマのカウント値［ASPD1012］
 */
HRTCNT	current_hrtcnt;

/*
 *  最も進んでいた時のイベント時刻［ASPD1041］
 */
EVTTIM	monotonic_evttim;

/*
 *  システム時刻のオフセット［ASPD1043］
 */
SYSTIM	systim_offset;

/*
 *  高分解能タイマ割込みの処理中であることを示すフラグ［ASPD1032］
 */
bool_t	in_signal_time;

/*
 *  タイムイベント管理モジュールの初期化［ASPD1061］
 */
void
initialize_time_event(void)
{
	current_evttim = 0U;							/*［ASPD1047］*/
	boundary_evttim = current_evttim - BOUNDARY_MARGIN;
													/*［ASPD1048］*/
	monotonic_evttim = 0U;							/*［ASPD1046］*/
	systim_offset = 0U;								/*［ASPD1044］*/
	in_signal_time = false;							/*［ASPD1033］*/
	
	/* タイムイベントキューの初期化 */
	queue_initialize(&TMEVT_HEAD() , (QUEIDX)tnum_tmevt_queue);	
}

#endif /* TOPPERS_tmeini */


/*
 *  現在のイベント時刻の更新
 */
#ifdef TOPPERS_tmecur

void
update_current_evttim(void)
{
	HRTCNT	new_hrtcnt, hrtcnt_advance;
	EVTTIM	previous_evttim;

	new_hrtcnt = target_hrt_get_current();			/*［ASPD1013］*/
	hrtcnt_advance = new_hrtcnt - current_hrtcnt;	/*［ASPD1014］*/
#ifdef TCYC_HRTCNT
	if (new_hrtcnt < current_hrtcnt) {
		hrtcnt_advance += TCYC_HRTCNT;
	}
#endif /* TCYC_HRTCNT */

	previous_evttim = current_evttim;
	current_evttim += (EVTTIM) hrtcnt_advance;		/*［ASPD1015］*/
	current_hrtcnt = new_hrtcnt;					/*［ASPD1016］*/
	boundary_evttim = current_evttim - BOUNDARY_MARGIN;	/*［ASPD1011］*/

	if (monotonic_evttim - previous_evttim < (EVTTIM) hrtcnt_advance) {
#ifdef UINT64_MAX
		if (current_evttim < monotonic_evttim) {
			systim_offset += 1LLU << 32;			/*［ASPD1045］*/
		}
#endif /* UINT64_MAX */
		monotonic_evttim = current_evttim;			/*［ASPD1042］*/
	}
}

#endif /* TOPPERS_tmecur */

/*
 *  現在のイベント時刻を遅い方に丸めたイベント時刻の算出［ASPD1027］
 *
 *  現在のイベント時刻を更新した後に呼ぶことを想定している．
 */
Inline EVTTIM
calc_current_evttim_ub(void)
{
	return(current_evttim + ((EVTTIM) TSTEP_HRTCNT));
}

/*
 *  高分解能タイマ割込みの発生タイミングの設定
 */
#ifdef TOPPERS_tmeset

void
set_hrt_event(void)
{
	HRTCNT	hrtcnt;

	if (!EVTTIM_LE(HRTCNT_BOUND, top_evttim)) {
		target_hrt_set_event(HRTCNT_BOUND);			/*［ASPD1007］*/
	}
	else if (EVTTIM_LE(top_evttim, current_evttim)) {
		target_hrt_raise_event();					/*［ASPD1017］*/
	}
	else {
		hrtcnt = (HRTCNT)(top_evttim - current_evttim);
		if (hrtcnt > HRTCNT_BOUND) {
			target_hrt_set_event(HRTCNT_BOUND);		/*［ASPD1006］*/
		}
		else {
			target_hrt_set_event(hrtcnt);			/*［ASPD1002］*/
		}
	}
}

#endif /* TOPPERS_tmeset */

/*
 *  タイムイベントブロックのキューへの挿入
 */
#ifdef TOPPERS_tmereg

void
time_event_register(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg)
{
	QUEIDX pos = TMEVT_HEAD().next;
	
	/* 挿入位置を検索 */
	while((pos != TMEVT_NULL)
			&& (EVTTIM_LE(tmevt_time[pos] , evttim))) {
		pos = tmevt_queue[pos].next;
	}
	
	/* キューに挿入 */
	queue_insert_prev(&(tmevt_queue[0]) , pos , (QUEIDX)tmevtid);
	tmevt_callback[tmevtid] = (CBACK)callback;
	tmevt_arg[tmevtid] = arg;
	tmevt_time[tmevtid] = evttim;
}

#endif /* TOPPERS_tmereg */


/*
 *  相対時間指定によるタイムイベントの登録
 *  
 */
#ifdef TOPPERS_tmeenq

void
time_event_enqueue(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg)
{
	RELTIM event_exec_time;
	
	/*
	 *  現在のイベント時刻とタイムイベントの発生時刻を求める［ASPD1026］．
	 */
	update_current_evttim();
	event_exec_time = calc_current_evttim_ub() + evttim;
	
	/* タイムイベントキューへの登録 */
	time_event_register((QUEIDX)tmevtid , event_exec_time , callback, arg);
	
	/*
	 *  高分解能タイマ割込みの発生タイミングを設定する［ASPD1031］
	 *  ［ASPD1034］．
	 */
	if (!in_signal_time 
	 && tmevtid == TMEVT_HEAD().next) {
		set_hrt_event();
	}
}

#endif /* TOPPERS_tmeenq */

/*
 *  タイムイベントの登録解除
 */
#ifdef TOPPERS_tmedeq

void
time_event_dequeue(ID tmevtid)
{
	QUEIDX next_index;

	/*
	 *  タイムイベントブロックをヒープから削除する［ASPD1039］．
	 */
	next_index = queue_delete_next(&(tmevt_queue[0]) , (QUEIDX)tmevtid);

	/*
	 *  高分解能タイマ割込みの発生タイミングを設定する［ASPD1040］．
	 */
	if (!in_signal_time && next_index != TMEVT_NULL) {
		update_current_evttim();
		set_hrt_event();
	}
}

#endif /* TOPPERS_tmedeq */

/*
 *  高分解能タイマ割込みの処理
 */
#ifdef TOPPERS_sig_tim

void
signal_time(void)
{
	bool_t	callflag;
	QUEIDX pos = TMEVT_HEAD().next , evtid;

	assert(sense_context());
	assert(!sense_lock());

	lock_cpu();
	in_signal_time = true;							/*［ASPD1033］*/

	do {
		/*
		 *  コールバック関数を呼び出さなければループを抜ける［ASPD1020］．
		 */
		callflag = false;

		/*
		 *  現在のイベント時刻を求める［ASPD1022］．
		 */
		update_current_evttim();

		/*
		 *  発生時刻がcurrent_evttim以前のタイムイベントがあれば，タイ
		 *  ムイベントヒープから削除し，コールバック関数を呼び出す
		 *  ［ASPD1018］［ASPD1019］．
		 */
		
		while((pos != TMEVT_NULL)
				&& EVTTIM_LT(tmevt_time[pos] , current_evttim)) {
			(void)queue_delete_next(&(tmevt_queue[0]) , pos);
			evtid = pos;
			pos = tmevt_queue[pos].next;
			(*tmevt_callback[evtid])(tmevt_arg[evtid]);
			callflag = true;
		}		
	} while (callflag);								/*［ASPD1020］*/

	/*
	 *  高分解能タイマ割込みの発生タイミングを設定する［ASPD1025］．
	 */
	set_hrt_event();

	in_signal_time = false;							/*［ASPD1033］*/
	unlock_cpu();
}

#endif /* TOPPERS_sigtim */
