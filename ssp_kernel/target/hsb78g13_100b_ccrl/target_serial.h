/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015 by Naoki Saito
 *              Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2017 by Meika Sugimoto
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 */

/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤��(CCRL���ߥ�졼����)
 */

#ifndef TOPPERS_TARGET_SERIAL_H
#define TOPPERS_TARGET_SERIAL_H

#include "hsb78g13_100b.h"
#include "target_syssvc.h"
#include "chip_serial.h"

/* �ǥե���ȤǤϥݡ���1��Ȥ� */
#ifndef SIO_PORTID
#define SIO_PORTID 1
#endif /* SIO_PORTID */

/*
 *  SIO�γ���ߥ٥����ֹ�
 */
#if (SIO_PORTID == 1)
#define INHNO_SIO_TX		INTST0
#define INTNO_SIO_TX		INTST0
#define INHNO_SIO_RX		INTSR0
#define INTNO_SIO_RX		INTSR0
#elif (SIO_PORTID == 2)
#define INHNO_SIO_TX		INTST1
#define INTNO_SIO_TX		INTST1
#define INHNO_SIO_RX		INTSR1
#define INTNO_SIO_RX		INTSR1
#elif (SIO_PORTID == 3)
#define INHNO_SIO_TX		INTST2
#define INTNO_SIO_TX		INTST2
#define INHNO_SIO_RX		INTSR2
#define INTNO_SIO_RX		INTSR2
#elif (SIO_PORTID == 4)
#define INHNO_SIO_TX		INTST3
#define INTNO_SIO_TX		INTST3
#define INHNO_SIO_RX		INTSR3
#define INTNO_SIO_RX		INTSR3
#endif

#define INTPRI_SIO		-2				/* �����ͥ���� */
#define INTATR_SIO		0				/* �����°�� */


/* ���ꥢ�륯���å������� */
#define SIO_CKO0       (0U)
#define SIO_CKO1       (1U)
/* �嵭�Τ����ɤ��餫�����򤹤� */
#define SIO_CLOCK      SIO_CKO0

/* SPS�쥸���������� */
#define SELECT_SPSm    (0U)	/* 0 �� 1������ */

#if defined(SIO_BPS_9600)
#define PRS_VALUE     (4U)
#define COMM_CLOCK_VALUE (64U)
#elif defined(SIO_BPS_19200)
#define PRS_VALUE     (3U)
#define COMM_CLOCK_VALUE (64U)
#elif defined(SIO_BPS_38400)
#define PRS_VALUE     (2U)
#define COMM_CLOCK_VALUE (64U)
#else
#error No defined SIO_BPS_XXX
#endif


/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_RDY_SND    1U        /* ������ǽ������Хå� */
#define SIO_RDY_RCV    2U        /* �������Υ�����Хå� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  SIO�����
 */
extern void sio_initialize(intptr_t exinf);

/*
 *  ���ꥢ�륪���ץ�
 */
extern SIOPCB *sio_opn_por(ID siopid, intptr_t exinf);

/*
 *  ���ꥢ�륯������
 */
extern void sio_cls_por(SIOPCB *p_siopcb);

/*
 *  ����ߥϥ�ɥ�
 */
extern void sio_isr_tx(intptr_t exinf);
extern void sio_isr_rx(intptr_t exinf);

/*
 *  1ʸ������
 */
extern bool_t sio_snd_chr(SIOPCB *siopcb, char c);

/*
 *  1ʸ������
 */
extern int_t sio_rcv_chr(SIOPCB *siopcb);

/*
 *  ������Хå��ε���
 */
extern void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/* 
 *  ������Хå��ζػ�
 */
extern void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  ������ǽ������Хå�
 */
extern void sio_irdy_snd(intptr_t exinf);

/*
 *  �������Υ�����Хå�
 */
extern void sio_irdy_rcv(intptr_t exinf);

/*
 *  1ʸ�������ʥݡ���󥰤Ǥν��ϡ�
 */
extern void sio_pol_snd_chr(char c, ID siopid);

/*
 *  �������åȤΥ��ꥢ������
 */
extern void target_usart_init(ID siopid);

/*
 *  ���٥���Ͻ����
 */
extern void target_low_output_init(ID siopid);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_SERIAL_H */