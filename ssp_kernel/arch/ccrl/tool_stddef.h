/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2016 by Meika Sugimoto
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
 *		t_stddef.h�̊J�����ˑ����iCC-RL�p�j
 */

#ifndef TOPPERS_TOOL_STDDEF_H
#define TOPPERS_TOOL_STDDEF_H

/*
 *  �R���p�C���̊g���@�\�̂��߂̃}�N����`
 */
#ifndef __cplusplus					/* C++�ɂ�inline ������ */
#if __STDC_VERSION__ < 199901L		/* C99�ɂ�inline ������ */
#define inline	 __inline			/* �C�����C���֐� */
#endif /* __STDC_VERSION__ < 199901L */
#endif /* __cplusplus */

#define Inline		static __inline	/* �C�����C���֐� */

#ifndef __cplusplus					/* C++�ɂ�asm������ */
#define asm		__asm__				/* �C�����C���A�Z���u�� */
#endif /* __cplusplus */

#define Asm		__asm /* �C�����C���A�Z���u���i�œK���}�~�j*/

#define NoReturn
									/* ���^�[�����Ȃ��֐� */

/*
 *  �J�����̕W���C���N���[�h�t�@�C���̗��p
 *
 *  NULL�̒�`��stddef.h����CINT_MAX�CINT_MIN�CUINT_MAX�CLONG_MAX�C
 *  LONG_MIN�CULONG_MAX�CCHAR_BIT�̒�`��limits.h�����荞�ށD
 *
 *  C++/EC++�ł́C�W���d�l��͂����̃C���N���[�h�t�@�C�����p�ӂ����
 *  ����Ƃ͌���Ȃ��̂Œ��ӂ��K�v�ł���i�قƂ�ǂ̊J�����ŗp�ӂ���
 *  �Ă���j�D
 */
#ifndef TOPPERS_MACRO_ONLY
#include <stdint.h>
#include <limits.h>
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  CCRL�ł�C99���T�|�[�g���Ă��邽�߁Cstdint.h�̑�p�ƂȂ��`�͕s�v
 *
 */

/*
 *  �R���p�C���ˑ��̃f�[�^�^�̐����萔�����}�N��
 */
#ifndef INT8_C
#define INT8_C(val)			(val)
#endif /* INT8_C */

#ifndef UINT8_C
#define UINT8_C(val)		(val ## U)
#endif /* UINT8_C */

#ifndef INT16_C
#define INT16_C(val)		(val)
#endif /* INT16_C */

#ifndef UINT16_C
#define UINT16_C(val)		(val ## U)
#endif /* UINT16_C */

#ifndef INT32_C
#define INT32_C(val)		(val)
#endif /* INT32_C */

#ifndef UINT32_C
#define UINT32_C(val)		(val ## U)
#endif /* UINT32_C */

#ifndef INT64_C
#define INT64_C(val)		(val ## LL)
#endif /* INT64_C */

#ifndef UINT64_C
#define UINT64_C(val)		(val ## ULL)
#endif /* UINT64_C */

/*
 *  CCRL�ł�C99���T�|�[�g���Ă��邽�߁C�R���p�C���ˑ��̃f�[�^�^�Ɋi�[�ł���ő�l�ƍŏ��l�̒�`�̒�`�͕s�v
 */


/*
 *  ���������_�^�Ɋւ����`
 *
 *  TOPPERS_STDFLOAT_TYPE1: float��IEEE754�����̒P���x���������_���C
 *							double���{���x���������_���̏ꍇ
 */
#ifdef TOPPERS_STDFLOAT_TYPE1
#ifndef TOPPERS_MACRO_ONLY

typedef float		float32_t;			/* IEEE754�����̒P���x���������_�� */
typedef double		double64_t;			/* IEEE754�����̔{���x���������_�� */

#endif /* TOPPERS_MACRO_ONLY */

#define FLOAT32_MIN		1.17549435e-38F
#define FLOAT32_MAX		3.40282347e+38F
#define DOUBLE64_MIN	2.2250738585072014e-308
#define DOUBLE64_MAX	1.7976931348623157e+308

#endif /* TOPPERS_STDFLOAT_TYPE1 */

/*
 *  �󃉃x���̒�`
 *    Visual Studio�ł͑傫���[���̔z��̓R���p�C���G���[�ɂȂ邽�߁A
 *    �����ŕʓr��`����B
 */
#define TOPPERS_EMPTY_LABEL(x,y) x y[1]

#endif /* TOPPERS_TOOL_STDDEF_H */
