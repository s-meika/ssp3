#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>

/* kernek_cfg.c */
extern STK_T *_kernel_stk;	// �����å��ΰ����Ƭ�ؤΥݥ���
extern SIZE _kernel_stksz;   	// �����å�������
extern STK_T * _kernel_istkpt;	// �����å�����ؤΥݥ���

STK_T user_stack[COUNT_STK_T(256)];

void
test_main(void)
{
	// ��ͭ�����å�
	CU_ASSERT_PTR_NOT_NULL(_kernel_stk);	/*  */
	CU_ASSERT_PTR_NOT_NULL(_kernel_istkpt);	/*  */
	CU_TEST(_kernel_stksz > 0);
	CU_TEST(_kernel_istkpt-_kernel_stk >= 256); /* ���ꤷ���������ʾ�ϳ��ݤ���Ƥ��뤳�� */
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}