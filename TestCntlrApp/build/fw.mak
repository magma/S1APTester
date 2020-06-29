# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

# /***************************************************************************
#
#       Name:   S1 Simulator Test Framwwork
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file.
#
#       Env:    Linux 2.4.x with GNU C (gcc)
#
#               BUILD TARGETS:
#                  clean    : remove TFW object files
#                  cleanall : remove all object files
#
#       File:  fw.mak
#
#       Prg:
#
# **************************************************************************/

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#

# TFW Library name
LIBNAME=libtfw.so

# Source code folders
FW_APP_DIR=../src/tfwApp
UE_APP_DIR=../src/ueApp
FW_CM_DIR=../src/fw_cm
SM_DIR=../src/sm
SSI_DIR=../src/ssi
HI_DIR=../src/tucl
CM_DIR=../src/cm
RLOG_DIR=../src/rlog
NB_DIR=../src/enbApp
EG_DIR=../src/egtpu
SZ_DIR=../src/s1ap
SB_DIR=../src/sctp
TIMER_DIR=../src/timer
UE_SEC_DIR=../src/sec

#JSON_INCLUDE=../src/Json/include
#JSON_SRC_DIR=../src/Json/src

OBJ_DIR=../obj
OBJ_CM=../obj/cm
OBJ_TUCL=../obj/tucl
OBJ_S1AP=../obj/s1ap
OBJ_SCTP=../obj/sctp
OBJ_EGTP=../obj/egtp
OBJ_SSI=../obj/ssi
OBJ_RLOG=../obj/rlog
OBJ_TIMER=../obj/timer

# Binaries path
BIN_DIR=../bin

# library path
LIB_DIR=../lib

# pcap archive name
PCAP_ARC=libpcap-64bit.a

# object file suffix
OBJ=o

# MTSS defines
MTOPTS = -DSS -DSS_MT -DSS_MT_TMR

# SSI Files
SSOPTS = -DSS

CMOPTS=-DCMINET_BSDCOMPAT -DSS_TICKS_SEC=100 -DCM_PASN_ESC_SUPPORT \
		 -DCM_PASN_CLASS_IDTYPE  -DCMFILE_REORG_1 -DCM_INET2  -DEU_DAT_APP \
		 -DEU_DAT_APP -DEG -DCMFILE_REORG_2 -DSSINT2 -DCMKV2 -DHI_MULTI_THREADED \
		 -DYS_ENB_CFG -DLTE_ENB_PAL -DSS_PERF -DSS_WL_REGION=1 -DNO_ERRCLS \
		 -DNOERRCHK -USS_M_PROTO_REGION -DDEBUGP -DCM_PASN_DBG -DREL_850 \
		 -DSS_FLOAT -DUSE_PURE -DPURE -DSLES9_PLUS -DTA_NEW -DSI_NEW -DRGR_SI_SCH \
		 -DVE_SRB2_SUPPORT -DNB_SB_SCTP -UCTF_VER3 -USSI_DEBUG_LEVEL1 \
		 -DMME_LDBAL -DSZ_ENB -DEGTP_U_REL_9 -DLEGV2 -DxSS_DIAG -DLCEGT \
		 -USS_MULTICORE_SUPPORT -USS_M_PROTO_REGION -USS_LOCKLESS_MEMORY \
		 -DTENB_RTLIN_CHANGES -DCZTV1 -DS1AP_REL9A6 -DSZTV3 -DSS_THR_REG_MAP \
		 -DREVIEW -DTENB_DISABLE_DL_ZBC  -DCZTV1 -DS1AP_REL9A6 -DLWLCNBU \
		 -DSZTV3 -UTUCL_TTI_RCV -USS_LICENSE_CHECK -DCM_NAS_SEC $(RLOG_OPTS) \
		 $(MTOPTS) -DS1SIMAPP -DMULTI_ENB_SUPPORT_ENABLE -DHI_NO_CHK_RES -DIPV6_SUPPORTED

# All TUCL product options
LHIOPTS=-DLCHIMILHI -DSM -DLCLHI -DxLOCAL_INTF
HIOPTS= $(HITOPTS) $(LHIOPTS) -DHI -DLCHIMILHI -DSM -DLCSMHIMILHI \
		  -DxLCHIUIHIT -DEG

# SM : Stack Manager defines
SMOPTS= -DSM_DEBUG -DRLOG_ENABLE_TEXT_LOGGING -DSM_LOGS -DLWLCSMMILFW

#Stack Manager Options
SMOPTS_ENBAPP= -DLCSMMILCL -DLCCLMILCL

# RLOG defines
CCRLOGOPTS= $(ENV) -DSS_LINUX -UUSE_RLOG_DATA_TYPES \
				-DRLOG_ENABLE_TEXT_LOGGING -DRLOG_ALLOW_CONSOLE_LOGS -DCMFILE_REORG_1 -DS1SIMAPP

#All S1AP product options
SZTOPTS=-DSZ -DUZ -DLCUZLISZT -DLWLCUZLISZT -DLCSZUISZT -DLCSZT -DPTSZUISZT\
        -US1AP_REL851 -DLSZV1 -DSZTV1 -DSZTV2 -DSZTV3 -DCM_PASN_CRIT_HANDL
LSZOPTS=-DLCLSZ -DLCSCT -DSM -DSZ -DLCSMSZMILSZ  -DLCSZMILSZ
SZOPTS=-DSZ $(SZTOPTS) $(LSZOPTS) $(SCTOPTS) -DLCSZMILSZ -DSM \
	  -DSZ_ENB -DSZ_DYNAMIC_PEER -DSZ_USTA

# All LTE EGTP-U product options
EGTOPTS=-DEG -DLCEGT -DLCEGUIEGT -DCCPU_OPT -DLCEULIEGT
LEGOPTS=-DLCSMMILEG -DLCLEG -DSM -DEG -DLCEGMILEG -DLCSMEGMILEG
EGOPTS=-DEG $(EGTOPTS) $(LEGOPTS) -DEG_DEBUG -DLCEGLIHIT -DxBRCM_ZBC -DEG_IPV6_SUPPORTED


#All SCTP product options
LSBOPTS=-DLCLSB -DSM -DSB -DLSB4  -DLSB8 -DHI_REL_1_4
SCTOPTS=-DSB  -DLCSBUISCT -DLCSZLISCT -DLCCZLISCT
HITOPTS=-DLCSBLIHIT -DLCHIUIHIT -DHI_REL_1_4 -DLCEGLIHIT
SBOPTS = $(LSBOPTS) $(HITOPTS) $(SCTOPTS) -DLCSBMILSB -DLCSMSBMILSB\
         -DSB_CHECKSUM -DSB_CHECKSUM_CRC

#All TUCL product options
STOPTS=-DENB
LHIOPTS=-DLCHIMILHI -DSM -DLCLHI
HIOPTS= $(LHIOPTS) $(HITOPTS) -DHI -DLCHIMILHI -DSM -DLCSMHIMILHI -DEG

LNBOPTS=-DNB -DSM -ULCLNB -ULCSMMILNB -ULCNBMILNB
NBOPTS=-DNB -DLCCZT $(LNBOPTS) $(SZTOPTS) -DNB_LOGS -DRLOG_ENABLE_TEXT_LOGGING
# macros for compile and link options

LNXENV=-DSUNOS -DSS -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT \
		 -D__EXTENSIONS__ -DDEBUGNOEXIT

#NB defines
CCLNXNBOPTS= $(LNXENV) $(NBOPTS) $(STOPTS) $(CMOPTS)

# Timer Module Options
CCTMROPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) $(MTOPTS)

#-----------------------------------------------------------------------
# macros for sw and include directories
#

# common include files
CM_INC=\
   $(SSI_DIR)/envdep.h         $(SSI_DIR)/envind.h         \
   $(SSI_DIR)/envopt.h                                     \
   $(SSI_DIR)/gen.h            $(SSI_DIR)/gen.x            \
   $(SSI_DIR)/cm_hash.x        $(SSI_DIR)/cm_hash.h        \
   $(SSI_DIR)/cm_inet.h        $(SSI_DIR)/cm_inet.x        \
   $(SSI_DIR)/cm_llist.h       $(SSI_DIR)/cm_llist.x       \
   $(SSI_DIR)/cm_tpt.h         $(SSI_DIR)/cm_tpt.x         \
   $(SSI_DIR)/cm_dns.h         $(SSI_DIR)/cm_dns.x         \
   $(SSI_DIR)/cm5.h            $(SSI_DIR)/cm5.x            \
   $(SSI_DIR)/cm_err.h         $(SSI_DIR)/cm_lib.x         \
   $(SSI_DIR)/cm_mblk.h        $(SSI_DIR)/cm_mblk.x        \
   $(SSI_DIR)/cm_tkns.h        $(SSI_DIR)/cm_tkns.x        \
   $(SSI_DIR)/cm_hash.h        $(SSI_DIR)/cm_hash.x        \
   $(SSI_DIR)/cm_gen.h         $(SSI_DIR)/cm_gen.x         \
   $(SSI_DIR)/ssi.h            $(SSI_DIR)/ssi.x            \
   $(SSI_DIR)/cm_mem.h         $(SSI_DIR)/cm_mem.x         \
	$(FW_CM_DIR)/lfw.h \
	$(CM_DIR)/egt.h            $(CM_DIR)/egt.x        \
	$(CM_DIR)/hit.h            $(CM_DIR)/hit.x        \
	$(CM_DIR)/szt.h            $(CM_DIR)/szt.x        \
	$(CM_DIR)/leg.h            $(CM_DIR)/leg.x        \
	$(CM_DIR)/lhi.h            $(CM_DIR)/lhi.x        \
	$(CM_DIR)/sct.h            $(CM_DIR)/szt_asn.h    \
	$(CM_DIR)/lsb.h            $(CM_DIR)/lsb.x        \
	$(CM_DIR)/lsz.h            $(CM_DIR)/lsz.x        \
	$(CM_DIR)/lcz.h            $(CM_DIR)/lcz.x        \
   $(CM_DIR)/szt_asn.h        $(CM_DIR)/szt_asn.x        \
	$(RLOG_DIR)/rl_common.h     $(RLOG_DIR)/rl_interface.h \
        $(CM_DIR)/cm_os.h     $(CM_DIR)/cm_os.x

#-----------------------------------------------------------------------
# macros for compile and link options
ENV=-DSUNOS -DSS -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT \
    -D__EXTENSIONS__

# compiler:
	CC=gcc -g3 -fPIC -m64 -DALIGN_64BIT -DBIT_64
	LL=gcc -g3 -m64

#Archive library command
AR=ar

# Copy Command
CP=cp

#-----------------------------------------------------------------------
# Compiler options
#
# Compiler options for enbApp
LNXCOPTS=" -pipe -pedantic -Wall -Wno-comment -Wshadow -Wcast-qual \
			 -Wstrict-prototypes -Wmissing-prototypes -fno-strict-aliasing \
			 -fsigned-char -Wno-variadic-macros --std=c99"

# Compiler options for Stack layers
COPTS=-pipe -pedantic -Wall -Wunused -Wno-comment -Wshadow \
		-Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
		-fno-strict-aliasing -Wno-variadic-macros --std=c99

# Compiler options for Application modules(ueApp, TFW, timer)
COPTS_APP=-pipe -pedantic -Wall -Wunused -Wno-comment -Wshadow \
			 -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
			 -fno-strict-aliasing -Wno-variadic-macros --std=c99

# linker options:
LOPTS=-lpthread -ldl

LNXLOPTS= -ldl -lpthread -lnsl -lrt -lm -export-dynamic

# include options:
IOPTS=-I$(SSI_DIR) -I$(FW_CM_DIR) -I$(FW_APP_DIR) -I$(UE_APP_DIR) \
		-I$(RLOG_DIR) -I$(HI_DIR) -I$(SM_DIR) -I$(UE_SEC_DIR) -I$(TIMER_DIR) -I$(CM_DIR)

LNXIOPTS= -I$(SSI_DIR) -I$(EG_DIR) -I$(SZ_DIR) -I$(FW_CM_DIR) -I$(SM_DIR) -I$(RLOG_DIR) -I$(CM_DIR)

# MTSS/SSI defines
CCMTOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) $(MTOPTS) -DLOCAL_INTF \
			-DIPV4_OPTS_SUPPORTED

# Common defines
CCCMOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) \
         $(HITOPTS) $(LHIOPTS)

# TUCL(HI) defines
CCHIOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) $(HIOPTS)

#HI defines
CCLNXHIOPTS= $(LNXENV) $(HIOPTS)  $(STOPTS) $(CMOPTS)

#SZ defines
CCLNXSZOPTS= $(LNXENV) $(SZOPTS)  $(STOPTS) $(CMOPTS)

#SB defines
CCLNXSBOPTS= $(LNXENV) $(SBOPTS)  $(STOPTS) $(CMOPTS)

#SZ defines
CCLNXEGOPTS= $(LNXENV) $(EGOPTS)  $(STOPTS) $(CMOPTS)

# Stack Manager defines
CCSMOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) $(SMOPTS) \
			-DFW_LOGS -DRLOG_ENABLE_TEXT_LOGGING

# Common Interface defines
CCNACMOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) $(SMOPTS) -DLWLCLNA -DLWLCLXN \
			  -DLWLCXNT

# FW defines
CCFWOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) -DLWLCFWLIUET -DLWLCFWLINBT \
			-DFW_LOGS -DRLOG_ENABLE_TEXT_LOGGING

# UE defines
CCUEOPTS=$(DEBUGPOPTS) $(ENV) $(CMOPTS) -DLWLCFWLIUET -DLWLCFWLINBT \
         -DUE_LOGS -DRLOG_ENABLE_TEXT_LOGGING -DSQN_ALGO_TS33102 -UUEHASHLIST -ULTE_UE_NAS_SEC

# SM defines
CCLNXSMOPTS= $(LNXENV) $(SMOPTS_ENBAPP) $(CMOPTS_ENBAPP) $(STOPTS)

all: BUILD TARGETS


BUILD:
	@echo "Setup..."
	$(Q)rsync -a $(CM_DIR)/envopt_s1sim.h $(CM_DIR)/envopt.h

TARGETS:
	@echo "Compiling SSI..."
	@$(MAKE) -f ssi.mak $(OBJ_SSI)/ssi COPTS='$(COPTS)' \
	LOPTS='$(LOPTS)' POPTS='$(CCLNXSBOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(SSI_DIR)' OUT_DIR='$(OBJ_SSI)' OBJ='$(OBJ)' CC='$(CC)' \
	LL='$(LL)' CM_INC='$(CM_INC)' LIB_DIR='$(LIB_DIR)'

	@echo "Compiling TUCL..."
	@$(MAKE) -f hi.mak $(OBJ_TUCL)/hiprepro COPTS='$(COPTS)' \
	AR='$(AR)' LOPTS='$(LOPTS)' POPTS='$(CCLNXHIOPTS)' IOPTS='$(LNXIOPTS)' \
	VS_DIR='$(HI_DIR)' IN_DIR='$(HI_DIR)' OUT_DIR='$(OBJ_TUCL)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

	@echo "Compiling S1AP..."
	@$(MAKE) -f sz.mak $(OBJ_S1AP)/szprepro COPTS='$(COPTS)' \
	AR='$(AR)' LOPTS='$(LOPTS)' POPTS='$(CCLNXSZOPTS)' IOPTS='$(LNXIOPTS)' \
	VS_DIR='$(SZ_DIR)' IN_DIR='$(SZ_DIR)' OUT_DIR='$(OBJ_S1AP)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

	@echo "Compiling SCTP..."
	@$(MAKE) -f sb.mak $(OBJ_SCTP)/sbprepro COPTS='$(COPTS)' \
	AR='$(AR)' LOPTS='$(LOPTS)' POPTS='$(CCLNXSBOPTS)' IOPTS='$(LNXIOPTS)' \
	VS_DIR='$(SB_DIR)' IN_DIR='$(SB_DIR)' OUT_DIR='$(OBJ_SCTP)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

	@echo "Compiling eGTP..."
	@$(MAKE) -f eg.mak $(OBJ_EGTP)/egtp COPTS='$(COPTS)' \
	AR='$(AR)' LOPTS='$(LOPTS)' POPTS='$(CCLNXEGOPTS)' IOPTS='$(LNXIOPTS)' \
	VS_DIR='$(EG_DIR)' IN_DIR='$(EG_DIR)' OUT_DIR='$(OBJ_EGTP)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' LIB_DIR='$(LIB_DIR)' SRC="c"

	@echo "Compiling Stack Manager..."
	@$(MAKE) -f sm.mak $(OBJ_DIR)/sm COPTS='$(COPTS)' LOPTS='$(LOPTS)' \
	POPTS='$(CCSMOPTS)' IOPTS='$(IOPTS)' IN_DIR='$(SM_DIR)' \
	OUT_DIR='$(OBJ_DIR)' OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

	@echo "Compiling rlog Framework..."
	@$(MAKE) -f rlog.mak $(OBJ_RLOG)/rlog COPTS='$(COPTS)' \
	LOPTS='$(LOPTS)' POPTS='$(CCRLOGOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(RLOG_DIR)' OUT_DIR='$(OBJ_RLOG)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' LIB_DIR='$(LIB_DIR)'

	@echo "Compiling Security related Files..."
	@$(MAKE) -f ue_sec.mak $(OBJ_DIR)/libuesec.a COPTS='$(COPTS)' \
	LOPTS='$(LOPTS)' POPTS='$(CCFWOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(UE_SEC_DIR)' OUT_DIR='$(OBJ_DIR)' OBJ='$(OBJ)' CC='$(CC)' \
	LL='$(LL)' CM_INC='$(CM_INC)' LIB_DIR='$(LIB_DIR)'

	@echo "Compiling Common Files..."
	@$(MAKE) -f cm.mak $(OBJ_CM)/cm_bld COPTS='$(COPTS)' SZ_DIR='$(SZ_DIR)' \
	EG_DIR='$(EG_DIR)' LOPTS='$(LOPTS)' POPTS='$(CCFWOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(FW_CM_DIR)' INF_DIR='$(CM_DIR)' OUT_DIR='$(OBJ_CM)' OBJ='$(OBJ)' CC='$(CC)' \
	LL='$(LL)' CM_INC='$(CM_INC)'

	@echo "Compiling enbApp..."
	@$(MAKE) -f nb.mak $(OBJ_DIR)/libnb.a COPTS=$(LNXCOPTS)  AR='$(AR)' \
	LOPTS='$(LOPTS)' POPTS='$(CCLNXNBOPTS)' SMPOPTS='$(CCLNXSMOPTS)' \
	HIOPTS='$(HIOPTS)' SBOPTS='$(SBOPTS)' IOPTS='$(LNXIOPTS)' \
	VS_DIR='$(NB_DIR)' IN_DIR='$(NB_DIR)' OUT_DIR='$(OBJ_DIR)' OBJ='$(OBJ)' \
	CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

	@echo "Compiling UE Application..."
	@$(MAKE) -f ue_app.mak $(OBJ_DIR)/ueApp COPTS='$(COPTS_APP)' \
	LOPTS='$(LOPTS)' POPTS='$(CCUEOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(UE_APP_DIR)' OUT_DIR='$(OBJ_DIR)' OBJ='$(OBJ)' CC='$(CC)' \
	LL='$(LL)' CM_INC='$(CM_INC)'

	@echo "Compiling FW Application..."
	@$(MAKE) -f fw_app.mak $(OBJ_DIR)/fw_app COPTS='$(COPTS_APP)' \
	LOPTS='$(LOPTS)' POPTS='$(CCFWOPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(FW_APP_DIR)' OUT_DIR='$(OBJ_DIR)' OBJ='$(OBJ)' CC='$(CC)' \
	LL='$(LL)' CM_INC='$(CM_INC)'

	@echo "Compiling TIMER MODULE..."
	@$(MAKE) -f timer.mak $(OBJ_TIMER)/timer COPTS='$(COPTS_APP)' \
	LOPTS='$(LOPTS)' POPTS='$(CCTMROPTS)' IOPTS='$(IOPTS)' \
	IN_DIR='$(TIMER_DIR)' OUT_DIR='$(OBJ_TIMER)' LIB_DIR='$(LIB_DIR)' \
	OBJ='$(OBJ)' CC='$(CC)' LL='$(LL)' CM_INC='$(CM_INC)'

	@echo "Linking Objects, Creating Shared Library"
	$(CC) $(LIBPATH) -shared $(OBJ_DIR)/*.o $(OBJ_CM)/*.o $(OBJ_TUCL)/*.o \
		$(OBJ_S1AP)/*.o $(OBJ_SCTP)/*.o $(LIB_DIR)/*.a $(PCAP_ARC) $(LOPTS) \
		-o $(LIB_DIR)/$(LIBNAME)

clean:
	\rm -f $(LIB_DIR)/$(LIBNAME) $(BIN_DIR)/*.cfg $(OBJ_DIR)/*.o  \
		$(OBJ_DIR)/*~ $(OBJ_DIR)/*.bak $(OBJ_DIR)/*.err

cleanall:
	\rm -f $(LIB_DIR)/$(LIBNAME) $(BIN_DIR)/*.so $(BIN_DIR)/*.cfg \
		$(OBJ_DIR)/*.o $(OBJ_DIR)/*.a $(OBJ_TUCL)/*.o $(OBJ_S1AP)/*.o \
		$(OBJ_SCTP)/*.o $(OBJ_SSI)/*.o $(OBJ_CM)/*.o \
		$(OBJ_RLOG)/*.o $(BIN_DIR)/core $(OBJ_DIR)/*~ $(OBJ_DIR)/*.bak \
		$(OBJ_EGTP)/*.o $(OBJ_DIR)/*.err $(LIBNAME) $(LIB_DIR)/*.a \
		$(OBJ_TIMER)/*.o
