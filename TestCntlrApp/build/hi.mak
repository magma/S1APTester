#
#-------------------------------------------------------------#
#Makefile for product HI - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CChiFLAGS=-USZ

# Product sources-------------------------------------------------------
hiSRCS= \
    $(IN_DIR)/hi_bdy1.$(SRC) \
    $(IN_DIR)/hi_bdy2.$(SRC) \
    $(IN_DIR)/hi_bdy3.$(SRC) \
    $(IN_DIR)/hi_ex_ms.$(SRC) \
    $(IN_DIR)/hi_id.$(SRC) \
    $(IN_DIR)/hi_ptmi.$(SRC) \
    $(IN_DIR)/hi_ptui.$(SRC) 


# Product objects-------------------------------------------------------
hiOBJS= \
    $(OUT_DIR)/hi_bdy1.$(OBJ) \
    $(OUT_DIR)/hi_bdy2.$(OBJ) \
    $(OUT_DIR)/hi_bdy3.$(OBJ) \
    $(OUT_DIR)/hi_ex_ms.$(OBJ) \
    $(OUT_DIR)/hi_id.$(OBJ) \
    $(OUT_DIR)/hi_ptmi.$(OBJ) \
    $(OUT_DIR)/hi_ptui.$(OBJ) 


HICM_INC=$(VS_DIR)/hi.h $(VS_DIR)/hi.x $(VS_DIR)/hi_err.h

ALL_INC=$(HICM_INC) $(CM_INC)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/hi_bdy1.$(OBJ): $(IN_DIR)/hi_bdy1.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_bdy1.$(SRC) \
	-o $(OUT_DIR)/hi_bdy1.$(OBJ)

$(OUT_DIR)/hi_bdy2.$(OBJ): $(IN_DIR)/hi_bdy2.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_bdy2.$(SRC) \
	-o $(OUT_DIR)/hi_bdy2.$(OBJ)
	
$(OUT_DIR)/hi_bdy3.$(OBJ): $(IN_DIR)/hi_bdy3.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_bdy3.$(SRC) \
	-o $(OUT_DIR)/hi_bdy3.$(OBJ)
	
$(OUT_DIR)/hi_ex_ms.$(OBJ): $(IN_DIR)/hi_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ex_ms.$(SRC) \
	-o $(OUT_DIR)/hi_ex_ms.$(OBJ)

$(OUT_DIR)/hi_id.$(OBJ): $(IN_DIR)/hi_id.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_id.$(SRC) -o \
	$(OUT_DIR)/hi_id.$(OBJ)

$(OUT_DIR)/hi_ptmi.$(OBJ): $(IN_DIR)/hi_ptmi.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ptmi.$(SRC) \
	-o $(OUT_DIR)/hi_ptmi.$(OBJ)

$(OUT_DIR)/hi_ptui.$(OBJ): $(IN_DIR)/hi_ptui.$(SRC) $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) $(IN_DIR)/hi_ptui.$(SRC) \
	-o $(OUT_DIR)/hi_ptui.$(OBJ)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#

$(OUT_DIR)/libhi.a:$(hiOBJS)
	$(AR) -cr $(OUT_DIR)/libhi.a $(hiOBJS)	

$(OUT_DIR)/hiprepro:$(hiOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libhi.a $(hiOBJS)

