#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <exception.h>

/* kernel_cfg.c */
extern void _kernel_exchdr_2_2(void);
extern void _kernel_exchdr_3_3(void);
extern void _kernel_exchdr_12_12(void);
extern void _kernel_exchdr_14_14(void);

void
test_main(void)
{
	// CPU例外
	CU_ASSERT_EQUAL(tnum_excno, 4); /* TNUM_EXCNO が直接テスト出来ないので代わりにこれだけテストする */
	
	CU_ASSERT_EQUAL(excinib_excno[0], 2);
	CU_ASSERT_EQUAL(excinib_excatr[0], TA_NULL);
	CU_ASSERT_EQUAL(excinib_entry[0], (FP)(EXC_ENTRY(2, exchdr_2)));
	
	CU_ASSERT_EQUAL(excinib_excno[1], 3);
	CU_ASSERT_EQUAL(excinib_excatr[1], TA_NULL);
	CU_ASSERT_EQUAL(excinib_entry[1], (FP)(EXC_ENTRY(3, exchdr_3)));
	
	CU_ASSERT_EQUAL(excinib_excno[2], 12);
	CU_ASSERT_EQUAL(excinib_excatr[2], TA_NULL);
	CU_ASSERT_EQUAL(excinib_entry[2], (FP)(EXC_ENTRY(12, exchdr_12)));
	
	CU_ASSERT_EQUAL(excinib_excno[3], 14);
	CU_ASSERT_EQUAL(excinib_excatr[3], TA_NULL);
	CU_ASSERT_EQUAL(excinib_entry[3], (FP)(EXC_ENTRY(14, exchdr_14)));

	/* pre condition */
	/* post condition */
}

void exchdr_2(intptr_t exinf){}
void exchdr_3(intptr_t exinf){}
void exchdr_12(intptr_t exinf){}
void exchdr_14(intptr_t exinf){}

void task1(intptr_t exinf){}