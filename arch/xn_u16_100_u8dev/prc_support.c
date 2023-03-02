/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *	2023/01/23 Ryutaro Morita
 */

/*
 *		プロセッサ依存モジュール アセンブリ言語部（uX-U16/100用）
 */

/*
 *  このファイルをC言語ソースとした場合「TYPE」疑似命令が自動的に挿入され
 *  機種依存しなくなるため，プロセッサ依存ディレクトリに配置する際に都合が良い．
 *  但し，このファイルをC言語ソースとしたインラインアセンブラの場合は
 *  デバッガでのライントレースが困難であるため
 *  デバッグ時にはアセンブラソースとしてコンパイルした方が良い．
 *  ソース形式の切り替えは，ファイル拡張子の変更，および
 *  このソースと「Makefile.prc」の若干の修正で行う．
 */

//	type (ML621577)		; C言語ソースとする場合にコメントアウト(//)
//	model large, near	; C言語ソースとする場合にコメントアウト(//)

#pragma ASM	// アセンブラソースとする場合にコメントアウト(;)

	extrn   code: _ext_tsk
	extrn   code: __kernel_call_texrtn
	extrn   code: __kernel_exit_kernel
	extrn   table near: __kernel_exc_tbl
	extrn   data near: __kernel_dspflg
	extrn   data near: _$$SP
	extrn   data near: __kernel_int_cnt
	extrn   data near: __kernel_int_sp
	extrn   data near: __kernel_ipmflg
	extrn   data near: __kernel_lock_flag
	extrn   data near: __kernel_p_runtsk
	extrn   data near: __kernel_p_schedtsk
	extrn   data near: __kernel_reqflg
	extrn   data near: __kernel_saved_iipm
	public __kernel_dispatch
	public __kernel_start_dispatch
	public __kernel_exit_and_dispatch
	public __kernel_call_exit_kernel
	public __kernel_start_r
	public __kernel_inthdr_entry
	$$_kernel_dispatch segment code 2h #0h
	$$_kernel_start_dispatch segment code 2h #0h
	$$_kernel_exit_and_dispatch segment code 2h #0h
	$$_kernel_call_exit_kernel segment code 2h #0h
	$$_kernel_start_r segment code 2h #0h
	$$_kernel_inthdr_entry segment code 2h #0h

	; /* オフセット（「offset.h」は使用せずに固定とする） */
	DEFINE TCB_p_tinib		"4"
	DEFINE TCB_texptn		"10"
	DEFINE TCB_sp			"14"
	DEFINE TCB_pc			"16"
	DEFINE TINIB_exinf		"2"
	DEFINE TINIB_task		"4"
	DEFINE TCB_enatex		"8"
	DEFINE TCB_enatex_bit	"2"
	DEFINE TCB_enatex_mask	"04h"

	rseg $$_kernel_dispatch
__kernel_dispatch:
	;/*
	; *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	; *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	; *  れる．
	; */
	push	lr
	push	xr4									; /* レジスタを保存 */
	push	xr8
	push	xr12

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_sp						; /* タスクスタックを保存 */
	mov		er2, sp
	st		er2, [er0]
	l		er0, __kernel_p_runtsk
	add		er0, #TCB_pc						; /* 実行再開番地を保存 */
	mov		r2,	#BYTE1 OFFSET dispatch_r		; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r3,	#BYTE2 OFFSET dispatch_r
	st		er2, [er0]
	b		dispatcher

dispatch_r:
	pop		xr12								; /* レジスタを復帰 */
	pop		xr8
	pop		xr4
	pop		lr

;	l		er0, __kernel_p_runtsk
	add		er0, #TCB_enatex
	l		r2, [er0]
	and		r2, #TCB_enatex_mask
	bz		dispatch_r_1						; /* enatexがfalseならリターン */

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_texptn
	l		er0, [er0]
	bz		dispatch_r_1						; /* texptnが0ならリターン */

	l		er0, __kernel_ipmflg
	bz		dispatch_r_1						; /* ipmflgがtrueであれば            */

	b		__kernel_call_texrtn				; /*  タスク例外処理ルーチンの呼出し */

dispatch_r_1:
	rt

	rseg $$_kernel_start_dispatch
__kernel_start_dispatch:
	;/*
	; *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
	; * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
	; *  タスクコンテキストと同等）で呼び出されることを想定している．
	; *
	; *  prc_initializeで，lock_flagをtrueに，saved_iipmをIIPM_ENAALLに
	; *  初期化しているため，カーネル管理外の割込みを許可することで，
	; *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
	; *  また，initialize_taskでdisdspをfalseに初期化しているため，ディ
	; *  スパッチ許可状態になっている．
	; */
	push	lr
	mov		er2, #0								; /* マスタモードに */
	st		er2, __kernel_int_cnt
	b		dispatcher_0

;/*
; *  現在のコンテキストを捨ててディスパッチ
; */
	rseg $$_kernel_exit_and_dispatch
__kernel_exit_and_dispatch:

;/*
; *  ディスパッチャ本体
; */
dispatcher:
	;/*
	; *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	; *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	; *  れる．
	; *
	; *  すなわち，マスタモード・lock_flagがtrue・disdspがfalse・dspflg
	; *  がtrue・saved_iipmがIIPM_ENAALLとなっている．実行再開番地へもこ
	; *  の状態のまま分岐する．
	; */

dispatcher_0:
	l		er0, __kernel_p_schedtsk			; /* p_schedtskをp_runtskに */
	st		er0, __kernel_p_runtsk
	mov		er2, #0
	cmp		er0, er2
	beq		dispatcher_1						; /* p_runtskがNULLならdispatcher_1へ */

	mov		er2, er0
	add		er2, #TCB_sp
	l		er2, [er2]
	mov		sp, er2
	mov		er2, er0
	add		er2, #TCB_pc
	l		er2, [er2]
	b		er2

dispatcher_1:
	; /*
	;  *  CPUロック状態を解除する準備をする．
	;  */
	mov		er0, #1								; /* 割込みモードに */
	st		er0, __kernel_int_cnt
	mov		r0,	#BYTE1 OFFSET _$$SP				; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r1,	#BYTE2 OFFSET _$$SP				; /* 割込み用のスタックへ切替え */
	mov		sp, er0
	mov		r0, psw								; /* pswをr0に保存 */
	mov		er2, #0								; /* CPUロック解除状態に */
	st		er2, __kernel_lock_flag

dispatcher_2:
	;/*
	; *  割込みを許可し，割込みモードに切り換えて，割込みを待つ．
	; *
	; *  ここで割込みモードに切り換えるのは，ここで発生する割込み処理に
	; *  どのスタックを使うかという問題の解決と，割込みハンドラ内でのタ
	; *  スクディスパッチの防止という2つの意味がある．
	; *
	; *  プロセッサを割込み待ちに移行させる処理と，割込み許可とは，不可
	; *  分に行なう必要がある（M68040ではstop命令で両方行なうので問題な
	; *  い）．これを不可分に行なわない場合，割込みを許可した直後に割込
	; *  みが入り，その中でタスクが実行可能状態になると，実行すべきタス
	; *  クがあるにもかかわらずプロセッサが割込み待ちになってしまう．
	; *
	; *  割込み待ちの間は，p_runtskをNULL（＝0）に設定しなければならな
	; *  い．このように設定しないと，割込みハンドラからiget_tidを呼び出
	; *  した際の動作が仕様に合致しなくなる．
	; */
	ei											; /* 割込み待ち */
	nop
	nop											; /* 割り込みを発生させるためにはeiのあと2サイクル必要 */
	di
	mov		psw, r0								; /* 元の状態に戻す */
	l		er2, __kernel_reqflg				; /* reqflgがfalseならdispatcher_2へ */
	bz		dispatcher_2

	mov		er2, #0								; /* reqflgをfalseに */
	st		er2, __kernel_reqflg

	;/*
	; *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラによ
	; *  り，saved_iipmが書き換えられる可能性があるため，元の値に戻す必
	; *  要がある．dispatcherが実行される時は，saved_iipmがIIPM_ENAALL
	; *  となっているため，ここではsaved_iipmをIIPM_ENAALL（＝0）に戻せ
	; *  ばよい．
	; */
	st		er2, __kernel_int_cnt				; /* マスタモードに */
	st		er2, __kernel_saved_iipm			; /* saved_iipmを0にする */
	mov		er2, #1								; /* CPUロック状態に */
	st		er2, __kernel_lock_flag
	b		dispatcher_0

;/*
; *  カーネルの終了処理の呼出し
; */
	rseg $$_kernel_call_exit_kernel
__kernel_call_exit_kernel:
	l		er0, __kernel_int_cnt				; /* 割込みモードに */
	add		er0, #1
	st		er0, __kernel_int_cnt
	mov		r0,	#BYTE1 OFFSET _$$SP				; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r1,	#BYTE2 OFFSET _$$SP				; /* 割込み用のスタックへ切替え */
	mov		sp, er0
	b		__kernel_exit_kernel				; /* カーネルの終了処理を呼ぶ */

;/*
; *
; *  タスク開始時処理
; *
; *  dispatcherから呼び出されるため，TCBのアドレスはer0に入っている
; *
; */
	rseg $$_kernel_start_r
__kernel_start_r:
	mov		er2, #0								; /* CPUロック解除状態に */
	st		er2, __kernel_lock_flag
	ei
	mov		er2, er0							; /* p_runtsk->p_tinibをer2に */
	add		er2, #TCB_p_tinib
	l		er2, [er2]
	push	er2									; /* er2（p_runtsk->p_tinib）を退避 */
	add		er2, #TINIB_exinf					; /* exinfをパラメータに積む */
	l		er0, [er2]
	; /*
	;  *  「lr」レジスタの復帰はラージモデルで4バイトであることに注意（先に上位をpop）
	;  */
	mov		r2, ecsr
	push	r2
	mov		r2,	#BYTE1 OFFSET _ext_tsk			; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r3,	#BYTE2 OFFSET _ext_tsk
	; /*
	;  *  「lr」レジスタの復帰はラージモデルで4バイトであることに注意（次に下位をpop）
	;  */
	push	er2
	pop		lr									; /* 「lr」レジスタの復帰 */
	pop		er2									; /* er2（p_runtsk->p_tinib）を復帰 */
	add		er2, #TINIB_task					; /* タスクの起動番地をer2に */
	l		er2, [er2]
	b		er2

	rseg $$_kernel_inthdr_entry
__kernel_inthdr_entry:
; //	push	ea, lr, epsw, elr				; /* スクラッチレジスタを保存 */
; //	push	xr0
	; /* 上記の処理は「kernel_cfg.c」の「_kernel_int_handler_XX()」関数の冒頭で既に行っている */
	l		er2, __kernel_int_cnt				; /* 割込みモードに */
	add		er2, #1
	st		er2, __kernel_int_cnt
	push	er0
	mov		er0, #1
	cmp		er2, er0
	pop		er0
	bne		inthdr_entry_0_d					; /* 加算前が0でなければ多重割込み */

	mov		er2, sp								; /* タスクスタックを保存 */
	st		er2, __kernel_int_sp
	mov		r2,	#BYTE1 OFFSET _$$SP				; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r3,	#BYTE2 OFFSET _$$SP				; /* 割込み用のスタックへ切替え */
	mov		sp, er2
	b		inthdr_entry_0

inthdr_entry_0_d:
	nop

inthdr_entry_0:
	ei											; /* 多重割込み許可 */
	mov		er2, #4
	mul		er2, r0
;	push	er0
	mov		r0,	#BYTE1 OFFSET __kernel_exc_tbl	; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r1,	#BYTE2 OFFSET __kernel_exc_tbl
	add		er2, er0
	l		er0, [er2]
;	push	r0									; /* for Debug */
	bl		er0									; /* Cルーチン呼び出し */

;/*
; *  割込みハンドラ出口処理
; *
; *  ret_intは，割込みハンドラから戻った直後に実行するルーチンで，
; *  INTHDR_ENTRYマクロで展開する割込みハンドラの入口処理で，割込みハン
; *  ドラからの戻り番地に設定される．
; */
ret_int:
	di											; /* 多重割り込み禁止 */
	mov		r0, #00h							; /* CIL = 0 */
	st		r0, 0f032h
	l		er0, __kernel_int_cnt				; /* 割込みモードに */
	add		er0, #-1
	st		er0, __kernel_int_cnt				; /* 戻り先が割込みモードなら */
	bnz		ret_int_1_d							; /*           すぐにリターン */

	l		er0, __kernel_reqflg				; /* reqflgがtrueであればret_int_2へ */
	bnz		ret_int_2

	l		er0, __kernel_int_sp				; /* マスタモードに（スタック切換え） */
	mov		sp, er0

ret_int_1:
	;/*
	; *  割込み処理からのリターンにより，CPUロック解除状態に移行するよう
	; *  準備する．割込み優先度マスクは，RTE命令により元の値に戻るため，
	; *  lock_flagをfalseにしておけばよい（lock_flagをfalseにするのは，
	; *  CPUロック状態のまま割込みハンドラから戻った時の対策）．
	; */
	mov		er0, #0								; /* CPUロック解除の準備 */
	st		er0, __kernel_lock_flag

	pop		xr0									; /* スクラッチレジスタを復帰 */
	; /*
	;  * 割り込みハンドラの戻りアドレスは「elr」レジスタに格納される．
	;  * これは冒頭で「push」されているので「pc」レジスタに「pop」することで
	;  * 戻りアドレスにジャンプさせる．
	;  */
	pop		pc, psw, lr, ea

; //	rti

ret_int_1_d:
	b		ret_int_1

ret_int_2:
	l		er0, __kernel_int_sp				; /* マスタモードに（スタック切換え） */
	mov		sp, er0

ret_int_3:
	;/*
	; *  ここへは，CPU例外ハンドラの出口処理からも分岐してくる．
	; *
	; *  ここでは，戻り先がタスクであり，スタックは，例外スタックフレー
	; *  ムの上にスクラッチレジスタのみが保存された状態になっている．ま
	; *  た，プロセッサは，マスタモード・カーネル管理の割込みを禁止した
	; *  状態となっている．
	; */
	mov		er0, #0								; /* reqflgをfalseに */
	st		er0, __kernel_reqflg

	;/*
	; *  CPUロック状態に移行し，割込み優先度マスクを割込み処理前の値に設
	; *	  定する．カーネル管理の割込みはすでに禁止しているので，lock_flag
	; *  とsaved_iipmを更新する．saved_iipmは，戻り先の割込み優先度マス
	; *  ク（の内部表現）に設定する．
	; *
	; *  この時点でCPUロック状態とするのは，dispatcherへ分岐する時と，
	; *  call_texrtnを呼び出す時に，CPUロック状態になっている必要がある
	; *  ためである．
	; */
	mov		er0, #1								; /* lock_flagをtrueに */
	st		er0, __kernel_lock_flag

	;/*
	; *  dspflgがfalseである場合と，p_runtskとp_schedtskが同じ場合には，
	; *  ディスパッチを行わない．このチェックが必要なのは，タスク例外処
	; *  理ルーチンの呼出しが必要な場合に，ディスパッチが必要なくても，
	; *  reqflgをtrueにするためである．
	; */
	l		er0, __kernel_p_runtsk				; /* p_runtskをer0に */
	l		er2, __kernel_dspflg				; /* dspflgがfalseならret_int_4へ */
	bz		ret_int_4

	l		er2, __kernel_p_schedtsk			; /* p_runtskとp_schedtskが同じなら */
	cmp		er0, er2
	beq		ret_int_4							; /*                    ret_int_4へ */

	push	xr4									; /* 残りのレジスタを保存*/
	push	xr8
	push	xr12

	add		er0, #TCB_sp						; /* タスクスタックを保存 */
	mov		er2, sp
	st		er2, [er0]
	l		er0, __kernel_p_runtsk
	add		er0, #TCB_pc						; /* 実行再開番地を保存 */
	mov		r2,	#BYTE1 OFFSET ret_int_r			; /* OFFSET演算子でアドレス式を数値式へ変換 */
	mov		r3,	#BYTE2 OFFSET ret_int_r
	st		er2, [er0]
	b		dispatcher

ret_int_r:
	pop		xr12								; /* レジスタを復帰 */
	pop		xr8
	pop		xr4

ret_int_4:
	;/*
	; *  enatexがtrueで，texptnが0でなく，ipmflgがtrueであれば，タスク
	; *  例外処理ルーチンを呼び出す．
	; *  ret_int_3とdispatcherから呼び出されるため，TCBのアドレスはer0に入っている
	; */
;	l		er0, __kernel_p_runtsk
	add		er0, #TCB_enatex
	l		r2, [er0]
	and		r2, #TCB_enatex_mask
	bz		ret_int_5							; /* enatexがfalseならret_int_5へ */

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_texptn
	l		er0, [er0]
	bz		ret_int_5							; /* texptnが0ならret_int_5へ */

	l		er0, __kernel_ipmflg
	bz		ret_int_5							; /* texptnが0ならret_int_5へ */

	b		__kernel_call_texrtn				; /*  タスク例外処理ルーチンの呼出し */

ret_int_5:
	;/*
	; *  割込み処理からのリターンにより，CPUロック解除状態に移行するよ
	; *  う準備する．割込み優先度マスクは，RTE命令により元の値に戻るた
	; *  め，lock_flagをfalseにしておけばよい．
	; */
	mov		er0, #0								; /* CPUロック解除の準備 */
	st		er0, __kernel_lock_flag

	pop		xr0									; /* スクラッチレジスタを復帰 */
	; /*
	;  * 割り込みハンドラの戻りアドレスは「elr」レジスタに格納される．
	;  * これは冒頭で「push」されているので「pc」レジスタに「pop」することで
	;  * 戻りアドレスにジャンプさせる．
	;  */
	pop		pc, psw, lr, ea

; //	rti

#pragma ENDASM	// アセンブラソースとする場合にコメントアウト(;)
