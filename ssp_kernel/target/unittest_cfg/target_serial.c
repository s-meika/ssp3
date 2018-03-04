/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2006-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: target_serial.c 891 2008-04-11 11:20:07Z hiro $
 */

/*
 *		���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�Mac OS X�ѡ�
 */

#include "macosx.h"
#include <t_stddef.h>
#include <t_syslog.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "target_serial.h"

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
	char		*path;			/* �ե�����Υѥ�̾ */
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
	const SIOPINIB *p_siopinib;	/* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	intptr_t	exinf;			/* ��ĥ���� */
	bool_t		openflag;		/* �����ץ�Ѥߥե饰 */
	struct termios saved_term;	/* ����ü��������� */

	int_t		read_fd;		/* �ɽФ��ѥե�����ǥ�������ץ� */
	bool_t		rcv_flag;		/* ����ʸ���Хåե�ͭ���ե饰 */
	char		rcv_buf;		/* ����ʸ���Хåե� */
	bool_t		rcv_rdy;		/* �������Υ�����Хå����ĥե饰 */

	int_t		write_fd;		/* ������ѥե�����ǥ�������ץ� */
	bool_t		snd_flag;		/* ����ʸ���Хåե�ͭ���ե饰 */
	char		snd_buf;		/* ����ʸ���Хåե� */
	bool_t		snd_rdy;		/* �������Υ�����Хå����ĥե饰 */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
	{ NULL }
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)	((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  SIO�ɥ饤�Фν����
 */
void
sio_initialize(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
	}
}

/*
 *  SIO�ɥ饤�Фν�λ����
 */
void
sio_terminate(intptr_t exinf)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  �����ץ󤵤�Ƥ��륷�ꥢ��I/O�ݡ��ȤΥ�����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
		if (p_siopcb->openflag) {
			sio_cls_por(p_siopcb);
		}
	}
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB			*p_siopcb;
	const SIOPINIB	*p_siopinib;
	int_t			fd;
	struct termios	term;

	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;

	if (p_siopinib->path != NULL) {
		fd = open(p_siopinib->path, O_RDWR, 0777);
		assert(fd >= 0);
		p_siopcb->read_fd = p_siopcb->write_fd = fd;
	}
	else {
		fd = p_siopcb->read_fd = STDIN_FILENO;		/* ɸ�������Ϥ�Ȥ� */
		p_siopcb->write_fd = STDOUT_FILENO;
	}
	fcntl(fd, F_SETOWN, getpid());
	fcntl(fd, F_SETFL, (O_NONBLOCK | O_ASYNC));

	tcgetattr(fd, &(p_siopcb->saved_term));
	term = p_siopcb->saved_term;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(fd, TCSAFLUSH, &term);

	p_siopcb->exinf = exinf;
	p_siopcb->rcv_flag = false;
	p_siopcb->rcv_rdy = false;
	p_siopcb->snd_flag = false;
	p_siopcb->snd_rdy = false;
	p_siopcb->openflag = true;
	return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	int_t	fd;

	fd = p_siopcb->read_fd;
	tcsetattr(fd, TCSAFLUSH, &(p_siopcb->saved_term));
	fcntl(fd, F_SETFL, 0);

	if (p_siopcb->p_siopinib->path != NULL) {
		close(p_siopcb->read_fd);
	}
	p_siopcb->openflag = false;
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
sio_isr(intptr_t exinf)
{
	SIOPCB	*p_siopcb = &(siopcb_table[0]);
	int_t	n;

	if (p_siopcb->snd_flag) {
		if ((n = write(p_siopcb->write_fd, &(p_siopcb->snd_buf), 1)) > 0) {
			p_siopcb->snd_flag = false;
			if (p_siopcb->snd_rdy) {
				sio_irdy_snd(p_siopcb->exinf);
			}
		}
	}
	if (!p_siopcb->rcv_flag) {
		if ((n = read(p_siopcb->read_fd, &(p_siopcb->rcv_buf), 1)) > 0) {
			p_siopcb->rcv_flag = true;
			if (p_siopcb->rcv_rdy) {
				sio_irdy_rcv(p_siopcb->exinf);
			}
		}
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
sio_snd_chr(SIOPCB *p_siopcb, char c)
{
	int_t	n;

	if (!p_siopcb->snd_flag) {
		if ((n = write(p_siopcb->write_fd, &c, 1)) > 0) {
			return(true);
		}
		else {
			assert(n < 0 && errno == EAGAIN);
			p_siopcb->snd_flag = true;
			p_siopcb->snd_buf = c;
			return(true);
		}
	}
	else {
		return(false);
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
	char	c;
	int_t	n;

	if (p_siopcb->rcv_flag) {
		p_siopcb->rcv_flag = false;
		return((int_t)(uint8_t)(p_siopcb->rcv_buf));
	}
	else if ((n = read(p_siopcb->read_fd, &c, 1)) > 0) {
		return((int_t)(uint8_t) c);
	}
	else {
		assert(n < 0 && errno == EAGAIN);
		return(-1);
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		p_siopcb->snd_rdy = true;
		break;
	case SIO_RDY_RCV:
		p_siopcb->rcv_rdy = true;
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		p_siopcb->snd_rdy = false;
		break;
	case SIO_RDY_RCV:
		p_siopcb->rcv_rdy = false;
		break;
	}
}
