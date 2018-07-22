/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
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

#ifndef TOPPERS_TIME_EVENT_H
#define TOPPERS_TIME_EVENT_H

#include "kernel_impl.h"
#include "target_timer.h"
#include "queue.h"

/* �C�x���g���� */
typedef ulong_t	EVTTIM;

/*
 *  �^�C���C�x���g�R�[���o�b�N�֐�
 */

typedef void (*CBACK)(uintptr_t arg);

/*
 *  �^�C���C�x���g�u���b�N
 *
 *  �R���t�B�M�����[�^�ɂ���Đ�������D
 */

/* �^�C���C�x���g�u���b�N�̃T�C�Y */
extern const uint_t tnum_tmevt_queue;

/* �^�C���C�x���g�L���[ */
extern QUEUE tmevt_queue[];

/* �^�C���C�x���g���� */
extern EVTTIM tmevt_time[];

/* �^�C���C�x���g�̃R�[���o�b�N */
extern CBACK tmevt_callback[];

/* �^�C���C�x���g�R�[���o�b�N�̈��� */
extern uintptr_t tmevt_arg[];


/* ���݂̃V�X�e������ */
extern EVTTIM current_time;

/*
 *  ���݂̃C�x���g�����Ƌ��E�C�x���g�����̍��mASPD1010�n
 */
#define BOUNDARY_MARGIN		(200000000U)

/*
 *  �Ō�Ɍ��ݎ������Z�o�������_�ł̃C�x���g�����mASPD1012�n
 */
extern EVTTIM	current_evttim;			/* ���݂̃C�x���g���� */
extern uint32_t	current_evttim_frac;	/* ���݂̃C�x���g�����̒[�� */

/*
 *  �Ō�Ɍ��ݎ������Z�o�������_�ł̍�����\�^�C�}�̃J�E���g�l�mASPD1012�n
 */
extern HRTCNT	current_hrtcnt;

/*
 *  �ł��i��ł������̃C�x���g�����mASPD1041�n
 */
extern EVTTIM	monotonic_evttim;


/*
 *  �V�X�e�������̃I�t�Z�b�g�mASPD1043�n
 *
 *  get_tim�ŎQ�Ƃ���V�X�e��������monotonic_evttim�̍���ێ�����D
 */
extern SYSTIM	systim_offset;

/*
 *  ������\�^�C�}�����݂̏������ł��邱�Ƃ������t���O�mASPD1032�n
 */
extern bool_t	in_signal_time;



/*
 *  �^�C���C�x���g�̏�����
 */
extern void
initialize_time_event(void);

/*
 *  �^�C���C�x���g�u���b�N�̃L���[�ւ̑}��
 */
extern void
time_event_register(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg);

/*
 *  �^�C���C�x���g�̓o�^
 */
extern void
time_event_enqueue(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg);

/*
 *  �^�C���C�x���g�̍폜
 */
extern void
time_event_dequeue(ID tmevtid);

/*
 *  ���݂̃C�x���g�����̍X�V
 */
extern void
update_current_evttim(void);

/*
 *  �^�C���e�B�b�N�̋���
 */
extern void
signal_time(void);


#endif	/* TOPPERS_TIME_EVENT_H */
