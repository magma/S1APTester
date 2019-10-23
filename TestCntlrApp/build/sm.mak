#-------------------------------------------------------------#
# Makefile for Stack manager files
#-------------------------------------------------------------#

#-------------------------------------------------------------#
# Obj macros             
#-------------------------------------------------------------#
smOBJS= \
        $(OUT_DIR)/fw_sm.$(OBJ) \
        $(OUT_DIR)/fw_tst.$(OBJ) \
        $(OUT_DIR)/fw_sm_ex_ms.$(OBJ) 

FUCM_INC= $(IN_DIR)/fw_sm_log.h \
			 $(IN_DIR)/fw_tst.h $(IN_DIR)/fw_sm.x

ALL_INC=$(FUCM_INC) $(CM_INC) $(MT_DIR)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
# Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/fw_sm.$(OBJ): $(IN_DIR)/fw_sm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_sm.o $(COPTS) $(IOPTS) $(POPTS) $(IN_DIR)/fw_sm.c

$(OUT_DIR)/fw_tst.$(OBJ): $(IN_DIR)/fw_tst.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_tst.o $(COPTS) $(IOPTS) $(POPTS) \
		$(IN_DIR)/fw_tst.c

$(OUT_DIR)/fw_sm_ex_ms.$(OBJ): $(IN_DIR)/fw_sm_ex_ms.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_sm_ex_ms.o $(COPTS) $(IOPTS) $(POPTS) \
		$(IN_DIR)/fw_sm_ex_ms.c

#-------------------------------------------------------------#
# Compile rule             
#-------------------------------------------------------------#
$(OUT_DIR)/sm:$(smOBJS)

#-------------------------------------------------------------#
# Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f ../obj/fw_sm_ex_ms*.$(OBJ) ../obj/fw_tst*.$(OBJ) 
