//----------------------------  vector.h  ---------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 1998, 1999, 2000 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------  vector.h  ---------------------------
#ifndef __deal2__vector_h
#define __deal2__vector_h


#include <base/exceptions.h>
#include <cstdio>


/**
 *  Numerical Vector of data.  For this class there are different
 * types of functions available. The first type of function mesures
 * the norm of the vector in order to mesure its length in a suitable
 * norm. The second type support the abgebraic operation for
 * vectors. The third und last type helps us to manipulate the
 * components of the vector.
 * As opposed to the array of the C++ standard library called #vector#, this class implements
 * an element of a vector space suitable for numerical computations.
 *
 * @author Guido Kanschat, Franz-Theo Suttmeier, Wolfgang Bangerth
 */
template <typename Number>
class Vector {
  public:
				     /**
				      * Declare standard types used in all
				      * containers. These types parallel
				      * those in the #C++# standard libraries
				      * #vector<...># class.
				      */
    typedef Number value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;


				     /**
				      * @name 1: Basic Object-handling 
				      */
				     //@{
				     /**
				      *  Dummy-Constructor. Dimension=0
				      */
    Vector ();
    
				     /**
				      * Copy-Constructor. Dimension set to
				      * that of V, all components are copied
				      * from V
				      */
    Vector (const Vector<Number>& V);


// note: I disabled this function for the time being, since egcs1.1.2
// does not respect the "explicit" keyword for template constructors.
// this leads to unwanted conversions and in some places to automatically
// generated temporaries, where this is not a good idea. [WB]
// 				     /**
// 				      * Copy constructor taking a vector of
// 				      * another data type. This will fail if
// 				      * there is no conversion path from
// 				      * #OtherNumber# to #Number#. Note that
// 				      * you may lose accuracy when copying
// 				      * to a vector with data elements with
// 				      * less accuracy.
// 				      */
//     template <typename OtherNumber>
//     explicit
//     Vector (const Vector<OtherNumber> &v);
    
				     /**
				      * Constructor. Set dimension to #n# and
				      * initialize all elements with zero.
				      */
    Vector (const unsigned int n);
    
				     /**
				      * Destructor, deallocates
				      * memory. Made virtual to allow
				      * for derived classes to behave
				      * properly.
				      */
    virtual ~Vector ();

				     /**
				      * Set all entries to zero. Equivalent to
				      * #v = 0#, but more obvious and faster.
				      * Note that this function does not change
				      * the size of the vector, unlike the
				      * STL's #vector<>::clear# function.
				      */
    void clear ();
    
				     /**
				      * $U(0-N) = s$: fill all components.
				      */
    Vector<Number> & operator= (const Number s);
    
				     /**
				      *  $U = V$: copy all components.
				      */
    Vector<Number> & operator= (const Vector<Number>& V);

				     /**
				      * $U = V$ for different types.
				      */
    template<typename Number2>
    Vector<Number> & operator= (const Vector<Number2>& V);
    
				     /**
				      * $U = U * V$: scalar product.
				      */
    Number operator* (const Vector<Number>& V) const;

				     /**
				      * Return square of the $l_2$-norm.
				      */
    Number norm_sqr () const;

				     /**
				      * Return the mean value of the elements of
				      * this vector.
				      */
    Number mean_value () const;

				     /**
				      * Return the $l_1$-norm of the vector, i.e.
				      * the sum of the absolute values.
				      */
    Number l1_norm () const;

				     /**
				      * Return the $l_2$-norm of the vector, i.e.
				      * the square root of the sum of the
				      * squares of the elements.
				      */
    Number l2_norm () const;

				     /**
				      * Return the maximum absolute value of the
				      * elements of this vector, which is the
				      * $l_\infty$-norm of a vector.
				      */
    Number linfty_norm () const;


				     /**
				      * Change the dimension of the vector to
				      * #N#. The reserved memory for this vector
				      * remains unchanged if possible, to make
				      * things faster, but this may waste some
				      * memory, so take this in the back of your
				      * head.
				      * However, if #N==0# all memory is freed,
				      * i.e. if you want to resize the vector
				      * and release the memory not needed, you
				      * have to first call #reinit(0)# and then
				      * #reinit(N)#. This cited behaviour is
				      * analogous to that of the STL containers.
				      *
				      * On #fast==false#, the vector is filled by
				      * zeros.
				      */ 
    void reinit (const unsigned int N,
		 const bool         fast=false);
    
				     /**
				      * Change the dimension to that of the
				      * vector #V#. The same applies as for
				      * the other #reinit# function.
				      *
				      * The elements of #V# are not copied, i.e.
				      * this function is the same as calling
				      * #reinit (V.size(), fast)#.
				      */
    void reinit (const Vector<Number> &V,
		 const bool            fast=false);
    
				     /**
				      * Return dimension of the vector. This
				      * function was formerly called #n()#, but
				      * was renamed to get the #Vector# class
				      * closer to the C++ standard library's
				      * #vector# container.
				      */
    unsigned int size () const;

				     /**
				      * Return whether the vector contains only
				      * elements with value zero. This function
				      * is mainly for internal consistency
				      * check and should seldomly be used when
				      * not in debug mode since it uses quite
				      * some time.
				      */
    bool all_zero () const;
    
				     /**
				      * Make the #Vector# class a bit like the
				      * #vector<># class of the C++ standard
				      * library by returning iterators to
				      * the start and end of the elements of this
				      * vector.
				      */
    iterator begin ();

				     /**
				      * Return constant iterator to the start of
				      * the vectors.
				      */
    const_iterator begin () const;

				     /**
				      * Return an iterator pointing to the
				      * element past the end of the array.
				      */
    iterator end ();

    				     /**
				      * Return a constant iterator pointing to
				      * the element past the end of the array.
				      */
    const_iterator end () const;  
				     //@}


				     /**
				      * @name 2: Data-Access
				      */
				     //@{
				     /**
				      * Access components, returns U(i).
				      */
    Number operator() (const unsigned int i) const;
    
				     /**
				      * Access components, returns U(i)
				      * as a writeable reference.
				      */
    Number& operator() (const unsigned int i);
				     //@}


				     /**
				      * @name 3: Modification of vectors
				      */
				     //@{
				     /**
				      * Addition operator.
				      * Fast equivalent to #U.add(1, V)#.
				      */
    Vector<Number> & operator += (const Vector<Number> &V);

    				     /**
				      * Subtraction operator.
				      * Fast equivalent to #U.add(-1, V)#.
				      */
    Vector<Number> & operator -= (const Vector<Number> &V);

				     /**
				      * $U(0-DIM)+=s$.
				      * Addition of #s# to all components. Note
				      * that #s# is a scalar and not a vector.
				      */
    void add (const Number s);
    
				     /**
				      * U+=V.
				      * Simple vector addition, equal to the
				      * #operator +=#.
				      */
    void add (const Vector<Number>& V);
    
				     /**
				      * U+=a*V.
				      * Simple addition of a scaled vector.
				      */
    void add (const Number a, const Vector<Number>& V);
    
				     /**
				      * U+=a*V+b*W.
				      * Multiple addition of scaled vectors.
				      */
    void add (const Number a, const Vector<Number>& V,
	      const Number b, const Vector<Number>& W);
    
				     /**
				      * U=s*U+V.
				      * Scaling and simple vector addition.
				      */
    void sadd (const Number s, const Vector<Number>& V);
    
				     /**
				      * U=s*U+a*V.
				      * Scaling and simple addition.
				      */
    void sadd (const Number s, const Number a, const Vector<Number>& V);
    
				     /**
				      * U=s*U+a*V+b*W.
				      * Scaling and multiple addition.
				      */
    void sadd (const Number s, const Number a,
	       const Vector<Number>& V, const Number b, const Vector<Number>& W);
    
				     /**
				      * U=s*U+a*V+b*W+c*X.
				      * Scaling and multiple addition.
				      */
    void sadd (const Number s, const Number a,
	       const Vector<Number>& V, const Number b, const Vector<Number>& W, 
	       const Number c, const Vector<Number>& X);
    
				     /**
				      * Scale each element of the vector by the
				      * given factor.
				      */
    void scale (const Number factor);
    
				     /**
				      *  U=a*V. Replacing.
				      */
    void equ (const Number a, const Vector<Number>& V);
    
				     /**
				      * U=a*V+b*W.
				      * Replacing by sum.
				      */
    void equ (const Number a, const Vector<Number>& V,
	      const Number b, const Vector<Number>& W);

				     /**
				      * Compute the elementwise ratio of the
				      * two given vectors, that is let
				      * #this[i] = a[i]/b[i]#. This is useful
				      * for example if you want to compute
				      * the cellwise ratio of true to estimated
				      * error.
				      *
				      * This vector is appropriately scaled to
				      * hold the result.
				      *
				      * If any of the #b[i]# is zero, the result
				      * is undefined. No attempt is made to
				      * catch such situations.
				      */
    void ratio (const Vector<Number> &a,
		const Vector<Number> &b);
				     //@}


				     /**
				      * @name 5: Mixed stuff
				      */
				     //@{
				     /**
				      *  Output of vector in user-defined format.
				      */
    void print (FILE* fp, const char* format = 0) const;
    
				     /**
				      *  Output of vector in user-defined format.
				      */
    void print (const char* format = 0) const;

				     /**
				      * Print to a stream.
				      * 
				      */
    void print (ostream &, unsigned int precision = 3,
		bool scientific = true,
		bool across = true) const;

				     /**
				      * Write the vector en bloc to a file. This
				      * is done in a binary mode, so the output
				      * is neither readable by humans nor 
				      * (probably) by other computers using
				      * a different operating system of number
				      * format.
				      */
    void block_write (ostream &out) const;

				     /**
				      * Read a vector en block from a file. This
				      * is done using the inverse operations to
				      * the above function, so it is reasonably
				      * fast because the bitstream is not
				      * interpreted.
				      *
				      * The vector is resized if necessary.
				      *
				      * A primitive form of error checking is
				      * performed which will recognize the
				      * bluntest attempts to interpret some
				      * data as a vector stored bitwise to a
				      * file, but not more.
				      */
    void block_read (istream &in);
				     //@}

				     /**
				      * Exception
				      */
    DeclException2 (ExcDimensionsDontMatch,
		    int, int,
		    << "The dimensions " << arg1 << " and " << arg2
		    << " do not match here.");
				     /**
				      * Exception
				      */
    DeclException1 (ExcInvalidNumber,
		    int,
		    << "The provided number is invalid here: " << arg1);
				     /**
				      * Exception
				      */
    DeclException0 (ExcOutOfMemory);
				     /**
				      * Exception
				      */
    DeclException0 (ExcEmptyVector);
				     /**
				      * Exception
				      */
    DeclException0 (ExcIO);

  protected:

				     /**
				      * Dimension. Actual number of components
				      * contained in the vector.
				      * Get this number by calling #size()#.
				      */
    unsigned int dim;

				     /**
				      * Amount of memory actually reserved for
				      * this vector. This number may be greater
				      * than #dim# if a #reinit# was called with
				      * less memory requirements than the vector
				      * needed last time. At present #reinit#
				      * does not free memory when the number of
				      * needed elements is reduced.
				      */
    unsigned int maxdim;

				     /**
				      * Pointer to the array of components.
				      */
    Number *val;
};


/*----------------------- Inline functions ----------------------------------*/


template <typename Number>
inline
unsigned int Vector<Number>::size () const
{
  return dim;
}


template <typename Number>
inline
Vector<Number>::iterator Vector<Number>::begin () {
  return &val[0];
};


template <typename Number>
inline
Vector<Number>::const_iterator Vector<Number>::begin () const {
  return &val[0];
};


template <typename Number>
inline
Vector<Number>::iterator Vector<Number>::end () {
  return &val[dim];
};


template <typename Number>
inline
Vector<Number>::const_iterator Vector<Number>::end () const {
  return &val[dim];
};


template <typename Number>
inline
Number Vector<Number>::operator() (const unsigned int i) const
{
  Assert (i<dim, ExcIndexRange(i,0,dim));
  return val[i];
}


template <typename Number>
inline
Number& Vector<Number>::operator() (const unsigned int i)
{
  Assert (i<dim, ExcIndexRange(i,0,dim));
  return val[i];
}


#endif
