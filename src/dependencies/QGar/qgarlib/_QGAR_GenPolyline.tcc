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
 * @file    _QGAR_GenPolyline.tcc
 * @brief   Implementation of function members of class qgar::GenPolyline.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 14, 2004  18:01
 * @since   Qgar 2.2
 */


// STD
#include <algorithm>
#include <deque>
#include <iterator>
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
GenPolyline<T>::GenPolyline()

  : AbstractGenPrimitive<T>(0, 0, 0, 0)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class T>
GenPolyline<T>::GenPolyline(const GenPolyline<T>& aPoly)

  : AbstractGenPrimitive<T>(aPoly._source, aPoly._target),
    _vertices(aPoly._vertices)

{
  // VOID
}


// INITIALIZE FROM A Qgar POLYLINE

template <class T>
GenPolyline<T>::GenPolyline(const GenQgarPolyline<T>& aQPoly)

  : AbstractGenPrimitive<T>(aQPoly.accessSource(),
			    aQPoly.accessTarget()),
    _vertices(aQPoly.accessVertices())

{
  // VOID
}


// INITIALIZE FROM A Qgar SEGMENT

template <class T>
GenPolyline<T>::GenPolyline(const GenQgarSegment<T>& aQSeg)

  : AbstractGenPrimitive<T>(aQSeg.source(), aQSeg.target())

{
  _vertices.push_back(this->_source);
  _vertices.push_back(this->_target);
}


// INITIALIZE FROM A (GEOMETRICAL) SEGMENT

template <class T>
GenPolyline<T>::GenPolyline(const GenSegment<T>& aSeg)

  : AbstractGenPrimitive<T>(aSeg.source(), aSeg.target())

{
  _vertices.push_back(this->_source);
  _vertices.push_back(this->_target);
}


// INITIALIZE FROM TWO VERTICES: SOURCE AND TARGET

template <class T>
GenPolyline<T>::GenPolyline(const GenPoint<T>& aSource,
			    const GenPoint<T>& aTarget)

  : AbstractGenPrimitive<T>(aSource, aTarget)

{
  _vertices.push_front(aSource);
  _vertices.push_back(aTarget);
}


// INITIALIZE FROM A LIST OF AT LEAST TWO VERTICES

template <class T>
GenPolyline<T>::GenPolyline(const std::list< GenPoint<T> >& aPtList)



  // The points of the given list are copied in the vertices list
  : _vertices(aPtList.begin(), aPtList.end())

{
  if (aPtList.size() < 2)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenPolyline<T>::GenPolyline(const std::list< qgar::GenPoint<T> >&)",
			  "Cannot create a polyline including less than 2 vertices.");
    }

  // Update source and target.
  this->_source = aPtList.front();
  this->_target = aPtList.back();
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class T>
GenPolyline<T>::~GenPolyline()
{
  // VOID
}


// -------------------------------------------------------------------
// C O P Y
// -------------------------------------------------------------------


// DEEP COPY

template <class T>
GenPolyline<T>*
GenPolyline<T>::clone() const
{
  return new GenPolyline<T>(*this);
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

template <class T>
GenPolyline<T>&
GenPolyline<T>::operator=(const GenPolyline<T>& aPoly)
{
  // Are left hand side and right hand side different objects?
  if (this != &aPoly)
    {
      AbstractGenPrimitive<T>::operator=(aPoly);
      this->_vertices = aPoly._vertices;
    }

  return *this;
}


// -------------------------------------------------------------------
// A C C E S S   T O   V E R T I C E S
// -------------------------------------------------------------------


// GET NUMBER OF VERTICES

template <class T>
inline int
GenPolyline<T>::size() const
{
  return (int) _vertices.size();
}


// GET THE LIST OF VERTICES

template <class T>
const std::deque< GenPoint<T> >&
GenPolyline<T>::accessVertices() const
{
  return this->_vertices;
}


// GIVE NON-PROTECTED ACCESS TO THE VERTICES

template <class T>
inline std::deque< GenPoint<T> >&
GenPolyline<T>::getVertices()
{
  return this->_vertices;
}


// GET A COPY OF THE LIST OF VERTICES

template <class T>
std::deque< GenPoint<T> >
GenPolyline<T>::vertices() const
{
  return this->_vertices;
}


// -------------------------------------------------------------------
// I N S E R T   V E R T I C E S
// -------------------------------------------------------------------


// INSERT A POINT AS NEW SOURCE

template <class T>
GenPolyline<T>&
GenPolyline<T>::appendSource(const GenPoint<T>& aPt)
{
  this->_source = aPt;
  _vertices.push_front(aPt);   
  return *this;
}
 

// INSERT A POINT AS NEW TARGET

template <class T>
GenPolyline<T>&
GenPolyline<T>::appendTarget(const GenPoint<T>& aPt)
{
  this->_target = aPt;
  this->_vertices.push_back(aPt);
  return *this;
}


// APPEND A POLYLINE

template<class T>
GenPolyline<T>&
GenPolyline<T>::append(const GenPolyline<T>& aPoly)
{
  // Copy the vertices of the given polyline
  std::copy(aPoly.accessVertices().begin(), 
	    aPoly.accessVertices().end(),
	    back_inserter(this->_vertices));

  // Update target
  this->_target = aPoly.target();

  return *this;
}


// APPEND A QGAR POLYLINE

template<class T>
GenPolyline<T>&
GenPolyline<T>::append(const GenQgarPolyline<T>& aQPoly)
{
  // Copy the vertices of the given polyline
  std::copy(aQPoly.accessVertices().begin(), 
	    aQPoly.accessVertices().end(),
	    back_inserter(this->_vertices));

  // Update target
  this->_target = aQPoly.target();

  return *this;
}


// APPEND A VECTOR OF POINTS

template<class T>
GenPolyline<T>&
GenPolyline<T>::append(const std::vector<GenPoint<T> >& aPtVect)
{
  std::copy(aPtVect.begin(), aPtVect.end(),
	    back_inserter(this->_vertices));
  
  // Update target, new target is the last vertex of the vector.
  this->_target = aPtVect.back();

  return *this;
}


// -------------------------------------------------------------------
// R E M O V E   V E R T I C E S
// -------------------------------------------------------------------


// REMOVE A VERTEX FROM THE POLYLINE

template <class T>
GenPolyline<T>&
GenPolyline<T>::remove(const GenPoint<T>& aPt)



{
  // The list of vertices must always include 2 elements at least
  if (_vertices.size() == 2)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> qgar::GenPolyline<T>& qgar::GenPolyline<T>::remove(const qgar::GenPoint<T>&)",
			  "Cannot remove a vertex from a polyline including 2 vertices.");
    }

  if ( aPt == _vertices.front() )
    {
      // Remove first element
      _vertices.pop_front();

      // New first element becomes the source of this polyline.
      this->_source = _vertices.front();
    }
  else if ( aPt == _vertices.back() )
    {
      // Remove last element
      _vertices.pop_back();

      // New last element becomes the target of this polyline.
      this->_target = _vertices.back();
    }
  else
    {
      typename std::deque<GenPoint<T> >::iterator it =
	find(_vertices.begin(), _vertices.end(), aPt);
  
      // Remove vertex if found
      if ( it != _vertices.end() )
	{
	  _vertices.erase(it);
	}
    }

  return *this;
}


// -------------------------------------------------------------------
// CONVERSIONS OF THE LIST OF VERTICES
// -------------------------------------------------------------------


// GET A VECTOR OF POINTS FROM THE LIST OF VERTICES

template <class T>
std::vector< GenPoint<T> >
GenPolyline<T>::toPointVector()
{
  std::vector< GenPoint<T> > ptVector;

  // Copy all vertices in the vector created above
  std::copy(_vertices.begin(),
	    _vertices.end(), 
	    std::back_inserter(ptVector));
  
  return ptVector;
}


// GET A LIST OF (GEOMETRICAL) SEGMENTS FROM THE LIST OF VERTICES

template <class T>
std::list<GenSegment<T> >
GenPolyline<T>::toSegList()
{
  typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();
  std::list<GenSegment<T> > segList;
  

  // Current source point
  GenPoint<T> source = *itDP;

  // Current target point
  GenPoint<T> target = *(++itDP);

  do
    {
      segList.push_back(GenSegment<T>(source, target));
    
      source = target;
      target = *(++itDP);
    }
  while (itDP != _vertices.end()) ;

  return segList;
}


// GET A LIST OF QGAR SEGMENTS FROM THE LIST OF VERTICES

template <class T>
std::list<GenQgarSegment<T> >
GenPolyline<T>::toQgarSegList(int aThickness,
			      QGEcolor aColor,
			      QGEoutline anOutline)
{
  typename std::deque< GenPoint<T> >::iterator itDP = _vertices.begin();
  std::list<GenQgarSegment<T> > segList;
  
  // Current source
  GenPoint<T> source = *itDP;
  
  // Current target
  GenPoint<T> target = *(++itDP);

  do
    {
      // Current target
      segList.push_back(GenQgarSegment<T>(source,
					  target,
					  aThickness,
					  aColor,
					  anOutline));
      source = target;
      target = *(++itDP);
    }
  while ( itDP != _vertices.end() );

  return segList;
}


// -------------------------------------------------------------------
// S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
// -------------------------------------------------------------------


template <class T>
inline std::istream& 
GenPolyline<T>::read(std::istream& anInStream)
{
  // Skip name
  qgReadObjName(anInStream, "Polyline");

  // Get source and target
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
inline std::ostream& 
GenPolyline<T>::write(std::ostream& anOutStream) const
{
  // Source, target and vertices number

  anOutStream << "Polyline("
	      << this->_source
	      << ")("
	      << this->_target
	      << ")("
	      << (this->_vertices).size()
	      << ')';

  // Vertices

  for(typename std::deque< GenPoint<T> >::const_iterator
	itDP = (this->_vertices).begin();
      itDP != (this->_vertices).end();
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
// V               INHERITED FROM AbstractGenPrimitive               V
// V                                                                 V
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV


// -------------------------------------------------------------------
// G E O M E T R I C A L   S T R U C T U R E   U P D A T E S
// -------------------------------------------------------------------


// THE SOURCE HAS BEEN CHANGED

template <class T>
void
GenPolyline<T>::updateSource()
{
  (this->_vertices.front()).setXY((this->_source).x(), (this->_source).y());
}


// THE TARGET HAS BEEN CHANGED

template <class T>
void
GenPolyline<T>::updateTarget()
{
  (this->_vertices.back()).setXY((this->_target).x(), (this->_target).y());
}


// BOTH SOURCE AND TARGET HAVE BEEN CHANGED

template <class T>
void
GenPolyline<T>::updateSourceTarget()
{
  this->updateSource();
  this->updateTarget();
}


// -------------------------------------------------------------------
// G E O M E T R Y :   T R A N S L A T I O N 
// -------------------------------------------------------------------


template <class T>
inline void
GenPolyline<T>::translate(T aTransX, T aTransY)
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
