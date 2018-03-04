/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE
 *  �Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒��쌠
 *      �\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[�X
 *      �R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg�p
 *      �ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p�҃}
 *      �j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L�̖���
 *      �؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg�p
 *      �ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g�ɕ�
 *        �����邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹�Q
 *      ������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD�܂��C
 *      �{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝�R�Ɋ��
 *      ������������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂���
 *  ��TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI�ɑ΂�
 *  ��K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p
 *  �ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC��
 *  ��Ȃ��D
 * 
 */

/*
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(task.c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "task.h"

#include <CUnit.h>
#include <Console.h>


/* �Q�ƕϐ� */
extern uint_t runtsk_ipri;
extern volatile uint_t	ready_primap;
extern bool_t	reqflg;
extern bool_t	disdsp;
extern const uint_t init_rdypmap;

void test_initialize_task(void)
{
	/* Pre Condition */
	/* variable reset */
	ready_primap = 0xffffu;
	actque_bitmap = 0xffffu;
	runtsk_ipri = 0u;
	disdsp = true;
	
	/* --- */
	initialize_task();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , init_rdypmap);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	CU_ASSERT_EQUAL(disdsp , false);

}

void test_search_schedtsk(void)
{
	int i , runtsk;
	
	for(i = 1 ; i < 256 ; i++)
	{
		/* Pre Condition */
		ready_primap = i;
		
		/* --- */
		runtsk = search_schedtsk();
		/* --- */
		
		/* Post Condition */
		if((i & 0x01) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 0);
		}
		else if((i & 0x02) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 1);
		}
		else if((i & 0x04) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 2);
		}
		else if((i & 0x08) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 3);
		}
		else if((i & 0x10) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 4);
		}
		else if((i & 0x20) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 5);
		}
		else if((i & 0x40) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 6);
		}
		else if((i & 0x80) != 0)
		{
			CU_ASSERT_EQUAL(runtsk , 7);
		}
		else
		{
			CU_ASSERT(0 != 1);
		}
	}
}

void test_test_dormant(void)
{
	int i , j;
	bool_t result;

	for(i = 0 ; i < sizeof(ready_primap) * 8 ; i++)
	{
		/* Pre Condition */
		ready_primap = 1u << i;
		
		/* �Z�b�g���ꂽ�r�b�g�Ȃ��false�ɂȂ邱�Ƃ��`�F�b�N */
		/* --- */
		result = test_dormant(i);
		/* --- */

		/* Post Condition */
		CU_ASSERT_EQUAL(result , false);

		/* �Z�b�g����Ă��Ȃ��r�b�g�Ȃ��true�ɂȂ邱�Ƃ��`�F�b�N */
		for(j = 0 ; j < i ; j++)
		{
			/* --- */
			result = test_dormant(j);
			/* --- */

			/* Post Condition */
			CU_ASSERT_EQUAL(result , true);
		}
		for(j = i + 1 ; j < sizeof(ready_primap) * 8 ; j++)
		{
			/* --- */
			result = test_dormant(j);
			/* --- */

			/* Post Condition */
			CU_ASSERT_EQUAL(result , true);
		}
	}
}

void test_make_active(void)
{
	bool_t result;

	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	disdsp = true;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(4);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0010u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);


	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	disdsp = false;
	runtsk_ipri = 4;
	runtsk_curpri = 4;

	/* --- */
	result = make_active(5);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(result , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0020u);
	CU_ASSERT_EQUAL(runtsk_ipri , 4);
}

void test_run_task(void)
{

	initialize_task();

	/* �����^�X�N��A�����s����p�^�[�� */
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(3 - 1);
	(void)make_active(4 - 1);

	/* --- */
	run_task(3 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* �����^�X�N�̂����D��x�������^�X�N�݂̂����s����p�^�[�� */
	/* Pre Condition */
	ready_primap = 0;
	runtsk_curpri = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(2 - 1);
	(void)make_active(4 - 1);

	/* --- */
	run_task(2 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0008);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* �P��^�X�N�����s����p�^�[�� */
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(4 - 1);
	
	/* --- */
	run_task(4 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

	/* �P��^�X�N�ŋN���v���L���[�C���O�ɂčĎ��s����p�^�[�� */
	/* Pre Condition */
	ready_primap = 0;
	runtsk_curpri = 5;
	actque_bitmap = 0x0008u;
	(void)make_active(4 - 1);
	
	/* --- */
	run_task(4 - 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);



}

void test_dispatcher(void)
{
	/* Pre Condition */
	ready_primap = 0;
	actque_bitmap = 0x0000u;
	(void)make_active(3 - 1);
	
	/* --- */
	dispatcher();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ready_primap , 0x0000);
	CU_ASSERT_EQUAL(disdsp , false);

}

