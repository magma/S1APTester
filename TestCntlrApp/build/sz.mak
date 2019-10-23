#
#
##-------------------------------------------------------------#
#Makefile for product SZ - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCszFLAGS=-DLCLSZ -DLCSCT -DSZ -DSM -US1AP_REL851 -DLSZV1 -DS1AP_REL9A6

# Product sources-------------------------------------------------------
szSRCS= \
    $(IN_DIR)/sz_db.$(SRC) \
    $(IN_DIR)/sz_li.$(SRC) \
    $(IN_DIR)/sz_mgmt.$(SRC) \
    $(IN_DIR)/sz_mi.$(SRC) \
    $(IN_DIR)/sz_msgfn.$(SRC) \
    $(IN_DIR)/sz_ex_ms.$(SRC) \
    $(IN_DIR)/sz_ndb.$(SRC) \
    $(IN_DIR)/sz_id.$(SRC) \
    $(IN_DIR)/sz_sm.$(SRC) \
    $(IN_DIR)/sz_smlienb.$(SRC) \
    $(IN_DIR)/sz_smuienb.$(SRC) \
    $(IN_DIR)/sz_ptli.$(SRC) \
    $(IN_DIR)/sz_ptmi.$(SRC) \
    $(IN_DIR)/sz_ptui.$(SRC) \
    $(IN_DIR)/sz_tmr.$(SRC) \
    $(IN_DIR)/sz_ui.$(SRC) \
    $(IN_DIR)/sz_utils.$(SRC) \
    $(IN_DIR)/sz_3gdb.$(SRC) 


# Product objects-------------------------------------------------------
szOBJS= \
    $(OUT_DIR)/sz_db.$(OBJ) \
    $(OUT_DIR)/sz_li.$(OBJ) \
    $(OUT_DIR)/sz_mgmt.$(OBJ) \
    $(OUT_DIR)/sz_mi.$(OBJ) \
    $(OUT_DIR)/sz_msgfn.$(OBJ) \
    $(OUT_DIR)/sz_ex_ms.$(OBJ) \
    $(OUT_DIR)/sz_ndb.$(OBJ) \
    $(OUT_DIR)/sz_id.$(OBJ) \
    $(OUT_DIR)/sz_sm.$(OBJ) \
    $(OUT_DIR)/sz_smlienb.$(OBJ) \
    $(OUT_DIR)/sz_smuienb.$(OBJ) \
    $(OUT_DIR)/sz_ptli.$(OBJ) \
    $(OUT_DIR)/sz_ptmi.$(OBJ) \
    $(OUT_DIR)/sz_ptui.$(OBJ) \
    $(OUT_DIR)/sz_tmr.$(OBJ) \
    $(OUT_DIR)/sz_ui.$(OBJ) \
    $(OUT_DIR)/sz_utils.$(OBJ) \
    $(OUT_DIR)/sz_3gdb.$(OBJ) 


SZCM_INC=$(VS_DIR)/sz.h $(VS_DIR)/sz.x $(VS_DIR)/sz_err.h

ALL_INC=$(SZCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/sz_db.$(OBJ): $(IN_DIR)/sz_db.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_db.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_db.$(SRC)

$(OUT_DIR)/sz_3gdb.$(OBJ): $(IN_DIR)/sz_3gdb.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_3gdb.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_3gdb.$(SRC)

$(OUT_DIR)/sz_li.$(OBJ): $(IN_DIR)/sz_li.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_li.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_li.$(SRC)

$(OUT_DIR)/sz_mgmt.$(OBJ): $(IN_DIR)/sz_mgmt.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_mgmt.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_mgmt.$(SRC)

$(OUT_DIR)/sz_mi.$(OBJ): $(IN_DIR)/sz_mi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_mi.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_mi.$(SRC)

$(OUT_DIR)/sz_msgfn.$(OBJ): $(IN_DIR)/sz_msgfn.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_msgfn.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_msgfn.$(SRC)

$(OUT_DIR)/sz_ex_ms.$(OBJ): $(IN_DIR)/sz_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ex_ms.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ex_ms.$(SRC)

$(OUT_DIR)/sz_ndb.$(OBJ): $(IN_DIR)/sz_ndb.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ndb.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ndb.$(SRC)

$(OUT_DIR)/sz_id.$(OBJ): $(IN_DIR)/sz_id.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_id.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_id.$(SRC)

$(OUT_DIR)/sz_sm.$(OBJ): $(IN_DIR)/sz_sm.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_sm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_sm.$(SRC)

$(OUT_DIR)/sz_smlienb.$(OBJ): $(IN_DIR)/sz_smlienb.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_smlienb.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_smlienb.$(SRC) 

$(OUT_DIR)/sz_smuienb.$(OBJ): $(IN_DIR)/sz_smuienb.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_smuienb.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_smuienb.$(SRC)

$(OUT_DIR)/sz_ptli.$(OBJ): $(IN_DIR)/sz_ptli.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ptli.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ptli.$(SRC)

$(OUT_DIR)/sz_ptmi.$(OBJ): $(IN_DIR)/sz_ptmi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ptmi.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ptmi.$(SRC)

$(OUT_DIR)/sz_ptui.$(OBJ): $(IN_DIR)/sz_ptui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ptui.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ptui.$(SRC)

$(OUT_DIR)/sz_tmr.$(OBJ): $(IN_DIR)/sz_tmr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_tmr.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_tmr.$(SRC)

$(OUT_DIR)/sz_ui.$(OBJ): $(IN_DIR)/sz_ui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_ui.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_ui.$(SRC)

$(OUT_DIR)/sz_utils.$(OBJ): $(IN_DIR)/sz_utils.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sz_utils.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCszFLAGS) $(IN_DIR)/sz_utils.$(SRC)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libsz.a:$(szOBJS)
	$(AR) -cr $(OUT_DIR)/libsz.a $(szOBJS)	

$(OUT_DIR)/szprepro:$(szOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libsz.a $(szOBJS)

