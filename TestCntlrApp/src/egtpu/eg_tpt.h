
/********************************************************************20**

     Name:    EGTP - Transport Module

     Type:    C source file

     Desc:    This file contains hash defines, enum etc
              used in Transport Module.

     File:    eg_tpt.h

     Sid:      eg_tpt.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:50 2015

     Prg:     ad 

*********************************************************************21*/
#ifndef __EG_TPT_H__
#define __EG_TPT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Max No. of Hash Bin */
#define EG_MAX_NUM_HASHBIN_SEQNO    500


#ifdef NOT_USED
/* This will check whether MSB is set in SeQ No. or Not */
#define EG_IS_MSB_SET_IN_SEQ_NO(_seqNo, _isMsbSet)     \
{\
   U16 msb = 1;                                       \
   U16 tmp = 0;                                       \
                                                      \
   (_isMsbSet) = FALSE;                               \
   msb = msb << 23;                                    \
   tmp = msb & _seqNo;                                 \
                                                      \
   tmp = tmp >> 23;                                    \
                                                      \
   if (tmp == 1)                                      \
      (_isMsbSet) = TRUE;                              \
}
#define EG_EXAM_U32(_param, _mBuf, _count) \
{ \
   U16   nwWord[EG_LEN_TWO]; \
   U32   tmpU32 = 0; \
   U16   tmpCnt = _count; \
   nwWord[0] = 0; nwWord[1] = 0; \
   EG_EXAM_U16(nwWord[0], _mBuf, tmpCnt); \
   tmpCnt = tmpCnt + 2;\
   EG_EXAM_U16(nwWord[1], _mBuf, tmpCnt); \
   tmpU32 = PutHiWord(tmpU32, nwWord[0]); \
   tmpU32 = PutLoWord(tmpU32, nwWord[1]); \
   _param = tmpU32; \
}

#endif /* NOT_USED */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __EG_TPT_H__ */



   


/********************************************************************30**

         End of file:     eg_tpt.h@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:50 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad                1. Created for Initial Release 1.1
/main/2      ---      rsharon           1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla       Initial Release of eGTP 2.1 release
*********************************************************************91*/
