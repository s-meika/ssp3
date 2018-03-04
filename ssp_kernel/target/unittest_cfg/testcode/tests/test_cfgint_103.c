#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

void
test_main(void)
{
	// 割込み要求ライン
	CU_ASSERT_EQUAL(tnum_intno, 1); /* TNUM_INTNO が直接テスト出来ないので代わりにこれだけテストする */
	CU_ASSERT_EQUAL(intinib_intno[0], 15);
	CU_ASSERT_EQUAL(intinib_intatr[0], TA_NULL);
	CU_ASSERT_EQUAL(intinib_intpri[0], -2);
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}