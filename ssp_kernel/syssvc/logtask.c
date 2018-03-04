/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010-2012 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  @(#) $Id: logtask.c 1111 2008-06-12 08:42:26Z ertl-hiro $
 */

/*
 *		�V�X�e�����O�^�X�N
 */

#include <kernel.h>
#include <t_syslog.h>
#include <log_output.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "logtask.h"

/*
 *  �V�X�e�����O�^�X�N�̏o�͐�̃|�[�gID
 */
static ID	logtask_portid;

/*
 *  �V���A���C���^�t�F�[�X�ւ�1�����o��
 */
static void
logtask_putc(char c)
{
	serial_wri_dat(logtask_portid, &c, 1);
}

/*
 *  ���O�^�X�N�̏���������
 */

void logtask_initialize(ID log_portid)
{
	logtask_portid = log_portid;
	serial_opn_por(logtask_portid);
	syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG));
	syslog_1(LOG_NOTICE, "System logging task is started on port %d.",
													logtask_portid);
}
/*
 *  �V�X�e�����O�^�X�N�̖{��
 */
void
logtask_main(intptr_t exinf)
{
	SYSLOG	syslog;
	static uint_t	lost = 0;
	ER_UINT	rercd;
	
	while ((rercd = syslog_rea_log(&syslog)) >= 0) {
		lost += (uint_t) rercd;
		if (syslog.logtype >= LOG_TYPE_COMMENT) {
			if (lost > 0U) {
				syslog_lostmsg(lost, logtask_putc);
				lost = 0U;
			}
			syslog_print(&syslog, logtask_putc);
			logtask_putc('\n');
		}
	}
	if (lost > 0U) {
		syslog_lostmsg(lost, logtask_putc);
	}
}

void cychdr_act_logtsk(intptr_t exinf)
{
	iact_tsk((ID)exinf);
}

/*
 *  �V�X�e�����O�^�X�N�̏I������
 */
void
logtask_terminate(intptr_t exinf)
{
	char	c;
	SYSLOG	syslog;
	bool_t	msgflg = false;
	ER_UINT	rercd;

	/*
	 *  �V���A���C���^�t�F�[�X�h���C�o�̑��M�o�b�t�@�ɒ~�ς��ꂽ�f�[�^
	 *  ���C�჌�x���o�͋@�\��p���ďo�͂���D
	 */
	while (serial_get_chr(logtask_portid, &c)) {
		target_fput_log(c);
	}

	/*
	 *  ���O�o�b�t�@�ɋL�^���ꂽ���O�����C�჌�x���o�͋@�\��p���ďo
	 *  �͂���D
	 */
	while ((rercd = syslog_rea_log(&syslog)) >= 0) {
		if (!msgflg) {
			/*
			 *  ���O�o�b�t�@�Ɏc�������O���ł��邱�Ƃ�������������o
			 *  �͂���D
			 */
			syslog_printf("-- buffered messages --\n", NULL, target_fput_log);
			msgflg = true;
		}
		if (rercd > 0) {
			syslog_lostmsg((uint_t) rercd, target_fput_log);
		}
		if (syslog.logtype >= LOG_TYPE_COMMENT) {
			syslog_print(&syslog, target_fput_log);
			target_fput_log('\n');
		}
	}
}
