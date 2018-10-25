
	$INCLUDE "prc_asm_symbol.inc"

	.SECTION .textf , TEXTF
;
;  ディスパッチャの動作開始
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
	MOV PSW , #(TIPM_LOCK << 1)
	EI
	
	; ディスパッチャへ
	BR	!!__kernel_dispatcher


__kernel_interrupt:
	; 割込み回数を加算
	INC !_intnest
	
	; log_inh_enterの呼び出し
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
	; 割込みハンドラの呼び出し
$IFDEF LOG_INH_LEAVE
	PUSH BC
$ENDIF
	EI
	CALL	HL
	DI
	
	; 割込みハンドラで変更された状態を元に戻す
	; 割込み優先度マスクは割込みコンテキストで修正できないため戻す必要がない
	MOV !_lock_flag, #0
	
	; log_inh_leaveの呼び出し
$IFDEF LOG_INH_LEAVE
	POP BC
$ENDIF
$IFDEF LOG_INH_LEAVE
	MOVW AX, BC
	call !!_log_inh_leave
$ENDIF

	; 割込み回数を減算
	DEC !_intnest
	BNZ  $__kernel_ret_int
	; reqflgをチェック，スケジューラ実行要否をチェック
	CMP !__kernel_reqflg, #1
	BNZ  $__kernel_ret_int
	
__kernel_call_task:
	MOV !__kernel_reqflg, #0
	; スケジューラを起動し，実行すべきタスクがあるならタスク実行ルーチンを呼び出す
	PUSH PSW
	MOV PSW, #0x86
	CALL !!__kernel_search_schedtsk
	CALL !!__kernel_run_task
	POP PSW
__kernel_ret_int:
	; コンテキストを復帰して割込み元へ戻る
	POP AX
	MOV ES, A
	POP AX
	MOV ES, A
	POP HL
	POP DE
	POP BC
	POP AX
	RETI


