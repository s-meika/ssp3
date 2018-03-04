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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(cyclic.h/c�p)
 */


#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"
#include "cyclic.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_cyclic(void)
{
	/* Pre Condition */
	cyccb_evttim[0] = 1;
	cyccb_cycact = ~0;

	/* --- */
	initialize_cyclic();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(cyccb_evttim[0] , cycinib_cycphs[0]);
	CU_ASSERT_EQUAL(cyccb_evttim[1] , 0);
	CU_ASSERT_EQUAL(cyccb_cycact , cycinib_cycact);
}

void test_sta_cyc(void)
{
	ER ercd;

	/* �^�C���C�x���g�n���h���Ǝ����n���h���̏����� */
	initialize_time_event();
	initialize_cyclic();

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	/* ����J�n�ς݂̎����n���h���ɑ΂���J�n */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(cyccb_cycact & (1 << (1 - 1)));

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* ����J�n���Ă��Ȃ������n���h���ɑ΂���J�n */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(cyccb_cycact & (1 << (2 - 1)));
}

void test_stp_cyc(void)
{
	ER ercd;

	/* �^�C���C�x���g�n���h���Ǝ����n���h���̏����� */
	initialize_time_event();
	initialize_cyclic();

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((cyccb_cycact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	/* ����J�n�ς݂̎����n���h���ɑ΂���J�n */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(cyccb_cycact & (1 << (1 - 1)));

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* ����J�n���Ă��Ȃ������n���h���ɑ΂���J�n */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_cyc(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(cyccb_cycact & (1 << (2 - 1)));
}

void test_call_cychdr(void)
{
	ER ercd;
	int i;

	/* �^�C���C�x���g�n���h���Ǝ����n���h���̏����� */
	initialize_time_event();
	initialize_cyclic();
	
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	ercd = sta_cyc(2);
	
	/* --- */
	for(i = 0 ; i < 100 ; i++)
	{
		if(i == 43)
		{
			ercd = stp_cyc(2);
			CU_ASSERT_EQUAL(ercd , E_OK);
		}
		signal_time();
	}

	/* --- */

	/* Post Condition */
	
}

extern EVTTIM	current_time;

void cychdr1(void)
{
	int call_timing[] =
	{ 1 , 11 , 21 , 31 , 41 , 51 , 61 , 71 , 81 , 91 };
	static int step = 0;

	CU_ASSERT_EQUAL(current_time-1 , call_timing[step]);
	step = (step + 1) % (sizeof(call_timing)/sizeof(call_timing[0]));
}

void cychdr2(void)
{
	int call_timing[] =
	{ 2 , 7 , 12 , 17 , 22 , 27 , 32 , 37 , 42 };
	static int step = 0;
	
	CU_ASSERT_EQUAL(current_time-1 , call_timing[step]);
	step = (step + 1) % (sizeof(call_timing)/sizeof(call_timing[0]));

	if(step == 7)
	{
		i_lock_cpu();
	}
}
