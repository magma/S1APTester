/*------------------------------------------------------------------------
* snow3g_f8f9.c
*------------------------------------------------------------------------*/
/* system include */
#include "math.h"
#include "malloc.h"

/* non system include */
#include "snow_3g.h"
double ceil(double x);
/*------------------------------------------------------------------------*/


u32 mask32bit(int n)
{
   u32 mask=0x0;
   if ( n%32 == 0 )
      return 0xffffffff;
   while (n--)
      mask = (mask>>1) ^ 0x80000000;
   return mask;
}



void XORx64(u32 *V1,u32 *V2,u32 c1,u32 c2)
{
    *V1 = *V1^c1;
    *V2 = *V2^c2;
}

void XORx64Eval(u32 *V1,u32 *V2,u32 EVAL1,u32 EVAL2,u32 c1,u32 c2)
{
   *V1 = EVAL1 ^ c1;
   *V2 = EVAL2 ^ c2;
}


void SHIFT64x1(u32 *V1,u32 *V2)
{
   u32 bit32 = 0x00;
   if(*V2 & 0x80000000)
      bit32 = 0x01; 
   *V2 = *V2<<1; 
   *V1 = *V1<<1;    
   *V1 = *V1 | bit32;
}

void MUL64x(u32 *V1,u32 *V2, u32 c1,u32 c2)
{
   if(*V1 & 0x80000000)
   {
      SHIFT64x1(V1,V2);
      XORx64(V1,V2,c1,c2);
   }
   else
   {
      SHIFT64x1(V1,V2);
   }
}


void MUL64xPOW(u32 *O1,u32 *O2,u32 V1,u32 V2,u8 i,u32 c1,u32 c2)
{
   if(i == 0)
   {
      *O1 = V1;
      *O2 = V2;
      return; 
   }
   else
   {
      MUL64xPOW(O1,O2,V1,V2,i-1,c1,c2); 
      MUL64x( O1,O2, c1,c2);
   }
}




void MUL64(u32 *EVAL1,u32 *EVAL2,u32 V1,u32 V2,u32 P1,u32 P2,u32 c1,u32 c2)
{

   int i = 0;
   u32 O1 = 0,O2 = 0;
   *EVAL1 = 0;
   *EVAL2 = 0;

   for ( i=0; i<64; i++)
   {

      if(i<=31)
      {
         if( ( P2>>i ) & 0x1 )
         {
            MUL64xPOW(&O1,&O2,V1,V2,i,c1,c2);
            XORx64(EVAL1,EVAL2,O1,O2);
         }
      }
      else
      {
         if( ( P1>>(i-32) ) & 0x1 )
         {
            MUL64xPOW(&O1,&O2,V1,V2,i,c1,c2);
            XORx64(EVAL1,EVAL2,O1,O2);
         }
      }
   }
}



u32 convertToNwOrder(u8* bytes)
{
   u32 networkOrder = 0;
   int i = 0;
   for(i = 0;i<4;i++)
   {
      if((bytes+i) != NULL)
      {
         if(i)
           networkOrder = (networkOrder<<(8))|((u8)bytes[i]&0xFF);
         else
           networkOrder = networkOrder|((u8)bytes[i]&0xFF);
      }
      else
      {
         if(i)
           networkOrder = (networkOrder<<(8))|((u8)0x00);
         else
           networkOrder = networkOrder|((u8)0x00);
      }
   }
   return networkOrder;
}

void convertToHostOrder(u32 u32num,u8* hostOrder)
{
   int i = 0;
   hostOrder[0] = 0x00;
   hostOrder[1] = 0x00;
   hostOrder[2] = 0x00;
   hostOrder[3] = 0x00;   
   for(i = 0;i<4;i++)
   {
      hostOrder[3-i] = ((u32num>>(i*8))&0xFF);
   }
}


void f8Snow3g( u8 *key, u32 count, u32 bearer, u32 dir, u8 *data, u32 length )
{
   u32 K[4],IV[4];
   int n = ( length + 31 ) / 32;
   u8 keyStream[4];
   int i = 0;

   u32 *KS;

   /*Initialisation*/
   /* Load the confidentiality key for SNOW 3G initialization as in section 3.4. */

   /*Network order conversion*/
   K[3] = convertToNwOrder((u8*)(key+0) );
   K[2] = convertToNwOrder((u8*)(key+4));
   K[1] = convertToNwOrder((u8*)(key+8));
   K[0] = convertToNwOrder((u8*)(key+12));
 
   /* Prepare the initialization vector (IV) for SNOW 3G initialization as in
   section 3.4. */
 
   IV[3] = count;
   IV[2] = (bearer << 27) | ((dir & 0x1) << 26);
   IV[1] = IV[3];
   IV[0] = IV[2];
 
   /* Run SNOW 3G algorithm to generate sequence of key stream bits KS*/
   Initialize(K,IV);
   KS = (u32 *)malloc(4*n);
   GenerateKeystream(n,(u32*)KS);
 
   /* Exclusive-OR the input data with keystream to generate the output bit
   stream */
   
   /*Network order conversion */
   for (i=0;i<(int)ceil(length/8.0);i++)
   {
       if((i%4) == 0)
       {
           convertToHostOrder(*(KS+(i/4)),keyStream);
       }
       data[i]^=keyStream[i%4]; 
   }
 
   free(KS);
}
 

u32 f9Snow3g( u8 *key, u32 count, u32 fresh, u32 dir, u8 *data, u32 length )
{
  u32 K[4],IV[4], z[5];
  int i=0,D;
  static u32 MAC_I = 0; /* static memory for the result */
  
  u32 EVAL1;
  u32 EVAL2;
  u32 V1;
  u32 V2;
  u32 P1;
  u32 P2;
  u32 Q1;
  u32 Q2;
  u32 c1;
  u32 c2;
  u32 M_D_2_1;
  u32 M_D_2_2;
 
  u32 length1 = 0x00;
  u32 length2 = (u32)length;
 
  int rem_bits = 0;
  u32 mask = 0;
  u32 *message;
 
 
 
  message = (u32*)data; 
  
  /* To operate 32 bit message internally. */
  /* Load the Integrity Key for SNOW3G initialization as in section 4.4. */
 
  /*Network order conversion*/
  K[3] = convertToNwOrder((u8*)(key+0) );
  K[2] = convertToNwOrder((u8*)(key+4));
  K[1] = convertToNwOrder((u8*)(key+8));
  K[0] = convertToNwOrder((u8*)(key+12));
 
 
  /* Prepare the Initialization Vector (IV) for SNOW3G initialization as in
  section 4.4. */
  IV[3] = count;
  IV[2] = fresh;
  IV[1] = count ^ ( dir << 31 ) ;
  IV[0] = fresh ^ (dir << 15);
  z[0] = z[1] = z[2] = z[3] = z[4] = 0;
 /* Run SNOW 3G to produce 5 keystream words z_1, z_2, z_3, z_4 and z_5. */
 
 
  Initialize(K,IV);
  GenerateKeystream(5,z);
 

  P1 = z[0];
  P2 = z[1];
  Q1 = z[2];
  Q2 = z[3];
 
  
   /* Calculation */
   D = (int)ceil( length2 / 64.0 ) + 1;
 
   EVAL1 = 0;
   EVAL2 = 0;
   c1 = 0x00;
   c2 = 0x1b;
   M_D_2_1 =0;
   M_D_2_2 =0;
 
   for (i=0;i<D-2;i++)
   {
      V1 = 0;
      V2 = 0;
      XORx64Eval(&V1, &V2, EVAL1, EVAL2, convertToNwOrder((u8*)&message[2*i]), convertToNwOrder((u8*)&message[2*i+1])) ;
      MUL64(&EVAL1, &EVAL2, V1, V2, P1, P2, c1, c2);
   } 
 

   /* for D-2 */
   rem_bits = length2 % 64;
   if (rem_bits == 0)
      rem_bits = 64;
 
   mask = mask32bit(rem_bits%32);
   if (rem_bits > 32)
   {
      M_D_2_1 = convertToNwOrder((u8*)&message[2*(D-2)]);
      M_D_2_2 = convertToNwOrder((u8*)&message[2*(D-2)+1]) &mask;
   } else
   {
      M_D_2_1 = convertToNwOrder((u8*)&message[2*(D-2)]) & mask;
      M_D_2_2 = 0x00000000;
   }

   V1 = 0;
   V2 = 0;
   XORx64Eval(&V1, &V2, EVAL1, EVAL2, M_D_2_1, M_D_2_2);
   MUL64(&EVAL1, &EVAL2, V1, V2, P1, P2, c1, c2);
 
   XORx64(&EVAL1, &EVAL2, length1, length2);
   MUL64(&EVAL1, &EVAL2, EVAL1, EVAL2, Q1, Q2, c1, c2);
 
   MAC_I = (u32)(EVAL1) ^ z[4];
   return MAC_I;
}

