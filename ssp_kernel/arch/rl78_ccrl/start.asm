; 
;  TOPPERS/SSP Kernel
;      Smallest Set Profile Kernel
; 
;  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
;              Graduate School of Information Science, Nagoya Univ., JAPAN
;  Copyright (C) 2015 by Naoki Saito
;              Nagoya Municipal Industrial Research Institute, JAPAN
;  Copyright (C) 2017 by Meika Sugimoto
; 
;  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
;  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
;  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
;  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
;      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
;      スコード中に含まれていること．
;  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
;      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
;      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
;      の無保証規定を掲載すること．
;  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
;      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
;      と．
;    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
;        作権表示，この利用条件および下記の無保証規定を掲載すること．
;    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
;        報告すること．
;  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
;      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
;      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
;      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
;      免責すること．
; 
;  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
;  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
;  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
;  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
;  の責任を負わない．
; 
; 


	.public _start
	.extern _sta_ker
	.extern _hardware_init_hook
	.extern _software_init_hook

.SECTION .start , TEXTF
_start:

; 割込み禁止
	DI

; スタックポインタの初期化
	MOVW	DE , #__kernel_istkpt
	MOVW	AX , [DE]
	MOVW	SP , AX

;
; .bssの初期化
;
	MOVW	HL , #LOWW( STARTOF( .bss ) )
	MOV	ES , #HIGHW( STARTOF( .bss ) )
	MOVW	AX , #LOWW( STARTOF( .bss ) + SIZEOF( .bss ) )
bss_clear_loop:
	CMPW	AX , HL
	BZ		$bss_clear_end
	MOV		ES:[HL] , #0
	INCW	HL
	BR 		$bss_clear_loop
bss_clear_end:
	
;
; .sbssの初期化
;
	MOVW	HL , #LOWW( STARTOF( .sbss ) )
	MOV	ES , #HIGHW( STARTOF( .sbss ) )
	MOVW	AX , #LOWW( STARTOF( .sbss ) + SIZEOF( .sbss ) )
sbss_clear_loop:
	CMPW	AX , HL
	BZ		$sbss_clear_end
	MOV		ES:[HL] , #0
	INCW	HL
	BR 		$sbss_clear_loop
sbss_clear_end:
	
;
; .dataRの初期化
;
	MOV	ES , #HIGHW( STARTOF( .data ) )
	CLRW	BC
initialize_data_loop:
	MOVW	AX , #LOWW( SIZEOF( .data ) )
	CMPW	AX , BC
	BZ	$initialize_data_end
	MOV	A , ES:LOWW(STARTOF( .data ) )[BC]
	MOV	LOWW( STARTOF(.dataR) )[BC] , A
	INCW	BC
	BR		$initialize_data_loop
initialize_data_end:

;
; .sdataRの初期化
;
	MOV	ES , #HIGHW( STARTOF( .sdata ) )
	CLRW	BC
initialize_sdata_loop:
	MOVW	AX , #LOWW( SIZEOF( .sdata ) )
	CMPW	AX , BC
	BZ	$initialize_sdata_end
	MOV	A , ES:LOWW(STARTOF( .sdata ) )[BC]
	MOV	LOWW( STARTOF(.sdataR) )[BC] , A
	INCW	BC
	BR		$initialize_sdata_loop
initialize_sdata_end:


;
; ハードウェア固有の初期化処理
;
; weakシンボルは使用できないので判定無しで呼び出す
;

	CALL		!!_hardware_init_hook

;
; ソフトウェア固有の初期化処理
;
; weakシンボルは使用できないので判定無しで呼び出す
;

	CALL		!!_software_init_hook



; カーネル動作開始

	BR		!!_sta_ker
unexpected_return:
	BR		!!unexpected_return
