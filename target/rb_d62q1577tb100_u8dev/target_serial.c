/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *		�V���A��I/O�f�o�C�X�iSIO�j�h���C�o�iRB-D62Q1577TB100�p�j
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "drivers.h"

#define UART_0F_PARAM_BR          (UART_GET_BAUDRATE_COUNT(SYS_CLOCK, BPS_SETTING))		/* The parameter of baud rate             */
#define UART_0F_PARAM_BR_ADJUST   (UART_GET_BAUDRATE_ADJUST(SYS_CLOCK, BPS_SETTING))	/* The parameter of baud rate adjustment  */

/*
 * ���W�X�^�ݒ�l
 */
#define PORT2SIOPID(x)	((x) + 1)
#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

/*
 * �V���A���ʐM���j�b�g�E���W�X�^��`
 */
#define SDnBUF(x)		*(volatile unsigned int __near *)(x)
#define SDnBUFL(x)		*(volatile unsigned char __near *)(x)
#define SDnBUFH(x)		*(volatile unsigned char __near *)(x + 0x01)
#define SUnMOD(x)		*(volatile unsigned char __near *)(x + 0x02)
#define SUnDLYL(x)		*(volatile unsigned char __near *)(x + 0x04)
#define SUnCON(x)		*(volatile unsigned int __near *)(x + 0x06)
#define SUnCONL(x)		*(volatile unsigned char __near *)(x + 0x06)
#define SUnCONH(x)		*(volatile unsigned char __near *)(x + 0x07)
#define SIOnMOD(x)		*(volatile unsigned int __near *)(x + 0x08)
#define SIOnMODL(x)		*(volatile unsigned char __near *)(x + 0x08)
#define SIOnMODH(x)		*(volatile unsigned char __near *)(x + 0x09)
#define SIOnSTAT(x)		*(volatile unsigned char __near *)(x + 0x0A)
#define UAn0MOD(x)		*(volatile unsigned int __near *)(x + 0x0C)
#define UAn0MODL(x)		*(volatile unsigned char __near *)(x + 0x0C)
#define UAn0MODH(x)		*(volatile unsigned char __near *)(x + 0x0D)
#define UAn0BRT(x)		*(volatile unsigned int __near *)(x + 0x0E)
#define UAn0BRTL(x)		*(volatile unsigned char __near *)(x + 0x0E)
#define UAn0BRTH(x)		*(volatile unsigned char __near *)(x + 0x0F)
#define UAn0BRC(x)		*(volatile unsigned char __near *)(x + 0x10)
#define UAn0STAT(x)		*(volatile unsigned char __near *)(x + 0x12)
#define UAn1MOD(x)		*(volatile unsigned int __near *)(x + 0x14)
#define UAn1MODL(x)		*(volatile unsigned char __near *)(x + 0x14)
#define UAn1MODH(x)		*(volatile unsigned char __near *)(x + 0x15)
#define UAn1BRT(x)		*(volatile unsigned int __near *)(x + 0x16)
#define UAn1BRTL(x)		*(volatile unsigned char __near *)(x + 0x16)
#define UAn1BRTH(x)		*(volatile unsigned char __near *)(x + 0x17)
#define UAn1BRC(x)		*(volatile unsigned char __near *)(x + 0x18)
#define UAn1STAT(x)		*(volatile unsigned char __near *)(x + 0x1A)

#define SUnMOD_SUnINTS	(1 <<  7)
#define SUnMOD_SUnTIMD	(1 <<  6)
#define SUnMOD_SUnRIMD	(1 <<  5)
#define SUnMOD_SUnMD1	(1 <<  1)
#define SUnMOD_SUnMD0	(1 <<  0)

#define SUnCONL_Un0EN	(1 <<  1)

#define UAn0MOD_Un0DIR	(1 << 15)
#define UAn0MOD_Un0NEG	(1 << 14)
#define UAn0MOD_Un0STP	(1 << 13)
#define UAn0MOD_Un0PT2	(1 << 12)
#define UAn0MOD_Un0PT1	(1 << 11)
#define UAn0MOD_Un0PT0	(1 << 10)
#define UAn0MOD_Un0LG1	(1 <<  9)
#define UAn0MOD_Un0LG0	(1 <<  8)
#define UAn0MOD_Un0RSS	(1 <<  7)
#define UAn0MOD_Un0CK1	(1 <<  2)
#define UAn0MOD_Un0CK0	(1 <<  1)
#define UAn0MOD_Un0IO	(1 <<  0)

#define UAn0STAT_Un0RXF	(1 <<  5)
#define UAn0STAT_Un0TXF	(1 <<  4)
#define UAn0STAT_Un0FUL	(1 <<  3)
#define UAn0STAT_Un0PER	(1 <<  2)
#define UAn0STAT_Un0OER	(1 <<  1)
#define UAn0STAT_Un0FER	(1 <<  0)

/*
 *  �V���A���|�[�g�̊Ǘ��u���b�N
 */
struct sio_port_control_block {
	ID port;
	uint16_t reg;
	intptr_t exinf;
};


/*
 * �V���A��I/O�|�[�g�Ǘ��u���b�N�G���A
 */
SIOPCB siopcb_table[TNUM_PORT];

static const uint16_t sioreg_table[TNUM_PORT] = {
	0xF600,	// Channel 0
#if (TNUM_PORT >= 2)
	0xF620,	// Channel 1
#endif
#if (TNUM_PORT >= 3)
	0xF640,	// Channel 2
#endif
#if (TNUM_PORT >= 4)
	0xF660,	// Channel 3
#endif
#if (TNUM_PORT >= 5)
	0xF680,	// Channel 4
#endif
#if (TNUM_PORT >= 8)
	0xF6A0,	// Channel 5
#endif
};

#if 0
static const uint16_t irqreg_table[TNUM_PORT] = {
	0xF02A,	// IRQ2
#if (TNUM_PORT >= 2)
	0xF02C, // IRQ4
#endif
#if (TNUM_PORT >= 3)
	0xF02D, // IRQ5
#endif
#if (TNUM_PORT >= 4)
	0xF02E, // IRQ6
#endif
#if (TNUM_PORT >= 5)
	0xF02E, // IRQ6
#endif
#if (TNUM_PORT >= 6)
	0xF02F, // IRQ7
#endif
};

static const uint8_t irqbit0_table[TNUM_PORT] = {
	3,
#if (TNUM_PORT >= 2)
	1,
#endif
#if (TNUM_PORT >= 3)
	0,
#endif
#if (TNUM_PORT >= 4)
	0,
#endif
#if (TNUM_PORT >= 5)
	2,
#endif
#if (TNUM_PORT >= 6)
	0,
#endif
};

static const uint8_t irqbit1_table[TNUM_PORT] = {
	4,
#if (TNUM_PORT >= 2)
	2,
#endif
#if (TNUM_PORT >= 3)
	1,
#endif
#if (TNUM_PORT >= 4)
	1,
#endif
#if (TNUM_PORT >= 5)
	3,
#endif
#if (TNUM_PORT >= 6)
	1,
#endif
};
#endif

/*
 *  SIO�h���C�o�̏�����
 */
void
sio_initialize(intptr_t exinf)
{
	int i;

	for (i = 0; i < TNUM_PORT; i++) {
		siopcb_table[i].port = i;
		siopcb_table[i].reg = sioreg_table[i];
		siopcb_table[i].exinf = 0;
	}
}

/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB* siopcb;
	uint8_t dummy;

	if (siopid > TNUM_PORT) {
		return NULL;
	}

	siopcb = GET_SIOPCB(siopid);
	siopcb->exinf = exinf;

	/* Init UART */
	if (read_reg16(SUnCON(siopcb->reg)) & SUnCONL_Un0EN == 0) {
		/*
		 *  �Y���̃|�[�g���utarget_config.c�v�́uusart_early_init()�v�Ŋ��ɏ���������Ă���ꍇ��
		 *  �ȉ��̏����̓X�L�b�v����D
		 *  ����ȊO�̃|�[�g���g�p����ꍇ�́C�ȉ��̏����̑O�Ƀu���b�N�N���b�N�C�u���b�N���Z�b�g�����
		 *  �ʐM�Ɏg�p����ėp�|�[�g�̃��[�h��ݒ肷��K�v������D
		 *  �i�utarget_config.c�v�́utarget_initialize()�v�C�uinitPort()�v���Q�Ƃ̂��ƁD�j
		 */
		write_reg16(SUnCON(siopcb->reg), 0x0000U);
		write_reg8(SUnMOD(siopcb->reg), (SUnMOD_SUnINTS | SUnMOD_SUnTIMD | SUnMOD_SUnMD1));
		write_reg16(UAn0MOD(siopcb->reg), (UAn0MOD_Un0CK1));
		write_reg16(UAn0BRT(siopcb->reg), UART_0F_PARAM_BR);
		write_reg8(UAn0BRC(siopcb->reg), UART_0F_PARAM_BR_ADJUST);
		write_reg8(UAn0STAT(siopcb->reg), (UAn0STAT_Un0PER | UAn0STAT_Un0OER | UAn0STAT_Un0FER));
		write_reg8(UAn0STAT(siopcb->reg), UAn0STAT_Un0FUL);
		write_reg8(SUnDLYL(siopcb->reg), 0);
	    /* Required to read data in buffer before UART start */
		dummy = (volatile uint8_t)read_reg8(SDnBUFL(siopcb->reg));
		/* Start UART */
		set_reg8(SUnCONL(siopcb->reg), SUnCONL_Un0EN);
	}

	return siopcb;
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	clear_reg8(SUnCONL(p_siopcb->reg), SUnCONL_Un0EN);
}

/*
 *  SIO�̎�M�����݃T�[�r�X���[�`��
 */
void
sio_isr_rx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);
	sio_irdy_rcv(siopcb->exinf);
}

/*
 *  SIO�̑��M�����݃T�[�r�X���[�`��
 */
void
sio_isr_tx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);
	sio_irdy_snd(siopcb->exinf);
}

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char c)
{
	if (read_reg8(UAn0STAT(siopcb->reg)) & UAn0STAT_Un0FUL)
		return false;

	write_reg8(SDnBUFH(siopcb->reg), c);
	return true;
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
	return (int_t)read_reg8(SDnBUFL(siopcb->reg));
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		ena_int(INTNO_SIO_TX);
		break;
	case SIO_RDY_RCV:
		ena_int(INTNO_SIO_RX);
		break;
	default:
		break;
	}
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	case SIO_RDY_SND:
		dis_int(INTNO_SIO_TX);
		break;
	case SIO_RDY_RCV:
		dis_int(INTNO_SIO_RX);
		break;
	default:
		break;
	}
}
