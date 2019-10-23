#
#
##--------------------------------------------------------------#
##Makefile for product NB
##--------------------------------------------------------------#
#
##--------------------------------------------------------------#
##User macros (to be modified)
#--------------------------------------------------------------#

#RrmFlags=-DRM_INTF -DRMU_LWLC -DRM_NPLC -DLWLCSMRMMILRM -UTCSMRMMILRM -DLCSMRMMILRM -DPTSMMILRM -LRM_NPLC

#SonFlags=-DNLU_LWLC -DNLU_TC -DLWLCSMSONILNL -DTCSMSONILNL -DLCSMSONILNL
COPTS_NO_WARN=-g -O3 -pipe -pedantic -W -Wno-comment -Wshadow -Wcast-qual -fno-strict-aliasing -fsigned-char --std=c99 -march=mips32r2 -mtune=mips32r2 -mips32r2

CCnbFLAGS=-DNB_RELAY -DxEU_DAT_APP -DEGTP_U -DUZ -DEU -DDG  -DSS_MT_TMR -DNB

#CCsmFLAGS=-DHI -DSB -DEG -DWR -DSZ

# Product sources-------------------------------------------------------
nbSRCS= \
    $(IN_DIR)/nb_smm_init.$(SRC)\
    $(IN_DIR)/nb_traffic_handler.$(SRC)\
    $(IN_DIR)/nb_lnb.$(SRC) \
    $(IN_DIR)/nb_ui.$(SRC) \
    $(IN_DIR)/nb_ue_msg_hndlr.$(SRC) \
    $(IN_DIR)/nb_s1ap_hndlr.$(SRC) \
    $(IN_DIR)/nb_lmm.$(SRC) \
    $(IN_DIR)/nb_smm_s1ap.$(SRC) \
    $(IN_DIR)/nb_smm_sctp.$(SRC) \
    $(IN_DIR)/nb_smm_tucl.$(SRC) \
    $(IN_DIR)/nb_smm_enbapp.$(SRC) \
    $(IN_DIR)/nb_ifm_s1ap.$(SRC) \
    $(IN_DIR)/nb_ifm_egtp.$(SRC) \
    $(IN_DIR)/nb_tmr.$(SRC) \
    $(IN_DIR)/nb_dam.$(SRC) \
    $(IN_DIR)/nb_dam_ex_ms.$(SRC) \
    $(IN_DIR)/nb_dam_ifm_app.$(SRC) \
    $(IN_DIR)/nb_ifm_dam.$(SRC) \
    $(IN_DIR)/nb_dam_tmr.$(SRC) \
    $(IN_DIR)/nb_ptmi.$(SRC) \
    $(IN_DIR)/nb_ex_ms.$(SRC) \
    $(IN_DIR)/nb_ifm_dam_utils.$(SRC) \
	 $(IN_DIR)/sm_bdy1.$(SRC) \
	 $(IN_DIR)/sm_ex_ms.$(SRC) \
    $(IN_DIR)/nb.$(SRC) \
    $(IN_DIR)/nb_enb_db.$(SRC)

# Product objects-------------------------------------------------------
nbOBJS= \
    $(OUT_DIR)/nb_utils.$(OBJ) \
    $(OUT_DIR)/nb_ui.$(OBJ) \
    $(OUT_DIR)/nb_ue_msg_hndlr.$(OBJ) \
    $(OUT_DIR)/nb_s1ap_hndlr.$(OBJ) \
    $(OUT_DIR)/nb_smm_sctp.$(OBJ) \
    $(OUT_DIR)/nb_smm_init.$(OBJ) \
    $(OUT_DIR)/nb_traffic_handler.$(OBJ) \
    $(OUT_DIR)/nb_smm_s1ap.$(OBJ) \
    $(OUT_DIR)/nb.$(OBJ) \
    $(OUT_DIR)/nb_ifm_s1ap.$(OBJ) \
    $(OUT_DIR)/nb_ifm_egtp.$(OBJ) \
    $(OUT_DIR)/nb_ex_ms.$(OBJ) \
    $(OUT_DIR)/nb.$(OBJ) \
    $(OUT_DIR)/nb_lnb.$(OBJ) \
    $(OUT_DIR)/nb_lmm.$(OBJ) \
    $(OUT_DIR)/nb_smm_tucl.$(OBJ) \
    $(OUT_DIR)/nb_smm_enbapp.$(OBJ) \
    $(OUT_DIR)/nb_tmr.$(OBJ) \
    $(OUT_DIR)/nb_dam.$(OBJ) \
    $(OUT_DIR)/nb_dam_ex_ms.$(OBJ) \
    $(OUT_DIR)/nb_dam_ifm_app.$(OBJ) \
    $(OUT_DIR)/nb_ifm_dam.$(OBJ) \
    $(OUT_DIR)/nb_dam_tmr.$(OBJ) \
    $(OUT_DIR)/nb_ifm_dam_utils.$(OBJ) \
    $(OUT_DIR)/nb_ptmi.$(OBJ) \
    $(OUT_DIR)/sm_bdy1.$(OBJ) \
	 $(OUT_DIR)/sm_ex_ms.$(OBJ) \
	 $(OUT_DIR)/nb_smm_egtp.$(OBJ) \
    $(OUT_DIR)/nb_enb_db.$(OBJ)

NBCM_INC=$(VS_DIR)/nb.h

CM_DIR=../src/fw_cm

ALL_INC=$(NBCM_INC) $(CM_INC)

SS_DIR=../

#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros
#-------------------------------------------------------------#
$(OUT_DIR)/nb_lmm.$(OBJ): $(IN_DIR)/nb_lmm.$(SRC) $(ALL_INC)
	$(CC) -c -o$(OUT_DIR)/nb_lmm.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_lmm.$(SRC)

$(OUT_DIR)/nb.$(OBJ): $(IN_DIR)/nb.$(SRC) $(ALL_INC)
	$(CC) -c -o$(OUT_DIR)/nb.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb.$(SRC)

$(OUT_DIR)/nb_utils.$(OBJ): $(IN_DIR)/nb_utils.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_utils.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_utils.$(SRC)

$(OUT_DIR)/nb_s1ap_hndlr.$(OBJ): $(IN_DIR)/nb_s1ap_hndlr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_s1ap_hndlr.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_s1ap_hndlr.$(SRC)

$(OUT_DIR)/nb_ui.$(OBJ): $(IN_DIR)/nb_ui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ui.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_ui.$(SRC)


$(OUT_DIR)/nb_ue_msg_hndlr.$(OBJ): $(IN_DIR)/nb_ue_msg_hndlr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ue_msg_hndlr.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_ue_msg_hndlr.$(SRC)

$(OUT_DIR)/nb_smm_init.$(OBJ): $(IN_DIR)/nb_smm_init.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_smm_init.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_smm_init.$(SRC)

$(OUT_DIR)/nb_traffic_handler.$(OBJ): $(IN_DIR)/nb_traffic_handler.$(SRC) \
	$(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_traffic_handler.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_traffic_handler.$(SRC)

$(OUT_DIR)/nb_smm_s1ap.$(OBJ): $(IN_DIR)/nb_smm_s1ap.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_smm_s1ap.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) \
	$(POPTS) -I$(CM_DIR) -I$(VS_DIR) $(CCnbFLAGS) -DLCSMMILSZ -DLCLSZ -DSZ_ENB \
	$(IN_DIR)/nb_smm_s1ap.$(SRC)

$(OUT_DIR)/nb_smm_sctp.$(OBJ): $(IN_DIR)/nb_smm_sctp.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_smm_sctp.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) \
	$(POPTS) -I$(CM_DIR) -I$(VS_DIR) $(CCnbFLAGS) -DLCSMSBMILSB -DLCLSB -DLSB4 \
	-DLSB8 $(IN_DIR)/nb_smm_sctp.$(SRC)

$(OUT_DIR)/nb_smm_tucl.$(OBJ): $(IN_DIR)/nb_smm_tucl.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_smm_tucl.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) \
	$(POPTS) -I$(CM_DIR) -I$(VS_DIR) $(CCnbFLAGS) -DLCSMHIMILHI \
	$(IN_DIR)/nb_smm_tucl.$(SRC)

$(OUT_DIR)/nb_smm_egtp.$(OBJ): $(IN_DIR)/nb_smm_egtp.$(SRC) $(ALL_INC)
	$(CC) -c -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DLCSMMILEG \
		-DLCLEG $(IN_DIR)/nb_smm_egtp.$(SRC) -o $(OUT_DIR)/nb_smm_egtp.$(OBJ)

$(OUT_DIR)/nb_smm_enbapp.$(OBJ): $(IN_DIR)/nb_smm_enbapp.$(SRC) $(ALL_INC)
	$(CC) -c -o	$(OUT_DIR)/nb_smm_enbapp.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) \
	$(POPTS) -I$(CM_DIR) -I$(VS_DIR) $(CCnbFLAGS) -DLWLCSMMILNB  -DLCSMMILNB \
	-DLWLCSNB -DLWLCNBMILNB -DSM -UPTSMMILNB $(IN_DIR)/nb_smm_enbapp.$(SRC)

$(OUT_DIR)/nb_ifm_s1ap.$(OBJ): $(IN_DIR)/nb_ifm_s1ap.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ifm_s1ap.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_ifm_s1ap.$(SRC)


$(OUT_DIR)/nb_ifm_egtp.$(OBJ): $(IN_DIR)/nb_ifm_egtp.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ifm_egtp.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) \
	-I$(VS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) \
	$(IN_DIR)/nb_ifm_egtp.$(SRC)

$(OUT_DIR)/nb_tmr.$(OBJ): $(IN_DIR)/nb_tmr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_tmr.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_tmr.$(SRC)


$(OUT_DIR)/nb_dam_ifm_app.$(OBJ): $(IN_DIR)/nb_dam_ifm_app.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_dam_ifm_app.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_dam_ifm_app.$(SRC)

$(OUT_DIR)/nb_ifm_dam.$(OBJ): $(IN_DIR)/nb_ifm_dam.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ifm_dam.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_ifm_dam.$(SRC)


$(OUT_DIR)/nb_dam_tmr.$(OBJ): $(IN_DIR)/nb_dam_tmr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_dam_tmr.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_dam_tmr.$(SRC)

$(OUT_DIR)/nb_dam_ex_ms.$(OBJ): $(IN_DIR)/nb_dam_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_dam_ex_ms.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_dam_ex_ms.$(SRC)

$(OUT_DIR)/nb_ifm_dam_utils.$(OBJ): $(IN_DIR)/nb_ifm_dam_utils.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ifm_dam_utils.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_ifm_dam_utils.$(SRC)

$(OUT_DIR)/nb_dam.$(OBJ): $(IN_DIR)/nb_dam.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_dam.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_dam.$(SRC)

$(OUT_DIR)/nb_ptmi.$(OBJ): $(IN_DIR)/nb_ptmi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ptmi.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DLCNBMILNB -DLWLCNBMILNB \
	-DLWLCNB -DSM -DLCLNB $(IN_DIR)/nb_ptmi.$(SRC)

$(OUT_DIR)/nb_ex_ms.$(OBJ): $(IN_DIR)/nb_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_ex_ms.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DHI -ULCNB -DRG -DLWLCNB -DLWLCLNB \
	-DLCLNB -DSM $(IN_DIR)/nb_ex_ms.$(SRC)

$(OUT_DIR)/sm_bdy1.$(OBJ): $(IN_DIR)/sm_bdy1.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sm_bdy1.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DHI -ULCNB -DRG -DLWLCNB -DLWLCLNB \
	-DLCLNB -DSM $(IN_DIR)/sm_bdy1.$(SRC)

$(OUT_DIR)/sm_ex_ms.$(OBJ): $(IN_DIR)/sm_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sm_ex_ms.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DHI -DSB -ULCNB -DRG -DLWLCNB \
	-DLWLCLNB -DLCLNB -DSM $(IN_DIR)/sm_ex_ms.$(SRC)

$(OUT_DIR)/nb_lnb.$(OBJ): $(IN_DIR)/nb_lnb.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_lnb.$(OBJ) -I$(SS_DIR) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(IOPTS) $(POPTS) $(CCnbFLAGS) -DLWLCSMMILNB -DSM -DLCLNB \
	-DLWLCLNB -DLCNBMILNB -DLCSMMILNB $(IN_DIR)/nb_lnb.$(SRC)

$(OUT_DIR)/nb_enb_db.$(OBJ): $(IN_DIR)/nb_enb_db.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/nb_enb_db.$(OBJ) $(IOPTS) -I$(CM_DIR) -I$(VS_DIR) \
	$(COPTS) $(POPTS) $(CCnbFLAGS) $(IN_DIR)/nb_enb_db.$(SRC)

#-------------------------------------------------------------#
#Linker macros
#-------------------------------------------------------------#

$(OUT_DIR)/libnb.a:$(nbOBJS)
	$(AR) -cr $(OUT_DIR)/libnb.a $(nbOBJS)

#-------------------------------------------------------------#
#Clean macros
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libnb.a $(nbOBJS)
