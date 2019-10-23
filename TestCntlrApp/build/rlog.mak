#-------------------------------------------------------------#
# Makefile for RLOG application files
#-------------------------------------------------------------#

#-------------------------------------------------------------#
# Obj macros             
#-------------------------------------------------------------#
rlogOBJS= \
        $(OUT_DIR)/rl_rlog.$(OBJ) \
        $(OUT_DIR)/rl_common.$(OBJ) \
        $(OUT_DIR)/rl_platform.$(OBJ) 


FUCM_INC= \
    $(IN_DIR)/rl_interface.h \
	 $(IN_DIR)/rl_rlog.h \
	 $(IN_DIR)/rl_platform.h \
	 $(IN_DIR)/rl_common.h 

ALL_INC=$(FUCM_INC) $(CM_INC)


#-------------------------------------------------------------#
#-------------------------------------------------------------#
# Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/rl_rlog.$(OBJ): $(IN_DIR)/rl_rlog.c $(ALL_INC)
	$(CC) -c -o$(OUT_DIR)/rl_rlog.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/rl_rlog.c

$(OUT_DIR)/rl_common.$(OBJ): $(IN_DIR)/rl_common.c $(ALL_INC)
	$(CC) -c -o$(OUT_DIR)/rl_common.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/rl_common.c

$(OUT_DIR)/rl_platform.$(OBJ): $(IN_DIR)/rl_platform.c $(ALL_INC)
	$(CC) -c -o$(OUT_DIR)/rl_platform.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/rl_platform.c

#-------------------------------------------------------------#
# Compile rule             
#-------------------------------------------------------------#
$(OUT_DIR)/rlog:$(rlogOBJS)
	$(AR) rcs $(LIB_DIR)/librlog.a $(rlogOBJS)


#-------------------------------------------------------------#
# Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(rlogOBJS)
