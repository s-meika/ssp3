/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(alarm.h/c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"
#include "alarm.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_alarm(void)
{
	/* Pre Condition */
	almcb_almact = ~0;

	/* --- */
	initialize_time_event();
	initialize_alarm();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(almcb_almact , 0);
}

void test_sta_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (1 - 1)));
	
	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

	
	/* E_OK�C�J�n�����A���[�����ēx�J�n */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = sta_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

}

void test_stp_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);


	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = stp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (2 - 1))) == 0);
	
	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almcb_almact |= (1 << (1 - 1));
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));

	/* E_OK�C��~�����A���[�����ēx��~ */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));
}

void test_ista_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	i_lock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_CTX */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))));

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	

	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (1 - 1)));
	
	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

	
	/* E_OK�C�J�n�����A���[�����ēx�J�n */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = ista_alm(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT(almcb_almact & (1 << (2 - 1)));

}

void test_istp_alm(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	i_lock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_CTX */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_FALSE((almcb_almact & (1 << (2 - 1))) == 0);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = istp_alm(3);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	
	/* --- */
	ercd = istp_alm(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);


	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (2 - 1));
	
	/* --- */
	ercd = istp_alm(2);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (2 - 1))) == 0);
	
	/* E_OK */
	/* Pre Condition */
	i_unlock_cpu();
	intnest = 1;
	almcb_almact |= (1 << (1 - 1));
	
	/* --- */
	ercd = istp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT((almcb_almact & (1 << (1 - 1))) == 0);

	/* E_OK�C��~�����A���[�����ēx��~ */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	
	/* --- */
	ercd = stp_alm(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_FALSE(almcb_almact & (1 << (1 - 1)));
}


int almhdr1_count;
int almhdr2_count;

void test_call_almhdr(void)
{
	int i;
	ER ercd;

	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	almhdr1_count = 0;
	almhdr2_count = 0;
	
	/* --- */
	ercd = sta_alm(1 , 10);
	for(i = 0 ; i < 11 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr1_count , 1);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* --- */
	ercd = sta_alm(2 , 5);
	for(i = 0 ; i < 6 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr2_count , 1);
	CU_ASSERT_EQUAL(lock_flag , false);


	almhdr1_count = 2;

	/* --- */
	ercd = sta_alm(1 , 7);
	for(i = 0 ; i < 8 ; i++)
	{
		signal_time();
	}
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr1_count , 3);

	almhdr2_count = 4;

	/* --- */
	ercd = sta_alm(2 , 9);
	for(i = 0 ; i < 9 ; i++)
	{
		signal_time();
	}

	CU_ASSERT_EQUAL(almhdr2_count , 4);
	
	for(i = 0 ; i < 1 ; i++)
	{
		signal_time();
	}
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(almhdr2_count , 5);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void almhdr1(intptr_t exinf)
{
	almhdr1_count += 1;
}

void almhdr2(intptr_t exinf)
{
	almhdr2_count += 1;
	i_lock_cpu();
}


