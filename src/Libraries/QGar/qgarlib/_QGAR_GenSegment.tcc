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
 * @file   _QGAR_GenSegment.tcc
 * @brief  Implementation of function members of class qgar::GenSegment.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  18:28
 * @since  Qgar 2.2
 */



// STD
#include <cmath>
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
GenSegment<T>::GenSegment()
{
   // VOID
}


// COPY-CONSTRUCTOR

template <class T>
GenSegment<T>::GenSegment(const GenSegment<T>& aSeg)

  : AbstractGenPrimitive<T>(aSeg)

{
  // VOID
}


// INITIALIZE FROM A QGAR SEGMENT

template <class T>
GenSegment<T>::GenSegment(const GenQgarSegment<T>& aQSeg)

  : AbstractGenPrimitive<T>(aQSeg.accessSource(),
			    aQSeg.accessTarget())

{
  // VOID
}


// INITIALIZE FROM SOURCE AND TARGET POINTS

template <class T>
GenSegment<T>::GenSegment(const GenPoint<T>& aSource,
			  const GenPoint<T>& aTarget)

  : AbstractGenPrimitive<T>(aSource, aTarget)

{
  // VOID
}


// INITIALIZE FROM COORDINATES

template <class T>
GenSegment<T>::GenSegment(const T aXSource,
			  const T aYSource,
			  const T aXTarget,
			  const T aYTarget)

  : AbstractGenPrimitive<T>(aXSource, aYSource, aXTarget, aYTarget)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T> GenSegment<T>::~GenSegment()
{
  // VOID
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


template <class T>  
GenSegment<T>*
GenSegment<T>::clone() const
{
  return new GenSegment<T>(*this);
}


// -------------------------------------------------------------------
// ACCESS TO GEOMETRICAL CHARACTERISTICS
// -------------------------------------------------------------------


// GET SEGMENT LENGTH

template <class T>
inline double
GenSegment<T>::length() const
{
  return hypot(this->dx(), this->dy());
}


// GET SEGMENT SQUARED LENGTH

template <class T>
double
GenSegment<T>::sqr_length() const
{
  double l = this->length();
  return l * l;
}
 

// SIGNED DISTANCE BETWEEN (0,0) AND ITS PERPENDICULAR
// PROJECTION ONTO THE LINE SUPPORTING THE SEGMENT
// Precomputed

template <class T>
double
GenSegment<T>::rho() const
{
  // Signed distance between point (0,0) and its perpendicular
  // projection onto the line supporting the current segment.
  // The value is negative if the line supporting the current
  // segment intersects the Y axis at a negative value.

  // Let A (XA,YA) be the source point,
  //     B (XB,YB) be the target point,
  //     C (XC,YC) be the origin of the coordinate system
  //     L be the length of AB
  //     I be the projection of C onto line AB
  //
  // s = ((YA-YC)(XB-XA)-(XA-XC)(YB-YA)) / L**2  [EQN2]
  // (XC,YC) == 0
  // s = (YA(XB-XA) - XA(YB-YA)) / L**2
  // s = (YA*XB - XA*YB) / L**2
  //
  // Distance from C to I:
  //   rho = s*L = (YA*XB - XA*YB) / L

  return
    (double) qgAbs((this->ySource() * this->xTarget()) - (this->xSource() * this->yTarget()))
    / this->length();

  // _________________________________________________________________
  //
  // Let A,B,C,D be 2-space position vectors.
  // The directed line segments AB & CD are given by:
  //
  //   AB = A + r(B - A), r in [0,1]
  //   CD = C + s(D - C), s in [0,1]
  //
  // If AB & CD intersect, then:
  //
  //   A + r(B - A) = C + s(D - C)
  //:  XA + r(XB - XA) = XC + s(XD - XC)
  //   YA + r(YB - YA) = YC + s(YD - YC)  for r,s in [0,1]
  //
  // Solving the above for r and s yields:
  //
  //       ((YA - YC)(XD - XC)) - ((XA - XC)(YD - YC))
  //   r = -------------------------------------------    [EQN5]
  //       ((XB - XA)(YD - YC)) - ((YB - YA)(XD - XC))
  //
  //       ((YA - YC)(XB - XA)) - ((XA - XC)(YB - YA))
  //   s = -------------------------------------------    [EQN6]
  //       ((XB - XA)(YD - YC)) - ((Y B -YA)(XD - XC))
  //
  // Let I be the position vector of the intersection point, then:
  //
  //   I = A + r(B - A)
  //   XI = XA + r(XB - XA)   [EQN7]
  //   YI = YA + r(YB - YA)   [EQN8]
  // _________________________________________________________________
  //
  // Intersection of the line supporting AB
  // and the Y axis supporting segment CD
  //
  //   (XC,YC) = (0,0)
  //   (XD,YD) = (0,-1)
  //
  // In EQN5 and EQN6, the denominator is:
  //   d = ((XB - XA)(YD - YC)) - ((YB - YA)(XD - XC))
  //   d = ((XB - XA)(-1))      - ((YB - YA)(0))
  //   d = XA - XB
  // EQN5 is:
  //   r = ((YA - YC)(XD - XC) - (XA - XC)(YD - YC)) / d
  //   r = ((YA)     (0)       - (XA)     (-1))      / (XA - XB)
  //   r = XA / (XA - XB)
  // EQN8 is:
  //   YI = YA + r(YB - YA)
  //   YI = YA + XA (YB - YA) / (XA - XB)
  //   YI = (YA (XA - XB) + XA (YB - YA)) / (XA - XB)
  //   YI = (XA*YB - XB*YA) / (XA - XB)
  //   YI = -rho / (XA - XB) = rho / (XB - XA)
  // _________________________________________________________________
  //

  // The distance is negative if the line supporting the
  // segment intersects the Y axis at a negative value.
  //
  // WARNING: When the line is parallel to the Y axis, the sign is +
  // when the segment is oriented towards positive Y coordinates and
  // its X coordinates are positive, or when the segment is oriented
  // towards negative Y coordinates ans its X coordinates are negative.
  //
  //  if (this->dx() < 0)
  //    {
  //      return -rho;
  //    }
  //  else
  //    {
  //      return rho;
  //    }
}


// -------------------------------------------------------------------
// G E O M E T R Y :   A N G L E S 
// -------------------------------------------------------------------


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, 2PI[ RADIANS

template <class T>
inline double
GenSegment<T>::theta() const
{
  return qgAngle(this->_source, this->_target);
}


// SAME AS PREVIOUS

template <class T>
inline double
GenSegment<T>::angle() const
{
  return this->theta();
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN DEGREES

template <class T>
inline double
GenSegment<T>::thetaDegrees() const
{
  return qgRadiansToDegrees(this->theta());
}

// SAME AS PREVIOUS

template <class T>
inline double
GenSegment<T>::angleDegrees() const
{
  return qgRadiansToDegrees(this->theta());
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, PI[ RADIANS

template <class T>
inline double
GenSegment<T>::slope() const
{
  return qgSlope(this->accessSource(), this->accessTarget());
}


// ANGLE BETWEEN THE X AXIS AND THE SEGMENT, IN [0, 180[ DEGREES

template <class T>
inline double
GenSegment<T>::slopeDegrees() const
{
  return qgRadiansToDegrees(this->slope());
}


// -------------------------------------------------------------------
// G E O M E T R I C A L   P R E D I C A T E S
// -------------------------------------------------------------------


// DOES THE GIVEN POINT APPROXIMATELY BELONGS TO THE CURRENT SEGMENT?

template <class T>
inline bool
GenSegment<T>::contains(const GenPoint<T>& c, double aDist)
{
  // ________________________________________________________________
  //
  // Each coordinate is separately casted: If only the result
  // of the operations of the numerator of 'r' were casted,
  // overflows may occur when dealing with large integers or floats

  double xA = static_cast<double>(this->xSource());
  double yA = static_cast<double>(this->ySource());

  double xB = static_cast<double>(this->xTarget());
  double yB = static_cast<double>(this->yTarget());

  double yC = static_cast<double>(c.y());
  double xC = static_cast<double>(c.x());
  // ________________________________________________________________

  // Let C  be the point (XC,YC)
  //     AB be the line (XA,YA) to (XB,YB)
  //     L  be the length of the line segment AB
  //
  // r = ((YA-YC)(YA-YB)-(XA-XC)(XB-XA)) / L**2  [EQN1]
  //
  // Let I be the point of perpendicular projection of C onto AB.
  //
  //   if r < 0         I is on backward extension of AB
  //   if r > 1         I is on ahead extension of AB
  //   if 0 <= r <= 1   I is on AB

  double l = this->length();
  double r = (((yA - yC) * (yA - yB)) - ((xA - xC) * (xB - xA))) / (l * l);

  if ((r >= 0.) && (r <= 1.))
    {
      // C is on AB
      // => it must be close to AB
      return qgDist(c,*this) <= aDist;
    }
  else 
    {
      // C is on a backward or ahead extension of AB
      // => it must close to A or to B
      return    ( qgDist(c,this->accessSource()) <= aDist )
	     ||
                ( qgDist(c,this->accessTarget()) <= aDist );
    }
}


// SPECIALIZED VERSION, TO PRESERVE EFFICIENCY WHEN USING DOUBLES
// => no cast/local variable needed

template <>
inline bool
GenSegment<double>::contains(const GenPoint<double>& c, double aDist)
{
  double l = this->length();
  double r =   (  (-this->dy() * (this->ySource() - c.y()))
	        - ( this->dx() * (this->xSource() - c.x())))
             /
               (l * l);

  if ((r >= 0.) && (r <= 1.))
    {
      // C is on AB
      // => it must be close to AB
      return qgDist(c,*this) <= aDist;
    }
  else 
    {
      // C is on a backward or ahead extension of AB
      // => it must close to A or to B
      return    ( qgDist(c,this->accessSource()) <= aDist )
	     ||
                ( qgDist(c,this->accessTarget()) <= aDist );
    }
}
  

// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
inline GenSegment<T>&
GenSegment<T>::operator=(const GenSegment<T>& aSeg)
{
// ___________________________________________________________
//
// Test removed for more efficiency
// ___________________________________________________________
//
  // Are left hand side and right hand side different objects?
  //   if (this != &aSeg)
  //     {
// ___________________________________________________________

  AbstractGenPrimitive<T>::operator=(aSeg);
// ___________________________________________________________
//
  //     }
// ___________________________________________________________

  return *this;
}


// SAME AS FUNCTION qgar::GenSegment::eq

template <class T>
inline bool
GenSegment<T>::operator==(const GenSegment<T>& aSeg) const
{
  return eq(aSeg);
}


// SAME AS FUNCTION qgar::GenSegment::notEq

template <class T>
inline bool
GenSegment<T>::operator!=(const GenSegment<T>& aSeg) const
{
  return notEq(aSeg);
}
  

// -------------------------------------------------------------------
// F U N C T I O N A L   O P E R A T O R S 
// -------------------------------------------------------------------


// EQUALITY

template <class T>
bool
GenSegment<T>::eq(const GenSegment<T>& aSeg) const
{
  return (this->_source == aSeg._source) 
    && (this->_target == aSeg._target);
}


// INEQUALITY

template <class T>
bool
GenSegment<T>::notEq(const GenSegment<T>& aSeg) const
{
  return (this->_source != aSeg._source) 
    || (this->_target != aSeg._target);
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenSegment<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "Segment");

  qgReadObjData(anInStream, this->_source);
  qgReadObjData(anInStream, this->_target);

  return anInStream;
}

template <class T>
std::ostream& 
GenSegment<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "Segment("
 	      << this->_source
     	      << ")("
 	      << this->_target
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
GenSegment<T>::updateSource()
{
  // NOTHING TO DO
}


// THE TARGET HAS BEEN CHANGED

template <class T>
void
GenSegment<T>::updateTarget()
{
  // NOTHING TO DO
}


// BOTH SOURCE AND TARGET HAVE BEEN CHANGED

template <class T>
void
GenSegment<T>::updateSourceTarget()
{
  // NOTHING TO DO
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
inline void
GenSegment<T>::translate(T aTransX, T aTransY)
{
  this->setSourceTarget(this->xSource() + aTransX,
			this->ySource() + aTransY,
			this->xTarget() + aTransX,
			this->yTarget() + aTransY);
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar 
