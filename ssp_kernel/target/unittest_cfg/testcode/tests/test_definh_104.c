#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>
#include <interrupt.h>

uint_t test_bitmap_isr;

/* kernel_cfg.c */
extern void INT_ENTRY(15, inthdr_15)(void);


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
	CU_ASSERT_EQUAL(intinib_intpri[0], -7);
	// ����ߥϥ�ɥ�
	CU_ASSERT_EQUAL(tnum_inhno, 1); /* TNUM_INHNO ��ľ�ܥƥ��Ƚ���ʤ��Τ�����ˤ�������ƥ��Ȥ��� */
	CU_ASSERT_EQUAL(inhinib_inhno[0], 15);
	CU_ASSERT_EQUAL(inhinib_inhatr[0], TA_NONKERNEL);
	CU_ASSERT_EQUAL(inhinib_entry[0], INT_ENTRY(15, inthdr_15));
	
	/* pre condition */
	/* post condition */
}

void inthdr_15(void){}

void task1(intptr_t exinf){}
