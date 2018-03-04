/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2008 by Embedded and Real-Time Systems Laboratory
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
 */

/*
 *		�V���A���C���^�t�F�[�X�h���C�o
 */

#include <kernel.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "serial.h"
#include "kernel_cfg.h"

/*
 *  �o�b�t�@�T�C�Y�̃f�t�H���g�l�ƃo�b�t�@�̒�`
 */
#ifndef SERIAL_RCV_BUFSZ1
#define	SERIAL_RCV_BUFSZ1	64			/* �|�[�g1�̎�M�o�b�t�@�T�C�Y */
#endif /* SERIAL_RCV_BUFSZ1 */

#ifndef SERIAL_SND_BUFSZ1
#define	SERIAL_SND_BUFSZ1	256			/* �|�[�g1�̑��M�o�b�t�@�T�C�Y */
#endif /* SERIAL_SND_BUFSZ1 */

static char	rcv_buffer1[SERIAL_RCV_BUFSZ1];
static char	snd_buffer1[SERIAL_SND_BUFSZ1];

#if TNUM_PORT >= 2						/* �|�[�g2�Ɋւ����` */

#ifndef SERIAL_RCV_BUFSZ2
#define	SERIAL_RCV_BUFSZ2	64			/* �|�[�g2�̎�M�o�b�t�@�T�C�Y */
#endif /* SERIAL_RCV_BUFSZ2 */

#ifndef SERIAL_SND_BUFSZ2
#define	SERIAL_SND_BUFSZ2	64			/* �|�[�g2�̑��M�o�b�t�@�T�C�Y */
#endif /* SERIAL_SND_BUFSZ2 */

static char	rcv_buffer2[SERIAL_RCV_BUFSZ2];
static char	snd_buffer2[SERIAL_SND_BUFSZ2];

#endif /* TNUM_PORT >= 2 */

#if TNUM_PORT >= 3						/* �|�[�g3�Ɋւ����` */

#ifndef SERIAL_RCV_BUFSZ3
#define	SERIAL_RCV_BUFSZ3	64			/* �|�[�g3�̎�M�o�b�t�@�T�C�Y */
#endif /* SERIAL_RCV_BUFSZ3 */

#ifndef SERIAL_SND_BUFSZ3
#define	SERIAL_SND_BUFSZ3	64			/* �|�[�g3�̑��M�o�b�t�@�T�C�Y */
#endif /* SERIAL_SND_BUFSZ3 */

static char	rcv_buffer3[SERIAL_RCV_BUFSZ3];
static char	snd_buffer3[SERIAL_SND_BUFSZ3];

#endif /* TNUM_PORT >= 3 */

/*
 *  �V���A���|�[�g�������u���b�N
 */
typedef struct serial_port_initialization_block {
	uint_t	rcv_bufsz;		/* ��M�o�b�t�@�T�C�Y */
	char	*rcv_buffer;	/* ��M�o�b�t�@ */
	uint_t	snd_bufsz;		/* ���M�o�b�t�@�T�C�Y */
	char	*snd_buffer;	/* ���M�o�b�t�@ */
} SPINIB;

static const SPINIB spinib_table[TNUM_PORT] = {
	{ SERIAL_RCV_BUFSZ1, rcv_buffer1,
	  SERIAL_SND_BUFSZ1, snd_buffer1 },
#if TNUM_PORT >= 2
	{ SERIAL_RCV_BUFSZ2, rcv_buffer2,
	  SERIAL_SND_BUFSZ2, snd_buffer2 },
#endif /* TNUM_PORT >= 2 */
#if TNUM_PORT >= 3
	{ SERIAL_RCV_BUFSZ3, rcv_buffer3,
	  SERIAL_SND_BUFSZ3, snd_buffer3 },
#endif /* TNUM_PORT >= 3 */
};

/*
 *  �V���A���|�[�g�Ǘ��u���b�N
 */
typedef struct serial_port_control_block {
	const SPINIB *p_spinib;		/* �V���A���|�[�g�������u���b�N */
	SIOPCB	*p_siopcb;			/* �V���A��I/O�|�[�g�Ǘ��u���b�N */
	bool_t	openflag;			/* �I�[�v���ς݃t���O */
	bool_t	errorflag;			/* �G���[�t���O */
	uint_t	ioctl;				/* ���쐧��̐ݒ�l */

	uint_t	rcv_read_ptr;		/* ��M�o�b�t�@�Ǐo���|�C���^ */
	uint_t	rcv_write_ptr;		/* ��M�o�b�t�@�����݃|�C���^ */
	uint_t	rcv_count;			/* ��M�o�b�t�@���̕����� */

	uint_t	snd_read_ptr;		/* ���M�o�b�t�@�Ǐo���|�C���^ */
	uint_t	snd_write_ptr;		/* ���M�o�b�t�@�����݃|�C���^ */
	uint_t	snd_count;			/* ���M�o�b�t�@���̕����� */
} SPCB;

static SPCB	spcb_table[TNUM_PORT];

/*
 *  �V���A���|�[�gID����V���A���|�[�g�Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_PORT(portid)	((uint_t)((portid) - 1))
#define get_spcb(portid)	(&(spcb_table[INDEX_PORT(portid)]))

/*
 *  �|�C���^�̃C���N�������g
 */
#define INC_PTR(ptr, bufsz)		{ if (++(ptr) == (bufsz)) { (ptr) = 0; }}

/*
 *  �T�[�r�X�R�[���ďo���}�N��
 *
 *  �T�[�r�X�R�[���ďo�����܂ގ�exp��]�����C�Ԓl���G���[�i���̒l�j�̏�
 *  ���ɂ́Cerc��ercd_exp��]�������l�������Cerror_exit��goto����D
 */
#define SVC(exp, ercd_exp) \
				{ if ((exp) < 0) { ercd = (ercd_exp); goto error_exit; }}

/*
 *  E_SYS�G���[�̐���
 */
static ER
gen_ercd_sys(SPCB *p_spcb)
{
	p_spcb->errorflag = true;
	return(E_SYS);
}


/*
 *  �V���A���C���^�t�F�[�X�h���C�o�̏��������[�`��
 */
void
serial_initialize(intptr_t exinf)
{
	uint_t	i;
	SPCB	*p_spcb;

	for (i = 0; i < TNUM_PORT; i++) {
		p_spcb = &(spcb_table[i]);
		p_spcb->p_spinib = &(spinib_table[i]);
		p_spcb->openflag = false;
	}
}

/*
 *  �V���A���C���^�[�t�F�[�X�h���C�o�̏I�����[�`��
 */

void
serial_terminate(intptr_t exinf)
{
	uint_t	i;
	SPCB	*p_spcb;
	
	/* �o�b�t�@�Ɏc���Ă���S�Ă̕������o�͂��� */
	for (i = 0; i < TNUM_PORT; i++) {
		p_spcb = &(spcb_table[i]);

		while(p_spcb->snd_count != 0U)
		{
			if(sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]) == true)
			{
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
			}
		}
	}

}

/*
 *  �V���A���|�[�g�̃I�[�v���i�T�[�r�X�R�[���j
 */
ER
serial_opn_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;

	if (sns_dpn()) {				/* �R���e�L�X�g�̃`�F�b�N */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �|�[�g�ԍ��̃`�F�b�N */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (p_spcb->openflag) {			/* �I�[�v���ς݂��̃`�F�b�N */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �ϐ��̏�����
		 */
		p_spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF);

		p_spcb->rcv_read_ptr = p_spcb->rcv_write_ptr = 0U;
		p_spcb->rcv_count = 0U;

		p_spcb->snd_read_ptr = p_spcb->snd_write_ptr = 0U;
		p_spcb->snd_count = 0U;

		/*
		 *  ����ȍ~�C�����݂��֎~����D
		 */
		if (loc_cpu() < 0) {
			ercd = E_SYS;
			goto error_exit_enadsp;
		}

		/*
		 *  �n�[�h�E�F�A�ˑ��̃I�[�v������
		 */
		p_spcb->p_siopcb = sio_opn_por(portid, (intptr_t) p_spcb);

		/*
		 *  ��M�ʒm�R�[���o�b�N��������D
		 */
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_RCV);
		p_spcb->openflag = true;
		p_spcb->errorflag = false;

		if (unl_cpu() < 0) {
			p_spcb->errorflag = true;
			ercd = E_SYS;
			goto error_exit_enadsp;
		}
		ercd = E_OK;
	}

  error_exit_enadsp:
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  �V���A���|�[�g�̃N���[�Y�i�T�[�r�X�R�[���j
 */
ER
serial_cls_por(ID portid)
{
	SPCB	*p_spcb;
	ER		ercd;
	bool_t	eflag = false;

	if (sns_dpn()) {				/* �R���e�L�X�g�̃`�F�b�N */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �|�[�g�ԍ��̃`�F�b�N */
	}
	p_spcb = get_spcb(portid);

	SVC(dis_dsp(), gen_ercd_sys(p_spcb));
	if (!(p_spcb->openflag)) {		/* �I�[�v���ς݂��̃`�F�b�N */
		ercd = E_OBJ;
	}
	else {
		/*
		 *  �n�[�h�E�F�A�ˑ��̃N���[�Y����
		 */
		if (loc_cpu() < 0) {
			eflag = true;
		}
		sio_cls_por(p_spcb->p_siopcb);
		p_spcb->openflag = false;
		if (unl_cpu() < 0) {
			eflag = true;
		}
		
		/*
		 *  �G���[�R�[�h�̐ݒ�
		 */
		if (eflag) {
			ercd = gen_ercd_sys(p_spcb);
		}
		else {
			ercd = E_OK;
		}
	}
	SVC(ena_dsp(), gen_ercd_sys(p_spcb));

  error_exit:
	return(ercd);
}

/*
 *  �V���A���|�[�g�ւ̕������M
 *
 *  p_spcb�Ŏw�肳���V���A��I/O�|�[�g�ɑ΂��āC����c�𑗐M����D����
 *  �𑗐M���W�X�^�ɂ��ꂽ�ꍇ�ɂ�true��Ԃ��D�����łȂ��ꍇ�ɂ́C���M
 *  ���W�X�^���󂢂����Ƃ�ʒm����R�[���o�b�N�֐��������Cfalse��Ԃ��D
 *  ���̊֐��́CCPU���b�N��ԂŌĂяo�����D
 */
Inline bool_t
serial_snd_chr(SPCB *p_spcb, char c)
{
	if (sio_snd_chr(p_spcb->p_siopcb, c)) {
		return(true);
	}
	else {
		sio_ena_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
		return(false);
	}
}

/*
 *  �V���A���|�[�g�ւ�1�������M
 *  �w�肳�ꂽ�����̑��M�����݂�.
 *  �f�o�C�X�ւ̑��M�����������ꍇ�܂��̓o�b�t�@�ɋ󂫂�����i�[�ł����ꍇ�� false, 
 *  �o�b�t�@���t���Ŋi�[�ł��Ȃ������ꍇ�� true ��Ԃ��D
 *  ����ȊO�̃G���[�����������ꍇ�� ER �^�̃G���[�R�[�h��Ԃ��D
 */
static ER_BOOL
serial_wri_chr(SPCB *p_spcb, char c)
{
	bool_t	buffer_full;
	ER		ercd, rercd;

	/*
	 *  LF�̑O��CR�𑗐M����D
	 *  �������C1�����ȉ��̋󂫂����Ȃ��ꍇ�̓o�b�t�@�t���Ƃ݂Ȃ��C���M���Ȃ��D
	 */
	if (c == '\n' && (p_spcb->ioctl & IOCTL_CRLF) != 0U) {
		if(p_spcb->snd_count + 1U < p_spcb->p_spinib->snd_bufsz) {
			SVC(rercd = serial_wri_chr(p_spcb, '\r'), rercd);
		}
		else {
			return (ER_BOOL) true;
		}
	}

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));
	if ((p_spcb->snd_count == 0U) && serial_snd_chr(p_spcb, c)) {
		/*
		 *  �V���A��I/O�f�o�C�X�̑��M���W�X�^�ɕ��������邱�Ƃɐ�����
		 *  ���ꍇ�D
		 */
		buffer_full = false;
	}
	else {
		/*
		 *  �󂫂�����΁C���M�o�b�t�@�ɕ���������D
		 *  �󂫂��Ȃ��ꍇ�C���M���Ȃ��D
		 */
		if(p_spcb->snd_count < p_spcb->p_spinib->snd_bufsz) {
			p_spcb->p_spinib->snd_buffer[p_spcb->snd_write_ptr] = c;
			INC_PTR(p_spcb->snd_write_ptr, p_spcb->p_spinib->snd_bufsz);
			p_spcb->snd_count++;
			buffer_full = false;
		}
		else {
			buffer_full = true;
		}
	}

	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_full;

  error_exit:
	return(ercd);
}

bool_t
serial_rcvbuf_empty(SPCB *p_spcb)
{
	return (p_spcb->rcv_count == 0u);
}

/*
 *  �V���A���|�[�g�ւ̕����񑗐M�i�T�[�r�X�R�[���j
 */
ER_UINT
serial_wri_dat(ID portid, const char *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_full;
	uint_t	wricnt = 0U;
	ER		ercd, rercd;

	if (sns_dpn()) {				/* �R���e�L�X�g�̃`�F�b�N */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �|�[�g�ԍ��̃`�F�b�N */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �I�[�v���ς݂��̃`�F�b�N */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* �G���[��Ԃ��̃`�F�b�N */
		return(E_SYS);
	}
	
	/*
	 *  len �܂�1���������M�����݂�D
	 *  �r���Ńo�b�t�@�t���ɂȂ����璆�f����D
	 */
	SVC((rercd = dis_dsp()) , rercd);
	for(wricnt = 0U; wricnt < len; wricnt++) {
		SVC(rercd = serial_wri_chr(p_spcb, *buf++), rercd);
		buffer_full = (bool_t)rercd;
		if(buffer_full) {
			break;
		}
	}
	SVC((rercd = ena_dsp()) , rercd);
	
	ercd = E_OK;
  error_exit:
	return(wricnt > 0U ? (ER_UINT) wricnt : ercd);
}

/*
 *  �V���A���|�[�g�����1������M
 *  �����̎�M�����݂�.
 *  �o�b�t�@�Ƀf�[�^�����݂��C�擾�ł����ꍇ�� false, 
 *  �o�b�t�@����Ŏ擾�ł��Ȃ������ꍇ�� true ��Ԃ��D
 *  ����ȊO�̃G���[�����������ꍇ�� ER �^�̃G���[�R�[�h��Ԃ��D
 */
static ER_BOOL
serial_rea_chr(SPCB *p_spcb, char *p_c)
{
	bool_t	buffer_empty;
	ER		ercd;

	SVC(loc_cpu(), gen_ercd_sys(p_spcb));

	/*
	 *  �f�[�^�����݂���΁C��M�o�b�t�@���當�������o���D
	 *  �Ȃ���Ύ��o���Ȃ��D
	 */
	if(p_spcb->rcv_count > 0U) {
		*p_c = p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_read_ptr];
		INC_PTR(p_spcb->rcv_read_ptr, p_spcb->p_spinib->rcv_bufsz);
		p_spcb->rcv_count--;
		buffer_empty = false;
	}
	else {
		buffer_empty = true;
	}
	
	SVC(unl_cpu(), gen_ercd_sys(p_spcb));
	ercd = (ER_BOOL) buffer_empty;

  error_exit:
	return(ercd);
}

/*
 *  �V���A���|�[�g����̕������M�i�T�[�r�X�R�[���j
 */
ER_UINT
serial_rea_dat(ID portid, char *buf, uint_t len)
{
	SPCB	*p_spcb;
	bool_t	buffer_empty;
	uint_t	reacnt = 0U;
	char	c = '\0';		/* �R���p�C���̌x����}�~���邽�߂ɏ��������� */
	ER		ercd, rercd;

	if (sns_dpn()) {				/* �R���e�L�X�g�̃`�F�b�N */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �|�[�g�ԍ��̃`�F�b�N */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �I�[�v���ς݂��̃`�F�b�N */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* �G���[��Ԃ��̃`�F�b�N */
		return(E_SYS);
	}
	
	/*
	 *  len �܂Ŏ�M�����݂�D
	 *  �o�b�t�@����œǂݏo���Ȃ������ꍇ�͒��f����
	 */
	SVC((rercd = dis_dsp()) , rercd);
	for(reacnt = 0U; reacnt < len; reacnt++) {
		SVC(rercd = serial_rea_chr(p_spcb, &c), rercd);
		buffer_empty = (bool_t)rercd;

		if(buffer_empty) {
			break;
		}
		else {
			/*
			 *  �G�R�[�o�b�N�����D
			 */
			if ((p_spcb->ioctl & IOCTL_ECHO) != 0U) {
				SVC(rercd = serial_wri_chr(p_spcb, c), rercd);
			}
			*buf++ = c;
		}
	}
	SVC((rercd = ena_dsp()) , rercd);
	
	ercd = E_OK;
  error_exit:
	return(reacnt > 0U ? (ER_UINT) reacnt : ercd);
}

/*
 *  �V���A���|�[�g�̐���i�T�[�r�X�R�[���j
 */
ER
serial_ctl_por(ID portid, uint_t ioctl)
{
	SPCB	*p_spcb;

	if (sns_dpn()) {				/* �R���e�L�X�g�̃`�F�b�N */
		return(E_CTX);
	}
	if (!(1 <= portid && portid <= TNUM_PORT)) {
		return(E_ID);				/* �|�[�g�ԍ��̃`�F�b�N */
	}

	p_spcb = get_spcb(portid);
	if (!(p_spcb->openflag)) {		/* �I�[�v���ς݂��̃`�F�b�N */
		return(E_OBJ);
	}
	if (p_spcb->errorflag) {		/* �G���[��Ԃ��̃`�F�b�N */
		return(E_SYS);
	}

	p_spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  �V���A���|�[�g����̑��M�\�R�[���o�b�N
 */
void
sio_irdy_snd(intptr_t exinf)
{
	SPCB	*p_spcb;

	p_spcb = (SPCB *) exinf;

	if (p_spcb->snd_count > 0U) {
		/*
		 *  ���M�o�b�t�@�����當�������o���đ��M����D
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
		INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
		p_spcb->snd_count--;
	}
	else {
		/*
		 *  ���M���ׂ��������Ȃ��ꍇ�́C���M�\�R�[���o�b�N���֎~����D
		 */
		sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
	}
}

/*
 *  �V���A���|�[�g����̎�M�ʒm�R�[���o�b�N
 */
void
sio_irdy_rcv(intptr_t exinf)
{
	SPCB	*p_spcb;
	char	c;
	
	p_spcb = (SPCB *) exinf;
	c = (char) sio_rcv_chr(p_spcb->p_siopcb);
	
	if (p_spcb->rcv_count != p_spcb->p_spinib->rcv_bufsz) {
		/*
		 *  ��M������������M�o�b�t�@�ɓ����D
		 *  �o�b�t�@�t���̏ꍇ�C��M�����������̂Ă�D
		 */
		p_spcb->p_spinib->rcv_buffer[p_spcb->rcv_write_ptr] = c;
		INC_PTR(p_spcb->rcv_write_ptr, p_spcb->p_spinib->rcv_bufsz);
		p_spcb->rcv_count++;
	}
}

/*
 *  �V���A���C���^�t�F�[�X�h���C�o����̖����M�����̎�o��
 */
bool_t
serial_get_chr(ID portid, char *p_c)
{
	SPCB	*p_spcb;

	if (1 <= portid && portid <= TNUM_PORT) {	/* �|�[�g�ԍ��̃`�F�b�N */
		p_spcb = get_spcb(portid);
		if (p_spcb->openflag) {					/* �I�[�v���ς݂��̃`�F�b�N */
			if (p_spcb->snd_count > 0U) {
				*p_c = p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr];
				INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
				p_spcb->snd_count--;
				return(true);
			}
		}
	}
	return(false);
}
