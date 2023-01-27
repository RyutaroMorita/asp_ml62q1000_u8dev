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
 *		�^�[�Q�b�g�ˑ����W���[���iRB-D62Q1577TB100�p�j
 */

#include "kernel_impl.h"
#include "target_syssvc.h"
#include <sil.h>
#include "drivers.h"


#define UART_00_CLOCK_HZ          (SYS_CLOCK)												/* The base clock frequency approximately */
#define UART_0F_PARAM_BR          (UART_GET_BAUDRATE_COUNT(UART_00_CLOCK_HZ, BPS_SETTING))	/* The parameter of baud rate             */
#define UART_0F_PARAM_BR_ADJUST   (UART_GET_BAUDRATE_ADJUST(UART_00_CLOCK_HZ, BPS_SETTING))	/* The parameter of baud rate adjustment  */


/*
 *  �v���Z�b�T���ʂ̂��߂̕ϐ��i�}���`�v���Z�b�T�Ή��j
 */
uint_t	board_id;			/* �{�[�hID */
void	*board_addr;		/* ���[�J���������̐擪�A�h���X */

#pragma ASM
	STACKSEG DEFAULT_STACKSEG
#pragma ENDASM

static int8_t setSystemClock(void)
{
    flmod_t flmod;
    initVls_t initVls;
    fcon_t fcon;

    /* HSCLK�̖����� */
    clk_disHsclk();

    flmod.source = CLK_LOSCM_RC;
    flmod.filter = CLK_LFTSEL_USE_FILTER;
    flmod.crystalmode = CLK_LMOD_STANDARD;
    clk_setLsclk(&flmod);

    /* VDD���x���̃`�F�b�N */
    vls0_stop();
    initVls.mode       = VLS_AMD_SINGLE1;
    initVls.resultMode = VLS_SEL_DISABLE;
    initVls.divide     = VLS_DIV_DIV1;
    initVls.sampling   = VLS_CS_DISABLE;
    vls0_init(&initVls);

    vls0_setTh(VLS_LV_185);

    vls0_start();
    while (vls0_getRunning() == 1U);

    if (vls0_getResult() == 1U)
        return -1;

    /* HSCLK�̐ݒ� */
    fcon.sysclk = CLK_SYSC_HSCLK;
    fcon.outclk = CLK_OUTC_HSCLK_DIV2;
    fcon.wakeup = CLK_FHUT_3MS;
    clk_setHsclk(&fcon);

    /* HSCLK�̗L���� */
    clk_enaHsclk();

    /* SYSCLK�̐ݒ� */
    clk_setSysclk(CLK_SYSCLK_HSCLK);

    return 0;
}

/*
 *  �uRB-D62Q1577TB100�v�]���{�[�h�̃|�[�g�����ݒ�
 */
static void initPort( void )
{
	/* P0 */
	write_reg8(P0DO, 0x00);
	write_reg16(P0MOD01, 0x0005);	// P00/TEST
	write_reg16(P0MOD23, 0x2211);	// P02/SU0_RXD0, P03/SU0_TXD1
	write_reg16(P0MOD45, 0x0000);
	write_reg16(P0MOD67, 0x0000);
	write_reg16(P0PMD, 0x0000);

	/* P1 */
	write_reg8(P1DO, 0x00);
	write_reg16(P1MOD01, 0x0000);
	write_reg16(P1MOD23, 0x0000);
	write_reg16(P1MOD45, 0x0000);
	write_reg16(P1MOD67, 0x0000);
	write_reg16(P1PMD, 0x0000);

	/* P2 */
	write_reg8(P2DO, 0x07);			// P20, P21, P22: High
	write_reg16(P2MOD01, 0x0A0A);	// P20/GPIO-OUT,P21/GPIO-OUT
	write_reg16(P2MOD23, 0x000A);	// P22/GPIO-OUT
	write_reg16(P2MOD45, 0x0000);
	write_reg16(P2MOD67, 0x0000);
	write_reg16(P2PMD, 0x0000);

	/* P3 */
	write_reg8(P3DO, 0x00);
	write_reg16(P3MOD01, 0x0000);
	write_reg16(P3MOD23, 0x0000);
	write_reg16(P3PMD, 0x0000);

	/* P4 */
	write_reg8(P4DO, 0x00);
	write_reg16(P4MOD01, 0x0000);
	write_reg16(P4MOD23, 0x0000);
	write_reg16(P4MOD45, 0x0000);
	write_reg16(P4MOD67, 0x0000);

	/* P5 */
	write_reg8(P5DO, 0x00);
	write_reg16(P5MOD01, 0x0000);
	write_reg16(P5MOD23, 0x0000);
	write_reg16(P5MOD45, 0x0000);
	write_reg16(P5MOD67, 0x0000);

	/* P6 */
	write_reg8(P6DO, 0x00);
	write_reg16(P6MOD01, 0x0000);
	write_reg16(P6MOD23, 0x0000);
	write_reg16(P6MOD45, 0x0000);
	write_reg16(P6MOD67, 0x0000);

	/* P7 */
	write_reg8(P7DO, 0x00);
	write_reg16(P7MOD01, 0x0000);
	write_reg16(P7MOD23, 0x0000);
	write_reg16(P7MOD45, 0x0000);
	write_reg16(P7MOD67, 0x0000);

	/* P8 */
	write_reg8(P8DO, 0x00);
	write_reg16(P8MOD01, 0x0000);
	write_reg16(P8MOD23, 0x0000);
	write_reg16(P8MOD45, 0x0000);
	write_reg16(P8MOD67, 0x0000);

	/* P9 */
	write_reg8(P9DO, 0x00);
	write_reg16(P9MOD01, 0x0000);
	write_reg16(P9MOD23, 0x0000);
	write_reg16(P9MOD45, 0x0000);
	write_reg16(P9MOD67, 0x0000);

	/* PA */
	write_reg8(PADO, 0x00);
	write_reg16(PAMOD01, 0x0000);
	write_reg16(PAMOD23, 0x0000);
	write_reg16(PAMOD45, 0x0000);
	write_reg16(PAMOD67, 0x0000);

	/* PB */
	write_reg8(PBDO, 0x00);
	write_reg16(PBMOD01, 0x0000);
	write_reg16(PBMOD23, 0x0000);
	write_reg16(PBMOD45, 0x0000);
	write_reg16(PBMOD67, 0x0000);

	/* PX */
	write_reg16(PXTMOD01, 0x0000);
}

static void usart_early_init()
{
	uint8_t dummy;

	/* UART�̏����� */
	write_reg16(SU0CON, 0x0000U);
	write_reg8(SU0MOD, 0xC2U);
	write_reg16(UA00MOD, 0x0004U);	/* UART_DIR_LSB | UART_NEG_POSITIVE | UART_STP_1BIT | UART_PT_NOTHING | UART_LG_8BIT | UART_RSS_DIV2 | UART_CK_HSCLK */
	uart0f_setBaudrateCnt(UART_0F_PARAM_BR);
	uart0f_setBaudrateAdj(UART_0F_PARAM_BR_ADJUST);
	uart0f_clrErrorStatus();
	uart0f_clrFull();
	uart0f_setInterval(0x00U);

    /* �o�b�t�@����ɂ��Ă��� */
	dummy = (volatile uint8_t)uart0f_getData();

	/* UART�J�n */
	uart0f_start();
}

/*
 *  �^�[�Q�b�g�ˑ��̏�����
 */
void
target_initialize(void)
{
	initVls_t initVls;

	/*
	 *  �v���Z�b�T�ˑ��̏�����
	 */
	prc_initialize();

	/* BRECON0L */
		/*  7bit - RSETM7		16 �r�b�g�^�C�}7 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  6bit - RSETM6		16 �r�b�g�^�C�}6 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  5bit - RSETM5		16 �r�b�g�^�C�}5 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  4bit - RSETM4		16 �r�b�g�^�C�}4 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  3bit - RSETM3		16 �r�b�g�^�C�}3 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  2bit - RSETM2		16 �r�b�g�^�C�}2 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  1bit - RSETM1		16 �r�b�g�^�C�}1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  0bit - RSETM0		16 �r�b�g�^�C�}0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
	write_reg8(BRECON0L, 0xfeU);

	/* BRECON1 */
		/* 15bit - */
		/* 14bit - */
		/* 13bit - */
		/* 12bit - RSEI2CU0		I2C �o�X���j�b�g0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/* 11bit - */
		/* 10bit - */
		/*  9bit - RSEI2CM1		I2C �o�X�}�X�^1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  8bit - RSEI2CM0		I2C �o�X�}�X�^0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  7bit - RSEFTM7		�t�@���N�V���i���^�C�}7 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  6bit - RSEFTM6		�t�@���N�V���i���^�C�}6 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  5bit - RSEFTM5		�t�@���N�V���i���^�C�}5 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  4bit - RSEFTM4		�t�@���N�V���i���^�C�}4 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  3bit - RSEFTM3		�t�@���N�V���i���^�C�}3 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  2bit - RSEFTM2		�t�@���N�V���i���^�C�}2 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  1bit - RSEFTM1		�t�@���N�V���i���^�C�}1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  0bit - RSEFTM0		�t�@���N�V���i���^�C�}0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
	write_reg16(BRECON1, 0x13ffU);

	/* BRECON2 */
		/* 15bit - RSEDMA		DMA �R���g���[���̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/* 14bit - RSEBUZ		�u�U�[�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/* 13bit - RSEACC		�揜�Z��̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/* 12bit - */
		/* 11bit - RSECRC		CRC ���Z��̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/* 10bit - */
		/*  9bit - */
		/*  8bit - */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSESU5		�V���A���ʐM���j�b�g5 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  4bit - RSESU4		�V���A���ʐM���j�b�g4 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  3bit - RSESU3		�V���A���ʐM���j�b�g3 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  2bit - RSESU2		�V���A���ʐM���j�b�g2 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  1bit - RSESU1		�V���A���ʐM���j�b�g1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  0bit - RSESU0		�V���A���ʐM���j�b�g0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
//	write_reg16(BRECON2, 0x403fU);
	write_reg16(BRECON2, 0x403eU);

	/* BRECON3L */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSECMP1		�A�i���O�R���p���[�^1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  4bit - RSECMP0		�A�i���O�R���p���[�^10�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  3bit - RSEDAC1		D/A �R���o�[�^1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  2bit - RSELCD		LCD �h���C�o�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  1bit - RSEDAC		D/A �R���o�[�^�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
		/*  0bit - RSESAD		������r�^A/D �R���o�[�^�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0: ���Z�b�g���� / 1: ���Z�b�g��) */
	write_reg8(BRECON3L, 0x3bU);

	/* BCKCON0L */
		/*  7bit - DCKTM7		16 �r�b�g�^�C�}7 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  6bit - DCKTM6		16 �r�b�g�^�C�}6 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  5bit - DCKTM5		16 �r�b�g�^�C�}5 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  4bit - DCKTM4		16 �r�b�g�^�C�}4 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  3bit - DCKTM3		16 �r�b�g�^�C�}3 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  2bit - DCKTM2		16 �r�b�g�^�C�}2 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  1bit - DCKTM1		16 �r�b�g�^�C�}1 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  0bit - DCKTM0		16 �r�b�g�^�C�}0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
	write_reg8(BCKCON0L, 0xfeU);

	/* BCKCON1 */
		/* 15bit - */
		/* 14bit - */
		/* 13bit - */
		/* 12bit - DCKI2CU0		I2C �o�X���j�b�g0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/* 11bit - */
		/* 10bit - */
		/*  9bit - DCKI2CM1		I2C �o�X�}�X�^1 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  8bit - DCKI2CM0		I2C �o�X�}�X�^0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  7bit - DCKFTM7		�t�@���N�V���i���^�C�}7 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  6bit - DCKFTM6		�t�@���N�V���i���^�C�}6 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  5bit - DCKFTM5		�t�@���N�V���i���^�C�}5 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  4bit - DCKFTM4		�t�@���N�V���i���^�C�}4 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  3bit - DCKFTM3		�t�@���N�V���i���^�C�}3 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  2bit - DCKFTM2		�t�@���N�V���i���^�C�}2 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  1bit - DCKFTM1		�t�@���N�V���i���^�C�}1 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  0bit - DCKFTM0		�t�@���N�V���i���^�C�}0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
	write_reg16(BCKCON1, 0x13ffU);

	/* BCKCON2 */
		/* 15bit - DCKDMA		DMA �R���g���[���̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/* 14bit - RSEBUZ		�u�U�[�̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/* 13bit - RSEACC		�揜�Z��̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/* 12bit - */
		/* 11bit - RSECRC		CRC ���Z��̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/* 10bit - */
		/*  9bit - */
		/*  8bit - */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSESU5		�V���A���ʐM���j�b�g5 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/*  4bit - RSESU4		�V���A���ʐM���j�b�g4 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/*  3bit - RSESU3		�V���A���ʐM���j�b�g3 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/*  2bit - RSESU2		�V���A���ʐM���j�b�g2 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/*  1bit - RSESU1		�V���A���ʐM���j�b�g1 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
		/*  0bit - RSESU0		�V���A���ʐM���j�b�g0 �̃��Z�b�g�𐧌䂷��r�b�g�ł��B(0:���� / 1:��~) */
//	write_reg16(BCKCON2, 0x403fU);
	write_reg16(BCKCON2, 0x403eU);

	/* BCKCON3L */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - DCKCMP1		�A�i���O�R���p���[�^1 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  4bit - DCKCMP0		�A�i���O�R���p���[�^0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  3bit - DCKDAC1		D/A �R���o�[�^1 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  2bit - DCKLCD		LCD �h���C�o�̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  1bit - DCKDAC		D/A �R���o�[�^0 �̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
		/*  0bit - DCKSAD		������r�^A/D �R���o�[�^�̃N���b�N���������^��~����r�b�g�ł��B(0:���� / 1:��~) */
	write_reg8(BCKCON3L, 0x3bU);

	/* �V�X�e���N���b�N�̐ݒ� */
	if (setSystemClock() != 0) {
		/* Error */
		target_exit();
	}

    /* �|�[�g�����ݒ� */
    initPort();

	/* �ᑬ�^�C���x�[�X�J�E���^���g���␳���W�X�^�̐ݒ� */
	tbc_setLtbAdj(0x0000U);

	/* �d�����x���Ď��@�\(VLS)�̐ݒ� */
	initVls.mode       = VLS_AMD_SUPERVISOR;
	initVls.resultMode = VLS_SEL_RESET;
	initVls.divide     = VLS_DIV_DIV1;
	initVls.sampling   = VLS_CS_DISABLE;
	vls0_init(&initVls);

	/*�@�d�����x���Ď��@�\(VLS)����d���̐ݒ�@*/
	vls0_setTh(VLS_LV_185);

	/* �d�����x���Ď��@�\(VLS)�̊J�n */
	vls0_start();

	/* �f�o�b�O�p�V���A���ʐM�|�[�g�̐ݒ� */
	usart_early_init();
}

/*
 *  �^�[�Q�b�g�ˑ��̏I������
 */
void
target_exit(void)
{
	/*
	 *  �v���Z�b�T�ˑ��̏I������
	 */
	prc_terminate();
	while(1);
}

/*
 *  �V�X�e�����O�̒჌�x���o�͂̂��߂̕����o��
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		while (uart0f_getFull());
		uart0f_putData('\r');
	}
	while (uart0f_getFull());
	uart0f_putData(c);
}

#define ADR_IRQ0		0xF028U
#define ADR_IE0			0xF020U
#define ADR_ILC0		0xF034U
#define INTNO_WDTINT	0
#define INTNO_VLS0INT	2

/*
 *  �����ݗv�����C���̑����̐ݒ�
 *
 *  ASP�J�[�l���ł̗��p��z�肵�āC�p�����[�^�G���[�̓A�T�[�V�����Ń`�F�b
 *  �N���Ă���Dcfg_int�T�[�r�X�R�[����݂���ꍇ�ɂ́C�G���[��Ԃ��悤
 *  �ɂ��ׂ��ł��낤�D
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  �����ݗv���}�X�N����(�K�v�ȏꍇ)
	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}

/*
 *  �����ݗv���֎~�t���O�̃Z�b�g
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���Z�b�g���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
bool_t
x_disable_int(INTNO intno)
{
	uint16_t adr;
	int bit;
	if (!VALID_INTNO_CFGINT(intno))
		return false;
	adr = ADR_IE0 + (((uint16_t)intno + 3) / 8);
	if (intno == INTNO_WDTINT)
		bit = 0;
	else
		bit = (((uint16_t)intno + 3) % 8);
	*(volatile unsigned char __near *)adr &= ~(1 << bit);
	return(true);
}

/*
 *  �����ݗv���֎~�t���O�̃N���A
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
bool_t
x_enable_int(INTNO intno)
{
	uint16_t adr;
	int bit;
	if (!VALID_INTNO_CFGINT(intno))
		return false;
	adr = ADR_IE0 + (((uint16_t)intno + 3) / 8);
	if (intno == INTNO_WDTINT)
		bit = 0;
	else
		bit = (((uint16_t)intno + 3) % 8);
	*(volatile unsigned char __near *)adr |= (1 << bit);
	return(true);
}

/*
 *  �����ݗv���̃N���A
 */
void
x_clear_int(INTNO intno)
{
	uint16_t adr;
	int bit;
	adr = ADR_IRQ0 + (((uint16_t)intno + 3) / 8);
	if (intno == INTNO_WDTINT)
		bit = 0;
	else
		bit = (((uint16_t)intno + 3) % 8);
	*(volatile unsigned char __near *)adr &= ~(1 << bit);
}

/*
 *  �����ݗv���̃`�F�b�N
 */
bool_t
x_probe_int(INTNO intno)
{
	uint16_t adr;
	int bit;
	adr = ADR_IRQ0 + (((uint16_t)intno + 3) / 8);
	if (intno == INTNO_WDTINT)
		bit = 0;
	else
		bit = (((uint16_t)intno + 3) % 8);
	if (*(volatile unsigned char __near *)adr & (1 << bit))
		return(true);
	return false;
}
