/*---------------------------------------------------------
* snow_3g.h
*---------------------------------------------------------*/
#ifndef __SNOW_3G__
#define __SNOW_3G__ 1

typedef unsigned char u8;
typedef unsigned int u32;

/* Initialization.
* Input k[4]: Four 32-bit words making up 128-bit key.
* Input IV[4]: Four 32-bit words making 128-bit initialization variable.
* Output: All the LFSRs and FSM are initialized for key generation.
* See Section 4.1.
*/
void Initialize(u32 k[4], u32 IV[4]);

/* Generation of Keystream.
* input n: number of 32-bit words of keystream.
* input z: space for the generated keystream, assumes
* memory is allocated already.
* output: generated keystream which is filled in z
* See section 4.2.
*/
void GenerateKeystream(u32 n, u32 *z);

#endif
