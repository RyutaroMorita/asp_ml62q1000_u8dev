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
 *		ターゲット依存モジュール（RB-D62Q1577TB100用）
 */

#include "kernel_impl.h"
#include "target_syssvc.h"
#include <sil.h>
#include "drivers.h"


#define UART_00_CLOCK_HZ          (SYS_CLOCK)												/* The base clock frequency approximately */
#define UART_0F_PARAM_BR          (UART_GET_BAUDRATE_COUNT(UART_00_CLOCK_HZ, BPS_SETTING))	/* The parameter of baud rate             */
#define UART_0F_PARAM_BR_ADJUST   (UART_GET_BAUDRATE_ADJUST(UART_00_CLOCK_HZ, BPS_SETTING))	/* The parameter of baud rate adjustment  */


/*
 *  プロセッサ識別のための変数（マルチプロセッサ対応）
 */
uint_t	board_id;			/* ボードID */
void	*board_addr;		/* ローカルメモリの先頭アドレス */

#pragma ASM
	STACKSEG DEFAULT_STACKSEG
#pragma ENDASM

static int8_t setSystemClock(void)
{
    flmod_t flmod;
    initVls_t initVls;
    fcon_t fcon;

    /* HSCLKの無効化 */
    clk_disHsclk();

    flmod.source = CLK_LOSCM_RC;
    flmod.filter = CLK_LFTSEL_USE_FILTER;
    flmod.crystalmode = CLK_LMOD_STANDARD;
    clk_setLsclk(&flmod);

    /* VDDレベルのチェック */
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

    /* HSCLKの設定 */
    fcon.sysclk = CLK_SYSC_HSCLK;
    fcon.outclk = CLK_OUTC_HSCLK_DIV2;
    fcon.wakeup = CLK_FHUT_3MS;
    clk_setHsclk(&fcon);

    /* HSCLKの有効化 */
    clk_enaHsclk();

    /* SYSCLKの設定 */
    clk_setSysclk(CLK_SYSCLK_HSCLK);

    return 0;
}

/*
 *  「RB-D62Q1577TB100」評価ボードのポート初期設定
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

	/* UARTの初期化 */
	write_reg16(SU0CON, 0x0000U);
	write_reg8(SU0MOD, 0xC2U);
	write_reg16(UA00MOD, 0x0004U);	/* UART_DIR_LSB | UART_NEG_POSITIVE | UART_STP_1BIT | UART_PT_NOTHING | UART_LG_8BIT | UART_RSS_DIV2 | UART_CK_HSCLK */
	uart0f_setBaudrateCnt(UART_0F_PARAM_BR);
	uart0f_setBaudrateAdj(UART_0F_PARAM_BR_ADJUST);
	uart0f_clrErrorStatus();
	uart0f_clrFull();
	uart0f_setInterval(0x00U);

    /* バッファを空にしておく */
	dummy = (volatile uint8_t)uart0f_getData();

	/* UART開始 */
	uart0f_start();
}

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	initVls_t initVls;

	/*
	 *  プロセッサ依存の初期化
	 */
	prc_initialize();

	/* BRECON0L */
		/*  7bit - RSETM7		16 ビットタイマ7 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  6bit - RSETM6		16 ビットタイマ6 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  5bit - RSETM5		16 ビットタイマ5 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  4bit - RSETM4		16 ビットタイマ4 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  3bit - RSETM3		16 ビットタイマ3 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  2bit - RSETM2		16 ビットタイマ2 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  1bit - RSETM1		16 ビットタイマ1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  0bit - RSETM0		16 ビットタイマ0 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
	write_reg8(BRECON0L, 0xfeU);

	/* BRECON1 */
		/* 15bit - */
		/* 14bit - */
		/* 13bit - */
		/* 12bit - RSEI2CU0		I2C バスユニット0 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/* 11bit - */
		/* 10bit - */
		/*  9bit - RSEI2CM1		I2C バスマスタ1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  8bit - RSEI2CM0		I2C バスマスタ0 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  7bit - RSEFTM7		ファンクショナルタイマ7 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  6bit - RSEFTM6		ファンクショナルタイマ6 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  5bit - RSEFTM5		ファンクショナルタイマ5 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  4bit - RSEFTM4		ファンクショナルタイマ4 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  3bit - RSEFTM3		ファンクショナルタイマ3 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  2bit - RSEFTM2		ファンクショナルタイマ2 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  1bit - RSEFTM1		ファンクショナルタイマ1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  0bit - RSEFTM0		ファンクショナルタイマ0 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
	write_reg16(BRECON1, 0x13ffU);

	/* BRECON2 */
		/* 15bit - RSEDMA		DMA コントローラのリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/* 14bit - RSEBUZ		ブザーのリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/* 13bit - RSEACC		乗除算器のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/* 12bit - */
		/* 11bit - RSECRC		CRC 演算器のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/* 10bit - */
		/*  9bit - */
		/*  8bit - */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSESU5		シリアル通信ユニット5 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  4bit - RSESU4		シリアル通信ユニット4 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  3bit - RSESU3		シリアル通信ユニット3 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  2bit - RSESU2		シリアル通信ユニット2 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  1bit - RSESU1		シリアル通信ユニット1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  0bit - RSESU0		シリアル通信ユニット0 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
//	write_reg16(BRECON2, 0x403fU);
	write_reg16(BRECON2, 0x403eU);

	/* BRECON3L */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSECMP1		アナログコンパレータ1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  4bit - RSECMP0		アナログコンパレータ10のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  3bit - RSEDAC1		D/A コンバータ1 のリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  2bit - RSELCD		LCD ドライバのリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  1bit - RSEDAC		D/A コンバータのリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
		/*  0bit - RSESAD		逐次比較型A/D コンバータのリセットを制御するビットです。(0: リセット解除 / 1: リセット中) */
	write_reg8(BRECON3L, 0x3bU);

	/* BCKCON0L */
		/*  7bit - DCKTM7		16 ビットタイマ7 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  6bit - DCKTM6		16 ビットタイマ6 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  5bit - DCKTM5		16 ビットタイマ5 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  4bit - DCKTM4		16 ビットタイマ4 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  3bit - DCKTM3		16 ビットタイマ3 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  2bit - DCKTM2		16 ビットタイマ2 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  1bit - DCKTM1		16 ビットタイマ1 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  0bit - DCKTM0		16 ビットタイマ0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
	write_reg8(BCKCON0L, 0xfeU);

	/* BCKCON1 */
		/* 15bit - */
		/* 14bit - */
		/* 13bit - */
		/* 12bit - DCKI2CU0		I2C バスユニット0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/* 11bit - */
		/* 10bit - */
		/*  9bit - DCKI2CM1		I2C バスマスタ1 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  8bit - DCKI2CM0		I2C バスマスタ0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  7bit - DCKFTM7		ファンクショナルタイマ7 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  6bit - DCKFTM6		ファンクショナルタイマ6 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  5bit - DCKFTM5		ファンクショナルタイマ5 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  4bit - DCKFTM4		ファンクショナルタイマ4 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  3bit - DCKFTM3		ファンクショナルタイマ3 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  2bit - DCKFTM2		ファンクショナルタイマ2 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  1bit - DCKFTM1		ファンクショナルタイマ1 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  0bit - DCKFTM0		ファンクショナルタイマ0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
	write_reg16(BCKCON1, 0x13ffU);

	/* BCKCON2 */
		/* 15bit - DCKDMA		DMA コントローラのクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/* 14bit - RSEBUZ		ブザーのリセットを制御するビットです。(0:許可 / 1:停止) */
		/* 13bit - RSEACC		乗除算器のリセットを制御するビットです。(0:許可 / 1:停止) */
		/* 12bit - */
		/* 11bit - RSECRC		CRC 演算器のリセットを制御するビットです。(0:許可 / 1:停止) */
		/* 10bit - */
		/*  9bit - */
		/*  8bit - */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - RSESU5		シリアル通信ユニット5 のリセットを制御するビットです。(0:許可 / 1:停止) */
		/*  4bit - RSESU4		シリアル通信ユニット4 のリセットを制御するビットです。(0:許可 / 1:停止) */
		/*  3bit - RSESU3		シリアル通信ユニット3 のリセットを制御するビットです。(0:許可 / 1:停止) */
		/*  2bit - RSESU2		シリアル通信ユニット2 のリセットを制御するビットです。(0:許可 / 1:停止) */
		/*  1bit - RSESU1		シリアル通信ユニット1 のリセットを制御するビットです。(0:許可 / 1:停止) */
		/*  0bit - RSESU0		シリアル通信ユニット0 のリセットを制御するビットです。(0:許可 / 1:停止) */
//	write_reg16(BCKCON2, 0x403fU);
	write_reg16(BCKCON2, 0x403eU);

	/* BCKCON3L */
		/*  7bit - */
		/*  6bit - */
		/*  5bit - DCKCMP1		アナログコンパレータ1 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  4bit - DCKCMP0		アナログコンパレータ0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  3bit - DCKDAC1		D/A コンバータ1 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  2bit - DCKLCD		LCD ドライバのクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  1bit - DCKDAC		D/A コンバータ0 のクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
		/*  0bit - DCKSAD		逐次比較型A/D コンバータのクロック供給を許可／停止するビットです。(0:許可 / 1:停止) */
	write_reg8(BCKCON3L, 0x3bU);

	/* システムクロックの設定 */
	if (setSystemClock() != 0) {
		/* Error */
		target_exit();
	}

    /* ポート初期設定 */
    initPort();

	/* 低速タイムベースカウンタ周波数補正レジスタの設定 */
	tbc_setLtbAdj(0x0000U);

	/* 電圧レベル監視機能(VLS)の設定 */
	initVls.mode       = VLS_AMD_SUPERVISOR;
	initVls.resultMode = VLS_SEL_RESET;
	initVls.divide     = VLS_DIV_DIV1;
	initVls.sampling   = VLS_CS_DISABLE;
	vls0_init(&initVls);

	/*　電圧レベル監視機能(VLS)判定電圧の設定　*/
	vls0_setTh(VLS_LV_185);

	/* 電圧レベル監視機能(VLS)の開始 */
	vls0_start();

	/* デバッグ用シリアル通信ポートの設定 */
	usart_early_init();
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *  プロセッサ依存の終了処理
	 */
	prc_terminate();
	while(1);
}

/*
 *  システムログの低レベル出力のための文字出力
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
 *  割込み要求ラインの属性の設定
 *
 *  ASPカーネルでの利用を想定して，パラメータエラーはアサーションでチェッ
 *  クしている．cfg_intサービスコールを設ける場合には，エラーを返すよう
 *  にすべきであろう．
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  割込み要求マスク解除(必要な場合)
	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，falseを返す．
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
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
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
 *  割込み要求のクリア
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
 *  割込み要求のチェック
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
