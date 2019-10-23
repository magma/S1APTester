
/********************************************************************20**
  
     Name:     system services - portable service provider
  
     Type:     CPP source file
  
     Desc:     Prototype CPP source code for the System Service
               service provider primitives that must be supplied
               by the customer.
  
     File:     ss_ptsp.cpp
  
     Sid:      ssmem_ptsp.cpp@@/main/1 - Fri Aug 29 20:18:13 2008
   
     Prg:      sv
  
*********************************************************************21*/
  

/*
  
System services are the functions required by the protocol
layer for buffer management, timer management, date/time
management, resource checking and initialization.

The following functions are provided in this file for the
system services service user with the help of SsiMem class:

     SsiMem::operator new  Operator overloading of new for all generic scope class objects.
     SsiMem::operator delete Operator overloading of delete for all generic scope class objects.
     SsiMem::operator new[]  Operator overloading of new[] for all generic scope class objects.
     SsiMem::operator delete[] Operator overloading of delete[] for all generic scope class objects.

It should be noted that not all of these functions may be required
by a particular system services service user.

*     This software may be combined with the following TRILLIUM
*     software:
*
*     part no.      description
*     --------    ----------------------------------------------
*     1000358     The Trillium SIP SDK.
*
*/
 

/* header include files (.h) */
  
#include "envopt.h"        /* environment options */  
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */
  
/* header/extern include files (.x) */
  
#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */

#ifdef SSI_MEM
 #include <new> 
#endif

#include "SsiMem.h"


/* local defines */
  
/* local typedefs */
  
/* local externs */
  
/* forward references */
  
/* functions in other modules */
  
/* public variable declarations */

/* private variable declarations */
  

/*
*     interface functions to system services service user
*/
 

#ifdef SSI_MEM
Void * SsiMem::operator new(size_t size) throw (std::bad_alloc)
{
  
   TRC2(SsiMem::new);
 
   // SSI function call to get the memory here
   RETVALUE(NULLP);

}

Void SsiMem::operator delete(Void *delPtr, size_t size) throw()
{
   TRC2(SsiMem::delete);
   RETVOID;
}

Void * SsiMem::operator new[](size_t size) throw(std::bad_alloc)
{
   TRC2(SsiMem::new[]);
   RETVALUE(NULLP);
}

Void SsiMem::operator delete[](Void *delPtr, size_t size) throw()
{
   TRC2(SsiMem::delete[]);
   RETVOID;
}

#endif

Void SsiMem::ssiSetMem(const Mem *inMem)
{
   TRC2(SsiMem::ssiSetMem);
   RETVOID;
}

const Mem SsiMem::ssiGetMem()
{
   Mem locMem;
   
   TRC2(SsiMem::ssiGetMem);
   RETVALUE(locMem);
} 



/********************************************************************30**
  
         End of file:     ssmem_ptsp.cpp@@/main/1 - Fri Aug 29 20:18:13 2008
  
*********************************************************************31*/
  

/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

 
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************70**
********************************************************************90**
  
  version    initials                   description
-----------  ---------  ------------------------------------------------
/main/1      ---     sv                1. Initial release.
*********************************************************************91*/
