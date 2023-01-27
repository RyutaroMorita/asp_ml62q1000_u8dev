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
#  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
# 
#  $Id: Makefile 2728 2015-12-30 01:46:11Z ertl-honda $
# 

#
#  ビルドの結果の全てをコンソールに表示できないため
#  「cygwin」にて以下のコマンドを使用する．
#
#  $ make all | tee build.log
#

#
#  ターゲットの指定（Makefile.targetで上書きされるのを防ぐため）
#
all:

# Export environment variables
export DCL=C:/U8Dev/Dcl
export INCLU8=C:/U8Dev/Inc;C:/U8Dev/BuildTools/V2_02_00/Inc
export LIBU8=C:/U8Dev/BuildTools/V2_02_00/Lib

#
#  ターゲット略称の定義
#
TARGET = rb_d62q1577tb100_u8dev

#
#  プログラミング言語の定義
#
LIBS = LU8100LW.LIB

#
#  ソースファイルのディレクトリの定義
#
SRCDIR = ..

#
#  オブジェクトファイル名の拡張子の設定
#
OBJEXT = abs

#
#  実行環境の定義（ターゲット依存に上書きされる場合がある）
#
DBGENV := 

#
#  カーネルライブラリ（libkernel.a）のディレクトリ名
#  （カーネルライブラリもmake対象にする時は，空に定義する）
#
KERNEL_LIB = 

#
#  カーネルを関数単位でコンパイルするかどうかの定義
#
KERNEL_FUNCOBJS = 

#
#  トレースログを取得するかどうかの定義
#
ENABLE_TRACE = 

#
#  ユーティリティプログラムの名称
#
PERL = /usr/bin/perl
CFG = $(SRCDIR)/cfg/cfg/cfg
NM = $(PRCDIR)/utils/nmu8
MAKEDEP = $(PRCDIR)/utils/makedepu8

#
#  オブジェクトファイル名の定義
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
#  ターゲット依存部のディレクトリの定義
#
TARGETDIR = $(SRCDIR)/target/$(TARGET)

#
#  ターゲット依存の定義のインクルード
#
include $(TARGETDIR)/Makefile.target

#
#  コンフィギュレータ関係の変数の定義
#
CFG_TABS := --api-table $(SRCDIR)/kernel_u8dev/kernel_api.csv \
			--cfg1-def-table $(SRCDIR)/kernel_u8dev/kernel_def.csv $(CFG_TABS)

CFG_ASMOBJS := $(CFG_ASMOBJS)
CFG_COBJS := kernel_cfg.o $(CFG_COBJS)
CFG_OBJS := $(CFG_ASMOBJS) $(CFG_COBJS)
CFG2_OUT_SRCS := kernel_cfg.h kernel_cfg.c $(CFG2_OUT_SRCS)

#
#  共通コンパイルオプションの定義
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
#  アプリケーションプログラムに関する定義
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
#  システムサービスに関する定義
#
SYSSVC_DIR := $(SYSSVC_DIR) $(PRCDIR)/syssvc $(SRCDIR)/syssvc $(SRCDIR)/library
SYSSVC_ASMOBJS := $(SYSSVC_ASMOBJS)
SYSSVC_COBJS := $(SYSSVC_COBJS) banner.o syslog.o serial.o logtask.o \
				 $(CXXRTS)
SYSSVC_CFLAGS := $(SYSSVC_CFLAGS)
SYSSVC_LIBS := $(SYSSVC_LIBS)
INCLUDES := $(INCLUDES)

#
#  カーネルに関する定義
#
#  KERNEL_ASMOBJS: カーネルライブラリに含める，ソースがアセンブリ言語の
#				   オブジェクトファイル．
#  KERNEL_COBJS: カーネルのライブラリに含める，ソースがC言語で，ソース
#				 ファイルと1対1に対応するオブジェクトファイル．
#  KERNEL_LCSRCS: カーネルのライブラリに含めるC言語のソースファイルで，
#				  1つのソースファイルから複数のオブジェクトファイルを生
#				  成するもの．
#  KERNEL_LCOBJS: 上のソースファイルから生成されるオブジェクトファイル．
#  KERNEL_AUX_COBJS: ロードモジュールに含めないが，カーネルのソースファ
#					 イルと同じオプションを適用してコンパイルすべき，ソー
#					 スがC言語のオブジェクトファイル．
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
#  ターゲットファイル（複数を同時に選択してはならない）
#
all: $(OBJFILE)
#all: $(OBJNAME).bin
#all: $(OBJNAME).srec

##### 以下は編集しないこと #####

#
#  環境に依存するコンパイルオプションの定義
#
ifdef DBGENV
  CDEFS := $(CDEFS) -D$(DBGENV)
endif

#
#  カーネルのファイル構成の定義
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
#  ソースファイルのあるディレクトリに関する定義
#
vpath %.c $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.asm $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.cfg $(APPL_DIR)

#
#  コンパイルのための変数の定義
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
#  オフセットファイル（offset.h）の生成規則
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
#  カーネルのコンフィギュレーションファイルの生成
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
#  カーネルライブラリファイルの生成
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
#  特別な依存関係の定義
#
banner.o: kernel_cfg.timestamp $(filter-out banner.o,$(ALL_OBJS)) $(LIBS_DEP) libkernel.timestamp

#
#  全体のリンク
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
#  バイナリファイルの生成
#
$(OBJNAME).bin: $(OBJFILE)
	$(OBJCOPY) -O binary -S $(OBJFILE) $(OBJNAME).bin

#
#  Sレコードファイルの生成
#
$(OBJNAME).srec: $(OBJFILE)
	$(OBJCOPY) -O srec -S $(OBJFILE) $(OBJNAME).srec

#
#  コンパイル結果の消去
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
#  コンフィギュレータが生成したファイルのコンパイルルールと依存関係作成
#  ルールの定義
#
#  コンフィギュレータが生成したファイルは，アプリケーションプログラム用，
#  システムサービス用，カーネル用のすべてのオプションを付けてコンパイル
#  する．
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
#  特殊な依存関係作成ルールの定義
#
cfg1_out.depend: $(APPL_CFG)
	@$(CFG) -M cfg1_out.c $(INCLUDES) $< >> Makefile.depend

#makeoffset.d: makeoffset.c
#	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-T "makeoffset.s" -O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

#
#  依存関係ファイルの生成
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
#  依存関係ファイルをインクルード
#
-include Makefile.depend

#
#  開発ツールのコマンド名の定義
#
ifeq ($(TOOL),u8dev)
  #
  #  U8DEV開発環境用
  #
  CC = ccu8
  AS = rasu8
  LINK = rlu8
  AR = libu8
  OBJCOPY = cnvohu8
endif

#
#  DTU8デバッガの起動
#
.PHONY: debug
debug:
	dtu8

#
#  コンパイルルールの定義
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
#  依存関係作成ルールの定義
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
