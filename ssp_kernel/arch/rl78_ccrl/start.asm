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
;  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
;  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
;  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
;  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
;      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
;      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
;  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
;      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
;      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
;      �̖��ۏ؋K����f�ڂ��邱�ƁD
;  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
;      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
;      �ƁD
;    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
;        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
;    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
;        �񍐂��邱�ƁD
;  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
;      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
;      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
;      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
;      �Ɛӂ��邱�ƁD
; 
;  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
;  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
;  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
;  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
;  �̐ӔC�𕉂�Ȃ��D
; 
; 


	.public _start
	.extern _sta_ker
	.extern _hardware_init_hook
	.extern _software_init_hook

.SECTION .start , TEXTF
_start:

; �����݋֎~
	DI

; �X�^�b�N�|�C���^�̏�����
	MOVW	DE , #__kernel_istkpt
	MOVW	AX , [DE]
	MOVW	SP , AX

;
; .bss�̏�����
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
; .sbss�̏�����
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
; .dataR�̏�����
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
; .sdataR�̏�����
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
; �n�[�h�E�F�A�ŗL�̏���������
;
; weak�V���{���͎g�p�ł��Ȃ��̂Ŕ��薳���ŌĂяo��
;

	CALL		!!_hardware_init_hook

;
; �\�t�g�E�F�A�ŗL�̏���������
;
; weak�V���{���͎g�p�ł��Ȃ��̂Ŕ��薳���ŌĂяo��
;

	CALL		!!_software_init_hook



; �J�[�l������J�n

	BR		!!_sta_ker
unexpected_return:
	BR		!!unexpected_return
