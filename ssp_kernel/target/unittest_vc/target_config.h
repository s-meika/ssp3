/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 * �^�[�Q�b�g�ˑ������W���[���iWindows�e�X�g���p�j
 *
 * �J�[�l���̃^�[�Q�b�g�ˑ����̃C���N���[�h�t�@�C���Dkernel_impl.h�̃^�[
 * �Q�b�g�ˑ����̈ʒu�t���ƂȂ��D
 */

/*
 *  �g���[�X���O�Ɋւ���ݒ�
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  �f�t�H���g�̔�^�X�N�R���e�L�X�g�p�̃X�^�b�N�̈�̒�`
 *  8byte�P�ʂŎ擾�����D 
 */
#define DEFAULT_ISTKSZ			(0x1000/8U)		/* 4KByte */
/*
 *  ��^�X�N�R���e�L�X�g�p�̃X�^�b�N�����l
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((istk) + (istksz)))


/*
 *  �������ԑ҂��̂��߂̒�`�i�{����SIL�̃^�[�Q�b�g�ˑ����j
 */
#define SIL_DLY_TIM1    162
#define SIL_DLY_TIM2    100

#define TIC_NUME		1

#ifndef TOPPERS_MACRO_ONLY

/*
 *  TOPPERS�W�������ݏ������f���̎���
 */

/*
 *  CPU���b�N�t���O�����̂��߂̕ϐ�
 * 
 *  �����̕ϐ��́CCPU���b�N��Ԃ̎��̂ݏ��������Ă��悢�Ƃ���D
 *  �C�����C���֐����ŁC�A�N�Z�X�̏������ω����Ȃ��悤�Cvolatile ���w��D 
 */
extern volatile bool_t  lock_flag;    /* CPU���b�N�t���O�̒l��ێ�����ϐ� */
extern volatile uint32_t saved_iipm;  /* �����ݗD��x���}�X�N����ϐ� */

extern uint_t intnest;

/*
 *  �R���e�L�X�g�̎Q��
 *
 */
Inline bool_t
sense_context(void)
{
	return (intnest > 0);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ݗD��x�}�X�N�̊O���\���Ɠ����\���̕ϊ�
 */
#define EXT_IPM(iipm)   (-(iipm))		/* �����\�����O���\���� */
#define INT_IPM(ipm)    (-(ipm))		/* �O���\��������\���� */

/*
 *  CPU���b�N��Ԃł̊����ݗD��x�}�X�N
 */
#define TIPM_LOCK    TMIN_INTPRI

/*
 *  CPU���b�N��Ԃł̊����ݗD��x�}�X�N�̓����\��
 *
 *  TIPM_LOCK�́CCPU���b�N��Ԃł�BASEPRI�̒l�D�J�[�l���Ǘ��O�̂��̂�
 *  �������ׂĂ̊����݂��}�X�N����l�ɒ�`����D  
 */
#define IIPM_LOCK    INT_IPM(TIPM_LOCK)

/*
 *  TIPM_ENAALL�i�����ݗD��x�}�X�N�S�����j�̓����\��
 *
 *  BASEPRI�� '0' ��ݒ肷�邱�ƂŁC�S�����݂�������D
 */
#define IIPM_ENAALL  (0)


#ifndef TOPPERS_MACRO_ONLY


/*
 *  CPU���b�N��Ԃւ̈ڍs
 */
Inline void
x_lock_cpu(void)
{
	lock_flag = true;
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPU���b�N��Ԃ̉���
 */
Inline void
x_unlock_cpu(void)
{
	lock_flag = false;
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  CPU���b�N��Ԃ̎Q��
 */
Inline bool_t
x_sense_lock(void)
{
	return(lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()

/*
 * �i���f����́j�����ݗD��x�}�X�N�̐ݒ�
 *
 *  CPU���b�N�t���O���N���A����Ă��鎞�́C�n�[�h�E�F�A�̊����ݗD��x�}
 *  �X�N��ݒ肷��DCPU���b�N�t���O���Z�b�g����Ă��鎞�́Csaved_iipm
 *  ��ݒ肵�C����ɁC�n�[�h�E�F�A�̊����ݗD��x�}�X�N���C�ݒ肵�悤��
 *  �����i���f����́j�����ݗD��x�}�X�N��TIPM_LOCK�̍������ɐݒ肷��D
 */
Inline void
x_set_ipm(PRI intpri)
{
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 *  �����ݔԍ��E�����݃n���h���ԍ�
 *
 *  �����݃n���h���ԍ�(inhno)�Ɗ����ݔԍ�(intno)�́C���荞�ݔ�������
 *  EPSR�ɐݒ肳����O�ԍ��Ƃ���D 
 */

/*
 *  �����ݔԍ��͈̔͂̔���
 */
#define VALID_INTNO(intno)           ((TMIN_INTNO <= (intno)) && ((intno) <= TMAX_INTNO))
#define VALID_INTNO_DISINT(intno)    VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)    VALID_INTNO(intno)

/*
 *  �����݃n���h���̐ݒ�
 *
 *  �x�N�g���ԍ�inhno�̊����݃n���h���̋N���Ԓnint_entry�ɐݒ肷��D������
 *  �n���h���e�[�u��
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  �����݃n���h���̏o���������̐����}�N��
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) extern void inthdr(void);

/*
 *  �����ݗv���֎~�t���O
 */

/*
 *  �����ݑ������ݒ肳��Ă��邩�𔻕ʂ��邽�߂̕ϐ��ikernel_cfg.c�j
 */
extern const bool_t	bitpat_cfgint[];

/*
 *  �����ݗv���֎~�t���O�̃Z�b�g
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D  
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	return bitpat_cfgint[intno];
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *  �����ݗv���֎~�t���O�̉���
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	return bitpat_cfgint[intno];

}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *  �����ݗv�����C���̑����̐ݒ�
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  �����݃n���h�������ŕK�v��IRC����
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  �����݃n���h���̏o���ŕK�v��IRC����
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  CPU��O�n���h���֌W
 */ 

/*
 *  CPU��O�n���h���ԍ�
 */
#define VALID_EXCNO_DEFEXC(excno)    (TMIN_EXCNO <= (excno) && (excno) <= TMAX_EXCNO)

/*
 *  CPU��O�n���h���̋���
 */
extern void enable_exc(EXCNO excno);

/*
 *  CPU��O�n���h���̋֎~
 */
extern void disable_exc(EXCNO excno);

/*
 *  CPU��O�n���h���̐ݒ�
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
}

/*
 *  CPU��O�n���h���̓��������̐����}�N��
 */
#define EXC_ENTRY(excno, exchdr)    exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr) extern void exchdr(void *p_excinf);

/*
 *  CPU��O�̔����������̃R���e�L�X�g�Ɗ����݂̃}�X�N��Ԃ̎Q��
 *
 *  CPU��O�̔����������̃V�X�e����Ԃ��C�J�[�l�����s���łȂ��C�^�X�N�R
 *  ���e�L�X�g�ł���C�����݃��b�N��ԂłȂ��CCPU���b�N��ԂłȂ��C�i��
 *  �f����́j�����ݗD��x�}�X�N�S������Ԃł��鎞��true�C�����łȂ���
 *  ��false��Ԃ��iCPU��O���J�[�l���Ǘ��O�̊����ݏ������Ŕ��������ꍇ
 *  �ɂ�false��Ԃ��j�D
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return false;
}

/*
 *  CPU��O�̔����������̃R���e�L�X�g�Ɗ����݁^CPU���b�N��Ԃ̎Q��
 *
 *  CPU��O�̔����������̃V�X�e����Ԃ��C�J�[�l�����s���łȂ��C�^�X�N�R
 *  ���e�L�X�g�ł���C�����݃��b�N��ԂłȂ��CCPU���b�N��ԂłȂ�����
 *  true�C�����łȂ�����false��Ԃ��iCPU��O���J�[�l���Ǘ��O�̊����ݏ�
 *  �����Ŕ��������ꍇ�ɂ�false��Ԃ��j�D
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
	return false;
}

/*
 *  CPU��O�G���g���iprc_support.S�j
 */
extern void exc_entry(void);

/*
 *  �����݃G���g���iprc_support.S�j
 */
extern void int_entry(void);

/*
 *  �v���Z�b�T�ˑ��̏�����
 */
extern void prc_initialize(void);

/*
 *  �v���Z�b�T�ˑ��̏I��������
 */
extern void prc_terminate(void);

/* �A�C�h�����[�v�̏��� */
#define idle_loop()						\
	{									\
		static volatile int count = 0;	\
		if(count++ >= 1u)				\
		{								\
			break;						\
		}								\
	}									\

/*
 *  �J�[�l���̏I�������̌ďo��
 *
 *  call_exit_kernel�́C�J�[�l���̏I�����ɌĂяo���ׂ����̂ŁC��^�X�N
 *  �R���e�L�X�g�ɐ؂芷���āC�J�[�l���̏I�������iexit_kernel�j���Ăяo
 *  ���D
 */
extern void call_exit_kernel(void);

/*
 *  atexit�̏����ƃf�X�g���N�^�̎��s
 */
Inline void
call_atexit(void)
{
	extern void    software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hook�ւ̃|�C���^���C��Uvolatile�w��̂���fp�ɑ�
	 *  �����Ă���g���̂́C0�Ƃ̔�r���œK���ō폜����Ȃ��悤�ɂ��邽
	 *  �߂ł���D
	 */
	if (fp != 0) {
		(*fp)();
	}
}

/*
 * �o�^����Ă��Ȃ���O����������ƌĂяo�����
 */
extern void default_exc_handler(void *p_excinf);

/*
 * ���o�^�̊����݂����������ꍇ�ɌĂяo�����
 */
extern void default_int_handler(void *p_excinf);

/*
 *  �^�[�Q�b�g�V�X�e���ˑ��̏�����
 */
extern void	target_initialize(void);

/*
 *  �f�B�X�p�b�`�J�n������
 */
extern void start_dispatch(void) NoReturn;

/*
 *  �^�[�Q�b�g�V�X�e���̏I��
 *
 *  �V�X�e�����I�����鎞�Ɏg���D
 */
extern void	target_exit(void);

#endif /* TOPPERS_MACRO_ONLY */


#endif /* TOPPERS_TARGET_CONFIG_H */
