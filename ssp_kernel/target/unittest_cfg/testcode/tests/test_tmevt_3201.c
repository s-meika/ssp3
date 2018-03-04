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
	CU_ASSERT_EQUAL(tnum_tmevt_queue, 32); // TNUM_TMEVT はチェック出来ないので，この変数のみチェック
	CU_ASSERT_EQUAL(almevtid_offset, 16);
	CU_ASSERT_EQUAL(cycevtid_offset, 0);
	
	CU_ASSERT_PTR_NOT_NULL(tmevt_queue);
	CU_ASSERT_PTR_NOT_NULL(tmevt_time);
	CU_ASSERT_PTR_NOT_NULL(tmevt_callback);
	CU_ASSERT_PTR_NOT_NULL(tmevt_arg);
	
	// 周期ハンドラの定義
	CU_ASSERT_EQUAL(TNUM_CYCID, 16);
	CU_ASSERT_EQUAL(CYC_ID1,  1);
	CU_ASSERT_EQUAL(CYC_ID2,  2);
	CU_ASSERT_EQUAL(CYC_ID3,  3);
	CU_ASSERT_EQUAL(CYC_ID4,  4);
	CU_ASSERT_EQUAL(CYC_ID5,  5);
	CU_ASSERT_EQUAL(CYC_ID6,  6);
	CU_ASSERT_EQUAL(CYC_ID7,  7);
	CU_ASSERT_EQUAL(CYC_ID8,  8);
	CU_ASSERT_EQUAL(CYC_ID9,  9);
	CU_ASSERT_EQUAL(CYC_ID10,10);
	CU_ASSERT_EQUAL(CYC_ID11,11);
	CU_ASSERT_EQUAL(CYC_ID12,12);
	CU_ASSERT_EQUAL(CYC_ID13,13);
	CU_ASSERT_EQUAL(CYC_ID14,14);
	CU_ASSERT_EQUAL(CYC_ID15,15);
	CU_ASSERT_EQUAL(CYC_ID16,16);
	
	CU_ASSERT_EQUAL(cycinib_cychdr[0], cychdr1);
	CU_ASSERT_EQUAL(cycinib_cychdr[1], cychdr2);
	CU_ASSERT_EQUAL(cycinib_cychdr[2], cychdr3);
	CU_ASSERT_EQUAL(cycinib_cychdr[3], cychdr4);
	CU_ASSERT_EQUAL(cycinib_cychdr[4], cychdr5);
	CU_ASSERT_EQUAL(cycinib_cychdr[5], cychdr6);
	CU_ASSERT_EQUAL(cycinib_cychdr[6], cychdr7);
	CU_ASSERT_EQUAL(cycinib_cychdr[7], cychdr8);
	CU_ASSERT_EQUAL(cycinib_cychdr[8], cychdr9);
	CU_ASSERT_EQUAL(cycinib_cychdr[9], cychdr10);
	CU_ASSERT_EQUAL(cycinib_cychdr[10], cychdr11);
	CU_ASSERT_EQUAL(cycinib_cychdr[11], cychdr12);
	CU_ASSERT_EQUAL(cycinib_cychdr[12], cychdr13);
	CU_ASSERT_EQUAL(cycinib_cychdr[13], cychdr14);
	CU_ASSERT_EQUAL(cycinib_cychdr[14], cychdr15);
	CU_ASSERT_EQUAL(cycinib_cychdr[15], cychdr16);
	
	CU_ASSERT_EQUAL(cycinib_exinf[0], EXINF1);
	CU_ASSERT_EQUAL(cycinib_exinf[1], EXINF2);
	CU_ASSERT_EQUAL(cycinib_exinf[2], EXINF3);
	CU_ASSERT_EQUAL(cycinib_exinf[3], EXINF4);
	CU_ASSERT_EQUAL(cycinib_exinf[4], EXINF5);
	CU_ASSERT_EQUAL(cycinib_exinf[5], EXINF6);
	CU_ASSERT_EQUAL(cycinib_exinf[6], EXINF7);
	CU_ASSERT_EQUAL(cycinib_exinf[7], EXINF8);
	CU_ASSERT_EQUAL(cycinib_exinf[8], EXINF9);
	CU_ASSERT_EQUAL(cycinib_exinf[9], EXINF10);
	CU_ASSERT_EQUAL(cycinib_exinf[10], EXINF11);
	CU_ASSERT_EQUAL(cycinib_exinf[11], EXINF12);
	CU_ASSERT_EQUAL(cycinib_exinf[12], EXINF13);
	CU_ASSERT_EQUAL(cycinib_exinf[13], EXINF14);
	CU_ASSERT_EQUAL(cycinib_exinf[14], EXINF15);
	CU_ASSERT_EQUAL(cycinib_exinf[15], EXINF16);
	
	CU_ASSERT_EQUAL(cycinib_cyctim[0], 10);
	CU_ASSERT_EQUAL(cycinib_cyctim[1], 20);
	CU_ASSERT_EQUAL(cycinib_cyctim[2], 30);
	CU_ASSERT_EQUAL(cycinib_cyctim[3], 40);
	CU_ASSERT_EQUAL(cycinib_cyctim[4], 50);
	CU_ASSERT_EQUAL(cycinib_cyctim[5], 60);
	CU_ASSERT_EQUAL(cycinib_cyctim[6], 70);
	CU_ASSERT_EQUAL(cycinib_cyctim[7], 80);
	CU_ASSERT_EQUAL(cycinib_cyctim[8], 90);
	CU_ASSERT_EQUAL(cycinib_cyctim[9], 100);
	CU_ASSERT_EQUAL(cycinib_cyctim[10], 110);
	CU_ASSERT_EQUAL(cycinib_cyctim[11], 120);
	CU_ASSERT_EQUAL(cycinib_cyctim[12], 130);
	CU_ASSERT_EQUAL(cycinib_cyctim[13], 140);
	CU_ASSERT_EQUAL(cycinib_cyctim[14], 150);
	CU_ASSERT_EQUAL(cycinib_cyctim[15], 160);
	
	CU_ASSERT_EQUAL(cycinib_cycphs[0], 5);
	CU_ASSERT_EQUAL(cycinib_cycphs[1], 10);
	CU_ASSERT_EQUAL(cycinib_cycphs[2], 15);
	CU_ASSERT_EQUAL(cycinib_cycphs[3], 20);
	CU_ASSERT_EQUAL(cycinib_cycphs[4], 25);
	CU_ASSERT_EQUAL(cycinib_cycphs[5], 30);
	CU_ASSERT_EQUAL(cycinib_cycphs[6], 35);
	CU_ASSERT_EQUAL(cycinib_cycphs[7], 40);
	CU_ASSERT_EQUAL(cycinib_cycphs[8], 45);
	CU_ASSERT_EQUAL(cycinib_cycphs[9], 50);
	CU_ASSERT_EQUAL(cycinib_cycphs[10], 55);
	CU_ASSERT_EQUAL(cycinib_cycphs[11], 60);
	CU_ASSERT_EQUAL(cycinib_cycphs[12], 65);
	CU_ASSERT_EQUAL(cycinib_cycphs[13], 70);
	CU_ASSERT_EQUAL(cycinib_cycphs[14], 75);
	CU_ASSERT_EQUAL(cycinib_cycphs[15], 80);
	
	CU_ASSERT_EQUAL(cycinib_cycact, 0x55aa);
	
	
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
	CU_ASSERT_EQUAL(ALM_ID10,10);
	CU_ASSERT_EQUAL(ALM_ID11,11);
	CU_ASSERT_EQUAL(ALM_ID12,12);
	CU_ASSERT_EQUAL(ALM_ID13,13);
	CU_ASSERT_EQUAL(ALM_ID14,14);
	CU_ASSERT_EQUAL(ALM_ID15,15);
	CU_ASSERT_EQUAL(ALM_ID16,16);
	
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

void cychdr1(intptr_t exinf){}
void cychdr2(intptr_t exinf){}
void cychdr3(intptr_t exinf){}
void cychdr4(intptr_t exinf){}
void cychdr5(intptr_t exinf){}
void cychdr6(intptr_t exinf){}
void cychdr7(intptr_t exinf){}
void cychdr8(intptr_t exinf){}
void cychdr9(intptr_t exinf){}
void cychdr10(intptr_t exinf){}
void cychdr11(intptr_t exinf){}
void cychdr12(intptr_t exinf){}
void cychdr13(intptr_t exinf){}
void cychdr14(intptr_t exinf){}
void cychdr15(intptr_t exinf){}
void cychdr16(intptr_t exinf){}

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
