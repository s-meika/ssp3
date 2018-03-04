#include <kernel.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>

uint16_t test_bitmap_terrtn;

void
test_main(void)
{
	/* precondition */
	test_bitmap_terrtn = UINT16_C(0);
	
	_kernel_call_terrtn(); // 初期化ルーチンが呼ばれていれば，flag がセットされているはず．
	
	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_terrtn, UINT16_C(0x007f));
}

void terrtn_1(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_1");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF1); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x007e); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 0;
}

void terrtn_2(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_2");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF2); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x007c); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 1;
}

void terrtn_3(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_3");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF3); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0078); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 2;
}

void terrtn_4(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_4");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF4); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0070); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 3;
}

void terrtn_5(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_5");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF5); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0060); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 4;
}

void terrtn_6(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_6");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF6); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0040); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 5;
}

void terrtn_7(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_7");   // 到達の確認
	CU_ASSERT_EQUAL(exinf, EXINF7); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0000); // 先に別の処理が実行されていないこと，複数解実行されていないことの確認
	test_bitmap_terrtn |= UINT16_C(0x0001) << 6;
}

void task1(intptr_t exinf){}