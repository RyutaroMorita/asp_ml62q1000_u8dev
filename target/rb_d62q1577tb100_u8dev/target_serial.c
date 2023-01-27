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
 *		シリアルI/Oデバイス（SIO）ドライバ（RB-D62Q1577TB100用）
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "drivers.h"

#define UART_0F_PARAM_BR          (UART_GET_BAUDRATE_COUNT(SYS_CLOCK, BPS_SETTING))		/* The parameter of baud rate             */
#define UART_0F_PARAM_BR_ADJUST   (UART_GET_BAUDRATE_ADJUST(SYS_CLOCK, BPS_SETTING))	/* The parameter of baud rate adjustment  */

/*
 * レジスタ設定値
 */
#define PORT2SIOPID(x)	((x) + 1)
#define INDEX_PORT(x)	((x) - 1)
#define GET_SIOPCB(x)	(&siopcb_table[INDEX_PORT(x)])

/*
 * シリアル通信ユニット・レジスタ定義
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
 *  シリアルポートの管理ブロック
 */
struct sio_port_control_block {
	ID port;
	uint16_t reg;
	intptr_t exinf;
};


/*
 * シリアルI/Oポート管理ブロックエリア
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
 *  SIOドライバの初期化
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
 *  シリアルI/Oポートのオープン
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
		 *  該当のポートが「target_config.c」の「usart_early_init()」で既に初期化されている場合は
		 *  以下の処理はスキップする．
		 *  それ以外のポートを使用する場合は，以下の処理の前にブロッククロック，ブロックリセットおよび
		 *  通信に使用する汎用ポートのモードを設定する必要がある．
		 *  （「target_config.c」の「target_initialize()」，「initPort()」を参照のこと．）
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
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	clear_reg8(SUnCONL(p_siopcb->reg), SUnCONL_Un0EN);
}

/*
 *  SIOの受信割込みサービスルーチン
 */
void
sio_isr_rx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);
	sio_irdy_rcv(siopcb->exinf);
}

/*
 *  SIOの送信割込みサービスルーチン
 */
void
sio_isr_tx(intptr_t exinf)
{
	SIOPCB* siopcb = GET_SIOPCB(exinf);
	sio_irdy_snd(siopcb->exinf);
}

/*
 *  シリアルI/Oポートへの文字送信
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
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
	return (int_t)read_reg8(SDnBUFL(siopcb->reg));
}

/*
 *  シリアルI/Oポートからのコールバックの許可
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
 *  シリアルI/Oポートからのコールバックの禁止
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
