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
 *		RL78/G13�}�C�R���ˑ��̒�`
 */

#ifndef TOPPERS_RL78_G13_H
#define TOPPERS_RL78_G13_H

#define RL78_G13_INTNO_MIN		(0)
#define RL78_G13_INTNO_MAX		(53)

/*
 *  �����݃x�N�^�ԍ���`
 */
#define INTWDTI			(0)
#define INTLVI			(1)
#define INTP0			(2)
#define INTP1			(3)
#define INTP2			(4)
#define INTP3			(5)
#define INTP4			(6)
#define INTP5			(7)
#define INTST2			(8)
#define INTCSI20		(8)
#define INTIIC20		(8)
#define INTSR2			(9)
#define INTCSI21		(9)
#define INTIIC21		(9)
#define INTSRE2			(10)
#define INTTM11H		(10)
#define INTDMA0			(11)
#define INTDMA1			(12)
#define INTST0			(13)
#define INTCSI00		(13)
#define INTIIC00		(13)
#define INTSR0			(14)
#define INTCSI01		(14)
#define INTIIC01		(14)
#define INTSRE0			(15)
#define INTTM01H		(15)
#define INTST1			(16)
#define INTCSI10		(16)
#define INTIIC10		(16)
#define INTSR1			(17)
#define INTCSI11		(17)
#define INTIIC11		(17)
#define INTSRE1			(18)
#define INTTM03H		(18)
#define INTIICA0		(19)
#define INTTM00			(20)
#define INTTM01			(21)
#define INTTM02			(22)
#define INTTM03			(23)
#define INTAD			(24)
#define INTRTC			(25)
#define INTIT			(26)
#define INTKR			(27)
#define INTST3			(28)
#define INTCSI30		(28)
#define INTIIC30		(28)
#define INTSR3			(29)
#define INTCSI31		(29)
#define INTIIC31		(29)
#define INTTM13			(30)
#define INTTM04			(31)
#define INTTM05			(32)
#define INTTM06			(33)
#define INTTM07			(34)
#define INTP6			(35)
#define INTP7			(36)
#define INTP8			(37)
#define INTP9			(38)
#define INTP10			(39)
#define INTP11			(40)
#define INTTM10			(41)
#define INTTM11			(42)
#define INTTM12			(43)
#define INTSRE3			(44)
#define INTTM13H		(44)
#define INTMD			(45)
#define INTIICA1		(46)
#define INTFL			(47)
#define INTDMA2			(48)
#define INTDMA3			(49)
#define INTTM14			(50)
#define INTTM15			(51)
#define INTTM16			(52)
#define INTTM17			(53)



#endif /* TOPPERS_RL78_G13_H */
