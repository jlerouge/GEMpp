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
 * @file RWArcVector.cpp
 *
 * @brief Implementation of class qgar::RWArcVector.
 *
 * See file RWArcVector.h for the interface.
 *
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Christian Ah-Soon">Christian Ah-Soon</a>
 * @date    July 3, 2001  16:29
 * @since   Qgar 1.0
 */



// STD
#include <algorithm>
// QGAR
#include "math.h"
#include "primitives.h"
#include "RWArcVector.h"
#include "RWSegmentVector.h"



using namespace std;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// L O C A L    F U N C T I O N S
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace
{

using namespace qgar;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

double
RWARCVECTOR_squareError(Point& aCenter,
			vector<Point>& thePoints,
			int firstIdx,
			int lastIdx)
{
  double deviation;
  double sum = 0.0;
  double radius = qgDist(aCenter, thePoints[firstIdx]);

  for (int i = firstIdx + 1 ; i < lastIdx ; ++i)
    {
      deviation = qgDist(aCenter, thePoints[i]) - radius;
      sum += deviation * deviation;
    }

  return sum;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

double
RWARCVECTOR_maxDeviation(Point& aCenter,
			 vector<Point>& thePoints,
			 int firstIdx,
			 int lastIdx,
			 int dir)
{
  double deviation;
  double deviationMax = 0;
  double radius = qgDist(aCenter, thePoints[firstIdx]);

  for (int l2 = firstIdx; l2 < lastIdx; ++l2)
    {
      double dx = (thePoints[l2+1].x() - thePoints[l2].x()) / 10.;
      double dy = (thePoints[l2+1].y() - thePoints[l2].y()) / 10.;
      int l3 = 1;
      while (l3 < 10)
	{
	  Point pt((int) (thePoints[l2].x() + dx * (l3 - 1)),
		   (int) (thePoints[l2].y() + dy * (l3 - 1)));
	  deviation = radius - qgDist(aCenter, pt);

	  if (deviation < 0)
	    {
	      deviation = -deviation; 
	    }
	  if (deviation > deviationMax)
	    {
	      deviationMax = deviation;
	    }

	  ++l3;
	}
    } // END for l2

  return deviationMax; 
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QgarArc*
RWARCVECTOR_bestAttributes(vector<Point>& thePoints,
			   int firstIdx,
			   int lastIdx,
			   double& dev,
			   int potRadius)
{
  Point intersection((thePoints[firstIdx].x() + thePoints[lastIdx].x()) / 2,
		     (thePoints[firstIdx].y() + thePoints[lastIdx].y()) / 2);

  int xIntersection =  intersection.x();
  int yIntersection =  intersection.y();
  
  // On which side of the segment does the center lie?
  int xNormalVector = thePoints[firstIdx].y() - thePoints[lastIdx].y();
  int yNormalVector = thePoints[lastIdx].x() - thePoints[firstIdx].x();
  int sum = 0;
  int maxAbs = 0;
  int xVectorI;
  int yVectorI;
  int projection; 

  for (int i = firstIdx + 1; i < lastIdx; ++i)
    {
      xVectorI = thePoints[i].x() - xIntersection;
      yVectorI = thePoints[i].y() - yIntersection;
      projection = xNormalVector * xVectorI + yNormalVector * yVectorI;
      sum += projection;
      projection = abs(projection);
      maxAbs = max(maxAbs, projection);      
    }

  maxAbs = (int)
    (maxAbs / hypot((double) xNormalVector, (double) yNormalVector));

  int sameSide = (sum > 0);

  double angle;
  if (yNormalVector == 0)
    {
      angle = (xNormalVector > 0) ? Math::QG_PI_2 : - Math::QG_PI_2; // ????
    }
  else
    {
      angle = atan( (double)xNormalVector / (double)yNormalVector );
    }

  double alphaX = sin(angle);
  double alphaY = cos(angle);

  // Small angle ou large angle?  
  int alphaXSign = (xNormalVector > 0) ? -1 : 1;
  int alphaYSign = (yNormalVector > 0) ? -1 : 1;

  if (alphaX < 0)
    {
      alphaX = - alphaX ;
    }
  alphaX =  alphaXSign * alphaX;
  if (alphaY < 0)
    {
      alphaY = - alphaY ;
    }
  alphaY =  alphaYSign * alphaY;

  Point center(xIntersection + int (alphaX * maxAbs / 2),
               yIntersection + int (alphaY * maxAbs / 2));
  
  /**
  double toto1 = 1 / alphaX;
  double toto2 = 1 / alphaY;
  double toto = max (toto1, toto2) + 1;
  Point center (xIntersection + int (alphaX * toto),
                yIntersection + int (alphaY * toto));
  **/

  double deviationOtherSide =
    RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);
  center.setXY(xIntersection - int(alphaX * maxAbs / 2),
	       yIntersection - int(alphaY * maxAbs / 2));
  
  /**
  center.setXY(xIntersection - int (alphaX * toto),
               yIntersection - int (alphaY * toto));
  **/
  double deviationSameSide =
    RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);

  int smallArc;
  if (deviationSameSide < deviationOtherSide)
    {
      smallArc = sameSide;
    }
  else
    {
      smallArc = !sameSide;
    }

  // Compute radius by dichotomy (step 5)
  int power2;
 
  if (potRadius != -1)
    {
      power2 = int(log((double)potRadius) / log(2.0)) + 1;
    }
  else
    {
      if (smallArc)
	{
	  // power2 = int(log(maxAbs) / log(2));
	  power2 = int(log((double)maxAbs) / log(2.0)) + 1;
	  if (power2 > 14)
	    power2 = 14;
	}
      else
	{
	  power2 =  14; 
	}
    }

  if (smallArc)
    {
      /**
      power2 = int(log(maxAbs) / log(2));
      power2 = int(log(maxAbs) / log(2)) + 1;
      if (power2 > 14)
	power2 = 14;
      **/
      if (sameSide)
	{
	  alphaX = -alphaX;
	  alphaY = -alphaY;
	}
    }
  else
    { 
      /**
      power2 = 14;
      **/
      if (!sameSide)
	{
	  alphaX = -alphaX;
	  alphaY = -alphaY;
	}
    }
  /**
  else                    // if large arc
    power2 = power2Large; // static
  **/

  long int devInf = 1;
  long int devSup = 1 << power2;
  long int devMid = devSup >> 1;  // == devSup / 2 
  long int iteration  = devMid;
  long int saveDevInf = 0; 
  long int saveDevSup = 0;
  long int saveDevMid = 0;
  long int saveIteration;
  int directionIter; 
  
  center.setXY(xIntersection + int(alphaX * devSup),
	       yIntersection + int(alphaY * devSup));
  
  double lastErrorSup =
    RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);
  double errorMid = 0.;

  bool proceed = false;

  do { ////////////////////////////////////////////////

    directionIter = 0;
    saveIteration = 0;
    for (; iteration != 1;)
      {
        iteration = iteration / 2;
        center.setXY(xIntersection + int(alphaX * devMid),
		     yIntersection + int(alphaY * devMid));      
        errorMid =
          RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);
      
        /**
        cout << "center " << center.x() <<" " << center.y()  <<"\n";
        cout << "errorMid " << errorMid << "devMid " 
             << devMid  << "it " << iteration << "\n";
        **/
        if (errorMid > lastErrorSup) 
          {
            if (directionIter == 0)
	      {
		directionIter = 1;
	      }
            else if (directionIter == - 1) 
              {
                saveDevInf = devMid; 
                saveDevMid = devSup ;
                saveDevSup = devSup + iteration * 4;
                saveIteration = iteration * 2 ;
                directionIter = 1;
                /**
                cout << "\n je save inf " << saveDevInf << "mil " 
                     << saveDevMid << "sup " << saveDevSup 
                     << "it " << saveIteration << "\n";
                **/
              }
            devInf = devMid;
            devMid = devMid + iteration ;
          }
        else if (errorMid < lastErrorSup ) 
          {
            if (directionIter == 0)
	      {
		directionIter = -1;
	      }
            else if (directionIter == 1) 
              {
                saveDevSup = devMid ;
                saveDevMid = devInf;
                saveDevInf = devInf - iteration * 4;
                saveIteration = iteration * 2;
                directionIter = -1;
	      }
            devSup = devMid;
            devMid = devMid - iteration ;
            lastErrorSup = errorMid;
          }
      } // for (;iteration;): 2^(nb iterations + 1) == devSup
	
    if ((directionIter == 0) || (devMid == 1) || (saveIteration == 0))
      {
        /**
        if ((directionIter != 0) && (saveIteration == 0))
          double min_error; 
        **/
	break;
      }
    
    center.setXY 
      (xIntersection + int(alphaX * (devMid + directionIter)), 
       yIntersection + int(alphaY * (devMid + directionIter)));
    
    double newError =
      RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);
    if (errorMid > newError)
      {
        devMid = saveDevMid;
        devSup = saveDevSup;
        devInf = saveDevInf;
        iteration = saveIteration;
        center.setXY(xIntersection + int(alphaX * devMid),
		     yIntersection + int(alphaY * devMid));
        errorMid =
          RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx); 
        center.setXY(xIntersection + int(alphaX * devSup),
		     yIntersection + int(alphaY * devSup));
        lastErrorSup =
          RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx); 

        if (directionIter == 1)
          {
            devInf = devMid;
            devMid = devMid + iteration ;
          }
        else
          {	
            devSup = devMid;
            devMid = devMid - iteration ;
            lastErrorSup = errorMid;
          }
        proceed = true;
      }
    else
      {
        proceed = false;
      }

  } while (proceed); ////////////////////////////////////////////////


  double min = errorMid + 100;
  for (int i = devMid - 10 ; i < devMid + 10 ; ++i)
    {
      center.setXY(xIntersection + int(alphaX * i), 
                   yIntersection + int(alphaY * i));
      errorMid =
        RWARCVECTOR_squareError(center, thePoints, firstIdx, lastIdx);
      if (min > errorMid)
	{
	  min = errorMid;
	  devMid = i;
	}
    } // END for i

  center.setXY(xIntersection + int(alphaX * devMid), 
               yIntersection + int(alphaY * devMid));
  double radius = qgDist(center, thePoints[firstIdx]);

  // Arc direction
  xNormalVector = thePoints[firstIdx].y() - yIntersection;
  yNormalVector = xIntersection - thePoints[firstIdx].x(); 
  
  double proj = xNormalVector * (thePoints[firstIdx].x() - xIntersection);
  proj += yNormalVector * (thePoints[firstIdx].y() - yIntersection);
  
  int dir; 
  if (smallArc)
    {
      if (proj > 0)
	{
	  dir = (deviationSameSide < deviationOtherSide); 
	}
      else
	{
	  dir = (deviationSameSide > deviationOtherSide); 
	}
    }
  else
    {
      if (proj > 0)
	{
	  dir = (deviationSameSide > deviationOtherSide); 
	}
      else
	{
	  dir = (deviationSameSide < deviationOtherSide); 
	}
    }

  // Arc significance
  double sinAng =
    qgDist(thePoints[firstIdx], thePoints[lastIdx]) / (2*radius);

  if (sinAng > 1)
    {
      sinAng = 1; // To eliminate roundness errors
    }
  angle = asin(sinAng);

  if (!smallArc)
    {
      angle = Math::QG_2PI - angle;
    }

  double arcLength  = angle * radius;
  double polyLength = 0.;
  for (int i = firstIdx; i < lastIdx; ++i)
    {
      polyLength += qgDist(thePoints[i], thePoints[i+1]);
    }

  double ratio;
  if (arcLength > polyLength)
    {
      ratio = arcLength / polyLength;
    }
  else
    {
      ratio = polyLength / arcLength ;
    }

  dev = RWARCVECTOR_maxDeviation(center, thePoints, firstIdx, lastIdx, dir);
  
  // double angDeb = center.angle(thePoints[firstIdx]);
  // double angFin = center.angle(thePoints[firstIdx]);
  // cout << qgDist(center, thePoints[firstIdx]) << "\n";
  
  if (dir)
    {
      return new QgarArc(thePoints[firstIdx], thePoints[lastIdx], center);
    }
  else
    {
      return new QgarArc(thePoints[lastIdx], thePoints[firstIdx], center);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int
RWARCVECTOR_thirdPoint(vector<Point>& thePoints,
		       int firstIdx,
		       int lastIdx,
		       Point& firstPoint,
		       Point& lastPoint,
		       Point& third)
{
  Point middlePt((firstPoint.x() + lastPoint.x()) / 2,
                 (firstPoint.y() + lastPoint.y()) / 2);

  Point bisectPt(middlePt.x() - lastPoint.y() + firstPoint.y(),
                 middlePt.y() + lastPoint.x() - firstPoint.x());

  for (int i = firstIdx ; i < lastIdx ; ++i)
    {
      double q = (bisectPt.x() - middlePt.x()) * 
                 (thePoints[i+1].y() - thePoints[i].y());

      q -= (bisectPt.y() - middlePt.y()) * 
           (thePoints[i+1].x() - thePoints[i].x());

      // A = middlePt, B = bisectPt, C = pt[i], D = pt[i+1]
      //
      //     (YA-YC)(XB-XA)-(XA-XC)(YB-YA)
      // s = -----------------------------
      //     (XB-XA)(YD-YC)-(YB-YA)(XD-XC)

      double s = (middlePt.y() - thePoints[i].y()) *  
                 (bisectPt.x() - middlePt.x());

      s -= (middlePt.x() - thePoints[i].x()) *
	   (bisectPt.y() - middlePt.y());

      double sq = s / q;
      if ((0 <= sq) && (sq <= 1))
	{
	  third.setXY((int) (s * (thePoints[i+1].x() - thePoints[i].x())
                             / q + thePoints[i].x()),
                      (int) (s * (thePoints[i+1].y() - thePoints[i].y())
                             / q + thePoints[i].y()));
	  return i; 
	}
    }

  return -1;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int
RWARCVECTOR_meanRadius(vector<Point>& thePoints,
		       int firstIdx,
		       int lastIdx,
		       int threshold)
{
  Point thirdPt; 
  DPoint center;
  int thirdIdx = RWARCVECTOR_thirdPoint(thePoints, firstIdx,
					lastIdx,
					thePoints[firstIdx],
					thePoints[lastIdx],
					thirdPt);

  if (!qgCircleCenter(thePoints[firstIdx], thirdPt, thePoints[lastIdx], center))
    {
      return -1;
    }

  Point thirdPt1;
  RWARCVECTOR_thirdPoint(thePoints,
			 firstIdx,
			 thirdIdx + 1, 
			 thePoints[firstIdx],
			 thirdPt,
			 thirdPt1);
  DPoint center1;
  if (!qgCircleCenter(thePoints[firstIdx], thirdPt1, thirdPt, center1))
    {
      return -1;
    }

  Point thirdPt2;
  RWARCVECTOR_thirdPoint(thePoints,
			 thirdIdx,
			 lastIdx,
			 thirdPt,
			 thePoints[lastIdx],
			 thirdPt2);
  DPoint center2;
  if (!qgCircleCenter(thirdPt, thirdPt2, thePoints[lastIdx], center2))
    {
      return -1;
    }

  if ((qgDist(center,  center1) > threshold) ||
      (qgDist(center1, center2) > threshold) ||
      (qgDist(center2, center)  > threshold)   )
    {  
      return -1;
    }
  else
    {
      return (int) ( (  qgDist(DPoint(thirdPt),  center)
                      + qgDist(DPoint(thirdPt1), center1)
                      + qgDist(DPoint(thirdPt2), center2)) / 3);
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Cross-recursivity between arcs3 and arcsInLoop
void
RWARCVECTOR_arcs3(RWArcVector* aRWvector,
		vector<Point>& thePoints,
		int firstIdx, int lastIdx, int thres);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void
RWARCVECTOR_arcsInLoop(RWArcVector* aRWvector,
		       vector<Point>& thePoints,
		       int firstIdx, int lastIdx, int thres)
{
  RWARCVECTOR_arcs3(aRWvector, thePoints, firstIdx, lastIdx - 1, thres);
  if (aRWvector->size() == 0)
    {
      return;
    }

  QgarArc& lastArc = (*aRWvector)[aRWvector->size() - 1 ];
 
  if ((lastArc.source() == thePoints[firstIdx]) && 
      (lastArc.target() == thePoints[lastIdx-1])   )
    {
      QgarArc anArc(thePoints[firstIdx],
		    thePoints[firstIdx],
		    lastArc.center());

      // Delete last but one arc
      vector<QgarArc>::iterator thisIdx = aRWvector->begin();      
      for (int i = 0; i < (int)aRWvector->size() - 1; ++i)
	{
	  ++thisIdx;
	}

      aRWvector->erase(thisIdx);
      // Insert new arc
      aRWvector->push_back(anArc);
    }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void
RWARCVECTOR_arcs3(RWArcVector* aRWvector,
		  vector<Point>& thePoints,
		  int firstIdx, int lastIdx, int thres)
{
  if ((lastIdx - firstIdx) < 3) return;

  const int maxDeviation = 15;

  if (thePoints[firstIdx] == thePoints[lastIdx])
    {
      RWARCVECTOR_arcsInLoop(aRWvector, thePoints, firstIdx, lastIdx, thres);
      return;
    }

  int radius =
    RWARCVECTOR_meanRadius(thePoints, firstIdx, lastIdx, thres);
  double deviation;
  QgarArc* anArc;
  if (radius != -1)
    {
      anArc = RWARCVECTOR_bestAttributes
                (thePoints, firstIdx, lastIdx, deviation, radius);
      if (deviation < maxDeviation)
	{
	  aRWvector->push_back(*anArc);
	  return;
	}
      delete anArc;
    }  

  for (int nbPoints = (lastIdx - firstIdx); nbPoints > 4; --nbPoints)
    {
      for (int i = firstIdx; (i + nbPoints - 1) <= lastIdx; ++i)
	{
	  radius = RWARCVECTOR_meanRadius(thePoints, i, i+nbPoints-1, thres);
	  if (radius != -1)
	    {
	      anArc = RWARCVECTOR_bestAttributes(thePoints,
					       i,
					       (i + nbPoints - 1), 
					       deviation, radius);
	      if (deviation < maxDeviation)
		{
		  aRWvector->push_back(*anArc);
		}
	      delete anArc;

	      if (i - firstIdx > 2)
		{
		  RWARCVECTOR_arcs3(aRWvector, thePoints, firstIdx, i, thres);
		}
	      if (lastIdx - (i + nbPoints - 1) > 2)
		{
		  RWARCVECTOR_arcs3(aRWvector,
				    thePoints,
				    (i + nbPoints - 1),
				    lastIdx,
				    thres);
		}
	      return;
	    } // if
	}  // END for i
    } // END for nbpoints
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

} // unnamed namespace

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------

RWArcVector::RWArcVector(RWSegmentVector &aRWvector, int thres)

  : _centerDispersionThreshold(thres)

{
  // Get points from the polygonal approximation

  vector<Point> pointVector;
  vector<Segment>::iterator seg = aRWvector.begin();

  while (seg != aRWvector.end())
    {
      pointVector.push_back(seg->source());
      ++seg;
    }
  pointVector.push_back(aRWvector[aRWvector.size() - 1].target());

  // Follow segments, keeping the same orientation
  int initIdx = 0;

  Point point1 = pointVector[0];
  Point point2 = pointVector[1];
  Point point3 = pointVector[2];

  for (int i = 2 ; i < (int)pointVector.size() ; ++i)
    {
      int angleSign = ((qgAngle(point2, point1, point3) < Math::QG_PI) ? 1 : 0);
      int newSign;

      do  // Do while angles have the same sign
	{
	  ++i;
	  if (i >= (int)pointVector.size())
	    {
	      break;
	    }
	  point1 = point2;
	  point2 = point3;
	  point3 = pointVector[i];
	  newSign = ((qgAngle(point2, point1, point3) < Math::QG_PI) ? 1 : 0);
	}
      while (angleSign == newSign); // do while

      --i;
      RWARCVECTOR_arcs3(this,
			pointVector,
			initIdx ,
			i,
			_centerDispersionThreshold);
      initIdx = i - 1;
    } // END for i
}

// -------------------------------------------------------------------

RWArcVector::RWArcVector(RWSegmentVector &aRWvector1,
			 RWSegmentVector &aRWvector2,
			 int thres)

  : _centerDispersionThreshold(thres)

{
  // Get points from the first polygonal approximation
  vector<Point> pointVector; 
  const Point& pt1 = aRWvector1[0].source();
  const Point& pt2 = aRWvector1[aRWvector1.size()-1].target();
  const Point& pt3 = aRWvector2[0].source();
  const Point& pt4 = aRWvector2[aRWvector2.size()-1].target();
  
  if ((pt2 == pt3) || (pt2 == pt4))
    {
      vector<Segment>::iterator seg = aRWvector1.begin();
      while (seg != aRWvector1.end())
	{
	  pointVector.push_back(seg->source());
	  ++seg;
	}
      pointVector.push_back(pt2);
    } 
  else
    {
      vector<Segment>::reverse_iterator seg = aRWvector1.rbegin();
      while (seg != aRWvector1.rend())
	{
	  pointVector.push_back(seg->target());
	  ++seg;
	}
      pointVector.push_back (pt1);
    }

  int cutIdx = pointVector.size() - 1;

  // Get points from the second polygonal approximation
  if (pointVector[cutIdx] == pt3)
    {
      vector<Segment>::iterator seg = aRWvector2.begin();
      pointVector.push_back(seg->target());
      ++seg;
      while (seg != aRWvector2.end())
	{
	  pointVector.push_back(seg->target());
	  ++seg;
	}
    }
  else
    {
      vector<Segment>::reverse_iterator seg = aRWvector2.rbegin();
      while (seg != aRWvector2.rend())
	{
	  pointVector.push_back(seg->source());
	  ++seg;
	}
    }

  // Follow segments, keeping the same orientation
  int initIdx;
  int idx;

  Point point1 = pointVector[0];
  Point point2 = pointVector[1];
  Point point3 = pointVector[2];

  for (idx = 2, initIdx = 0; idx < (int)pointVector.size(); ++idx)
    {
      int angleSign = ((qgAngle(point2, point1, point3) < Math::QG_PI) ? 1 : 0);
      int newSign;

      do  // Do while angles have the same sign
	{
	  ++idx;
	  if (idx >= (int)pointVector.size())
	    {
	      break;
	    }
	  point1 = point2;
	  point2 = point3;
	  point3 = pointVector[idx];
	  newSign = ((qgAngle(point2, point1, point3) < Math::QG_PI) ? 1 : 0);
	}
      while (newSign == angleSign); // do while

      --idx;

      if (idx > cutIdx)
	{
	  RWARCVECTOR_arcs3(this,
			    pointVector, initIdx,
			    idx,
			    _centerDispersionThreshold);
	}

      initIdx = idx - 1;
      if (initIdx >= cutIdx)
	{
	  break;
	}
    }
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// NON-VIRTUAL DESTRUCTOR

RWArcVector::~RWArcVector()
{
  // VOID
}


// -------------------------------------------------------------------

} // namespace qgar
