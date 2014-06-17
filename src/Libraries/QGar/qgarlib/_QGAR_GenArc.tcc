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
 * @file   _QGAR_GenArc.tcc
 * @brief  Implementation of function members of class qgar::GenArc.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    January 28, 2005  15:51
 * @since   Qgar 2.2
 */



// STD
#include <iostream>
// QGAR
#include "ISerializable.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenArc<T>::GenArc()

  : AbstractGenPrimitive<T>(0, 0, 0, 0),
    _center(0, 0)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenArc<T>::GenArc(const GenArc<T>& anArc)

  : AbstractGenPrimitive<T>(anArc._source, anArc._target),
    _center(anArc._center)

{
  // VOID
}


// INITIALIZE FROM A QGAR ARC

template <class T>
GenArc<T>::GenArc(const GenQgarArc<T>& aQArc)

  : AbstractGenPrimitive<T>(aQArc.accessSource(), aQArc.accessTarget()),
    _center(aQArc.accessCenter())

{
  // VOID
}


// INITIALIZE FROM THREE POINTS

template <class T>
GenArc<T>::GenArc(const GenPoint<T>& aSource,
		  const GenPoint<T>& aTarget,
		  const GenPoint<T>& aCenter)

  : AbstractGenPrimitive<T>(aSource, aTarget),
    _center(aCenter)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenArc<T>::~GenArc()
{
  // VOID
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


template <class T> 
GenArc<T>*
GenArc<T>::clone() const
{
  return new GenArc<T>(*this);
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL CHARACTERISTICS
// -------------------------------------------------------------------


// GET THE RADIUS

template <class T>
inline double
GenArc<T>::radius() const
{
  return qgDist(this->_source, this->_center);
}


// GET LENGTH OF THE ARC

template <class T>
double
GenArc<T>::length() const
{
  return std::fabs(this->radius() * angle());
}


// GET THE ANGLE OF THE ARC, IN [0, 2PI] RADIANS

template <class T>
double
GenArc<T>::angle() const
{
  double s = this->sourceAngle();
  double t = this->targetAngle();

  if(t > s)
    {
      return t - s;
    }
  else
    {
      return t - s + Math::QG_2PI;
    }
}


// GET THE ANGLE OF THE ARC, IN [0, 360] DEGREES

template <class T>
double
GenArc<T>::angleDegrees() const
{
  return qgRadiansToDegrees(angle());
}


// GET THE SOURCE ANGLE: ANGLE BETWEEN THE VECTOR JOINING THE CENTER
// TO THE SOURCE POINT AND THE X AXIS, IN [0, 2PI] RADIANS

template <class T>
inline double
GenArc<T>::sourceAngle() const
{
  return qgAngle(this->_center, this->_source);
}


// Get the source angle in [0, 360[ degrees

template <class T>
inline double
GenArc<T>::sourceAngleDegrees() const
{
  return qgRadiansToDegrees(this->sourceAngle());
}


// GET THE TARGET ANGLE: ANGLE BETWEEN THE VECTOR JOINING THE CENTER
// TO THE TARGET POINT AND THE X AXIS, IN [0, 2PI] RADIANS

template <class T>
inline double
GenArc<T>::targetAngle() const
{
  return qgAngle(this->_center, this->_target);
}

 
// Get the target angle in [0, 360[ degrees

template <class T>
inline double
GenArc<T>::targetAngleDegrees() const
{
  return qgRadiansToDegrees(this->targetAngle());
}


// -------------------------------------------------------------------
// C E N T E R
// -------------------------------------------------------------------


// GET CENTER POINT

template <class T>
inline const GenPoint<T>&
GenArc<T>::accessCenter() const
{
  return this->_center;
}


// GET A COPY OF THE CENTER POINT

template <class T>
inline GenPoint<T>
GenArc<T>::center() const
{
  return this->_center;
}


// GET X COORDINATE OF CENTER POINT

template <class T>
inline T
GenArc<T>::xCenter() const
{
  return (this->_center).x();
}


// GET Y COORDINATE OF CENTER POINT

template <class T>
inline T
GenArc<T>::yCenter() const
{
  return (this->_center).y();
}


// SET X COORDINATE OF THE CENTER POINT


template <class T>
inline void
GenArc<T>::setXCenter(T aX)
{
  (this->_center).setX(aX);
}


// SET Y COORDINATE OF THE CENTER POINT


template <class T>
inline void
GenArc<T>::setYCenter(T aY)
{
  (this->_center).setY(aY);
}


// SET THE CENTER POINT

template <class T>
inline void
GenArc<T>::setCenter(T aX, T aY)
{
  (this->_center).setXY(aX,aY);
}


// SET THE CENTER POINT

template <class T>
inline void
GenArc<T>::setCenter(const GenPoint<T>& aCenter)
{
  (this->_center) = aCenter;
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


template <class T>
GenArc<T>&
GenArc<T>::operator=(const GenArc<T>& anArc)
{
  // Are left hand side and right hand side different objects?
  if (this != &anArc)
    {
      AbstractGenPrimitive<T>::operator=(anArc);
      this->_center = anArc._center;
    }

  return *this;
}


// SAME AS FUNCTION qgar::GenArc::eq

template <class T>
inline bool
GenArc<T>::operator==(const GenArc<T>& anArc) const
{
  return eq(anArc);
}


// SAME AS FUNCTION qgar::GenArc::notEq

template <class T>
inline bool
GenArc<T>::operator!=(const GenArc<T>& anArc) const
{
  return notEq(anArc);
}
  

// -------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S 
// -------------------------------------------------------------------


// EQUALITY

template <class T>
bool
GenArc<T>::eq(const GenArc<T>& anArc) const
{
  return
       (this->_source == anArc._source) 
    && (this->_target == anArc._target)
    && (this->_center == anArc._center);
}


// INEQUALITY

template <class T>
bool
GenArc<T>::notEq(const GenArc<T>& anArc) const
{
  return
       (this->_source != anArc._source) 
    || (this->_target != anArc._target)
    || (this->_center != anArc._center);
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenArc<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "Arc");

  qgReadObjData(anInStream, this->_source);
  qgReadObjData(anInStream, this->_target);
  qgReadObjData(anInStream, this->_center);

  return anInStream;
}


template <class T>
std::ostream& 
GenArc<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "Arc("
	      << this->source()
	      << ")("
	      << this->target()
	      << ")("
	      << this->center()
	      << ')';
  return anOutStream;
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// V            IMPLEMENTATION OF PURE VIRTUAL FUNCTIONS             V
// V               INHERITED FROM AbstractGenPrimitive               V
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


// -------------------------------------------------------------------
// G E O M E T R I C A L   S T R U C T U R E   U P D A T E S
// -------------------------------------------------------------------


// THE SOURCE HAS BEEN CHANGED

template <class T>
void
GenArc<T>::updateSource()
{
  // NOTHING TO DO
}


// THE TARGET HAS BEEN CHANGED

template <class T>
void
GenArc<T>::updateTarget()
{
  // NOTHING TO DO
}


// BOTH SOURCE AND TARGET HAVE BEEN CHANGED

template <class T>
void
GenArc<T>::updateSourceTarget()
{
  // NOTHING TO DO
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
inline void
GenArc<T>::translate(T aTransX, T aTransY)
{
  this->setSourceTarget(this->xSource() + aTransX,
			this->ySource() + aTransY,
			this->xTarget() + aTransX,
			this->yTarget() + aTransY);

  this->setCenter(_center.x() + aTransX, _center.y() + aTransY);
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar
