#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

uint_t test_bitmap_isr;

/* kernel_cfg.c */
extern void _kernel_inthdr_15(void);
extern FP INT_ENTRY(15,_kernel_inthdr_15)(void); 


// ��ư������������ߥϥ�ɥ�ؽ�������ã���뤫�ɤ����ϡ��������åȰ�¸��������Ǥ��ꡤ�ƥ����оݳ��Ȥ���
// INTHDR_ENTRY �ޥ�������Ƥϥ������åȤ�����Ǥ��ꡤ����ߤ�����������������ߥϥ�ɥ�θƽФ���
// �μ¤˼»ܤ���뤫�ɤ������ܥƥ��Ȥ��ϰϳ��Ȥ��롥�����Ǥϳ���ߥϥ�ɥ餬�����뤵���褦�������������Ѱդ���
// �������åȤ��ȼ��� .tf �ե����������������Ϥ��Υƥ��Ȥ��ϰϳ�

void
test_main(void)
{
	// ������׵�饤��
	CU_ASSERT_EQUAL(tnum_intno, 1); /* TNUM_INTNO ��ľ�ܥƥ��Ƚ���ʤ��Τ�����ˤ�������ƥ��Ȥ��� */
	CU_ASSERT_EQUAL(intinib_intno[0], 15);
	CU_ASSERT_EQUAL(intinib_intatr[0], TA_EDGE);
	CU_ASSERT_EQUAL(intinib_intpri[0], -6);
	// ����ߥϥ�ɥ�
	CU_ASSERT_EQUAL(tnum_inhno, 1); /* TNUM_INHNO ��ľ�ܥƥ��Ƚ���ʤ��Τ�����ˤ�������ƥ��Ȥ��� */
	CU_ASSERT_EQUAL(inhinib_inhno[0], 15);
	CU_ASSERT_EQUAL(inhinib_inhatr[0], TA_NULL);
	CU_ASSERT_EQUAL(inhinib_entry[0], (FP)INT_ENTRY(15,_kernel_inthdr_15));
	
	/* pre condition */
	test_bitmap_isr = 0;
	ipm_value = 6;
	
	// �������������������Ū�ˤ˸Ƥ��Ǥ��ơ�ISR�������뤵��뤫�Υƥ���
	(FP)INT_ENTRY(15,_kernel_inthdr_15)();

	/* post condition */
	CU_ASSERT_EQUAL(test_bitmap_isr, 0xaa);
}

// ISR
void isr_15_1(intptr_t exinf)
{
	CU_PASS("test_attisr_110: isr_15_1");	// ISR����ã�������Ȥγ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF1); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_isr, 0); // ��˼¹Ԥ��줿���Ȥγ�ǧ
	test_bitmap_isr = 0x55;	// ��ǧ�Ѥ��ͤ򥻥å�
}

// ISR
void isr_15_2(intptr_t exinf)
{
	CU_PASS("test_attisr_110: isr_15_2");	// ISR����ã�������Ȥγ�ǧ
	CU_ASSERT_EQUAL(exinf, EXINF2); // �������������Ϥ���뤳�Ȥγ�ǧ
	CU_ASSERT_EQUAL(test_bitmap_isr, 0x55); // ��˼¹Ԥ��줿���Ȥγ�ǧ
	test_bitmap_isr = 0xaa;	// ��ǧ�Ѥ��ͤ򥻥å�
}

/*
 *  ����ߥϥ�ɥ��������ɬ�פ�IRC���
 */
void
i_begin_int(INTNO intno)
{
	CU_PASS("test_attisr_110: i_begin_int");	// ISR����ã�������Ȥγ�ǧ
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
void
i_end_int(INTNO intno)
{
	CU_PASS("test_attisr_110: i_end_int");	// ISR����ã�������Ȥγ�ǧ
}

void task1(intptr_t exinf){}
