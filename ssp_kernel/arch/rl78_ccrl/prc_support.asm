
	$INCLUDE "prc_asm_symbol.inc"

	.SECTION .textf , TEXTF
;
;  ディスパッチャの動作開始
;

	.PUBLIC		__kernel_start_dispatch
	.EXTERN		_dispatcher
	.PUBLIC		__kernel_interrupt

__kernel_start_dispatch:
	;/*
	; *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
	; * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
	; *  タスクコンテキストと同等）で呼び出されることを想定している．
	; *
	; *  prc_initializeで，lock_flagをtrueに，saved_iipmをIIPM_ENAALLに
	; *  初期化しているため，カーネル管理外の割込みを許可することで，
	; *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
	; *  また，task_initializeでdisdspをfalseに初期化しているため，ディ
	; *  スパッチ許可状態になっている．
	; */
	
	
	; CPUロック状態への移行と全割込み禁止状態の解除
	MOV PSW , #(TIPM_LOCK << 2)
	EI
	
	; ディスパッチャへ
	BR	!!__kernel_dispatcher


__kernel_interrupt:
	RETI


