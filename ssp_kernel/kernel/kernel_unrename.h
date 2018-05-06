/* This file is generated from kernel_rename.def by genrename. */

/* This file is included only when kernel_rename.h has been included. */
#ifdef TOPPERS_KERNEL_RENAME_H
#undef TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#undef kerflg
#undef exit_kernel

/*
 *  task.c
 */
#undef runtsk_curpri
#undef runtsk_ipri
#undef ready_primap
#undef actque_bitmap
#undef reqflg
#undef disdsp
#undef get_ipri
#undef bitmap_search_table
#undef bitmap_search
#undef primap_empty
#undef primap_test
#undef primap_search
#undef primap_set
#undef primap_clear
#undef search_schedtsk
#undef test_dormant
#undef initialize_task
#undef make_active
#undef run_task
#undef dispatcher

/*
 *  interrupt.c
 */
#undef initialize_interrupt

/*
 *  exception.c
 */
#undef initialize_exception


/*
 *  alarm.c
 */
#undef initialize_alarm
#undef call_almhdr

/*
 *  cyclic.c
 */
#undef initialize_cyclic
#undef call_cychdr

/*
 *  dataqueue.c
 */
#undef initialize_dataqueue
#undef send_data
#undef receive_data

/*
 *  eventflag.c
 */
#undef initialize_eventflag

/*
 *  time_event.c
 */
#undef current_time
#undef min_time
#undef initialize_time_event
#undef time_event_enqueue
#undef time_event_dequeue
#undef signal_time


/*
 *  kernel_cfg.c
 */
#undef tmax_tskid
#undef tinib_tskatr
#undef init_rdypmap
#undef tinib_exinf
#undef tinib_task
#undef tinib_epriority

#undef tmax_flgid
#undef flginib_atr
#undef flginib_iflgptn
#undef flgcb_flgptn

#undef tmax_dtqid
#undef dtqinib_atr
#undef dtqinib_size
#undef dtqinib_data
#undef dtqcb_count
#undef dtqcb_head
#undef dtqcb_tail

#undef tnum_inhno
#undef inhinib_inhno
#undef inhinib_inhatr
#undef inhinib_entry

#undef tnum_intno
#undef intinib_intno
#undef intinib_intatr
#undef intinib_intpri

#undef tnum_excno
#undef excinib_excno
#undef excinib_excatr
#undef excinib_entry

#undef tmax_cycid
#undef cycevtid_offset
#undef cycinib_cycact
#undef cycinib_exinf
#undef cycinib_nfyhdr
#undef cycinib_cyctim
#undef cycinib_cycphs
#undef cyccb_evttim
#undef cyccb_cycact

#undef tmax_almid
#undef almevtid_offset
#undef alminib_almhdr
#undef alminib_exinf
#undef almcb_almact

#undef tnum_tmevt_queue
#undef tmevt_queue
#undef tmevt_time
#undef tmevt_callback
#undef tmevt_arg

#undef stksz
#undef stk
#undef istkpt

#undef initialize_object
#undef call_inirtn
#undef call_terrtn

/*
 *  target_config.c
 */
#undef target_initialize
#undef target_exit


#include "chip_unrename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
