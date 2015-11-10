/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2006  Qgar Project, LORIA                             |
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
 | http://www.gnu.org/licenses/lgpl.html for the terms of the license. |
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
 * @file DesShapeContext.cpp
 *
 * @brief Implementation of class qgar::DesShapeContext.
 *
 * See file DesShapeContext.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 7, 2006  15:54
 * @since  Qgar 2.2
 */


//////////////////////////////////////////////////////////////////////////////
#include <iostream>
//////////////////////////////////////////////////////////////////////////////


// STD
#include <cmath>
#include <list>
#include <vector>
// QGAR
#include "array.h"
#include "DesShapeContext.h"
#include "math.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"



using namespace std;



namespace qgar
{

// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------


// ___________________________________________________________________
//
// WARNING: the default constructor belongs to the private section
// so that clients cannot use it

DesShapeContext::DesShapeContext()
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::DesShapeContext::DesShapeContext()",
			   "Disabled constructor: should not be used!");
}
// ___________________________________________________________________



// CONSTRUCTOR

DesShapeContext::DesShapeContext(const std::list< GenPoint<int> >& aPtList,
				 double aRhoMax,
				 int aRhoBinCnt,
				 int aThetaBinCnt)

  : rhoMax_      (aRhoMax),
    rhoMaxLog_   (log(aRhoMax + 1.)),
    rhoBinCnt_   (aRhoBinCnt),
    thetaBinCnt_ (aThetaBinCnt)
{
  // Number of given points
  int ptCnt = (int) aPtList.size();
  // Number of bin points
  int binCnt = aRhoBinCnt * aThetaBinCnt;

  // ALLOCATE MEMORY SPACE FOR POINTS
  // --------------------------------

  points_.reserve(ptCnt);

  // ALLOCATE AND SHAPE CONTEXTS
  // ---------------------------

  pShapeContexts_.reserve(ptCnt);

  for (int pdx = 0 ; pdx < ptCnt ; ++pdx)
    {
      // Allocate Shape Context...
      int* currShapeContext = new int[binCnt];
      pShapeContexts_.push_back(currShapeContext);
      // ...and initialize it to zero
      qgMemSet0(currShapeContext, binCnt);
    }

  // ACCESS TO BINS
  // --------------

  double rhoSamplingRate   = rhoMaxLog_   / (double) rhoBinCnt_;
  double thetaSamplingRate = Math::QG_2PI / (double) thetaBinCnt_;


//////////////////////////////////////////////////////////////////////////////
  std::cout << std::endl
	    << "- Nb points = " << ptCnt << std::endl
	    << "- Taille vecteur points = " << points_.size() << std::endl
	    << "- Taille vecteur Shape Contexts = " << pShapeContexts_.size() << std::endl
	    << "- Nb bins pour rho = " << aRhoBinCnt << std::endl
	    << "- Nb bins pour theta = " << aThetaBinCnt << std::endl
	    << "- Rho max = " << rhoMax_ << std::endl
	    << "- log(rho_max+1) = " << rhoMaxLog_ << std::endl
	    << "- Rho sampling rate = " << rhoSamplingRate << std::endl
	    << "- Theta sampling rate = " << thetaSamplingRate
	    << " = " << qgRadiansToDegrees(thetaSamplingRate) << " degrees" << std::endl
	    << std::endl;
//////////////////////////////////////////////////////////////////////////////

  // LOOP ON POINTS
  // --------------
  // Let P be the current point
  // pIt: pointer to P
  // pdx: index of P in the data structures of the descriptor

  std::list<Point>::const_iterator pIt = aPtList.begin();

  for (int pdx = 0; pdx < ptCnt; ++pdx, ++pIt)
    {

      // Save current point
      points_.push_back(*pIt);

      int pX = (*pIt).x();
      int pY = (*pIt).y();

//////////////////////////////////////////////////////////////////////////////
      std::cout << "pdx = " << pdx
		<< "    x=" << pX << "  y=" << pY << std::endl;
//////////////////////////////////////////////////////////////////////////////

      // _______________________________________________________________
      //
      // Do not compute again rho's & theta's computed in previous steps
      // _______________________________________________________________
      //
      // * let pdx be the index of point P
      // * let qdx be the index of point Q, different from P
      // * let V(P,Q) stand for rho(P,Q) or theta(P,Q)
      //
      //   V(P,Q) can be deduced from V(Q,P):
      //     - rho(P,Q)   == rho(Q,P)
      //     - theta(P,Q) == (theta(Q,P) + PI) % 2PI
      //
      // * When qdx > pdx, both V(P,Q) and V(Q,P)
      //   are computed and registered in adequate bins
      // * Thus, when qdx < pdx, V(P,Q) has already been
      //   computed and registered: there is nothing to do...
      // _______________________________________________________________

      // qIt: pointer to point Q, different from current point P
      // qdx: index of Q in the data structures of the descriptor

      std::list< GenPoint<int> >::const_iterator qIt = pIt;
      ++qIt;

      for (int qdx = pdx + 1; qdx < ptCnt ; ++qdx, ++qIt)
	{

	  int qX = (*qIt).x();
	  int qY = (*qIt).y();

//////////////////////////////////////////////////////////////////////////////
      std::cout << "    qdx = " << qdx
		<< "    x=" << qX << "  y=" << qY << std::endl;
//////////////////////////////////////////////////////////////////////////////

	  // Offset (in the Shape Context table) corresponding
	  // to bin number given by log(rho(P,Q))
	  int rhoOffset =
	    thetaBinCnt_ * (int) (log(qgDist(pX, pY, qX, qY)) / rhoSamplingRate);

	  // Theta(P,Q)
	  double theta = qgAngle(pX, pY, qX, qY);

	  // Register position of Q relatively to P
	  ++(pShapeContexts_[pdx][rhoOffset + (int) (theta / thetaSamplingRate)]);

//////////////////////////////////////////////////////////////////////////////
      std::cout << "        rho=" << qgDist(pX, pY, qX, qY)
		<< "  log(rho)= " << log(qgDist(pX, pY, qX, qY))
		<< "  index=" << (int) (log(qgDist(pX, pY, qX, qY)) / rhoSamplingRate)
		<< "  offset=" << rhoOffset
		<< std::endl
		<< "        theta_1=" << qgRadiansToDegrees(theta)
		<< "  index_1=" << (int) (theta / thetaSamplingRate) << std::endl;
//////////////////////////////////////////////////////////////////////////////

	  // Theta(Q,P)
	  if (theta > Math::QG_PI)
	    {
	      theta -= Math::QG_PI;
	    }
	  else
	    {
	      theta += Math::QG_PI;
	    }

	  // Register position of P relatively to Q
          ++(pShapeContexts_[qdx][rhoOffset + (int) (theta / thetaSamplingRate)]);

//////////////////////////////////////////////////////////////////////////////
	  std::cout << "        theta_2=" << qgRadiansToDegrees(theta)
		<< "  index_2=" << (int) (theta / thetaSamplingRate) << std::endl;
//////////////////////////////////////////////////////////////////////////////
	} // END for qdx

    } // END for pdx

}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ----------------------------------------------------------------------


DesShapeContext::~DesShapeContext()
{
  // Free space allocated for shape contexts
  for (std::vector<int*>::iterator scIt = pShapeContexts_.begin();
       scIt != pShapeContexts_.end();
       ++scIt)
    {
      delete [] (*scIt);
    }
}


// ----------------------------------------------------------------------

} // namespace qgar
