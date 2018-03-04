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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(sys_manage.c�p)
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
extern const uint_t init_rdypri;

void test_loc_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = loc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);
}

void test_iloc_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = iloc_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , true);
}

void test_unl_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;
	
	/* --- */
	ercd = unl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void test_iunl_cpu(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(lock_flag , true);

	/* E_OK */
	/* Pre Condition */
	lock_flag = true;
	intnest = 1;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;
	
	/* --- */
	ercd = iunl_cpu();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(lock_flag , false);
}

void test_dis_dsp(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 1;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_OK */
	/* Pre Condition */
	lock_flag = false;

	disdsp = false;
	
	/* --- */
	ercd = dis_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , true);
}

void test_ena_dsp(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	disdsp = true;
	intnest = 1;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , true);

	/* E_CTX */
	/* Pre Condition */
	lock_flag = true;
	disdsp = true;
	intnest = 0;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(disdsp , true);

	/* E_OK */
	/* Pre Condition */
	disdsp = true;
	lock_flag = false;
	runtsk_ipri = 1;
	ready_primap = 0x0003u;
	intnest = 0;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , false);

	/* E_OK */
	/* Pre Condition */
	disdsp = true;
	lock_flag = false;
	runtsk_ipri = 1;
	ready_primap = 0x0006u;
	
	/* --- */
	ercd = ena_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(disdsp , false);
}

void test_sns_ctx(void)
{
	bool_t intctx;

	/* E_OK , true */
	/* Pre Condition */
	intnest = 1;
	
	/* --- */
	intctx = sns_ctx();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(intctx , true);

	/* E_OK , false */
	/* Pre Condition */
	intnest = 0;
	
	/* --- */
	intctx = sns_ctx();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(intctx , false);

}

void test_sns_loc(void)
{
	bool_t locked;

	/* E_OK , true */
	/* Pre Condition */
	lock_flag = true;
	
	/* --- */
	locked = sns_loc();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(locked , true);

	/* E_OK , false */
	/* Pre Condition */
	lock_flag = false;
	
	/* --- */
	locked = sns_loc();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(locked , false);
}

void test_sns_dsp(void)
{
	bool_t dsp_disabled;

	/* E_OK , true */
	/* Pre Condition */
	disdsp = true;
	intnest = 0;
	
	/* --- */
	dsp_disabled = sns_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dsp_disabled , true);

	/* E_OK , false */
	/* Pre Condition */
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dsp_disabled = sns_dsp();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dsp_disabled , false);
}

void test_sns_dpn(void)
{
	bool_t dpn;

	/* E_OK , false */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , false);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = true;
	disdsp = false;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = false;
	disdsp = true;
	intnest = 0;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);


	/* E_OK , true */
	/* Pre Condition */
	lock_flag = false;
	disdsp = false;
	intnest = 1;
	
	/* --- */
	dpn = sns_dpn();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(dpn , true);
}

void test_sns_ker(void)
{
	bool_t kernel_running;

	/* E_OK , true */
	/* Pre Condition */
	kerflg = true;
	
	/* --- */
	kernel_running = sns_ker();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(kernel_running , false);

	/* E_OK , false */
	/* Pre Condition */
	kerflg = false;
	
	/* --- */
	kernel_running = sns_ker();
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(kernel_running , true);
}

