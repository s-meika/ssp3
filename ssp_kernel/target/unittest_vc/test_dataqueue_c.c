/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2013 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(dataqueue.h/c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "dataqueue.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_dataqueue(void)
{
	int i;

	/* Pre Condition */
	for(i = 0 ; i < tmax_dtqid ; i++)
	{
		dtqcb_count[i] = 1U;
		dtqcb_head[i] = 1U;
		dtqcb_tail[i] = 1U;
	}

	/* --- */
	initialize_dataqueue();
	/* --- */

	/* Post Condition */
	for(i = 0 ; i < tmax_dtqid ; i++)
	{
		CU_ASSERT_EQUAL(dtqcb_count[i] , 0U);
		CU_ASSERT_EQUAL(dtqcb_head[i] , 0U);
		CU_ASSERT_EQUAL(dtqcb_tail[i] , 0U);
	}
	

}

void test_psnd_dtq(void)
{
	ER ercd;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = psnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);


	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = psnd_dtq(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_count[(1 - 1)] = 3;

	/* --- */
	ercd = psnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 0;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 0;

	/* --- */
	ercd = psnd_dtq(2 , 0x12345678);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[0] , 0x12345678);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 0;
	dtqcb_tail[(2 - 1)] = 4;
	dtqcb_count[(2 - 1)] = 4;

	/* --- */
	ercd = psnd_dtq(2 , 0xAA55AA55);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 5);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[4] , 0xAA55AA55);

}

void test_ipsnd_dtq(void)
{
	ER ercd;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = ipsnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = ipsnd_dtq(1 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(3 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = ipsnd_dtq(0 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	dtqcb_count[(2 - 1)] = 5;

	/* --- */
	ercd = ipsnd_dtq(2 , 0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);


	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(1 - 1)] = 0;
	dtqcb_tail[(1 - 1)] = 0;
	dtqcb_count[(1 - 1)] = 0;

	/* --- */
	ercd = psnd_dtq(1 , 0xABCDEF12);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(1 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(1 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(1 - 1)] , 1);
	CU_ASSERT_EQUAL(_kernel_dataqueue_0[0] , 0xABCDEF12);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	dtqcb_head[(2 - 1)] = 2;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 3;

	/* --- */
	ercd = ipsnd_dtq(2 , 0x11223344);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 2);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 1);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 4);
	CU_ASSERT_EQUAL(_kernel_dataqueue_1[0] , 0x11223344);
}

void test_prcv_dtq(void)
{
	ER ercd;
	uint_t data;
	extern intptr_t _kernel_dataqueue_0[];
	extern intptr_t _kernel_dataqueue_1[];

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(3 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;

	/* --- */
	ercd = prcv_dtq(0 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_count[(2 - 1)] = 0;
	data = 1;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 1);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(1 - 1)] = 1;
	dtqcb_tail[(1 - 1)] = 0;
	dtqcb_count[(1 - 1)] = 4;
	_kernel_dataqueue_0[1] = 0x11223344;

	/* --- */
	ercd = prcv_dtq(1 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(1 - 1)] , 2);
	CU_ASSERT_EQUAL(dtqcb_tail[(1 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(1 - 1)] , 3);
	CU_ASSERT_EQUAL(data , 0x11223344);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	dtqcb_head[(2 - 1)] = 4;
	dtqcb_tail[(2 - 1)] = 0;
	dtqcb_count[(2 - 1)] = 1;
	_kernel_dataqueue_1[4] = 0xAABBCCDD;

	/* --- */
	ercd = prcv_dtq(2 , (intptr_t *)&data);
	/* --- */

	/* Post Condition */

	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(dtqcb_head[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_tail[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(dtqcb_count[(2 - 1)] , 0);
	CU_ASSERT_EQUAL(data , 0xAABBCCDD);


}
