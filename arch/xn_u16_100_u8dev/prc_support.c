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
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 *
 *	2023/01/23 Ryutaro Morita
 */

/*
 *		�v���Z�b�T�ˑ����W���[�� �A�Z���u�����ꕔ�iuX-U16/100�p�j
 */

/*
 *  ���̃t�@�C����C����\�[�X�Ƃ����ꍇ�uTYPE�v�^�����߂������I�ɑ}������
 *  �@��ˑ����Ȃ��Ȃ邽�߁C�v���Z�b�T�ˑ��f�B���N�g���ɔz�u����ۂɓs�����ǂ��D
 *  �A���C���̃t�@�C����C����\�[�X�Ƃ����C�����C���A�Z���u���̏ꍇ��
 *  �f�o�b�K�ł̃��C���g���[�X������ł��邽��
 *  �f�o�b�O���ɂ̓A�Z���u���\�[�X�Ƃ��ăR���p�C�����������ǂ��D
 *  �\�[�X�`���̐؂�ւ��́C�t�@�C���g���q�̕ύX�C�����
 *  ���̃\�[�X�ƁuMakefile.prc�v�̎኱�̏C���ōs���D
 */

//	type (ML621577)		; C����\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g(//)
//	model large, near	; C����\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g(//)

#pragma ASM	// �A�Z���u���\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g(;)

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

	; /* �I�t�Z�b�g�i�uoffset.h�v�͎g�p�����ɌŒ�Ƃ���j */
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
	; *  ���̃��[�`���́C�^�X�N�R���e�L�X�g�ECPU���b�N��ԁE�f�B�X�p�b�`
	; *  ����ԁE�i���f����́j�����ݗD��x�}�X�N�S������ԂŌĂяo��
	; *  ���D
	; */
	push	lr
	push	xr4									; /* ���W�X�^��ۑ� */
	push	xr8
	push	xr12

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_sp						; /* �^�X�N�X�^�b�N��ۑ� */
	mov		er2, sp
	st		er2, [er0]
	l		er0, __kernel_p_runtsk
	add		er0, #TCB_pc						; /* ���s�ĊJ�Ԓn��ۑ� */
	mov		r2,	#BYTE1 OFFSET dispatch_r		; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r3,	#BYTE2 OFFSET dispatch_r
	st		er2, [er0]
	b		dispatcher

dispatch_r:
	pop		xr12								; /* ���W�X�^�𕜋A */
	pop		xr8
	pop		xr4
	pop		lr

;	l		er0, __kernel_p_runtsk
	add		er0, #TCB_enatex
	l		r2, [er0]
	and		r2, #TCB_enatex_mask
	bz		dispatch_r_1						; /* enatex��false�Ȃ烊�^�[�� */

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_texptn
	l		er0, [er0]
	bz		dispatch_r_1						; /* texptn��0�Ȃ烊�^�[�� */

	l		er0, __kernel_ipmflg
	bz		dispatch_r_1						; /* ipmflg��true�ł����            */

	b		__kernel_call_texrtn				; /*  �^�X�N��O�������[�`���̌ďo�� */

dispatch_r_1:
	rt

	rseg $$_kernel_start_dispatch
__kernel_start_dispatch:
	;/*
	; *  ���̃��[�`���́C�J�[�l���N�����ɁC���ׂĂ̊����݂��֎~�������
	; * �i�����݃��b�N��ԂƓ����j�ŌĂяo�����D�܂��C�����݃��[�h�i��
	; *  �^�X�N�R���e�L�X�g�Ɠ����j�ŌĂяo����邱�Ƃ�z�肵�Ă���D
	; *
	; *  prc_initialize�ŁClock_flag��true�ɁCsaved_iipm��IIPM_ENAALL��
	; *  ���������Ă��邽�߁C�J�[�l���Ǘ��O�̊����݂������邱�ƂŁC
	; *  CPU���b�N��ԁE�i���f����́j�����ݗD��x�}�X�N�S������ԂɂȂ�D
	; *  �܂��Cinitialize_task��disdsp��false�ɏ��������Ă��邽�߁C�f�B
	; *  �X�p�b�`����ԂɂȂ��Ă���D
	; */
	push	lr
	mov		er2, #0								; /* �}�X�^���[�h�� */
	st		er2, __kernel_int_cnt
	b		dispatcher_0

;/*
; *  ���݂̃R���e�L�X�g���̂Ăăf�B�X�p�b�`
; */
	rseg $$_kernel_exit_and_dispatch
__kernel_exit_and_dispatch:

;/*
; *  �f�B�X�p�b�`���{��
; */
dispatcher:
	;/*
	; *  ���̃��[�`���́C�^�X�N�R���e�L�X�g�ECPU���b�N��ԁE�f�B�X�p�b�`
	; *  ����ԁE�i���f����́j�����ݗD��x�}�X�N�S������ԂŌĂяo��
	; *  ���D
	; *
	; *  ���Ȃ킿�C�}�X�^���[�h�Elock_flag��true�Edisdsp��false�Edspflg
	; *  ��true�Esaved_iipm��IIPM_ENAALL�ƂȂ��Ă���D���s�ĊJ�Ԓn�ւ���
	; *  �̏�Ԃ̂܂ܕ��򂷂�D
	; */

dispatcher_0:
	l		er0, __kernel_p_schedtsk			; /* p_schedtsk��p_runtsk�� */
	st		er0, __kernel_p_runtsk
	mov		er2, #0
	cmp		er0, er2
	beq		dispatcher_1						; /* p_runtsk��NULL�Ȃ�dispatcher_1�� */

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
	;  *  CPU���b�N��Ԃ��������鏀��������D
	;  */
	mov		er0, #1								; /* �����݃��[�h�� */
	st		er0, __kernel_int_cnt
	mov		r0,	#BYTE1 OFFSET _$$SP				; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r1,	#BYTE2 OFFSET _$$SP				; /* �����ݗp�̃X�^�b�N�֐ؑւ� */
	mov		sp, er0
	mov		r0, psw								; /* psw��r0�ɕۑ� */
	mov		er2, #0								; /* CPU���b�N������Ԃ� */
	st		er2, __kernel_lock_flag

dispatcher_2:
	;/*
	; *  �����݂������C�����݃��[�h�ɐ؂芷���āC�����݂�҂D
	; *
	; *  �����Ŋ����݃��[�h�ɐ؂芷����̂́C�����Ŕ������銄���ݏ�����
	; *  �ǂ̃X�^�b�N���g�����Ƃ������̉����ƁC�����݃n���h�����ł̃^
	; *  �X�N�f�B�X�p�b�`�̖h�~�Ƃ���2�̈Ӗ�������D
	; *
	; *  �v���Z�b�T�������ݑ҂��Ɉڍs�����鏈���ƁC�����݋��Ƃ́C�s��
	; *  ���ɍs�Ȃ��K�v������iM68040�ł�stop���߂ŗ����s�Ȃ��̂Ŗ���
	; *  ���j�D�����s���ɍs�Ȃ�Ȃ��ꍇ�C�����݂�����������Ɋ���
	; *  �݂�����C���̒��Ń^�X�N�����s�\��ԂɂȂ�ƁC���s���ׂ��^�X
	; *  �N������ɂ�������炸�v���Z�b�T�������ݑ҂��ɂȂ��Ă��܂��D
	; *
	; *  �����ݑ҂��̊Ԃ́Cp_runtsk��NULL�i��0�j�ɐݒ肵�Ȃ���΂Ȃ��
	; *  ���D���̂悤�ɐݒ肵�Ȃ��ƁC�����݃n���h������iget_tid���Ăяo
	; *  �����ۂ̓��삪�d�l�ɍ��v���Ȃ��Ȃ�D
	; */
	ei											; /* �����ݑ҂� */
	nop
	nop											; /* ���荞�݂𔭐������邽�߂ɂ�ei�̂���2�T�C�N���K�v */
	di
	mov		psw, r0								; /* ���̏�Ԃɖ߂� */
	l		er2, __kernel_reqflg				; /* reqflg��false�Ȃ�dispatcher_2�� */
	bz		dispatcher_2

	mov		er2, #0								; /* reqflg��false�� */
	st		er2, __kernel_reqflg

	;/*
	; *  CPU���b�N��Ԃɖ߂��D�����ݑ҂��̊ԂɎ��s���������݃n���h���ɂ�
	; *  ��Csaved_iipm��������������\�������邽�߁C���̒l�ɖ߂��K
	; *  �v������Ddispatcher�����s����鎞�́Csaved_iipm��IIPM_ENAALL
	; *  �ƂȂ��Ă��邽�߁C�����ł�saved_iipm��IIPM_ENAALL�i��0�j�ɖ߂�
	; *  �΂悢�D
	; */
	st		er2, __kernel_int_cnt				; /* �}�X�^���[�h�� */
	st		er2, __kernel_saved_iipm			; /* saved_iipm��0�ɂ��� */
	mov		er2, #1								; /* CPU���b�N��Ԃ� */
	st		er2, __kernel_lock_flag
	b		dispatcher_0

;/*
; *  �J�[�l���̏I�������̌ďo��
; */
	rseg $$_kernel_call_exit_kernel
__kernel_call_exit_kernel:
	l		er0, __kernel_int_cnt				; /* �����݃��[�h�� */
	add		er0, #1
	st		er0, __kernel_int_cnt
	mov		r0,	#BYTE1 OFFSET _$$SP				; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r1,	#BYTE2 OFFSET _$$SP				; /* �����ݗp�̃X�^�b�N�֐ؑւ� */
	mov		sp, er0
	b		__kernel_exit_kernel				; /* �J�[�l���̏I���������Ă� */

;/*
; *
; *  �^�X�N�J�n������
; *
; *  dispatcher����Ăяo����邽�߁CTCB�̃A�h���X��er0�ɓ����Ă���
; *
; */
	rseg $$_kernel_start_r
__kernel_start_r:
	mov		er2, #0								; /* CPU���b�N������Ԃ� */
	st		er2, __kernel_lock_flag
	ei
	mov		er2, er0							; /* p_runtsk->p_tinib��er2�� */
	add		er2, #TCB_p_tinib
	l		er2, [er2]
	push	er2									; /* er2�ip_runtsk->p_tinib�j��ޔ� */
	add		er2, #TINIB_exinf					; /* exinf���p�����[�^�ɐς� */
	l		er0, [er2]
	; /*
	;  *  �ulr�v���W�X�^�̕��A�̓��[�W���f����4�o�C�g�ł��邱�Ƃɒ��Ӂi��ɏ�ʂ�pop�j
	;  */
	mov		r2, ecsr
	push	r2
	mov		r2,	#BYTE1 OFFSET _ext_tsk			; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r3,	#BYTE2 OFFSET _ext_tsk
	; /*
	;  *  �ulr�v���W�X�^�̕��A�̓��[�W���f����4�o�C�g�ł��邱�Ƃɒ��Ӂi���ɉ��ʂ�pop�j
	;  */
	push	er2
	pop		lr									; /* �ulr�v���W�X�^�̕��A */
	pop		er2									; /* er2�ip_runtsk->p_tinib�j�𕜋A */
	add		er2, #TINIB_task					; /* �^�X�N�̋N���Ԓn��er2�� */
	l		er2, [er2]
	b		er2

	rseg $$_kernel_inthdr_entry
__kernel_inthdr_entry:
; //	push	ea, lr, epsw, elr				; /* �X�N���b�`���W�X�^��ۑ� */
; //	push	xr0
	; /* ��L�̏����́ukernel_cfg.c�v�́u_kernel_int_handler_XX()�v�֐��̖`���Ŋ��ɍs���Ă��� */
	l		er2, __kernel_int_cnt				; /* �����݃��[�h�� */
	add		er2, #1
	st		er2, __kernel_int_cnt
	push	er0
	mov		er0, #1
	cmp		er2, er0
	pop		er0
	bne		inthdr_entry_0_d					; /* ���Z�O��0�łȂ���Α��d������ */

	mov		er2, sp								; /* �^�X�N�X�^�b�N��ۑ� */
	st		er2, __kernel_int_sp
	mov		r2,	#BYTE1 OFFSET _$$SP				; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r3,	#BYTE2 OFFSET _$$SP				; /* �����ݗp�̃X�^�b�N�֐ؑւ� */
	mov		sp, er2
	b		inthdr_entry_0

inthdr_entry_0_d:
	nop

inthdr_entry_0:
	ei											; /* ���d�����݋��� */
	mov		er2, #4
	mul		er2, r0
;	push	er0
	mov		r0,	#BYTE1 OFFSET __kernel_exc_tbl	; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r1,	#BYTE2 OFFSET __kernel_exc_tbl
	add		er2, er0
	l		er0, [er2]
;	push	r0									; /* for Debug */
	bl		er0									; /* C���[�`���Ăяo�� */

;/*
; *  �����݃n���h���o������
; *
; *  ret_int�́C�����݃n���h������߂�������Ɏ��s���郋�[�`���ŁC
; *  INTHDR_ENTRY�}�N���œW�J���銄���݃n���h���̓��������ŁC�����݃n��
; *  �h������̖߂�Ԓn�ɐݒ肳���D
; */
ret_int:
	di											; /* ���d���荞�݋֎~ */
	mov		r0, #00h							; /* CIL = 0 */
	st		r0, 0f032h
	l		er0, __kernel_int_cnt				; /* �����݃��[�h�� */
	add		er0, #-1
	st		er0, __kernel_int_cnt				; /* �߂�悪�����݃��[�h�Ȃ� */
	bnz		ret_int_1_d							; /*           �����Ƀ��^�[�� */

	l		er0, __kernel_reqflg				; /* reqflg��true�ł����ret_int_2�� */
	bnz		ret_int_2

	l		er0, __kernel_int_sp				; /* �}�X�^���[�h�Ɂi�X�^�b�N�؊����j */
	mov		sp, er0

ret_int_1:
	;/*
	; *  �����ݏ�������̃��^�[���ɂ��CCPU���b�N������ԂɈڍs����悤
	; *  ��������D�����ݗD��x�}�X�N�́CRTE���߂ɂ�茳�̒l�ɖ߂邽�߁C
	; *  lock_flag��false�ɂ��Ă����΂悢�ilock_flag��false�ɂ���̂́C
	; *  CPU���b�N��Ԃ̂܂܊����݃n���h������߂������̑΍�j�D
	; */
	mov		er0, #0								; /* CPU���b�N�����̏��� */
	st		er0, __kernel_lock_flag

	pop		xr0									; /* �X�N���b�`���W�X�^�𕜋A */
	; /*
	;  * ���荞�݃n���h���̖߂�A�h���X�́uelr�v���W�X�^�Ɋi�[�����D
	;  * ����͖`���Łupush�v����Ă���̂Łupc�v���W�X�^�Ɂupop�v���邱�Ƃ�
	;  * �߂�A�h���X�ɃW�����v������D
	;  */
	pop		pc, psw, lr, ea

; //	rti

ret_int_1_d:
	b		ret_int_1

ret_int_2:
	l		er0, __kernel_int_sp				; /* �}�X�^���[�h�Ɂi�X�^�b�N�؊����j */
	mov		sp, er0

ret_int_3:
	;/*
	; *  �����ւ́CCPU��O�n���h���̏o��������������򂵂Ă���D
	; *
	; *  �����ł́C�߂�悪�^�X�N�ł���C�X�^�b�N�́C��O�X�^�b�N�t���[
	; *  ���̏�ɃX�N���b�`���W�X�^�݂̂��ۑ����ꂽ��ԂɂȂ��Ă���D��
	; *  ���C�v���Z�b�T�́C�}�X�^���[�h�E�J�[�l���Ǘ��̊����݂��֎~����
	; *  ��ԂƂȂ��Ă���D
	; */
	mov		er0, #0								; /* reqflg��false�� */
	st		er0, __kernel_reqflg

	;/*
	; *  CPU���b�N��ԂɈڍs���C�����ݗD��x�}�X�N�������ݏ����O�̒l�ɐ�
	; *	  �肷��D�J�[�l���Ǘ��̊����݂͂��łɋ֎~���Ă���̂ŁClock_flag
	; *  ��saved_iipm���X�V����Dsaved_iipm�́C�߂��̊����ݗD��x�}�X
	; *  �N�i�̓����\���j�ɐݒ肷��D
	; *
	; *  ���̎��_��CPU���b�N��ԂƂ���̂́Cdispatcher�֕��򂷂鎞�ƁC
	; *  call_texrtn���Ăяo�����ɁCCPU���b�N��ԂɂȂ��Ă���K�v������
	; *  ���߂ł���D
	; */
	mov		er0, #1								; /* lock_flag��true�� */
	st		er0, __kernel_lock_flag

	;/*
	; *  dspflg��false�ł���ꍇ�ƁCp_runtsk��p_schedtsk�������ꍇ�ɂ́C
	; *  �f�B�X�p�b�`���s��Ȃ��D���̃`�F�b�N���K�v�Ȃ̂́C�^�X�N��O��
	; *  �����[�`���̌ďo�����K�v�ȏꍇ�ɁC�f�B�X�p�b�`���K�v�Ȃ��Ă��C
	; *  reqflg��true�ɂ��邽�߂ł���D
	; */
	l		er0, __kernel_p_runtsk				; /* p_runtsk��er0�� */
	l		er2, __kernel_dspflg				; /* dspflg��false�Ȃ�ret_int_4�� */
	bz		ret_int_4

	l		er2, __kernel_p_schedtsk			; /* p_runtsk��p_schedtsk�������Ȃ� */
	cmp		er0, er2
	beq		ret_int_4							; /*                    ret_int_4�� */

	push	xr4									; /* �c��̃��W�X�^��ۑ�*/
	push	xr8
	push	xr12

	add		er0, #TCB_sp						; /* �^�X�N�X�^�b�N��ۑ� */
	mov		er2, sp
	st		er2, [er0]
	l		er0, __kernel_p_runtsk
	add		er0, #TCB_pc						; /* ���s�ĊJ�Ԓn��ۑ� */
	mov		r2,	#BYTE1 OFFSET ret_int_r			; /* OFFSET���Z�q�ŃA�h���X���𐔒l���֕ϊ� */
	mov		r3,	#BYTE2 OFFSET ret_int_r
	st		er2, [er0]
	b		dispatcher

ret_int_r:
	pop		xr12								; /* ���W�X�^�𕜋A */
	pop		xr8
	pop		xr4

ret_int_4:
	;/*
	; *  enatex��true�ŁCtexptn��0�łȂ��Cipmflg��true�ł���΁C�^�X�N
	; *  ��O�������[�`�����Ăяo���D
	; *  ret_int_3��dispatcher����Ăяo����邽�߁CTCB�̃A�h���X��er0�ɓ����Ă���
	; */
;	l		er0, __kernel_p_runtsk
	add		er0, #TCB_enatex
	l		r2, [er0]
	and		r2, #TCB_enatex_mask
	bz		ret_int_5							; /* enatex��false�Ȃ�ret_int_5�� */

	l		er0, __kernel_p_runtsk
	add		er0, #TCB_texptn
	l		er0, [er0]
	bz		ret_int_5							; /* texptn��0�Ȃ�ret_int_5�� */

	l		er0, __kernel_ipmflg
	bz		ret_int_5							; /* texptn��0�Ȃ�ret_int_5�� */

	b		__kernel_call_texrtn				; /*  �^�X�N��O�������[�`���̌ďo�� */

ret_int_5:
	;/*
	; *  �����ݏ�������̃��^�[���ɂ��CCPU���b�N������ԂɈڍs�����
	; *  ����������D�����ݗD��x�}�X�N�́CRTE���߂ɂ�茳�̒l�ɖ߂邽
	; *  �߁Clock_flag��false�ɂ��Ă����΂悢�D
	; */
	mov		er0, #0								; /* CPU���b�N�����̏��� */
	st		er0, __kernel_lock_flag

	pop		xr0									; /* �X�N���b�`���W�X�^�𕜋A */
	; /*
	;  * ���荞�݃n���h���̖߂�A�h���X�́uelr�v���W�X�^�Ɋi�[�����D
	;  * ����͖`���Łupush�v����Ă���̂Łupc�v���W�X�^�Ɂupop�v���邱�Ƃ�
	;  * �߂�A�h���X�ɃW�����v������D
	;  */
	pop		pc, psw, lr, ea

; //	rti

#pragma ENDASM	// �A�Z���u���\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g(;)
