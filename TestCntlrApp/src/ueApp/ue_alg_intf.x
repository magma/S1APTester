#ifndef __UE_ALG_INTF_X__
#define __UE_ALG_INTF_X__ 1


/*Algorithm Interface*/
EXTERN Void ueAppEncSnow3GAlg ARGS((U8    *key, 
                                    U32    count, 
                                    U8     dir, 
                                    U8     bearer, 
                                    U8    *msg, 
                                    U16    len));

EXTERN Void ueAppEncNullAlg  ARGS((U8    *key, 
                                   U32    count, 
                                   U8     dir, 
                                   U8     bearer, 
                                   U8    *msg, 
                                   U16    len));

EXTERN Void ueAppEncAESAlg  ARGS((U8    *key,
                                   U32    count,
                                   U8     dir,
                                   U8     bearer,
                                   U8    *msg,
                                   U16    len));

EXTERN U32  ueAppIntSnow3GAlg ARGS((U8     *key, 
                                    U32     count, 
                                    U8      dir, 
                                    U8      bearer, 
                                    U8     *msg, 
                                    U16     len));

EXTERN U32  ueAppIntNullAlg ARGS((U8     *key, 
                                  U32     count, 
                                  U8      dir, 
                                  U8      bearer, 
                                  U8     *msg, 
                                  U16     len));

EXTERN U32  ueAppIntAESAlg ARGS((U8     *key,
                                  U32     count,
                                  U8      dir,
                                  U8      bearer,
                                  U8     *msg,
                                  U16     len));

EXTERN Void ueAppKeyGenAlg ARGS((U8    *key,
                                 U16   keyLen,
                                 U8    *s,
                                 U16   sLen,
                                 U8    *output,
                                 U16   outputLen));


EXTERN Void ueUsimAuthF2345 ARGS((U8    *k, 
                                 U8    *op, 
                                 U8    *rand, 
                                 U8    *res, 
                                 U8    *ck, 
                                 U8    *ik, 
                                 U8    *ak));

EXTERN Void ueUsimAuthF1 ARGS((U8    *k, 
                              U8    *op, 
                              U8    *rand, 
                              U8    *sqn, 
                              U8    *amf, 
                              U8    *mac));

EXTERN Void ueUsimAuthF1Star ARGS((U8    *k, 
                                  U8    *op, 
                                  U8    *rand, 
                                  U8    *sqn, 
                                  U8    *amf, 
                                  U8    *mac));

EXTERN Void ueUsimAuthF5Star ARGS((U8    *k, 
                                  U8    *op, 
                                  U8    *rand, 
                                  U8    *ak));

PUBLIC Void ueUsimXorAuthMac
(
U8    *k, 
U8    *rnd, 
U8    *sqn, 
U8    *amf, 
U8    *mac
);

PUBLIC Void ueUsimXorAuthVectors
(
U8    *k, 
U8    *rnd, 
U8    *res, 
U8    *ck, 
U8    *ik, 
U8    *ak
);

#endif /*__UE_ALG_INTF_X__*/
