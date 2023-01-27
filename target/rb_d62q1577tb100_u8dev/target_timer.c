/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
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
 *		�^�C�}�h���C�o�iRB-D62Q1577TB100�p�j
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_syssvc.h"
#include "target_timer.h"
#include "drivers.h"

/*
 *  �^�C�}�̋N������
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK	cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	initTm_t st_initTimer;

	/*
	 *  �^�C�}������ݒ肵�C�^�C�}�̓�����J�n����D
	 */
	assert(cyc <= MAX_CLOCK);

	/* Init timer */
	st_initTimer.outPole       = TM_NEG_POS;
	st_initTimer.mode          = TM_OST_CONTINUOUS;
	st_initTimer.timerMode     = TM_BM_16BIT;
	st_initTimer.divisionRatio = TM_DIV16;
	st_initTimer.extCntTrigger = TM_EXS_P02;
	st_initTimer.cntClock      = TM_EX_INTERNAL;
	st_initTimer.timerClock    = TM_CS_HSCLK;
	timer0_init(&st_initTimer);

	/* Clear and set timer count */
	timer0_clrCnt16();
	timer0_setCnt16((uint16_t)cyc);

	/* Set clock source */
//	timer0_setTimerClock(TM_CS_LSCLK);	// �����Œᑬ(LSCLK)�ɖ߂��Ă���I

	/* Enable interrupt */
	irq_tm0_clearIRQ();

	/* Start timer*/
	timer0_start();
}

/*
 *  �^�C�}�̒�~����
 */
void
target_timer_terminate(intptr_t exinf)
{
	/*
	 *  �^�C�}�̓�����~����D
	 */
	ftimer0_stop();
}

/*
 *  �^�C�}�����݃n���h��
 */
void
target_timer_handler(void)
{
	signal_time();					/* �^�C���e�B�b�N�̋��� */
}
