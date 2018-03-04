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
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 16); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 0);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// アラームハンドラの定義
	CU_ASSERT_EQUAL(TNUM_ALMID, 16);
	CU_ASSERT_EQUAL(ALM_ID1,  1);
	CU_ASSERT_EQUAL(ALM_ID2,  2);
	CU_ASSERT_EQUAL(ALM_ID3,  3);
	CU_ASSERT_EQUAL(ALM_ID4,  4);
	CU_ASSERT_EQUAL(ALM_ID5,  5);
	CU_ASSERT_EQUAL(ALM_ID6,  6);
	CU_ASSERT_EQUAL(ALM_ID7,  7);
	CU_ASSERT_EQUAL(ALM_ID8,  8);
	CU_ASSERT_EQUAL(ALM_ID9,  9);
	CU_ASSERT_EQUAL(ALM_ID10, 10);
	CU_ASSERT_EQUAL(ALM_ID11, 11);
	CU_ASSERT_EQUAL(ALM_ID12, 12);
	CU_ASSERT_EQUAL(ALM_ID13, 13);
	CU_ASSERT_EQUAL(ALM_ID14, 14);
	CU_ASSERT_EQUAL(ALM_ID15, 15);
	CU_ASSERT_EQUAL(ALM_ID16, 16);
	
	CU_ASSERT_EQUAL(alminib_almhdr[0], almhdr1);
	CU_ASSERT_EQUAL(alminib_almhdr[1], almhdr2);
	CU_ASSERT_EQUAL(alminib_almhdr[2], almhdr3);
	CU_ASSERT_EQUAL(alminib_almhdr[3], almhdr4);
	CU_ASSERT_EQUAL(alminib_almhdr[4], almhdr5);
	CU_ASSERT_EQUAL(alminib_almhdr[5], almhdr6);
	CU_ASSERT_EQUAL(alminib_almhdr[6], almhdr7);
	CU_ASSERT_EQUAL(alminib_almhdr[7], almhdr8);
	CU_ASSERT_EQUAL(alminib_almhdr[8], almhdr9);
	CU_ASSERT_EQUAL(alminib_almhdr[9], almhdr10);
	CU_ASSERT_EQUAL(alminib_almhdr[10], almhdr11);
	CU_ASSERT_EQUAL(alminib_almhdr[11], almhdr12);
	CU_ASSERT_EQUAL(alminib_almhdr[12], almhdr13);
	CU_ASSERT_EQUAL(alminib_almhdr[13], almhdr14);
	CU_ASSERT_EQUAL(alminib_almhdr[14], almhdr15);
	CU_ASSERT_EQUAL(alminib_almhdr[15], almhdr16);
	
	CU_ASSERT_EQUAL(alminib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(alminib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(alminib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(alminib_exinf[3], EXINF4);
	CU_ASSERT_EQUAL(alminib_exinf[4], EXINF5);
	CU_ASSERT_EQUAL(alminib_exinf[5], EXINF6);
	CU_ASSERT_EQUAL(alminib_exinf[6], EXINF7);
	CU_ASSERT_EQUAL(alminib_exinf[7], EXINF8);
	CU_ASSERT_EQUAL(alminib_exinf[8], EXINF9);
	CU_ASSERT_EQUAL(alminib_exinf[9], EXINF10);
	CU_ASSERT_EQUAL(alminib_exinf[10], EXINF11);
	CU_ASSERT_EQUAL(alminib_exinf[11], EXINF12);
	CU_ASSERT_EQUAL(alminib_exinf[12], EXINF13);
	CU_ASSERT_EQUAL(alminib_exinf[13], EXINF14);
	CU_ASSERT_EQUAL(alminib_exinf[14], EXINF15);
	CU_ASSERT_EQUAL(alminib_exinf[15], EXINF16);
	
	
	CU_ASSERT_PTR_NOT_NULL(&almcb_almact);
}

void almhdr1(intptr_t exinf){}
void almhdr2(intptr_t exinf){}
void almhdr3(intptr_t exinf){}
void almhdr4(intptr_t exinf){}
void almhdr5(intptr_t exinf){}
void almhdr6(intptr_t exinf){}
void almhdr7(intptr_t exinf){}
void almhdr8(intptr_t exinf){}
void almhdr9(intptr_t exinf){}
void almhdr10(intptr_t exinf){}
void almhdr11(intptr_t exinf){}
void almhdr12(intptr_t exinf){}
void almhdr13(intptr_t exinf){}
void almhdr14(intptr_t exinf){}
void almhdr15(intptr_t exinf){}
void almhdr16(intptr_t exinf){}
void task1(intptr_t exinf){}
