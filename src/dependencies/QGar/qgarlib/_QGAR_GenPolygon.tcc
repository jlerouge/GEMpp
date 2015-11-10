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
 * @file   _QGAR_GenPolygon.tcc
 * @brief  Implementation of function members
 *         of class qgar::GenPolygon.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 14, 2004  16:16
 * @since  Qgar 2.2
 */



// STD
#include <cmath>
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
GenPolygon<T>::GenPolygon()

  : AbstractGenPrimitive<T>(0, 0, 0, 0)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenPolygon<T>::GenPolygon(const GenPolygon<T>& aPoly)

  : AbstractGenPrimitive<T>(aPoly._source, aPoly._target),
    _vertices(aPoly._vertices)

{
  // VOID
}


// INITIALIZE FROM A Qgar POLYGON

template <class T>
GenPolygon<T>::GenPolygon(const GenQgarPolygon<T>& aQPoly)

  : AbstractGenPrimitive<T>(aQPoly.accessSource(),
			    aQPoly.accessTarget()),
    _vertices(aQPoly.accessVertices())

{
  // VOID
}


// INITIALIZE FROM A STL LIST OF AT LEAST 3 POINTS

template <class T>
GenPolygon<T>::GenPolygon(const std::list< GenPoint<T> >& aPtList)



{
  if (aPtList.size() < 3)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenPolygon<T>::GenPolygon(const std::list< qgar::GenPoint<T> >&)",
			  "Cannot create a polygon including less than 3 vertices");
    }

  // Create vertices by copying the given list
  for (typename std::list< GenPoint<T> >::const_iterator itPL = aPtList.begin() ;
       itPL != aPtList.end() ;
       ++itPL)
    {
      _vertices.push_back(*itPL);
    }

  // Update source and target.
  this->_source = aPtList.front();
  this->_target = aPtList.back();
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenPolygon<T>::~GenPolygon()
{
  // VOID
}


// -------------------------------------------------------------------
// C O P Y 
// -------------------------------------------------------------------


// DEEP COPY

template <class T>
GenPolygon<T>*
GenPolygon<T>::clone() const
{
  return new GenPolygon<T>(*this);
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenPolygon<T>&
GenPolygon<T>::operator=(const GenPolygon<T>& aPoly)
{
  // Are left hand side and right hand side different objects?
  if (this != &aPoly)
    {
      AbstractGenPrimitive<T>::operator=(aPoly);
      _vertices = aPoly._vertices;
    }

  return *this;
}


// -------------------------------------------------------------------
// A R E A
// -------------------------------------------------------------------


// GET SIGNED AREA

template <class T>
double
GenPolygon<T>::signedArea()
{
  typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();

  // First vertex
  double x1 = (double) (*itDP).x();
  double y1 = (double) (*itDP).y();
  // Previous vertex (in loop)
  double xp = x1;
  double yp = y1;
  ++itDP;

  // The area
  double area = 0.;

  while (itDP != _vertices.end())
    {
      // Current vertice
      double xc = (double) (*itDP).x();
      double yc = (double) (*itDP).y();

      // Update area
      area += (xp * yc) - (yp * xc);

      // Current vertex becomes previous vertex
      xp = xc;
      yp = yc;

      // Next vertex
      ++itDP;
    }

  // Last vertex and first vertex to complete computation
  area += (xp * y1) - (yp * x1);

  return area / 2.;
}


// GET AREA

template <class T>
inline double
GenPolygon<T>::area()
{
  return std::fabs(signedArea());
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


// GET NUMBER OF VERTICES

template <class T>
inline int
GenPolygon<T>::size() const
{
  return _vertices.size();
}


// GET VERTICES

template <class T>
inline const std::deque< GenPoint<T> >&
GenPolygon<T>::accessVertices() const
{
  return this->_vertices;
}


// GIVE NON-PROTECTED ACCESS TO THE VERTICES

template <class T>
inline std::deque< GenPoint<T> >&
GenPolygon<T>::getVertices()
{
  return this->_vertices;
}


// GET A COPY OF VERTICES

template <class T>
inline std::deque< GenPoint<T> >
GenPolygon<T>::vertices() const
{
  return this->_vertices;
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


// INSERT A POINT AS NEW SOURCE

template <class T>
GenPolygon<T>&
GenPolygon<T>::appendSource(const GenPoint<T>& aPt)
{
  this->_source = aPt;
  this->_vertices.push_front(aPt);   
  return *this;
}
 

// INSERT A POINT AS NEW TARGET

template <class T>
GenPolygon<T>&
GenPolygon<T>::appendTarget(const GenPoint<T>& aPt)
{
  this->_target = aPt;
  this->_vertices.push_back(aPt);
  return *this;
}


// APPEND A STL VECTOR OF POINTS

template<class T>
GenPolygon<T>&
GenPolygon<T>::append(const std::vector<GenPoint<T> >& aPtVector)
{
  std::copy(aPtVector.begin(),
	    aPtVector.end(),
	    back_inserter(this->_vertices));
  
  // Update target: New target is the last point of the given list
  this->_target = aPtVector.back();

  return *this;
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


// REMOVE A VERTICE FROM THE POLYGON

template <class T>
GenPolygon<T>&
GenPolygon<T>::remove(const GenPoint<T>& aPt)



{
  // The polygon must always be provided with at least 3 vertices
  if (this->_vertices.size() == 3)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenPolygon<T>& qgar::GenPolygon<T>::remove(const qgar::GenPoint<T>&)",
			  "Cannot remove a vertex from a polygon including 3 vertices");
    }

  if (aPt == (this->_vertices).front())
    {
      // Remove first element
      (this->_vertices).pop_front();

      // New first element becomes the source of the polygon
      this->_source = this->_vertices.front();
    }
  else if (aPt == (this->_vertices).back())
    {
      // Remove last element
      _vertices.pop_back();

      // New last element becomes the source of the polygon
      this->_target = _vertices.back();
    }
  else
    {
      typename std::deque<GenPoint<T> >::iterator it =
	find((this->_vertices).begin(), (this->_vertices).end(), aPt);
  
      // Remove vertex if found
      if (it != (this->_vertices).end())
	{
	  (this->_vertices).erase(it);
	}
    }

  return *this;
}


// -------------------------------------------------------------------
// CONVERSIONS OF THE SERIES OF VERTICES
// -------------------------------------------------------------------


// GET A VECTOR OF POINTS FROM THE LIST OF VERTICES

template <class T>
std::vector< GenPoint<T> >
GenPolygon<T>::toPointVector()
{
  std::vector< GenPoint<T> > ptVector;

  // Copy all vertices in the vector created above
  std::copy(_vertices.begin(),
	    _vertices.end(), 
	    std::back_inserter(ptVector));
  
  return ptVector;
}


// GET A STL LIST OF (GEOMETRICAL) SEGMENTS FROM THE VERTICES

template <class T>
std::list<GenSegment<T> >
GenPolygon<T>::toSegList()
{
  std::list< GenSegment<T> > segList;

  // Iterators on current and previous vertices
  typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();
  typename std::deque< GenPoint<T> >::iterator itDPP = itDP;
  ++itDP;

  for ( ; itDP != _vertices.end() ; ++itDP)
    {
      // Create current segment
      segList.push_back(GenSegment<T>(*itDPP, *itDP));

      // Update previous vertex
      itDPP = itDP;
    }

  // Create last segment
  segList.push_back(GenSegment<T>(*itDPP, _vertices[0]));

  return segList;
}


// GET A STL LIST OF Qgar SEGMENTS FROM THE VERTICES

template <class T>
std::list<GenQgarSegment<T> >
GenPolygon<T>::toQgarSegList(int aThickness,
			     QGEcolor aColor,
			     QGEoutline anOutline)
{
  std::list< GenQgarSegment<T> > segList;

  // Iterators on current and previous vertices
  typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();
  typename std::deque< GenPoint<T> >::iterator itDPP = itDP;
  ++itDP;

  for ( ; itDP != _vertices.end() ; ++itDP)
    {
      // Create current segment
      segList.push_back(GenQgarSegment<T>(*itDPP,
					  *itDP,
					  aThickness,
					  aColor,
					  anOutline));

      // Update previous vertex
      itDPP = itDP;
    }

  // Create last segment
  segList.push_back(GenQgarSegment<T>(*itDPP,
				      _vertices[0],
				      aThickness,
				      aColor,
				      anOutline));

  return segList;
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N 
// -------------------------------------------------------------------


template <class T>
std::istream& 
GenPolygon<T>::read(std::istream& anInStream)
{
  // Skip name
  qgReadObjName(anInStream, "Polygon");

  // Source and target
  qgReadObjData(anInStream, this->_source);
  qgReadObjData(anInStream, this->_target);

  // Remove possible stored vertices
  (this->_vertices).clear();

  // Get vertices number
  int pointCnt;
  qgReadObjData(anInStream, pointCnt);
  
  // Get vertices, conforming to their initial ordering
  for(int iCnt = 0 ; iCnt < pointCnt ; ++iCnt)
    {
      GenPoint<T> point;
      qgReadObjData(anInStream, point);
      (this->_vertices).push_back(point);
    }

  return anInStream;
}


template <class T>
std::ostream& 
GenPolygon<T>::write(std::ostream& anOutStream) const
{
  // Source, target and vertices number

  anOutStream << "Polygon("
	      << this->source()
	      << ")("
	      << this->target()
	      << ")("
	      << (this->accessVertices()).size()
	      << ')';

  // Vertices

  for(typename std::deque< GenPoint<T> >::const_iterator itDP
	= (this->accessVertices()).begin();
      itDP != (this->accessVertices()).end();
      ++itDP)
    {
      anOutStream << '('
		  << *itDP
		  << ')';
    }

  return anOutStream;
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// V            IMPLEMENTATION OF PURE VIRTUAL FUNCTIONS             V
// V              INHERITED FROM AbstractGenPrimitive                V
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


// -------------------------------------------------------------------
// G E O M E T R I C A L   S T R U C T U R E   U P D A T E S
// -------------------------------------------------------------------


// THE SOURCE HAS BEEN CHANGED

template <class T>
void
GenPolygon<T>::updateSource()
{
  (_vertices.front()).setXY(this->_source.x(), this->_source.y());
}


// THE TARGET HAS BEEN CHANGED

template <class T>
void
GenPolygon<T>::updateTarget()
{
  (_vertices.back()).setXY(this->_target.x(), this->_target.y());
}


// BOTH SOURCE AND TARGET HAVE BEEN CHANGED

template <class T>
void
GenPolygon<T>::updateSourceTarget()
{
  this->updateSource();
  this->updateTarget();
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
void
GenPolygon<T>::translate(T aTransX, T aTransY)
{
  // Translate source and target
  this->setSourceTarget(this->xSource() + aTransX,
			this->ySource() + aTransY,
			this->xTarget() + aTransX,
			this->yTarget() + aTransY);

  // Translate vertices
  for(typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();
      itDP < _vertices.end();
      ++itDP)
    {
      (*itDP).translate(aTransX, aTransY);
    }
}


// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


} // namespace qgar 
