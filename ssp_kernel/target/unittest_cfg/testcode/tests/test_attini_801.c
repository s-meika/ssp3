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
	CU_ASSERT_EQUAL(test_bitmap_inirtn, UINT16_C(0x00ff));
}

void inirtn_1(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_1");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF1); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0000); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 0;
}

void inirtn_2(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_2");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF2); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0001); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 1;
}

void inirtn_3(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_3");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF3); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0003); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 2;
}

void inirtn_4(intptr_t exinf) {
	CU_PASS("test_attini_801: initrtn_4");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF4); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x0007); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 3;
}

void inirtn_5(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_5");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF5); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x000f); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 4;
}

void inirtn_6(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_6");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF6); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x001f); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 5;
}

void inirtn_7(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_7");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF7); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x003f); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 6;
}

void inirtn_8(intptr_t exinf) {
	CU_PASS("test_attini_801: inirtn_8");   // ��ã�γ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF8); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_inirtn, 0x007f); // ����̤ν������¹Ԥ���Ƥ��ʤ����ȡ�ʣ����¹Ԥ���Ƥ��ʤ����Ȥγ�ǧ
	test_bitmap_inirtn |= UINT16_C(0x0001) << 7;
}

void task1(intptr_t exinf){}