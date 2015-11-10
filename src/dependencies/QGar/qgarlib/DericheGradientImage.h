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


#ifndef __DERICHEGRADIENTIMAGE_H_INCLUDED__
#define __DERICHEGRADIENTIMAGE_H_INCLUDED__


/**
 * @file DericheGradientImage.h
 *
 * @brief Header file of class qgar::DericheGradientImage.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *   from previous work by Karl Tombre
 * @date   July 3,  2001  11:15
 * @since  Qgar 1.0
 */



// For RCS/CVS use: Do not delete
/* $Id: DericheGradientImage.h,v 1.15 2007/02/14 17:34:04 masini Exp $ */



// QGAR
#include "AbstractGradientImage.h"
#include "GenImage.h"



namespace qgar
{


/**
 * @ingroup IMGPROC_GRAD
 *
 * @class DericheGradientImage DericheGradientImage.h "qgarlib/DericheGradientImage.h"
 *
 * @brief Deriche's optimal edge detector.
 *
 * The code is based on a previous implementation by Djemel Ziou
 * and Salvatore Tabbone, as described in
 * [<a href="Bibliography.html#Deriche-1987">Deriche,&nbsp;1987</a>].
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>,
 *   from previous work by Karl Tombre
 * @date   July 3,  2001  11:15
 * @since  Qgar 1.0
 */
class DericheGradientImage

  : public AbstractGradientImage

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from given grey-level image.
   *
   * @param anImg    grey-level image to derive
   * @param anAlpha  parameter of the Deriche filter (default <b>1.0</b>)
   * @param aW       parameter of the Deriche filter (default <b>0.01</b>)
   * @param aNorm    <b>true</b> if filter is normalized to have a
   *   surface of <b>1</b>. Default is <b>false</b>: in this case,
   *   the filter preserves the height of the step edge
   */
  DericheGradientImage(const GreyLevelImage& anImg,
		       double anAlpha = 1.0,
		       double aW      = 0.01,
		       bool   aNorm   = false);


  /**
   * @brief Construct from a float image.
   *
   * @param anImg    float image to derive
   * @param anAlpha  parameter of the Deriche filter (default <b>1.0</b>)
   * @param aW       parameter of the Deriche filter (default <b>0.01</b>)
   * @param aNorm    <b>true</b> if filter is normalized to have a
   *   surface of <b>1</b>. Default is <b>false</b>: in this case,
   *   the filter preserves the height of the step edge
   */
  DericheGradientImage(const FloatImage& anImg,
		       double anAlpha = 1.0,
		       double aW      = 0.01,
		       bool   aNorm   = false);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D   M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Parameters */
  //        ==========
  //@{

  /**
   * @brief The alpha parameter (see Deriche's paper).
   */
  double alpha_;

  /**
   * @brief The w parameter (see Deriche's paper).
   */
  double w_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief The effective computation of the Gradient images.
   *
   * @param alpha  parameter of the Deriche filter (default <b>1.0</b>)
   * @param w      parameter of the Deriche filter (default <b>0.01</b>)
   * @param norm   <b>true</b> if filter is normalized to have a
   *   surface of <b>1</b>. Default is <b>false</b>: in this case,
   *   the filter preserves the height of the step edge
   */
  void PRIVATE_Gradient(double alpha, double w, bool norm);

  //@}

// -------------------------------------------------------------------
}; // class DericheGradientImage


} // namespace qgar


#endif /* __DERICHEGRADIENTIMAGE_H_INCLUDED__ */
