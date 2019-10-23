# /***************************************************************************
#
#       Name:   S1 Simulator Test Stub
#
#       Type:   make file
#
#       Desc:   Compile, assemble and link product software for
#               various configurations. Further comments are
#               embedded in the file. 
#
#       Env:    Linux 2.4.x with GNU C (gcc)
#
#               BUILD TARGETS:
#                  clean    : remove test stub object files
#   
#       File:  tc.mak
#
#       Prg:   
#
# **************************************************************************/

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#

SRC_DIR=../src
OBJ_DIR=../obj
BIN_DIR=../bin
CFG_DIR=../../TestCntlrApp/cfg
IOPTS=../../TestCntlrApp/src/tfwApp

TC_DEFINES= -DTFW_STUB
DEPS=$(IOPTS)/fw_api_int.x

# Compiler options
CC=gcc -g3 -c -Wall -Werror -DUNUSED

#CC=gcc -g3 -c -Wall -Werror  \
	 -ansi -pipe -pedantic -Wall -Wunused -Wno-comment -Wshadow \
	 -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
	 -fno-strict-aliasing -Wno-variadic-macros -Werror

# Linker options
#LOPTS=-lpthread -ldl
LL=gcc -g3 -m64

tcObjs=\
		 $(OBJ_DIR)/ts_main.o \
		 $(OBJ_DIR)/ts_utls.o \
		 $(OBJ_DIR)/ts_config.o \
		 $(OBJ_DIR)/ts_atchDtchProcs.o \
		 $(OBJ_DIR)/ts_periodicTauProcs.o \
		 $(OBJ_DIR)/ts_enbProc.o \
		 $(OBJ_DIR)/ts_serviceProcs.o\
		 $(OBJ_DIR)/ts_PagingProc.o\
		 $(OBJ_DIR)/ts_timer_thread.o\
		 $(OBJ_DIR)/ts_timer_queue.o\
                 $(OBJ_DIR)/ts_Att_tau_det.o

$(OBJ_DIR)/ts_main.o: $(SRC_DIR)/ts_main.c $(DEPS)
	@echo "Compiling ts_main.c ..."
	$(CC) ../src/ts_main.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_main.o

$(OBJ_DIR)/ts_utls.o: $(SRC_DIR)/ts_utls.c $(DEPS)
	@echo "Compiling ts_utls.c..."
	$(CC) ../src/ts_utls.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_utls.o

$(OBJ_DIR)/ts_config.o: $(SRC_DIR)/ts_config.c $(DEPS)
	@echo "Compiling ts_config.c ..."
	$(CC) ../src/ts_config.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_config.o

$(OBJ_DIR)/ts_atchDtchProcs.o: $(SRC_DIR)/ts_atchDtchProcs.c $(DEPS)
	@echo "Compiling ts_atchDtchProcs.c ..."
	$(CC) ../src/ts_atchDtchProcs.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_atchDtchProcs.o

$(OBJ_DIR)/ts_periodicTauProcs.o: $(SRC_DIR)/ts_periodicTauProcs.c $(DEPS)
	@echo "Compiling ts_periodicTauProcs.c ..."
	$(CC) ../src/ts_periodicTauProcs.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_periodicTauProcs.o

$(OBJ_DIR)/ts_serviceProcs.o: $(SRC_DIR)/ts_serviceProcs.c $(DEPS)
	@echo "Compiling ts_serviceProcs.c ..."
	$(CC) ../src/ts_serviceProcs.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_serviceProcs.o

$(OBJ_DIR)/ts_enbProc.o: $(SRC_DIR)/ts_enbProc.c $(DEPS)
	@echo "Compiling ts_enbProc.c ..."
	$(CC) ../src/ts_enbProc.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_enbProc.o

$(OBJ_DIR)/ts_PagingProc.o: $(SRC_DIR)/ts_PagingProc.c $(DEPS)
	@echo "Compiling ts_enbProc.c ..."
	$(CC) ../src/ts_PagingProc.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_PagingProc.o

$(OBJ_DIR)/ts_timer_thread.o: $(SRC_DIR)/ts_timer_thread.c $(DEPS)
	@echo "Compiling /ts_timer_thread.c ..."
	$(CC) ../src/ts_timer_thread.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_timer_thread.o

$(OBJ_DIR)/ts_timer_queue.o: $(SRC_DIR)/ts_timer_queue.c $(DEPS)
	@echo "Compiling /ts_timer_queue.c ..."
	$(CC) ../src/ts_timer_queue.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_timer_queue.o

$(OBJ_DIR)/ts_Att_tau_det.o: $(SRC_DIR)/ts_Att_tau_det.c $(DEPS)
	@echo "Compiling /ts_Att_tau_det.c ..."
	$(CC) ../src/ts_Att_tau_det.c $(TC_DEFINES) -I$(IOPTS) \
	   -I../../Trfgen/src -o $(OBJ_DIR)/ts_Att_tau_det.o

all: $(tcObjs)
	@echo "Linking Objects, Creating binary"
	$(LL) $(OBJ_DIR)/*.o -ltfw -lpthread -L ../../TestCntlrApp/lib \
	   -liperf -L ../../Trfgen/lib/ \
	   -ltrfgen -L ../../Trfgen/lib -o $(BIN_DIR)/testCntrlr -lm
	
	\ln -sf $(CFG_DIR)/imsi.txt $(BIN_DIR)/imsi.txt
	\ln -sf $(CFG_DIR)/nbAppCfg.txt $(BIN_DIR)/nbAppCfg.txt
	\ln -sf $(CFG_DIR)/tfwAppcfg.txt $(BIN_DIR)/tfwAppcfg.txt
	\ln -sf $(CFG_DIR)/ueAppCfg.txt $(BIN_DIR)/ueAppCfg.txt
	\ln -sf $(CFG_DIR)/ueCfg.txt $(BIN_DIR)/ueCfg.txt
	\ln -sf $(CFG_DIR)/testCaseList_1.txt $(BIN_DIR)/testCaseList_1.txt
	\ln -sf $(CFG_DIR)/testCaseList_2.txt $(BIN_DIR)/testCaseList_2.txt
	\ln -sf $(CFG_DIR)/testCaseList_3.txt $(BIN_DIR)/testCaseList_3.txt

clean:
	\rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/testCntrlr

cleanall:
	\rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/testCntrlr
