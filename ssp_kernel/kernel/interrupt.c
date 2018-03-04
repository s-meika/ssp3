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
 *		割込み管理機能
 */

#include "kernel_impl.h"
#include "check.h"
#include "interrupt.h"

/*
 *  トレースログマクロのデフォルト定義
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
 *  割込み番号の範囲の判定
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
 *  割込み管理機能の初期化
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
 *  割込みの禁止［NGKI3555］
 */
#ifdef TOPPERS_dis_int
#ifdef TOPPERS_TARGET_SUPPORT_DIS_INT					/*［NGKI3093］*/

ER
dis_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;
	
	LOG_DIS_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_DISINT(intno));		/*［NGKI3083］［NGKI3087］*/
	
	locked = sense_lock();
	
	if (!locked) {
		lock_cpu();
	}
	
	if (check_intno_cfg(intno)) {
		disable_int(intno);						/*［NGKI3086］*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*［NGKI3085］*/
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
 *  割込みの許可［NGKI3556］
 */
#ifdef TOPPERS_ena_int
#ifdef TOPPERS_TARGET_SUPPORT_ENA_INT					/*［NGKI3106］*/

ER
ena_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_ENA_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_DISINT(intno));		/*［NGKI3096］［NGKI3100］*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	
	if (check_intno_cfg(intno)) {
		enable_int(intno);						/*［NGKI3099］*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*［NGKI3098］*/
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
 *  割込み要求のクリア［NGKI3920］
 */
#ifdef TOPPERS_clr_int
#ifdef TOPPERS_TARGET_SUPPORT_CLR_INT					/*［NGKI3927］*/

ER
clr_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_CLR_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_CLRINT(intno));		/*［NGKI3921］［NGKI3930］*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno) && check_intno_clear(intno)) {
		clear_int(intno);						/*［NGKI3924］*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*［NGKI3923］［NGKI3929］*/
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
 *  割込みの要求［NGKI3932］
 */
#ifdef TOPPERS_ras_int
#ifdef TOPPERS_SUPPORT_RAS_INT					/*［NGKI3939］*/

ER
ras_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_RAS_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_RASINT(intno));		/*［NGKI3933］［NGKI3942］*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno) && check_intno_raise(intno)) {
		raise_int(intno);						/*［NGKI3936］*/
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;							/*［NGKI3935］［NGKI3941］*/
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
 *  割込み要求のチェック［NGKI3944］
 */
#ifdef TOPPERS_prb_int
#ifdef TOPPERS_SUPPORT_PRB_INT					/*［NGKI3951］*/

ER_BOOL
prb_int(INTNO intno)
{
	bool_t	locked;
	ER		ercd;

	LOG_PRB_INT_ENTER(intno);
	CHECK_PAR(VALID_INTNO_PRBINT(intno));		/*［NGKI3945］［NGKI3952］*/

	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (check_intno_cfg(intno)) {
		ercd = (ER_BOOL) probe_int(intno);		/*［NGKI3948］*/
	}
	else {
		ercd = E_OBJ;							/*［NGKI3947］*/
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

