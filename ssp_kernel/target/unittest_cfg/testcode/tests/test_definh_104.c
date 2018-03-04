#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

uint_t test_bitmap_isr;

/* kernel_cfg.c */
extern void INT_ENTRY(15, inthdr_15)(void);


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
	CU_ASSERT_EQUAL(intinib_intpri[0], -7);
	// 割込みハンドラ
	CU_ASSERT_EQUAL(tnum_inhno, 1); /* TNUM_INHNO が直接テスト出来ないので代わりにこれだけテストする */
	CU_ASSERT_EQUAL(inhinib_inhno[0], 15);
	CU_ASSERT_EQUAL(inhinib_inhatr[0], TA_NONKERNEL);
	CU_ASSERT_EQUAL(inhinib_entry[0], INT_ENTRY(15, inthdr_15));
	
	/* pre condition */
	/* post condition */
}

void inthdr_15(void){}

void task1(intptr_t exinf){}
