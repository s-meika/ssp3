#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <eventflag.h>

void
test_main(void)
{
	// イベントフラグの定義
	CU_ASSERT_EQUAL(TNUM_FLGID, 2);
	CU_ASSERT_EQUAL(FLG_ID1,  1);
	CU_ASSERT_EQUAL(FLG_ID2,  2);
	
	CU_ASSERT_EQUAL(tmax_flgid,  2);
	CU_ASSERT_EQUAL(flginib_atr[0], TA_NULL);
	CU_ASSERT_EQUAL(flginib_iflgptn[0], 0x5a5a);
	CU_ASSERT_EQUAL(flginib_atr[1], TA_CLR);
	CU_ASSERT_EQUAL(flginib_iflgptn[1], 0xa5a5);
	
	CU_ASSERT_PTR_NOT_NULL(&flgcb_flgptn);
}

void task1(intptr_t exinf){}
