#-------------------------------------------------------------#
# Makefile for DSC application files
#-------------------------------------------------------------#

#-------------------------------------------------------------#
# Obj macros             
#-------------------------------------------------------------#
ueOBJS=\
	$(OUT_DIR)/ue_ptmi.$(OBJ)\
	$(OUT_DIR)/ue_mi.$(OBJ)\
	$(OUT_DIR)/ue_ptui.$(OBJ)\
	$(OUT_DIR)/ue_ui.$(OBJ)\
	$(OUT_DIR)/ue_app.$(OBJ)\
	$(OUT_DIR)/ue_ex_ms.$(OBJ)\
	$(OUT_DIR)/ue_emm_edm.$(OBJ) \
	$(OUT_DIR)/ue_esm_edm.$(OBJ) \
	$(OUT_DIR)/ue_emm_esm.$(OBJ) \
	$(OUT_DIR)/ue_db.$(OBJ) \
	$(OUT_DIR)/ue_li.$(OBJ) \
	$(OUT_DIR)/ue_ptli.$(OBJ) \
	$(OUT_DIR)/ue_app_sec.$(OBJ) \
   $(OUT_DIR)/ue_usim_auth.$(OBJ) \
   $(OUT_DIR)/ue_alg_intf.$(OBJ) \
	$(OUT_DIR)/ue_app_sec_ut.$(OBJ) \
	$(OUT_DIR)/ue_aes_mode.$(OBJ)

FUCM_INC= \
	$(IN_DIR)/ue.h           $(IN_DIR)/ue_app.x \
	$(IN_DIR)/ue.x           $(IN_DIR)/ue_emm_esm.x \
	$(IN_DIR)/ue_emm.x       $(IN_DIR)/ue_esm.x	\
	$(IN_DIR)/ue_emm_esm.h   $(IN_DIR)/ue_emm.h \
	$(IN_DIR)/ue_esm.h       $(IN_DIR)/ueAppdbm.x \
	$(IN_DIR)/ue_app_sec.x   $(IN_DIR)/ue_app_sec.h \
	$(IN_DIR)/ue_usim_auth.h $(IN_DIR)/ue_usim_auth.x \
	$(IN_DIR)/ue_alg_intf.x  $(IN_DIR)/ue_aes_mode.h \
	$(IN_DIR)/ue_aes_mode.x  


ALL_INC= $(FUCM_INC) $(CM_INC) 

#-------------------------------------------------------------#
#-------------------------------------------------------------#
# Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/ue_ptmi.$(OBJ): $(IN_DIR)/ue_ptmi.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_ptmi.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_ptmi.c

$(OUT_DIR)/ue_mi.$(OBJ): $(IN_DIR)/ue_mi.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_mi.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_mi.c

$(OUT_DIR)/ue_ptui.$(OBJ): $(IN_DIR)/ue_ptui.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_ptui.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_ptui.c

$(OUT_DIR)/ue_ui.$(OBJ): $(IN_DIR)/ue_ui.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_ui.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_ui.c

$(OUT_DIR)/ue_app.$(OBJ): $(IN_DIR)/ue_app.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_app.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_app.c

$(OUT_DIR)/ue_ex_ms.$(OBJ): $(IN_DIR)/ue_ex_ms.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_ex_ms.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_ex_ms.c

$(OUT_DIR)/ue_emm_edm.$(OBJ): $(IN_DIR)/ue_emm_edm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_emm_edm.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_emm_edm.c

$(OUT_DIR)/ue_esm_edm.$(OBJ): $(IN_DIR)/ue_esm_edm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_esm_edm.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_esm_edm.c

$(OUT_DIR)/ue_emm_esm.$(OBJ): $(IN_DIR)/ue_emm_esm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_emm_esm.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_emm_esm.c

$(OUT_DIR)/ue_db.$(OBJ): $(IN_DIR)/ue_db.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_db.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_db.c

$(OUT_DIR)/ue_app_sec.$(OBJ): $(IN_DIR)/ue_app_sec.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_app_sec.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_app_sec.c

$(OUT_DIR)/ue_usim_auth.$(OBJ): $(IN_DIR)/ue_usim_auth.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_usim_auth.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_usim_auth.c

$(OUT_DIR)/ue_alg_intf.$(OBJ): $(IN_DIR)/ue_alg_intf.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_alg_intf.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_alg_intf.c

$(OUT_DIR)/ue_app_sec_ut.$(OBJ): $(IN_DIR)/ue_app_sec_ut.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_app_sec_ut.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_app_sec_ut.c

$(OUT_DIR)/ue_aes_mode.$(OBJ): $(IN_DIR)/ue_aes_mode.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_aes_mode.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_aes_mode.c

$(OUT_DIR)/ue_li.$(OBJ): $(IN_DIR)/ue_li.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_li.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_li.c

$(OUT_DIR)/ue_ptli.$(OBJ): $(IN_DIR)/ue_ptli.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ue_ptli.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ue_ptli.c
#-------------------------------------------------------------#
# Compile rule             
#-------------------------------------------------------------#
$(OUT_DIR)/ueApp:$(ueOBJS)

#-------------------------------------------------------------#
# Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f ../obj/ue*.o

