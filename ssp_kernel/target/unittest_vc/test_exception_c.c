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
 *  TOPPERS/SSP単体テスト用ソースファイル(exception.c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "exception.h"

#include <CUnit.h>
#include <Console.h>


/* 参照変数 */
extern bool_t	reqflg;
extern bool_t	disdsp;
extern uint_t	ready_primap;

	/* Pre Condition */
	
	/* --- */
	/* --- */

	/* Post Condition */

void test_initialize_exception(void)
{
	/* Pre Condition */
	
	/* --- */
	initialize_exception();
	/* --- */

	/* Post Condition */}

#if 0
void test_kernel_exception(void)
{
	/* no change kernel state between handler start to end and no task activate */
	/* Pre Condition */
	lock_flag = false;
	reqflg = false;

	/* --- */
	kernel_exception(0 , exc_handler_0 , NULL);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , false);
	

	/* invalid kernel state at end of handler and task activate */
	/* Pre Condition */
	lock_flag = true;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = false;

	/* --- */
	kernel_exception(0 , exc_handler_1 , NULL);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , true);
	

	/* no task activate because dispatch disabled */
	/* Pre Condition */
	lock_flag = false;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = true;

	/* --- */
	kernel_exception(0 , exc_handler_0 , NULL);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , false);
	
	/* nested interrupt */
	/* Pre Condition */
	lock_flag = false;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = false;

	/* --- */
	kernel_exception(0 , exc_handler_0 , NULL);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , false);
}
#endif
