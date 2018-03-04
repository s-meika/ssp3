#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>

/* kernek_cfg.c */
extern STK_T *_kernel_stk;	// スタック領域の先頭へのポインタ
extern SIZE _kernel_stksz;   	// スタックサイズ
extern STK_T * _kernel_istkpt;	// スタックの底へのポインタ

void
test_main(void)
{
	// TOPPERS_ISTKSZ はテストで調べようがないので，目視によるチェックとする．
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}