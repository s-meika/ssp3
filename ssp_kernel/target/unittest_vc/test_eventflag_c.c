/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2013 by Meika Sugimoto
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
 *  TOPPERS/SSP単体テスト用ソースファイル(eventflag.h/c用)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "eventflag.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_eventflag(void)
{
	/* Pre Condition */
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	initialize_eventflag();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAAAAAAAA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x55555555);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x12345678);

}

void test_set_flg(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(0 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(4 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(1 , 0x1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 1);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(3 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0x0FF00FF0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(2 , 0x80018001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x8FF18FF1);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);
}



void test_iset_flg(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(0 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(4 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 1);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(3 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0x0FF00FF0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(2 , 0x80018001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x8FF18FF1);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);
}

void test_pol_flg(void)
{
	ER ercd;
	FLGPTN data;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(0 , 0xFFFFFFFF , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	/* --- */
	ercd = pol_flg(4 , 0xFFFFFFFF , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_PAR(waiptn) */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);
	CU_ASSERT_EQUAL(data , 0x00000000);
	
	/* E_PAR(mode) */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0x2 , ~(TWF_ORW|TWF_ANDW) , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);
	CU_ASSERT_EQUAL(data , 0x00000000);
	

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(2 , 0x00000001 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(data , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0x12345678;
	data = 0;

	/* --- */
	ercd = pol_flg(3 , 0x10000008 , TWF_ANDW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(data , 0x12345678);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x00000000);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(2 , 0x00000004 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 0x00000000);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AB , TWF_ANDW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 0x00000000);

}

void test_clr_flg(void)
{
	ER ercd;
	FLGPTN data;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(1 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(2 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(3 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0x12345678;

	/* --- */
	ercd = clr_flg(0 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000002);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	/* --- */
	ercd =clr_flg(4 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	ercd = clr_flg(3 , 0x00000000);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000002);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x00000000);




}

