#include <kernel.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <time_event.h>
#include <cyclic.h>
#include <alarm.h>

void
test_main(void)
{
	// タイムイベントの定義
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 6); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 4);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// 周期ハンドラの定義
	CU_ASSERT_EQUAL(TNUM_CYCID, 4);
	CU_ASSERT_EQUAL(CYC_ID1,  1);
	CU_ASSERT_EQUAL(CYC_ID2,  2);
	CU_ASSERT_EQUAL(CYC_ID3,  3);
	CU_ASSERT_EQUAL(CYC_ID4,  4);
	
	CU_ASSERT_EQUAL(cycinib_cychdr[0], cychdr1);
	CU_ASSERT_EQUAL(cycinib_cychdr[1], cychdr2);
	CU_ASSERT_EQUAL(cycinib_cychdr[2], cychdr3);
	CU_ASSERT_EQUAL(cycinib_cychdr[3], cychdr4);
	
	CU_ASSERT_EQUAL(cycinib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(cycinib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(cycinib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(cycinib_exinf[3], EXINF4);
	
	CU_ASSERT_EQUAL(cycinib_cyctim[0], 10);
	CU_ASSERT_EQUAL(cycinib_cyctim[1], 20);
	CU_ASSERT_EQUAL(cycinib_cyctim[2], 30);
	CU_ASSERT_EQUAL(cycinib_cyctim[3], 40);
	
	CU_ASSERT_EQUAL(cycinib_cycphs[0], 5);
	CU_ASSERT_EQUAL(cycinib_cycphs[1], 10);
	CU_ASSERT_EQUAL(cycinib_cycphs[2], 15);
	CU_ASSERT_EQUAL(cycinib_cycphs[3], 20);
	
	CU_ASSERT_EQUAL(cycinib_cycact, 5);
	
	
	// アラームハンドラの定義
	CU_ASSERT_EQUAL(TNUM_ALMID, 2);
	CU_ASSERT_EQUAL(ALM_ID1,  1);
	CU_ASSERT_EQUAL(ALM_ID2,  2);
	
	CU_ASSERT_EQUAL(alminib_almhdr[0], almhdr1);
	CU_ASSERT_EQUAL(alminib_almhdr[1], almhdr2);
	
	CU_ASSERT_EQUAL(alminib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(alminib_exinf[1], EXINF2);
	
	CU_ASSERT_PTR_NOT_NULL(&almcb_almact);
}

void cychdr1(intptr_t exinf){}
void cychdr2(intptr_t exinf){}
void cychdr3(intptr_t exinf){}
void cychdr4(intptr_t exinf){}

void almhdr1(intptr_t exinf){}
void almhdr2(intptr_t exinf){}

void task1(intptr_t exinf){}
