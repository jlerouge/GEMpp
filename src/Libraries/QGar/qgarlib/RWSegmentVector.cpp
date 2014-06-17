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
 * @file    RWSegmentVector.cpp
 * @brief   Header file of class qgar::RWSegmentVector.
 *
 * See file for the RWSegmentVector.h interface.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date    July 3, 2001  16:37
 * @since   Qgar 1.0
 */



// STD
#include <vector>
// QGAR
#include "AbstractGenPointChain.h"
#include "math.h"
#include "primitives.h"
#include "RWSegmentVector.h"



using namespace std;


namespace qgar
{

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// L O C A L    C O N S T A N T S
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


const double RWSEGMENTVECTOR_VERY_LARGE_SIGNIFICANCE = 100000.0;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++





/*---------------------------------------------------------------------*
 |                                                                     |
 |                 C  L  A  S  S      R  W  T  R  E  E                 |
 |                                                                     |
 *---------------------------------------------------------------------*/

// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR


RWTree::RWTree()
{
  // VOID
}


// CONSTRUCT FROM INDEXES AND SIGNIFICANCE


RWTree::RWTree(int fi, int li, double s)

  : _firstIdx     (fi),
    _lastIdx      (li),
    _leftChild    (0),
    _rightChild   (0),
    _significance (s)
  
{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// NON-VIRTUAL DESTRUCTOR


RWTree::~RWTree()
{
  if (_leftChild != 0)
    {
      delete _leftChild;
    }

  if (_rightChild != 0)
    {
      delete _rightChild;
    }
}


// -------------------------------------------------------------------




/*---------------------------------------------------------------------*
 |                                                                     |
 |      C  L  A  S  S      R  W  S  E  G  M  E  N  T  V E C T O R      |
 |                                                                     |
 *---------------------------------------------------------------------*/

// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


RWSegmentVector::RWSegmentVector(AbstractGenPointChain<int>& aChain,
				 double minDeviation) 
{
  if (aChain.empty())
    {
      return;  // Nothing to do
    }

  // Convert chain to a vector of points

  vector<Point> myChain;
  aChain.setToBegin();

  while (!aChain.isAtEnd())
    {
      myChain.push_back(aChain.accessCurrent());
      aChain.moveNext();
    }

  // Build the tree
  _root = buildTree(myChain, 0, (myChain.size() - 1), minDeviation);

  // And now, construct the vector of Segments we want to retrieve
  if (_root != 0)
    {
      addSegmentIfTerminalNode(_root, myChain);
    }

  // Post-processing : Can we simplify?
  // Based on an idea by Rosin and West...
  // *** WAIT AND SEE ***
  
  // Delete auxiliary data structures
  if (_root != 0)
    {
      delete _root;
    }

  _indexes.erase(_indexes.begin(), _indexes.end());
//  _significance.erase(_significance.begin(), _significance.end());
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

RWSegmentVector::~RWSegmentVector()
{
  // VOID
}



// -------------------------------------------------------------------
// P R I V A T E   F U N C T I O N S 
// -------------------------------------------------------------------


// INTERNAL FUNCTION TO BUILD THE TREE


RWTree*
RWSegmentVector::buildTree(std::vector<Point>& myChain,
			   int fidx,
			   int lidx,
			   double minDeviation)
{
  RWTree* myNode = new RWTree(fidx, lidx);

  // Find maximum deviation
  double maxDeviation = 0.0;
  int whereToCut = fidx;

  if (myChain[fidx] == myChain[lidx]) // Closed curves
    {
      Point p = myChain[fidx];
      for (int i = fidx + 1 ; i < lidx ; ++i)
	{
	  double d = qgDist(p, myChain[i]);
	  if (d > maxDeviation)
	    {
	      whereToCut = i;
	      maxDeviation = d;
	    }
	}
      // If loop too small or max deviation equal to zero, forget it
      if ((lidx - fidx + 1) < 4 || maxDeviation < minDeviation)
	{
	  delete myNode;
	  return 0;
	}
      else // Otherwise, create a very large significance
	{
	  myNode->setSignificance(RWSEGMENTVECTOR_VERY_LARGE_SIGNIFICANCE);
	  myNode->setLeftChild(buildTree(myChain, fidx, whereToCut, minDeviation));
	  myNode->setRightChild(buildTree(myChain, whereToCut, lidx, minDeviation));
	  searchBestApproximation (myNode);
	  return myNode;
	}
    }
  else // Open curves
    {
      for (int i = fidx + 1 ; i < lidx ; ++i)
	{
	  double d = qgDist(myChain[i], myChain[fidx], myChain[lidx]);
	  if (d > maxDeviation)
	    {
	      whereToCut = i;
	      maxDeviation = d;
	    }
	}

      // If loop too small or max deviation equal to zero, keep as such
      if ((lidx - fidx + 1) < 4 || maxDeviation < minDeviation)
	{
	  myNode->setSignificance(maxDeviation / qgDist(myChain[fidx], myChain[lidx]));
	  return myNode;
	}
      else // Otherwise, recursive call
	{
	  myNode->setSignificance(maxDeviation / qgDist(myChain[fidx], myChain[lidx]));
	  myNode->setLeftChild(buildTree(myChain, fidx, whereToCut, minDeviation));
	  myNode->setRightChild(buildTree(myChain, whereToCut, lidx, minDeviation));
	  searchBestApproximation (myNode);
	  return myNode;
	}
    }
}


// SEARCH FOR THE BEST APPROXIMATION IN THE TREE


void
RWSegmentVector::searchBestApproximation(RWTree* aNode)
{
  // The lowest the signifiance, the best
  double bestSignif;
  if (aNode->leftChild() == 0)
    {
      if (aNode->rightChild() != 0)
	{
	  bestSignif = aNode->rightChild()->significance();
	}
      else
	{
	  bestSignif = aNode->significance();
	}
    }
  else if (aNode->rightChild() == 0)
    {
      bestSignif = aNode->leftChild()->significance();
    }
  else if (aNode->leftChild()->significance() < aNode->rightChild()->significance())
    {
      bestSignif = aNode->leftChild()->significance();
    }
  else
    {
      bestSignif = aNode->rightChild()->significance();
    }


  if (bestSignif < aNode->significance())
    {
      aNode->setSignificance(bestSignif);
    }
  else
    {
      if (aNode->leftChild() != 0)
	{
	  delete aNode->leftChild();
	}

      if (aNode->rightChild() != 0)
	{
	  delete aNode->rightChild();
	}

      aNode->setLeftChild(0);
      aNode->setRightChild(0);
    }
}


// ADD A SEGMENT WHEN ON A TERMINAL NODE


void
RWSegmentVector::addSegmentIfTerminalNode(RWTree* aNode,
					  std::vector<Point>& myChain)
{
  if ((aNode->leftChild() != 0) || (aNode->rightChild() != 0))
    {
      if (aNode->leftChild() != 0)
	{
	  addSegmentIfTerminalNode(aNode->leftChild(), myChain);
	}

      if (aNode->rightChild() != 0)
	{
	  addSegmentIfTerminalNode(aNode->rightChild(), myChain);
	}
    }
  else
    {
      Segment newSeg(myChain[aNode->firstIdx()],
		     myChain[aNode->lastIdx()]);
      push_back(newSeg);
      _significance.push_back(aNode->significance());
      _indexes.push_back(aNode->firstIdx());
    }
}


// -------------------------------------------------------------------

} // namespace qgar
