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


#ifndef __HISTOGRAM_H_INCLUDED__
#define __HISTOGRAM_H_INCLUDED__


/**
 * @file Histogram.h
 *
 * @brief Header file of class qgar::Histogram.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   December 5, 2003  14:58
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: Histogram.h,v 1.27 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <algorithm>
#include <numeric>
#include <vector>
// QGAR
#include "GenImage.h"
#include "QgarErrorDomain.h"



namespace qgar
{


/**
 * @ingroup DS_HISTO
 *
 * @class Histogram Histogram.h "qgarlib/Histogram.h"
 *
 * @brief General representation of a histogram.
 *
 * A histogram records frequencies of <i>samples</i> in a vector
 * of <i>cells</i>. A sample is a value in the range
 * [ <b>lowerBnd</b>, <b>upperBnd</b> ]. Bounds may be negative.
 * A cell records the frequency of samples included in
 * [ sample, sample + <b>samplingRate</b> [; the default sampling rate
 * is <b>1</b>. For example, the cell at the lower bound records the frequency
 * of samples in [ <b>lowerBnd</b>, <b>lowerBnd</b> + <b>samplingRate</b> [.
 *
 * @warning
 * Frequencies may be negative. Function qgar::Histogram::minus,
 * that decrements a frequency, does not perform any check about the value
 * of the resulting frequency.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *         from previous work by karl Tombre
 * @date   December 5, 2003  14:58
 * @since  Qgar 2.1.1
 */
class Histogram
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Default constructor.
   *
   * Sampling rate is set to <b>1</b>, lower and upper bounds
   * to <b>0</b>, and the vector of cells is empty.
   */
  Histogram();

  /**
   * @brief Copy constructor.
   * @param aHistg  a histogram
   */
  Histogram(const Histogram& aHistg);

  /**
   * @brief Construct from lower and upper bounds, and a sampling rate.
   *
   * All cells are set to <b>0</b>.
   *
   * @param aLowerBnd   lower bound
   * @param anUpperBnd  upper bound
   * @param aSampRate   sampling rate, i.e. cell width (default <b>1</b>)
   *
   * @exception qgar::QgarErrorDomain  sampling rate is 0
   * @exception qgar::QgarErrorDomain  lower bound greater than upper bound
   */
  Histogram(int aLowerBnd, int anUpperBnd, unsigned int aSampRate = 1)
   ;

  /**
   * @brief Construct from a grey-level image.
   *
   * @param anImg       a grey-level image
   * @param aLowerBnd   lower bound (default <b>0</b>)
   * @param anUpperBnd  upper bound (default <b>255</b>)
   * @param aSampRate   sampling rate, i.e. cell width (default <b>1</b>)
   *
   * @exception qgar::QgarErrorDomain  sampling rate is 0
   * @exception qgar::QgarErrorDomain  lower bound greater than upper bound
   */
  explicit Histogram(const GreyLevelImage& anImg,
		     int aLowerBnd  = 0,
		     int anUpperBnd = 255,
		     unsigned int aSampRate = 1)
   ;

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~Histogram();

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get lower bound.
   */
  inline int lowerBnd() const;

  /**
   * @brief Get upper bound.
   */
  inline int upperBnd() const;

  /**
   * @brief Get cell width.
   */
  inline int samplingRate() const;

  //@}


  /** @name Frequencies */
  //        ===========
  //@{

  /**
   * @brief Add a given value (default <b>1</b>) to the frequency of a sample.
   *
   * @param aSample  a sample
   * @param anIncr   value to be added to the corresponding frequency
   */
  void plus(int aSample, unsigned int anIncr = 1);

  /**
   * @brief Subtract a given value (default <b>1</b>)
   *   to the frequency of a sample.
   *
   * @param aSample  a sample
   * @param aDecr    value to be subtracted to the corresponding frequency
   *
   * @warning
   * The corresponding frequency may become negative: The function
   * does not perfom any check about the value of the frequency
   * after the subtraction.
   */
  void minus(int aSample, unsigned int aDecr = 1);

  /**
   * @brief Get sample with maximum frequency.
   *
   * If several samples have the same (maximum) frequency,
   * return the first sample starting from the lower bound.
   */
  int maxSample();

  /**
   * @brief Get sample with maximum frequency
   *   in [<b>aBnd</b>, <b>upperBnd</b>].
   *
   * If several samples have the same (maximum) frequency,
   * return the first sample starting from <b>aBnd</b>.
   *
   * @param aBnd  lower bound to start the search
   */
  int maxSample(int aBnd);

  /**
   * @brief Get sample with minimum frequency.
   *
   * If several samples have the same (minimum) frequency,
   * return the first sample starting from the lower bound.
   */
  int minSample();

  /**
   * @brief Get sample with minimum frequency
   *   in [<b>aBnd</b>, <b>upperBnd</b>].
   *
   * If several samples have the same (minimum) frequency,
   * return the first sample starting from <b>aBnd</b>.
   *
   * @param aBnd  lower bound to start the search
   */
  int minSample(int aBnd);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Return the frequency of a sample.
   *
   * @param aSample  a sample
   *
   * @exception qgar::QgarErrorDomain  sample out of bounds
   */
  inline int& operator[](int aSample);

  /**
   * @brief Assignment.
   *
   * @param aHistg  a histogram
   */
  Histogram& operator=(const Histogram& aHistg);

  //@}


  /** @name Histogram transformations */
  //        =========================
  //@{

  /**
   * @brief Transform into an accumulated histogram.
   */
  inline void partialSum();

  /**
   * @brief Smooth by computing a simple average on a window of given size.
   *
   * @param aWidth  width of smoothing window
   *
   * @exception qgar::QgarErrorDomain  bad window size
   */
  void smooth(unsigned int aWidth);

  //@}
 
// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Representation of a histogram */
  //        =============================
  //@{

  /**
   * @brief Sampling rate.
   *
   * It is the ``width'' of a cell of the cell vector.
   */
  int _samplingRate;

  /**
   * @brief Lower (non-sampled) bound.
   */
  int _lowerBnd;

  /**
   * @brief Upper (non-sampled) bound.
   */
  int _upperBnd;

  /**
   * @brief Vector of cells.
   */
  std::vector<int> _cells;

 //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Access to the cell vector */
  //        =========================
  //@{

  /**
   * @brief Index (in the cell vector) corresponding to a sample.
   *
   * @param aSample  a sample
   *
   * @exception qgar::QgarErrorDomain  sample out of bounds
   */
  int sampIdx(int aSample) const;

  //@}

// -------------------------------------------------------------------
}; // class Histogram




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// D E F I N I T I O N S   O F   I N L I N E    F U N C T I O N S
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ======
// ACCESS
// ======


// GET LOWER BOUND

inline int
Histogram::lowerBnd() const
{
  return _lowerBnd;
}


// GET UPPER BOUND

inline int
Histogram::upperBnd() const
{
  return _upperBnd;
}

// GET SAMPLING RATE

inline int
Histogram::samplingRate() const
{
  return _samplingRate;
}


// =========
// OPERATORS
// =========


// RETURN THE FREQUENCY OF A SAMPLE

int&
Histogram::operator[](int aSample)



{
  return _cells[sampIdx(aSample)];
}


// ===============
// TRANSFORMATIONS
// ===============


// TRANSFORM INTO AN ACCUMULATED HISTOGRAM

void
Histogram::partialSum()
{
  std::partial_sum(_cells.begin(), _cells.end(), _cells.begin());
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar 


#endif /* __HISTOGRAM_H_INCLUDED__ */
