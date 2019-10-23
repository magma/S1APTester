

#-------------------------------------------------------------#
#Makefile for product EG - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCegFLAGS=-DEGTP_U -DLCHIT -DLCEGLIHIT -DEU

#-------------------------------------------------------------#
#File/Obj macros             
#-------------------------------------------------------------#

egSRCS= \
        $(IN_DIR)/eg_cpm.$(SRC) \
        $(IN_DIR)/eg_edm.$(SRC) \
        $(IN_DIR)/eg_ex_ms.$(SRC) \
        $(IN_DIR)/eg_id.$(SRC) \
        $(IN_DIR)/eg_tunn.$(SRC) \
        $(IN_DIR)/eg_li.$(SRC) \
        $(IN_DIR)/eg_ui.$(SRC) \
        $(IN_DIR)/eg_tpt.$(SRC) \
        $(IN_DIR)/eg_mi.$(SRC) \
        $(IN_DIR)/eg_tmr.$(SRC) \
        $(IN_DIR)/eg_ptli.$(SRC) \
        $(IN_DIR)/eg_ptmi.$(SRC) \
        $(IN_DIR)/eg_util.$(SRC) \
        $(IN_DIR)/eg_ptui.$(SRC) \
		$(IN_DIR)/eg_socklayer.$(SRC)

egOBJS= \
	$(OUT_DIR)/eg_cpm.$(OBJ) \
	$(OUT_DIR)/eg_edm.$(OBJ) \
	$(OUT_DIR)/eg_ex_ms.$(OBJ) \
	$(OUT_DIR)/eg_id.$(OBJ) \
	$(OUT_DIR)/eg_tunn.$(OBJ) \
	$(OUT_DIR)/eg_li.$(OBJ) \
	$(OUT_DIR)/eg_ui.$(OBJ) \
	$(OUT_DIR)/eg_tpt.$(OBJ) \
	$(OUT_DIR)/eg_mi.$(OBJ) \
	$(OUT_DIR)/eg_tmr.$(OBJ) \
	$(OUT_DIR)/eg_ptli.$(OBJ) \
	$(OUT_DIR)/eg_ptmi.$(OBJ) \
	$(OUT_DIR)/eg_util.$(OBJ) \
	$(OUT_DIR)/eg_ptui.$(OBJ) \
	$(OUT_DIR)/eg_socklayer.$(OBJ) 
	
EGCM_INC= \
    $(VS_DIR)/eg.h $(VS_DIR)/eg.x $(VS_DIR)/eg_util.h $(VS_DIR)/eg_util.x

ALL_INC=$(EGCM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/eg_cpm.$(OBJ): $(IN_DIR)/eg_cpm.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_cpm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_cpm.$(SRC)
	
$(OUT_DIR)/eg_edm.$(OBJ): $(IN_DIR)/eg_edm.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_edm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_edm.$(SRC)
	
$(OUT_DIR)/eg_ex_ms.$(OBJ): $(IN_DIR)/eg_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_ex_ms.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_ex_ms.$(SRC)
	
$(OUT_DIR)/eg_id.$(OBJ): $(IN_DIR)/eg_id.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_id.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_id.$(SRC)
	
$(OUT_DIR)/eg_tunn.$(OBJ): $(IN_DIR)/eg_tunn.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_tunn.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_tunn.$(SRC)
	
$(OUT_DIR)/eg_li.$(OBJ): $(IN_DIR)/eg_li.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_li.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_li.$(SRC)
	
$(OUT_DIR)/eg_ui.$(OBJ): $(IN_DIR)/eg_ui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_ui.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_ui.$(SRC)
	
$(OUT_DIR)/eg_tpt.$(OBJ): $(IN_DIR)/eg_tpt.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_tpt.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_tpt.$(SRC)
	
$(OUT_DIR)/eg_mi.$(OBJ): $(IN_DIR)/eg_mi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_mi.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_mi.$(SRC)
	
$(OUT_DIR)/eg_tmr.$(OBJ): $(IN_DIR)/eg_tmr.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_tmr.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_tmr.$(SRC)
	
$(OUT_DIR)/eg_ptli.$(OBJ): $(IN_DIR)/eg_ptli.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_ptli.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_ptli.$(SRC)
	
$(OUT_DIR)/eg_ptmi.$(OBJ): $(IN_DIR)/eg_ptmi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_ptmi.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_ptmi.$(SRC)
	
$(OUT_DIR)/eg_util.$(OBJ): $(IN_DIR)/eg_util.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_util.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_util.$(SRC)
	
$(OUT_DIR)/eg_ptui.$(OBJ): $(IN_DIR)/eg_ptui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_ptui.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_ptui.$(SRC)
	
$(OUT_DIR)/eg_socklayer.$(OBJ): $(IN_DIR)/eg_socklayer.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/eg_socklayer.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
		$(CCegFLAGS) $(IN_DIR)/eg_socklayer.$(SRC)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/egtp:$(egOBJS)
	$(AR) -cr $(LIB_DIR)/libeg.a $(egOBJS)

$(OUT_DIR)/egprepro:$(egOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libeg.a $(egOBJS)

