#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <dataqueue.h>

void
test_main(void)
{
	// データキューの定義
	CU_ASSERT_EQUAL(TNUM_DTQID, 256);
	CU_ASSERT_EQUAL(DTQ_ID1,  1);
	CU_ASSERT_EQUAL(DTQ_ID2,  2);
	CU_ASSERT_EQUAL(DTQ_ID255,  255);
	CU_ASSERT_EQUAL(DTQ_ID256,  256);
	
	CU_ASSERT_EQUAL(tmax_dtqid,  256);
	CU_ASSERT_EQUAL(dtqinib_atr[0], TA_NULL);
	CU_ASSERT_EQUAL(dtqinib_size[0], 1);
	CU_ASSERT_EQUAL(dtqinib_atr[1], TA_NULL);
	CU_ASSERT_EQUAL(dtqinib_size[1], 2);
	CU_ASSERT_EQUAL(dtqinib_atr[254], TA_NULL);
	CU_ASSERT_EQUAL(dtqinib_size[254], 255);
	CU_ASSERT_EQUAL(dtqinib_atr[255], TA_NULL);
	CU_ASSERT_EQUAL(dtqinib_size[255], 1);

	// NULL で無いことの確認まで
	CU_ASSERT_PTR_NOT_NULL(&(dtqinib_data[0]));
	CU_ASSERT_PTR_NOT_NULL(&(dtqinib_data[1]));
	CU_ASSERT_PTR_NOT_NULL(&(dtqinib_data[254]));
	CU_ASSERT_PTR_NOT_NULL(&(dtqinib_data[255]));
	CU_ASSERT_PTR_NOT_NULL(dtqcb_count);
	CU_ASSERT_PTR_NOT_NULL(dtqcb_head);
	CU_ASSERT_PTR_NOT_NULL(dtqcb_tail);
}

void task1(intptr_t exinf){}
