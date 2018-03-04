/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2010-2011,2016 by Meika Sugimoto
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
 *		�����݊Ǘ��@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "interrupt.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_DIS_INT_ENTER
#define LOG_DIS_INT_ENTER(intno)
#endif /* LOG_DIS_INT_ENTER */

#ifndef LOG_DIS_INT_LEAVE
#define LOG_DIS_INT_LEAVE(ercd)
#endif /* LOG_DIS_INT_LEAVE */

#ifndef LOG_ENA_INT_ENTER
#define LOG_ENA_INT_ENTER(intno)
#endif /* LOG_ENA_INT_ENTER */

#ifndef LOG_ENA_INT_LEAVE
#define LOG_ENA_INT_LEAVE(ercd)
#endif /* LOG_ENA_INT_LEAVE */

#ifndef LOG_CLR_INT_ENTER
#define LOG_CLR_INT_ENTER(intno)
#endif /* LOG_CLR_INT_ENTER */

#ifndef LOG_CLR_INT_LEAVE
#define LOG_CLR_INT_LEAVE(ercd)
#endif /* LOG_CLR_INT_LEAVE */

#ifndef LOG_RAS_INT_ENTER
#define LOG_RAS_INT_ENTER(intno)
#endif /* LOG_RAS_INT_ENTER */

#ifndef LOG_RAS_INT_LEAVE
#define LOG_RAS_INT_LEAVE(ercd)
#endif /* LOG_RAS_INT_LEAVE */

#ifndef LOG_PRB_INT_ENTER
#define LOG_PRB_INT_ENTER(intno)
#endif /* LOG_PRB_INT_ENTER */

#ifndef LOG_PRB_INT_LEAVE
#define LOG_PRB_INT_LEAVE(ercd)
#endif /* LOG_PRB_INT_LEAVE */

/*
 *  �����ݔԍ��͈̔͂̔���
 */
#ifndef VALID_INTNO_DISINT
#define VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)
#endif /* VALID_INTNO_DISINT */

#ifndef VALID_INTNO_CLRINT
#define VALID_INTNO_CLRINT(intno)	VALID_INTNO(intno)
#endif /* VALID_INTNO_CLRINT */

#ifndef VALID_INTNO_RASINT
#define VALID_INTNO_RASINT(intno)	VALID_INTNO(intno)
#endif /* VALID_INTNO_RASINT */

#ifndef VALID_INTNO_PRBINT
#define VALID_INTNO_PRBINT(intno)	VALID_INTNO(intno)
#endif /* VALID_INTNO_PRBINT */

#ifndef VALID_INTNO_CREISR
#define VALID_INTNO_CREISR(intno)	VALID_INTNO(intno)
#endif /* VALID_INTNO_CREISR */

/* 
 *  �����݊Ǘ��@�\�̏�����
 */
#ifdef TOPPERS_intini
#ifndef OMIT_INITIALIZE_INTERRUPT

void
initialize_interrupt(void)
{
	uint_t			i;
	
	for (i = 0U; i < tnum_inhno; i++) {
		define_inh(inhinib_inhno[i], (FP)(inhinib_entry[i]));
	}
	for (i = 0U; i < tnum_intno; i++) {
		config_int(intinib_intno[i], intinib_intatr[i], intinib_intpri[i]);
	}
}

#endif /* OMIT_INITIALIZE_INTERRUPT */
#endif /* TOPPERS_intini */

/*
 *  �����݂̋֎~�mNGKI3555�n
 */
#ifdef TOPPERS_dis_int
#ifdef TOPPERS_TARGET_SUPPORT_DIS_INT					/*�mNGKI3093�n*/

ER
dis_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;
	
	LOG_DIS_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_DISINT(intno));		/*�mNGKI3083�n�mNGKI3087�n*/
	
	locked = sense_lock();
	
	if (!locked) {
		lock_cpu();
	}
	
	if (check_intno_cfg(intno)) {
		disable_int(intno);						/*�mNGKI3086�n*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*�mNGKI3085�n*/
	}
	
	if (!locked) {
		unlock_cpu();
	}

  error_exit:
	LOG_DIS_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_DIS_INT */
#endif /* TOPPERS_dis_int */


/*
 *  �����݂̋��mNGKI3556�n
 */
#ifdef TOPPERS_ena_int
#ifdef TOPPERS_TARGET_SUPPORT_ENA_INT					/*�mNGKI3106�n*/

ER
ena_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_ENA_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_DISINT(intno));		/*�mNGKI3096�n�mNGKI3100�n*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	
	if (check_intno_cfg(intno)) {
		enable_int(intno);						/*�mNGKI3099�n*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*�mNGKI3098�n*/
	}
	
	if (!locked) {
		unlock_cpu();
	}

  error_exit:
	LOG_ENA_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_ENA_INT */
#endif /* TOPPERS_ena_int */


/*
 *  �����ݗv���̃N���A�mNGKI3920�n
 */
#ifdef TOPPERS_clr_int
#ifdef TOPPERS_TARGET_SUPPORT_CLR_INT					/*�mNGKI3927�n*/

ER
clr_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_CLR_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_CLRINT(intno));		/*�mNGKI3921�n�mNGKI3930�n*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno) && check_intno_clear(intno)) {
		clear_int(intno);						/*�mNGKI3924�n*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*�mNGKI3923�n�mNGKI3929�n*/
	}
	if (!locked) {
		unlock_cpu();
	}

  error_exit:
	LOG_CLR_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_TARGET_SUPPORT_CLR_INT */
#endif /* TOPPERS_clr_int */

/*
 *  �����݂̗v���mNGKI3932�n
 */
#ifdef TOPPERS_ras_int
#ifdef TOPPERS_SUPPORT_RAS_INT					/*�mNGKI3939�n*/

ER
ras_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_RAS_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_RASINT(intno));		/*�mNGKI3933�n�mNGKI3942�n*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno) && check_intno_raise(intno)) {
		raise_int(intno);						/*�mNGKI3936�n*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*�mNGKI3935�n�mNGKI3941�n*/
	}
	if (!locked) {
		unlock_cpu();
	}

  error_exit:
	LOG_RAS_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_RAS_INT */
#endif /* TOPPERS_ras_int */

/*
 *  �����ݗv���̃`�F�b�N�mNGKI3944�n
 */
#ifdef TOPPERS_prb_int
#ifdef TOPPERS_SUPPORT_PRB_INT					/*�mNGKI3951�n*/

ER_BOOL
prb_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_PRB_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_PRBINT(intno));		/*�mNGKI3945�n�mNGKI3952�n*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno)) {
		ercd = (ER_BOOL) probe_int(intno);		/*�mNGKI3948�n*/
	}
	else {
		ercd = E_OBJ;							/*�mNGKI3947�n*/
	}
	if (!locked) {
		unlock_cpu();
	}

  error_exit:
	LOG_PRB_INT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_SUPPORT_PRB_INT */
#endif /* TOPPERS_prb_int */

