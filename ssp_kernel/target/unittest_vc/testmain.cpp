/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2010 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 * 
 *  上記著作権者は，以下の (1)～(4) の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改変・
 *  再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作権
 *      表示，この利用条件および下記の無保証規定が，そのままの形でソース
 *      コード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使用
 *      できる形で再配布する場合には，再配布に伴うドキュメント（利用者マ
 *      ニュアルなど）に，上記の著作権表示，この利用条件および下記の無保
 *      証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使用
 *      できない形で再配布する場合には，次のいずれかの条件を満たすこと．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに報
 *        告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損害
 *      からも，上記著作権者およびTOPPERSプロジェクトを免責すること．また，
 *      本ソフトウェアのユーザまたはエンドユーザからのいかなる理由に基づ
 *      く請求からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者およ
 *  びTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的に対す
 *  る適合性も含めて，いかなる保証も行わない．また，本ソフトウェアの利用
 *  により直接的または間接的に生じたいかなる損害に関しても，その責任を負
 *  わない．
 * 
 */

/*
 *  TOPPERS/SSP単体テスト テスト実行部
 */

/*
 *  カバレッジ測定のためにGNU環境でもビルドできるように
 *  している．
 */
#ifndef __GNUC__
	#include "stdafx.h"
#endif
#include <CUnit.h>
#include <Console.h>

/*
 *  テスト関数のプロトタイプ宣言
 */
extern "C"
{

/* タスク管理のテスト */
extern void test_initialize_task(void);
extern void test_search_schedtsk(void);
extern void test_test_dormant(void);
extern void test_make_active(void);
extern void test_run_task(void);
extern void test_dispatcher(void);
extern void test_act_tsk(void);
extern void test_iact_tsk(void);

/* 割込み管理のテスト */
extern void test_interrupt_initialize(void);
extern void test_ena_int(void);
extern void test_dis_int(void);
//extern void test_kernel_interrupt(void);

/* CPU例外のテスト */
extern void test_initialize_exception(void);
//extern void test_kernel_exception(void);

/* システム管理のテスト */
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

/* キュー操作のテスト */
extern void test_queue_initialize(void);
extern void test_queue_insert_prev(void);

/* タイムイベントのテスト */
extern void test_initialize_time_event(void);
extern void test_time_event_enqueue(void);
extern void test_time_event_dequeue(void);
extern void test_signal_time(void);

/* 周期ハンドラのテスト */
extern void test_initialize_cyclic(void);
extern void test_sta_cyc(void);
extern void test_stp_cyc(void);
extern void test_call_cychdr(void);

/* アラームハンドラのテスト */
extern void test_initialize_alarm(void);
extern void test_sta_alm(void);
extern void test_ista_alm(void);
extern void test_stp_alm(void);
extern void test_istp_alm(void);
extern void test_call_almhdr(void);

/* イベントフラグのテスト */
extern void test_initialize_eventflag(void);
extern void test_set_flg(void);
extern void test_iset_flg(void);
extern void test_pol_flg(void);
extern void test_clr_flg(void);

/* データキューのテスト */
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
	
	/* タスク管理のテスト */
	suite = CU_add_suite("Task Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for initialize_task" , test_initialize_task);
	CU_add_test(suite, "Test for search_schedtsk" , test_search_schedtsk);
	CU_add_test(suite, "Test for test_dormant" , test_test_dormant);
	CU_add_test(suite, "Test for make_active" , test_make_active);
	CU_add_test(suite, "Test for run_task" , test_run_task);
	CU_add_test(suite, "Test for dispatcher" , test_dispatcher);
	CU_add_test(suite, "Test for act_tsk" , test_act_tsk);
	CU_add_test(suite, "Test for iact_tsk" , test_iact_tsk);


	/* 割込み管理のテスト */
	suite = CU_add_suite("Interrupt Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for interrupt_initialize" , test_interrupt_initialize);
	CU_add_test(suite, "Test for ena_int" , test_ena_int);
	CU_add_test(suite, "Test for dis_int" , test_dis_int);
	//CU_add_test(suite, "Test for kernel_interrupt" , test_kernel_interrupt);

	/* CPU例外のテスト */
	suite = CU_add_suite("Exception Management Test" , NULL, NULL);
	
	CU_add_test(suite, "Test for initialize_exception" , test_initialize_exception);

	/* システム管理のテスト */
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

	/* 起動，終了のテスト */
	suite = CU_add_suite("System startup/exit Test" , NULL, NULL);
	CU_add_test(suite, "Test for sta_ker" , test_sta_ker);
	CU_add_test(suite, "Test for ext_ker" , test_ext_ker);

	/* キュー操作のテスト */
	suite = CU_add_suite("[Internal Module] queue opration test" , NULL, NULL);
	CU_add_test(suite, "Test for queue_initialize" , test_queue_initialize);
	CU_add_test(suite, "Test for queue_insert_prev" , test_queue_insert_prev);

	/* タイムイベント操作のテスト */
	suite = CU_add_suite("[Internal Module] time event test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_time_event" , test_initialize_time_event);
	CU_add_test(suite, "Test for time_event_enqueue" , test_time_event_enqueue);
	CU_add_test(suite, "Test for time_event_dequeue" , test_time_event_dequeue);
	CU_add_test(suite, "Test for signal_time" , test_signal_time);
	
	/* 周期ハンドラのテスト */
	suite = CU_add_suite("cyclic handler test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_cyclic" , test_initialize_cyclic);
	CU_add_test(suite, "Test for sta_cyc" , test_sta_cyc);
	CU_add_test(suite, "Test for stp_cyc" , test_stp_cyc);
	CU_add_test(suite, "Test for call_cychdr" , test_call_cychdr);

	/* アラームハンドラのテスト */
	suite = CU_add_suite("alarm handler test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_alarm" , test_initialize_alarm);
	CU_add_test(suite, "Test for sta_alm" , test_sta_alm);
	CU_add_test(suite, "Test for stp_alm" , test_stp_alm);
	CU_add_test(suite, "Test for ista_alm" , test_ista_alm);
	CU_add_test(suite, "Test for istp_alm" , test_istp_alm);
	CU_add_test(suite, "Test for call_almhdr" , test_call_almhdr);
	
	/* イベントフラグのテスト */
	suite = CU_add_suite("eventflag test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_eventflag" , test_initialize_eventflag);
	CU_add_test(suite, "Test for set_flg" , test_set_flg);
	CU_add_test(suite, "Test for iset_flg" , test_iset_flg);
	CU_add_test(suite, "Test for pol_flg" , test_pol_flg);
	CU_add_test(suite, "Test for clr_flg" , test_clr_flg);

	/* データキューのテスト */
	suite = CU_add_suite("dataqueue test" , NULL, NULL);
	CU_add_test(suite, "Test for initialize_dataqueue" , test_initialize_dataqueue);
	CU_add_test(suite, "Test for psnd_dtq" , test_psnd_dtq);
	CU_add_test(suite, "Test for ipsnd_dtq" , test_ipsnd_dtq);
	CU_add_test(suite, "Test for prcv_dtq" , test_prcv_dtq);

	CU_console_run_tests();
	CU_cleanup_registry();

	return 0;
}

