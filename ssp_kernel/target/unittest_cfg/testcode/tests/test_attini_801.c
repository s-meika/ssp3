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
	CU_ASSERT_EQUAL(test_bitmap_inirtn, UINT16_C(0x00ff));
}

void inirtn_1(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_1");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF1); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0000); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 0;
}

void inirtn_2(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_2");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF2); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0001); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 1;
}

void inirtn_3(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_3");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF3); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0003); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 2;
}

void inirtn_4(intptr_t exinf) {
	CU_PASS("test_attini_801: initrtn_4");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF4); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0007); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 3;
}

void inirtn_5(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_5");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF5); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x000f); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 4;
}

void inirtn_6(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_6");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF6); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x001f); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 5;
}

void inirtn_7(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_7");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF7); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x003f); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 6;
}

void inirtn_8(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_8");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF8); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x007f); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_inirtn |= UINT16_C(0x0001) << 7;
}

void task1(intptr_t exinf){}