/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2011 by Meika Sugimoto
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

#ifndef TOPPERS_TASK_H
#define TOPPERS_TASK_H

#include "kernel_impl.h"


/*
 *  �^�X�N�D��x�̓����\���E�O���\���ϊ��}�N��
 */
#define INT_PRIORITY(x)		((uint_t)((x) - TMIN_TPRI))

/*
 *  �^�X�NID�̍ő�l�ikernel_cfg.c�j
 */
extern const ID	tmax_tskid;

/*
 *  �^�X�N�̐�
 */
#define tnum_tsk	((uint_t)(tmax_tskid - TMIN_TSKID + 1))

/*
 *  ���s�\��Ԃ̃^�X�N���Ȃ����Ɏ��s���^�X�N�̌��ݗD��x�ɐݒ肷��l
 */
#define TSKPRI_NULL		(UINT_MAX)


/*
 *  ���f�B�L���[�T�[�`�̂��߂̃r�b�g�}�b�v
 */
extern volatile uint_t	ready_primap;

/*
 *  �N���v���L���[�C���O�̃r�b�g�}�b�v
 */
extern uint_t	actque_bitmap;

/*
 *  �f�B�X�p�b�`�^�^�X�N��O�������[�`���N���v���t���O
 *
 *  �����݃n���h���^CPU��O�n���h���̏o�������ɁC�f�B�X�p�b�`�܂���
 *  �^�X�N��O�������[�`���̋N����v�����邱�Ƃ������t���O�D
 */
extern bool_t	reqflg;

/*
 *  �f�B�X�p�b�`�֎~���
 *
 *  �f�B�X�p�b�`�֎~��Ԃł��邱�Ƃ������t���O�D
 */
extern bool_t	disdsp;

/*
 *  ���s��ԃ^�X�N�̌��ݗD��x
 *
 *  ���s���̃^�X�N�Ɏ��s���D��x���ݒ肳��Ă���Ύ��s���D��x���C
 *  �ݒ肳��Ă��Ȃ���΋N�����D��x���ݒ肳���D
 */
extern uint_t runtsk_curpri;

/*
 *  ���s��ԃ^�X�N�̋N�����D��x
 */
extern uint_t runtsk_ipri;

/*
 *  �^�X�N�Ǘ����W���[���̏�����
 *
 *  �S�Ẵ^�X�N������������D�e�^�X�N�̓^�X�N������TA_ACT���ݒ肳��Ă����
 *  ���s�\��ԁC�����łȂ��ꍇ�͋x�~��ԂƂȂ�D
 *  
 *  �܂��A�f�B�X�p�b�`���t���O���f�B�X�p�b�`����Ԃɐݒ肷��D
 *  
 *  �{�֐��̓R���t�B�M�����[�^����������object_initialize�ȊO�ŌĂ�ł͂Ȃ�Ȃ��D
 */
extern void initialize_task(void);

/*
 *  �^�X�N�̋N��
 *
 *  ipri�Ŏw�肵���N�����D��x�����^�X�N�����s�\��ԂɑJ�ڂ�����D
 *  �{�֐������s���邱�Ƃɂ��v���G���v�g����������ꍇ��true���C
 *  �����łȂ��ꍇ��false��Ԃ��D
 *
 *  �{�֐���CPU���b�N��ԁC�S�����݃��b�N������ԁC�����ݗD��x�}�X�N�S������Ԃ�
 *  �Ăяo�����ƁD
 */
extern bool_t make_active(uint_t ipri);

/*
 *  �w�肵���N�����D��x�̃^�X�N���x�~��Ԃ��ǂ����̃e�X�g
 *
 *  ipri�Ŏw�肵���N�����D��x�����^�X�N���x�~��Ԃł����
 *  true������ȊO�i���s�\��ԁC���s�\��ԁj�ł����false��Ԃ��D
 *
 *  �{�֐���CPU���b�N��ԁC�S�����݃��b�N������ԁC�����ݗD��x�}�X�N�S������Ԃ�
 *  �Ăяo�����ƁD
 */
extern bool_t test_dormant(uint_t ipri);

/*
 *  �ō��D�揇�ʃ^�X�N�̃T�[�`
 *
 *  ���s�\��Ԃ̃^�X�N�̒�����ł��D�揇�ʂ������^�X�N�̏����D��x��
 *  �Ԃ��D
 *
 *  �{�֐���CPU���b�N��ԁC�S�����݃��b�N������ԁC�����ݗD��x�}�X�N�S������Ԃ�
 *  �Ăяo�����ƁD
 */
extern uint_t search_schedtsk(void);

/*
 *  �^�X�N�̎��s
 *
 *  ipri�Ŏw�肵���N�����D��x�����^�X�N�����s����D
 *  �{�֐�������s�����^�X�N����T�[�r�X�R�[�����o�R����
 *  �ċA�I�ɌĂ΂�邱�Ƃ�����D
 *
 *  �{�֐���CPU���b�N��ԁC�S�����݃��b�N������ԁC�����ݗD��x�}�X�N�S������Ԃ�
 *  �Ăяo�����ƁD
 */
extern void run_task(uint_t ipri);

/*
 *  �^�X�N�f�B�X�p�b�`��
 *
 *  �J�[�l��������������ɌĂяo����C�ō��D�揇�ʂƂȂ����^�X�N�����s����D
 *
 *  �{�֐���CPU���b�N��ԁC�S�����݃��b�N������ԁC�����ݗD��x�}�X�N�S������Ԃ�
 *  �Ăяo�����ƁD
 *  �Ȃ��C�{�֐�����̓��^�[�����Ȃ��D
 *  
 */
extern void dispatcher(void) NoReturn;

/*
 *  �^�X�N�̋N�����D��x�擾(�^�X�N�R���e�L�X�g�p)
 *
 *  tskid�Ŏw�肵���^�X�N�̋N�����D��x���擾����D
 *  tskid��TMIN_TSKID�ȏ�Ctmax_tskid�ȉ��̒l�C��������TSK_SELF��
 *  �w�肵�Ȃ���΂Ȃ�Ȃ��D
 */
extern uint_t get_ipri_self(ID tskid);

/*
 *  �^�X�N�̋N�����D��x�擾
 *
 *  tskid�Ŏw�肵���^�X�N�̋N�����D��x���擾����D
 *  tskid��TMIN_TSKID�ȏ�Ctmax_tskid�ȉ��̒l�Ŏw�肵�Ȃ���΂Ȃ�Ȃ��D
 */
Inline uint_t
get_ipri(ID tskid)
{
	return (uint_t)(tskid - TMIN_TSKID);
}


/* �N���v���L���[�C���O�r�b�g�}�b�v�̑��� */
#define ACTQUE_BIT(ipri)			(1U << (ipri))

/* �N���v���L���[�C���O�̃Z�b�g */
Inline
void actque_set(uint_t ipri)
{
	actque_bitmap |= ACTQUE_BIT(ipri);
}

/* �N���v���L���[�C���O�̃N���A */
Inline
void actque_clear(uint_t ipri)
{
	actque_bitmap &= ~ACTQUE_BIT(ipri);
}

/* �N���v���L���[�C���O���̃`�F�b�N */
Inline
bool_t actque_test(uint_t ipri)
{
	return ((actque_bitmap & ACTQUE_BIT(ipri)) != 0U);
}


#endif /* TOPPERS_TASK_H */
