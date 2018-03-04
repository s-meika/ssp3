#include <kernel.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>

uint16_t test_bitmap_inirtn;

void
test_main(void)
{
	/* precondition */
	test_bitmap_inirtn = UINT16_C(0);
	
	_kernel_call_inirtn(); // ルーチンが呼ばれていれば，flag がセットされているはず．
	
	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_inirtn, UINT16_C(0x0003));
}

void inirtn_1(intptr_t exinf) {
	CU_PASS("test_attini_201: inirtn_1");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF1); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0000); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 0;
}

void inirtn_2(intptr_t exinf) {
	CU_PASS("test_attini_201: inirtn_2");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF2); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0001); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 1;
}

void task1(intptr_t exinf){}