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
 * @file   _QGAR_GenQgarArc.tcc
 * @brief  Implementation of function members of class qgar::GenQgarArc.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  17:17
 * @since  Qgar 2.2
 */



// STD
#include <iostream>
#include <cmath>
// QGAR
#include "ISerializable.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenQgarArc<T>::GenQgarArc(int aThickness,
			  QGEcolor aColor,
			  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(GenPoint<T>(static_cast<T>(0),static_cast<T>(0)),
		   GenPoint<T>(static_cast<T>(0),static_cast<T>(0)),
		   GenPoint<T>(static_cast<T>(0),static_cast<T>(0)))

{
  // VOID
}


// COPY-CONSTRUCTOR

template <class T>
GenQgarArc<T>::GenQgarArc(const GenQgarArc<T>& aQArc)
  
  : AbstractGenQgarPrimitive<T>(aQArc._thickness,
				aQArc._color,
				aQArc._outline),
    _geomStructure(aQArc._geomStructure)

{
  // VOID
}


// INITIALIZE FROM A GEOMETRICAL ARC

template <class T>
GenQgarArc<T>::GenQgarArc(const GenArc<T>& anArc,
			  int aThickness,
			  QGEcolor aColor,
			  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(anArc)

{
  // VOID
}


// INITIALIZE FROM THREE POINTS

template <class T>
GenQgarArc<T>::GenQgarArc(const GenPoint<T>& aSource,
			  const GenPoint<T>& aTarget,
			  const GenPoint<T>& aCenter,
			  int aThickness,
			  QGEcolor aColor,
			  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(aSource, aTarget, aCenter)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenQgarArc<T>::~GenQgarArc()
{
  // VOID
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenQgarArc<T>&
GenQgarArc<T>::operator=(const GenQgarArc<T>& aQArc)
{
  // Are left hand side and right hand side different objects?
  if (this != &aQArc)
    {
      AbstractGenQgarPrimitive<T>::operator=(aQArc);
      this->_geomStructure = aQArc._geomStructure;
    }
  return *this;
}


// SAME AS FUNCTION qgar::GenQgarArc::eq

template <class T>
inline bool
GenQgarArc<T>::operator==(const GenQgarArc<T>& aQArc) const
{
  return eq(aQArc);
}


// SAME AS FUNCTION qgar::GenQgarArc::notEq

template <class T>
inline bool
GenQgarArc<T>::operator!=(const GenQgarArc<T>& aQArc) const
{
  return notEq(aQArc);
}
  

// -------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S 
// -------------------------------------------------------------------


// EQUALITY OF GEOMETRICAL STRUCTURES

template <class T>
inline bool
GenQgarArc<T>::eq(const GenQgarArc<T>& aQArc) const
{
  return (this->accessGeomStructure()).eq(aQArc.accessGeomStructure());
}


// FULL EQUALITY

template <class T>
bool
GenQgarArc<T>::equal(const GenQgarArc<T>& aQArc) const
{
  return
       (this->eq(aQArc))
    && (this->_thickness == aQArc._thickness)
    && (this->_color     == aQArc._color)
    && (this->_outline   == aQArc._outline);
}


// INEQUALITY OF GEOMETRICAL STRUCTURES

template <class T>
inline bool
GenQgarArc<T>::notEq(const GenQgarArc<T>& aQArc) const
{
  return (this->accessGeomStructure()).notEq(aQArc.accessGeomStructure());
}


// FULL INEQUALITY

template <class T>
bool
GenQgarArc<T>::notEqual(const GenQgarArc<T>& aQArc) const
{
  return
       (this->notEq(aQArc))
    || (this->_source != aQArc._source) 
    || (this->_target != aQArc._target)
    || (this->_center != aQArc._center);
}


// -------------------------------------------------------------------
// A C C E S S   T O   G E O M E T R I C A L   F E A T U R E S
// -------------------------------------------------------------------


// GET THE RADIUS

template <class T>
inline double
GenQgarArc<T>::radius() const
{
  return (this->_geomStructure).radius();
}


// GET LENGTH OF THE ARC

template <class T>
inline double
GenQgarArc<T>::length() const
{
  return (this->_geomStructure).length();
}


// GET THE SOURCE ANGLE, IN [0, 2PI] RADIANS

template <class T>
inline double
GenQgarArc<T>::sourceAngle() const
{
  return (this->_geomStructure).sourceAngle();
}


// GET THE SOURCE ANGLE, IN [0, 360] DEGREES

template <class T>
inline double
GenQgarArc<T>::sourceAngleDegrees() const
{
  return (this->_geomStructure).sourceAngleDegrees();
}


// GET THE TARGET ANGLE, IN [0, 2PI] RADIANS

template <class T>
inline double
GenQgarArc<T>::targetAngle() const
{
  return (this->_geomStructure).targetAngle();
}


// GET THE TARGET ANGLE, IN [0, 360] DEGREES

template <class T>
inline double
GenQgarArc<T>::targetAngleDegrees() const
{
  return (this->_geomStructure).targetAngleDegrees();
}


// GET THE ANGLE OF THE ARC, IN [0, 2PI] RADIANS

template <class T>
inline double
GenQgarArc<T>::angle() const
{
  return (this->_geomStructure).angle();
}


// GET THE ANGLE OF THE ARC, IN [0, 360] DEGREES

template <class T>
inline double
GenQgarArc<T>::angleDegrees() const
{
  return (this->_geomStructure).angleDegrees();
}


// -------------------------------------------------------------------
// C E N T E R
// -------------------------------------------------------------------


// GET THE CENTER POINT

template <class T>
inline const GenPoint<T>&
GenQgarArc<T>::accessCenter() const
{
  return (this->_geomStructure).accessCenter();
}


// GET A COPY OF THE CENTER POINT

template <class T>
inline GenPoint<T>
GenQgarArc<T>::center() const
{
  return (this->_geomStructure).center();
}


// GET X COORDINATE OF CENTER POINT

template <class T>
inline T
GenQgarArc<T>::xCenter() const
{
  return (this->_geomStructure).xCenter();
}


// GET Y COORDINATE OF CENTER POINT

template <class T>
inline T
GenQgarArc<T>::yCenter() const
{
  return (this->_geomStructure).yCenter();
}


// SET X COORDINATE OF THE CENTER POINT

template <class T>
inline void
GenQgarArc<T>::setXCenter(T aX)
{
  (this->_geomStructure).setXCenter(aX);
}

 
// SET Y COORDINATE OF THE CENTER POINT

template <class T>
inline void
GenQgarArc<T>::setYCenter(T aY)
{
  (this->_geomStructure).setYCenter(aY);
}


// SET THE CENTER POINT

template <class T>
inline void
GenQgarArc<T>::setCenter(T aX, T aY)
{
  (this->_geomStructure).setCenter(aX,aY);
}


template <class T>
inline void
GenQgarArc<T>::setCenter(const GenPoint<T>& aCenter)
{
  (this->_geomStructure).setCenter(aCenter);
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenQgarArc<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "QgarArc");

  // Geometrical structure

  qgReadObjData(anInStream, this->_geomStructure);

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
GenQgarArc<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "QgarArc("
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
// THE GEOMETRICAL ASPECT OF A QGAR ARC

template <class T>
GenQgarArc<T>*
GenQgarArc<T>::clone() const
{
  return new GenQgarArc<T>(*this);
}


// -------------------------------------------------------------------
// A C C E S S   T O   G E O M E T R I C A L   F E A T U R E S
// -------------------------------------------------------------------


// GET THE STRUCTURE IMPLEMENTING
// THE GEOMETRICAL ASPECT OF A QGAR ARC

template <class T>
inline const GenArc<T>&
GenQgarArc<T>::accessGeomStructure() const
{
  return this->_geomStructure;
}


// -------------------------------------------------------------------
// NON-PROTECTED ACCESS TO THE GEOMETRICAL ASPECT
// -------------------------------------------------------------------


// RETURN THE GEOMETRICAL ASPECT, THAT MAY THEN BE MODIFIED
// USING APPROPRIATE TRANSFORMATION FUNCTION MEMBERS

template <class T>
inline AbstractGenPrimitive<T>&
GenQgarArc<T>::getGeomStructure()
{
  return this->_geomStructure;
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar
