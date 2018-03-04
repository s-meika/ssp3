/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
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

/*
 *  TOPPERS/SSP�P�̃e�X�g�p�\�[�X�t�@�C��(time_event.h/c�p)
 */

#include <kernel.h>
#include "stubtask.h"
#include "kernel_cfg.h"

#include "kernel_impl.h"
#include "time_event.h"

#include <CUnit.h>
#include <Console.h>

static void callback1(uintptr_t arg);
static void callback2(uintptr_t arg);
static void callback3(uintptr_t arg);

void test_initialize_time_event(void)
{
	/* Pre Condition */
	
	/* --- */
	initialize_time_event();
	/* --- */

	/* Post Condition */
	CU_ASSERT_EQUAL(tmevt_queue[tnum_tmevt_queue].next , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_queue[tnum_tmevt_queue].prev , tnum_tmevt_queue);
}

void test_time_event_enqueue(void)
{
	uint_t tmevtid;
	const int queue_header = tnum_tmevt_queue;

	/* Pre Condition */
	initialize_time_event();
	
	/* --- */
	tmevtid = 0;
	time_event_enqueue(tmevtid , 10 , callback1 , 1);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 10 | xx , xx | xx , xx | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 0 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , tmevtid);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , tmevtid);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , tnum_tmevt_queue);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 10);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 1);
	

	/* Pre Condition */
	
	/* --- */
	tmevtid = 2;
	time_event_enqueue(tmevtid , 50 , callback2 , 2);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 2 | xx , xx | 0 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 2 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , queue_header);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 0);
	CU_ASSERT_EQUAL(tmevt_queue[0].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[0].prev , queue_header);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 50);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 2);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 1;
	time_event_enqueue(tmevtid , 40 , callback1 , 3);

	/* --- */

	/* Post Condition */
	/*
	 *  | 10 , 1 | 0 , 2 | 1 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | xx , xx | xx , xx | 2 , 0 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[0].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[2].prev , 1);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 40);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 3);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 8;
	time_event_enqueue(tmevtid , 5 , callback2 , 1000);

	/* --- */

	/* Post Condition */
	/*
	 *  | 8 , 1 | 0 , 2 | 1 , 10 | xx , xx | xx , xx |
	 *    xx , xx | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[0].prev , 8);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 0);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 10);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 8);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 5);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 1000);

	/* Pre Condition */
	
	/* --- */
	tmevtid = 5;
	time_event_enqueue(tmevtid , 40 , callback2 , 155);

	/* --- */

	/* Post Condition */
	/*
	 *  | 8 , 1 | 0 , 5 | 5 , 10 | xx , xx | xx , xx |
	 *    1 , 2 | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[1].next , 5);
	CU_ASSERT_EQUAL(tmevt_queue[2].prev , 5);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].next , 2);
	CU_ASSERT_EQUAL(tmevt_queue[tmevtid].prev , 1);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 8);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 2);
	CU_ASSERT_EQUAL(tmevt_time[tmevtid] , 40);
	CU_ASSERT_EQUAL(tmevt_arg[tmevtid] , 155);
}

void test_time_event_dequeue(void)
{
	uint_t tmevtid;
	const int queue_header = tnum_tmevt_queue;
	
	/* Pre Condition */
	/*
	 *  10(head) -> 8 -> 0 -> 1 -> 5 -> 2
	 */
	/* --- */
	tmevtid = 0;

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 0 , 5 | 5 , 10 | xx , xx | xx , xx |
	 *    1 , 2 | xx , xx | 10 , 0 | xx , xx | 2 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[8].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[1].prev , 8);

	/*
	 *  10(head) -> 8 -> 1 -> 5 -> 2
	 */
	/* --- */
	tmevtid = 2;
	/* enqueue�̃e�X�g���瑱���ōs�� */

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 0 , 5 | xx , xx | xx , xx | xx , xx |
	 *    1 , 10 | xx , xx | 10 , 0 | xx , xx | 5 , 8 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[5].next , queue_header);
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].prev , 5);


	/*
	 *  10(head) -> 8 -> 1 -> 5
	 */
	/* --- */
	tmevtid = 8;
	/* enqueue�̃e�X�g���瑱���ōs�� */

	/* --- */
	
	time_event_dequeue(tmevtid);
	
	/* --- */

	/* Post Condition */
	/*
	 *  | xx , xx | 10 , 5 | xx , xx | xx , xx | xx , xx |
	 *    1 , 10 | xx , xx | xx , xx | xx , xx | 5 , 1 | 
	 */
	CU_ASSERT_EQUAL(tmevt_queue[queue_header].next , 1);
	CU_ASSERT_EQUAL(tmevt_queue[1].prev , queue_header);

	/*
	 *  10(head) -> 1 -> 5
	 */

}

void test_signal_time(void)
{
	int i;

	time_event_enqueue(9 , 10 , callback3 , 1000);
	
	for(i = 0 ; i < 50 ; i++)
	{
		signal_time();
		CU_ASSERT_EQUAL(lock_flag , false);
	}

}


static void callback1(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 3);
}

static void callback2(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 155);
}

static void callback3(uintptr_t arg)
{
	CU_ASSERT_EQUAL(arg , 1000);
	i_lock_cpu();
}

