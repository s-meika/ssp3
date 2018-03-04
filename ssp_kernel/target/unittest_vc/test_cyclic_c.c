/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
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
 *  TOPPERS/SSP単体テスト用ソースファイル(cyclic.h/c用)
 */


#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"
#include "cyclic.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_cyclic(void)
{
	/* Pre Condition */
	cyccb_evttim[0] = 1;
	cyccb_cycact = ~0;

	/* --- */
	initialize_cyclic();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(cyccb_evttim[0] , cycinib_cycphs[0]);
	CU_ASSERT_EQUAL(cyccb_evttim[1] , 0);
	CU_ASSERT_EQUAL(cyccb_cycact , cycinib_cycact);
}

void test_sta_cyc(void)
{
	ER ercd;

	/* タイムイベントハンドラと周期ハンドラの初期化 */
	initialize_time_event();
	initialize_cyclic();

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	/* 動作開始済みの周期ハンドラに対する開始 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(cyccb_cycact & (1 << (1 - 1)));

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* 動作開始していない周期ハンドラに対する開始 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(cyccb_cycact & (1 << (2 - 1)));
}

void test_stp_cyc(void)
{
	ER ercd;

	/* タイムイベントハンドラと周期ハンドラの初期化 */
	initialize_time_event();
	initialize_cyclic();

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	/* 動作開始済みの周期ハンドラに対する開始 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(cyccb_cycact & (1 << (1 - 1)));

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* 動作開始していない周期ハンドラに対する開始 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(cyccb_cycact & (1 << (2 - 1)));
}

void test_call_cychdr(void)
{
	ER ercd;
	int i;

	/* タイムイベントハンドラと周期ハンドラの初期化 */
	initialize_time_event();
	initialize_cyclic();
	
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	ercd = sta_cyc(2);
	
	/* --- */
	for(i = 0 ; i < 100 ; i++)
	{
		if(i == 43)
		{
			ercd = stp_cyc(2);
			CU_ASSERT_EQUAL(ercd , E_OK);
		}
		signal_time();
	}

	/* --- */

	/* Post Condition */
	
}

extern EVTTIM	current_time;

void cychdr1(void)
{
	int call_timing[] =
	{ 1 , 11 , 21 , 31 , 41 , 51 , 61 , 71 , 81 , 91 };
	static int step = 0;

	CU_ASSERT_EQUAL(current_time-1 , call_timing[step]);
	step = (step + 1) % (sizeof(call_timing)/sizeof(call_timing[0]));
}

void cychdr2(void)
{
	int call_timing[] =
	{ 2 , 7 , 12 , 17 , 22 , 27 , 32 , 37 , 42 };
	static int step = 0;
	
	CU_ASSERT_EQUAL(current_time-1 , call_timing[step]);
	step = (step + 1) % (sizeof(call_timing)/sizeof(call_timing[0]));

	if(step == 7)
	{
		i_lock_cpu();
	}
}
