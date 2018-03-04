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
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 4); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 0);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// アラームハンドラの定義
	CU_ASSERT_EQUAL(TNUM_ALMID, 4);
	CU_ASSERT_EQUAL(ALM_ID1,  1);
	CU_ASSERT_EQUAL(ALM_ID2,  2);
	CU_ASSERT_EQUAL(ALM_ID3,  3);
	CU_ASSERT_EQUAL(ALM_ID4,  4);
	
	CU_ASSERT_EQUAL(alminib_almhdr[0], almhdr1);
	CU_ASSERT_EQUAL(alminib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(alminib_almhdr[1], almhdr2);
	CU_ASSERT_EQUAL(alminib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(alminib_almhdr[2], almhdr3);
	CU_ASSERT_EQUAL(alminib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(alminib_almhdr[3], almhdr4);
	CU_ASSERT_EQUAL(alminib_exinf[3], EXINF4);
	
	CU_ASSERT_PTR_NOT_NULL(&almcb_almact);
}

void almhdr1(intptr_t exinf){}
void almhdr2(intptr_t exinf){}
void almhdr3(intptr_t exinf){}
void almhdr4(intptr_t exinf){}
void task1(intptr_t exinf){}
