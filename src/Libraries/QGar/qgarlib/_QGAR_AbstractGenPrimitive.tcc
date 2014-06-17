/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file     _QGAR_AbstractGenPrimitive.tcc
 * @brief    Implementation of the function members
 *           of class qgar::AbstractGenPrimitive.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 14, 2004  14:14
 * @since   Qgar 2.2
 */



namespace qgar
{


// -------------------------------------------------------------------
// JUST A FAKE CLASS (NOT DEFINED)
// TO BE USED TO CAUSE COMPILATION ERRORS WHEN SOME TEMPLATE FUNCTION
// CANNOT BE INSTANTIATED USING ANY TYPE
// -------------------------------------------------------------------


class TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC;


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR


template <class T>
AbstractGenPrimitive<T>::AbstractGenPrimitive()

  : _source(static_cast<T>(0), static_cast<T>(0)),
    _target(static_cast<T>(0), static_cast<T>(0))

{
  // VOID
}


// COPY-CONSTRUCTOR


template <class T>
AbstractGenPrimitive<T>::AbstractGenPrimitive(const AbstractGenPrimitive<T>& aPrim)

  : _source(aPrim._source),
    _target(aPrim._target)

{
  // VOID
}


// INITIALIZE FROM SOURCE AND TARGET


template <class T>
AbstractGenPrimitive<T>::AbstractGenPrimitive(const GenPoint<T> aSource,
					      const GenPoint<T> aTarget)

  : _source(aSource),
    _target(aTarget)

{
  // VOID
}


// INITIALIZE FROM COORDINATES


template <class T>
AbstractGenPrimitive<T>::AbstractGenPrimitive(T aXSource,
					      T aYSource,
					      T aXTarget,
					      T aYTarget)

  : _source(aXSource, aYSource),
    _target(aXTarget, aYTarget)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR


template <class T>
AbstractGenPrimitive<T>::~AbstractGenPrimitive()
{
  // VOID
}


// -------------------------------------------------------------------
// A C C E S S   T O   S O U R C E   A N D   T A R G E T 
// -------------------------------------------------------------------


// GET SOURCE POINT

template <class T>
inline const GenPoint<T>&
AbstractGenPrimitive<T>::accessSource() const
{
  return _source;
}


// GET A COPY OF THE SOURCE POINT

template <class T>
inline GenPoint<T>
AbstractGenPrimitive<T>::source() const
{
  return _source;
}


// GET TARGET POINT

template <class T>
inline const GenPoint<T>&
AbstractGenPrimitive<T>::accessTarget() const
{
  return _target;
}


// GET A COPY OF THE TARGET POINT

template <class T>
inline GenPoint<T>
AbstractGenPrimitive<T>::target() const
{
  return _target;
}


// -------------------------------------------------------------------
// A C C E S S   T O   S E P A R A T E   C O O R D I N A T E S 
// -------------------------------------------------------------------


// GET X COORDINATE OF THE SOURCE POINT

template <class T>
inline T
AbstractGenPrimitive<T>::xSource() const
{
  return _source.x();
}


// GET X COORDINATE OF THE TARGET POINT

template <class T>
inline T
AbstractGenPrimitive<T>::xTarget() const
{
  return _target.x();
}


// GET Y COORDINATE OF THE SOURCE POINT

template <class T>
inline T
AbstractGenPrimitive<T>::ySource() const
{
  return _source.y();
}


// GET Y COORDINATE OF THE TARGET POINT

template <class T>
inline T
AbstractGenPrimitive<T>::yTarget() const
{
  return _target.y();
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL CHARACTERISTICS
// -------------------------------------------------------------------


// VERTICAL (SIGNED) DISTANCE

template <class T>
inline T
AbstractGenPrimitive<T>::dx() const
{
  return (_target.x() - _source.x());
}


// HORIZONTAL (SIGNED) DISTANCE

template <class T>
inline T
AbstractGenPrimitive<T>::dy() const
{
  return (_target.y() - _source.y());
}
 

// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITHOUT UPDATE
// -------------------------------------------------------------------


// SET SOURCE POINT


template <class T>
inline void
AbstractGenPrimitive<T>::setSource(T aX, T aY)
{
  _source.setXY(aX,aY);
}


template <class T>
inline void
AbstractGenPrimitive<T>::setSource(const GenPoint<T>& aPt)
{
  _source = aPt;
}


// SET TARGET POINT


template <class T>
inline void
AbstractGenPrimitive<T>::setTarget(T aX, T aY)
{
  _target.setXY(aX,aY);
}


template <class T>
inline void
AbstractGenPrimitive<T>::setTarget(const GenPoint<T>& aPt)
{
  _target = aPt;
}


// SET BOTH SOURCE AND TARGET POINTS


template <class T>
void
AbstractGenPrimitive<T>::setSourceTarget(T aXSource,
					 T aYSource,
					 T aXTarget,
					 T aYTarget)
{
  _source.setXY(aXSource, aYSource);
  _target.setXY(aXTarget, aYTarget);
}


template <class T>
void
AbstractGenPrimitive<T>::setSourceTarget(const GenPoint<T>& aSource,
					 const GenPoint<T>& aTarget)
{
  _source = aSource;
  _target = aTarget;
}


// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITH UPDATE
// -------------------------------------------------------------------


// SET SOURCE POINT


template <class T>
void
AbstractGenPrimitive<T>::fixSource(T aX, T aY)
{
  this->setSource(aX,aY);
  this->updateSource();
}


template <class T>
void
AbstractGenPrimitive<T>::fixSource(const GenPoint<T>& aPt)
{
  this->setSource(aPt);
  this->updateSource();
}


// SET TARGET POINT


template <class T>
void
AbstractGenPrimitive<T>::fixTarget(T aX, T aY)
{
  this->setTarget(aX,aY);
  this->updateTarget();
}


template <class T>
void
AbstractGenPrimitive<T>::fixTarget(const GenPoint<T>& aPt)
{
  this->setTarget(aPt);
  this->updateTarget();
}


// SET BOTH SOURCE AND TARGET POINTS


template <class T>
void
AbstractGenPrimitive<T>::fixSourceTarget(T aXSource,
					 T aYSource,
					 T aXTarget,
					 T aYTarget)
{
  this->setSourceTarget(aXSource, aYSource, aXTarget, aYTarget);
  this->updateSourceTarget();
}


template <class T>
void
AbstractGenPrimitive<T>::fixSourceTarget(const GenPoint<T>& aSource,
					 const GenPoint<T>& aTarget)
{
  this->setSourceTarget(aSource, aTarget);
  this->updateSourceTarget();
}


// -------------------------------------------------------------------
//  SET SEPARATE COORDINATES WITHOUT UPDATE
// -------------------------------------------------------------------


// SET X COORDINATE OF THE SOURCE POINT

template <class T>
inline void
AbstractGenPrimitive<T>::setXSource(T aX) 
{
  (this->_source).setX(aX);
}


// SET X COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenPrimitive<T>::setXTarget(T aX)
{
  (this->_target).setX(aX);
}


// SET Y COORDINATE OF THE SOURCE POINT

template <class T>
inline void
AbstractGenPrimitive<T>::setYSource(T aY)
{
  (this->_source).setY(aY);
}


// SET Y COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenPrimitive<T>::setYTarget(T aY)
{
  (this->_target).setY(aY);
}


// -------------------------------------------------------------------
//  SET SEPARATE COORDINATES WITH UPDATE
// -------------------------------------------------------------------


// SET X COORDINATE OF THE SOURCE POINT

template <class T>
void
AbstractGenPrimitive<T>::fixXSource(T aX) 
{
  this->setXSource(aX);
  this->updateSource();
}


// SET X COORDINATE OF THE TARGET POINT

template <class T>
void
AbstractGenPrimitive<T>::fixXTarget(T aX)
{
  this->setXTarget(aX);
  this->updateTarget();
}


// SET Y COORDINATE OF THE SOURCE POINT

template <class T>
void
AbstractGenPrimitive<T>::fixYSource(T aY)
{
  this->setYSource(aY);
  this->updateSource();
}


// SET Y COORDINATE OF THE TARGET POINT

template <class T>
void
AbstractGenPrimitive<T>::fixYTarget(T aY)
{
  this->setYTarget(aY);
  this->updateTarget();
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
AbstractGenPrimitive<T>&
AbstractGenPrimitive<T>::operator=(const AbstractGenPrimitive<T>& aPrim)
{
  // Are left hand side and right hand side different objects?
  if (this != &aPrim)
    {
      this->_source = aPrim._source;
      this->_target = aPrim._target;
    }

  return *this;
}



// // -------------------------------------------------------------------
// // G E O M E T R Y :   S Y M M E T R Y 
// // -------------------------------------------------------------------


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE POINT OF GIVEN COORDINATES


// template <class T>
// inline void
// AbstractGenPrimitive<T>::symmetry(T aX, T aY)
// {
//   qgSymmetry(*this, aX, aY);
// }


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE GIVEN CENTER


// template <class T>
// inline void
// AbstractGenPrimitive<T>::symmetry(const GenPoint<T>& aCenter)
// {
//   qgSymmetry(*this, aCenter);
// }


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE LINE SUPPORTING THE GIVEN SEGMENT

// // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
// // W                                                                 W
// // W WARNING: THESE FUNCTIONS APPLY TO POINTS WITH COORDINATES       W
// // W          OF TYPE DOUBLE ONLY                                    W
// // W                                                                 W
// // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE LINE PASSING THROUGH THE GIVEN POINTS


// template <>
// void
// AbstractGenPrimitive<double>::symmetry(const GenSegment<double>& aPt1,
// 				       const GenSegment<double>& aPt2)
// {
//   qgSymmetry(*this, aPt1, aPt2);
// }


// template <class T>
// void
// AbstractGenPrimitive<T>::symmetry(const GenSegment<double>& aSeg)
// {
//   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
// }


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE LINE SUPPORTING THE GIVEN SEGMENT


// template <>
// void
// AbstractGenPrimitive<double>::symmetry(const GenSegment<double>& aSeg)
// {
//   qgSymmetry(*this, aSeg);
// }


// template <class T>
// void
// AbstractGenPrimitive<T>::symmetry(const GenSegment<double>& aSeg)
// {
//   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
// }


// -------------------------------------------------------------------


} // namespace qgar
