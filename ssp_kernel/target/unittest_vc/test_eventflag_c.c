/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2013 by Meika Sugimoto
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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(eventflag.h/c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "eventflag.h"

#include <CUnit.h>
#include <Console.h>

void test_initialize_eventflag(void)
{
	/* Pre Condition */
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	initialize_eventflag();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAAAAAAAA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x55555555);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x12345678);

}

void test_set_flg(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = set_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(0 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(4 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(1 , 0x1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 1);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(3 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0x0FF00FF0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = set_flg(2 , 0x80018001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x8FF18FF1);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);
}



void test_iset_flg(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(0 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(4 , 0x11111111);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(1 , 0x1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 1);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(3 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0;
	flgcb_flgptn[1] = 0x0FF00FF0;
	flgcb_flgptn[2] = 0;

	/* --- */
	ercd = iset_flg(2 , 0x80018001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x8FF18FF1);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0);
}

void test_pol_flg(void)
{
	ER ercd;
	FLGPTN data;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0x55AA55AA;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AA , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0x12345678;

	/* --- */
	ercd = pol_flg(0 , 0xFFFFFFFF , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	/* --- */
	ercd = pol_flg(4 , 0xFFFFFFFF , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(data , 0x12345678);

	/* E_PAR(waiptn) */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);
	CU_ASSERT_EQUAL(data , 0x00000000);
	
	/* E_PAR(mode) */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0x2 , ~(TWF_ORW|TWF_ANDW) , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);
	CU_ASSERT_EQUAL(data , 0x00000000);
	

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(2 , 0x00000001 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(data , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0x12345678;
	data = 0;

	/* --- */
	ercd = pol_flg(3 , 0x10000008 , TWF_ANDW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(data , 0x12345678);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000003);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x00000000);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(2 , 0x00000004 , TWF_ORW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 0x00000000);

	/* E_TMOUT */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000003;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0;

	/* --- */
	ercd = pol_flg(1 , 0x55AA55AB , TWF_ANDW , &data);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_TMOUT);
	CU_ASSERT_EQUAL(data , 0x00000000);

}

void test_clr_flg(void)
{
	ER ercd;
	FLGPTN data;

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(1 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_CTX */
	/* Pre Condition */
	t_lock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(2 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_CTX */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 1;
	flgcb_flgptn[0] = 0xAA55AA55;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0x11111111;

	/* --- */
	ercd = clr_flg(3 , 0x000000001);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0xAA55AA55);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x11111111);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;
	data = 0x12345678;

	/* --- */
	ercd = clr_flg(0 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000002);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_ID */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000001;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	/* --- */
	ercd =clr_flg(4 , 0xFFFFFFFF);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000001);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0xFFFFFFFF);

	/* E_OK */
	/* Pre Condition */
	t_unlock_cpu();
	intnest = 0;
	flgcb_flgptn[0] = 0x55AA55AA;
	flgcb_flgptn[1] = 0x00000002;
	flgcb_flgptn[2] = 0xFFFFFFFF;

	ercd = clr_flg(3 , 0x00000000);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(flgcb_flgptn[0] , 0x55AA55AA);
	CU_ASSERT_EQUAL(flgcb_flgptn[1] , 0x00000002);
	CU_ASSERT_EQUAL(flgcb_flgptn[2] , 0x00000000);




}

