/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2006 by Embedded and Real-Time Systems Laboratory
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
 *		sil.h�̃^�[�Q�b�g�ˑ����iRB-D62Q1577TB100�p�j
 *
 *  ���̃C���N���[�h�t�@�C���́Csil.h�̐擪�ŃC���N���[�h�����D���̃t�@
 *  �C������͒��ڃC���N���[�h���邱�Ƃ͂Ȃ��D���̃t�@�C�����C���N���[
 *  �h����O�ɁCt_stddef.h���C���N���[�h�����̂ŁC�����Ɉˑ����Ă�
 *  �悢�D
 */

#ifndef TOPPERS_TARGET_SIL_H
#define TOPPERS_TARGET_SIL_H

/*
 *  �v���Z�b�T�ŋ��ʂȒ�`
 */
#include "xn_u16_100_u8dev/prc_sil.h"

/*
 *  �uML62Q1577�v�����ݔԍ��iintno�j�̒�`
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
