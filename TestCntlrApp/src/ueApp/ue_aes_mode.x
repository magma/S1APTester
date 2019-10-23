
/********************************************************************20**

     Name:    Trillium - AES Mode Module

     Type:    C source file

     Desc:    This file contains AES mode module c structure

     File:    ue_aes_mode.x

     Sid:     ue_aes_mode.x@@/main/1 - Mon Jun 01 19:35:38 2012

     Prg:     sk 
*********************************************************************21*/

#ifndef __UE_AES_MODE_X__
#define __UE_AES_MODE_X__


PUBLIC S16 ueAESCTR ARGS(( U8    *key,
                          U16   bitKeyLen,
                          U8    *counterBlk,
                          U16   bitCounterBlkLen,
                          U8    *data,
                          U32   bitDataLen 
                       ));

PUBLIC U16 ueAESCMAC ARGS((U8    *key,
                           U8    bitKeyLen, /* Bits Len */
                           U8    *data,
                           U16   bitDataLen, /* Bits Len */
                           U8    *mac,
                           U8    byteMacLen
                           ));

#endif
