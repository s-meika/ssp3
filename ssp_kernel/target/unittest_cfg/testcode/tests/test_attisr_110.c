#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

uint_t test_bitmap_isr;

/* kernel_cfg.c */
extern void _kernel_inthdr_15(void);
extern FP INT_ENTRY(15,_kernel_inthdr_15)(void); 


// 自動生成される割込みハンドラへ処理が到達するかどうかは，ターゲット依存部の問題であり，テスト対象外とする
// INTHDR_ENTRY マクロの内容はターゲットの問題であり，割込みの入り口処理から割込みハンドラの呼出しが
// 確実に実施されるかどうかは本テストの範囲外とする．ここでは割込みハンドラがコールされるような入口処理を用意する
// ターゲットで独自に .tf ファイルを作成した場合はこのテストの範囲外

void
test_main(void)
{
	// 割込み要求ライン
	CU_ASSERT_EQUAL(tnum_intno, 1); /* TNUM_INTNO が直接テスト出来ないので代わりにこれだけテストする */
	CU_ASSERT_EQUAL(intinib_intno[0], 15);
	CU_ASSERT_EQUAL(intinib_intatr[0], TA_EDGE);
	CU_ASSERT_EQUAL(intinib_intpri[0], -6);
	// 割込みハンドラ
	CU_ASSERT_EQUAL(tnum_inhno, 1); /* TNUM_INHNO が直接テスト出来ないので代わりにこれだけテストする */
	CU_ASSERT_EQUAL(inhinib_inhno[0], 15);
	CU_ASSERT_EQUAL(inhinib_inhatr[0], TA_NULL);
	CU_ASSERT_EQUAL(inhinib_entry[0], (FP)INT_ENTRY(15,_kernel_inthdr_15));
	
	/* pre condition */
	test_bitmap_isr = 0;
	ipm_value = 6;
	
	// 割込み入口処理を明示的にに呼び打して，ISRがコールされるかのテスト
	(FP)INT_ENTRY(15,_kernel_inthdr_15)();

	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_isr, 0xaa);
}

// ISR
void isr_15_1(intptr_t exinf)
{
	CU_PASS("test_attisr_110: isr_15_1");	// ISRへ到達したことの確認
	CU_ASSERT_EQUAL(exinf, EXINF1); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_isr, 0); // 先に実行されたことの確認
	test_bitmap_isr = 0x55;	// 確認用に値をセット
}

// ISR
void isr_15_2(intptr_t exinf)
{
	CU_PASS("test_attisr_110: isr_15_2");	// ISRへ到達したことの確認
	CU_ASSERT_EQUAL(exinf, EXINF2); // 引数が正しく渡されることの確認
	CU_ASSERT_EQUAL(test_bitmap_isr, 0x55); // 先に実行されたことの確認
	test_bitmap_isr = 0xaa;	// 確認用に値をセット
}

/*
 *  割込みハンドラの入口で必要なIRC操作
 */
void
i_begin_int(INTNO intno)
{
	CU_PASS("test_attisr_110: i_begin_int");	// ISRへ到達したことの確認
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 */
void
i_end_int(INTNO intno)
{
	CU_PASS("test_attisr_110: i_end_int");	// ISRへ到達したことの確認
}

void task1(intptr_t exinf){}
