
/********************************************************************20**

     Name:    SSI Memory Usage Allocator File

     Type:    CPP header file

     Desc:    Code for SSI memory wrapper

     File:    SsiAlloc.h

     Sid:      SsiAlloc.h@@/main/1 - Fri Aug 29 19:50:49 2008

     Prg:     sv

*********************************************************************21*/



#ifndef __SS_ALLOCH__
#define __SS_ALLOCH__

#ifdef SSI_MEM
#include <new>
#include "SsiMem.h"

#include <memory>
#include <exception> 

/** @ingroup SSI_MEM
 *  @class SsiAllocator.
 *  @brief This is a template class TAPA SSI allocator for using C++ STL library and C++ strings.
 *  @details All the SIP SDK scope classes must use this allocator, to use SSI memory allocation/deallocation.
 *  It invokes SsiMem new and delete operators to make extensive use of SSI memory allocation/deallocation 
 *  for STL library container elements.
 *  Application must initialize the static Mem field in this class (for region and pool fields), 
 *  before creating the first new class of SDK scope or the class of its interest. 
 *    @note This class inherits SsiMem class for overloaded operations of new and delete in order to use TAPA SSI.
 *  The example for the usage of this class is found from below: @example swSdSsiAlloc.h.
 */

template<class T>
class SsiAllocator : virtual public SsiMem 
{

public:

   /// Unsigned integral value that represents the size of the largest object in the memory model.
    typedef size_t size_type;

   /// Represents the difference between the two pointers.
    typedef ptrdiff_t difference_type;

   /// Type of a pointer to the element type being used in the memory model. 
   /// If the allocator is used with STL containers, this type must be 
   /// equivalent to 'T*' for allocator<T>.   
    typedef T *pointer;

   /// Type of a constant pointer to the element type being used in the memory model.
   ///  If the allocator is used with STL containers, this type must be 
   ///  equivalent to 'const T*' for allocator<T>.
    typedef const T *const_pointer;

   /// Type of a reference to the element type being used in the memory model.
   /// If the allocator is used with STL containers, this type must be 
   /// equivalent to 'T&' for allocator<T>.
    typedef T& reference;

   /** Type of a constant reference to the element type being used in the memory model.
    * If the allocator is used with STL containers, this type must be 
    * equivalent to 'const T&' for allocator<T>.
    */
    typedef const T& const_reference;

    /// Type of the element that is used in this memory model.
    typedef T value_type;

    /** @brief This function returns a pointer to the value r.
     *  @param[in] r Reference to the element type used in the memory model.
     *  @return The pointer to the element type used in the memory model. 
     */
    pointer address(reference r) const
    {
       return &r;
    }

    /** @brief This function returns a constant pointer to the value r.
     *  @param[in] r The constant reference to the element type used in the memory model.
     *  @return The constant pointer to the element type used in the memory model. 
     */
    const_pointer address(const_reference r) const
    {
       return &r;
    }

    /// A template structure, which allows any allocator can allocate memory of another type indirectly.
    template<class U> struct rebind
    {
       typedef SsiAllocator <U> other;
    };

   /// @brief This is a default constructor.
    SsiAllocator()
    {
       // Nothing to do
    }

   /** @brief This is a copy constructor from the same class type.
    *  @details It copies an allocator, so that storage allocated by the original can be
    * released by the copy and vice-versa.
    */
    SsiAllocator(const SsiAllocator<T>& x)
    {

    }

   /** @brief This is a copy constructor from other class type.    
    *  @details It copies an allocator, so that storage allocated by the original can be
    * released by the copy and vice-versa.
    */
    template<class U> 
    SsiAllocator(const SsiAllocator<U>& x)
    {

    }

   /** @brief This function is a operator assignment(=) overloaded.
    *  @details It assigns an allocator, so that storage allocated by the original can be
    *  released by the copy and vice-versa.
    */
   template<class U> 
   SsiAllocator& operator=(const SsiAllocator<U>& x)
   {
      TRC2(SsiAllocator::operator=);
      RETVALUE(*this);
   }

   /** @brief This function returns storage for n elements of the element type T used in the memory model.
       @details The elements are not constructed/initialized.
       @param[in] n The number of elements to allocate memory as size_type.
       @return The pointer to allocated memory as pointer.
    */
   pointer allocate(size_type n)
   {
      TRC2(SsiAllocator::allocate);
      // SSI function to allocator memory here
      pointer p = NULL;
      try
      {
         p = static_cast<pointer>( SsiMem::operator new(n*sizeof(T)));
      }
      catch(std::exception &e) // Catch all standard exceptions here
      {
         p = NULL; 
         throw; // Inform the caller.
      }
      RETVALUE(p);
   }

   /** @brief This function deallocates the storage for n elements of the element type T
    *   used in the memory model, beginning at location p.
    *  @details The storage must have been allocated by the same or any equal allocator. 
    *  This function doesnt destroy the n objects of element type T.
    *  Elements must have been destroyed before.
    *  @param[in] p The pointer to deallocate the space from.p must not be 0.
    *  @param[in] n The number of elements using which memory was allocated before for type T.
    *  n must be the same value as it was while calling allocate(). 
   */   
   void deallocate(pointer p, size_type n)
   {
      // SSI function to deallocate memory here
      SsiMem::operator delete(p, (n*sizeof(T)));
   }

   /** @brief This function initializes the storage of the element type T, pointed to by p, with the value val.
    *  @details The storage must have been allocated by a call to allocate().
    *  @param[in] p The pointer to construct the object for, with element type T.
    *  @param[in] val The constant reference to value of type T. 
    */
   void construct(pointer p, const T& val)
   {
      new((void *)p) T(val); // Invoke the constructor of it
   }

   /** @brief This function destroys the element, pointed to by p, without deallocating the storage.
    *  @param[in] p The pointer to the element type T, to destroy.
    */
   void destroy(pointer p)
   {
      ((T *)p)->~T(); // Invoke destructor , do not deallocate 
   }

   /** @brief Returns the largest value which is passed to the 'allocate()' function.
    *  @details The maximum size for the allocate(), as size_type.
   */
   size_type max_size() const
   {
      TRC2(SsiAllocator::max_size);
      size_type maxSize = (size_type)(-1) / sizeof(T);
      RETVALUE (0 < maxSize ? maxSize:1);
   }

};

/** @brief This is an == operator overloaded.
    @details It returns true if storage allocated by allocator a1 can be deallocated by allocator a2 and vice-versa.
    If the allocator is used with STL containers, this is required. 
    Thus, this function always return true.
    @param[in] ssAlloc1 The allocator for element type T1, of SsiAllocator.
    @param[in] ssAlloc2 The allocator for element type T2, of SsiAllocator.
    @return 
      - TRUE if storage allocated by allocator ssAlloc1 can be deallocated by allocator ssAlloc2 and vice-versa.
      - FALSE otherwise.
 */  
 
template <class T1, class T2>
bool operator==(const SsiAllocator<T1>& ssAlloc1, const SsiAllocator<T2>& ssAlloc2) throw()
{
    TRC2(SsiAlloc::operator==);
   RETVALUE(1);
}

/** @brief This is an operator != overloaded.
    @details It returns true if storage allocated by allocator a1 cannot be deallocated by allocator a2 and vice-versa.
    If the allocator is used with STL containers, the opposite of this is required. 
    Thus, this function always return false.
    @param[in] ssAlloc1 The allocator for element type T1, of SsiAllocator.
    @param[in] ssAlloc2 The allocator for element type T2, of SsiAllocator.
    @return 
      - TRUE if storage allocated by allocator ssAlloc1 cannot be deallocated by allocator ssAlloc2 and vice-versa.
      - FALSE otherwise.
 */
template <class T1, class T2>
bool operator!=(const SsiAllocator<T1>&ssAlloc1, const SsiAllocator<T2>& ssAlloc2) throw()
{
   TRC2(SsiAlloc::operator!=);
   RETVALUE(0);
}

/** @brief This is an == operator overloaded.
    @details It returns true if storage allocated by allocator a1 can be deallocated by allocator a2 and vice-versa.
    If the allocator is used with STL containers, this is required. 
    Thus, this function always return true.
    @param[in] ssAlloc1 The allocator for element type T, of SsiAllocator.
    @param[in] ssAlloc2 The allocator for element type T, of SsiAllocator.
    @return 
      - TRUE if storage allocated by allocator ssAlloc1 can be deallocated by allocator ssAlloc2 and vice-versa.
      - FALSE otherwise.
 */  
template <class T>
bool operator==(const SsiAllocator<T>&ssAlloc1, const SsiAllocator<T>&ssAlloc2) throw()
{
   TRC2(SsiAlloc::operator==);
   RETVALUE(1);
}


/** @brief This is an operator != overloaded.
    @details It returns true if storage allocated by allocator a1 cannot be deallocated by allocator a2 and vice-versa.
    If the allocator is used with STL containers, the opposite of this is required. 
    Thus, this function always return false.
    @param[in] ssAlloc1 The allocator for element type T, of SsiAllocator.
    @param[in] ssAlloc2 The allocator for element type T, of SsiAllocator.
    @return 
      - TRUE if storage allocated by allocator ssAlloc1 cannot be deallocated by allocator ssAlloc2 and vice-versa.
      - FALSE otherwise.
 */
template <class T>
bool operator!=(const SsiAllocator<T>&ssAlloc1, const SsiAllocator<T>&ssAlloc2) throw()
{
   TRC2(SsiAlloc::operator!=);
   RETVALUE(0);
}

#endif
#endif


/********************************************************************30**

         End of file:     SsiAlloc.h@@/main/1 - Fri Aug 29 19:50:49 2008

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

