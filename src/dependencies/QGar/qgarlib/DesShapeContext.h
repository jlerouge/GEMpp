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


#ifndef __DESSHAPECONTEXT_H_INCLUDED__
#define __DESSHAPECONTEXT_H_INCLUDED__


/**
 * @file DesShapeContext.h
 *
 * @brief Header file of class qgar::DesShapeContext.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 7, 2006  15:54
 * @since  Qgar 2.2
 */



// For RCS/CVS use: Do not delete.
/* $Id: DesShapeContext.h,v 1.2 2006/07/04 13:37:39 masini Exp $ */



// STD
#include <list>
#include <vector>
// QGAR
#include "primitives.h"




namespace qgar
{


/**
 * @ingroup DESCR_SC
 *
 * @class DesShapeContext DesShapeContext.h "qgarlib/DesShapeContext.h"
 *
 * @brief Descriptor based on shape context.
 *
 * See paper by S. Belongie, J. Malik, and J. Puzicha
 * [<a href="Bibliography.html#Belongie-et-al-2002">Belongie&nbsp;et&nbsp;al,&nbsp;2002</a>]
 * for details.
 *
 * A shape is represented by a set of points sampled from the internal
 * and/or internal contours of the shape.
 * For each point <i>P</i>, a histogram of the relative
 * coordinates of all the other points <i>Q</i> is computed.
 * This histogram is called the <i>Shape Context</i> of <i>P</i>.
 * The coordinates are expressed in log-polar space
 * \f$(log(\rho),\Theta)\f$.
 *
 * A Shape Context is represented by a two-dimensional table:
 *
@verbatim
             0   T1 T2 T3...          2PI (Theta)
              +--+--+--+--+--+--+--+--+
              |  |  |  |  |  |  |  |  |
    log(rho1) +--+--+--+--+--+--+--+--+
              |  |  |BI|  |  |  |  |  |
    log(rho2) +--+--+--+--+--+--+--+--+
              |  |  |  |  |  |  |  |  |
    log(rho3) +--+--+--+--+--+--+--+--+
            . |  |  |  |  |  |  |  |  |
            . +--+--+--+--+--+--+--+--+
            . |  |  |  |  |  |  |  |  |
log(rhoMax+1) +--+--+--+--+--+--+--+--+
@endverbatim
 *
 * An element of the table, such as <i>BI</i>, represents a bin,
 * which gives the number of points <i>Q</i>
 * such as \f$log(\rho_{P,Q})\in[log(\rho_1),log(\rho_2)[\f$
 * and \f$Theta_{P,Q}\in[\Theta_2,\Theta_3[\f$.
 *
 * The user must provide:
 * - \f$\rho_{max}\f$, see function qgar::DesShapeContext::rhoMax,
 * - the number of bins for \f$\rho\f$ (default <b>5</b>),
 *   see function qgar::DesShapeContext::rhoBinCnt,
 * - the number of bins for \f$\Theta\f$ (default <b>12</b>),
 *   see function qgar::DesShapeContext::thetaBinCnt.
 *
 * The points representing the shape are stored in a table
 * (implemented by a STL vector), provided by functions
 * qgar::DesShapeContext::accessPoints
 * and qgar::DesShapeContext::points.
 * The Shape Contexts (implemented in a two-dimensional table,
 * as described above) are stored in a separate table of the same
 * size (implemented by a STL vector), provided by functions
 * qgar::DesShapeContext::accessShapeContexts
 * and qgar::DesShapeContext::pShapeContexts.
 * The size of both tables is given by function
 * qgar::DesShapeContext::size.
 *
 * Let <i>Ptab</i> be the table of points,
 * and <i>scTab</i> be the table of Shape Contexts:
 * <i>scTab[i]</i> represents the Shape Context of point <i>pTab[i]</i>.
 * Operator qgar::DesShapeContext::operator[] provides a direct access
 * to a Shape Context using the index of the corresponding point.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 7, 2006  15:54
 * @since  Qgar 2.2
 */
// image html shapecontext.jpg "Ou qu'elle est ?"
class DesShapeContext
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


  //
  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct the Shape Contexts of all given points,
   * as described in class header.
   *
   * @param aPtList       set of the points representing a shape
   * @param aRhoMax       maximum value of \f$\rho\f$
   * @param aRhoBinCnt    number of bins for \f$\rho\f$ (default <b>5</b>)
   * @param aThetaBinCnt  number of bins for \f$\theta\f$ (default <b>12</b>)
   */
  DesShapeContext(const std::list< GenPoint<int> >& aPtList,
          double aRhoMax,
          int aRhoBinCnt   =  5,
          int aThetaBinCnt = 12);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~DesShapeContext();

  //@}


  /** @name Access to shape context characteristics */
  //        =======================================
  //@{

  /**
   * @brief Get maximum \f$\rho\f$.
   */
  inline double rhoMax() const;

  /**
   * @brief Get upper bound used for \f$log(\rho)\f$:
   * \f$log(\rho_{max}+1)\f$
   */
  inline double rhoMaxLog() const;

  /**
   * @brief Get number of bins for \f$\rho\f$.
   */
  inline int rhoBinCnt();

  /**
   * @brief Get number of bins for \f$\Theta\f$.
   */
  inline int thetaBinCnt();

  //@}


  /** @name Access to points and corresponding Shape Contexts */
  //        =================================================
  //@{

  /**
   * @brief Get number of points representing the shape.
   */
  inline int size() const;

  /**
   * @brief Get the STL vector storing the points.
   *
   * See class header for full details.
   */
  inline const std::vector< GenPoint<int> >& accessPoints() const;

  /**
   * @brief Get a copy of the vector storing the points.
   *
   * See class header for full details.
   */
  inline std::vector< GenPoint<int> > points() const;

  /**
   * @brief Get the STL vector storing the Shape Contexts
   * (<i>i.e.</i> histograms) of the points representing the shape.
   *
   * See class header for full details.
   */
  inline const std::vector<int*>& accessShapeContexts() const;

  /**
   * @brief Get a copy of the STL vector storing the Shape Contexts
   * (<i>i.e.</i> histograms) of the points representing the shape.
   *
   * See class header for full details.
   */
  inline std::vector<int*> pShapeContexts() const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Get the Shape Context of the point at given index.
   *
   * See class header for full details.
   *
   * @param anIdx  index of one of the points representing the shape.
   */
  inline const int* operator[](int anIdx) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Relative coordinates */
  //        ====================
  //@{

  /**
   * @brief Maximum \f$\rho\f$, given by the client.
   */
  double rhoMax_;

  /**
   * @brief log(qgar::DesShapeContext::rhoMax_ + 1).
   */
  double rhoMaxLog_;

  /**
   * @brief Number of bins for \f$\rho\f$.
   */
  int rhoBinCnt_;

  /**
   * @brief Number of bins for \f$\Theta\f$.
   */
  int thetaBinCnt_;

  //@}


  /** @name Shape Contexts */
  //        ==============
  //@{

  /**
   * @brief Points representing the shape.
   *
   * Points are stored in a STL vector.
   * See class header for full details.
   */
  std::vector< GenPoint<int> > points_;

  /**
   * @brief Shape contexts (<i>i.e.</i> histograms)
   * of the points representing the shape.
   *
   * This is a STL vector of pointers to shape contexts.
   * A shape context itself is represented as a two-dimensional table
   * (of bins). First index is for \f$\rho\f$, second for \f$\Theta\f$.
   * See class header for full details.
   */
  std::vector<int*> pShapeContexts_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Disabled */
  //        ========
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * The default constructor belongs to the private section
   * so that clients cannot use it.
   */
  DesShapeContext();

  //@}


// -------------------------------------------------------------------
}; // class DesShapeContext




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =======================================
// ACCESS TO SHAPE CONTEXT CHARACTERISTICS
// =======================================


// GET MAXIMUM RHO

inline double
DesShapeContext::rhoMax() const
{
  return rhoMax_;
}


// GET UPPER BOUND USED FOR LOG(RHO)

inline double
DesShapeContext::rhoMaxLog() const
{
  return rhoMaxLog_;
}


// GET NUMBER OF BINS FOR RHO

inline int
DesShapeContext::rhoBinCnt()
{
  return rhoBinCnt_;
}


// GET NUMBER OF BINS FOR THETA

inline int
DesShapeContext::thetaBinCnt()
{
  return thetaBinCnt_;
}


// =================================================
// ACCESS TO POINTS AND CORRESPONDING SHAPE CONTEXTS
// =================================================


// GET NUMBER OF POINTS REPRESENTING THE SHAPE

inline int
DesShapeContext::size() const
{
  return (int) points_.size();
}


// GET THE STL VECTOR STORING THE POINTS

inline const std::vector< GenPoint<int> >&
DesShapeContext::accessPoints() const
{
  return points_;
}


// GET A COPY OF THE VECTOR STORING THE POINTS

inline std::vector< GenPoint<int> >
DesShapeContext::points() const
{
  return points_;
}


// GET THE STL VECTOR STORING THE SHAPE CONTEXTS

inline const std::vector<int*>&
DesShapeContext::accessShapeContexts() const
{
  return pShapeContexts_;
}


// GET A COPY OF THE STL VECTOR STORING THE SHAPE CONTEXTS

inline std::vector<int*>
DesShapeContext::pShapeContexts() const
{
  return pShapeContexts_;
}


// =========
// OPERATORS
// =========


// GET THE SHAPE CONTEXT OF THE POINT AT GIVEN INDEX

inline const int*
DesShapeContext::operator[](int anIdx) const
{
  return pShapeContexts_[anIdx];
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __DESSHAPECONTEXT_H_INCLUDED__ */
