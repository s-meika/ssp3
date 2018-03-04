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
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 8); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 8);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// 周期ハンドラの定義
	CU_ASSERT_EQUAL(TNUM_CYCID, 8);
	CU_ASSERT_EQUAL(CYC_ID1,  1);
	CU_ASSERT_EQUAL(CYC_ID2,  2);
	CU_ASSERT_EQUAL(CYC_ID3,  3);
	CU_ASSERT_EQUAL(CYC_ID4,  4);
	CU_ASSERT_EQUAL(CYC_ID5,  5);
	CU_ASSERT_EQUAL(CYC_ID6,  6);
	CU_ASSERT_EQUAL(CYC_ID7,  7);
	CU_ASSERT_EQUAL(CYC_ID8,  8);
	
	CU_ASSERT_EQUAL(cycinib_cychdr[0], cychdr1);
	CU_ASSERT_EQUAL(cycinib_cychdr[1], cychdr2);
	CU_ASSERT_EQUAL(cycinib_cychdr[2], cychdr3);
	CU_ASSERT_EQUAL(cycinib_cychdr[3], cychdr4);
	CU_ASSERT_EQUAL(cycinib_cychdr[4], cychdr5);
	CU_ASSERT_EQUAL(cycinib_cychdr[5], cychdr6);
	CU_ASSERT_EQUAL(cycinib_cychdr[6], cychdr7);
	CU_ASSERT_EQUAL(cycinib_cychdr[7], cychdr8);
	
	CU_ASSERT_EQUAL(cycinib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(cycinib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(cycinib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(cycinib_exinf[3], EXINF4);
	CU_ASSERT_EQUAL(cycinib_exinf[4], EXINF5);
	CU_ASSERT_EQUAL(cycinib_exinf[5], EXINF6);
	CU_ASSERT_EQUAL(cycinib_exinf[6], EXINF7);
	CU_ASSERT_EQUAL(cycinib_exinf[7], EXINF8);
	
	CU_ASSERT_EQUAL(cycinib_cyctim[0], 10);
	CU_ASSERT_EQUAL(cycinib_cyctim[1], 20);
	CU_ASSERT_EQUAL(cycinib_cyctim[2], 30);
	CU_ASSERT_EQUAL(cycinib_cyctim[3], 40);
	CU_ASSERT_EQUAL(cycinib_cyctim[4], 50);
	CU_ASSERT_EQUAL(cycinib_cyctim[5], 60);
	CU_ASSERT_EQUAL(cycinib_cyctim[6], 70);
	CU_ASSERT_EQUAL(cycinib_cyctim[7], 80);
	
	CU_ASSERT_EQUAL(cycinib_cycphs[0], 5);
	CU_ASSERT_EQUAL(cycinib_cycphs[1], 10);
	CU_ASSERT_EQUAL(cycinib_cycphs[2], 15);
	CU_ASSERT_EQUAL(cycinib_cycphs[3], 20);
	CU_ASSERT_EQUAL(cycinib_cycphs[4], 25);
	CU_ASSERT_EQUAL(cycinib_cycphs[5], 30);
	CU_ASSERT_EQUAL(cycinib_cycphs[6], 35);
	CU_ASSERT_EQUAL(cycinib_cycphs[7], 40);
	
	
	CU_ASSERT_EQUAL(cycinib_cycact, 85);
}

void cychdr1(intptr_t exinf){}
void cychdr2(intptr_t exinf){}
void cychdr3(intptr_t exinf){}
void cychdr4(intptr_t exinf){}
void cychdr5(intptr_t exinf){}
void cychdr6(intptr_t exinf){}
void cychdr7(intptr_t exinf){}
void cychdr8(intptr_t exinf){}
void task1(intptr_t exinf){}
