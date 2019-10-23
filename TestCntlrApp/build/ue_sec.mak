#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
#ifeq ($(BLDENV),lnx_perf_msstub_acc)
#CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
#          -UTFU_TDD -DRG -UYS_LTE_PAL -DYS_MSPD -DYS_MSPD_OSAL 
#else
#ifeq ($(BLDENV),lnx_e2e_msstub_acc)
#CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
#          -UTFU_TDD -DRG -UYS_LTE_PAL -DYS_MSPD -DYS_MSPD_OSAL
#else
#ifeq ($(BLDENV),lnx_e2e_acc)
#CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
#          -UTFU_TDD -DRG -DYS_LTE_PAL  -DKW_PDCP -DRLCPDCP -DKW -DPJ
#else
#CCueFLAGS=-DTF -DLCCTF -DLCTFUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 \
#          -UTFU_TDD -DRG -UYS_LTE_PAL -DKW_PDCP
#endif
#endif
#endif


# Product sources-------------------------------------------------------
UE_SEC_SRC= \
    $(IN_DIR)/auth_alg.c \
    $(IN_DIR)/endianness.c \
    $(IN_DIR)/hmac.c \
    $(IN_DIR)/hmacsha256.c \
    $(IN_DIR)/mp.c \
    $(IN_DIR)/sha256.c \
    $(IN_DIR)/snow_3g. \
    $(IN_DIR)/snow3g_f8f9.c \
    $(IN_DIR)/aes.c 


# Product objects-------------------------------------------------------
UE_SEC_OBJS= \
    $(OUT_DIR)/auth_alg.o \
    $(OUT_DIR)/endianness.o \
    $(OUT_DIR)/hmac.o \
    $(OUT_DIR)/hmacsha256.o \
    $(OUT_DIR)/mp.o \
    $(OUT_DIR)/sha256.o \
    $(OUT_DIR)/snow_3g.o \
    $(OUT_DIR)/snow3g_f8f9.o \
    $(OUT_DIR)/aes.o 


ALL_INC= $(CM_INC)
#-------------------------------------------------------------#
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#

$(OUT_DIR)/auth_alg.$(OBJ): $(IN_DIR)/auth_alg.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/auth_alg.c -o \
	$(OUT_DIR)/auth_alg.$(OBJ)

$(OUT_DIR)/endianness.$(OBJ): $(IN_DIR)/endianness.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/endianness.c -o \
	$(OUT_DIR)/endianness.$(OBJ)

$(OUT_DIR)/hmac.$(OBJ): $(IN_DIR)/hmac.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/hmac.c -o \
	$(OUT_DIR)/hmac.$(OBJ)

$(OUT_DIR)/hmacsha256.$(OBJ): $(IN_DIR)/hmacsha256.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/hmacsha256.c -o \
	$(OUT_DIR)/hmacsha256.$(OBJ)

$(OUT_DIR)/mp.$(OBJ): $(IN_DIR)/mp.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/mp.c -o \
	$(OUT_DIR)/mp.$(OBJ)

$(OUT_DIR)/sha256.$(OBJ): $(IN_DIR)/sha256.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/sha256.c -o \
	$(OUT_DIR)/sha256.$(OBJ)

$(OUT_DIR)/snow_3g.$(OBJ): $(IN_DIR)/snow_3g.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/snow_3g.c -o \
	$(OUT_DIR)/snow_3g.$(OBJ)

$(OUT_DIR)/snow3g_f8f9.$(OBJ): $(IN_DIR)/snow3g_f8f9.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/snow3g_f8f9.c -o \
	$(OUT_DIR)/snow3g_f8f9.$(OBJ)

$(OUT_DIR)/aes.$(OBJ): $(IN_DIR)/aes.c $(ALL_INC)
	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCueFLAGS) $(IN_DIR)/aes.c -o \
	$(OUT_DIR)/aes.$(OBJ)

#-------------------------------------------------------------#
#Linker macros             
#-------------------------------------------------------------#
$(OUT_DIR)/libuesec.a:$(UE_SEC_OBJS)
	 $(AR) rcs $(LIB_DIR)/libuesec.a 

#-------------------------------------------------------------#
#Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(OUT_DIR)/libuesec.a $(UE_SEC_OBJS)

