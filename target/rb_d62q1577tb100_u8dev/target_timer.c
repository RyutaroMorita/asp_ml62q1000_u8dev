/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
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
 *		タイマドライバ（RB-D62Q1577TB100用）
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_syssvc.h"
#include "target_timer.h"
#include "drivers.h"

/*
 *  タイマの起動処理
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK	cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	initTm_t st_initTimer;

	/*
	 *  タイマ周期を設定し，タイマの動作を開始する．
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
//	timer0_setTimerClock(TM_CS_LSCLK);	// ここで低速(LSCLK)に戻している！

	/* Enable interrupt */
	irq_tm0_clearIRQ();

	/* Start timer*/
	timer0_start();
}

/*
 *  タイマの停止処理
 */
void
target_timer_terminate(intptr_t exinf)
{
	/*
	 *  タイマの動作を停止する．
	 */
	ftimer0_stop();
}

/*
 *  タイマ割込みハンドラ
 */
void
target_timer_handler(void)
{
	signal_time();					/* タイムティックの供給 */
}
