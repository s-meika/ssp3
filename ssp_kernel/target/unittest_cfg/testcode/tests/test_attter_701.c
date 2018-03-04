#include <kernel.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>

uint16_t test_bitmap_terrtn;

void
test_main(void)
{
	/* precondition */
	test_bitmap_terrtn = UINT16_C(0);
	
	_kernel_call_terrtn(); // ������롼���󤬸ƤФ�Ƥ���С�flag �����åȤ���Ƥ���Ϥ���
	
	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_terrtn, UINT16_C(0x007f));
}

void terrtn_1(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_1");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF1); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x007e); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 0;
}

void terrtn_2(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_2");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF2); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x007c); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 1;
}

void terrtn_3(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_3");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF3); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0078); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 2;
}

void terrtn_4(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_4");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF4); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0070); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 3;
}

void terrtn_5(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_5");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF5); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0060); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 4;
}

void terrtn_6(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtrn_6");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF6); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0040); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 5;
}

void terrtn_7(intptr_t exinf) {
	CU_PASS("test_attter_701: terrtn_7");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF7); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_terrtn, 0x0000); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_terrtn |= UINT16_C(0x0001) << 6;
}

void task1(intptr_t exinf){}