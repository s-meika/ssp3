/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010-2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2011-2012 by Meika Sugimoto
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

/*
 *		���ׂĂ̊֐����R���p�C�����邽�߂̒�`
 */

#ifndef TOPPERS_ALLFUNC_H
#define TOPPERS_ALLFUNC_H

/* startup.c */
#define TOPPERS_sta_ker
#define TOPPERS_ext_ker

/* task.c */
#define TOPPERS_get_ipriself
#define TOPPERS_get_ipri
#define TOPPERS_tskini
#define TOPPERS_tsksched
#define TOPPERS_tskrun
#define TOPPERS_tskdsp
#define TOPPERS_tskact
#define TOPPERS_tskdmt


/* task_manage.c */
#define TOPPERS_act_tsk

/* sys_manage.c */
#define TOPPERS_loc_cpu
#define TOPPERS_unl_cpu
#define TOPPERS_dis_dsp
#define TOPPERS_ena_dsp
#define TOPPERS_sns_ctx
#define TOPPERS_sns_loc
#define TOPPERS_sns_dsp
#define TOPPERS_sns_dpn
#define TOPPERS_sns_ker

/* interrupt.c */
#define TOPPERS_intini
#define TOPPERS_dis_int
#define TOPPERS_ena_int
#define TOPPERS_clr_int
#define TOPPERS_ras_int
#define TOPPERS_prb_int

/* exception.c */
#define TOPPERS_excini

/* time_event.c */
#define TOPPERS_tmevtini
#define TOPPERS_tmevtenq
#define TOPPERS_tmevtdeq
#define TOPPERS_sig_tim

/* cyclic.c */
#define TOPPERS_cycini
#define TOPPERS_sta_cyc
#define TOPPERS_stp_cyc
#define TOPPERS_cyccal

/* alarm.c */
#define TOPPERS_almini
#define TOPPERS_sta_alm
#define TOPPERS_stp_alm
#define TOPPERS_almcal

/* time_manage.c */
#define TOPPERS_get_tim

/* eventflag.c */
#define TOPPERS_iniflg
#define TOPPERS_flgcnd
#define TOPPERS_set_flg
#define TOPPERS_clr_flg
#define TOPPERS_pol_flg

/* dataqueue.c */
#define TOPPERS_dtqini
#define TOPPERS_dtqenq
#define TOPPERS_dtqdeq
#define TOPPERS_psnd_dtq
#define TOPPERS_prcv_dtq


#endif /* TOPPERS_ALLFUNC_H */
