#include <kernel_impl.h>
#include <cfgtest.h>
#include <kernel_cfg.h>
#include <CUnit/CUnit.h>
#include <target_config.h>

/* kernek_cfg.c */
extern STK_T *_kernel_stk;	// �����å��ΰ����Ƭ�ؤΥݥ���
extern SIZE _kernel_stksz;   	// �����å�������
extern STK_T * _kernel_istkpt;	// �����å�����ؤΥݥ���

void
test_main(void)
{
	// TOPPERS_ISTKSZ �ϥƥ��Ȥ�Ĵ�٤褦���ʤ��Τǡ��ܻ�ˤ������å��Ȥ��롥
	
	/* pre condition */
	/* post condition */
}

void task1(intptr_t exinf){}