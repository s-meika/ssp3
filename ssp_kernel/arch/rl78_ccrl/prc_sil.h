/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
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

/*
 *		sil.h�̃^�[�Q�b�g�ˑ����iRL78�p�j
 */

#ifndef TOPPERS_PRC_SIL_H
#define TOPPERS_PRC_SIL_H

#ifndef TOPPERS_MACRO_ONLY

#include <builtin.h>
#include "prc_sil.h"

/*
 *  �S�����݃��b�N��Ԃ̐���
 */
#define SIL_PRE_LOC		bool_t int_enable
#define SIL_LOC_INT()	\
	int_enable = ( __get_psw() & 0x80U != 0U )? true : false
#define SIL_UNL_INT()	\
	if( int_enable )	\
	{					\
		__EI();			\
	}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �v���Z�b�T�̃G���f�B�A����`
 *    RL78�̓��g���G���f�B�A��
 */
#define SIL_ENDIAN_LITTLE			/* ���g���G���f�B�A�� */

#define TOPPERS_OMIT_SIL_ACCESS
/*
 *  8�r�b�g�P�ʂ̓Ǐo���^������
 */

Inline uint8_t
sil_reb_mem(const uint8_t __far *mem)
{
	uint8_t	data;

	data = *((const volatile __far uint8_t *) mem);
	return(data);
}

Inline void
sil_wrb_mem(uint8_t __far *mem, uint8_t data)
{
	*((volatile uint8_t *) mem) = data;
}

/*
 *  16�r�b�g�P�ʂ̓Ǐo���^������
 */

 Inline uint16_t
sil_reh_mem(const __far uint16_t *mem)
{
	uint16_t	data;

	data = *((const volatile uint16_t *) mem);
	return(data);
}

Inline void
sil_wrh_mem(uint16_t __far *mem, uint16_t data)
{
	*((volatile uint16_t *) mem) = data;
}

/*
 *  32�r�b�g�P�ʂ̓Ǐo���^������
 */

Inline uint32_t
sil_rew_mem(const __far uint32_t *mem)
{
	uint32_t	data;

	data = *((const volatile uint32_t *) mem);
	return(data);
}

Inline void
sil_wrw_mem(uint32_t __far *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = data;
}
#endif /* TOPPERS_PRC_SIL_H */
