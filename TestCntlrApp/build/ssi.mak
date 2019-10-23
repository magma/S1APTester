#-------------------------------------------------------------#
# Makefile for product SSI
#-------------------------------------------------------------#

#-------------------------------------------------------------#
# Obj macros             
#-------------------------------------------------------------#
mtOBJS= \
	$(OUT_DIR)/cm_bdy5.$(OBJ)   \
	$(OUT_DIR)/cm_dns.$(OBJ)    \
	$(OUT_DIR)/cm_gen.$(OBJ)    \
	$(OUT_DIR)/cm_hash.$(OBJ)   \
	$(OUT_DIR)/cm_inet.$(OBJ)   \
	$(OUT_DIR)/cm_lib.$(OBJ)    \
	$(OUT_DIR)/cm_llist.$(OBJ)  \
	$(OUT_DIR)/cm_mblk.$(OBJ)   \
	$(OUT_DIR)/cm_mem.$(OBJ)    \
	$(OUT_DIR)/cm_task.$(OBJ)   \
	$(OUT_DIR)/cm_tkns.$(OBJ)   \
	$(OUT_DIR)/cm_tpt.$(OBJ)    \
	$(OUT_DIR)/mt_id.$(OBJ)     \
	$(OUT_DIR)/mt_ss.$(OBJ)     \
	$(OUT_DIR)/ss_drvr.$(OBJ)   \
	$(OUT_DIR)/ss_gen.$(OBJ)    \
	$(OUT_DIR)/ss_id.$(OBJ)     \
	$(OUT_DIR)/ss_mem.$(OBJ)    \
	$(OUT_DIR)/ss_msg.$(OBJ)    \
	$(OUT_DIR)/ss_pack.$(OBJ)   \
	$(OUT_DIR)/ss_queue.$(OBJ)  \
	$(OUT_DIR)/ss_rtr.$(OBJ)    \
	$(OUT_DIR)/ss_strm.$(OBJ)   \
	$(OUT_DIR)/ss_task.$(OBJ)   \
	$(OUT_DIR)/ss_timer.$(OBJ)  \
	$(OUT_DIR)/ss_tskent.$(OBJ)

MT_INC=\
   $(IN_DIR)/cm5.h       $(IN_DIR)/cm5.x       $(IN_DIR)/cm_dns.h   \
   $(IN_DIR)/cm_dns.x    $(IN_DIR)/cm_err.h    $(IN_DIR)/cm_gen.h   \
   $(IN_DIR)/cm_gen.x    $(IN_DIR)/cm_hash.h   $(IN_DIR)/cm_hash.x  \
   $(IN_DIR)/cm_inet.h   $(IN_DIR)/cm_inet.x   $(IN_DIR)/cm_lib.x   \
   $(IN_DIR)/cm_llist.h  $(IN_DIR)/cm_llist.x  $(IN_DIR)/cm_mblk.h  \
   $(IN_DIR)/cm_mblk.x   $(IN_DIR)/cm_mem.h    $(IN_DIR)/cm_mem.x   \
   $(IN_DIR)/cm_task.h   $(IN_DIR)/cm_task.x   $(IN_DIR)/cm_tkns.h  \
   $(IN_DIR)/cm_tkns.x   $(IN_DIR)/cm_tpt.h    $(IN_DIR)/cm_tpt.x   \
   $(IN_DIR)/envdep.h    $(IN_DIR)/envind.h    $(IN_DIR)/envopt.h   \
   $(IN_DIR)/gen.h       $(IN_DIR)/gen.x       $(IN_DIR)/mt_err.h   \
   $(IN_DIR)/mt_ss.h     $(IN_DIR)/mt_ss.x     $(IN_DIR)/ss_dep.h   \
   $(IN_DIR)/ss_dep.x    $(IN_DIR)/ss_drvr.x   $(IN_DIR)/ss_err.h   \
   $(IN_DIR)/ss_gen.h    $(IN_DIR)/ss_gen.x    $(IN_DIR)/ss_mem.h   \
   $(IN_DIR)/ss_mem.x    $(IN_DIR)/ss_msg.h    $(IN_DIR)/ss_msg.x   \
   $(IN_DIR)/ss_queue.h  $(IN_DIR)/ss_queue.x  $(IN_DIR)/ss_strm.h  \
   $(IN_DIR)/ss_strm.x   $(IN_DIR)/ss_task.h   $(IN_DIR)/ss_task.x  \
   $(IN_DIR)/ss_timer.x  $(IN_DIR)/ssi.h       $(IN_DIR)/ssi.x  

ALL_INC=$(MT_INC) $(CM_INC)

#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
#Compiler macros             
#-------------------------------------------------------------#
$(OUT_DIR)/cm_bdy5.$(OBJ): $(IN_DIR)/cm_bdy5.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_bdy5.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_bdy5.c
$(OUT_DIR)/cm_dns.$(OBJ): $(IN_DIR)/cm_dns.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_dns.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_dns.c
$(OUT_DIR)/cm_gen.$(OBJ): $(IN_DIR)/cm_gen.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_gen.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_gen.c
$(OUT_DIR)/cm_hash.$(OBJ): $(IN_DIR)/cm_hash.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_hash.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_hash.c
$(OUT_DIR)/cm_inet.$(OBJ): $(IN_DIR)/cm_inet.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_inet.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_inet.c
$(OUT_DIR)/cm_lib.$(OBJ): $(IN_DIR)/cm_lib.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_lib.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_lib.c
$(OUT_DIR)/cm_llist.$(OBJ): $(IN_DIR)/cm_llist.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_llist.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_llist.c
$(OUT_DIR)/cm_mblk.$(OBJ): $(IN_DIR)/cm_mblk.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_mblk.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_mblk.c
$(OUT_DIR)/cm_mem.$(OBJ): $(IN_DIR)/cm_mem.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_mem.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_mem.c
$(OUT_DIR)/cm_task.$(OBJ): $(IN_DIR)/cm_task.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_task.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_task.c
$(OUT_DIR)/cm_tkns.$(OBJ): $(IN_DIR)/cm_tkns.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_tkns.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_tkns.c
$(OUT_DIR)/cm_tpt.$(OBJ): $(IN_DIR)/cm_tpt.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/cm_tpt.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/cm_tpt.c
$(OUT_DIR)/mt_id.$(OBJ): $(IN_DIR)/mt_id.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/mt_id.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/mt_id.c
$(OUT_DIR)/mt_ss.$(OBJ): $(IN_DIR)/mt_ss.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/mt_ss.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/mt_ss.c
$(OUT_DIR)/ss_drvr.$(OBJ): $(IN_DIR)/ss_drvr.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_drvr.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_drvr.c
$(OUT_DIR)/ss_gen.$(OBJ): $(IN_DIR)/ss_gen.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_gen.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_gen.c
$(OUT_DIR)/ss_id.$(OBJ): $(IN_DIR)/ss_id.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_id.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_id.c
$(OUT_DIR)/ss_mem.$(OBJ): $(IN_DIR)/ss_mem.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_mem.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_mem.c
$(OUT_DIR)/ss_msg.$(OBJ): $(IN_DIR)/ss_msg.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_msg.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_msg.c
$(OUT_DIR)/ss_pack.$(OBJ): $(IN_DIR)/ss_pack.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_pack.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_pack.c
$(OUT_DIR)/ss_queue.$(OBJ): $(IN_DIR)/ss_queue.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_queue.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_queue.c
$(OUT_DIR)/ss_rtr.$(OBJ): $(IN_DIR)/ss_rtr.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_rtr.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_rtr.c
$(OUT_DIR)/ss_strm.$(OBJ): $(IN_DIR)/ss_strm.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_strm.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_strm.c
$(OUT_DIR)/ss_task.$(OBJ): $(IN_DIR)/ss_task.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_task.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_task.c
$(OUT_DIR)/ss_timer.$(OBJ): $(IN_DIR)/ss_timer.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_timer.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_timer.c
$(OUT_DIR)/ss_tskent.$(OBJ): $(IN_DIR)/ss_tskent.c $(ALL_INC)
	$(CC) -c -o $(OUT_DIR)/ss_tskent.o $(COPTS) $(IOPTS) $(POPTS) \
	$(IN_DIR)/ss_tskent.c


#-------------------------------------------------------------#
# Compile rule             
#-------------------------------------------------------------#
$(OUT_DIR)/ssi:$(mtOBJS)
	$(AR) rcs $(LIB_DIR)/libssi.a $(mtOBJS)

#-------------------------------------------------------------#
# Clean macros             
#-------------------------------------------------------------#
clean:
	\rm -f $(mtOBJS)
