$
$ 		パス2のターゲット依存テンプレート（RB-D62Q1577TB100用）
$

$
$  有効な割込み番号，割込みハンドラ番号
$
$INTNO_VALID = { 1,2,...,124 }$
$INHNO_VALID = INTNO_VALID$

$
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$
$INHNO_DEFINH_VALID = INHNO_VALID$

$
$  CFG_INTで使用できる割込み番号と割込み優先度
$
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$
$  標準テンプレートファイルのインクルード
$
$INCLUDE "kernel_u8dev/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (RB-D62Q1577TB100)$NL$
$SPC$*/$NL$
$NL$

$
$   CFG_INTのターゲット依存のエラーチェックと_kernel_bitpat_cfgintの生成
$
$bitpat_cfgint = 0$

$FOREACH inhno INTNO_VALID$
	$FORMAT("static void _kernel_int_handler_%d(void);", +inhno)$$NL$
$END$
$NL$
$FOREACH inhno INTNO_VALID$
	$IF inhno < 3$
		#pragma INTERRUPT$TAB$$FORMAT("_kernel_int_handler_%d", +inhno)$$TAB$$FORMAT("0x%04X", +((inhno * 2) + 6))$$TAB$2$NL$
	$ELIF inhno > 60$
		#pragma SWI$TAB$$FORMAT("_kernel_int_handler_%d", +inhno)$$TAB$$FORMAT("0x%04X", +((inhno * 2) + 6))$$TAB$1$NL$
	$ELSE$
		#pragma INTERRUPT$TAB$$FORMAT("_kernel_int_handler_%d", +inhno)$$TAB$$FORMAT("0x%04X", +((inhno * 2) + 6))$$TAB$1$NL$
	$END$
$END$
$NL$
#pragma ASM$NL$
$TAB$extrn$TAB$code: __kernel_inthdr_entry$NL$
#pragma ENDASM$NL$
$NL$
$FOREACH inhno INTNO_VALID$
	$FORMAT("static void _kernel_int_handler_%d(void)", +inhno)$$NL$
	{$NL$
	#pragma ASM$NL$
	$IF LENGTH(INH.INHNO[inhno]) && ((INH.INHATR[inhno] & TA_NONKERNEL) != 0)$
		$TAB$push	ea, lr, epsw, elr$NL$
		$TAB$ei$NL$
		$TAB$bl		_$INH.INTHDR[inhno]$$NL$
		$TAB$pop		pc, psw, lr, ea$NL$
	$ELSE$
		$TAB$push	ea, lr, epsw, elr$NL$
		$TAB$push	xr0$NL$
		$TAB$$FORMAT("mov		r0,	#%d", +inhno)$$NL$
		$TAB$b		__kernel_inthdr_entry$NL$
	$END$
	#pragma ENDASM$NL$
	}$NL$
$NL$
$END$
const FP _kernel_exc_tbl[] = $NL$
{$NL$
$TAB$(FP)0,$NL$
$FOREACH inhno INTNO_VALID$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_int_handler),
	$END$
	$SPC$$FORMAT("/* %d */", +inhno)$$NL$
$END$
};$NL$
