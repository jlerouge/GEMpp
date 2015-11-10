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
 * @file  WDSegmentList.cpp
 * @brief Implementation of class qgar::WDSegmentList.
 *
 *        See file WDSegmentList.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  10:51
 * @since  Qgar 1.0
 */



// STD
#include <algorithm>
#include <cmath>
#include <cstdlib>
// QGAR
#include "AbstractGenPointChain.h"
#include "image.h"
#include "math.h"
#include "primitives.h"
#include "WDSegmentList.h"



using namespace std;



namespace qgar
{

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// L O C A L    C O N S T A N T S
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Maximum trivial direction change
static const int WALLDANIELSSONSEGMENTLIST_MAX_DIR_CHANGE = 1;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




/*---------------------------------------------------------------------*
 |                                                                     |
 |             C  L  A  S  S      W  D  S  E  G  M  E  N  T            |
 |                                                                     |
 *---------------------------------------------------------------------*/

// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR: CREATION OF A NULL SEGMENT

WDSegment::WDSegment()

  : _sqrLength(0),
    _approxFactor(0)

{
  // VOID
}


// CONSTRUCT FROM FULL DATA (USED DURING APPROXIMATION)

WDSegment::WDSegment(GenPoint<int>& orig,
		     int deltaX,
		     int deltaY,
		     QGEdirection d)

  : Segment(orig, orig),
    _sqrLength(deltaX * deltaX + deltaY * deltaY),
    _approxFactor(0),
    _direction(d)

{
  _target.translate(deltaX, deltaY);
}


// COPY CONSTRUCTOR

WDSegment::WDSegment(const WDSegment& aSeg)
{
  _source = aSeg._source;
  _target = aSeg._target;
  _sqrLength = aSeg._sqrLength;
  _approxFactor = aSeg._approxFactor;
  _direction = aSeg._direction;
}


// -------------------------------------------------------------------
// T R A N S F O R M A T I O N 
// -------------------------------------------------------------------


// SET SEGMENT FROM AN OTHER SEGMENT (MEMBER-TO-MEMBER COPY)

void
WDSegment::set(const WDSegment& aSeg)
{
  _source = aSeg._source;
  _target = aSeg._target;
  _sqrLength = aSeg._sqrLength;
  _approxFactor = aSeg._approxFactor;
  _direction = aSeg._direction;
}


// SET SEGMENT FROM GIVEN DATA.

void
WDSegment::set(GenPoint<int>& orig,
	       int deltaX,
	       int deltaY,
	       QGEdirection d)
{
  _source = orig;
  _target = orig;
  _target.translate(deltaX, deltaY);
  _sqrLength = deltaX * deltaX + deltaY * deltaY;
  _approxFactor = 0;
  _direction = d;
}


// TRANSLATE EXTREMUM POINT WITH GIVEN POINT

void WDSegment::translateTarget(GenPoint<int>& translation)
{
  _target += translation;
  
  // Work in relative coordinates
  Point p0 = _target - _source;
  _sqrLength = p0.x() * p0.x() + p0.y() * p0.y();

  int b1 = (abs(p0.x()) > (2 * abs(p0.y())));
  int b2 = (abs(p0.y()) > (2 * abs(p0.x())));

  _direction = (p0.x() > 0)
    ? (p0.y() > 0)
      ? (b1) ? QGE_DIRECTION_E : (b2) ? QGE_DIRECTION_S : QGE_DIRECTION_SE
      : (b1) ? QGE_DIRECTION_E : (b2) ? QGE_DIRECTION_N : QGE_DIRECTION_NE
    : (p0.y() > 0)
      ? (b1) ? QGE_DIRECTION_W : (b2) ? QGE_DIRECTION_S : QGE_DIRECTION_SE
      : (b1) ? QGE_DIRECTION_W : (b2) ? QGE_DIRECTION_N : QGE_DIRECTION_NW;
}


// -------------------------------------------------------------------
// O P E R A T O R S 
// -------------------------------------------------------------------


// ASSIGNMENT

WDSegment&
WDSegment::operator=(const WDSegment& w)
{
  _sqrLength = w._sqrLength;
  _approxFactor = w._approxFactor;
  _direction = w._direction;
  setSource(w.source());
  setTarget(w.target());
  return *this;
}


// -------------------------------------------------------------------






/*---------------------------------------------------------------------*
 |                                                                     |
 |       C  L  A  S  S      W  D  S  E  G  M  E  N  T  L  I  S  T      |
 |                                                                     |
 *---------------------------------------------------------------------*/

// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// CONSTRUCT FROM GIVEN CHAIN, USING GIVEN THRESHOLD

WDSegmentList::WDSegmentList(AbstractGenPointChain<int>& chain,
			     int wdThreshold)
{ 
  PRIVATEperform(chain, wdThreshold);
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

WDSegmentList::~WDSegmentList()
{
  // VOID
}


// -------------------------------------------------------------------
// COMPUTE THE WALL & DANIELSSON POLYGONAL APPROXIMATION OF A CHAIN
// -------------------------------------------------------------------
// Computer Vision, Graphics and Image Processing, 28:220-227, 1984
//
// Input parameters:
//    the chain to approximate
//    the W&D threshold
// -------------------------------------------------------------------

void
WDSegmentList::PRIVATEperform(AbstractGenPointChain<int>& aChain,
			      int wdThreshold)
{
  int ddist;
  int f;
  int l2;
  Point relativeCoords;
  WDSegment currseg;

  if (aChain.empty()) return; // nothing else to do
  
  // Initialize position in chain
  aChain.setToBegin();
  
  // Create first segment
  Point currpoint = aChain.current();
  WDSegment wdtmp(currpoint, 0, 0, QGE_DIRECTION_E);
//   push_back(wdtmp);
//   currseg = &back();

  currseg = wdtmp;
  _cutSeg.setSource(currpoint);  /*current point potential cut*/
  _cutSeg.setTarget(currpoint);
  _cutSeg.setApproxFactor(0);
  _cutSeg.setSqrLength(0);
  _cutSeg.setDirection(QGE_DIRECTION_E);
  
  while (aChain.hasNext())
    {
      Point prevpoint = currpoint;
      aChain.moveNext();
      currpoint = aChain.current();

      int dx = currpoint.x() - prevpoint.x();
      int dy = currpoint.y() - prevpoint.y();

      QGEdirection dir = qgDirection(dx, dy);
      Point translation = Point(dx, dy);

      /* call approximation algorithm */
      if(currseg.sqrLength() != 0)
	{
	  relativeCoords = currpoint - currseg.source();
	  f = currseg.approxFactor() + 
	    (relativeCoords.x() * translation.y() - 
	     relativeCoords.y() * translation.x());   /*new approximation*/

	  l2 = relativeCoords.x() * relativeCoords.x() +
	       relativeCoords.y() * relativeCoords.y();
	  
	  /*square of new length*/

	  if (   (abs(f) <= Math::QG_SQRT_MAX_INT16b)
	      && ((f * f) < (l2 * wdThreshold)))
	    {
	      /*if the new point can be added to current segment*/
	
	      int oldf = currseg.approxFactor(); 
	      int oldl2 = currseg.sqrLength();   /*save old values*/
	      QGEdirection olddir = currseg.direction();

	      currseg.translateTarget(translation);
	      currseg.setApproxFactor(f);	  /*new values*/

	      ddist = abs(((int) dir) - ((int) olddir));
	      if (min(ddist,(8-ddist)) > WALLDANIELSSONSEGMENTLIST_MAX_DIR_CHANGE)
		{
		  /*if there is a non trivial direction change*/

		  if (_cutSeg.target() != prevpoint)
		    {
		      /*if cutpoint is not endpoint of segment*/

		      _newSeg.translateTarget(translation);
		      
		      Point newRelativeCoord = currpoint - _newSeg.source();
		      /*new approximation*/
		      _newSeg.setApproxFactor(_newSeg.approxFactor() + 
			(newRelativeCoord.x() * translation.y() - 
			 newRelativeCoord.y() * translation.x()));
		    }
		  else
		    {
		      /*if there was no previous cutpoint*/

		      _newSeg.setSource(prevpoint); // new _newSeg
		      _newSeg.setTarget(prevpoint);
		      _newSeg.translateTarget(translation);
		      _newSeg.setApproxFactor(0);

		      // new _cutSeg is old segment
		      _cutSeg.setTarget(prevpoint);
		      _cutSeg.setSqrLength(oldl2);
		      _cutSeg.setApproxFactor(oldf);
		      _cutSeg.setDirection(olddir);
		    }
		}
	  
	      else 
		_cutSeg.setTarget(currpoint);
	    }
	  else
	    {
	      /*if it was not a good approximation, we must create new segment*/
	      /*now, where do we have to cut the previous segment?*/

	      if (_cutSeg.target() == prevpoint)
		{
		  /*there was no special cutpoint : no problem*/
		  // store currseg
		  push_back(currseg);
		  // And modfiy it to new
		  currseg.set(prevpoint, translation.x(), translation.y(), dir);
		}
	      else
		{
		  /*if there was a cutpoint*/
		  // store _cutSeg
		  push_back(_cutSeg);

		  // start again with _newSeg
		  currseg = _newSeg;
		  
		  relativeCoords = currpoint - currseg.source();

		  f = currseg.approxFactor() + 
		    (relativeCoords.x() * translation.y() - 
		     relativeCoords.y() * translation.x());
		  /*new approximation*/

		  l2 = relativeCoords.x() * relativeCoords.x() +
	           relativeCoords.y() * relativeCoords.y();
	  
		  if ((l2 == 0) || 
		      ((abs(f) <= Math::QG_SQRT_MAX_INT16b) &&
                       ((f * f) < (l2 * wdThreshold))))
		  
		    {
		      /*if this segment is good*/

		      currseg.translateTarget(translation);
		      currseg.setApproxFactor(f);	    /*new values*/
		    }

		  else
		    {
		      // We must store the intermediate segment
		      // comprising former _newSeg and start a new one
		      push_back(_newSeg);
		      currseg.set(prevpoint, translation.x(),
				  translation.y(), dir);
		      
		    }
		}

	      _cutSeg.setTarget(currpoint);
	      _cutSeg.setSource(currseg.source()); /*no special cutpoint yet*/
	    }
	}
      else
	{
	  currseg.setSource(prevpoint);
	  currseg.setTarget(currpoint);
	  currseg.setSqrLength(translation.x() * translation.x() +
			 translation.y() * translation.y());
	  currseg.setApproxFactor(0);
	  currseg.setDirection(dir);
	  _cutSeg = currseg;
	}
    }

  /*See if we can merge the first and the last into one segment*/
  /* This only applies to closed curves */

  if (aChain.front() == aChain.back())   // if chain is a loop
    {
      // currseg = &back(); // *** ATTENTION !!! ****
      WDSegment firstseg = front();
  
      ddist = abs((int) currseg.direction() - (int) firstseg.direction());
      if ((currseg != firstseg) &&
          (min(ddist,(8-ddist)) <= WALLDANIELSSONSEGMENTLIST_MAX_DIR_CHANGE))
	{
	  /*it may be possible to merge them*/
      
	  /*according to my calculations, the new f should be equal*/
	  /*to vectorial_product(currseg,firstseg) + f1 + f2*/
	  /*where f1 and f2 are the WD approximations for*/
	  /*the 2 segments*/
	  f = (firstseg.source().x() - currseg.source().x()) *
	    (firstseg.target().y() - firstseg.source().y()) -
	    (firstseg.source().y() - currseg.source().y()) *
	    (firstseg.target().x() - firstseg.source().x());
	  f += firstseg.approxFactor() + currseg.approxFactor();

	  relativeCoords = firstseg.target() - currseg.source();

	  l2 = relativeCoords.x() * relativeCoords.x() +
	    relativeCoords.y() * relativeCoords.y();
	  
	  /*square of new length*/
    
	  if ((abs(f) <= Math::QG_SQRT_MAX_INT16b) &&
              (f*f < (l2*wdThreshold)))
	    {
	      /*we can merge the 2 segments*/
	      firstseg.setSource(currseg.source());  /*new origin of firstseg*/
	      firstseg.setTarget(currseg.source());
	      firstseg.translateTarget(relativeCoords);
	      firstseg.setApproxFactor(f);
	      // Update chaining
	      // pop_back();
	    }
	  else
	    // Store currseg
	    push_back(currseg);
	}
      else
	push_back(currseg);
    }
  else
    push_back(currseg);
}

// -------------------------------------------------------------------

} // namespace qgar
