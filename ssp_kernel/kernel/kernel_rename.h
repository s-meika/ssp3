/* This file is generated from kernel_rename.def by genrename. */

#ifndef TOPPERS_KERNEL_RENAME_H
#define TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#define kerflg						_kernel_kerflg
#define exit_kernel					_kernel_exit_kernel

/*
 *  task.c
 */
#define runtsk_curpri				_kernel_runtsk_curpri
#define runtsk_ipri					_kernel_runtsk_ipri
#define ready_primap				_kernel_ready_primap
#define actque_bitmap				_kernel_actque_bitmap
#define reqflg						_kernel_reqflg
#define disdsp						_kernel_disdsp
#define get_ipri					_kernel_get_ipri
#define bitmap_search_table			_kernel_bitmap_search_table
#define bitmap_search				_kernel_bitmap_search
#define primap_empty				_kernel_primap_empty
#define primap_test					_kernel_primap_test
#define primap_search				_kernel_primap_search
#define primap_set					_kernel_primap_set
#define primap_clear				_kernel_primap_clear
#define search_schedtsk				_kernel_search_schedtsk
#define test_dormant				_kernel_test_dormant
#define initialize_task				_kernel_initialize_task
#define make_active					_kernel_make_active
#define run_task					_kernel_run_task
#define dispatcher					_kernel_dispatcher

/*
 *  interrupt.c
 */
#define initialize_interrupt		_kernel_initialize_interrupt

/*
 *  exception.c
 */
#define initialize_exception		_kernel_initialize_exception


/*
 *  alarm.c
 */
#define initialize_alarm			_kernel_initialize_alarm
#define call_almhdr					_kernel_call_almhdr

/*
 *  cyclic.c
 */
#define initialize_cyclic			_kernel_initialize_cyclic
#define call_cychdr					_kernel_call_cychdr

/*
 *  dataqueue.c
 */
#define initialize_dataqueue		_kernel_initialize_dataqueue
#define send_data					_kernel_send_data
#define receive_data				_kernel_receive_data

/*
 *  eventflag.c
 */
#define initialize_eventflag		_kernel_initialize_eventflag

/*
 *  time_event.c
 */
#define current_time				_kernel_current_time
#define min_time					_kernel_min_time
#define initialize_time_event		_kernel_initialize_time_event
#define time_event_enqueue			_kernel_time_event_enqueue
#define time_event_dequeue			_kernel_time_event_dequeue
#define signal_time					_kernel_signal_time


/*
 *  kernel_cfg.c
 */
#define tmax_tskid					_kernel_tmax_tskid
#define tinib_tskatr				_kernel_tinib_tskatr
#define init_rdypmap				_kernel_init_rdypmap
#define tinib_exinf					_kernel_tinib_exinf
#define tinib_task					_kernel_tinib_task
#define tinib_epriority				_kernel_tinib_epriority

#define tmax_flgid					_kernel_tmax_flgid
#define flginib_atr					_kernel_flginib_atr
#define flginib_iflgptn				_kernel_flginib_iflgptn
#define flgcb_flgptn				_kernel_flgcb_flgptn

#define tmax_dtqid					_kernel_tmax_dtqid
#define dtqinib_atr					_kernel_dtqinib_atr
#define dtqinib_size				_kernel_dtqinib_size
#define dtqinib_data				_kernel_dtqinib_data
#define dtqcb_count					_kernel_dtqcb_count
#define dtqcb_head					_kernel_dtqcb_head
#define dtqcb_tail					_kernel_dtqcb_tail

#define tnum_inhno					_kernel_tnum_inhno
#define inhinib_inhno				_kernel_inhinib_inhno
#define inhinib_inhatr				_kernel_inhinib_inhatr
#define inhinib_entry				_kernel_inhinib_entry

#define tnum_intno					_kernel_tnum_intno
#define intinib_intno				_kernel_intinib_intno
#define intinib_intatr				_kernel_intinib_intatr
#define intinib_intpri				_kernel_intinib_intpri

#define tnum_excno					_kernel_tnum_excno
#define excinib_excno				_kernel_excinib_excno
#define excinib_excatr				_kernel_excinib_excatr
#define excinib_entry				_kernel_excinib_entry

#define tmax_cycid					_kernel_tmax_cycid
#define cycevtid_offset				_kernel_cycevtid_offset
#define cycinib_cycact				_kernel_cycinib_cycact
#define cycinib_exinf				_kernel_cycinib_exinf
#define cycinib_nfyhdr				_kernel_cycinib_nfyhdr
#define cycinib_cyctim				_kernel_cycinib_cyctim
#define cycinib_cycphs				_kernel_cycinib_cycphs
#define cyccb_evttim				_kernel_cyccb_evttim
#define cyccb_cycact				_kernel_cyccb_cycact

#define tmax_almid					_kernel_tmax_almid
#define almevtid_offset				_kernel_almevtid_offset
#define alminib_almhdr				_kernel_alminib_almhdr
#define alminib_exinf				_kernel_alminib_exinf
#define almcb_almact				_kernel_almcb_almact

#define tnum_tmevt_queue			_kernel_tnum_tmevt_queue
#define tmevt_queue					_kernel_tmevt_queue
#define tmevt_time					_kernel_tmevt_time
#define tmevt_callback				_kernel_tmevt_callback
#define tmevt_arg					_kernel_tmevt_arg

#define stksz						_kernel_stksz
#define stk							_kernel_stk
#define istkpt						_kernel_istkpt

#define initialize_object			_kernel_initialize_object
#define call_inirtn					_kernel_call_inirtn
#define call_terrtn					_kernel_call_terrtn

/*
 *  target_config.c
 */
#define target_initialize			_kernel_target_initialize
#define target_exit					_kernel_target_exit


#include "chip_rename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
