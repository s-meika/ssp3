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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(interrupt.c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "interrupt.h"

#include <CUnit.h>
#include <Console.h>


/* �Q�ƕϐ� */
extern bool_t	reqflg;
extern bool_t	disdsp;
extern uint_t	ready_primap;



void test_interrupt_initialize(void)
{
	/* Pre Condition */
	
	/* --- */
	initialize_interrupt();
	/* --- */

	/* Post Condition */
}

void test_ena_int(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;

	/* --- */
	ercd = ena_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_PAR */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = ena_int(TMAX_INTNO + 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);


	/* E_OBJ */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = ena_int(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OBJ);


	/* E_OK in CPU unlocked */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = ena_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* E_OK in CPU locked */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;

	/* --- */
	ercd = ena_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
}

void test_dis_int(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	lock_flag = false;
	intnest = 1;

	/* --- */
	ercd = dis_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);

	/* E_PAR */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = dis_int(TMAX_INTNO + 1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_PAR);


	/* E_OBJ */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = dis_int(1);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OBJ);


	/* E_OK in CPU unlocked */
	/* Pre Condition */
	lock_flag = false;
	intnest = 0;

	/* --- */
	ercd = dis_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);


	/* E_OK in CPU locked */
	/* Pre Condition */
	lock_flag = true;
	intnest = 0;

	/* --- */
	ercd = dis_int(0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
}

#if 0
void test_kernel_interrupt(void)
{
	/* valid kernel state at end of handler and no task activate */
	/* Pre Condition */
	lock_flag = true;
	reqflg = false;

	/* --- */
	kernel_interrupt(0 , int_handler_0);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , true);

	/* invalid kernel state at end of handler and task activate */
	/* Pre Condition */
	lock_flag = true;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = false;

	/* --- */
	kernel_interrupt(0 , int_handler_4);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , true);
	
	/* no task activate because dispatch disabled */
	/* Pre Condition */
	lock_flag = true;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = true;

	/* --- */
	kernel_interrupt(0 , int_handler_4);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , true);
	
	/* nested interrupt */
	/* Pre Condition */
	lock_flag = true;
	ready_primap = 0x0001u;
	reqflg = true;
	disdsp = false;

	/* --- */
	kernel_interrupt(0 , int_handler_4);
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(lock_flag , true);

}
#endif
