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


/*
 *		�V���A���h���C�o�̃^�[�Q�b�g�ˑ����iRL78/G13�p�j
 *
 *		�{�h���C�o�̎g�p����SAU0/1�����ӃC�l�[�u�����W�X�^0(PER0)�ŗL��������Ă��邱�Ƃ�O��Ƃ���
 */
 
#ifndef TOPPERS_CHIP_SERIAL_H
#define TOPPERS_CHIP_SERIAL_H

#include "kernel_impl.h"

#define TNUM_UART_CH	(4)

#ifndef TOPPERS_MACRO_ONLY
typedef struct
{
	__far uint16_t *SMR_tx;
	__far uint16_t *SMR_rx;
	__far uint16_t *SCR_tx;
	__far uint16_t *SCR_rx;
	__far uint16_t *SDR_tx;
	__far uint16_t *SDR_rx;
	__far uint16_t *SIR;
	__far uint16_t *SSR_tx;
	__far uint16_t *SSR_rx;
	__far uint8_t  *SPS;
	__far uint16_t *SS;
	__far uint16_t *ST;
	__far uint16_t *SOE;
	__far uint16_t *SO;
} SAU_REGADDRS;

/*
 *  �V���A���|�[�g�̊Ǘ��u���b�N
 */
typedef struct sio_port_control_block {
	ID port;
	const SAU_REGADDRS *regaddrs;
	intptr_t exinf;
} SIOPCB;


/*
 *  UART�̏�����
 */
void sau_init(uint_t ch);

/*
 *  �჌�x��1�����o��
 */
extern void sau_log_output(uint_t ch, char c);


#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CHIP_SERIAL_H */
