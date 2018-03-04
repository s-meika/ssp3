$ 
$ 		�ѥ�2�Υ������åȰ�¸�ƥ�ץ졼�ȡ�Mac OS X�ѡ�
$ 

$ 
$  ���ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$  ������ֹ�ȳ���ߥϥ�ɥ��ֹ�ϡ������ʥ��ֹ�˰��פ����롥1��31��
$  �����ʥ��ֹ���⡤SIGKILL�ʡ�9�ˡ�SIGSTOP�ʡ�17�ˡ�SIGUSR2�ʡ�31�˰�
$  �������ѤǤ��롥
$ 
$INTNO_VALID = { 1, 2,..., 8; 10, 11,..., 16; 18, 19,..., 30 }$
$INHNO_VALID = INTNO_VALID$
$EXCNO_VALID = INHNO_VALID$

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT��DEF_EXC�ǻ��ѤǤ������ߥϥ�ɥ��ֹ桿CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$  �����ͥ���٤ϡ�-1��-7�����ѤǤ��롥-7��NMI�Ȱ�����
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -1, -2,..., -7 }$

$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (Mac OS X)$NL$
$SPC$*/$NL$
$NL$

$ 
$  �ޥ����Ǥ��ʤ������ʥ�ȥ����ͥ뤬�Ȥ������ʥ�˴ؤ�������
$ 
$  SIGKILL�ʥޥ����Բġ�
$  SIGSTOP�ʥޥ����Բġ�
$  SIGUSR2�ʥ����ͥ뤬���ѡ�
$ 
$INT.INTPRI[SIGKILL] = -7$
$INT.INTPRI[SIGSTOP] = -7$
$INT.INTPRI[SIGUSR2] = -7$

$ 
$   CFG_INT�Υ������åȰ�¸�Υ��顼�����å� -> ����ե�����졼���Υƥ��ȤǤϻ��Ѥ��ʤ�
$ 
$ $FOREACH intno INT.ORDER_LIST$
$ 	$IF (INT.INTATR[intno] & TA_EDGE) == 0$
$ 		$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT("Level trigger is not supported for intno `%1%\' in CFG_INT", INT.INTNO[intno])$$END$
$	$END$
$ $END$

$ 
$  CPU�㳰�ϥ�ɥ�˴ؤ������
$ 
$FOREACH excno EXC.ORDER_LIST$
$	// ����ߥϥ�ɥ�Ȥν�ʣ�����å�
	$IF LENGTH(INH.INHNO[excno])$
		$ERROR EXC.TEXT_LINE[excno]$E_OBJ: $FORMAT(_("%1% `%2%\' in %3% is duplicated with %4% `%5%\'"), "excno", EXC.EXCNO[excno], "DEF_EXC", "inhno", INH.INHNO[excno])$$END$
	$END$

$	// CPU�㳰�ϥ�ɥ����Ͽ���������ʥ�˴ؤ�������
	$IF LENGTH(INTNO[excno])$
		$INT.INTPRI[INTNO[excno]] = -7$
	$END$
$END$

$ 
$  �ǥХå��Ѥ˥ޥ������ʤ������ʥ�˴ؤ�������
$ 
$  SIGINT�ʥǥХå��ѡ�
$  SIGBUS�ʥǥХå��ѡ�
$  SIGSEGV�ʥǥХå��ѡ�
$ 
$IF !LENGTH(INT.INTPRI[SIGINT])$
	$INT.INTPRI[SIGINT] = -7$
$END$
$IF !LENGTH(INT.INTPRI[SIGBUS])$
	$INT.INTPRI[SIGBUS] = -7$
$END$
$IF !LENGTH(INT.INTPRI[SIGSEGV])$
	$INT.INTPRI[SIGSEGV] = -7$
$END$

$ 
$  ����ߥϥ�ɥ�ν������ɬ�פʾ���
$ 

$ ����ߥϥ�ɥ��
$ #define TNUM_INHNO	$LENGTH(INH.ORDER_LIST)$$NL$
$ const uint_t _kernel_tnum_inhno = TNUM_INHNO;$NL$
$ $NL$
$ $FOREACH inhno INH.ORDER_LIST$
$ 	$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
$		INTHDR_ENTRY($INH.INHNO[inhno]$, $INH.INTHDR[inhno]$, $INT.INTPRI[INTNO[inhno]]$)$NL$
$	$END$
$ $END$
$ $NL$

$ ����ߥϥ�ɥ������ơ��֥�
$IF LENGTH(INH.ORDER_LIST)$
	const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {$NL$
	$JOINEACH inhno INH.ORDER_LIST ",\n"$
		$IF (INH.INHATR[inhno] & TA_NONKERNEL) == 0$
			$TAB${ ($INH.INHNO[inhno]$), ($INH.INHATR[inhno]$), (FP)(INT_ENTRY($INH.INHNO[inhno]$, $INH.INTHDR[inhno]$)), ($INT.INTPRI[INTNO[INH.INHNO[inhno]]]$) }
		$ELSE$
			$TAB${ ($INH.INHNO[inhno]$), ($INH.INHATR[inhno]$), (FP)($INH.INTHDR[inhno]$), ($INT.INTPRI[INTNO[INH.INHNO[inhno]]]$) }
		$END$
	$END$$NL$
	};$NL$
$ELSE$
	TOPPERS_EMPTY_LABEL(const INHINIB, _kernel_inhinib_table);$NL$
$END$
$NL$

$ 
$  �����ͥ������Τ���ʲ��γ�����׵��ޥ������뤿��ξ���Υơ��֥�
$ 
const sigset_t _kernel_sigmask_table[8] = {$NL$
$FOREACH intpri { 0, -1,..., -6 }$
	$intmask = 0$
	$FOREACH intno { 1, 2, ..., 31 }$
		$IF ALT(INT.INTPRI[intno], 0) >= intpri$
			$intmask = intmask | (1 << (intno - 1))$
		$END$
	$END$
	$TAB$UINT32_C($FORMAT("0x%08x", intmask)$),$NL$
$END$
$TAB$UINT32_C($FORMAT("0x%08x", intmask)$)$NL$
};$NL$

$ 
$  ������׵�ػߥե饰�¸��Τ�����ѿ��ν����
$ 
$sigmask_disint_init = 0$
$FOREACH intno INT.ORDER_LIST$
	$IF (INT.INTATR[intno] & TA_ENAINT) == 0$
		$sigmask_disint_init = sigmask_disint_init | (1 << (INT.INTNO[intno] - 1))$
	$END$
$END$
$NL$
const sigset_t	_kernel_sigmask_disint_init = 
		UINT32_C($FORMAT("0x%08x", sigmask_disint_init)$);$NL$
