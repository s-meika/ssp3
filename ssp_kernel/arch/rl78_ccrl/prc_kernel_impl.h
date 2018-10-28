/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2017 by Meika Sugimoto
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

#ifndef PRC_KERNEL_IMPL_H
#define PRC_KERNEL_IMPL_H

#include "builtin.h"

/*
 *  CPU��O�n���h���ԍ��͈̔͂̔���
 */
#define VALID_EXCNO(excno)	(void)0

/*
 *  ��^�X�N�R���e�L�X�g�p�̃X�^�b�N�����l
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((istk) + (istksz)))

/* �S�����݉������̊����݃��x���}�X�N */
#define IIPM_ENAALL   ( 0U )

/*
 *  �����݃n���h���̓��������̐����}�N��
 */

extern void _kernel_interrupt(const uint16_t inhno, void (*inthdr)(void));
#define INT_ENTRY(inhno, inthdr)	inthdr
#define INTHDR_ENTRY(inhno, intno, inthdr)

/*
 *  CPU��O�n���h���̓��������̐����}�N��
 */
#define EXC_ENTRY(excno, exchdr)	exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr)	\
	Asm("\tPUSH AX");	\
	Asm("\tPUSH BC");	\
	Asm("\tPUSH DE");	\
	Asm("\tPUSH HL");	\
	Asm("\tPUSH ES");	\
	Asm("\tPUSH CS");	\
	Asm("\tMOV X, #" ## inhno);	\
	Asm("\tMOVW BC, !!_" ## inthdr);	\
	Asm("\tMOVW ES, HIGHW(, _" ## inthdr ## ")");	\
	Asm("\tBR !!__kernel_int_entry");

#define ISP_MASK	(0x06U)
	
/* ��ԊǗ��p�ϐ� */
extern bool_t	lock_flag;
extern PRI		saved_iipm;
extern uint8_t	intnest;


/*
 *  �v���Z�b�T�ˑ����̏�����
 */
extern void prc_initialize(void);

/*
 *  �R���e�L�X�g�̎Q��
 */
Inline bool_t
sense_context(void)
{
	return (intnest > 0U);
}

/*
 *  CPU���b�N��Ԃւ̑J��
 */
Inline void
lock_cpu(void)
{
	unsigned char current_psw;
	
	__DI();
	
	current_psw = __get_psw();
	
	saved_iipm = (current_psw & ISP_MASK) >> 0x1U;
	
	__set_psw(current_psw & ~ISP_MASK | (TIPM_LOCK << 1U));

	lock_flag = true;
	
	__EI();
}

/*
 *  CPU���b�N��Ԃւ̈ڍs�i�f�B�X�p�b�`�ł����ԁj
 */
#define lock_cpu_dsp()		lock_cpu()

/*
 *  CPU���b�N��Ԃ̉���
 */
Inline void
unlock_cpu(void)
{
	unsigned char current_psw;
	
	__DI();
	
	current_psw = __get_psw();
	lock_flag = false;
	
	__set_psw(current_psw & ~ISP_MASK | (saved_iipm << 1U));

	__EI();
}

/*
 *  CPU���b�N��Ԃ̉����i�f�B�X�p�b�`�ł����ԁj
 */
#define unlock_cpu_dsp()	unlock_cpu()

/*
 *  CPU���b�N��Ԃ̎Q��
 */
Inline bool_t
sense_lock(void)
{
	return lock_flag;
}

/*
 *  �����ݗD��x�}�X�N�̐ݒ�
 */
Inline void
t_set_ipm(PRI intpri)
{
	if(lock_flag)
	{
		saved_iipm = intpri;
	}
	else
	{
		unsigned char current_psw = __get_psw();
		__set_psw(current_psw & ~0x06U | (intpri << 1U));
	}
}

/*
 *  �����ݗD��x�}�X�N�̎Q��
 */
Inline PRI
t_get_ipm(void)
{
	PRI ipm;
	
	if(lock_flag)
	{
		ipm = saved_iipm;
	}
	else
	{
		unsigned char current_psw = __get_psw();
		ipm = (current_psw >> 0x1U) & 0x03U;
	}

	return ipm;
}

/*
 *  �f�B�X�p�b�`���̓���J�n
 */
extern void start_dispatch(void);





/*
 *  �ō��D�揇�ʃ^�X�N�ւ̃f�B�X�p�b�`
 */
extern void	dispatch(void);

/*
 *  ��^�X�N�R���e�L�X�g����̃f�B�X�p�b�`�v��
 */
#define request_dispatch()

/*
 *  ���݂̃R���e�L�X�g���̂Ăăf�B�X�p�b�`
 */
extern void	exit_and_dispatch(void);


/*
 *  CPU��O�̔����������̃R���e�L�X�g�Ɗ����݂̃}�X�N��Ԃ̎Q��
 *
 *  CPU��O�̔����������̃V�X�e����Ԃ��C�J�[�l�����̃N���e�B�J���Z�N�V��
 *  ���̎��s���łȂ��C�S�����݃��b�N��ԂłȂ��CCPU���b�N��ԂłȂ��C�J�[
 *  �l���Ǘ��O�̊����݃n���h�����s���łȂ��C�J�[�l���Ǘ��O��CPU��O�n��
 *  �h�����s���łȂ��C�^�X�N�R���e�L�X�g�ł���C�����ݗD��x�}�X�N���S
 *  �����ł��鎞��true�C�����łȂ�����false��Ԃ��D
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(true);
}

/*
 *  �����݃n���h���o��������
 */
Inline void
int_handler_entry(void)
{
}

/*
 *  CPU��O�n���h���o��������
 */
Inline void
exc_handler_entry(void)
{
}

/*
 *  CPU��O�n���h���̐ݒ�
 *
 *  �x�N�g���ԍ�excno��CPU��O�n���h���̏o���������̔Ԓn��exc_entry�ɐ�
 *  �肷��D
 */
Inline void
define_exc(EXCNO excno, FP exc_entry)
{
	/* CPU��O�̓T�|�[�g���Ȃ� */
}

/*
 *  �A�C�h�����[�v
 */
extern void idle_loop(void);


/*
 *  �J�[�l���̏I�������̌ďo��
 */
extern void call_exit_kernel(void) NoReturn;



#endif /* PRC_KERNEL_IMPL_H */
