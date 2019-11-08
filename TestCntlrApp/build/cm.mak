# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

#-------------------------------------------------------------#
# Makefile for common & interface files
#-------------------------------------------------------------#

CCrmFLAGS=-DLRM_LWLC -DRMU_LWLC -URMU_NPLC -DRGM_LWLC -DLWLCSMRMMILRM -DLCSMRMMILRM -DSM
CCnlFlags=-DLWLCSMSONILNL -DNLU_LWLC -DLCSMSONILNL -DNLU_TC -DTCSMSONILNL -DNL
ifeq (${BLDENV}, lnx_e2e_ms)
CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT  -DRGR_V1 -DLSZV1 $(CCrmFLAGS)  #<---Insert cm specific defines here
else
ifeq (${BLDENV},lnx_ms_withoutdiag)
CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT  -DRGR_V1 -DLSZV1 $(CCrmFLAGS)  #<---Insert cm specific defines here
else
#CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT  -DRGR_V1 -DLSZV1 -DVE_SB_SCTP $(CCrmFLAGS)#<---Insert cm specific defines here
CCcmFLAGS=-DVE_SB_SCTP $(CCrmFLAGS)#<---Insert cm specific defines here
endif
endif

ifeq (${BLDENV}, lnx_e2e_ms)
CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UWR_SM_LOG_TO_FILE -DRGR_SI_SCH -UTA_NEW -DSI_NEW -DCZ $(CCrmFLAGS) $(CCnlFlags)
else
ifeq (${BLDENV},lnx_ms_withoutdiag)
CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UWR_SM_LOG_TO_FILE -DRGR_SI_SCH -UTA_NEW -DSI_NEW -DCZ $(CCrmFLAGS) $(CCnlFlags)
else
CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UVE_SM_LOG_TO_FILE -DTA_NEW -DSI_NEW -DCZ $(CCrmFLAGS) $(CCnlFlags)
endif
endif

EGTOPTS=-DEG -DLCEGT -DLCEGUIEGT -DEGTP_U
LEGOPTS=-DLCSMMILEG -DLCLEG -DSM -DEG -DEGTP_U
LHIOPTS=-DLCHIMILHI -DSM -DLCLHI
HITOPTS=-DLCHIT -DLCSBLIHIT -DLCHIUIHIT -DHI_REL_1_4 -DLCEGLIHIT
SCTOPTS=-DLCSCT
LRGOPTS= -DLCSMMILRG -DLCLRG -DSM -DRG -DLCRGMILRG
LSBOPTS=-DLCLSB -DSM -DSB -DLSB4  -DLSB8 -DHI_REL_1_4
LSZOPTS=-DLCLSZ -DLCSCT -DSM -DSZ -DLCSMSZMILSZ  -DLCSZMILSZ -DSZ_ENB
SZTOPTS=-DSZ -DUZ -DLCUZLISZT -DLWLCUZLISZT -DLCSZUISZT -DLCSZT -DPTSZUISZT
LCZOPTS=-DLCLCZ -DLCSCT -DSM -DCZ -DLCSMCZMILCZ  -DLCCZMILCZ
CZTOPTS=-DCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DPTCZUICZT
RGROPTS=-DRG -DLCWRLIRGR -DLCRGR -DLWLCWRLIRGR -DLCRGUIRGR
CTFOPTS=-DLCCTF -DWR -DLCWRLICTF -DLCYSUICTF
LNHOPTS=-DNH -DSM -DLCLNH -DLCSMMILNH -DLCSMNHMILNH -DLCNHMILNH
NHUOPTS=-DLCNHU -DWR -DNX -DLCWRLINHU -DLCNXLINHU -DLCNHUINHU
LWROPTS=-DWR -DSM -DLCLWR -ULCSMMILWR -ULCWRMILWR -DWR_RELAY -DEU_DAT_APP
LPJOPTS=-DPJ -DSM -DLCLPJ -DLCSMMILPJ -DLCPJMILPJ -DKW_PDCP
LKWOPTS=-DKW -DSM -DLCLKW -DLCSMMILKW -DLCKWMILKW -DKW_PDCP
PJUVEOPTS=-DPJ -DLCPJU -DWR -DNX -DNH -DLCWRLIPJU -DLCPJUIPJU -DLCNHLIPJU
CKWOPTS=-DLCNHLICKW -DLCCKW -DLCKWUICKW -DKW -DNH
CPJOPTS=-DPJ -DLCCPJ -DNH -DLCNHLICPJ -DLCPJUICPJ
CRGOPTS= -DLCNHLICRG -DLCCRG -DLCRGUICRG -DRG
KWUOPTS=-DKW -DNH -DLCKWUIKWU -DLCKWU -DLCNHLIKWU -DCCPU_OPT
RGUOPTS= -DRG -DKW -DLCKWLIRGU -DLCRGU -DLCRGUIRGU -DCCPU_OPT
TFUOPTS= -DTFU_VER_2 -DLCTFU
LYSOPTS=-DYS -DLCLYS -DLCSMMILYS -DLCYSMILYS

LYSOPTS=-DYS -DLCLYS -DLCSMMILYS -DLCYSMILYS
EGT_INC= \
    $(EG_DIR)/eg.h $(EG_DIR)/eg_util.h $(EG_DIR)/eg_util.x

LSZ_INC= \
    $(SZ_DIR)/sz.h $(SZ_DIR)/sz_err.h

EGALL_INC=$(EGT_INC) $(CM_INC)

#-------------------------------------------------------------#
# Obj macros
#-------------------------------------------------------------#
cmOBJS=\
		 $(OUT_DIR)/lhi.$(OBJ)\
		 $(OUT_DIR)/hit.$(OBJ)\
		 $(OUT_DIR)/lsb.$(OBJ)\
		 $(OUT_DIR)/sct.$(OBJ)\
		 $(OUT_DIR)/lsz.$(OBJ)\
		 $(OUT_DIR)/szt.$(OBJ)\
		 $(OUT_DIR)/szt_pk.$(OBJ)\
		 $(OUT_DIR)/szt_3gpk.$(OBJ)\
		 $(OUT_DIR)/szt_unpk.$(OBJ)\
		 $(OUT_DIR)/szt_3gunpk.$(OBJ)\
		 $(OUT_DIR)/leg.$(OBJ)\
		 $(OUT_DIR)/egt.$(OBJ)\
		 $(OUT_DIR)/nbt.$(OBJ)\
		 $(OUT_DIR)/nbu.$(OBJ) \
		 $(OUT_DIR)/uet.$(OBJ) \
		 $(OUT_DIR)/cm_pasn1.$(OBJ) \
		 $(OUT_DIR)/cm_pasn2.$(OBJ) \
		 $(OUT_DIR)/cm_pasn3.$(OBJ) \
		 $(OUT_DIR)/cm_pasn4.$(OBJ) \
		 $(OUT_DIR)/cm_os.$(OBJ)

ALL_INC=$(CM_INC)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
# Compiler macros
#-------------------------------------------------------------#
$(OUT_DIR)/lhi.$(OBJ): $(INF_DIR)/lhi.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/lhi.o $(COPTS) $(IOPTS) $(POPTS) $(LHIOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/lhi.c

$(OUT_DIR)/hit.$(OBJ): $(INF_DIR)/hit.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/hit.o $(COPTS) $(IOPTS) $(POPTS) $(HITOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/hit.c

$(OUT_DIR)/lsb.$(OBJ): $(INF_DIR)/lsb.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/lsb.o $(COPTS) $(IOPTS) $(POPTS) $(LSBOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/lsb.c

$(OUT_DIR)/sct.$(OBJ): $(INF_DIR)/sct.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/sct.o $(COPTS) $(IOPTS) $(POPTS) $(SCTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/sct.c

$(OUT_DIR)/lsz.$(OBJ): $(INF_DIR)/lsz.c $(CM_INC) $(LSZ_INC)
	$(CC) -c -o $(OUT_DIR)/lsz.o $(COPTS) $(IOPTS) $(POPTS) $(LSZOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/lsz.c

$(OUT_DIR)/egt.$(OBJ): $(INF_DIR)/egt.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/egt.o $(COPTS) $(IOPTS) $(POPTS) $(EGTOPTS) \
	-I$(EG_DIR) $(CCcmFLAGS) $(INF_DIR)/egt.c

$(OUT_DIR)/leg.$(OBJ): $(INF_DIR)/leg.c $(CM_INC) $(EGT_INC)
	$(CC) -c -o $(OUT_DIR)/leg.o $(COPTS) $(IOPTS) $(POPTS) $(LEGOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/leg.c

$(OUT_DIR)/szt.$(OBJ): $(INF_DIR)/szt.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/szt.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/szt.c

$(OUT_DIR)/szt_pk.$(OBJ): $(INF_DIR)/szt_pk.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/szt_pk.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/szt_pk.c

$(OUT_DIR)/szt_3gpk.$(OBJ): $(INF_DIR)/szt_3gpk.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/szt_3gpk.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/szt_3gpk.c

$(OUT_DIR)/szt_unpk.$(OBJ): $(INF_DIR)/szt_unpk.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/szt_unpk.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/szt_unpk.c

$(OUT_DIR)/szt_3gunpk.$(OBJ): $(INF_DIR)/szt_3gunpk.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/szt_3gunpk.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(INF_DIR)/szt_3gunpk.c

$(OUT_DIR)/nbu.$(OBJ): $(IN_DIR)/nbu.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/nbu.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(IN_DIR)/nbu.c

$(OUT_DIR)/nbt.$(OBJ): $(IN_DIR)/nbt.c $(CM_INC)
	$(CC) -c -o $(OUT_DIR)/nbt.o $(COPTS) $(IOPTS) $(POPTS) $(SZTOPTS) \
	$(CCcmFLAGS) $(IN_DIR)/nbt.c

$(OUT_DIR)/uet.$(OBJ): $(IN_DIR)/uet.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/uet.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/uet.c

$(OUT_DIR)/cm_pasn1.$(OBJ): $(IN_DIR)/cm_pasn1.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_pasn1.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_pasn1.c

$(OUT_DIR)/cm_pasn2.$(OBJ): $(IN_DIR)/cm_pasn2.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_pasn2.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_pasn2.c

$(OUT_DIR)/cm_pasn3.$(OBJ): $(IN_DIR)/cm_pasn3.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_pasn3.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_pasn3.c

$(OUT_DIR)/cm_pasn4.$(OBJ): $(IN_DIR)/cm_pasn4.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_pasn4.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_pasn4.c

$(OUT_DIR)/cm_os.$(OBJ): $(IN_DIR)/cm_os.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_os.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_os.c
#-------------------------------------------------------------#
# Compile rule
#-------------------------------------------------------------#
$(OUT_DIR)/cm_bld:$(cmOBJS)

#-------------------------------------------------------------#
# Clean macros
#-------------------------------------------------------------#
clean:
	\rm -f $(fwAppOBJS)
