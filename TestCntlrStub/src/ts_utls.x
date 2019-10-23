
/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for S1SIM Test Controller

     File:     ts_utls.x

     Prg:      

**********************************************************************/
#define TRUE  1
#define FALSE 0

#define TEST_TYPE_SERVICE_REQUEST 0
#define TEST_TYPE_SERVICE_REJECT  1
#define TEST_TYPE_PAGING          2

#define TEST_TYPE_TAU_REQUEST     0
#define TEST_TYPE_TAU_REJECT      1

extern char videoSrvrIp[];

typedef struct _msgbuf
{
   long msgType;
   long msgLen;
   char msg[BUFSIZE];
}MsgBuf;

typedef struct _tsErabList
{
   int numOfBrs;
   unsigned char *brLst;
}tsErabLst;

extern tsErabLst ueErabInfo[];

typedef struct _ueIpInfo
{
  unsigned char UeIpAdrLst[11][4];
  unsigned char noIfAssinedIps; 
}UeIpInfo;

typedef struct _ueDedBerInfo
{
  unsigned char ueId;
  unsigned char dedBerIdLst[10];
  unsigned char noOfDedBer; 
}UeDedBerInfo;


int testUeInitiatedDedBerReq(unsigned char ueId);
int testActvDedBerRejWithIvalidEpsBerId(unsigned char ueId);
int s1SetUpReq(int result);

void tsUeConfig(unsigned char, unsigned char*, int imsiLen);
void tsUeAppConfig(void);
void tsEnbConfig(void);
void testUePdnConnReq(unsigned char ueId);
void testUePdnConnReqAndData(unsigned char ueId);
void testUePdnConnRej(unsigned char ueId);
void tsStepByStepAttachWithImsi(unsigned char);
void tsStepByStepAttachWithGuti(unsigned char);
void tsStepByStepReAttach(unsigned char);
void tsStepByStepAttachWithIdProc(unsigned char);
void tsAttach_PCO_DRX(unsigned char);
void tsCompleteAttach(unsigned char);
void tsAttachEmergency(unsigned char);
void tsReadImsiAndSendUeConfig(int);
void SyncFailureWithWrapARound(unsigned char ueId);
void SyncFailureWithAgeLimit(unsigned char ueId);
void SyncFailureWithDelta(unsigned char ueId);
void tsAuthFailAMF(unsigned char ueId);
void tsAttachWithSecModeReject(unsigned char);
void testErrIndMsg(unsigned char ueId);
void tsAttachWithAUTV(unsigned char);
void TC_API(short int, void *, short int);
int TC_msg_recv(int, int);

void trf_test_init(void);

void tsSendAttachRequest(unsigned char);
int tsSendServiceRequest(unsigned char, unsigned char);
void tsSendDetachRequest(unsigned char, unsigned char, Ue_Mode);
void tsStartPeriodicTauTimer(unsigned char, unsigned char);
void tsSendTauRequest(unsigned char, char*, unsigned char, unsigned char);
int tsSendUeCntxtReleaseRequest(unsigned char, unsigned char);
int tsSendUeRadCapUpdReq(U8 ueId, U8 * msg, U8 len, Bool sndS1AP  );

void tsCleanup(void);
void tsStartUlData(unsigned char);
void tsStartDlData(unsigned char);
void deleteCfgdUeIps(unsigned char);
int tsSendPdnConnReq(uepdnConReq_t *pdnConReq);
void testAttachAndUlData(unsigned char);
void testAttachAndDlData(unsigned char);
void testDetachiWithCauseSwitchOff(unsigned char);
void testDetachiWithCauseNormal(unsigned char);
int testServiceRequest(unsigned char);
int testServiceRequestAndData(unsigned char);
int testServiceRequestReject(unsigned char);
int testPeriodicTauRequest(unsigned char);
int testPeriodicTauRequestReject(unsigned char);
int testNormalTauRequest(unsigned char);
int testNormalTauRequestWithActFlag(unsigned char);
void testUeCntxtRelRequest(unsigned char);
void testUeRadCapModReq(unsigned char ueId);
int testNormalPaging(unsigned char);
int testTimeoutPaging(unsigned char);
int testNwInitDetach(unsigned char );
void tsSendDetachAccept(unsigned char);
void flush(int);
void tsSendErrIndMsg(void *msgptr);
void testErrIndWithIvalidUeS1apIds(unsigned char);
int tsSendResetReq(unsigned int resetType, int numOfUes, unsigned char *ueLst);
int tsSendErabRelReq(unsigned char, unsigned char, unsigned char*);
void tsAttach_tau_detach(unsigned char nUE, unsigned char nTAUReq);
void testNasNonDelivery(unsigned char ueId);
void testInitialContextSetupFailure(unsigned char ueId);
void testInitialContextSetupUeCtxtRelReq(unsigned char ueId);
void testInitialContextSetupDelayRsp(unsigned char ueId);
void testInitialContextSetupDrop(unsigned char ueId);
int testServiceRequest1(unsigned char ueId);
extern char noTauComplete;
extern char requestedIdType;
extern int T3412;
extern int msgQid;
#if 0
extern unsigned char UeIpAdrLst[16][4];
#endif
extern UeIpInfo UeIpInfoLst[];
extern UeDedBerInfo UeDedBerLst[];
