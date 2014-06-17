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
 * @file   _QGAR_AbstractGenQgarPrimitive.tcc
 * @brief  Implementation of function members
 *         of class qgar::AbstractGenQgarPrimitive.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  15:15
 * @since  Qgar 2.2
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
AbstractGenQgarPrimitive<T>::AbstractGenQgarPrimitive(int        aThickness,
						      QGEcolor   aColor,
						      QGEoutline anOutline)

  : _thickness(aThickness),
    _color(aColor),
    _outline(anOutline)

{
  // VOID
}


// COPY-CONSTRUCTOR

template <class T>
AbstractGenQgarPrimitive<T>::AbstractGenQgarPrimitive(const AbstractGenQgarPrimitive<T>& aQPrim)

  : _thickness(aQPrim._thickness),
    _color(aQPrim._color),
    _outline(aQPrim._outline)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

template <class T>
AbstractGenQgarPrimitive<T>::~AbstractGenQgarPrimitive()
{
  // VOID
}


// -------------------------------------------------------------------
// A C C E S S   T O   A T T R I B U T E S 
// -------------------------------------------------------------------


// GET THICKNESS

template <class T>
inline int
AbstractGenQgarPrimitive<T>::thickness() const
{
  return _thickness;
}


// GET COLOR

template <class T>
inline QGEcolor
AbstractGenQgarPrimitive<T>::color() const
  {
    return _color;
  }


// GET OUTLINE

template <class T>
inline QGEoutline
AbstractGenQgarPrimitive<T>::outline() const
{
  return _outline;
}


// -------------------------------------------------------------------
// A C C E S S   T O   S O U R C E   A N D   T A R G E T 
// -------------------------------------------------------------------


// GET SOURCE POINT

template <class T>
inline const GenPoint<T>&
AbstractGenQgarPrimitive<T>::accessSource() const
{
  return accessGeomStructure().accessSource();
}


// GET A COPY OF THE SOURCE POINT

template <class T>
inline GenPoint<T>
AbstractGenQgarPrimitive<T>::source() const
{
  return accessGeomStructure().source();
}


// GET TARGET POINT

template <class T>
inline const GenPoint<T>&
AbstractGenQgarPrimitive<T>::accessTarget() const
{
  return accessGeomStructure().accessTarget();
}


// GET A COPY OF THE TARGET POINT

template <class T>
inline GenPoint<T>
AbstractGenQgarPrimitive<T>::target() const
{
  return accessGeomStructure().target();
}


// -------------------------------------------------------------------
// A C C E S S   T O   S E P A R A T E   C O O R D I N A T E S 
// -------------------------------------------------------------------


// GET X COORDINATE OF THE SOURCE POINT

template <class T>
inline T
AbstractGenQgarPrimitive<T>::xSource() const
{
  return accessGeomStructure().xSource();
}


// GET X COORDINATE OF THE TARGET POINT

template <class T>
inline T
AbstractGenQgarPrimitive<T>::xTarget() const
{
  return accessGeomStructure().xTarget();
}


// GET Y COORDINATE OF THE SOURCE POINT

template <class T>
inline T
AbstractGenQgarPrimitive<T>::ySource() const
{
  return accessGeomStructure().ySource();
}


// GET Y COORDINATE OF THE TARGET POINT

template <class T>
inline T
AbstractGenQgarPrimitive<T>::yTarget() const
{
  return accessGeomStructure().yTarget();
}


// -------------------------------------------------------------------
// ACCESS  TO  GEOMETRICAL  CHARACTERISTICS
// -------------------------------------------------------------------


// DIFFERENCE BETWEEN TARGET AND SOURCE X COORDINATES

template <class T>
inline T
AbstractGenQgarPrimitive<T>::dx() const
{
  return accessGeomStructure().dx();
}


// DIFFERENCE BETWEEN TARGET AND SOURCE Y COORDINATES

template <class T>
inline T
AbstractGenQgarPrimitive<T>::dy() const
{
  return accessGeomStructure().dy();
}


// -------------------------------------------------------------------
// S E T   A T T R I B U T E S 
// -------------------------------------------------------------------


// SET THICKNESS

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setThickness(int aThickness)
{
  _thickness = aThickness;
}


// SET COLOR

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setColor(QGEcolor aColor)
{
  _color = aColor;
}


// SET OUTLINE

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setOutline(QGEoutline anOutline)
{
  _outline = anOutline;
}


// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITHOUT UPDATE
// -------------------------------------------------------------------


// SET SOURCE POINT


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setSource(T aX, T aY)
{
  getGeomStructure().setSource(aX,aY);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setSource(const GenPoint<T>& aPt)
{
  getGeomStructure().setSource(aPt);
}


// SET TARGET POINT


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setTarget(T aX, T aY)
{
  getGeomStructure().setTarget(aX, aY);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setTarget(const GenPoint<T>& aPt)
{
  getGeomStructure().setTarget(aPt);
}


// SET BOTH SOURCE AND TARGET POINTS


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setSourceTarget(T aXSource,
					     T aYSource,
					     T aXTarget,
					     T aYTarget)
{
  getGeomStructure().setSourceTarget(aXSource, aYSource, aXTarget, aYTarget);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::setSourceTarget(const GenPoint<T>& aSource,
					     const GenPoint<T>& aTarget)
{
  getGeomStructure().setSourceTarget(aSource, aTarget);
}


// -------------------------------------------------------------------
// SET SOURCE AND/OR TARGET WITH UPDATE
// -------------------------------------------------------------------


// SET SOURCE POINT


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixSource(T aX, T aY)
{
  getGeomStructure().fixSource(aX,aY);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixSource(const GenPoint<T>& aPt)
{
  getGeomStructure().fixSource(aPt);
}


// SET TARGET POINT


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixTarget(T aX, T aY)
{
  getGeomStructure().fixTarget(aX,aY);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixTarget(const GenPoint<T>& aPt)
{
  getGeomStructure().fixTarget(aPt);
}


// SET BOTH SOURCE AND TARGET POINTS


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixSourceTarget(T aXSource,
					     T aYSource,
					     T aXTarget,
					     T aYTarget)
{
  getGeomStructure().fixSourceTarget(aXSource, aYSource, aXTarget, aYTarget);
}


template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixSourceTarget(const GenPoint<T>& aSource,
					     const GenPoint<T>& aTarget)
{
  getGeomStructure().fixSourceTarget(aSource, aTarget);
}


// -------------------------------------------------------------------
// SET SEPARATE COORDINATES WITHOUT UPDATE
// -------------------------------------------------------------------


// SET COORDINATES OF THE SOURCE POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setXSource(T aX)
{
  getGeomStructure().setXSource(aX);
}


// SET X COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setXTarget(T aX)
{
  getGeomStructure().setXTarget(aX);
}


// SET Y COORDINATE OF THE SOURCE POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setYSource(T aY)
{
  getGeomStructure().setYSource(aY);
}


// SET Y COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::setYTarget(T aY)
{
  getGeomStructure().setYTarget(aY);
}


// -------------------------------------------------------------------
// SET SEPARATE COORDINATES WITH UPDATE
// -------------------------------------------------------------------


// SET X COORDINATE OF THE SOURCE POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixXSource(T aX)
{
  getGeomStructure().fixXSource(aX);
}


// SET X COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixXTarget(T aX)
{
  getGeomStructure().fixXTarget(aX);
}


// SET Y COORDINATE OF THE SOURCE POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixYSource(T aY)
{
  getGeomStructure().fixYSource(aY);
}


// SET Y COORDINATE OF THE TARGET POINT

template <class T>
inline void
AbstractGenQgarPrimitive<T>::fixYTarget(T aY)
{
  getGeomStructure().fixYTarget(aY);
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
AbstractGenQgarPrimitive<T>&
AbstractGenQgarPrimitive<T>::operator=(const AbstractGenQgarPrimitive<T>& aQPrim)
{
  // Are left hand side and right hand side different objects?
  if (this != &aQPrim)
    {
      _thickness = aQPrim._thickness;
      _color     = aQPrim._color;
      _outline   = aQPrim._outline;
    }
  return *this;
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


// TRANSLATE ALONG Y AND Y AXIS


template <class T>
inline void
AbstractGenQgarPrimitive<T>::translate(T aTransX, T aTransY)
{
  (this->getGeomStructure()).translate(aTransX, aTransY);
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
//   (this->getGeomStructure()).symmetry(aX,aY);
// }


// // TRANSFORM CURRENT PRIMITIVE INTO ITS SYMMETRICAL PRIMITIVE
// // RELATIVELY TO THE GIVEN CENTER


// template <class T>
// inline void
// AbstractGenPrimitive<T>::symmetry(const GenPoint<T>& aCenter)
// {
//   (this->getGeomStructure()).qgSymmetry(aCenter);
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
//   (this->getGeomStructure()).symmetry(aPt1,aPt2);
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
//   (this->getGeomStructure()).symmetry(aSeg);
// }


// template <class T>
// void
// AbstractGenPrimitive<T>::symmetry(const GenSegment<double>& aSeg)
// {
//   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
// }


// -------------------------------------------------------------------


} // namespace qgar
