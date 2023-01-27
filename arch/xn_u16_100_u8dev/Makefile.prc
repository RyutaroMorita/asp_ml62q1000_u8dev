#
#		Makefileのプロセッサ依存部（uX-U16/100用）
#

#
#  GNU開発環境のターゲットアーキテクチャの定義
#
U8DEV_TARGET = xn_u16_100-abs

#
#  プロセッサ依存部ディレクトリ名の定義
#
PRCDIR = $(SRCDIR)/arch/$(PRC)_$(TOOL)

#
#  コンパイルオプション
#
INCLUDES := $(INCLUDES) -I$(PRCDIR)/driver/inc
ASMOPTS := $(ASMOPTS) -CD -ABW -DN -ML -WRPEAST -L -NS -NR -NPL -NPW
#                 -SD -ABW -TML621577 -ML -near $(INCLUDES) -Om -Oa -W1 -D_ML62Q1577
COPTS := $(COPTS) -ABW -ML -near -Oa -SL63
LDFLAGS := $(LDFLAGS) -D -SD -S -CC -ABW -EXC -LA

#
#  カーネルに関する定義
#
KERNEL_DIR := $(KERNEL_DIR) $(PRCDIR) $(PRCDIR)/driver/src

#  「prc_support」をアセンブラソースとする場合にコメントアウト
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o prc_sil.o prc_support.o

#  「prc_support」をC言語ソースとする場合にコメントアウト
#KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
#KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o

#
#  コンフィギュレータ関係の変数の定義
#
CFG_TABS := $(CFG_TABS) --cfg1-def-table $(PRCDIR)/prc_def.csv

#
#  オフセットファイル生成のための定義
#
OFFSET_TF = $(PRCDIR)/prc_offset.tf
