/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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
 *  TOPPERS/SSP�P�̃e�X�g �e�X�g���s��
 */

/*
 *  �J�o���b�W����̂��߂�GNU���ł��r���h�ł���悤��
 *  ���Ă���D
 */
#ifndef __GNUC__
	#include "stdafx.h"
#endif
#include <CUnit.h>
#include <Console.h>

/*
 *  �e�X�g�֐��̃v���g�^�C�v�錾
 */
extern "C"
{

/* �^�X�N�Ǘ��̃e�X�g */
extern void test_initialize_task(void);
extern void test_search_schedtsk(void);
extern void test_test_dormant(void);
extern void test_make_active(void);
extern void test_run_task(void);
extern void test_dispatcher(void);
extern void test_act_tsk(void);
extern void test_iact_tsk(void);

/* �����݊Ǘ��̃e�X�g */
extern void test_interrupt_initialize(void);
extern void test_ena_int(void);
extern void test_dis_int(void);
//extern void test_kernel_interrupt(void);

/* CPU��O�̃e�X�g */
extern void test_initialize_exception(void);
//extern void test_kernel_exception(void);

/* �V�X�e���Ǘ��̃e�X�g */
extern void test_loc_cpu(void);
extern void test_iloc_cpu(void);
extern void test_unl_cpu(void);
extern void test_iunl_cpu(void);
extern void test_dis_dsp(void);
extern void test_ena_dsp(void);
extern void test_sns_ctx(void);
extern void test_sns_loc(void);
extern void test_sns_dsp(void);
extern void test_sns_dpn(void);
extern void test_sns_ker(void);

extern void test_sta_ker(void);
extern void test_ext_ker(void);

/* �L���[����̃e�X�g */
extern void test_queue_initialize(void);
extern void test_queue_insert_prev(void);

/* �^�C���C�x���g�̃e�X�g */
extern void test_initialize_time_event(void);
extern void test_time_event_enqueue(void);
extern void test_time_event_dequeue(void);
extern void test_signal_time(void);

/* �����n���h���̃e�X�g */
extern void test_initialize_cyclic(void);
extern void test_sta_cyc(void);
extern void test_stp_cyc(void);
extern void test_call_cychdr(void);

/* �A���[���n���h���̃e�X�g */
extern void test_initialize_alarm(void);
extern void test_sta_alm(void);
extern void test_ista_alm(void);
extern void test_stp_alm(void);
extern void test_istp_alm(void);
extern void test_call_almhdr(void);

/* �C�x���g�t���O�̃e�X�g */
extern void test_initialize_eventflag(void);
extern void test_set_flg(void);
extern void test_iset_flg(void);
extern void test_pol_flg(void);
extern void test_clr_flg(void);

/* �f�[�^�L���[�̃e�X�g */
extern void test_initialize_dataqueue(void);
extern void test_psnd_dtq(void);
extern void test_ipsnd_dtq(void);
extern void test_prcv_dtq(void);
}

#ifndef __GNUC__
int _tmain(int argc, _TCHAR* argv[])
#else
int main(void)
#endif
{
	CU_pSuite suite;

	CU_initialize_registry();
	
	/* �^�X�N�Ǘ��̃e�X�g */
	suite = CU_add_suite("Task Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for initialize_task" , test_initialize_task);
	CU_add_test(suite, "Test for search_schedtsk" , test_search_schedtsk);
	CU_add_test(suite, "Test for test_dormant" , test_test_dormant);
	CU_add_test(suite, "Test for make_active" , test_make_active);
	CU_add_test(suite, "Test for run_task" , test_run_task);
	CU_add_test(suite, "Test for dispatcher" , test_dispatcher);
	CU_add_test(suite, "Test for act_tsk" , test_act_tsk);
	CU_add_test(suite, "Test for iact_tsk" , test_iact_tsk);


	/* �����݊Ǘ��̃e�X�g */
	suite = CU_add_suite("Interrupt Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for interrupt_initialize" , test_interrupt_initialize);
	CU_add_test(suite, "Test for ena_int" , test_ena_int);
	CU_add_test(suite, "Test for dis_int" , test_dis_int);
	//CU_add_test(suite, "Test for kernel_interrupt" , test_kernel_interrupt);

	/* CPU��O�̃e�X�g */
	suite = CU_add_suite("Exception Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for initialize_exception" , test_initialize_exception);

	/* �V�X�e���Ǘ��̃e�X�g */
	suite = CU_add_suite("System Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for loc_cpu" , test_loc_cpu);
	CU_add_test(suite, "Test for iloc_cpu" , test_iloc_cpu);
	CU_add_test(suite, "Test for unl_cpu" , test_unl_cpu);
	CU_add_test(suite, "Test for iunl_cpu" , test_iunl_cpu);
	CU_add_test(suite, "Test for dis_dsp" , test_dis_dsp);
	CU_add_test(suite, "Test for ena_dsp" , test_ena_dsp);
	CU_add_test(suite, "Test for sns_ctx" , test_sns_ctx);
	CU_add_test(suite, "Test for sns_loc" , test_sns_loc);
	CU_add_test(suite, "Test for sns_dsp" , test_sns_dsp);
	CU_add_test(suite, "Test for sns_dpn" , test_sns_dpn);
	CU_add_test(suite, "Test for sns_ker" , test_sns_ker);

	/* �N���C�I���̃e�X�g */
	suite = CU_add_suite("System startup/exit Test" , NULL, NULL);
	CU_add_test(suite, "Test for sta_ker" , test_sta_ker);
	CU_add_test(suite, "Test for ext_ker" , test_ext_ker);

	/* �L���[����̃e�X�g */
	suite = CU_add_suite("[Internal Module] queue opration test" , NULL, NULL);
	CU_add_test(suite, "Test for queue_initialize" , test_queue_initialize);
	CU_add_test(suite, "Test for queue_insert_prev" , test_queue_insert_prev);

	/* �^�C���C�x���g����̃e�X�g */
	suite = CU_add_suite("[Internal Module] time event test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_time_event" , test_initialize_time_event);
	CU_add_test(suite, "Test for time_event_enqueue" , test_time_event_enqueue);
	CU_add_test(suite, "Test for time_event_dequeue" , test_time_event_dequeue);
	CU_add_test(suite, "Test for signal_time" , test_signal_time);
	
	/* �����n���h���̃e�X�g */
	suite = CU_add_suite("cyclic handler test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_cyclic" , test_initialize_cyclic);
	CU_add_test(suite, "Test for sta_cyc" , test_sta_cyc);
	CU_add_test(suite, "Test for stp_cyc" , test_stp_cyc);
	CU_add_test(suite, "Test for call_cychdr" , test_call_cychdr);

	/* �A���[���n���h���̃e�X�g */
	suite = CU_add_suite("alarm handler test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_alarm" , test_initialize_alarm);
	CU_add_test(suite, "Test for sta_alm" , test_sta_alm);
	CU_add_test(suite, "Test for stp_alm" , test_stp_alm);
	CU_add_test(suite, "Test for ista_alm" , test_ista_alm);
	CU_add_test(suite, "Test for istp_alm" , test_istp_alm);
	CU_add_test(suite, "Test for call_almhdr" , test_call_almhdr);
	
	/* �C�x���g�t���O�̃e�X�g */
	suite = CU_add_suite("eventflag test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_eventflag" , test_initialize_eventflag);
	CU_add_test(suite, "Test for set_flg" , test_set_flg);
	CU_add_test(suite, "Test for iset_flg" , test_iset_flg);
	CU_add_test(suite, "Test for pol_flg" , test_pol_flg);
	CU_add_test(suite, "Test for clr_flg" , test_clr_flg);

	/* �f�[�^�L���[�̃e�X�g */
	suite = CU_add_suite("dataqueue test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_dataqueue" , test_initialize_dataqueue);
	CU_add_test(suite, "Test for psnd_dtq" , test_psnd_dtq);
	CU_add_test(suite, "Test for ipsnd_dtq" , test_ipsnd_dtq);
	CU_add_test(suite, "Test for prcv_dtq" , test_prcv_dtq);

	CU_console_run_tests();
	CU_cleanup_registry();

	return 0;
}

