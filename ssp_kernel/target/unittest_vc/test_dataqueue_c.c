/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2013 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  TOPPERS/SSP単体テスト用ソースファイル(dataqueue.h/c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "dataqueue.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_dataqueue(void)
{
	int i;

	/* Pre Condition */
	for(i = 0 ; i < tmax_dtqid ; i++)
	{
		dtqcb_count[i] = 1U;
		dtqcb_head[i] = 1U;
		dtqcb_tail[i] = 1U;
	}

	/* --- */
	initialize_dataqueue();
	/* --- */

	/* Post Condition */
	for(i = 0 ; i < tmax_dtqid ; i++)
	{
		CU_ASSERT_EQUAL(dtqcb_count[i] , 0U);
		CU_ASSERT_EQUAL(dtqcb_head[i] , 0U);
		CU_ASSERT_EQUAL(dtqcb_tail[i] , 0U);
	}
	

}

void test_psnd_dtq(void)
{
	ER ercd;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = psnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);


	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_count[(1 - 1)] = 3;

	/* --- */
	ercd = psnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 0;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 0;

	/* --- */
	ercd = psnd_dtq(2 , 0x12345678);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[0] , 0x12345678);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 0;
	dtqcb_tail[(2 - 1)] = 4;
	dtqcb_count[(2 - 1)] = 4;

	/* --- */
	ercd = psnd_dtq(2 , 0xAA55AA55);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 5);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[4] , 0xAA55AA55);

}

void test_ipsnd_dtq(void)
{
	ER ercd;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = ipsnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = ipsnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	dtqcb_count[(2 - 1)] = 5;

	/* --- */
	ercd = ipsnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);


	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(1 - 1)] = 0;
	dtqcb_tail[(1 - 1)] = 0;
	dtqcb_count[(1 - 1)] = 0;

	/* --- */
	ercd = psnd_dtq(1 , 0xABCDEF12);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(1 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(1 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(1 - 1)] , 1);
	CU_ASSERT_EQUAL(_kernel_dataqueue_0[0] , 0xABCDEF12);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	dtqcb_head[(2 - 1)] = 2;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 3;

	/* --- */
	ercd = ipsnd_dtq(2 , 0x11223344);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 2);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 4);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[0] , 0x11223344);
}

void test_prcv_dtq(void)
{
	ER ercd;
	uint_t data;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(3 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(0 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_count[(2 - 1)] = 0;
	data = 1;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 1);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(1 - 1)] = 1;
	dtqcb_tail[(1 - 1)] = 0;
	dtqcb_count[(1 - 1)] = 4;
	_kernel_dataqueue_0[1] = 0x11223344;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(1 - 1)] , 2);
	CU_ASSERT_EQUAL(dtqcb_tail[(1 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(1 - 1)] , 3);
	CU_ASSERT_EQUAL(data , 0x11223344);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 4;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 1;
	_kernel_dataqueue_1[4] = 0xAABBCCDD;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(data , 0xAABBCCDD);


}
