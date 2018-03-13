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

/* �J�[�l�������ˑ���(RL78/G13�p) */

#ifndef TOPPERS_CHIP_KERNEL_IMPL_H
#define TOPPERS_CHIP_KERNEL_IMPL_H

/*
 *  �����ݔԍ��C�����݃n���h���ԍ��̔���
 *
 *  0��INTNO�̔�r�͈Ӗ����Ȃ����߁C�x������̂��߃R�����g�A�E�g���Ă���
 */
#define	VALID_INTNO(intno)	(/* 0U <= (intno) && */ (intno) <= (INTNO)RL78_G13_INTNO_MAX)
#define VALID_INHNO(inhno)	VALID_INTNO((INTNO)(inhno))

/* �J�[�l���̃R�A�ˑ����̃C���N���[�h */
#include "prc_kernel_impl.h"

/*
 *  ������\�^�C�}�̃^�C�}����
 *
 *  �^�C�}������2^32�̏ꍇ�ɂ́C���̃}�N�����`���Ȃ��D
 */
#define TCYC_HRTCNT		(65535)

/*
 *  ������\�^�C�}�̃J�E���g�l�̐i�ݕ�
 */
#define TSTEP_HRTCNT	(1U)

/*
 *  �`�b�v�ˑ����Ŏg�p�ł��銄���ݗv�����C���̊����ݑ���
 */
#define TA_POSEDGE    ( 0x04 )
#define TA_NEGEDGE    ( 0x08 )


/*
 *  �����݋@�\�̐�����
 */

typedef struct
{
	volatile __far uint8_t* address;		/* �A�h���X */
	uint8_t				bitmask;			/* �r�b�g�ʒu */
} RL78G13_INTREG_INFO;

typedef struct
{
	RL78G13_INTREG_INFO request;			/* �v�����W�X�^ */
	RL78G13_INTREG_INFO mask;				/* �}�X�N���W�X�^ */
	RL78G13_INTREG_INFO pri1;				/* �D��x1 */
	RL78G13_INTREG_INFO pri2;				/* �D��x2 */
	RL78G13_INTREG_INFO extint_posedge;		/* �O�����荞�ݗ����オ��G�b�W�ݒ� */
	RL78G13_INTREG_INFO extint_negedge;	/* �O�����荞�ݗ���������G�b�W�ݒ� */
} RL78G13_INTCTL_INFO;


/* �����ݐ�����e�[�u�� */
extern RL78G13_INTCTL_INFO const intctl_reg_table[RL78_G13_INTNO_MAX+1];


/* �����݃n���h������`�ς݂����i�[����z�� */
extern const uint32_t _kernel_bitpat_cfgint[];

/*
 *  �`�b�v�ˑ����̏�����
 */
 extern void chip_initialize(void);

/*
 *  �����ݗv���֎~�t���O�̃Z�b�g
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���Z�b�g���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
Inline void
disable_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far mask_reg = &intctl_reg_table[intno].mask;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(mask_reg->address) &= ~(mask_reg->bitmask);
}

/*
 *  �����ݗv���֎~�t���O�̃N���A
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
Inline void
enable_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far mask_reg = &intctl_reg_table[intno].mask;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(mask_reg->address) |= mask_reg->bitmask;
}

/*
 *  �����ݗv���̃N���A
 */
Inline void
clear_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far request_reg = &intctl_reg_table[intno].request;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	*(request_reg->address) &= ~(request_reg->bitmask);
}

/*
 *  �����ݗv���̃`�F�b�N
 */
Inline bool_t
probe_int(INTNO intno)
{
	const RL78G13_INTREG_INFO * __far request_reg = &intctl_reg_table[intno].request;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	return ((*(request_reg->address) &request_reg->bitmask) != 0);
}


/*
 *  �����ݗv�����N���A�ł����Ԃ��H
 */
Inline bool_t check_intno_clear(INTNO intno)
{
	/* ��ɃN���A�͉\ */
	return true;
}

/*
 * �����ݗv�����C�����ݒ肳��Ă��邩�̃`�F�b�N
 */
Inline bool_t check_intno_cfg(INTNO intno)
{
	return (_kernel_bitpat_cfgint[(intno >> 5)] & (1U << (intno & 0x01FU))) != 0U;
}


/*
 *  �����݃n���h���̐ݒ�
 *
 *  �x�N�g���ԍ�inhno�̊����݃n���h���̏o���������̔Ԓn��int_entry��
 *  �ݒ肷��D
 */
Inline void
define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  �����ݗv�����C�������̐ݒ�
 */
Inline void
config_int(INTNO intno, ATR intatr, PRI intpri)
{
	const RL78G13_INTREG_INFO * __far pri_reg1 = &intctl_reg_table[intno].pri1;
	const RL78G13_INTREG_INFO * __far pri_reg2 = &intctl_reg_table[intno].pri2;
	const RL78G13_INTREG_INFO * __far ext_pos_reg = &intctl_reg_table[intno].extint_posedge;
	const RL78G13_INTREG_INFO * __far ext_neg_reg = &intctl_reg_table[intno].extint_negedge;
	
	assert(intno <= RL78_G13_INTNO_MAX);
	
	/* �����ݗD��x */
	if(intpri == 1)
	{
		*(pri_reg1->address) |= pri_reg1->bitmask;
		*(pri_reg2->address) &= ~(pri_reg2->bitmask);
	}
	else if(intpri == 2)
	{
		*(pri_reg1->address) &= ~(pri_reg1->bitmask);
		*(pri_reg2->address) |= pri_reg2->bitmask;
	}
	else if(intpri == 3)
	{
		*(pri_reg1->address) |= pri_reg1->bitmask;
		*(pri_reg2->address) |= pri_reg2->bitmask;
	}
	else	/* 1 �` 3�ȊO */
	{
		*(pri_reg1->address) &= ~(pri_reg1->bitmask);
		*(pri_reg2->address) &= ~(pri_reg2->bitmask);
	}
	
	/* �����݃G�b�W */
	if((intatr & TA_POSEDGE) && ext_pos_reg)
	{
		*(ext_pos_reg->address) |= ext_pos_reg->bitmask;
	}
	if((intatr & TA_NEGEDGE) && ext_neg_reg)
	{
		*(ext_neg_reg->address) |= ext_neg_reg->bitmask;
	}
	
	
	/* �����݋��� */
	if(intatr & TA_ENAINT)
	{
		enable_int(intno);
	}
	
}

/*
 *  �����݃n���h���̓����ŕK�v��IRC����
 */
Inline void
i_begin_int(INTNO intno)
{
	/* �������Ȃ��C�����ݗv���͎����N���A */
}

/*
 *  �����݃n���h���̏o���ŕK�v��IRC����
 */
Inline void
i_end_int(INTNO intno)
{
	/* �������Ȃ� */
}



#endif /* TOPPERS_CHIP_KERNEL_IMPL_H */
