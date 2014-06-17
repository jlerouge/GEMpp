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
 * @file   _QGAR_GenQgarPolygon.tcc
 * @brief  Implementation of function members
 *         of class qgar::GenQgarPolygon.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  17:27
 * @since  Qgar 2.2
 */



// STD
#include <deque>
#include <iostream>
#include <list>
#include <vector>
// QGAR
#include "ISerializable.h"
#include "QgarErrorUser.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenQgarPolygon<T>::GenQgarPolygon(int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline)

{
  // VOID
}


// COPY-CONSTRUCTOR

template <class T>
GenQgarPolygon<T>::GenQgarPolygon(const GenQgarPolygon<T>& aQPoly)

  : AbstractGenQgarPrimitive<T>(aQPoly._thickness,
				aQPoly._color,
				aQPoly._outline),
    _geomStructure(aQPoly._geomStructure)

{
  // VOID
}


// INITIALIZE FROM A GEOMETRICAL POLYGON

template <class T>
GenQgarPolygon<T>::GenQgarPolygon(const GenPolygon<T>& aPoly,
				  int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline),
    _geomStructure(aPoly)

{
  // VOID
}


// INITIALIZE FROM A LIST OF AT LEAST 3 POINTS

template <class T>
GenQgarPolygon<T>::GenQgarPolygon(const std::list< GenPoint<T> >& aPtList,
				  int aThickness,
				  QGEcolor aColor,
				  QGEoutline anOutline)



  : AbstractGenQgarPrimitive<T>(aThickness, aColor, anOutline)

{
  if (aPtList.size() < 3)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenQgarPolygon<T>::GenQgarPolygon(const std::list< qgar::GenPoint<T> >&, int, qgar::QGEcolor, qgar::QGEoutline)",
			  "Cannot create a polygon including less than 3 vertices.");
    }

  _geomStructure = GenPolygon<T>(aPtList);
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenQgarPolygon<T>::~GenQgarPolygon()
{
  // VOID
}


// -------------------------------------------------------------------
// COPY
// -------------------------------------------------------------------


// DEEP COPY

template <class T>
GenQgarPolygon<T>*
GenQgarPolygon<T>::clone() const
{
  return new GenQgarPolygon<T>(*this);
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenQgarPolygon<T>&
GenQgarPolygon<T>::operator=(const GenQgarPolygon<T>& aQPoly)
{
  // Are left hand side and right hand side different objects?
  if (this != &aQPoly)
    {
      AbstractGenQgarPrimitive<T>::operator=(aQPoly);
      _geomStructure = aQPoly._geomStructure;
    }

  return *this;
}


// -------------------------------------------------------------------
// ACCESS TO THE GEOMETRICAL STRUCTURE
// -------------------------------------------------------------------


// GET THE STRUCTURE IMPLEMENTING
// THE GEOMETRICAL ASPECT OF A QGAR POLYGON

template <class T>
inline const GenPolygon<T>&
GenQgarPolygon<T>::accessGeomStructure() const
{
  return _geomStructure;
}


// -------------------------------------------------------------------
// A R E A
// -------------------------------------------------------------------


// GET SIGNED AREA

template <class T>
inline double
GenQgarPolygon<T>::signedArea()
{
  return _geomStructure.signedArea();
}


// GET AREA

template <class T>
inline double
GenQgarPolygon<T>::area()
{
  return _geomStructure.area();
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


// GET NUMBER OF VERTICES

template <class T>
inline int
GenQgarPolygon<T>::size() const
{
  return _geomStructure.size();
}


// GET VERTICES

template <class T>
inline const std::deque< GenPoint<T> >&
GenQgarPolygon<T>::accessVertices() const
{
  return _geomStructure.accessVertices();
}


// GIVE NON-PROTECTED ACCESS TO THE VERTICES

template <class T>
inline std::deque< GenPoint<T> >&
GenQgarPolygon<T>::getVertices()
{
  return _geomStructure.getVertices();
}


// GET A COPY OF VERTICES

template <class T>
inline std::deque< GenPoint<T> >
GenQgarPolygon<T>::vertices() const
{
  return _geomStructure.vertices();
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


// INSERT A POINT AS NEW SOURCE

template <class T>
GenQgarPolygon<T>&
GenQgarPolygon<T>::appendSource(const GenPoint<T>& aPt)
{
  _geomStructure.appendSource(aPt);
  return *this;
}


// INSERT A POINT AS NEW TARGET

template <class T>
GenQgarPolygon<T>&
GenQgarPolygon<T>::appendTarget(const GenPoint<T>& aPt)
{
  _geomStructure.appendTarget(aPt);
  return *this;
}


// APPEND A LIST OF POINTS

template<class T>
GenQgarPolygon<T>& 
GenQgarPolygon<T>::append(const std::vector< GenPoint<T> >& aPtVect)
{
  _geomStructure.append(aPtVect);
  return *this;
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


// REMOVE A VERTEX FROM THE POLYGON

template <class T>
GenQgarPolygon<T>&
GenQgarPolygon<T>::remove(const GenPoint<T>& aPt)



{
  // The polygon must always be provided with at least 3 vertices
  if ((_geomStructure.vertices()).size() == 3)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenQgarPolygon<T>& qgar::GenQgarPolygon<T>::remove(const qgar::GenPoint<T>&)",
			  "Cannot remove a vertex from a polygon including 3 vertices.");
    }

  _geomStructure.remove(aPt);
  return *this;
}


// -------------------------------------------------------------------
// CONVERSIONS OF THE SERIES OF VERTICES
// -------------------------------------------------------------------


// GET A VECTOR OF POINTS FROM THE VERTICES

template <class T>
inline std::vector< GenPoint<T> >
GenQgarPolygon<T>::toPointVector()
{
  return _geomStructure.toPointVector();
}


// GET A STL LIST OF (GEOMETRICAL) SEGMENTS FROM THE VERTICES

template <class T>
inline std::list< GenSegment<T> >
GenQgarPolygon<T>::toSegList()
{
  return _geomStructure.toSegList();
}


// GET A STL LIST OF QGAR SEGMENTS, PROVIDED WITH GIVEN ATTRIBUTES,
// FROM THE VERTICES

template <class T>
inline std::list< GenQgarSegment<T> >
GenQgarPolygon<T>::toQgarSegList()
{
  return _geomStructure.toQgarSegList(this->_thickness,
				      this->_color,
				      this->_outline);
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenQgarPolygon<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "QgarPolygon");

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
GenQgarPolygon<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "QgarPolygon("
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


// -------------------------------------------------------------------
// NON-PROTECTED ACCESS TO THE GEOMETRICAL ASPECT
// -------------------------------------------------------------------


// RETURN THE GEOMETRICAL ASPECT

template <class T>
inline AbstractGenPrimitive<T>&
GenQgarPolygon<T>::getGeomStructure()
{
  return _geomStructure;
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// V            IMPLEMENTATION OF PURE VIRTUAL FUNCTIONS             V
// V            INHERITED FROM AbstractGenQgarPrimitive              V
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
inline void
GenQgarPolygon<T>::translate(T aX, T aY)
{
  (this->_geomStructure).translate(aX, aY);
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar
