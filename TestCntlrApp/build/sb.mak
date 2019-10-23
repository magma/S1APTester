#
#
##-------------------------------------------------------------#
#Makefile for product SB - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCsbFLAGS=

# Product sources-------------------------------------------------------
sbSRCS= \
    $(IN_DIR)/sb_bdy1.$(SRC) \
    $(IN_DIR)/sb_bdy2.$(SRC) \
    $(IN_DIR)/sb_bdy3.$(SRC) \
    $(IN_DIR)/sb_bdy4.$(SRC) \
    $(IN_DIR)/sb_ex_ms.$(SRC) \
    $(IN_DIR)/sb_id.$(SRC) \
    $(IN_DIR)/sb_ptmi.$(SRC) \
    $(IN_DIR)/sb_ptui.$(SRC) \
    $(IN_DIR)/sb_ptli.$(SRC) \
    $(IN_DIR)/sb_mtu.$(SRC) \
    $(IN_DIR)/sb_port.$(SRC)


# Product objects-------------------------------------------------------
sbOBJS= \
    $(OUT_DIR)/sb_bdy1.$(OBJ) \
    $(OUT_DIR)/sb_bdy2.$(OBJ) \
    $(OUT_DIR)/sb_bdy3.$(OBJ) \
    $(OUT_DIR)/sb_bdy4.$(OBJ) \
    $(OUT_DIR)/sb_ex_ms.$(OBJ) \
    $(OUT_DIR)/sb_id.$(OBJ) \
    $(OUT_DIR)/sb_ptmi.$(OBJ) \
    $(OUT_DIR)/sb_ptui.$(OBJ) \
    $(OUT_DIR)/sb_ptli.$(OBJ) \
    $(OUT_DIR)/sb_mtu.$(OBJ) \
    $(OUT_DIR)/sb_port.$(OBJ) 


SBCM_INC=$(VS_DIR)/sb.h $(VS_DIR)/sb.x $(VS_DIR)/sb_mtu.h $(VS_DIR)/sb_mtu.x $(VS_DIR)/sb_port.h $(VS_DIR)/sb_port.x $(VS_DIR)/sb_err.h

ALL_INC=$(SBCM_INC) $(CM_INC) $(MT_DIR)
   
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/sb_bdy1.$(OBJ): $(IN_DIR)/sb_bdy1.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_bdy1.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_bdy1.$(SRC)

$(OUT_DIR)/sb_bdy2.$(OBJ): $(IN_DIR)/sb_bdy2.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_bdy2.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_bdy2.$(SRC)

$(OUT_DIR)/sb_bdy3.$(OBJ): $(IN_DIR)/sb_bdy3.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_bdy3.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_bdy3.$(SRC)

$(OUT_DIR)/sb_bdy4.$(OBJ): $(IN_DIR)/sb_bdy4.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_bdy4.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_bdy4.$(SRC)

$(OUT_DIR)/sb_ex_ms.$(OBJ): $(IN_DIR)/sb_ex_ms.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_ex_ms.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_ex_ms.$(SRC)

$(OUT_DIR)/sb_id.$(OBJ): $(IN_DIR)/sb_id.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_id.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_id.$(SRC)

$(OUT_DIR)/sb_ptmi.$(OBJ): $(IN_DIR)/sb_ptmi.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_ptmi.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_ptmi.$(SRC)

$(OUT_DIR)/sb_ptui.$(OBJ): $(IN_DIR)/sb_ptui.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_ptui.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_ptui.$(SRC)

$(OUT_DIR)/sb_ptli.$(OBJ): $(IN_DIR)/sb_ptli.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_ptli.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_ptli.$(SRC)

$(OUT_DIR)/sb_mtu.$(OBJ): $(IN_DIR)/sb_mtu.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_mtu.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_mtu.$(SRC)

$(OUT_DIR)/sb_port.$(OBJ): $(IN_DIR)/sb_port.$(SRC) $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/sb_port.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) \
	$(CCsbFLAGS) $(IN_DIR)/sb_port.$(SRC)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libsb.a:$(sbOBJS)
	$(AR) -cr $(OUT_DIR)/libsb.a $(sbOBJS)	

$(OUT_DIR)/sbprepro:$(sbOBJS)

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libsb.a $(sbOBJS)

