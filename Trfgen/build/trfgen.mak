# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

# /***************************************************************************
#
#       Name:   S1 Simulator Traffic Generator
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
#                  clean    : remove traffic generator object files
#
#       File:  trfgen.mak
#
#       Prg:
#
# **************************************************************************/

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#

LIBNAME=libtrfgen.so

SERVER_MODE=-DxSRV_FRM_API
# Source code folders
TRF_GEN_DIR=../src
TRF_GEN_DIR_INC=../inc

OBJ_DIR=../obj
BIN_DIR=../../Trfgen/bin
LIB_DIR=../../Trfgen/lib
# library path

# object file suffix
OBJ=o


#-----------------------------------------------------------------------
#

# macros for compile and link options

# compiler:
UNAME_M := $(shell uname -m)
	ifeq ($(UNAME_M),aarch64)
		CC=gcc -g3 -fPIC -march=armv8-a -DALIGN_64BIT -DBIT_64
		LL=gcc -g3 -march=armv8-a
		IPERF_ARC=libiperf_arm64.so
	else
		CC=gcc -g3 -fPIC -m64 -DALIGN_64BIT -DBIT_64
		LL=gcc -g3 -m64
		IPERF_ARC=libiperf.so
	endif

#Archive library command
AR=ar

# Copy Command
CP=cp

COPTS=-pipe -Wall -Wunused -Wno-comment -Wshadow -Werror \
      -Wcast-qual -fno-strict-aliasing -Wno-variadic-macros

# linker options:
LOPTS=-lpthread -ldl

# include options:
IOPTS= -I$(TRF_GEN_DIR_INC)

trfGenOBJS=\
        $(OBJ_DIR)/trfgen.$(OBJ)

TRGN_INC= \
    $(IN_DIR)/trfgen.x

ALL_INC=$(TRGN_INC)

all: TARGETS
TARGETS:
	@echo "Compiling Traffic Generator..."
	$(CC) $(COPTS) $(SERVER_MODE) -c -o $(OBJ_DIR)/trfgen.o $(IOPTS) \
	$(TRF_GEN_DIR)/trfgen.c

	@echo "Linking Objects, Creating Shared Library"
	$(CC) -shared $(OBJ_DIR)/*.o \
	   -liperf -L $(LIB_DIR) $(LOPTS) -o $(LIB_DIR)/$(LIBNAME)

clean:
	\rm -f $(LIB_DIR)/$(LIBNAME) $(OBJ_DIR)/*.o $(OBJ_DIR)/*.a  \
		$(OBJ_DIR)/*~ $(OBJ_DIR)/*.bak $(OBJ_DIR)/*.err
