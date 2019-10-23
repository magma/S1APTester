#-------------------------------------------------------------#
# Makefile for Test Framework files
#-------------------------------------------------------------#

#-------------------------------------------------------------#
# Obj macros             
#-------------------------------------------------------------#
fwAppOBJS=\
        $(OUT_DIR)/fw_ex_ms.$(OBJ)\
        $(OUT_DIR)/fw_mi.$(OBJ)\
        $(OUT_DIR)/fw_li.$(OBJ)\
        $(OUT_DIR)/fw_ptli.$(OBJ)\
        $(OUT_DIR)/fw_ptmi.$(OBJ)\
		  $(OUT_DIR)/fw_read_dflcfg.$(OBJ)\
		  $(OUT_DIR)/fw_nbmsg_handler.$(OBJ)\
		  $(OUT_DIR)/fw_uemsg_handler.$(OBJ)\
		  $(OUT_DIR)/fw_api_int.$(OBJ)      \
		  $(OUT_DIR)/fw_tmr.$(OBJ)

FUCM_INC= \
    $(IN_DIR)/fw.h     $(IN_DIR)/fw.x \
    $(IN_DIR)/fw_log.h $(IN_DIR)/fw_json_parser.h

ALL_INC=$(FUCM_INC) $(CM_INC)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
# Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/fw_mi.$(OBJ): $(IN_DIR)/fw_mi.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_mi.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_mi.c

$(OUT_DIR)/fw_ex_ms.$(OBJ): $(IN_DIR)/fw_ex_ms.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_ex_ms.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_ex_ms.c

$(OUT_DIR)/fw_li.$(OBJ): $(IN_DIR)/fw_li.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_li.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_li.c

$(OUT_DIR)/fw_ptmi.$(OBJ): $(IN_DIR)/fw_ptmi.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_ptmi.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_ptmi.c

$(OUT_DIR)/fw_ptli.$(OBJ): $(IN_DIR)/fw_ptli.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_ptli.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_ptli.c

$(OUT_DIR)/fw_json_parser.$(OBJ): $(IN_DIR)/fw_json_parser.cpp $(ALL_INC)
	$(CPP) -c -o $(OUT_DIR)/fw_json_parser.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_json_parser.cpp

$(OUT_DIR)/fw_nbmsg_handler.$(OBJ): $(IN_DIR)/fw_nbmsg_handler.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_nbmsg_handler.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_nbmsg_handler.c

$(OUT_DIR)/fw_uemsg_handler.$(OBJ): $(IN_DIR)/fw_uemsg_handler.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_uemsg_handler.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_uemsg_handler.c

$(OUT_DIR)/fw_read_dflcfg.$(OBJ): $(IN_DIR)/fw_read_dflcfg.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_read_dflcfg.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_read_dflcfg.c

$(OUT_DIR)/fw_api_int.$(OBJ): $(IN_DIR)/fw_api_int.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_api_int.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_api_int.c

$(OUT_DIR)/fw_tmr.$(OBJ): $(IN_DIR)/fw_tmr.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/fw_tmr.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/fw_tmr.c

#-------------------------------------------------------------#
# Compile rule             
#-------------------------------------------------------------#
$(OUT_DIR)/fw_app:$(fwAppOBJS)

#-------------------------------------------------------------#
# Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(fwAppOBJS)
