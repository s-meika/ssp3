#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <exception.h>

/* kernel_cfg.c */
extern void _kernel_exchdr_2_2(void);

void
test_main(void)
{
	// CPU例外
	CU_ASSERT_EQUAL(tnum_excno, 1); /* TNUM_EXCNO が直接テスト出来ないので代わりにこれだけテストする */
	CU_ASSERT_EQUAL(excinib_excno[0], 2);
	CU_ASSERT_EQUAL(excinib_excatr[0], TA_NULL);
	CU_ASSERT_EQUAL(excinib_entry[0], (FP)(EXC_ENTRY(2, exchdr_2)));

	/* pre condition */
	/* post condition */
}

void exchdr_2(intptr_t exinf){}

void task1(intptr_t exinf){}