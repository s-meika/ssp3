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
 *  TOPPERS/SSP単体テスト用スタブタスク
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "task.h"

#include <CUnit.h>
#include <Console.h>

extern volatile uint_t	ready_primap;
int task2_activate = 0;

void task1(intptr_t exinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(runtsk_curpri , 1 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);
	CU_ASSERT_EQUAL(t_sense_lock() , false);
}

void task2(intptr_t exinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(runtsk_curpri , 2 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 1);
	CU_ASSERT_EQUAL(t_sense_lock() , false);
}

void task3(intptr_t exinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(runtsk_curpri , 2 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 2);
	CU_ASSERT_EQUAL(t_sense_lock() , false);

}

void task4(intptr_t exinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(runtsk_curpri , 4 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 3);
	CU_ASSERT_EQUAL(t_sense_lock() , false);

	/* Pre Condition */
	/* 誤ったタスク状態の設定 */
	disdsp = true;
	t_lock_cpu();
}

void int_handler_0(void)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(i_sense_lock() , false);

	/* Pre Condition */

}

void int_handler_4(void)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(i_sense_lock() , false);

	/* Pre Condition */
	/* 誤った割込みハンドラ終了時状態の設定 */
	lock_flag = true;
}

void exc_handler_0(void *excinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(i_sense_lock() , false);

	/* Pre Condition */
	/* CPU例外ハンドラ終了時状態の設定 */
	lock_flag = false;

}

void exc_handler_1(void *excinf)
{
	/* Post Condition */
	CU_ASSERT_EQUAL(i_sense_lock() , false);

	/* Pre Condition */
	/* CPU例外ハンドラ終了時状態の設定 */
	lock_flag = true;

}
