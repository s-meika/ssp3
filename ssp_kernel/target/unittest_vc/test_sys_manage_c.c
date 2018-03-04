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
 *  TOPPERS/SSP単体テスト用ソースファイル(sys_manage.c用)
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

void test_loc_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);
}

void test_iloc_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);
}

void test_unl_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void test_iunl_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void test_dis_dsp(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 1;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;

	disdsp = false;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , true);
}

void test_ena_dsp(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	disdsp = true;
	intnest = 1;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , true);

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	disdsp = true;
	intnest = 0;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , true);

	/* E_OK */
	/* Pre Condition */
	disdsp = true;
	lock_flag = false;
	runtsk_ipri = 1;
	ready_primap = 0x0003u;
	intnest = 0;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_OK */
	/* Pre Condition */
	disdsp = true;
	lock_flag = false;
	runtsk_ipri = 1;
	ready_primap = 0x0006u;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , false);
}

void test_sns_ctx(void)
{
	bool_t intctx;

	/* E_OK , true */
	/* Pre Condition */
	intnest = 1;
	
	/* --- */
	intctx = sns_ctx();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(intctx , true);

	/* E_OK , false */
	/* Pre Condition */
	intnest = 0;
	
	/* --- */
	intctx = sns_ctx();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(intctx , false);

}

void test_sns_loc(void)
{
	bool_t locked;

	/* E_OK , true */
	/* Pre Condition */
	lock_flag = true;
	
	/* --- */
	locked = sns_loc();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(locked , true);

	/* E_OK , false */
	/* Pre Condition */
	lock_flag = false;
	
	/* --- */
	locked = sns_loc();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(locked , false);
}

void test_sns_dsp(void)
{
	bool_t dsp_disabled;

	/* E_OK , true */
	/* Pre Condition */
	disdsp = true;
	intnest = 0;
	
	/* --- */
	dsp_disabled = sns_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dsp_disabled , true);

	/* E_OK , false */
	/* Pre Condition */
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dsp_disabled = sns_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dsp_disabled , false);
}

void test_sns_dpn(void)
{
	bool_t dpn;

	/* E_OK , false */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , false);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = true;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = false;
	disdsp = true;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 1;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);
}

void test_sns_ker(void)
{
	bool_t kernel_running;

	/* E_OK , true */
	/* Pre Condition */
	kerflg = true;
	
	/* --- */
	kernel_running = sns_ker();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(kernel_running , false);

	/* E_OK , false */
	/* Pre Condition */
	kerflg = false;
	
	/* --- */
	kernel_running = sns_ker();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(kernel_running , true);
}

