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
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 1); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 1);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// 周期ハンドラの定義
	CU_ASSERT_EQUAL(TNUM_CYCID, 1);
	CU_ASSERT_EQUAL(CYC_ID1,  1);
	
	CU_ASSERT_EQUAL(cycinib_cychdr[0], cychdr1);
	CU_ASSERT_EQUAL(cycinib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(cycinib_cyctim[0], 1);
	CU_ASSERT_EQUAL(cycinib_cycphs[0], 5);
	
	CU_ASSERT_EQUAL(cycinib_cycact, 0);
}

void cychdr1(intptr_t exinf){}
void task1(intptr_t exinf){}