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
 *  TOPPERS/SSP単体テスト用ソースファイル(time_event.h/c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"

#include <CUnit.h>
#include <Console.h>

static void callback1(uintptr_t arg);
static void callback2(uintptr_t arg);
static void callback3(uintptr_t arg);

void test_initialize_time_event(void)
{
	/* Pre Condition */
	
	/* --- */
	initialize_time_event();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(tmevt_queue[tnum_tmevt_queue].next , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_queue[tnum_tmevt_queue].prev , tnum_tmevt_queue);
}

void test_time_event_enqueue(void)
{
	uint_t tmevtid;
	const int queue_header = tnum_tmevt_queue;

	/* Pre Condition */
	initialize_time_event();
	
	/* --- */
	tmevtid = 0;
	time_event_enqueue(tmevtid , 10 , callback1 , 1);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 10 | xx , xx | xx , xx | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 0 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , tmevtid);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , tmevtid);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 10);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 1);
	

	/* Pre Condition */
	
	/* --- */
	tmevtid = 2;
	time_event_enqueue(tmevtid , 50 , callback2 , 2);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 2 | xx , xx | 0 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 2 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , queue_header);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 0);
	CU_ASSERT_EQUAL(tmevt_queue[0].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[0].prev , queue_header);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 50);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 2);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 1;
	time_event_enqueue(tmevtid , 40 , callback1 , 3);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 1 | 0 , 2 | 1 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 2 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[0].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[2].prev , 1);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 40);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 3);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 8;
	time_event_enqueue(tmevtid , 5 , callback2 , 1000);

	/* --- */

	/* Post Condition */
	/*
	 *  | 8 , 1 | 0 , 2 | 1 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[0].prev , 8);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 10);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 8);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 5);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 1000);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 5;
	time_event_enqueue(tmevtid , 40 , callback2 , 155);

	/* --- */

	/* Post Condition */
	/*
	 *  | 8 , 1 | 0 , 5 | 5 , 10 | xx , xx | xx , xx |
	 *    1 , 2 | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[1].next , 5);
	CU_ASSERT_EQUAL(tmevt_queue[2].prev , 5);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 1);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 8);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 40);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 155);
}

void test_time_event_dequeue(void)
{
	uint_t tmevtid;
	const int queue_header = tnum_tmevt_queue;
	
	/* Pre Condition */
	/*
	 *  10(head) -> 8 -> 0 -> 1 -> 5 -> 2
	 */
	/* --- */
	tmevtid = 0;

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 0 , 5 | 5 , 10 | xx , xx | xx , xx |
	 *    1 , 2 | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[8].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[1].prev , 8);

	/*
	 *  10(head) -> 8 -> 1 -> 5 -> 2
	 */
	/* --- */
	tmevtid = 2;
	/* enqueueのテストから続きで行う */

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 0 , 5 | xx , xx | xx , xx | xx , xx |
	 *    1 , 10 | xx , xx | 10 , 0 | xx , xx | 5 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[5].next , queue_header);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 5);


	/*
	 *  10(head) -> 8 -> 1 -> 5
	 */
	/* --- */
	tmevtid = 8;
	/* enqueueのテストから続きで行う */

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 10 , 5 | xx , xx | xx , xx | xx , xx |
	 *    1 , 10 | xx , xx | xx , xx | xx , xx | 5 , 1 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[1].prev , queue_header);

	/*
	 *  10(head) -> 1 -> 5
	 */

}

void test_signal_time(void)
{
	int i;

	time_event_enqueue(9 , 10 , callback3 , 1000);
	
	for(i = 0 ; i < 50 ; i++)
	{
		signal_time();
		CU_ASSERT_EQUAL(lock_flag , false);
	}

}


static void callback1(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 3);
}

static void callback2(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 155);
}

static void callback3(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 1000);
	i_lock_cpu();
}

