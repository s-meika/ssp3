
	$INCLUDE "prc_asm_symbol.inc"

	.SECTION .textf , TEXTF
;
;  �ǥ����ѥå����ư���
;

	.PUBLIC		__kernel_start_dispatch
	.EXTERN		_dispatcher
	.PUBLIC		__kernel_interrupt

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
	MOV PSW , #(TIPM_LOCK << 2)
	EI
	
	; �ǥ����ѥå����
	BR	!!__kernel_dispatcher


__kernel_interrupt:
	RETI


