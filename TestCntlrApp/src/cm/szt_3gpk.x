
/***********************************************************************

************************************************************************

     Name: S1AP Layer

     Type: C Soruce code File

     Desc: Primitives for szt interface

     File: szt_pk.x

     Sid:      

     Prg: akaranth 

***********************************************************************/

/*  szt_3gpk_x_001.main_1 :Support for Source RNC to Target RNC TC Enc/Dec. */

EXTERN S16 cmPkSztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs ARGS ((SztProtExtnField_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs ARGS (( SztProtExtnCont_SrcRNC_ToTgetRNC_TprntCont_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnTrCH_ID_ExtIEsCls ARGS ((Szt_ExtnTrCH_ID_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_TrCH_ID_ExtIEs ARGS ((SztProtExtnField_TrCH_ID_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_TrCH_ID_ExtIEs ARGS ((SztProtExtnCont_TrCH_ID_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztTrCH_ID ARGS ((SztTrCH_ID *param, Buffer *mBuf));
EXTERN S16 cmPkSztTrCH_ID_Lst ARGS ((SztTrCH_ID_Lst *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs ARGS ((SztProtExtnCont_RAB_TrCH_MappingItem_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztRAB_TrCH_MappingItem ARGS ((SztRAB_TrCH_MappingItem *param, Buffer *mBuf));
EXTERN S16 cmPkSztRAB_TrCH_Mapping ARGS ((SztRAB_TrCH_Mapping *param, Buffer *mBuf ));
EXTERN S16 cmPkSztSrcRNC_ToTgetRNC_TprntCont ARGS ((SztSrcRNC_ToTgetRNC_TprntCont_3gasn *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls ARGS ((Szt_ExtnTgetRNC_ToSrcRNC_TprntCont_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs ARGS ((SztProtExtnField_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs ARGS ((SztProtExtnCont_TgetRNC_ToSrcRNC_TprntCont_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztTgetRNC_ToSrcRNC_TprntCont ARGS ((SztTgetRNC_ToSrcRNC_TprntCont_3gasn *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnSRB_TrCH_MappingItem_ExtIEsCls ARGS ((Szt_ExtnSRB_TrCH_MappingItem_ExtIEsCls *param, U32 val, Buffer *mBuf ));
EXTERN S16 cmPkSztProtExtnField_SRB_TrCH_MappingItem_ExtIEs ARGS ((SztProtExtnField_SRB_TrCH_MappingItem_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs ARGS ((SztProtExtnCont_SRB_TrCH_MappingItem_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztSRB_TrCH_MappingItem ARGS ((SztSRB_TrCH_MappingItem *param, Buffer *mBuf));
EXTERN S16 cmPkSztSRB_TrCH_Mapping ARGS ((SztSRB_TrCH_Mapping *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnCellLoadInformGroup_ExtIEsCls ARGS ((Szt_ExtnCellLoadInformGroup_ExtIEsCls *param, U32 val, Buffer *mBuf ));
EXTERN S16 cmPkSztProtExtnField_CellLoadInformGroup_ExtIEs ARGS ((SztProtExtnField_CellLoadInformGroup_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztProtExtnCont_CellLoadInformGroup_ExtIEs ARGS ((SztProtExtnCont_CellLoadInformGroup_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnCellLoadInform_ExtIEsCls ARGS ((Szt_ExtnCellLoadInform_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_CellLoadInform_ExtIEs ARGS ((SztProtExtnField_CellLoadInform_ExtIEs *param,  Buffer *mBuf ));
EXTERN S16 cmPkSztProtExtnCont_CellLoadInform_ExtIEs ARGS ((SztProtExtnCont_CellLoadInform_ExtIEs *param, Buffer *mBuf ));
EXTERN S16 cmPkSztCellLoadInform ARGS ((SztCellLoadInform *param, Buffer *mBuf));
EXTERN S16 cmPkSzt3g_ExtnCGI_ExtIEsCls ARGS ((Szt3g_ExtnCGI_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSzt3gProtExtnField_CGI_ExtIEs ARGS ((Szt3gProtExtnField_CGI_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSzt3g_ExtnCGI_ExtIEsCls ARGS ((Szt3g_ExtnCGI_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSzt3gProtExtnCont_CGI_ExtIEs ARGS ((Szt3gProtExtnCont_CGI_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSzt3gCGI ARGS ((Szt3gCGI *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnSrcUTRANCellID_ExtIEsCls ARGS ((Szt_ExtnSrcUTRANCellID_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_SrcUTRANCellID_ExtIEs ARGS ((SztProtExtnField_SrcUTRANCellID_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_SrcUTRANCellID_ExtIEs ARGS ((SztProtExtnCont_SrcUTRANCellID_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztSrcUTRANCellID ARGS ((SztSrcUTRANCellID *param, Buffer *mBuf));
EXTERN S16 cmPkSztSrcCellID ARGS ((SztSrcCellID *param, Buffer *mBuf));
EXTERN S16 cmPkSztCellLoadInformGroup ARGS ((SztCellLoadInformGroup *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnTraceRecordingSessionInform_ExtIEsCls ARGS ((Szt_ExtnTraceRecordingSessionInform_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_TraceRecordingSessionInform_ExtIEs ARGS ((SztProtExtnField_TraceRecordingSessionInform_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_TraceRecordingSessionInform_ExtIEs ARGS ((SztProtExtnCont_TraceRecordingSessionInform_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztTraceRecordingSessionInform ARGS ((SztTraceRecordingSessionInform *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnSRVCC_Inform_ExtIEsCls ARGS ((Szt_ExtnSRVCC_Inform_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_SRVCC_Inform_ExtIEs ARGS ((SztProtExtnField_SRVCC_Inform_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnCont_SRVCC_Inform_ExtIEs ARGS ((SztProtExtnCont_SRVCC_Inform_ExtIEs *param, Buffer *mBuf));
EXTERN S16 cmPkSztSRVCC_Inform ARGS ((SztSRVCC_Inform *param, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls ARGS ((Szt_ExtnSrcRNC_ToTgetRNC_TprntCont_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSzt_ExtnRAB_TrCH_MappingItem_ExtIEsCls ARGS ((Szt_ExtnRAB_TrCH_MappingItem_ExtIEsCls *param, U32 val, Buffer *mBuf));
EXTERN S16 cmPkSztProtExtnField_RAB_TrCH_MappingItem_ExtIEs ARGS ((SztProtExtnField_RAB_TrCH_MappingItem_ExtIEs *param, Buffer *mBuf));


/**********************************************************************
 
         End of file:     szt_3gpk.x

**********************************************************************/

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
------------ -------- ---- ----------------------------------------------
  $SID$    szt_3gpk_x_001.main_1  akaranth 1. Support for Source RNC to Target RNC TC Enc/Dec.

*********************************************************************91*/
