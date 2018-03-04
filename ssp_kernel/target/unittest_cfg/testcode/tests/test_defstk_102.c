#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>

/* kernek_cfg.c */
extern STK_T *_kernel_stk;	// スタック領域の先頭へのポインタ
extern SIZE _kernel_stksz;   	// スタックサイズ
extern STK_T * _kernel_istkpt;	// スタックの底へのポインタ

STK_T user_stack[COUNT_STK_T(256)];

void
test_main(void)
{
	// 共有スタック
	CU_ASSERT_PTR_NOT_NULL(_kernel_stk);	/*  */
	CU_ASSERT_PTR_NOT_NULL(_kernel_istkpt);	/*  */
	CU_TEST(_kernel_stksz > 0);
	CU_TEST(_kernel_istkpt-_kernel_stk >= 256); /* 指定したサイズ以上は確保されていること */
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}