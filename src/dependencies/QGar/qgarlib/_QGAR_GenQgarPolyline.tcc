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
 * @file _QGAR_GenQgarPolyline.tcc
 *
 * @brief Implementation of function members of class qgar::GenQgarPolyline.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  18:19
 * @since  Qgar 2.2
 */



// STD
#include <deque>
#include <iostream>
#include <list>
#include <vector>
// QGAR
#include "ISerializable.h"



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(int aThickness,
				    QGEcolor aColor,
				    QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness,
				aColor,
				anOutline)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const GenQgarPolyline<T>& aQPoly)

  : AbstractGenQgarPrimitive<T>(aQPoly._thickness,
				aQPoly._color,
				aQPoly._outline),
    _geomStructure(aQPoly._geomStructure)

{
  // VOID
}


// INITIALIZE FROM A GEOMETRICAL POLYLINE

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const GenPolyline<T>& aPoly,
				    int aThickness,
				    QGEcolor aColor,
				    QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness,
				aColor,
				anOutline),
    _geomStructure(aPoly)

{
  // VOID
}


// INITIALIZE FROM A QGAR SEGMENT

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const GenQgarSegment<T>& aQSeg)

  : AbstractGenQgarPrimitive<T>(aQSeg.thickness(),
				aQSeg.color(),
				aQSeg.outline())

{
  _geomStructure = GenPolyline<T>(aQSeg.accessGeomStructure());
}


// INITIALIZE FROM A (GEOMETRICAL) SEGMENT

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const GenSegment<T>& aSeg,
				    int aThickness,
				    QGEcolor aColor,
				    QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness,
				aColor,
				anOutline)

{
  _geomStructure = GenPolyline<T>(aSeg);
}


// INITIALIZE FROM SOURCE AND TARGET

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const GenPoint<T>& aSource,
				    const GenPoint<T>& aTarget,
				    int        aThickness,
				    QGEcolor   aColor,
				    QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness,
				aColor,
				anOutline),
    _geomStructure(aSource, aTarget)
{
  // VOID
}


// INITIALIZE FROM A LIST OF AT LEAST 2 POINTS

template <class T>
GenQgarPolyline<T>::GenQgarPolyline(const std::list< GenPoint<T> >& aPtList,
				    int aThickness,
				    QGEcolor aColor,
				    QGEoutline anOutline)

  : AbstractGenQgarPrimitive<T>(aThickness,
				aColor,
				anOutline)

{
  _geomStructure = GenPolyline<T>(aPtList);
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

template <class T>
GenQgarPolyline<T>::~GenQgarPolyline()
{
  // VOID
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// DEEP COPY

template <class T>
GenQgarPolyline<T>*
GenQgarPolyline<T>::clone() const
{
  return new GenQgarPolyline<T>(*this);
}


// -------------------------------------------------------------------
// OPERATORS
// -------------------------------------------------------------------


// Assignment.
template <class T>
GenQgarPolyline<T>&
GenQgarPolyline<T>::operator=(const GenQgarPolyline<T>& aQPoly)
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
// THE GEOMETRICAL ASPECT OF A QGAR POLYLINE

template <class T>
inline const GenPolyline<T>&
GenQgarPolyline<T>::accessGeomStructure() const
{
  return _geomStructure;
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


// GET NUMBER OF VERTICES

template <class T>
inline int
GenQgarPolyline<T>::size() const
{
  return _geomStructure.size();
}


// GET VERTICES

template <class T>
inline const std::deque< GenPoint<T> >&
GenQgarPolyline<T>::accessVertices() const
{
  return _geomStructure.accessVertices();
}


// GIVE NON-PROTECTED ACCESS TO THE VERTICES

template <class T>
inline std::deque< GenPoint<T> >&
GenQgarPolyline<T>::getVertices()
{
  return _geomStructure.getVertices();
}


// GET A COPY OF VERTICES

template <class T>
inline std::deque< GenPoint<T> >
GenQgarPolyline<T>::vertices() const
{
  return _geomStructure.vertices();
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


// ADD A POINT AS NEW SOURCE

template <class T>
GenQgarPolyline<T>&
GenQgarPolyline<T>::appendSource(const GenPoint<T>& aPt)
{
  _geomStructure.appendSource(aPt);
  return *this;
}


// ADD A POINT AS NEW TARGET

template <class T>
GenQgarPolyline<T>&
GenQgarPolyline<T>::appendTarget(const GenPoint<T>& aPt)
{
  _geomStructure.appendTarget(aPt);
  return *this;
}


// APPEND A QGAR POLYLINE

template<class T>
GenQgarPolyline<T>& 
GenQgarPolyline<T>::append(const GenQgarPolyline<T>& aQPoly)
{
  _geomStructure.append(aQPoly);
  return *this;
}


// APPEND A POLYLINE

template<class T>
GenQgarPolyline<T>& 
GenQgarPolyline<T>::append(const GenPolyline<T>& aPoly)
{
  _geomStructure.append(aPoly);
  return *this;
}


// APPEND A VECTOR OF POINTS

template<class T>
GenQgarPolyline<T>& 
GenQgarPolyline<T>::append(const std::vector<GenPoint<T> >& aPtVect)
{
  _geomStructure.append(aPtVect);
  return *this;
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


// REMOVE A VERTEX

template <class T>
GenQgarPolyline<T>&
GenQgarPolyline<T>::remove(const GenPoint<T>& aPt)
{
  _geomStructure.remove(aPt);
  return *this;
}


// -------------------------------------------------------------------
// CONVERSIONS OF THE SERIES OF VERTICES
// -------------------------------------------------------------------


// GET A VECTOR OF POINTS FROM THE LIST OF VERTICES

template <class T>
inline std::vector< GenPoint<T> >
GenQgarPolyline<T>::toPointVector()
{
  return _geomStructure.toPointVector();
}


// GET A STL LIST OF (GEOMETRICAL) SEGMENTS FROM THE VERTICES

template <class T>
inline std::list<GenSegment<T> >
GenQgarPolyline<T>::toSegList()
{
  return _geomStructure.toSegList();
}


// GET A STL LIST OF QGAR SEGMENTS FROM THE VERTICES

template <class T>
inline std::list< GenQgarSegment<T> >
GenQgarPolyline<T>::toQgarSegList()
{
  return _geomStructure.toQgarSegList(this->_thickness, 
				      this->_color,
				      this->_outline);
}


// -------------------------------------------------------------------
// NON-PROTECTED ACCESS TO THE GEOMETRICAL ASPECT
// -------------------------------------------------------------------


// RETURN THE GEOMETRICAL ASPECT

template <class T>
inline AbstractGenPrimitive<T>&
GenQgarPolyline<T>::getGeomStructure()
{
  return _geomStructure;
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
inline std::istream& 
GenQgarPolyline<T>::read(std::istream& anInStream)
{
  qgReadObjName(anInStream, "QgarPolyline");

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
inline std::ostream& 
GenQgarPolyline<T>::write(std::ostream& anOutStream) const
{
  anOutStream << "QgarPolyline("
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
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
inline void
GenQgarPolyline<T>::translate(T aX, T aY)
{
  (this->_geomStructure).translate(aX, aY);
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar 
