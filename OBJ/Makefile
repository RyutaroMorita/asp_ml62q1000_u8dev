#
#  TOPPERS/ASP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Advanced Standard Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2006-2014 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
# 
#  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
#  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
#  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
#  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
#      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
#      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
#  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
#      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
#      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
#      �̖��ۏ؋K����f�ڂ��邱�ƁD
#  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
#      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
#      �ƁD
#    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
#        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
#    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
#        �񍐂��邱�ƁD
#  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
#      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
#      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
#      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
#      �Ɛӂ��邱�ƁD
# 
#  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
#  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
#  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
#  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
#  �̐ӔC�𕉂�Ȃ��D
# 
#  $Id: Makefile 2728 2015-12-30 01:46:11Z ertl-honda $
# 

#
#  �r���h�̌��ʂ̑S�Ă��R���\�[���ɕ\���ł��Ȃ�����
#  �ucygwin�v�ɂĈȉ��̃R�}���h���g�p����D
#
#  $ make all | tee build.log
#

#
#  �^�[�Q�b�g�̎w��iMakefile.target�ŏ㏑�������̂�h�����߁j
#
all:

# Export environment variables
export DCL=C:/U8Dev/Dcl
export INCLU8=C:/U8Dev/Inc;C:/U8Dev/BuildTools/V2_02_00/Inc
export LIBU8=C:/U8Dev/BuildTools/V2_02_00/Lib

#
#  �^�[�Q�b�g���̂̒�`
#
TARGET = rb_d62q1577tb100_u8dev

#
#  �v���O���~���O����̒�`
#
LIBS = LU8100LW.LIB

#
#  �\�[�X�t�@�C���̃f�B���N�g���̒�`
#
SRCDIR = ..

#
#  �I�u�W�F�N�g�t�@�C�����̊g���q�̐ݒ�
#
OBJEXT = abs

#
#  ���s���̒�`�i�^�[�Q�b�g�ˑ��ɏ㏑�������ꍇ������j
#
DBGENV := 

#
#  �J�[�l�����C�u�����ilibkernel.a�j�̃f�B���N�g����
#  �i�J�[�l�����C�u������make�Ώۂɂ��鎞�́C��ɒ�`����j
#
KERNEL_LIB = 

#
#  �J�[�l�����֐��P�ʂŃR���p�C�����邩�ǂ����̒�`
#
KERNEL_FUNCOBJS = 

#
#  �g���[�X���O���擾���邩�ǂ����̒�`
#
ENABLE_TRACE = 

#
#  ���[�e�B���e�B�v���O�����̖���
#
PERL = /usr/bin/perl
CFG = $(SRCDIR)/cfg/cfg/cfg
NM = $(PRCDIR)/utils/nmu8
MAKEDEP = $(PRCDIR)/utils/makedepu8

#
#  �I�u�W�F�N�g�t�@�C�����̒�`
#
OBJNAME = asp
ifdef OBJEXT
  OBJFILE = $(OBJNAME).$(OBJEXT)
  CFG1_OUT = cfg1_out.$(OBJEXT)
else
  OBJFILE = $(OBJNAME)
  CFG1_OUT = cfg1_out
endif

#
#  �^�[�Q�b�g�ˑ����̃f�B���N�g���̒�`
#
TARGETDIR = $(SRCDIR)/target/$(TARGET)

#
#  �^�[�Q�b�g�ˑ��̒�`�̃C���N���[�h
#
include $(TARGETDIR)/Makefile.target

#
#  �R���t�B�M�����[�^�֌W�̕ϐ��̒�`
#
CFG_TABS := --api-table $(SRCDIR)/kernel_u8dev/kernel_api.csv \
			--cfg1-def-table $(SRCDIR)/kernel_u8dev/kernel_def.csv $(CFG_TABS)

CFG_ASMOBJS := $(CFG_ASMOBJS)
CFG_COBJS := kernel_cfg.o $(CFG_COBJS)
CFG_OBJS := $(CFG_ASMOBJS) $(CFG_COBJS)
CFG2_OUT_SRCS := kernel_cfg.h kernel_cfg.c $(CFG2_OUT_SRCS)

#
#  ���ʃR���p�C���I�v�V�����̒�`
#
COPTS := $(COPTS) -SD
ifndef OMIT_WARNING_ALL
  COPTS := $(COPTS) -W1
endif
ifndef OMIT_OPTIMIZATION
  COPTS := $(COPTS) -Om
endif
CDEFS := $(CDEFS) 
INCLUDES := -I. -I$(SRCDIR)/include_u8dev -I$(SRCDIR)/arch -I$(SRCDIR) $(INCLUDES)
LDFLAGS := $(LDFLAGS) 
CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) 
LIBS := $(LIBS) $(CXXLIBS)
CFLAGS = $(COPTS) $(CDEFS) $(INCLUDES)
ASMFLAGS = $(ASMOPTS)

#
#  �A�v���P�[�V�����v���O�����Ɋւ����`
#
APPLNAME = sample1
APPLDIR = 
APPL_CFG = $(APPLNAME).cfg

APPL_DIR = $(APPLDIR) $(SRCDIR)/library
APPL_ASMOBJS =
APPL_COBJS = $(APPLNAME).o 
APPL_COBJS := $(APPL_COBJS) log_output.o vasyslog.o t_perror.o strerror.o
APPL_CFLAGS =
APPL_LIBS =
ifdef APPLDIR
  INCLUDES := $(INCLUDES) $(foreach dir,$(APPLDIR),-I$(dir))
endif

#
#  �V�X�e���T�[�r�X�Ɋւ����`
#
SYSSVC_DIR := $(SYSSVC_DIR) $(PRCDIR)/syssvc $(SRCDIR)/syssvc $(SRCDIR)/library
SYSSVC_ASMOBJS := $(SYSSVC_ASMOBJS)
SYSSVC_COBJS := $(SYSSVC_COBJS) banner.o syslog.o serial.o logtask.o \
				 $(CXXRTS)
SYSSVC_CFLAGS := $(SYSSVC_CFLAGS)
SYSSVC_LIBS := $(SYSSVC_LIBS)
INCLUDES := $(INCLUDES)

#
#  �J�[�l���Ɋւ����`
#
#  KERNEL_ASMOBJS: �J�[�l�����C�u�����Ɋ܂߂�C�\�[�X���A�Z���u�������
#				   �I�u�W�F�N�g�t�@�C���D
#  KERNEL_COBJS: �J�[�l���̃��C�u�����Ɋ܂߂�C�\�[�X��C����ŁC�\�[�X
#				 �t�@�C����1��1�ɑΉ�����I�u�W�F�N�g�t�@�C���D
#  KERNEL_LCSRCS: �J�[�l���̃��C�u�����Ɋ܂߂�C����̃\�[�X�t�@�C���ŁC
#				  1�̃\�[�X�t�@�C�����畡���̃I�u�W�F�N�g�t�@�C����
#				  ��������́D
#  KERNEL_LCOBJS: ��̃\�[�X�t�@�C�����琶�������I�u�W�F�N�g�t�@�C���D
#  KERNEL_AUX_COBJS: ���[�h���W���[���Ɋ܂߂Ȃ����C�J�[�l���̃\�[�X�t�@
#					 �C���Ɠ����I�v�V������K�p���ăR���p�C�����ׂ��C�\�[
#					 �X��C����̃I�u�W�F�N�g�t�@�C���D
#
KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/kernel_u8dev
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS)
KERNEL_CFLAGS := $(KERNEL_CFLAGS) -I$(SRCDIR)/kernel_u8dev
ifdef OMIT_MAKEOFFSET
  OFFSET_H =
else
  OFFSET_H = offset.h
ifndef OFFSET_TF
  KERNEL_AUX_COBJS := $(KERNEL_AUX_COBJS) makeoffset.o
endif
endif

#
#  �^�[�Q�b�g�t�@�C���i�����𓯎��ɑI�����Ă͂Ȃ�Ȃ��j
#
all: $(OBJFILE)
#all: $(OBJNAME).bin
#all: $(OBJNAME).srec

##### �ȉ��͕ҏW���Ȃ����� #####

#
#  ���Ɉˑ�����R���p�C���I�v�V�����̒�`
#
ifdef DBGENV
  CDEFS := $(CDEFS) -D$(DBGENV)
endif

#
#  �J�[�l���̃t�@�C���\���̒�`
#
include $(SRCDIR)/kernel_u8dev/Makefile.kernel
ifdef KERNEL_FUNCOBJS
  KERNEL_LCSRCS := $(KERNEL_FCSRCS)
  KERNEL_LCOBJS := $(foreach file,$(KERNEL_FCSRCS),$($(file:.c=)))
else
  KERNEL_CFLAGS := -DALLFUNC $(KERNEL_CFLAGS)
  KERNEL_COBJS := $(KERNEL_COBJS) \
					$(foreach file,$(KERNEL_FCSRCS),$(file:.c=.o))
endif

#
#  �\�[�X�t�@�C���̂���f�B���N�g���Ɋւ����`
#
vpath %.c $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.asm $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.cfg $(APPL_DIR)

#
#  �R���p�C���̂��߂̕ϐ��̒�`
#
KERNEL_LIB_COBJS = $(KERNEL_COBJS) $(KERNEL_LCOBJS)
KERNEL_LIB_ASMOBJS = $(KERNEL_ASMOBJS)
SYSSVC_OBJS = $(SYSSVC_ASMOBJS) $(SYSSVC_COBJS)
APPL_OBJS = $(APPL_ASMOBJS) $(APPL_COBJS) $(APPL_CXXOBJS)
ALL_OBJS = $(START_COBJS) $(START_ASMOBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG_OBJS) \
											$(END_OBJS) $(HIDDEN_COBJS) $(HIDDEN_ASMOBJS)
ifdef KERNEL_LIB
  ALL_LIBS = $(APPL_LIBS) $(SYSSVC_LIBS) -lkernel $(LIBS)
  LIBS_DEP = $(filter %.a,$(ALL_LIBS)) $(KERNEL_LIB)/libkernel.lib
  LDFLAGS := $(LDFLAGS) -L$(KERNEL_LIB)
  REALCLEAN_FILES := libkernel.lib $(REALCLEAN_FILES)
else
  ALL_LIBS = $(APPL_LIBS) $(SYSSVC_LIBS) libkernel.lib $(LIBS)
  LIBS_DEP = $(filter %.lib,$(ALL_LIBS))
endif

  LDFLAGS := $(LDFLAGS)
  CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS)

#
#  �I�t�Z�b�g�t�@�C���ioffset.h�j�̐����K��
#
ifdef OFFSET_TF
offset.h: $(APPL_CFG) kernel_cfg.timestamp
	$(CFG) --pass 3 --kernel asp $(INCLUDES) \
				--rom-image cfg1_out.srec --symbol-table cfg1_out.syms \
				-T $(OFFSET_TF) $(CFG_TABS) $<
else
offset.h: makeoffset.s $(SRCDIR)/utils/genoffset
	$(PERL) $(SRCDIR)/utils/genoffset makeoffset.s > offset.h
endif

#
#  �J�[�l���̃R���t�B�M�����[�V�����t�@�C���̐���
#
cfg1_out.c: $(APPL_CFG)
	$(CFG) --pass 1 --kernel asp $(INCLUDES) $(CFG_TABS) $<

$(CFG2_OUT_SRCS): kernel_cfg.timestamp
kernel_cfg.timestamp: $(APPL_CFG) \
						$(START_COBJS) $(START_ASMOBJS) cfg1_out.o $(END_OBJS) $(HIDDEN_COBJS) $(HIDDEN_ASMOBJS)
	$(LINK) $(LDFLAGS) $(START_COBJS) $(START_ASMOBJS) cfg1_out.o $(END_OBJS), \
			$(CFG1_OUT), ,\;
	$(NM) cfg1_out.map > cfg1_out.syms
	$(OBJCOPY) -S -D $(CFG1_OUT) cfg1_out.srec
#	objcopy -I srec -O binary cfg1_out.srec cfg1_out.bin
	$(CFG) --pass 2 --kernel asp $(INCLUDES) \
				-T $(TARGETDIR)/target.tf $(CFG_TABS) $<
	touch -r kernel_cfg.c kernel_cfg.timestamp

#
#  �J�[�l�����C�u�����t�@�C���̐���
#
libkernel.lib: $(OFFSET_H) $(KERNEL_LIB_COBJS) $(KERNEL_LIB_ASMOBJS)

$(KERNEL_LIB_COBJS): %.o: %.c
	$(CC) $(CFLAGS) $(KERNEL_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -SD -O$(*F).o $(*F).asm
	$(AR) libkernel.lib -$(*F).o\; || :
	$(AR) libkernel.lib +$(*F).o\;
	rm -f libkernel.timestamp

$(KERNEL_LIB_ASMOBJS): %.o: %.asm
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -D -O$(*F).o $<
	$(AR) libkernel.lib -$(*F).o\; || :
	$(AR) libkernel.lib +$(*F).o\;
	rm -f libkernel.timestamp

libkernel.timestamp:
	touch libkernel.timestamp

#
#  ���ʂȈˑ��֌W�̒�`
#
banner.o: kernel_cfg.timestamp $(filter-out banner.o,$(ALL_OBJS)) $(LIBS_DEP) libkernel.timestamp

#
#  �S�̂̃����N
#
$(OBJFILE): $(APPL_CFG) kernel_cfg.timestamp $(ALL_OBJS) $(LIBS_DEP) libkernel.timestamp
	@echo "ALL_OBJS:$(ALL_OBJS) LIBS_DEP:$(LIBS_DEP)"
	$(LINK) $(LDFLAGS) $(START_COBJS) $(START_ASMOBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG_OBJS) $(END_OBJS), \
			$(OBJFILE), , $(ALL_LIBS)\;
	$(NM) $(OBJNAME).map > $(OBJNAME).syms
	$(OBJCOPY) -S -D $(OBJFILE) $(OBJNAME).srec
#	objcopy -I srec -O binary $(OBJNAME).srec $(OBJNAME).bin
	$(CFG) --pass 3 --kernel asp $(INCLUDES) \
				--rom-image $(OBJNAME).srec --symbol-table $(OBJNAME).syms \
				-T $(TARGETDIR)/target_check.tf $(CFG_TABS) $<

#
#  �o�C�i���t�@�C���̐���
#
$(OBJNAME).bin: $(OBJFILE)
	$(OBJCOPY) -O binary -S $(OBJFILE) $(OBJNAME).bin

#
#  S���R�[�h�t�@�C���̐���
#
$(OBJNAME).srec: $(OBJFILE)
	$(OBJCOPY) -O srec -S $(OBJFILE) $(OBJNAME).srec

#
#  �R���p�C�����ʂ̏���
#
.PHONY: clean
clean:
	rm -f \#* *~ *.o *.map *.ler *.cal *.prn *.asm *.lib *.lst *.lbk *.sym *.log $(CLEAN_FILES)
	rm -f $(OBJFILE) $(OBJNAME).syms $(OBJNAME).srec $(OBJNAME).bin
	rm -f kernel_cfg.timestamp $(CFG2_OUT_SRCS) libkernel.timestamp
	rm -f cfg1_out.c $(CFG1_OUT) cfg1_out.syms cfg1_out.srec
ifndef KERNEL_LIB
	rm -f libkernel.lib
endif
	rm -f makeoffset.s offset.h

.PHONY: cleankernel
cleankernel:
	rm -rf $(KERNEL_LIB_COBJS)
	rm -rf $(KERNEL_LIB_ASMOBJS)
	rm -f makeoffset.s offset.h

.PHONY: cleandep
cleandep:
	if ! [ -f Makefile.depend ]; then \
		rm -f kernel_cfg.timestamp $(CFG2_OUT_SRCS); \
		rm -f cfg1_out.c cfg1_out.o $(CFG1_OUT) cfg1_out.syms cfg1_out.srec; \
		rm -f makeoffset.s offset.h; \
	fi
	rm -f Makefile.depend

.PHONY: realclean
realclean: cleandep clean
	rm -f $(REALCLEAN_FILES)

#
#  �R���t�B�M�����[�^�����������t�@�C���̃R���p�C�����[���ƈˑ��֌W�쐬
#  ���[���̒�`
#
#  �R���t�B�M�����[�^�����������t�@�C���́C�A�v���P�[�V�����v���O�����p�C
#  �V�X�e���T�[�r�X�p�C�J�[�l���p�̂��ׂẴI�v�V������t���ăR���p�C��
#  ����D
#
ALL_CFG_COBJS = $(CFG_COBJS) cfg1_out.o
ALL_CFG_ASMOBJS = $(CFG_ASMOBJS)
CFG_CFLAGS = $(APPL_CFLAGS) $(SYSSVC_CFLAGS) $(KERNEL_CFLAGS)
CFG_ASMFLAGS = $(APPL_ASMFLAGS) $(SYSSVC_ASMFLAGS) $(KERNEL_ASMFLAGS)

$(ALL_CFG_COBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CFG_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
	$(AS) $(ASMFLAGS) $(CFG_ASMFLAGS) -SD -O$(*F).o $(*F).asm

$(ALL_CFG_COBJS:.o=.d): %.d: %.c
	$(CC) $(CFLAGS) $(CFG_CFLAGS) -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(CFG_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(ALL_CFG_ASMOBJS): %.o: %.asm
	$(AS) $(ASMFLAGS) $(CFG_ASMFLAGS) -D -O$(*F).o $<

$(ALL_CFG_ASMOBJS:.o=.d): %.d: %.asm
	$(AS) $(ASMFLAGS) $(CFG_ASMFLAGS) -SD -NO -PR$(*F).prn $<
	$(MAKEDEP) $(*F).prn >> Makefile.depend

#
#  ����Ȉˑ��֌W�쐬���[���̒�`
#
cfg1_out.depend: $(APPL_CFG)
	@$(CFG) -M cfg1_out.c $(INCLUDES) $< >> Makefile.depend

#makeoffset.d: makeoffset.c
#	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-T "makeoffset.s" -O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

#
#  �ˑ��֌W�t�@�C���̐���
#
.PHONY: gendepend
gendepend:
	@echo "Generating Makefile.depend."

.PHONY: depend
ifdef KERNEL_LIB
depend: cleandep kernel_cfg.timestamp gendepend \
		cfg1_out.depend cfg1_out.d \
		$(ALL_OBJS:.o=.d)
else
depend: cleandep $(OFFSET_H) kernel_cfg.timestamp gendepend \
		cfg1_out.depend cfg1_out.d \
		$(KERNEL_AUX_COBJS:.o=.d) $(KERNEL_ASMOBJS:.o=.d) \
		$(KERNEL_COBJS:.o=.d) $(KERNEL_LCSRCS:.c=.d) $(ALL_OBJS:.o=.d)
endif

#
#  �ˑ��֌W�t�@�C�����C���N���[�h
#
-include Makefile.depend

#
#  �J���c�[���̃R�}���h���̒�`
#
ifeq ($(TOOL),u8dev)
  #
  #  U8DEV�J�����p
  #
  CC = ccu8
  AS = rasu8
  LINK = rlu8
  AR = libu8
  OBJCOPY = cnvohu8
endif

#
#  DTU8�f�o�b�K�̋N��
#
.PHONY: debug
debug:
	dtu8

#
#  �R���p�C�����[���̒�`
#
#KERNEL_ALL_COBJS = $(KERNEL_COBJS) $(KERNEL_AUX_COBJS)

$(KERNEL_AUX_COBJS): %.o: %.c
	$(CC) $(CFLAGS) $(KERNEL_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -SD -O$(*F).o $(*F).asm

#$(KERNEL_ALL_COBJS): %.o: %.c
#	$(CC) $(CFLAGS) $(KERNEL_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
#	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -SD -O$(*F).o $(*F).asm

$(KERNEL_ASMOBJS): %.o: %.asm
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -D -O$(*F).o $<

$(SYSSVC_COBJS): %.o: %.c
	$(CC) $(CFLAGS) $(SYSSVC_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
	$(AS) $(ASMFLAGS) -SD -O$(*F).o $(*F).asm

$(SYSSVC_ASMOBJS): %.o: %.asm
	$(AS) $(ASMFLAGS) $(SYSSVC_ASMFLAGS) -D -O$(*F).o $<

$(APPL_COBJS): %.o: %.c
	$(CC) $(CFLAGS) $(APPL_CFLAGS) -Fa$(*F).asm -LE$(*F).ler -CT$(*F).cal $<
	$(AS) $(ASMFLAGS) -SD -O$(*F).o $(*F).asm

$(APPL_ASMOBJS): %.o: %.asm
	$(AS) $(ASMFLAGS) $(APPL_ASMFLAGS) -D -O$(*F).o $<

#
#  �ˑ��֌W�쐬���[���̒�`
#
$(KERNEL_COBJS:.o=.d): %.d: %.c
	$(CC) $(CFLAGS) $(KERNEL_CFLAGS) -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(KERNEL_LCSRCS:.c=.d): %.d: %.c
	$(CC) $(CFLAGS) $(KERNEL_CFLAGS) -DEFALLFUNC -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(KERNEL_ASMOBJS:.o=.d): %.d: %.asm
	$(AS) $(ASMFLAGS) $(KERNEL_ASMFLAGS) -D -NO -PR$(*F).prn $<
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(SYSSVC_COBJS:.o=.d): %.d: %.c
	$(CC) $(CFLAGS) $(SYSSVC_CFLAGS) -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(APPL_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(SYSSVC_ASMOBJS:.o=.d): %.d: %.asm
	$(AS) $(ASMFLAGS) $(SYSSVC_ASMFLAGS) -D -NO -PR$(*F).prn $<
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(APPL_COBJS:.o=.d): %.d: %.c
	$(CC) $(CFLAGS) $(APPL_CFLAGS) -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(APPL_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(APPL_CXXOBJS:.o=.d): %.d: %.cpp
	$(CC) $(CFLAGS) $(APPL_CFLAGS) -Fa$(*F).asm $<
	$(AS) $(ASMFLAGS) $(APPL_ASMFLAGS) -SD -NO -PR$(*F).prn $(*F).asm
	$(MAKEDEP) $(*F).prn >> Makefile.depend

$(APPL_ASMOBJS:.o=.d): %.d: %.asm
	$(AS) $(ASMFLAGS) $(APPL_ASMFLAGS) -D -NO -PR$(*F).prn $<
	$(MAKEDEP) $(*F).prn >> Makefile.depend