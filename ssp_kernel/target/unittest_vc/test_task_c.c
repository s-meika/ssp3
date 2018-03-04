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
 *  TOPPERS/SSP単体テスト用ソースファイル(task.c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "task.h"

#include <CUnit.h>
#include <Console.h>


/* 参照変数 */
extern uint_t runtsk_ipri;
extern volatile uint_t	ready_primap;
extern bool_t	reqflg;
extern bool_t	disdsp;
extern const uint_t init_rdypmap;

void test_initialize_task(void)
{
	/* Pre Condition */
	/* variable reset */
	ready_primap = 0xffffu;
	actque_bitmap = 0xffffu;
	runtsk_ipri = 0u;
	disdsp = true;
	
	/* --- */
	initialize_task();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , init_rdypmap);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	CU_ASSERT_EQUAL(disdsp , false);

}

void test_search_schedtsk(void)
{
	int i , runtsk;
	
	for(i = 1 ; i < 256 ; i++)
	{
		/* Pre Condition */
		ready_primap = i;
		
		/* --- */
		runtsk = search_schedtsk();
		/* --- */
		
		/* Post Condition */
		if((i & 0x01) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 0);
		}
		else if((i & 0x02) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 1);
		}
		else if((i & 0x04) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 2);
		}
		else if((i & 0x08) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 3);
		}
		else if((i & 0x10) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 4);
		}
		else if((i & 0x20) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 5);
		}
		else if((i & 0x40) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 6);
		}
		else if((i & 0x80) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 7);
		}
		else
		{
			CU_ASSERT(0 != 1);
		}
	}
}

void test_test_dormant(void)
{
	int i , j;
	bool_t result;

	for(i = 0 ; i < sizeof(ready_primap) * 8 ; i++)
	{
		/* Pre Condition */
		ready_primap = 1u << i;
		
		/* セットされたビットならばfalseになることをチェック */
		/* --- */
		result = test_dormant(i);
		/* --- */

		/* Post Condition */
		CU_ASSERT_EQUAL(result , false);

		/* セットされていないビットならばtrueになることをチェック */
		for(j = 0 ; j < i ; j++)
		{
			/* --- */
			result = test_dormant(j);
			/* --- */

			/* Post Condition */
			CU_ASSERT_EQUAL(result , true);
		}
		for(j = i + 1 ; j < sizeof(ready_primap) * 8 ; j++)
		{
			/* --- */
			result = test_dormant(j);
			/* --- */

			/* Post Condition */
			CU_ASSERT_EQUAL(result , true);
		}
	}
}

void test_make_active(void)
{
	bool_t result;

	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	disdsp = true;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(4);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0010u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(5);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0020u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);
}

void test_run_task(void)
{

	initialize_task();

	/* 複数タスクを連続実行するパターン */
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(3 - 1);
	(void)make_active(4 - 1);

	/* --- */
	run_task(3 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* 複数タスクのうち優先度が高いタスクのみを実行するパターン */
	/* Pre Condition */
	ready_primap = 0;
	runtsk_curpri = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(2 - 1);
	(void)make_active(4 - 1);

	/* --- */
	run_task(2 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0008);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* 単一タスクを実行するパターン */
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(4 - 1);
	
	/* --- */
	run_task(4 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* 単一タスクで起動要求キューイングにて再実行するパターン */
	/* Pre Condition */
	ready_primap = 0;
	runtsk_curpri = 5;
	actque_bitmap = 0x0008u;
	(void)make_active(4 - 1);
	
	/* --- */
	run_task(4 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);



}

void test_dispatcher(void)
{
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(3 - 1);
	
	/* --- */
	dispatcher();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

}

