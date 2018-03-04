#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

void
test_main(void)
{
	// ������׵�饤��
	CU_ASSERT_EQUAL(tnum_intno, 1); /* TNUM_INTNO ��ľ�ܥƥ��Ƚ���ʤ��Τ�����ˤ�������ƥ��Ȥ��� */
	CU_ASSERT_EQUAL(intinib_intno[0], 15);
	CU_ASSERT_EQUAL(intinib_intatr[0], TA_NULL);
	CU_ASSERT_EQUAL(intinib_intpri[0], -2);
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}