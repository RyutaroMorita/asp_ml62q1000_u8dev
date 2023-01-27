#
#		Makefile�̃v���Z�b�T�ˑ����iuX-U16/100�p�j
#

#
#  GNU�J�����̃^�[�Q�b�g�A�[�L�e�N�`���̒�`
#
U8DEV_TARGET = xn_u16_100-abs

#
#  �v���Z�b�T�ˑ����f�B���N�g�����̒�`
#
PRCDIR = $(SRCDIR)/arch/$(PRC)_$(TOOL)

#
#  �R���p�C���I�v�V����
#
INCLUDES := $(INCLUDES) -I$(PRCDIR)/driver/inc
ASMOPTS := $(ASMOPTS) -CD -ABW -DN -ML -WRPEAST -L -NS -NR -NPL -NPW
#                 -SD -ABW -TML621577 -ML -near $(INCLUDES) -Om -Oa -W1 -D_ML62Q1577
COPTS := $(COPTS) -ABW -ML -near -Oa -SL63
LDFLAGS := $(LDFLAGS) -D -SD -S -CC -ABW -EXC -LA

#
#  �J�[�l���Ɋւ����`
#
KERNEL_DIR := $(KERNEL_DIR) $(PRCDIR) $(PRCDIR)/driver/src

#  �uprc_support�v���A�Z���u���\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o prc_sil.o prc_support.o

#  �uprc_support�v��C����\�[�X�Ƃ���ꍇ�ɃR�����g�A�E�g
#KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
#KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o

#
#  �R���t�B�M�����[�^�֌W�̕ϐ��̒�`
#
CFG_TABS := $(CFG_TABS) --cfg1-def-table $(PRCDIR)/prc_def.csv

#
#  �I�t�Z�b�g�t�@�C�������̂��߂̒�`
#
OFFSET_TF = $(PRCDIR)/prc_offset.tf
