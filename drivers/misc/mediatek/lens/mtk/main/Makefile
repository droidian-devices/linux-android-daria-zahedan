#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

#
# Makefile for misc devices that really don't fit anywhere else.
#

MTK_PLATFORM := $(subst ",,$(CONFIG_MTK_PLATFORM))
ARCH_MTK_PROJECT := $(subst ",,$(CONFIG_ARCH_MTK_PROJECT))

MTK_CUSTOM_PATH  := $(srctree)/drivers/misc/mediatek


subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/lens/mtk/main/inc
subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/lens/mtk/main/common/lc898122af
subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/lens/mtk/main/common/lc898212xdaf/inc
ifeq ($(CONFIG_MTK_LENS_BU63165AF_SUPPORT), y)
  subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/lens/mtk/main/common/bu63165af/inc
else
  subdir-ccflags-y += -I$(MTK_CUSTOM_PATH)/lens/mtk/main/common/bu63169af/inc
endif
ifeq ($(CONFIG_MACH_MT6779), y)
  ccflags-y += -I$(srctree)/drivers/misc/mediatek/timer/timesync/
endif
subdir-ccflags-y += -Wframe-larger-than=20624

obj-$(CONFIG_MTK_LENS)    += mainaf.o

mainaf-y  += main_lens.o
mainaf-y  += common/fp5516weaf/FP5516WEAF.o
mainaf-y  += common/fp5510e2af/FP5510E2AF.o
mainaf-y  += common/bu6424af/BU6424AF.o
mainaf-y  += common/bu6429af/BU6429AF.o
mainaf-y  += common/bu64748af/bu64748_function.o
mainaf-y  += common/bu64748af/bu64748af.o
mainaf-y  += common/dw9714af/DW9714AF.o
mainaf-y  += common/dw9800waf/DW9800WAF.o
mainaf-y  += common/dw9814af/DW9814AF.o
mainaf-y  += common/dw9718af/DW9718AF.o
mainaf-y  += common/dw9718gaf/DW9718AF.o
mainaf-y  += common/dw9718saf/DW9718SAF.o
mainaf-y  += common/dw9718taf/DW9718TAF.o
mainaf-y  += common/dw9719taf/DW9719TAF.o
mainaf-y  += common/dw9763af/DW9763AF.o
mainaf-y  += common/dw9761af/DW9761AF.o
mainaf-y  += common/dw9839af/DW9839AF.o
mainaf-y  += common/gt9764af/GT9764AF.o
mainaf-y  += common/lc898212af/LC898212AF.o
mainaf-y  += common/lc898212xdaf/LC898212XDAF.o
mainaf-y  += common/lc898212xdaf/AfInter.o
mainaf-y  += common/lc898212xdaf/AfInit.o
mainaf-y  += common/lc898212xdaf/AfSTMV.o
mainaf-y  += common/lc898214af/LC898214AF.o
mainaf-y  += common/lc898217af/LC898217AF.o
mainaf-y  += common/lc898217afa/LC898217AFA.o
mainaf-y  += common/lc898217afb/LC898217AFB.o
mainaf-y  += common/lc898217afc/LC898217AFC.o
mainaf-y  += common/lc898229af/LC898229AF.o
mainaf-y  += common/lc898122af/LC898122AF.o
mainaf-y  += common/lc898122af/OisCmd.o
mainaf-y  += common/lc898122af/OisIni.o
mainaf-y  += common/wv511aaf/WV511AAF.o
mainaf-y  += common/ak7371af/AK7371AF.o
mainaf-y  += common/bu63169af/BU63169AF.o
mainaf-y  += common/bu63169af/OIS_func.o
mainaf-y  += common/bu63169af/OIS_main.o
mainaf-y  += common/bu63169af/OIS_user.o
mainaf-y  += common/bu64253gwzaf/BU64253GWZAF.o
#/*prize add by zhuzhengjiang for lens:zc535 20220110 start*/
mainaf-y  += common/zc535af/ZC535AF.o
mainaf-y  += common/gt9767af/GT9767AF.o
mainaf-y  += common/gt9772af/GT9772AF.o
mainaf-y  += common/aw8601csr/AW8601CSR.o
mainaf-y  += common/fp5510fe4af/FP5510FE4AF.o
mainaf-y  += common/cn3927elcaf/CN3927ELCAF.o
ifeq ($(CONFIG_MTK_LENS_DW9781CAF_SUPPORT), y)
mainaf-y  += common/dw9781caf/DW9781CAF.o
mainaf-y  += common/dw9781caf/OIS_func_register.o
endif
mainaf-y  += common/aw8601xaf/AW8601xAF.o
mainaf-y  += common/aw86014af/AW86014AF.o
mainaf-y  += common/gt9764baf/GT9764BAF.o
mainaf-y  += common/aw86017csraf/AW86017CSRAF.o
#/*prize add by zhuzhengjiang for lens:zc535 20220110 end*/

