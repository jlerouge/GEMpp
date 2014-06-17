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


#ifndef __CONNECTEDCOMPONENTSIMPL_H_INCLUDED__
#define __CONNECTEDCOMPONENTSIMPL_H_INCLUDED__


/**
 * @file ConnectedComponentsImpl.h
 *
 * @brief Header file of class qgar::ConnectedComponentsImpl.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   May 28, 2004  15:41
 * @since  Qgar 2.1.1
 */



// For RCS/CVS use: Do not delete
/* $Id: ConnectedComponentsImpl.h,v 1.17 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <list>
#include <vector>
// QGAR
#include "Component.h"
#include "ConnectedComponents.h"
#include "GenImage.h"
#include "GenTree.h"
#include "QgarErrorAlgorithm.h"



namespace qgar
{

/**
 * @ingroup GRAPHPROC_CC
 *
 * @class ConnectedComponentsImpl ConnectedComponentsImpl.h "qgarlib/ConnectedComponentsImpl.h"
 *
 * @brief Implementation of the construction of connected components
 * of a binary image.
 *
 * A (connected) component is a region defined by a set of connected
 * pixels having the same color.
@verbatim
      b b b                    x w x
      b B b                    w W w
      b b b                    x w x

 8-connectivity           4-connectivity
    for BLACK                for WHITE
@endverbatim
 * <ul>
 * <li>
 * Black components are constructed using 8-connectivity: when black,
 * the central point, <b>B</b> on the figure, is connected
 * to its 8 black neighbors marked <b>b</b>.
 * </li>
 * <li>
 * White components are constructed using 4-connectivity: when white,
 * the central point, <b>W</b> on the figure, is connected
 * to its 4 white neighbors marked <b>w</b> and is not connected
 * to the 4 white neighbors marked <b>x</b>.
 * </li>
 * </ul>
 *
 * See class qgar::Component for the way a component is represented.
 *
@verbatim
                     aRCompTree
                  ________________
                 |                |    0     j     k
  +----------+   |      +--+      |   +--+--+--+--+--+- -+--+
  |COMPONENT |<----------C0|<----------- |  |  |  |  |   |  |  aRCompTab
  |LABELLED 0|   |      +--+      |   +--+--+|-+--+|-+- -+--+
  +----------+   |       /\       |          |     |
                 |      /  \      |          |     |
  +----------+   |  +--+    +--+  |          |     |
  |COMPONENT |<------Ci|    |Cj|<------------+     |
  |LABELLED i|   |  +--+    +--+  |                |
  +----------+   |    |     /||\  |                |
  +----------+   |  +--+          |                |
  |COMPONENT |<------Ck|<--------------------------+
  |LABELLED k|   |  +--+          |
  +----------+   |________________|
@endverbatim
 *
 * Each component is associated with a label (a number of type
 * qgar::Component::label_type).
 *
 * The set of components is hierarchically organized as a tree,
 * the so-called <i>component tree</i>, given by argument
 * <b>aRCompTree</b> of function qgar::ConnectedComponentsImpl::run.
 * Each node represents a component (in fact, the data associated
 * with the node is a pointer to the component, <b>Ci</b> on the
 * figure above), and its children represent the components which
 * are directly included into the component,
 * <i>i.e.</i> has a common border with it.
 *
 * The root of the tree is always a white component, labelled <b>0</b>.
 * It represents the background of the initial binary image,
 * in which all the other components are (transitively) included.
 *
 * To be sure to get a component representing the background,
 * the first and last rows of the given binary image, as well as
 * its first and last columns, are considered as being white.
 *
 * The so-called <i>component table</i>, given by argument
 * <b>aRCompTab</b> of function qgar::ConnectedComponentsImpl::run,
 * provides a direct access to the nodes representing the components,
 * using their labels to index the table. In other words, an element
 * of this table is a pointer to the node of the tree representing
 * the component having the same label as the element index.
 *
 * The location of the components is given by the so-called
 * <i>component image</i>, given by argument <b>aRCompImg</b> of
 * function qgar::ConnectedComponentsImpl::ConnectedComponentsImpl:
 * the value of a pixel is the label of the component to which
 * the pixel belongs.
 *
 *
 * @todo
 * Give the user the choice between implementing components as
 * labelled regions in an image (like now) and implementing
 * components through tables of runs and labels (these tables are
 * presently deleted once components are constructed)
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   May 28, 2004  15:41
 * @since  Qgar 2.1.1
 */
class ConnectedComponentsImpl
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Initialize data
   * in order to run the construction of components.
   *
   * @param aBinImg        binary image from which components are extracted
   * @param aPCompImg      pointer to component image
   * @param aRCompTree     reference to the component tree
   *                       (see class qgar::ConnectedComponents)
   * @param aRCompTab      reference to the component table
   *                       (see class qgar::ConnectedComponents)
   * @param aPOffset3X3_4_ offset table to get 4-connected neighbors
   *                       in a 3X3 neighborhood (see class qgar::Component)
   * @param aPOffset3X3_8_ offset table to get 8-connected neighbors
   *                       in a 3X3 neighborhood (see class qgar::Component)
   */
  ConnectedComponentsImpl(const BinaryImage& aBinImg,
			  ConnectedComponents::image_type* aPCompImg,
			  ConnectedComponents::tree_type& aRCompTree,
			  std::vector<ConnectedComponents::node_type*>& aRCompTab,
			  int* aPOffset3X3_4_,
			  int* aPOffset3X3_8_);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  ~ConnectedComponentsImpl();

  //@}


  /** @name Construction of connected components */
  //        ====================================
  //@{

  /**
   * @brief Run the construction of connected components.
   *
   * @exception qgar::QgarErrorAlgorithm  maximum label exceeded
   */
  void run();

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name (I) The initial binary image */
  //        ============================
  //@{

  /**
   * @brief Width of the initial binary image
   * (and of the component image).
   */
  int width_;

  /**
   * @brief Height of the initial binary image
   * (and of the component image).
   */
  int height_;

  /**
   * @brief Index of the last column of the initial binary image
   * (and of the component image).
   */
  int colEndIdx_;

  /**
   * @brief Index of the last row of the initial binary image
   * (and of the component image).
   */
  int rowEndIdx_;

  //@}


  // =================================================================
  /** @name (II) Runs in the given binary image

<a name="II"></a>For each row (of the given image),
whose index is <b>rowIdx_</b>:

@verbatim
                          0 1 2 3 4 5 6 7 8 9  <- column numbers
row #rowIdx_             +-+-+-+-+-+-+-+-+-+-+
of the given image       |b|w|b|b|b|w|w|b|b|b| <- pixels
                         +-+-+-+-+-+-+-+-+-+-+
                          ^                 ^
                          |_  considered   _|
                               as WHITE

                           0  1  2  3  4   <- run numbers
                          +--+--+--+--+--+
runRowsTab_[rowIdx_]      |2 |3 |2 |2 |1 | <- run lengths
                          +--+--+--+--+--+
                          +--+--+--+--+--+
labelRowsTab_[rowIdx_]    |L0|L1|L2|L3|L4| <- run labels
                          +--+--+--+--+--+

=> Even indexes in a run/label row correspond to white runs
   Odd  indexes in a run/label row correspond to black runs
@endverbatim

- The run row, stored in <b>runRowsTab[rowIdx_]</b>, gives the lengths
  of the runs of same-colored consecutive pixels in the row.
  First and last rows are considered as completely white.
  First and last pixels of a given row are considered as being white.

- The label row, stored in <b>labelRowsTab_[rowIdx_]</b>, gives the labels
  of the corresponding runs: <b>labelRowsTab_[rowIdx_][rdx]</b> gives
  the label of the run whose length is <b>runRowsTab[rowIdx_][rdx]</b>.
  */
  // =================================================================
  //@{

  /**
   * @brief Table of run rows:
   * 1 run row for each row of the given binary image.
   */
  std::vector< std::vector<int> > runRowsTab_;

  /**
   * @brief Table of label rows:
   * 1 label row for each row of the given binary image.
   */
  std::vector< std::vector<Component::label_type> > labelRowsTab_;

  /**
   * @brief True while all runs in a row are not processed.
   */
  bool moreCurrentRuns_;

  //@}


  //        ============================================
  /** @name (III) Previous row of the given binary image
            <a name="III"></a>
  */
  //        ============================================
  //@{

  /**
   * @brief Index of the previous row in the given image,
   * and in the tables of run/label rows.
   *
   * See qgar::ConnectedComponentsImpl::runRowsTab_
   * and qgar::ConnectedComponentsImpl::labelRowsTab_,
   * in <a href="#II">section II</a> about runs.
   */
  int prevRowIdx_;

  /**
   * @brief Considering the current run in the (previous) row,
   * index of this run in the run/label row.
   */
  int prevRunIdx_;

  /**
   * @brief Considering the current run in the (previous) row,
   * number of runs (starting from <b>0</b>) in the run row.
   */
  int prevRunCnt_;

  /**
   * @brief Considering the current run in the (previous) row,
   * label number of this run.
   */
  Component::label_type prevLabel_;

  /**
   * @brief Considering the current run in the (previous) row,
   * color of this run.
   */
  QGEbw prevColor_;

  /**
   * @brief Considering the current run in the (previous) row,
   * index (in image row) of the beginning of this run.
   */
  int prevRunBeginX_;

  /**
   * @brief Considering the current run in the (previous) row,
   * index (in image row) of the end of this run.
   */
  int prevRunEndX_;

  //@}


  //        ===========================================
  /** @name (IV) Current row of the given binary image
            <a name="IV"></a>
  */
  //        ===========================================
  //@{

  /**
   * @brief Pointer to the current row in the pixel map
   * of the given binary image.
   */
  BinaryImage::pointer ptRow_;

  /**
   * @brief Pointer to the end of the current row in the pixel map
   * of the given binary image.
   */
  BinaryImage::pointer ptRowEnd_;

  /**
   * @brief Index of the current row in the given binary image,
   * and in the tables of run/label rows.
   *
   * See qgar::ConnectedComponentsImpl::runRowsTab_
   * and qgar::ConnectedComponentsImpl::labelRowsTab_,
   * in <a href="#II">section II</a> about runs.
   */
  int rowIdx_;

  /**
   * @brief Considering the current run in the (current) row,
   * index of this run in the run/label row.
   */
  int currRunIdx_;

  /**
   * @brief Considering the current run in the (current) row,
   * label number of this run.
   */
  Component::label_type currLabel_;

  /**
   * @brief Considering the current run in the (current) row,
   * color of this run.
   */
  QGEbw currColor_;

  /**
   * @brief Considering the current run in the (current) row,
   * index (in image row) of the beginning of this run.
   */
  int currRunBeginX_;

  /**
   * @brief Considering the current run in the (current) row,
   * index (in image row) of the end of the run.
   */
  int currRunEndX_;

  //@}


  // =================================================================
  /** @name (V) Labels

Each created component is associated with a label, which is used
as an index to store/access information about the component in
the different tables representing the components.
See <a href="#VI">section VI</a> about component features.

  */
  // =================================================================
  //@{

  /**
   * @brief Current label count.
   */
  Component::label_type labelCnt_;

  /**
   * @brief Table of equivalent labels.
   *
@verbatim
                                 labelCnt_
                                     |
                  0  1  2  3  4  ... v     <- labels
                 +--+--+--+--+--+- -+--+
 equivLabelTab_  |NO|E1|NO|NO|E4|   |  |   <- equivalent labels
                 +--+--+--+--+--+- -+--+
@endverbatim
   *
   * - When a component is created, it is associated with a label
   *   <b>Li</b> and <b>equivLabelTab_[Li]</b> is set to <b>NO_LABEL</b>
   *   which means that the component is a <i>valid</i> one.
   *
   * - When components labelled <b>Lj</b> and <b>Lk (Lj < Lk)</b> have
   *   to be merged, the component with the greatest label (<b>Lk</b>)
   *   is merged into the component with the smallest label (<b>Lj</b>).
   *   <b>equivLabelTab_[Lk]</b> is set to <b>Lj</b>, to indicate that
   *   labels <b>Lj</b> and <b>Lk</b> are <i>equivalent</i>,
   *   that is to say are associated with the same component.
   *
   * @note
   * The smallest label of a set of equivalent labels is called
   * the <i>valid label</i>, and the component corresponding to a
   * valid label is called the <i>valid component</i>.
   * @note
   * By construction, component labelled <b>0</b> is always valid
   * and represents the background.
   */
  std::vector<Component::label_type> equivLabelTab_;

  /**
   * @brief Table giving the final label numbering.
   *
@verbatim
                              labelCnt_
                                  |
                  0  1  2  3  ... v    <- initial label numbers
                 +--+--+--+--+- -+--+
 finalLabelTab_  |0 |F1|F2|F3|   |  |  final labels
                 +--+--+--+--+- -+--+  0 <= Fi <= finalLabelCnt_
@endverbatim
   *
   * <b>finalLabelTab_[Li]</b> gives the final valid label, equivalent
   * to initial label <b>Li</b>. Final label numbers are computed
   * so as to get a consecutive final numbering.
   *
   * @note
   * By construction, the final label of component <b>0</b>
   * (background) is always <b>0</b>.
   */
  std::vector<Component::label_type> finalLabelTab_;

  /**
   * @brief Final label count.
   */
  Component::label_type finalLabelCnt_;

  /**
   * @brief List recording the indexes of valid components
   * in the table of equivalent labels,
   * qgar::ConnectedComponentsImpl::equivLabelTab_.
   *
@verbatim
       +---+---+---
       |   |   |...  validCompIdxList_
       +-|-+-|-+---
         |   |
         |   |    labelCnt_
         V   V        |
   0  1  2   3  4 ... V
  +--+--+--+--+--+- -+--+
  |NO|E1|NO|NO|E4|   |  |  equivLabelTab_
  +--+--+--+--+--+- -+--+
@endverbatim
   * This list is constructed once all the rows of the given binary
   * image are processed, and it is used to construct the final
   * component tree. Component labelled <b>0</b>, which always
   * represents the background, is not recorded in the list.
   */
  std::list<int> validCompIdxList_;

  //@}

 
  // =================================================================
  /** @name (VI) Tables to store component features

<a name="VI"></a>The component in which a given component is directly
included is called the <i>comprising component</i>.

@verbatim
   0  1  2  3  4...  <- component labels (<= labelCnt_)
  +--+--+--+--+--+-                                                 --+  C
  |i0|i1|i2|i3|i4|   inLabel_     : label of the comprising component |  O
  +--+--+--+--+--+-                                                   |  M
  |c0|c1|c2|c3|c4|   color_       : color                             |  P
  +--+--+--+--+--+-                                                   |  O
  |p0|p1|p2|p3|p4|   xTopLeftPix_ : X of top left pixel               |  N
  +--+--+--+--+--+-                                                   |  E
  |P0|P1|P2|P3|P4|   yTopLeftPix_ : Y of top left pixel               |  N
  +--+--+--+--+--+-                                                   |  T
  |t0|t1|t2|t3|t4|   xTopLeft_    : X of top left corner              >
  +--+--+--+--+--+-                                                   |
  |T0|T1|T2|T3|T4|   yTopLeft_    : Y of top left corner              |  F
  +--+--+--+--+--+-                                                   |  E
  |b0|b1|b2|b3|b4|   xBottomRight_: X of bottom right corner          |  A
  +--+--+--+--+--+-                                                   |  T
  |B0|B1|B2|B3|B4|   yBottomRight_: Y of bottom right corner          |  U
  +--+--+--+--+--+-                                                   |  R
  |a0|a1|a2|a3|a4|   areaPx_      : area                              |  E
  +--+--+--+--+--+-                                                 --+  S
@endverbatim

For component labelled <b>Li</b>, <b>inLabel_[Li]</b> gives
the label of its comprising component, <b>color_[Li]</b> gives
its color, etc.

  */
  // =================================================================
  //@{

  /**
   * @brief Label of the comprising component of each component.
   */
  std::vector<Component::label_type> inLabel_;

  /**
   * @brief Color of each component.
   */
  std::vector<QGEbw> color_;

  /**
   * @brief X coordinate of the top left pixel of each component.
   */
  std::vector<int> xTopLeftPix_;

  /**
   * @brief Y coordinate of the top left pixel of each component.
   */
  std::vector<int> yTopLeftPix_;

  /**
   * @brief X coordinate of the top left corner
   * of the bounding box of each component.
   */
  std::vector<int> xTopLeft_;

  /**
   * @brief Y coordinate of the top left corner
   * of the bounding box of each component.
   */
  std::vector<int> yTopLeft_;

  /**
   * @brief X coordinate of the bottom right corner
   * of the bounding box of each component.
   */
  std::vector<int> xBottomRight_;

  /**
   * @brief Y coordinate of the bottom right corner
   * of the bounding box of each component.
   */
  std::vector<int> yBottomRight_;

  /**
   * @brief Area (in pixels) of each component.
   */
  std::vector<int> areaPx_;

  //@}


  /** @name (VII) The connected components */
  //        ==============================
  //@{

  /**
   * @brief Pointer to the component image.
   */
  ConnectedComponents::image_type* pCompImg_;

  /**
   * @brief Pointer to the pixel map of the component image.
   */
  Component::label_type* pMapCCImg_;

  /**
   * @brief Reference to the component tree.
   *
   * See class qgar::ConnectedComponents.
   */
  ConnectedComponents::tree_type& rCompTree_;

  /**
   * @brief Reference to the component table.
   *
   * See class qgar::ConnectedComponents.
   */
  std::vector<ConnectedComponents::node_type*>& rCompTab_;

  //@}


  /** @name (VIII) 3X3 neighborhood */
  //        =======================
  //@{

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * 4-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
   * See qgar::Component::offset3X3_4_ for full details.
   */
  int* offset3X3_4_;

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * pertinent 8-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
   * See qgar::Component::offset3X3_8_ for full details.
   */
  int* offset3X3_8_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Functions working on labels */
  //        ===========================
  //@{

  /**
   * @brief Get the <i>valid label</i> of a given label.
   *
   * In other words, get the label equivalent to a given label.
   *
   * @param aLabel  a label
   */
  int validLabel(Component::label_type aLabel);

  //@}


  /** @name Functions working on components */
  //        ===============================
  //@{

  /**
   * @brief Merge component including previous run
   * and component including current run.
   *
   * @warning
   * By construction, component with the greatest label
   * must be merged into component with the smallest label.
   */
  void mergePrevAndCurrComponents();

  //@}


  /** @name Functions working on runs */
  //        =========================
  //@{

  /**
   * @brief Move to next run in previous row.
   *
   * See <a href="#III">section III</a> about previous row.
   */
  void nextPrevRun();

  /**
   * @brief Move to next run in current row.
   *
   * See <a href="#IV">section IV</a> about current row.
   */
  void nextCurrRun();

  /**
   * @brief Perform moves according to black- and white-connectivity
   * when end of previous run and end of current run coincide.
   *
   * @warning
   * End of current row must be tested before calling this function.
   */
  void prevAndCurrRunsCoincide();

  //@}


  /** @name Functions working on the component tree */
  //        =======================================
  //@{

  /**
   * @brief Construction the component tree.
   *
   * @param aTree    reference to the tree being constructed
   * @param aPNode   pointer to a node representing a component
   *                 which has not yet children
   * @param aCCTab   reference to the table of pointers to nodes
   *                 representing components: <b>aCCTab[lab]</b>
   *                 gives a pointer to the node representing
   *                 the component labelled <b>lab</b>
   *                 (<b>lab</b> is a <i>valid</i> label)
   */
  void constructComponentTree
    (ConnectedComponents::tree_type&               aTree,
     ConnectedComponents::node_type*               aPNode,
     std::vector<ConnectedComponents::node_type*>& aCCTab);

  //@}


// -------------------------------------------------------------------
}; // class ConnectedComponentsImpl


} // namespace qgar


#endif /* __CONNECTEDCOMPONENTSIMPL_H_INCLUDED__ */
