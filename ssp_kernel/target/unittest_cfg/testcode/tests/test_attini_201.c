#include <kernel.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>

uint16_t test_bitmap_inirtn;

void
test_main(void)
{
	/* precondition */
	test_bitmap_inirtn = UINT16_C(0);
	
	_kernel_call_inirtn(); // �롼���󤬸ƤФ�Ƥ���С�flag �����åȤ���Ƥ���Ϥ���
	
	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_inirtn, UINT16_C(0x0003));
}

void inirtn_1(intptr_t exinf) {
	CU_PASS("test_attini_201: inirtn_1");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF1); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0000); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 0;
}

void inirtn_2(intptr_t exinf) {
	CU_PASS("test_attini_201: inirtn_2");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF2); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0001); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 1;
}

void task1(intptr_t exinf){}