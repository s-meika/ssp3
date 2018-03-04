/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010,2016 by Meika Sugimoto
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
 *		�V�X�e����ԊǗ��@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */

#ifndef LOG_LOC_CPU_ENTER
#define LOG_LOC_CPU_ENTER()
#endif /* LOG_LOC_CPU_ENTER */

#ifndef LOG_LOC_CPU_LEAVE
#define LOG_LOC_CPU_LEAVE(ercd)
#endif /* LOG_LOC_CPU_LEAVE */

#ifndef LOG_UNL_CPU_ENTER
#define LOG_UNL_CPU_ENTER()
#endif /* LOG_UNL_CPU_ENTER */

#ifndef LOG_UNL_CPU_LEAVE
#define LOG_UNL_CPU_LEAVE(ercd)
#endif /* LOG_UNL_CPU_LEAVE */

#ifndef LOG_DIS_DSP_ENTER
#define LOG_DIS_DSP_ENTER()
#endif /* LOG_DIS_DSP_ENTER */

#ifndef LOG_DIS_DSP_LEAVE
#define LOG_DIS_DSP_LEAVE(ercd)
#endif /* LOG_DIS_DSP_LEAVE */

#ifndef LOG_ENA_DSP_ENTER
#define LOG_ENA_DSP_ENTER()
#endif /* LOG_ENA_DSP_ENTER */

#ifndef LOG_ENA_DSP_LEAVE
#define LOG_ENA_DSP_LEAVE(ercd)
#endif /* LOG_ENA_DSP_LEAVE */

#ifndef LOG_SNS_CTX_ENTER
#define LOG_SNS_CTX_ENTER()
#endif /* LOG_SNS_CTX_ENTER */

#ifndef LOG_SNS_CTX_LEAVE
#define LOG_SNS_CTX_LEAVE(state)
#endif /* LOG_SNS_CTX_LEAVE */

#ifndef LOG_SNS_LOC_ENTER
#define LOG_SNS_LOC_ENTER()
#endif /* LOG_SNS_LOC_ENTER */

#ifndef LOG_SNS_LOC_LEAVE
#define LOG_SNS_LOC_LEAVE(state)
#endif /* LOG_SNS_LOC_LEAVE */

#ifndef LOG_SNS_DSP_ENTER
#define LOG_SNS_DSP_ENTER()
#endif /* LOG_SNS_DSP_ENTER */

#ifndef LOG_SNS_DSP_LEAVE
#define LOG_SNS_DSP_LEAVE(state)
#endif /* LOG_SNS_DSP_LEAVE */

#ifndef LOG_SNS_DPN_ENTER
#define LOG_SNS_DPN_ENTER()
#endif /* LOG_SNS_DPN_ENTER */

#ifndef LOG_SNS_DPN_LEAVE
#define LOG_SNS_DPN_LEAVE(state)
#endif /* LOG_SNS_DPN_LEAVE */

#ifndef LOG_SNS_KER_ENTER
#define LOG_SNS_KER_ENTER()
#endif /* LOG_SNS_KER_ENTER */

#ifndef LOG_SNS_KER_LEAVE
#define LOG_SNS_KER_LEAVE(state)
#endif /* LOG_SNS_KER_LEAVE */

/*
 *  CPU���b�N��Ԃւ̈ڍs�mNGKI3538�n
 */
#ifdef TOPPERS_loc_cpu

ER
loc_cpu(void)
{
	ER		ercd;

	LOG_LOC_CPU_ENTER();

	if (!sense_lock()) {						/*�mNGKI2731�n*/
		lock_cpu();								/*�mNGKI2730�n*/
	}
	ercd = E_OK;

	LOG_LOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_loc_cpu */

/*
 *  CPU���b�N��Ԃ̉����mNGKI3539�n
 *
 *  CPU���b�N���́C�f�B�X�p�b�`���K�v�ƂȂ�T�[�r�X�R�[�����Ăяo����
 *  �Ƃ͂ł��Ȃ����߁CCPU���b�N��Ԃ̉������Ƀf�B�X�p�b�`�����N������
 *  �K�v�͂Ȃ��D
 */
#ifdef TOPPERS_unl_cpu

ER
unl_cpu(void)
{
	ER		ercd;

	LOG_UNL_CPU_ENTER();

	if (sense_lock()) {							/*�mNGKI2738�n*/
		unlock_cpu();							/*�mNGKI2737�n*/
	}
	ercd = E_OK;

	LOG_UNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_unl_cpu */

/*
 *  �f�B�X�p�b�`�̋֎~�mNGKI2740�n
 */
#ifdef TOPPERS_dis_dsp

ER
dis_dsp(void)
{
	ER		ercd;
	
	LOG_DIS_DSP_ENTER();
	CHECK_TSKCTX_UNL();							/*�mNGKI2741�n�mNGKI2742�n*/

	
	lock_cpu();
	disdsp = true;
	ercd = E_OK;
	unlock_cpu();
	
  error_exit:
	LOG_DIS_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_dis_dsp */

/*
 *  �f�B�X�p�b�`�̋��mNGKI2746�n
 */
#ifdef TOPPERS_ena_dsp

ER
ena_dsp(void)
{
	ER		ercd;
	uint_t	tskipri;
	
	LOG_ENA_DSP_ENTER();							/*�mNGKI2747�n�mNGKI2748�n*/
	CHECK_TSKCTX_UNL();
	
	lock_cpu();
	disdsp = false;
	
	tskipri = search_schedtsk();
	if (tskipri < runtsk_curpri) {
		run_task(tskipri);
	}
	ercd = E_OK;
	unlock_cpu();
	
  error_exit:
	LOG_ENA_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ena_dsp */

/*
 *  �R���e�L�X�g�̎Q�ƁmNGKI2752�n
 */
#ifdef TOPPERS_sns_ctx

bool_t
sns_ctx(void)
{
	bool_t	state;
	
	LOG_SNS_CTX_ENTER();
	state = sense_context() ? true : false;
	LOG_SNS_CTX_LEAVE(state);
	
	return(state);
}

#endif /* TOPPERS_sns_ctx */

/*
 *  CPU���b�N��Ԃ̎Q�ƁmNGKI2754�n
 */
#ifdef TOPPERS_sns_loc

bool_t
sns_loc(void)
{
	bool_t	state;
	
	LOG_SNS_LOC_ENTER();
	state = sense_lock() ? true : false;
	LOG_SNS_LOC_LEAVE(state);
	
	return(state);
}

#endif /* TOPPERS_sns_loc */

/*
 *  �f�B�X�p�b�`�֎~��Ԃ̎Q�ƁmNGKI2756�n
 */
#ifdef TOPPERS_sns_dsp

bool_t
sns_dsp(void)
{
	bool_t	state;
	
	LOG_SNS_DSP_ENTER();
	state = disdsp;
	LOG_SNS_DSP_LEAVE(state);
	
	return(state);
}

#endif /* TOPPERS_sns_dsp */

/*
 *  �f�B�X�p�b�`�ۗ���Ԃ̎Q�ƁmNGKI2756�n
 */
#ifdef TOPPERS_sns_dpn

bool_t
sns_dpn(void)
{
	bool_t	state;
	
	LOG_SNS_DPN_ENTER();
	state = ((sense_context()) || (sense_lock()) || disdsp) ?
		true : false;
	LOG_SNS_DPN_LEAVE(state);
	
	return(state);
}

#endif /* TOPPERS_sns_dpn */

/*
 *  �J�[�l���񓮍��Ԃ̎Q��
 *  �J�[�l���񓮍��Ԃ̎Q��
 */
#ifdef TOPPERS_sns_ker

bool_t
sns_ker(void)
{
	bool_t	state;
	
	LOG_SNS_KER_ENTER();
	state = kerflg ? false : true;
	LOG_SNS_KER_LEAVE(state);
	
	return(state);
}

#endif /* TOPPERS_sns_ker */
