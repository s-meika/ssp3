/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  TOPPERS/SSP単体テスト用ソースファイル(alarm.h/c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"
#include "alarm.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_alarm(void)
{
	/* Pre Condition */
	almcb_almact = ~0;

	/* --- */
	initialize_time_event();
	initialize_alarm();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(almcb_almact , 0);
}

void test_sta_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (1 - 1)));
	
	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

	
	/* E_OK，開始したアラームを再度開始 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

}

void test_stp_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);


	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (2 - 1))) == 0);
	
	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (1 - 1));
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));

	/* E_OK，停止したアラームを再度停止 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));
}

void test_ista_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	i_lock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	

	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (1 - 1)));
	
	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

	
	/* E_OK，開始したアラームを再度開始 */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

}

void test_istp_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	i_lock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_CTX */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = istp_alm(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = istp_alm(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);


	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (2 - 1))) == 0);
	
	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (1 - 1));
	
	/* --- */
	ercd = istp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (1 - 1))) == 0);

	/* E_OK，停止したアラームを再度停止 */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));
}


int almhdr1_count;
int almhdr2_count;

void test_call_almhdr(void)
{
	int i;
	ER ercd;

	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almhdr1_count = 0;
	almhdr2_count = 0;
	
	/* --- */
	ercd = sta_alm(1 , 10);
	for(i = 0 ; i < 11 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr1_count , 1);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* --- */
	ercd = sta_alm(2 , 5);
	for(i = 0 ; i < 6 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr2_count , 1);
	CU_ASSERT_EQUAL(lock_flag , false);


	almhdr1_count = 2;

	/* --- */
	ercd = sta_alm(1 , 7);
	for(i = 0 ; i < 8 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr1_count , 3);

	almhdr2_count = 4;

	/* --- */
	ercd = sta_alm(2 , 9);
	for(i = 0 ; i < 9 ; i++)
	{
		signal_time();
	}

	CU_ASSERT_EQUAL(almhdr2_count , 4);
	
	for(i = 0 ; i < 1 ; i++)
	{
		signal_time();
	}
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr2_count , 5);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void almhdr1(intptr_t exinf)
{
	almhdr1_count += 1;
}

void almhdr2(intptr_t exinf)
{
	almhdr2_count += 1;
	i_lock_cpu();
}


