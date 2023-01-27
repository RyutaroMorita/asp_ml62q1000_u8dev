/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2006 by Embedded and Real-Time Systems Laboratory
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
 *		sil.hのターゲット依存部（RB-D62Q1577TB100用）
 *
 *  このインクルードファイルは，sil.hの先頭でインクルードされる．他のファ
 *  イルからは直接インクルードすることはない．このファイルをインクルー
 *  ドする前に，t_stddef.hがインクルードされるので，それらに依存しても
 *  よい．
 */

#ifndef TOPPERS_TARGET_SIL_H
#define TOPPERS_TARGET_SIL_H

/*
 *  プロセッサで共通な定義
 */
#include "xn_u16_100_u8dev/prc_sil.h"

/*
 *  「ML62Q1577」割込み番号（intno）の定義
 */

#define TINTNO_WDTINT		 1U
//#define TINTNO_			 2U
#define TINTNO_VLS0INT		 3U
//#define TINTNO_			 4U

#define TINTNO_EXI0INT		 5U
#define TINTNO_EXI1INT		 6U
#define TINTNO_EXI2INT		 7U
#define TINTNO_EXI3INT		 8U
#define TINTNO_EXI4INT		 9U
#define TINTNO_EXI5INT		10U
#define TINTNO_EXI6INT		11U
#define TINTNO_EXI7INT		12U

#define TINTNO_CBUINT		13U
#define TINTNO_DMACINT		14U
#define TINTNO_MCSINT		15U
#define TINTNO_SIU00INT		16U
#define TINTNO_SIU01INT		17U
//#define TINTNO_			18U
#define TINTNO_SADINT		19U
//#define TINTNO_			20U

#define TINTNO_EXTXINT		21U
//#define TINTNO_			22U
#define TINTNO_I2CM0INT		23U
#define TINTNO_I2CM1INT		24U
#define TINTNO_FTM0INT		25U
#define TINTNO_FTM1INT		26U
#define TINTNO_TM0INT		27U
#define TINTNO_TM1INT		28U

#define TINTNO_I2CU0INT		29U
#define TINTNO_SIU10INT		30U
#define TINTNO_SIU11INT		31U
//#define TINTNO_			32U
#define TINTNO_FTM2INT		33U
#define TINTNO_FTM3INT		34U
#define TINTNO_TM2INT		35U
#define TINTNO_TM3INT		36U

#define TINTNO_SIU20INT		37U
#define TINTNO_SIU21INT		38U
#define TINTNO_CMP0INT		39U
#define TINTNO_CMP1INT		40U
#define TINTNO_FTM4INT		41U
#define TINTNO_FTM5INT		42U
#define TINTNO_TM4INT		43U
#define TINTNO_TM5INT		44U

#define TINTNO_SIU30INT		45U
#define TINTNO_SIU31INT		46U
#define TINTNO_SIU40INT		47U
#define TINTNO_SIU41INT		48U
#define TINTNO_FTM6INT		49U
#define TINTNO_FTM7INT		50U
#define TINTNO_TM6INT		51U
#define TINTNO_TM7INT		52U

#define TINTNO_SIU50INT		53U
#define TINTNO_SIU51INT		54U
#define TINTNO_LTB0INT		55U
//#define TINTNO	_		56U
#define TINTNO_LTB1INT		57U
#define TINTNO_LTB2INT		58U
#define TINTNO_RTCINT		59U
//#define TINTNO_			60U

#endif /* TOPPERS_TARGET_SIL_H */
