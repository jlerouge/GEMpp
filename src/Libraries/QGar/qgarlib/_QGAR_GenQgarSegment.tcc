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
 * @file _QGAR_GenQgarSegment.tcc
 *
 * @brief Implementation of function members of class qgar::GenQgarSegment.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 15, 2004  14:14
 * @since  Qgar 2.2
 */



// STD
#include <cmath>
#include <iostream>
// QGAR
#include "ISerializable.h"
#include "math.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenQgarSegment<T>::GenQgarSegment(int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(0, 0, 0, 0)

{
  // VOID
}


// COPY-CONSTRUCTOR

template <class T>
GenQgarSegment<T>::GenQgarSegment(const GenQgarSegment<T>& aQSeg)

  : AbstractGenQgarPrimitive<T>(aQSeg._thickness,
				aQSeg._color,
				aQSeg._outline),
    _geomStructure(aQSeg._geomStructure)

{
  // VOID
}


// INITIALIZE FROM A GEOMETRICAL SEGMENT

template <class T>
GenQgarSegment<T>::GenQgarSegment(const GenSegment<T>& aSeg,
				  int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(aSeg)

{
  // VOID
}


// INITIALIZE FROM SOURCE AND TARGET POINTS

template <class T>
GenQgarSegment<T>::GenQgarSegment(const GenPoint<T>& aSource,
				  const GenPoint<T>& aTarget,
				  int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(aSource, aTarget)

{
  // VOID
}


// INITIALIZE FROM COORDINATES

template <class T>
GenQgarSegment<T>::GenQgarSegment(T aXSource,
				  T aYSource,
				  T aXTarget,
				  T aYTarget,
				  int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(aXSource, aYSource, aXTarget, aYTarget)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenQgarSegment<T>::~GenQgarSegment()
{
  // VOID
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// -------------------------------------------------------------------


// GET LENGTH OF THE SEGMENT

template <class T>
inline double
GenQgarSegment<T>::length() const
{
  return _geomStructure.length();
}


// GET SQUARED LENGTH OF THE SEGMENT

template <class T>
inline double
GenQgarSegment<T>::sqr_length() const
{
  return _geomStructure.sqr_length();
}


// SIGNED DISTANCE BETWEEN (0,0) AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING THE SEGMENT
// Precomputed
// WARNING: This value is negative if the line supporting the
// segment intersects the Y axis at a negative value

template <class T>
inline double
GenQgarSegment<T>::rho() const
{
  return _geomStructure.rho();
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, 2PI[ RADIANS
// Precomputed

template <class T>
inline double
GenQgarSegment<T>::theta() const
{
  return _geomStructure.theta();
}


// SAME AS PREVIOUS

template <class T>
inline double
GenQgarSegment<T>::angle() const
{
  return _geomStructure.angle();
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, 360[ DEGREES

template <class T>
inline double
GenQgarSegment<T>::thetaDegrees() const
{
  return _geomStructure.thetaDegrees();
}


// SAME AS PREVIOUS

template <class T>
inline double
GenQgarSegment<T>::angleDegrees() const
{
  return _geomStructure.angleDegrees();
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, PI[ RADIANS

template <class T>
inline double
GenQgarSegment<T>::slope() const
{
  return _geomStructure.slope();
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, 180[ DEGREES

template <class T>
inline double
GenQgarSegment<T>::slopeDegrees() const
{
  return _geomStructure.slopeDegrees();
}

  
// -------------------------------------------------------------------
// G E O M E T R I C A L   P R E D I C A T E S
// -------------------------------------------------------------------


// DOES THE GIVEN POINT APPROXIMATELY BELONGS
// TO THE CURRENT QGAR SEGMENT?

template <class T>
inline bool
GenQgarSegment<T>::contains(const GenPoint<T>& c, double aDist)
{
  return _geomStructure.contains(c, aDist);
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenQgarSegment<T>&
GenQgarSegment<T>::operator=(const GenQgarSegment<T>& aQSeg)
{
  // Are left hand side and right hand side different objects?
  if (this != &aQSeg)
    {
      AbstractGenQgarPrimitive<T>::operator=(aQSeg);
      _geomStructure = aQSeg._geomStructure;
    }
  return *this;
}


// EQUALITY

template <class T>
inline bool
GenQgarSegment<T>::operator==(const GenQgarSegment<T>& aQSeg) const
{
  return this->_geomStructure == aQSeg._geomStructure;
}


// INEQUALITY

template <class T>
inline bool
GenQgarSegment<T>::operator!=(const GenQgarSegment<T>& aQSeg) const
{
  return this->_geomStructure != aQSeg._geomStructure;
}


  
// -------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S 
// -------------------------------------------------------------------


// EQUALITY OF COORDINATES ONLY

template <class T>
inline bool
GenQgarSegment<T>::eq(const GenQgarSegment<T>& aQSeg) const
{
  return (this->_geomStructure).eq(aQSeg._geomStructure);
}


// EQUALITY OF COORDINATES AND ALL FEATURES

template <class T>
bool
GenQgarSegment<T>::equal(const GenQgarSegment<T>& aQSeg) const
{
  return
    (this->_geomStructure).eq(aQSeg._geomStructure)
    && ((this->_thickness) == (aQSeg._thickness))
    && ((this->_color)     == (aQSeg._color))
    && ((this->_outline)   == (aQSeg._outline));
}


// INEQUALITY OF COORDINATES ONLY

template <class T>
inline bool
GenQgarSegment<T>::notEq(const GenQgarSegment<T>& aQSeg) const
{
  return (this->_geomStructure).notEq(aQSeg._geomStructure);
}


// INEQUALITY OF COORDINATES OR ALL FEATURES

template <class T>
bool
GenQgarSegment<T>::notEqual(const GenQgarSegment<T>& aQSeg) const
{
  return
    (this->_geomStructure).notEq(aQSeg._geomStructure)
    || ((this->_thickness) != (aQSeg._thickness))
    || ((this->_color)     != (aQSeg._color))
    || ((this->_outline)   != (aQSeg._outline));
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenQgarSegment<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "QgarSegment");

  // Geometrical structure

  qgReadObjData(anInStream, _geomStructure);

  // Attributes

  qgReadObjData(anInStream, this->_thickness);

  int color;
  qgReadObjData(anInStream, color);
  this->_color = static_cast<QGEcolor>(color);

  int outline;
  qgReadObjData(anInStream, outline);
  this->_outline = static_cast<QGEoutline>(outline);

  return anInStream;
}


template <class T>
std::ostream& 
GenQgarSegment<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "QgarSegment("
	      << this->_geomStructure
	      << ")("
	      << this->_thickness
	      << ")("
	      << this->_color
	      << ")("
	      << this->_outline
	      << ')';
  return anOutStream;  
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// V            IMPLEMENTATION OF PURE VIRTUAL FUNCTIONS             V
// V            INHERITED FROM AbstractGenQgarPrimitive              V
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// GET A COPY OF THE STRUCTURE IMPLEMENTING
// THE GEOMETRICAL ASPECT OF A QGAR SEGMENT

template <class T>
GenQgarSegment<T>*
GenQgarSegment<T>::clone() const
{
  return new GenQgarSegment<T>(*this);
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL FEATURES
// -------------------------------------------------------------------


// GET THE STRUCTURE IMPLEMENTING
// THE GEOMETRICAL ASPECT OF A QGAR SEGMENT

template <class T>
inline const GenSegment<T>&
GenQgarSegment<T>::accessGeomStructure() const
{
  return _geomStructure;
}


// -------------------------------------------------------------------
// NON-PROTECTED ACCESS TO THE GEOMETRICAL ASPECT
// -------------------------------------------------------------------


// RETURN THE GEOMETRICAL ASPECT, THAT MAY THEN BE MODIFIED
// USING APPROPRIATE TRANSFORMATION FUNCTION MEMBERS

template <class T>
inline AbstractGenPrimitive<T>&
GenQgarSegment<T>::getGeomStructure()
{
  return _geomStructure;
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar
