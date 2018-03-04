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


#include "kernel_int.h"
#include <sil.h>
#include "target_timer.h"
#include "chip_timer.h"

/* �g�p�^�C�}�ԍ� */
#define TIMER_NO_MASTER		(HRT_TIMER_NO)
#define TIMER_NO_SLAVE		(HRT_TIMER_NO + 1)


/*
 *  ���W�X�^�A�h���X�̎Z�o�}�N��
 *
 *  ROM�e�ʂ����炷���߂Ƀe�[�u���������C�}�N���Œ��ڃA�h���X�Z�o����
 */
#define PER0_ADDR			((uint8_t __far *)0xF00F0)	/* ���ӃC�l�[�u���E���W�X�^ 0 */
#define TPS0_ADDR			((uint16_t __far *)0xF01B6)	/* �^�C�}�E�N���b�N�I�����W�X�^0 */
#define TS0L_ADDR			((uint16_t __far *)0xF01B2)	/* �^�C�}�E�`���l���J�n���W�X�^0 */
#define TT0L_ADDR			((uint16_t __far *)0xF01B4)	/* �^�C�}�E�`���l����~���W�X�^0 */

/* �^�C�}�E���[�h���W�X�^0 */
#define TMR0x_ADDR(x)		((uint16_t __far *)0xF0190 + (x))
/* �^�C�}�E�f�[�^���W�X�^ */
#define TDR0x_ADDR(x)	( x < 2 )? ((uint16_t __far *)0xFFF18 + (x)) : ((uint16_t __far *)0xFFF64 + (x))
/* �^�C�}�E�J�E���^���W�X�^ */
#define TCR0x_ADDR(x)		((uint16_t __far *)0xF0180 + (x))

/* �����ݗv���t���O���W�X�^ */
#if ( TAU_NUMBER >= 0 ) && ( TAU_NUMBER <= 3 )
#define IFx					((uint8_t __far *)0xFFFE2)		/* IF1L */
#define IFx_bit				( 0x01U << ( TAU_NUMBER + 4 ) )
#elif ( TAU_NUMBER == 4 )
#define IFx					((uint8_t*) __far 0xFFFE3)		/* IF1H */
#define IFx_bit				( 0x01U << 7 ) )
#elif ( TAU_NUMBER >= 5 ) && ( TAU_NUMBER <=7 )
#define IFx					((uint8_t __far *)0xFFFD0)		/* IF2L */
#define IFx_bit				( 0x01U << ( TAU_NUMBER - 5 ) )
#else
#error TAU_NUMBER is allowed from 0 to 7.
#endif /* TAU_NUMBER */


/* �J�E���g����ʕb�ւ̕Ԋ� */
#define COUNT2USEC( cnt )	( (cnt) )

/*
 *  ������\�^�C�}�̏���������
 */
void chip_hrt_timer_initialize(intptr_t exinf)
{
	/* TAU0�̗L���� */
	sil_wrb_mem( PER0_ADDR, sil_reb_mem( PER0_ADDR ) | 0x01U );

	/*
	 *  �^�C�}�N���b�N�̐ݒ�
	 *
	 *  CK00    1MHz(32����)
	 *  CK01    32MHz(�f�t�H���g�ݒ�)
	 *  CK02    16MHz(�f�t�H���g�ݒ�)
	 *  CK03    125kHz(�f�t�H���g�ݒ�)
	 */
	sil_wrh_mem( TPS0_ADDR , 0x0005U );

	/* �^�C�}��~ */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );

	/* �^�C�}�ݒ� */
	sil_wrh_mem( TDR0x_ADDR( TAU_NUMBER), TO_CLOCK(TIC_NUME, TIC_DENO) );
	sil_wrh_mem( TMR0x_ADDR( TAU_NUMBER) ,
				0x0000U   << 14U		/* CKS:CK00 */
				| 0x0000U << 12U		/* CCS:CKS�Ŏw�肵���N���b�N */
				| 0x0001U << 11U		/* MASTER:�}�X�^�[���� */
				| 0x0000U << 8U 		/* STS:�\�t�g�E�F�A�g���K */
				| 0x0000U << 6U 		/* CIS:Don't care */
				| 0x0000U << 0U			/* MD:�C���^�[�o�� */
			);


	/* �^�C�}�J�n */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );
}

/*
 *  ������\�^�C�}�̏I������
 */
void chip_hrt_timer_terminate(intptr_t exinf)
{
	/* �^�C�}��~ */
	sil_wrh_mem( TS0L_ADDR , 0x01U << TAU_NUMBER );
}

/*
 *  ������\�^�C�}�ւ̊����݃^�C�~���O�̐ݒ�
 */
void chip_hrt_set_event(HRTCNT hrtcnt)
{

}

/*
 *  ������\�^�C�}�����݂̗v��
 */
void chip_hrt_raise_event(void)
{
	
}

/*
 *  ������\�^�C�}�����݃n���h��
 */
void chip_hrt_handler(void)
{
}

