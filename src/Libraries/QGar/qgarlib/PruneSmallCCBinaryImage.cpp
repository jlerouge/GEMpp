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
 * @file   PruneSmallCCBinaryImage.cpp
 * @brief  Implementation of class qgar::PruneSmallCCBinaryImage.
 *
 * See file PruneSmallCCBinaryImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   Jul 3, 2001  16:56
 * @since  Qgar 1.0
 */



// STD
#include <algorithm>
#include <limits>
#include <list>
#include <set>
#include <vector>
// QGAR
#include "GenImage.h"
#include "PruneSmallCCBinaryImage.h"



namespace qgar
{

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// L O C A L   V A R I A B L E S 
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


static int PRUNESMALLCC_WHITE = 0;
static int PRUNESMALLCC_BLACK = 1;

static int PRUNESMALLCC_NOCOMP = -1;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

PruneSmallCCBinaryImage::PruneSmallCCBinaryImage(const BinaryImage img, int size)

  : BinaryImage(img), _size(size)

{
  int i, j;

  // Initializations

  _lastRow = new int[width()];
  _curRow = new int[width()];

  // Iterations on rows and columns

  for (j = 0; j < height(); ++j)
    {
      for (i = 0; i < width(); ++i)
	if (pixel(i, j) == PRUNESMALLCC_BLACK)
	  {
	    processPixel(i, j);
	  }
	else
	  {
	    _curRow[i] = PRUNESMALLCC_NOCOMP;
	  }
      
      endOfLineProcess(j);
    }
  
  // Cleaning

  delete [] _lastRow;
  delete [] _curRow;
}

// ---------------------------------------------------------------------
// O T H E R    F U N C T I O N S
// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::processPixel(int i, int j)
{
  int lp;   // Left pixel
  int lup;  // Left upper pixel
  int up;   // Upper pixel
  int rup;  // Right upper pixel
  int flag; // Flag representing state of all neighbor pixels


  // First, computing neighbor pixels

  lp  = (i) ? _curRow[i - 1] : PRUNESMALLCC_NOCOMP;
  lup = (i && j) ? _lastRow[i - 1] : PRUNESMALLCC_NOCOMP;
  up  = (j) ? _lastRow[i] : PRUNESMALLCC_NOCOMP;
  rup = ((i != width() - 1) && j)? _lastRow[i + 1] : PRUNESMALLCC_NOCOMP;

  // Computing flag...

  flag = 0;
  flag |= (lp  != PRUNESMALLCC_NOCOMP) ? 1 : 0;
  flag |= (lup != PRUNESMALLCC_NOCOMP) ? 2 : 0;
  flag |= (up  != PRUNESMALLCC_NOCOMP) ? 4 : 0;
  flag |= (rup != PRUNESMALLCC_NOCOMP) ? 8 : 0;

  // Now process the 16 possible states
  //
  // Note: As unification is done after each row, the only
  // guarantee we have is that 2 horizontal and connected
  // pixels share the same entry

  switch(flag)
    {
    case 0:
      _curRow[i] = createNewEntry(i, j);
      break;
    case 1:
      attachPixel(i, j, lp);
      break;
    case 2:
      attachPixel(i, j, lup);
      break;
    case 3:
      attachPixelTwoEntries(i, j, lp, lup);
      break;
    case 4:
      attachPixel(i, j, up);
      break;
    case 5:
      attachPixelTwoEntries(i, j, lp, up);
      break;
    case 6:
      attachPixel(i, j, lup);
      break;
    case 7:
      attachPixelTwoEntries(i, j, lp, up);
      break;
    case 8:
      attachPixel(i, j, rup);
      break;
    case 9:
      attachPixelTwoEntries(i, j, lp, rup);
      break;
    case 10:
      attachPixelTwoEntries(i, j, lup, rup);
      break;
    case 11:
      attachPixelThreeEntries(i, j, lp, lup, rup);
      break;
    case 12:
      attachPixel(i, j, up);
      break;
    case 13:
      attachPixelTwoEntries(i, j, lp, up);
      break;
    case 14:
      attachPixel(i, j, lup);
      break;
    case 15:
      attachPixelTwoEntries(i, j, lp, lup);
      break;
    }
}

// ---------------------------------------------------------------------

int
PruneSmallCCBinaryImage::createNewEntry(int i, int j)
{
  if (_unusedEntries.empty())
    {
      _theEntries.push_back(ComponentEntry(i, j));

      // assert((_theEntries.size() - 1) <= std::numeric_limits<unsigned int>::max());
      return _theEntries.size() - 1;
    }
  else
    {
      int index;

      index = _unusedEntries.back();
      _unusedEntries.pop_back();
      _theEntries[index] = ComponentEntry(i, j);
      return index;
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::attachPixel(int i, int j, int entry)
{
  _curRow[i] = entry;
  _theEntries[entry].inc(i, j);
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::attachPixelTwoEntries(int i, int j, int e1, int e2)
{
  if (e1 != e2)
    {
      attachPixel(i, j, std::max(e1, e2));
      addEquivEntries(std::min(e1, e2), std::max(e1, e2));
    }
  else
    {
      attachPixel(i, j, e1);
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::attachPixelThreeEntries(int i,
						 int j,
						 int e1,
						 int e2,
						 int e3)
{
  if (e1 == e2)
    {
      if (e2 == e3)
	{
	  attachPixel(i, j, e1);
	}
      else
	{
	  attachPixelTwoEntries(i, j, e1, e3);
	}
    }
  else
    {
      if (e2 == e3)
	{
	  attachPixelTwoEntries(i, j, e1, e3);
	}
      else
	{
	  if (e1 == e3)
	    {
	      attachPixelTwoEntries(i, j, e1, e2);
	    }
	  else
	    {
	      int max = std::max(std::max(e1, e2), e3);
	      attachPixel(i, j, max);
	      
	      if (e1 != max)
		{
		  addEquivEntries(e1, max);
		}
	      
	      if (e2 != max)
		{
		  addEquivEntries(e2, max);
		}
	      
	      if (e3 != max)
		{
		  addEquivEntries(e3, max);
		}
	    }
	}
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::endOfLineProcess(int j)
{
  int * tmp;

  if (j)
    {
      unification();
      searchAndRemoveSmallComponents(j);
    }

  tmp = _curRow;
  _curRow = _lastRow;
  _lastRow = tmp;
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::unification()
{
  std::list< std::set<int> >::iterator itList;
  std::set<int>::iterator itSet;
  int min;
  int i;
  int x;
  int y;

  // Note: The elements of a set are always sorted in ascending order

  if (!_equivTable.empty())
    {

      // Unification on the last row

      for (i = 0; i < width(); ++i)
	if (_lastRow[i] != PRUNESMALLCC_NOCOMP)
	  for (itList = _equivTable.begin(); itList != _equivTable.end(); ++itList)
	    if ((*itList).count(_lastRow[i]))
	      {
		_lastRow[i] = *((*itList).begin());
		break;
	      }

      // Unification on the current row

      for (i = 0; i < width(); ++i)
	if (_curRow[i] != PRUNESMALLCC_NOCOMP)
	  for (itList = _equivTable.begin(); itList != _equivTable.end(); ++itList)
	    if ((*itList).count(_curRow[i]))
	      {
		_curRow[i] = *((*itList).begin());
		break;
	      }

      // Update entries
      //
      // It is important to keep as last point of an entry a point
      // where 'y' is maximum for the component (this information
      // is used after to determine if the recognition of a 
      // component is over)

      for (itList = _equivTable.begin(); itList != _equivTable.end(); ++itList)
	{
	  min = *((*itList).begin());
	  
	  x = _theEntries[min].x();
	  y = _theEntries[min].y();
	  
	  for (itSet = (*itList).begin(), ++itSet; itSet != (*itList).end(); ++itSet)
	    {
	      if (_theEntries[*itSet].y() > y)
		{
		  _theEntries[min].inc(_theEntries[*itSet].x(),
				       _theEntries[*itSet].y(),
				       _theEntries[*itSet].count());
		}
	      else
		{
		  _theEntries[min].inc(_theEntries[*itSet].count());
		}
	      
	      _theEntries[*itSet].setValid(false);
	      _unusedEntries.push_back(*itSet);
	    }
	}
      
      _equivTable.clear();
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::addEquivEntries(int e1, int e2)
{
  std::list< std::set<int> >::iterator itList;
  int inserted = 0;
  int minValue = std::numeric_limits<int>::max();
  std::list< std::set<int> >::iterator minIt;
  std::list<std::list< std::set<int> >::iterator> theIterators;
  std::list<std::list< std::set<int> >::iterator>::iterator itIt;
  std::set<int>::iterator itSet;

  // Search sets whose these entries belong

  if (!_equivTable.empty())
    for (itList = _equivTable.begin(); itList != _equivTable.end(); ++itList)
      if ((*itList).count(e1) || (*itList).count(e2))
	{
	  (*itList).insert(e1);
	  (*itList).insert(e2);
	  ++inserted;
	  theIterators.push_back(itList);
	  
	  if (*((*itList).begin()) <= minValue)
	    {
	      minValue = *((*itList).begin());
	      minIt = itList;
	    }
	}

  // If no set is found, create a new set and add the entries

  if (!inserted)
    {
      std::set<int> aSet;
      
      aSet.insert(e1);
      aSet.insert(e2);
      _equivTable.push_back(aSet);
    }

  // If entries are added to more than one set, start
  // a set unification

  if (inserted > 1)
    {
      for (itIt = theIterators.begin(); itIt != theIterators.end(); ++itIt)
	if (*itIt != minIt)
	  {
	    for (itSet = (*(*itIt)).begin(); itSet != (*(*itIt)).end(); ++itSet)
	      {
		(*minIt).insert(*itSet);
	      }

	    _equivTable.erase(*itIt);
	  }
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::searchAndRemoveSmallComponents(int j)
{
  std::vector<ComponentEntry>::iterator it;
  int n;

  // Analyze all the entries. If the last point of a component
  // is located on the last row, the recognition if this component
  // is then over, and its entry can be removed from the vector.
  // If its size is equal or lesser than the threshold,
  // we can remove the component. 

  for (it = _theEntries.begin(), n = 0; it != _theEntries.end(); ++it, ++n)
    {
      if ((*it).valid() && ((*it).y() == j - 1))
	{
	  if ((*it).count() <= _size)
	    {
	      removeComponent((*it).x(), (*it).y());
	      
	      (*it).setValid(false);
	      _unusedEntries.push_back(n);
	    }
	}
    }
}

// ---------------------------------------------------------------------

void
PruneSmallCCBinaryImage::removeComponent(int x, int y)
{
  int a, b;

  setPixel(x, y, PRUNESMALLCC_WHITE);


  while (isNeighbor(x, y, &a, &b))
    {
      removeComponent(a, b);
    }
}

// ---------------------------------------------------------------------

bool
PruneSmallCCBinaryImage::isNeighbor(int i, int j, int * a, int * b)
{
  int l, m, wd = width(), ht = height();

  for (l = -1; l <= 1; ++l)
    {
      for (m = -1; m <= 1; ++m)
	{
	  if (((l != 0) || (m != 0)) &&
	      (i + l >= 0) &&
	      (i + l < wd) &&
	      (j + m >= 0) &&
	      (j + m < ht))
	    {
	      if (pixel(i + l, j + m) == PRUNESMALLCC_BLACK)
		{
		  *a = i + l;
		  *b = j + m;
		  return true;
		}
	    }
	}
    }

  return false;
}
  
// ---------------------------------------------------------------------

} // namespace qgar
