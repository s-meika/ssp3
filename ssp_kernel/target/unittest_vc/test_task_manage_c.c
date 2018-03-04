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
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(task_manage.c�p)
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



void test_act_tsk(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	t_lock_cpu();

	/* --- */
	ercd = act_tsk(0);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	lock_flag = true;
	intnest = 1;
	t_unlock_cpu();

	/* --- */
	ercd = act_tsk(0);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);

	/* E_ID */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	t_unlock_cpu();

	/* --- */
	ercd = act_tsk(TNUM_TSKID + 1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_QOVR */
	/* Pre Condition */
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	intnest = 0;

	/* --- */
	ercd = act_tsk(TSK_SELF);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);

	/* E_QOVR */
	/* Pre Condition */
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	intnest = 0;

	/* --- */
	ercd = act_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);

	/* E_OK , non dispatch */
	/* Pre Condition */
	ready_primap = 0x0004u;
	actque_bitmap = 0x0000u;
	intnest = 0;
	runtsk_curpri = 3 - 1;
	runtsk_ipri = 2;
	
	/* --- */
	ercd = act_tsk(4);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x000Cu);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_curpri , 3 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 2);

	/* E_OK , non dispatch & activation queuing */
	/* Pre Condition */
	
	/* --- */
	ercd = act_tsk(4);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x000Cu);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0008u);
	CU_ASSERT_EQUAL(runtsk_curpri , 3 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 2);

	/* E_OK , dispatch */
	/* Pre Condition */
	ready_primap = 0x0004u;
	actque_bitmap = 0x0000u;
	intnest = 0;
	runtsk_curpri = 4 - 1;
	runtsk_ipri = 3;
	
	/* --- */
	ercd = act_tsk(2);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_curpri , 4 - 1);
	CU_ASSERT_EQUAL(runtsk_ipri , 3);



}

void test_iact_tsk(void)
{
	ER ercd;

	/* E_CTX */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;
	reqflg = false;
	i_lock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);
	
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	i_unlock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 0;
	i_lock_cpu();

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_CTX);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_ID */
	/* Pre Condition */
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	reqflg = false;
	intnest = 1;
	i_unlock_cpu();

	/* --- */
	ercd = iact_tsk(TNUM_TSKID + 1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_ID */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;

	/* --- */
	ercd = iact_tsk(TSK_SELF);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_ID);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0000u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);


	/* E_QOVR */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0001u;
	actque_bitmap = 0x0001u;
	runtsk_ipri = 0;
	runtsk_ipri = 0;
	intnest = 1;

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_QOVR);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);


	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	intnest = 1;
	i_unlock_cpu();
	
	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0001u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = 0;
	runtsk_curpri = 1 - 1;
	intnest = 1;
	
	/* --- */
	ercd = iact_tsk(2);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , false);
	CU_ASSERT_EQUAL(ready_primap , 0x0003u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , 0);
	CU_ASSERT_EQUAL(runtsk_curpri , 1 - 1);

	/* E_OK */
	/* Pre Condition */
	reqflg = false;
	ready_primap = 0x0000u;
	actque_bitmap = 0x0000u;
	runtsk_ipri = UINT_MAX;
	runtsk_curpri = UINT_MAX;
	intnest = 1;
	i_unlock_cpu();
	
	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0000u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

	/* --- */
	ercd = iact_tsk(1);
	/* --- */
	
	/* Post Condition */
	CU_ASSERT_EQUAL(ercd , E_OK);
	CU_ASSERT_EQUAL(reqflg , true);
	CU_ASSERT_EQUAL(ready_primap , 0x0001u);
	CU_ASSERT_EQUAL(actque_bitmap , 0x0001u);
	CU_ASSERT_EQUAL(runtsk_ipri , UINT_MAX);

}

