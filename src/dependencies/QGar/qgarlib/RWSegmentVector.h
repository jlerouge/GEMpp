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


#ifndef __RWSEGMENTVECTOR_H_INCLUDED__
#define __RWSEGMENTVECTOR_H_INCLUDED__


/**
 * @file   RWSegmentVector.h
 * @brief  Header file of class qgar::RWSegmentVector.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:37
 * @since  Qgar 1.0
 */



// For RCS/CVS use: Do not delete
/* $Id: RWSegmentVector.h,v 1.5 2006/04/14 15:30:48 gerald Exp $ */



// STD
#include <vector>
// QGAR
#include "primitives.h"
namespace qgar
{
  // Avoid #include's when not necessary
   template <class T> class AbstractGenPointChain;
}



namespace qgar
{


/*---------------------------------------------------------------------*
 |                                                                     |
 |                 C  L  A  S  S      R  W  T  R  E  E                 |
 |                                                                     |
 *---------------------------------------------------------------------*/

/** 
 * @ingroup GRAPHPROC_POLYAPPROX
 *
 * @class RWTree RWSegmentVector.h "qgarlib/RWSegmentVector.h"
 *
 * @brief Private class of class RWSegmentVector to construct a binary
 * tree during Rosin and West's polygonal approximation.
 *
 * @warning Class qgar::RWSegmentVector is a friend.
 *
 * @todo Find an other solution than a private class!
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  00:02
 * @since  Qgar 1.0
 */
class RWTree 
{

// -------------------------------------------------------------------
// F R I E N D S
// -------------------------------------------------------------------

friend class RWSegmentVector;

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Representation of a node */
  //        ========================
  //@{

  /**
   * @brief Index in chain of first point.
   */
  int _firstIdx;

  /**
   * @brief Index in chain of last point.
   */
  int _lastIdx;

  /**
   * @brief Left child.
   */
  RWTree* _leftChild;

  /**
   * @brief Right child.
   */
  RWTree* _rightChild;

  /**
   * @brief Significance associated to the node.
   */
  double _significance;

  //@}


  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Default constructor.
   */
  RWTree();

  /**
   * @brief Construct from indexes and significance.
   *
   * @param fi index of first point
   * @param li index of last point
   * @param s  significance (default <b>0</b>)
   */
  RWTree(int fi, int li, double s = 0.0);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  ~RWTree();

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get significance.
   */
  inline double significance() const;

  /**
   * @brief Get Index of first point.
   */
  inline int firstIdx() const;

  /**
   * @brief Get Index of last point.
   */
  inline int lastIdx() const;

  /**
   * @brief Get left child.
   */
  inline RWTree* leftChild() const;

  /**
   * @brief Get right child.
   */
  inline RWTree* rightChild() const;

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Set significance.
   *
   * @param s  a significance
   */
  inline void setSignificance(double s);

  /**
   * @brief Set index of first point.
   *
   * @param fi first point index
   */
  inline void setFirstIdx(int fi);

  /**
   * @brief Set index of last point.
   *
   * @param li last point index
   */
  inline void setLastIdx(int li);

  /**
   * @brief Set left child.
   *
   * @param ls  left child
   */
  inline void setLeftChild(RWTree* ls);

  /**
   * @brief Set right child.
   *
   * @param rs  right child
   */
  inline void setRightChild(RWTree* rs);

  //@}

// -------------------------------------------------------------------
}; // class RWTree




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ======
// ACCESS
// ======


// GET SIGNIFICANCE

inline double
RWTree::significance() const
{
  return _significance;
}

 
// GET INDEX OF FIRST POINT

inline int
RWTree::firstIdx() const
{
  return _firstIdx;
}


// GET INDEX OF LAST POINT

inline int
RWTree::lastIdx() const
{
  return _lastIdx;
}

 
// GET LEFT CHILD

inline RWTree* 
RWTree::leftChild() const
{
  return _leftChild;
}

 
// GET RIGHT CHILD

inline RWTree*
RWTree::rightChild() const
{
  return _rightChild;
}


// ==============
// TRANSFORMATION
// ==============


// SET SIGNIFICANCE

inline void
RWTree::setSignificance(double s)
{
  _significance = s;
}

 
//` SET INDEX OF FIRST POINT

inline void
RWTree::setFirstIdx(int fi)
{
  _firstIdx = fi;
}

 
// SET INDEX OF LAST POINT

inline void
RWTree::setLastIdx(int li)
{
  _lastIdx = li; 
}


// SET LEFT CHILD

inline void
RWTree::setLeftChild(RWTree* ls)
{
  _leftChild = ls;
}

 
// SET RIGHT CHILD

inline void
RWTree::setRightChild(RWTree* rs)
{
  _rightChild = rs;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII






/*---------------------------------------------------------------------*
 |                                                                     |
 |       C  L  A  S  S      R  W  S  E  G  M  E  N  T  L  I  S  T      |
 |                                                                     |
 *---------------------------------------------------------------------*/

/** 
 * @ingroup GRAPHPROC_POLYAPPROX
 *
 * @class RWSegmentVector RWSegmentVector.h "qgarlib/RWSegmentVector.h"
 *
 * @brief Recursive polygonal approximation of a chain.
 *
 * The approximation is performed using the algorithm proposed by David
 * Lowe and further refined by P. Rosin and G. West
 * [<a href="Bibliography.html#Rosin-and-West-1989">Rosin&nbsp;and&nbsp;West,&nbsp;1989</a>].
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3, 2001  16:37
 * @since  Qgar 1.0
 */
class RWSegmentVector

  : public std::vector<Segment>

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct a polygonal approximation of a given chain.
   *
   * @param aChain chain to approximate
   * @param minDeviation minimum deviation considered as good
   *   (default <b>1.9</b>, which is an ad hoc value)
   */
  DLL_EXPORT RWSegmentVector(AbstractGenPointChain<int>& aChain,
		  double minDeviation = 1.9);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~RWSegmentVector();

  //@}

// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliary data */
  //        ==============
  //@{

  /**
   * @brief Associated vector of indexes in chain.
   */
  std::vector<int> _indexes;

  /**
   * @brief Associated vector of significances.
   */
  std::vector<double> _significance;

  /**
   * @brief Root of the chain tree.
   */
  RWTree* _root;

  //@}


  /** @name Auxiliary functions */
  //        ===================
  //@{

  /**
   * @brief Build the tree.
   */
  RWTree* buildTree(std::vector<Point>&, int, int, double);

  /**
   * @brief Search for the best approximation in the tree.
   */
  void searchBestApproximation(RWTree* aNode);

  /**
   * @brief Add a segment when on a terminal node.
   */
  void addSegmentIfTerminalNode(RWTree* aNode, std::vector<Point>&);

  /**
   * @brief Get <b>i</b>-th significance.
   */
  inline double significance(int i);

  //@}

// -------------------------------------------------------------------
}; // Class RWSegmentVector




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N 
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// GET i-TH SIGNIFICANCE

inline double
RWSegmentVector::significance(int i)
{
  return _significance[i];
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar 


#endif /* __RWSEGMENTVECTOR_H_INCLUDED__ */
