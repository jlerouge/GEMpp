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
 * @file Histogram.cpp
 *
 * @brief Implementation of class qgar::Histogram.
 *
 * See file GreyLevelHistogram.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    December 5, 2003  14:58
 * @since   Qgar 2.1.1
 */



// STD
#include <sstream>
// QGAR
#include "GenImage.h"
#include "Histogram.h"
#include "QgarErrorDomain.h"



using namespace std;



namespace qgar
{

// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T O R S 
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

Histogram::Histogram()

 : _samplingRate(1),
   _lowerBnd(0),
   _upperBnd(0)

{
  // VOID
}


// COPY CONSTRUCTOR

Histogram::Histogram(const Histogram& aHistg)

  : _samplingRate(aHistg._samplingRate),
    _lowerBnd(aHistg._lowerBnd),
    _upperBnd(aHistg._upperBnd),
    _cells(aHistg._cells)

{
  // VOID
}


// CONSTRUCT FROM BOUNDS AND SAMPLING RATE

Histogram::Histogram(int aLowerBnd,
		     int anUpperBnd,
		     unsigned int aSampRate)



  : _samplingRate(aSampRate),
    _lowerBnd(aLowerBnd),
    _upperBnd(anUpperBnd)

{
  if (aSampRate == 0)
    {
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::Histogram::Histogram(int, int, unsigned int)",
			    "Sampling rate is 0");
    }

  if (aLowerBnd > anUpperBnd)
    {
      ostringstream os;
      os << "Lower bound "
	 << aLowerBnd
	 << " is greater than upper bound "
	 << anUpperBnd;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "qgar::Histogram::Histogram(int, int, unsigned int)",
			    os.str());
    }

  int size =   (anUpperBnd - aLowerBnd + 1) / aSampRate
             + ((((anUpperBnd - aLowerBnd + 1) % aSampRate) == 0) ? 0 : 1);
  
  for (int iCnt = 0; iCnt < size; ++iCnt)
    {
      _cells.push_back(0);
    }
}


// CONSTRUCT FROM A GREY-LEVEL IMAGE

Histogram::Histogram(const GreyLevelImage& anImg,
		     int aLowerBnd,
		     int anUpperBnd,
		     unsigned int aSampRate)



  : _samplingRate(aSampRate),
    _lowerBnd(aLowerBnd),
    _upperBnd(anUpperBnd)

{
  if (aSampRate == 0)
    {
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::Histogram::Histogram(const qgar::GreyLevelImage&, int, int, unsigned int)",
			    "Sampling rate is 0");
    }

  if (aLowerBnd > anUpperBnd)
    {
      ostringstream os;
      os << "Lower bound "
	 << aLowerBnd
	 << " is greater than upper bound "
	 << anUpperBnd;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::Histogram::Histogram(const qgar::GreyLevelImage&, int, int, unsigned int)",
			    os.str());
    }

  // Initialize the cell vector
  int size =   (anUpperBnd - aLowerBnd + 1) / aSampRate
             + ((((anUpperBnd - aLowerBnd + 1) % aSampRate) == 0) ? 0 : 1);

  _cells.reserve((unsigned int) size);

  for (int iCnt = 0; iCnt < size; ++iCnt)
    {
      _cells.push_back(0);
    }

  // Compute frequencies
  GreyLevelImage::pointer pimg = anImg.pPixMap();
  size = anImg.width() * anImg.height();

  for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pimg)
    {
      (*this)[*pimg] += 1;
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


Histogram::~Histogram()
{
  // VOID
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A C C E S S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET SAMPLE WITH MAXIMUM FREQUENCY

int
Histogram::maxSample()
{ 
  vector<int>::iterator
    itVec = max_element(_cells.begin(), _cells.end());

  return ((itVec - _cells.begin()) * _samplingRate) + _lowerBnd;
}


int
Histogram::maxSample(int aBnd)
{ 
  vector<int>::iterator
    itVec = max_element(_cells.begin() + ((aBnd - _lowerBnd) / _samplingRate),
                        _cells.end());

  return ((itVec - _cells.begin()) * _samplingRate) + _lowerBnd;
}


// GET SAMPLE WITH MINIMUM FREQUENCY

int
Histogram::minSample()
{ 
  vector<int>::iterator
    itVec = min_element(_cells.begin(), _cells.end());

  return ((itVec - _cells.begin()) * _samplingRate) + _lowerBnd;
}


int
Histogram::minSample(int aBnd)
{ 
  vector<int>::iterator
    itVec = min_element(_cells.begin() + ((aBnd - _lowerBnd) / _samplingRate),
	                _cells.end());

  return ((itVec - _cells.begin()) * _samplingRate) + _lowerBnd;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ASSIGNMENT.

Histogram&
Histogram::operator=(const Histogram& aHistg)
{
  // Are left hand side and right hand side different objects?
  if (this != &aHistg)
    {
      _cells        = aHistg._cells;
      _samplingRate = aHistg._samplingRate;
      _lowerBnd     = aHistg._lowerBnd;
      _upperBnd     = aHistg._upperBnd;
    }
  return *this;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// S M O O T H I N G
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// SMOOTH WITH A MOVING AVERAGE OF GIVEN WINDOW SIZE

void
Histogram::smooth(unsigned int aWidth)



{
  int csize = _cells.size();
  int wsize = aWidth;

  if ((wsize == 0) || (wsize >= csize))
    {
      ostringstream os;
      os << "Bad window size ("
	 << aWidth
	 << ") for histogram ["
	 << _lowerBnd
	 << ','
	 << _upperBnd
	 << "], using sampling rate "
	 << _samplingRate;
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "void qgar::Histogram::smooth(unsigned int)",
			    os.str());
    }

  vector<int> cellsCopy = _cells;
  int sum = 0;

  int idx = 0;
  for ( ; idx < (wsize / 2) ; ++idx)
    {
      sum += cellsCopy[idx];
      _cells[idx] = sum / (idx + 1);
    }

  int jdx = idx;
  for ( ; jdx < wsize ; ++jdx)
    {
      sum += cellsCopy[jdx];
    }

  int kdx = 0;
  for ( ; jdx < csize ; ++jdx, ++idx, ++kdx)
    {
      _cells[idx] = sum / wsize;
      sum += cellsCopy[jdx] - cellsCopy[kdx];
    }

  for (int denom = wsize ; idx < csize ; ++idx, ++kdx, --denom)
    {
      _cells[idx] = sum / denom;
      sum -= cellsCopy[kdx];
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// F R E Q U E N C I E S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ADD TO THE FREQUENCY OF A SAMPLE

void
Histogram::plus(int aSample, unsigned int anIncr)
{
  _cells[sampIdx(aSample)] += anIncr;
}


// SUBTRACT TO THE FREQUENCY OF A SAMPLE

void
Histogram::minus(int aSample, unsigned int aDecr)
{
  _cells[sampIdx(aSample)] -= aDecr;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A C C E S S   T O   T H E   C E L L   V E C T O R   (P R I V A T E)
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// INDEX (IN THE CELL VECTOR) CORRESPONDING TO A SAMPLE

int
Histogram::sampIdx(int aSample) const



{
  if ((aSample < _lowerBnd) || (aSample > _upperBnd))
    {
      ostringstream os;
      os << "Sample "
	 << aSample
	 << " is out of bounds ["
	 << _lowerBnd
	 << ','
	 << _upperBnd
	 << ']';
      throw QgarErrorDomain(__FILE__, __LINE__,
			    "int qgar::Histogram::sampIdx(int)",
			    os.str());
    }

  return (aSample - _lowerBnd) / _samplingRate;
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------

} // namespace qgar

