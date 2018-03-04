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
 *  TOPPERS/SSP単体テスト用ソースファイル(task_manage.c用)
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
extern const uint_t init_rdypri;



void test_act_tsk(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	t_lock_cpu();

	/* --- */
	ercd = act_tsk(0);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	lock_flag = true;
	intnest = 1;
	t_unlock_cpu();

	/* --- */
	ercd = act_tsk(0);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);

	/* E_ID */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	t_unlock_cpu();

	/* --- */
	ercd = act_tsk(TNUM_TSKID + 1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_QOVR */
	/* Pre Condition */
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	intnest = 0;

	/* --- */
	ercd = act_tsk(TSK_SELF);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);

	/* E_QOVR */
	/* Pre Condition */
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	intnest = 0;

	/* --- */
	ercd = act_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);

	/* E_OK , non dispatch */
	/* Pre Condition */
	ready_primap = 0x0004u;
	actque_bitmap = 0x0000u;
	intnest = 0;
	runtsk_curpri = 3 - 1;
	runtsk_ipri = 2;
	
	/* --- */
	ercd = act_tsk(4);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x000Cu);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_curpri , 3 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 2);

	/* E_OK , non dispatch & activation queuing */
	/* Pre Condition */
	
	/* --- */
	ercd = act_tsk(4);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x000Cu);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_curpri , 3 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 2);

	/* E_OK , dispatch */
	/* Pre Condition */
	ready_primap = 0x0004u;
	actque_bitmap = 0x0000u;
	intnest = 0;
	runtsk_curpri = 4 - 1;
	runtsk_ipri = 3;
	
	/* --- */
	ercd = act_tsk(2);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_curpri , 4 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 3);



}

void test_iact_tsk(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;
	reqflg = false;
	i_lock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	i_unlock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	i_lock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_ID */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	reqflg = false;
	intnest = 1;
	i_unlock_cpu();

	/* --- */
	ercd = iact_tsk(TNUM_TSKID + 1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_ID */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;

	/* --- */
	ercd = iact_tsk(TSK_SELF);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);


	/* E_QOVR */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	runtsk_ipri = 0;
	intnest = 1;

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);


	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;
	i_unlock_cpu();
	
	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0001u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = 0;
	runtsk_curpri = 1 - 1;
	intnest = 1;
	
	/* --- */
	ercd = iact_tsk(2);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0003u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);
	CU_ASSERT_EQUAL(runtsk_curpri , 1 - 1);

	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	runtsk_curpri = UINT_MAX;
	intnest = 1;
	i_unlock_cpu();
	
	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

}

