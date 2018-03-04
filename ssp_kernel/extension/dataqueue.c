/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011 by Meika Sugimoto
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
 *		�f�[�^�L���[�@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "dataqueue.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_PSND_DTQ_ENTER
#define LOG_PSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_PSND_DTQ_ENTER */

#ifndef LOG_PSND_DTQ_LEAVE
#define LOG_PSND_DTQ_LEAVE(ercd)
#endif /* LOG_PSND_DTQ_LEAVE */

#ifndef LOG_IPSND_DTQ_ENTER
#define LOG_IPSND_DTQ_ENTER(dtqid, data)
#endif /* LOG_IPSND_DTQ_ENTER */

#ifndef LOG_IPSND_DTQ_LEAVE
#define LOG_IPSND_DTQ_LEAVE(ercd)
#endif /* LOG_IPSND_DTQ_LEAVE */

#ifndef LOG_PRCV_DTQ_ENTER
#define LOG_PRCV_DTQ_ENTER(dtqid, p_data)
#endif /* LOG_PRCV_DTQ_ENTER */

#ifndef LOG_PRCV_DTQ_LEAVE
#define LOG_PRCV_DTQ_LEAVE(ercd, data)
#endif /* LOG_PRCV_DTQ_LEAVE */

/*
 *  �f�[�^�L���[�ւ̃f�[�^���M
 */
void
enqueue_data(intptr_t* const data , uint8_t* const tail , const uint8_t size , const intptr_t sdata);

/*
 *  �f�[�^�L���[����̃f�[�^��M
 */
void
dequeue_data(intptr_t* const data , uint8_t* const head , const uint8_t size , intptr_t* rdata);


/*
 *  �f�[�^�L���[�̐�
 */
#define tnum_dtq	((uint_t)(tmax_dtqid - TMIN_DTQID + 1))

/*
 *  �f�[�^�L���[ID����f�[�^�L���[�Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_DTQ(dtqid)	((uint_t)((dtqid) - TMIN_DTQID))

/*
 *  �f�[�^�L���[�@�\�̏�����
 */
#ifdef TOPPERS_dtqini

void
initialize_dataqueue(void)
{
	uint_t	i;

	for (i = 0U ; i < tnum_dtq ; i++) {
		dtqcb_count[i] = 0U;
		dtqcb_head[i] = 0U;
		dtqcb_tail[i] = 0U;
	}
}

#endif /* TOPPERS_dtqini */


/*
 *  �f�[�^�L���[�����t���̃`�F�b�N
 */

Inline bool_t
data_full(uint8_t count , uint8_t size)
{
	return (count >= size)? true : false;
}

/*
 *  �f�[�^�L���[���󂩂̃`�F�b�N
 */

Inline bool_t
data_empty(uint8_t count)
{
	return (count == 0)? true : false;
}


/*
 *  �f�[�^�L���[�ւ̃f�[�^���M
 */


#ifdef TOPPERS_dtqenq

void
enqueue_data(intptr_t* const data , uint8_t* const tail , const uint8_t size , const intptr_t sdata)
{
	data[*tail] = sdata;
	(*tail)++;
	if (*tail >= size) {
		*tail = 0U;
	}
}

#endif /* TOPPERS_dtqenq */

/*
 *  ���M�҂��L���[�̐擪�^�X�N����̃f�[�^��M
 */
#ifdef TOPPERS_dtqdeq

void
dequeue_data(intptr_t* const data , uint8_t* const head , const uint8_t size , intptr_t* rdata)
{
	*rdata = data[*head];
	(*head)++;
	if (*head >= size) {
		*head = 0U;
	}
	
}

#endif /* TOPPERS_dtqdeq */

/*
 *  �f�[�^�L���[�ւ̑��M�i�|�[�����O�j
 */
#ifdef TOPPERS_psnd_dtq

ER
psnd_dtq(ID dtqid, intptr_t data)
{
	ER		ercd;
	int_t	index;
	
	LOG_PSND_DTQ_ENTER(dtqid, data);
	CHECK_TSKCTX_UNL();
	CHECK_ID(VALID_DTQID(dtqid));
	
	lock_cpu();
	index = INDEX_DTQ(dtqid);
	
	if (!data_full(dtqcb_count[index] , dtqinib_size[index]))
	{
		enqueue_data(dtqinib_data[index] , &(dtqcb_tail[index]) , 
					dtqinib_size[index] , data);
		dtqcb_count[index]++;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	unlock_cpu();
	
  error_exit:
	LOG_PSND_DTQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_psnd_dtq */

/*
 *  �f�[�^�L���[����̎�M�i�|�[�����O�j
 */
#ifdef TOPPERS_prcv_dtq

ER
prcv_dtq(ID dtqid, intptr_t *p_data)
{
	ER		ercd;
	int_t	index;

	LOG_PRCV_DTQ_ENTER(dtqid, p_data);
	CHECK_TSKCTX_UNL();
	CHECK_ID(VALID_DTQID(dtqid));

	lock_cpu();
	index = INDEX_DTQ(dtqid);
	
	if (!data_empty(dtqcb_count[index]))
	{
		dequeue_data(dtqinib_data[index] , &(dtqcb_head[index]) , 
					dtqinib_size[index] , p_data);
		dtqcb_count[index]--;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	unlock_cpu();

  error_exit:
	LOG_PRCV_DTQ_LEAVE(ercd, *p_data);
	return(ercd);
}

#endif /* TOPPERS_prcv_dtq */
