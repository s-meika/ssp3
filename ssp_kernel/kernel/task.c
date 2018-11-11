/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010-2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2010 by Meika Sugimoto
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

#include "kernel_impl.h"
#include "task.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */

#ifndef LOG_DSP_ENTER
	#define LOG_DSP_ENTER(tskidx)
#endif /* LOG_DSP_ENTER */

#ifndef LOG_DSP_LEAVE
	#define LOG_DSP_LEAVE(tskidx)
#endif /* LOG_DSP_ENTER */


extern const intptr_t	tinib_exinf[];			/* �^�X�N�̊g����� */
extern const TASK    	tinib_task[];			/* �^�X�N�̋N���Ԓn */
extern const uint_t  	tinib_epriority[];		/* �^�X�N�̎��s���D��x�i�����\���j */

/* �����֐��̃v���g�^�C�v�錾 */
Inline bool_t primap_empty(void);
Inline bool_t primap_test(uint_t pri);
Inline uint_t primap_search(void);
Inline void primap_set(uint_t pri);
Inline void primap_clear(uint_t pri);
Inline uint_t bitmap_search(uint_t bitmap);


#ifdef TOPPERS_tskini

/*
 *  ���s��ԃ^�X�N�̌��ݗD��x
 */
uint_t runtsk_curpri;

/*
 *  ���s��ԃ^�X�N�̋N�����D��x
 */
uint_t runtsk_ipri;

/*
 *  ���f�B�L���[�T�[�`�̂��߂̃r�b�g�}�b�v
 */
volatile uint_t	ready_primap;

/*
 *  �N���v���L���[�C���O�̃r�b�g�}�b�v
 */
uint_t	actque_bitmap;

/*
 *  �^�X�N�f�B�X�p�b�`�N���v���t���O
 */
bool_t	reqflg;

/*
 *  �f�B�X�p�b�`�֎~���
 */
bool_t	disdsp;

/*
 *  read_primap�̏����l
 */
extern const uint_t init_rdypmap;

#endif /* TOPPERS_tskini */

/*
 *  �r�b�g�}�b�v�T�[�`�֐�
 *
 *  bitmap����1�̃r�b�g�̓��C�ł����ʁi�E�j�̂��̂��T�[�`���C���̃r�b
 *  �g�ԍ���Ԃ��D�r�b�g�ԍ��́C�ŉ��ʃr�b�g��0�Ƃ���Dbitmap��0���w��
 *  ���Ă͂Ȃ�Ȃ��D���̊֐��ł́Cbitmap��8�r�b�g�ł��邱�Ƃ����肵�C
 *  uint8_t�^�Ƃ��Ă���D
 *
 *  �r�b�g�T�[�`���߂����v���Z�b�T�ł́C�r�b�g�T�[�`���߂��g���悤��
 *  ���������������������ǂ��ꍇ������D���̂悤�ȏꍇ�ɂ́C�^�[�Q�b�g
 *  �ˑ����Ńr�b�g�T�[�`���߂��g����bitmap_search���`���C
 *  OMIT_BITMAP_SEARCH���}�N����`����΂悢�D�܂��C�r�b�g�T�[�`���߂�
 *  �T�[�`�������t�Ȃǂ̗��R�ŗD��x�ƃr�b�g�Ƃ̑Ή���ύX�������ꍇ��
 *  �́CPRIMAP_BIT���}�N����`����΂悢�D
 *
 *  �܂��C�W�����C�u������ffs������Ȃ�C���̂悤�ɒ�`���ĕW�����C�u
 *  �������g���������������ǂ��\��������D
 *		#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1U << (pri))
#endif /* PRIMAP_BIT */

#ifndef OMIT_BITMAP_SEARCH

static const uint8_t bitmap_search_table[] = { 0U, 1U, 0U, 2U, 0U, 1U, 0U,
												3U, 0U, 1U, 0U, 2U, 0U, 1U, 0U };

Inline uint_t
bitmap_search(uint_t bitmap)
{
	uint_t	n = 0U;

#if TMAX_TPRI != 8
	if ((bitmap & 0x00ffU) == 0U) {
		bitmap >>= 8U;
		n += 8U;
	}
#endif
	
	if ((bitmap & 0x0fU) == 0U) {
		bitmap >>= 4U;
		n += 4U;
	}
	return (n + bitmap_search_table[(bitmap & 0x0fU) - 1U]);
}

#endif /* OMIT_BITMAP_SEARCH */


/*
 *  �N�����D��x�r�b�g�}�b�v���󂩂̃`�F�b�N
 */
Inline bool_t
primap_empty(void)
{
	return (ready_primap == 0U);
}

/*
 *  �w�肵���N�����D��x�̋N�����D��x�r�b�g�}�b�v���Z�b�g����Ă��邩�ǂ����̃`�F�b�N
 */
Inline bool_t
primap_test(uint_t pri)
{
	return ((ready_primap & PRIMAP_BIT(pri)) != 0U);
}

/*
 *  �N�����D��x�r�b�g�}�b�v�̃T�[�`
 */
Inline uint_t
primap_search(void)
{
	return bitmap_search(ready_primap);
}

/*
 *  �N�����D��x�r�b�g�}�b�v�̃Z�b�g
 */
Inline void
primap_set(uint_t pri)
{
	ready_primap |= PRIMAP_BIT(pri);
}

/*
 *  �N�����D��x�r�b�g�}�b�v�̃N���A
 */
Inline void
primap_clear(uint_t pri)
{
	ready_primap &= ~PRIMAP_BIT(pri);
}

/*
 *  �ō��D�揇�ʃ^�X�N�̃T�[�`
 */

#ifdef TOPPERS_tsksched

uint_t
search_schedtsk(void)
{
	return primap_search();
}

#endif /* TOPPERS_tsksched */

#ifdef TOPPERS_tskdmt
/*
 *  �w�肵���N�����D��x�̃^�X�N�����s�ł����Ԃ��ǂ����̃e�X�g
 *
 */
bool_t
test_dormant(uint_t ipri)
{
	return !primap_test(ipri);
}

#endif /* TOPPERS_tskdmt */

/*
 *  �^�X�N�Ǘ����W���[���̏�����
 */


#ifdef TOPPERS_tskini

void
initialize_task(void)
{
	/* �N�����D��x�r�b�g�}�b�v�̏����� */
	ready_primap = init_rdypmap;
	
	/* �^�X�N�D��x�̏����� */
	runtsk_curpri = TSKPRI_NULL;
	runtsk_ipri = TSKPRI_NULL;
	
	/* �N���v���L���[�C���O�̏����� */
	actque_bitmap = 0U;
	
	/* �����݋֎~�t���O�̏����� */
	disdsp = false;
	
	/* �^�X�N�f�B�X�p�b�`�N���v���t���O�̏����� */
	reqflg = false;
}

#endif /* TOPPERS_tskini */

/*
 *  �^�X�N�̋N��
 */

#ifdef TOPPERS_tskact

bool_t
make_active(uint_t ipri)
{
	bool_t dsp;
	
	primap_set(ipri);
	
	/* 
	 *  ���s��ԃ^�X�N�̌��ݗD��x�ƈ����Ŏw�肳�ꂽ
	 *  �N���Ώۃ^�X�N�̏����D��x���r���C���s��ԃ^�X�N��
	 *  �ύX���邩���肷��D
	 *
	 *  ���������s��ԃ^�X�N��ύX����ꍇ�̓f�B�X�p�b�`�֎~��Ԃ��Q�Ƃ���D
	 */
	if(ipri < runtsk_curpri) {
		dsp = !disdsp;
	}
	else {
		dsp = false;
	}
	
	return dsp;
}

#endif /* TOPPERS_tskact */


/*
 *  �^�X�N�̎��s
 */

#ifdef TOPPERS_tskrun

void
run_task(uint_t ipri)
{
	uint_t next_pri;		/* ���Ɏ��s�J�n����^�X�N�̋N�����D��x */
	uint_t saved_ipri;		/* �Ăяo�����^�X�N�̏����D��x */
	uint_t saved_curpri;	/* �Ăяo�����^�X�N�̌��ݗD��x */
	bool_t cont;
	
	/* �ō��D�揇�ʃ^�X�N�����s����O�ɁC���ݎ��s���̃^�X�N�̌��ݗD��x�Ə����D��x��ۑ����� */
	next_pri = ipri;
	saved_ipri = runtsk_ipri;
	saved_curpri = runtsk_curpri;
	
	do {
		/* ���s����^�X�N�̌��ݗD��x�����s���D��x�ɐݒ肷�� */
		runtsk_curpri = tinib_epriority[next_pri];
		runtsk_ipri = next_pri;
		
		/* CPU���b�N���� */
		unlock_cpu();
		
		/* �^�X�N���s�J�n */
		(*((TASK)(tinib_task[next_pri])))(tinib_exinf[next_pri]);
		
		if (sense_lock()) {
			/*
			 *  CPU���b�N��Ԃ�ext_tsk���Ă΂ꂽ�ꍇ�́CCPU���b�N��������
			 *  �Ă���^�X�N���I������D������́C�T�[�r�X�R�[�����ł�CPU
			 *  ���b�N���ȗ�����΂悢�����D
			 */
		}
		else {
			/*
			 *  ����lock_cpu�����̉���disdsp�̐ݒ�̂悤�ɂ��Ȃ��̂́C
			 *  CPU���b�N���ɍēxlock_cpu���Ă΂Ȃ����߂ł���D
			 */
			lock_cpu();
		}
		
		/* �����ݗD��x�}�X�N�͑S������Ԃ̂͂��Ȃ̂ŁC�������Ȃ� */
		
		/*
		 *  �f�B�X�p�b�`�֎~��Ԃ�ext_tsk���Ă΂ꂽ�ꍇ�́C�f�B�X�p�b
		 *  �`����Ԃɂ��Ă���^�X�N���I������D
		 *
		 *	�{���͈ȉ��̂悤�ɋL�q���ׂ��ł��邪�C������ɂ���disdsp��
		 *	false�ɂ���΂������߁C�P��false�ɐݒ肷��D
		 *
		 *		if (disdsp) {
		 *			disdsp = false;
		 *		}
		 */
		disdsp = false;
		
		/* �r�b�g�}�b�v�N���A�D */
		primap_clear(next_pri);
		
		cont = false;
		
		/* �^�X�N�N���v���L���[�C���O�̃`�F�b�N */
		if (actque_test(next_pri)) {
			actque_clear(next_pri);
			(void) make_active(next_pri);
		}
		
		/* �����ꂩ�̃^�X�N�����s�\��ԂɂȂ��Ă��邩 */
		if(!primap_empty())
		{
			/* �߂��^�X�N�̌��ݗD��x��荂���N�����D��x�����^�X�N���N�����ꂽ�� */
			next_pri = search_schedtsk();
			if(saved_curpri > next_pri)
			{
				cont = true;
			}
		}
	} while(cont);
	
	runtsk_curpri = saved_curpri;
	runtsk_ipri = saved_ipri;
}

#endif /* TOPPERS_tskrun */

/*
 *  �^�X�N�f�B�X�p�b�`��
 */

#ifdef TOPPERS_tskdsp

void
dispatcher(void)
{
	do {
		if(!primap_empty()) {
			/* �^�X�N�̊J�n */
			run_task(search_schedtsk());
		}
		else {
			idle_loop();
		}
	} while(true);
}

#endif /* TOPPERS_tsk_dsp */
