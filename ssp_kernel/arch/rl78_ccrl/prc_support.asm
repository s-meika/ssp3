
	$INCLUDE "prc_asm_symbol.inc"

	.SECTION .textf , TEXTF
;
;  �ǥ����ѥå����ư���
;

	.PUBLIC		__kernel_start_dispatch
	.PUBLIC		__kernel_interrupt
	.EXTERN		__kernel__dispatcher
	.EXTERN		_intnest
	.EXTERN		_lock_flag
	.EXTERN		__kernel_reqflg
	.EXTERN		__kernel_search_schedtsk
	.EXTERN		__kernel_run_task

__kernel_start_dispatch:
	;/*
	; *  ���Υ롼����ϡ������ͥ뵯ư���ˡ����٤Ƥγ���ߤ�ػߤ�������
	; * �ʳ���ߥ�å����֤�Ʊ���ˤǸƤӽФ���롥�ޤ�������ߥ⡼�ɡ���
	; *  ����������ƥ����Ȥ�Ʊ���ˤǸƤӽФ���뤳�Ȥ����ꤷ�Ƥ��롥
	; *
	; *  prc_initialize�ǡ�lock_flag��true�ˡ�saved_iipm��IIPM_ENAALL��
	; *  ��������Ƥ��뤿�ᡤ�����ͥ�������γ���ߤ���Ĥ��뤳�Ȥǡ�
	; *  CPU��å����֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ˤʤ롥
	; *  �ޤ���task_initialize��disdsp��false�˽�������Ƥ��뤿�ᡤ�ǥ�
	; *  ���ѥå����ľ��֤ˤʤäƤ��롥
	; */
	
	
	; CPU��å����֤ؤΰܹԤ�������߶ػ߾��֤β��
	MOV PSW , #(TIPM_LOCK << 1)
	EI
	
	; �ǥ����ѥå����
	BR	!!__kernel_dispatcher


__kernel_interrupt:
	; ����߲����û�
	INC !_intnest
	
	; log_inh_enter�θƤӽФ�
$IFDEF LOG_INH_ENTER
	PUSH HL
$IFDEF LOG_INH_LEAVE
	PUSH BC
$ENDIF
	MOVW AX, BC
	call !!_log_inh_enter
$IFDEF LOG_INH_LEAVE
	POP BC
$ENDIF
	POP HL
$ENDIF

__kernel_call_int_handler:
	; ����ߥϥ�ɥ�θƤӽФ�
$IFDEF LOG_INH_LEAVE
	PUSH BC
$ENDIF
	EI
	CALL	HL
	DI
	
	; ����ߥϥ�ɥ���ѹ����줿���֤򸵤��᤹
	; �����ͥ���٥ޥ����ϳ���ߥ���ƥ����Ȥǽ����Ǥ��ʤ������᤹ɬ�פ��ʤ�
	MOV !_lock_flag, #0
	
	; log_inh_leave�θƤӽФ�
$IFDEF LOG_INH_LEAVE
	POP BC
$ENDIF
$IFDEF LOG_INH_LEAVE
	MOVW AX, BC
	call !!_log_inh_leave
$ENDIF

	; ����߲���򸺻�
	DEC !_intnest
	BNZ  $__kernel_ret_int
	; reqflg������å����������塼��¹����ݤ�����å�
	CMP !__kernel_reqflg, #1
	BNZ  $__kernel_ret_int
	
__kernel_call_task:
	MOV !__kernel_reqflg, #0
	; �������塼���ư�����¹Ԥ��٤�������������ʤ饿�����¹ԥ롼�����ƤӽФ�
	PUSH PSW
	MOV PSW, #0x86
	CALL !!__kernel_search_schedtsk
	CALL !!__kernel_run_task
	POP PSW
__kernel_ret_int:
	; ����ƥ����Ȥ��������Ƴ���߸������
	POP AX
	MOV ES, A
	POP AX
	MOV ES, A
	POP HL
	POP DE
	POP BC
	POP AX
	RETI


