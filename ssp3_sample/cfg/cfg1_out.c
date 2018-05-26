/* cfg1_out.c */
#define TOPPERS_CFG1_OUT
#include "kernel/kernel_int.h"
#include "sample1.h"
#include "target_timer.h"
#include "chip_timer.h"
#include "target_syssvc.h"
#include "target_timer.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/banner.h"
#include "syssvc/syslog.h"
#include "syssvc/logtask.h"

#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"
#include <limits.h>

const uint32_t TOPPERS_magic_number = 0x12345678;
const uint32_t TOPPERS_sizeof_signed_t = sizeof(signed_t);

const unsigned_t TOPPERS_cfg_CHAR_BIT = (unsigned_t)(CHAR_BIT);
const signed_t TOPPERS_cfg_SCHAR_MAX = (signed_t)(SCHAR_MAX);
const signed_t TOPPERS_cfg_SCHAR_MIN = (signed_t)(SCHAR_MIN);
const unsigned_t TOPPERS_cfg_UCHAR_MAX = (unsigned_t)(UCHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MAX = (signed_t)(CHAR_MAX);
const signed_t TOPPERS_cfg_CHAR_MIN = (signed_t)(CHAR_MIN);
const signed_t TOPPERS_cfg_SHRT_MAX = (signed_t)(SHRT_MAX);
const signed_t TOPPERS_cfg_SHRT_MIN = (signed_t)(SHRT_MIN);
const unsigned_t TOPPERS_cfg_USHRT_MAX = (unsigned_t)(USHRT_MAX);
const signed_t TOPPERS_cfg_INT_MAX = (signed_t)(INT_MAX);
const signed_t TOPPERS_cfg_INT_MIN = (signed_t)(INT_MIN);
const unsigned_t TOPPERS_cfg_UINT_MAX = (unsigned_t)(UINT_MAX);
const signed_t TOPPERS_cfg_LONG_MAX = (signed_t)(LONG_MAX);
const signed_t TOPPERS_cfg_LONG_MIN = (signed_t)(LONG_MIN);
const unsigned_t TOPPERS_cfg_ULONG_MAX = (unsigned_t)(ULONG_MAX);
#if defined(SIL_ENDIAN_BIG)
const signed_t TOPPERS_cfg_SIL_ENDIAN_BIG = (signed_t)(true);
#endif
#if defined(SIL_ENDIAN_LITTLE)
const signed_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = (signed_t)(true);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = (unsigned_t)(TA_NULL);
const unsigned_t TOPPERS_cfg_TA_ACT = (unsigned_t)(TA_ACT);
const unsigned_t TOPPERS_cfg_TA_RSTR = (unsigned_t)(TA_RSTR);
const unsigned_t TOPPERS_cfg_TA_STA = (unsigned_t)(TA_STA);
const unsigned_t TOPPERS_cfg_TA_CLR = (unsigned_t)(TA_CLR);
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = (unsigned_t)(TA_NONKERNEL);
const unsigned_t TOPPERS_cfg_TA_ENAINT = (unsigned_t)(TA_ENAINT);
const unsigned_t TOPPERS_cfg_TA_EDGE = (unsigned_t)(TA_EDGE);
const unsigned_t TOPPERS_cfg_TNFY_HANDLER = (unsigned_t)(TNFY_HANDLER);
const unsigned_t TOPPERS_cfg_TNFY_SETVAR = (unsigned_t)(TNFY_SETVAR);
const unsigned_t TOPPERS_cfg_TNFY_INCVAR = (unsigned_t)(TNFY_INCVAR);
const unsigned_t TOPPERS_cfg_TNFY_ACTTSK = (unsigned_t)(TNFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TNFY_SETFLG = (unsigned_t)(TNFY_SETFLG);
const unsigned_t TOPPERS_cfg_TNFY_SNDDTQ = (unsigned_t)(TNFY_SNDDTQ);
const unsigned_t TOPPERS_cfg_TENFY_SETVAR = (unsigned_t)(TENFY_SETVAR);
const unsigned_t TOPPERS_cfg_TENFY_INCVAR = (unsigned_t)(TENFY_INCVAR);
const unsigned_t TOPPERS_cfg_TENFY_ACTTSK = (unsigned_t)(TENFY_ACTTSK);
const unsigned_t TOPPERS_cfg_TENFY_SETFLG = (unsigned_t)(TENFY_SETFLG);
const unsigned_t TOPPERS_cfg_TENFY_SNDDTQ = (unsigned_t)(TENFY_SNDDTQ);
const unsigned_t TOPPERS_cfg_DEFAULT_ISTKSZ = (unsigned_t)(DEFAULT_ISTKSZ);
const signed_t TOPPERS_cfg_TMIN_TPRI = (signed_t)(TMIN_TPRI);
const signed_t TOPPERS_cfg_TMAX_TPRI = (signed_t)(TMAX_TPRI);
const signed_t TOPPERS_cfg_TMIN_ISRPRI = (signed_t)(TMIN_ISRPRI);
const signed_t TOPPERS_cfg_TMAX_ISRPRI = (signed_t)(TMAX_ISRPRI);
const unsigned_t TOPPERS_cfg_TBIT_FLGPTN = (unsigned_t)(TBIT_FLGPTN);
const unsigned_t TOPPERS_cfg_TMAX_MAXCYC = (unsigned_t)(TMAX_MAXCYC);
const unsigned_t TOPPERS_cfg_TMAX_MAXALM = (unsigned_t)(TMAX_MAXALM);
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = (unsigned_t)(TMAX_RELTIM);
const signed_t TOPPERS_cfg_TMIN_INTPRI = (signed_t)(TMIN_INTPRI);
const signed_t TOPPERS_cfg_TMIN_TSKID = (signed_t)(TMIN_TSKID);
const signed_t TOPPERS_cfg_TMIN_FLGID = (signed_t)(TMIN_FLGID);
const signed_t TOPPERS_cfg_TMIN_DTQID = (signed_t)(TMIN_DTQID);
const signed_t TOPPERS_cfg_TMIN_CYCID = (signed_t)(TMIN_CYCID);
const signed_t TOPPERS_cfg_TMIN_ALMID = (signed_t)(TMIN_ALMID);
#if defined(OMIT_INITIALIZE_INTERRUPT)
const signed_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = (signed_t)(true);
#endif
const signed_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = (signed_t)(true);
#if defined(TARGET_TSKATR)
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = (unsigned_t)(TARGET_TSKATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = (unsigned_t)(0);
#endif
#if defined(TARGET_INTATR)
const unsigned_t TOPPERS_cfg_TARGET_INTATR = (unsigned_t)(TARGET_INTATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_INTATR = (unsigned_t)(0);
#endif
#if defined(TARGET_INHATR)
const unsigned_t TOPPERS_cfg_TARGET_INHATR = (unsigned_t)(TARGET_INHATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_INHATR = (unsigned_t)(0);
#endif
#if defined(TARGET_ISRATR)
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = (unsigned_t)(TARGET_ISRATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = (unsigned_t)(0);
#endif
#if defined(TARGET_EXCATR)
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = (unsigned_t)(TARGET_EXCATR);
#else
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = (unsigned_t)(0);
#endif
#if defined(TARGET_MIN_STKSZ)
const unsigned_t TOPPERS_cfg_TARGET_MIN_STKSZ = (unsigned_t)(TARGET_MIN_STKSZ);
#else
const unsigned_t TOPPERS_cfg_TARGET_MIN_STKSZ = (unsigned_t)(1);
#endif
#if defined(TARGET_MIN_ISTKSZ)
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = (unsigned_t)(TARGET_MIN_ISTKSZ);
#else
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = (unsigned_t)(1);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ID = (unsigned_t)(sizeof(ID));
const unsigned_t TOPPERS_cfg_sizeof_uint_t = (unsigned_t)(sizeof(uint_t));
const unsigned_t TOPPERS_cfg_sizeof_SIZE = (unsigned_t)(sizeof(size_t));
const unsigned_t TOPPERS_cfg_sizeof_ATR = (unsigned_t)(sizeof(ATR));
const unsigned_t TOPPERS_cfg_sizeof_PRI = (unsigned_t)(sizeof(PRI));
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = (unsigned_t)(sizeof(void*));
const unsigned_t TOPPERS_cfg_sizeof_VP = (unsigned_t)(sizeof(void*));
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = (unsigned_t)(sizeof(intptr_t));
const unsigned_t TOPPERS_cfg_sizeof_FP = (unsigned_t)(sizeof(FP));
const unsigned_t TOPPERS_cfg_sizeof_INHNO = (unsigned_t)(sizeof(INHNO));
const unsigned_t TOPPERS_cfg_sizeof_INTNO = (unsigned_t)(sizeof(INTNO));
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = (unsigned_t)(sizeof(EXCNO));
#if defined(CHECK_FUNC_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = (unsigned_t)(CHECK_FUNC_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = (unsigned_t)(1);
#endif
#if defined(CHECK_STACK_ALIGN)
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = (unsigned_t)(CHECK_STACK_ALIGN);
#else
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = (unsigned_t)(1);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TASK = (unsigned_t)(sizeof(TASK));
const unsigned_t TOPPERS_cfg_sizeof_TMEHDR = (unsigned_t)(sizeof(TMEHDR));
const unsigned_t TOPPERS_cfg_TKERNEL_PRVER = (unsigned_t)(TKERNEL_PRVER);
const signed_t TOPPERS_cfg_TIPM_LOCK = (signed_t)(TIPM_LOCK);
const signed_t TOPPERS_cfg_IIPM_ENAALL = (signed_t)(IIPM_ENAALL);
const unsigned_t TOPPERS_cfg_TMAX_INTNO = (unsigned_t)(TMAX_INTNO);
const unsigned_t TOPPERS_cfg_TA_POSEDGE = (unsigned_t)(TA_POSEDGE);
const unsigned_t TOPPERS_cfg_TA_NEGEDGE = (unsigned_t)(TA_NEGEDGE);


#line 7 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
#line 7 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_1 = (unsigned_t)(TA_NULL);

#line 8 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
#line 8 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_2 = (unsigned_t)(TA_NULL);

#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhno_3 = (unsigned_t)(INHNO_HRT);
#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_inhatr_3 = (unsigned_t)(TA_NULL);

#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_4 = (unsigned_t)(INTNO_HRT);
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_4 = (unsigned_t)(TA_ENAINT|INTATR_HRT);
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_timer.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_4 = (signed_t)(INTPRI_HRT);

#line 8 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
#line 8 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_5 = (unsigned_t)(TA_NULL);

#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_isratr_6 = (unsigned_t)(TA_NULL);
#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_6 = (unsigned_t)(INTNO_SIO_TX);
#line 9 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const signed_t TOPPERS_cfg_valueof_isrpri_6 = (signed_t)(1);

#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_isratr_7 = (unsigned_t)(TA_NULL);
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_7 = (unsigned_t)(INTNO_SIO_RX);
#line 10 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const signed_t TOPPERS_cfg_valueof_isrpri_7 = (signed_t)(2);

#line 11 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
#line 11 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_8 = (unsigned_t)(INTNO_SIO_TX);
#line 11 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_8 = (unsigned_t)(INTATR_SIO);
#line 11 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_8 = (signed_t)(INTPRI_SIO);

#line 12 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
#line 12 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intno_9 = (unsigned_t)(INTNO_SIO_RX);
#line 12 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_intatr_9 = (unsigned_t)(INTATR_SIO);
#line 12 "../../ssp_kernel/arch/rl78_ccrl/rl78_g13/chip_serial.cfg"
const signed_t TOPPERS_cfg_valueof_intpri_9 = (signed_t)(INTPRI_SIO);

#line 13 "../../ssp_kernel/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
#line 13 "../../ssp_kernel/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_10 = (unsigned_t)(TA_NULL);

#line 14 "../../ssp_kernel/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
#line 14 "../../ssp_kernel/syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_11 = (unsigned_t)(TA_NULL);

#line 10 "../../ssp_kernel/syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
#line 10 "../../ssp_kernel/syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_12 = (unsigned_t)(TA_NULL);

#line 10 "../../ssp_kernel/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
#line 10 "../../ssp_kernel/syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_iniatr_13 = (unsigned_t)(TA_NULL);

#line 10 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
#define LOGTASK	(<>)
#line 10 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_14 = (unsigned_t)(TA_ACT);
#line 10 "../../ssp_kernel/syssvc/logtask.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_14 = (signed_t)(LOGTASK_PRIORITY);
#line 10 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_14 = (unsigned_t)(LOGTASK_STACK_SIZE);

#line 12 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
#define LOCCYC	(<>)
#line 12 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_15 = (unsigned_t)(TA_ACT);
#line 12 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_15 = (unsigned_t)(TNFY_HANDLER);
#line 12 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_cyctim_15 = (unsigned_t)(LOGTASK_INTERVAL);
#line 12 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycphs_15 = (unsigned_t)(LOGTASK_INTERVAL);

#line 15 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
#line 15 "../../ssp_kernel/syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_teratr_16 = (unsigned_t)(TA_NULL);

#line 13 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
#define INIT_TASK	(<>)
#line 13 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_17 = (unsigned_t)(TA_ACT);
#line 13 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_17 = (signed_t)(INIT_PRIORITY);
#line 13 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_17 = (unsigned_t)(STACK_SIZE);

#line 14 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
#define MAIN_TASK	(<>)
#line 14 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_18 = (unsigned_t)(TA_NULL);
#line 14 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_18 = (signed_t)(MAIN_PRIORITY);
#line 14 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_18 = (unsigned_t)(STACK_SIZE);

#line 15 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
#define TASK1	(<>)
#line 15 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_19 = (unsigned_t)(TA_NULL);
#line 15 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_19 = (signed_t)(TASK1_PRIORITY);
#line 15 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_19 = (unsigned_t)(STACK_SIZE);

#line 16 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
#define TASK2	(<>)
#line 16 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_20 = (unsigned_t)(TA_NULL);
#line 16 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_20 = (signed_t)(TASK2_PRIORITY);
#line 16 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_20 = (unsigned_t)(STACK_SIZE);

#line 17 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
#define TASK3	(<>)
#line 17 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_21 = (unsigned_t)(TA_NULL);
#line 17 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_atskpri_21 = (signed_t)(TASK3_PRIORITY);
#line 17 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_21 = (unsigned_t)(STACK_SIZE);

#line 19 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
#line 19 "../../ssp_kernel/sample/sample1.cfg"
const signed_t TOPPERS_cfg_valueof_exepri_22 = (signed_t)(TASK3_EXEPRIORITY);

#ifdef WITH_EXTENTION

#line 22 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
#define MAIN_CYC	(<>)
#line 22 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_23 = (unsigned_t)(TA_NULL);
#line 22 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_23 = (unsigned_t)(TNFY_HANDLER);
#line 22 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cyctim_23 = (unsigned_t)(100);
#line 22 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycphs_23 = (unsigned_t)(100);

#line 23 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
#define CYC1	(<>)
#line 23 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_24 = (unsigned_t)(TA_NULL);
#line 23 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_24 = (unsigned_t)(TNFY_HANDLER);
#line 23 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cyctim_24 = (unsigned_t)(2000);
#line 23 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycphs_24 = (unsigned_t)(2000);

#line 24 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
#define ALM1	(<>)
#line 24 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_25 = (unsigned_t)(TA_NULL);
#line 24 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_nfymode_25 = (unsigned_t)(TNFY_HANDLER);

#line 26 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
#define FLG1	(<>)
#line 26 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_flgatr_26 = (unsigned_t)(TA_NULL);
#line 26 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_iflgptn_26 = (unsigned_t)(0x00000000);

#line 27 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
#define DTQ1	(<>)
#line 27 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_27 = (unsigned_t)(TA_NULL);
#line 27 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqcnt_27 = (unsigned_t)(3);

#endif

#line 30 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
#line 30 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_stksz_28 = (unsigned_t)(ALL_STACKSIZE);

#line 31 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
#line 31 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_istksz_29 = (unsigned_t)(INTERRUPT_STACKSIZE);

#ifdef CPUEXC1

#line 34 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
#line 34 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_excno_30 = (unsigned_t)(CPUEXC1);
#line 34 "../../ssp_kernel/sample/sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_excatr_30 = (unsigned_t)(TA_NULL);

#endif

