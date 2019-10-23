
/********************************************************************20**

     Name:    SSI Memory Usage File

     Type:    CPP header file

     Desc:    Code for SSI memory wrapper for C++ classes.

     File:    SsiMem.h

     Sid:      SsiMem.h@@/main/1 - Fri Aug 29 19:50:49 2008

     Prg:     sv

*********************************************************************21*/


#ifndef __SSIMEMH__
#define __SSIMEMH__

/** @defgroup SSI_MEM The Trillium SSI Interface */
/** @ingroup SSI_MEM
 *  @class SsiMem 
 *  @brief This is a base class for using TAPA SSI memory management. 
 *  @details All the classes must inherit from this class, to use SSI memory
 *  It internally uses Region and Pool parameters initially set from the user for class objects which 
 *    require SSI usage.
 *  Application must initialize the static Mem field in this class (for region and pool fields), before creating the first new class of its interest. 
 *  It must use ssiSetMem static API for this purpose. 
 *  The same Mem field is then used by operator new and delete functions
 *  for accessing Region and Pool parameters.<br>
 *  The example for the usage of this class is found from below: @example swSdSsiMem.h.
 */


class SsiMem 
{

public:

#ifdef SSI_MEM

   /** @brief This operator overloads new operator for all generic scope class objects.
    *
    *  @details If there is a mismatch in passed size and expected size, as per class size, 
    *  function delegates the allocating functionality to default opeartor new to handle the same.
    *
    *  @param[in] size number of bytes to allocate the memory.
    *
    *  @return  Actual memory allocated if success for size, else throws exception accordingly.
    */
   Void * operator new (size_t size) throw (std::bad_alloc);

   /** @brief This operator overloads delete operator for all generic scope class objects.
    *
    *  @details If there is a mismatch in passed size and expected size, as per class size, 
    *  function delegates the allocating functionality to default opeartor delete to handle the same.
    *
    *  @param[in] delPtr The actual pointer intended to be deleted as void Type.
    *
    *  @param[in] size The size to delete which was previously allocated with new.
    *
    *  @exception std::badalloc If the memory for size cannot be allocated.
    *
    *  @return  none. deltPtr is nonNull if there is a failure during the processing.
    */
   Void  operator delete (Void *delPtr, size_t size) throw();

   /** @brief This operator overloads new[] operator for all generic scope class objects.
    *
    *  @details This function is invoked to allocate multiple blocks of same object type.
    *  If there is a mismatch in passed size and expected size, as per class size, 
    *  function delegates as runtime error.
    *
    *  @param[in] size number of bytes to to allocate the memory.
    *
    *  @exception std::badalloc If the memory for size cannot be allocated.
    *  @return  Actual memory allocated if success for size, else throws exception accordingly.
    */
   Void * operator new[] (size_t size) throw(std::bad_alloc);

   /** @brief This operator overloads delete[] operator for all generic scope class objects.
    *
    *  @details This function is invoked when multiple blocks of same object type were allocated before.
    *  If there is a mismatch in passed size and expected size, as per class size, 
    *  function delegates the allocating functionality to default opeartor delete to handle the same.
    *
    *  @param[in] delPtr The actual pointer intended to be deleted as void type.
    *
    *  @param[in] size The size to delete which was previously allocated with new[].
    *
    *  @return none. deltPtr is nonNull if there is a failure during the processing.
    */
   Void  operator delete[] (Void *delPtr, size_t size) throw(); 

#endif
 
   /** @brief This static function is used to set the Mem field.
    *  @details Service user must initialize the static Mem field in this class (for region and pool fields), 
    *  before creating the first new class of its interest. 
    *  The same Mem field is then used by new and delete functions for accessing Region and Pool parameters 
    *  with respect to SSI memory management.
    *  @param[in] inMem The constant pointer initialized with Region and Pool values.
    *  @return none. 
    */
   static Void ssiSetMem(const Mem *inMem);

   /** @brief This static function is used to get the Mem field.
    *  @details Incase if the service user wishes to use SSI memory management services, can use this API 
    *  to retrieve region and pool parameters' values. 
    *  @return Memory field as a constant structure[Mem].
    *  The same Mem is used by new and delete functions for accessing Region and Pool parameters 
    *  with respect to SSI memory management.
    */
   static const Mem ssiGetMem();
  
private:
   static Mem ssiMem;

};
#endif

/********************************************************************30**

         End of file:     SsiMem.h@@/main/1 - Fri Aug 29 19:50:49 2008

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
/main/1      ---      sv                1. Initial release.
*********************************************************************91*/
