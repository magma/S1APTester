
/********************************************************************20**

     Name:    SSI Memory Usage File

     Type:    CPP source file

     Desc:    Code for SSI memory wrapper for SDK

     File:    SsiMem.cpp

     Sid:      SsiMem.cpp@@/main/1 - Fri Aug 29 19:50:48 2008

     Prg:     sv

*********************************************************************21*/



/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#ifdef SS
#include "ss_err.h"            /* system services              */
#endif

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */


#ifdef SSI_MEM
 #include <new> 
#endif

#include "SsiMem.h"

Mem SsiMem::ssiMem = { 0 };

#ifdef SSI_MEM
Void * SsiMem::operator new(size_t size) throw (std::bad_alloc)
{
   Void *buffer = NULLP;
  
   TRC2(SsiMem::new);
 
   // SSI function call to get the memory here
   if (SGetSBuf(ssiMem.region, ssiMem.pool, (Data **) &buffer,(Size) size) == ROK)  
   {
      cmMemset((U8 *)(buffer), 0, size);   
   }
   else
   { 
#ifdef SS
      SSLOGERROR(ERRCLS_DEBUG, ESS648, ERRZERO, "Memory Allocation failed");
#endif
      (buffer) = NULLP;
      throw(std::bad_alloc()); // Inform the caller.
   }
   RETVALUE(buffer);

}

Void SsiMem::operator delete(Void *delPtr, size_t size) throw()
{
   TRC2(SsiMem::delete);
   if(NULLP != delPtr)
   {
      (Void) SPutSBuf(ssiMem.region, ssiMem.pool, (Data *) delPtr,  (Size) size);
   }
}

/* No need to catch the exceptions here. Inform the respective exception through throw.
   size input would be n*sizeof(class required) typical case. */

Void * SsiMem::operator new[](size_t size) throw(std::bad_alloc)
{
   Void *buffer = NULLP;

   TRC2(SsiMem::new[]);

   // SSI function call to get the memory here
   if (SGetSBuf(ssiMem.region, ssiMem.pool, (Data **)&buffer,(Size) size) == ROK)  
   {
      cmMemset((U8 *)(buffer), 0, size);   
   }
   else
   { 
#ifdef SS
      SSLOGERROR(ERRCLS_DEBUG, ESS648, ERRZERO, "Memory Allocation in blocks failed");
#endif
      (buffer) = NULLP;
      throw(std::bad_alloc()); // Inform the caller.
   }
   RETVALUE(buffer);
}

Void SsiMem::operator delete[](Void *delPtr, size_t size) throw()
{
   TRC2(SsiMem::delete[]);
   if(NULLP != delPtr)
   {
      (Void) SPutSBuf(ssiMem.region, ssiMem.pool, (Data *) delPtr,  (Size) size);
   }
}

#endif

Void SsiMem::ssiSetMem(const Mem *inMem)
{
   cmMemset ((U8 *)&(ssiMem), 0, sizeof (Mem));
   cmMemcpy ((U8 *)&(ssiMem), (U8 *)(const_cast<Mem *>(inMem)), sizeof (Mem));
}

const Mem SsiMem::ssiGetMem()
{
   TRC2(SsiMem::ssiGetMem);
   RETVALUE(ssiMem);
} 



/********************************************************************30**

         End of file:     SsiMem.cpp@@/main/1 - Fri Aug 29 19:50:48 2008

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
------------ -------- ---- ----------------------------------------------
/main/1      ---     sv                1. Initial release.
*********************************************************************91*/

