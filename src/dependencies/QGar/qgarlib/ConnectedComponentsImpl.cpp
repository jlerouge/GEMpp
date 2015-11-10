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
 * @file ConnectedComponentsImpl.cpp
 *
 * @brief Implementation of class qgar::ConnectedComponentsImpl.
 *
 * See file ConnectedComponentsImpl.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   May 28, 2004  17:51
 * @since  Qgar 2.1.1
 */



// STD
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <vector>
// QGAR
#include "Component.h"
#include "ConnectedComponents.h"
#include "ConnectedComponentsImpl.h"
#include "GenImage.h"
#include "GenTree.h"
#include "QgarErrorAlgorithm.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// INITIALIZE DATA TO CONSTRUCT CONNECTED COMPONENTS

ConnectedComponentsImpl::ConnectedComponentsImpl
  (const BinaryImage&                       aBinImg,
   ConnectedComponents::image_type*         aPCompImg,
   ConnectedComponents::tree_type&          aRCompTree,
   vector<ConnectedComponents::node_type*>& aRCompTab,
   int* aPOffset3X3_4_,
   int* aPOffset3X3_8_)

  : width_         (aBinImg.width()),      // width of initial binary image
    height_        (aBinImg.height()),     // height of initial binary image
    ptRow_         (aBinImg.pPixMap()),    // pointer to pixel map of binary image
    labelCnt_      (0),                    // label counter
    finalLabelCnt_ (0),                    // integer final label count
    pCompImg_      (aPCompImg),            // pointer to component image
    pMapCCImg_     (aPCompImg->pPixMap()), // pointer to pixel map of component image
    rCompTree_     (aRCompTree),           // reference to the component tree
    rCompTab_      (aRCompTab),            // reference to the component table
    offset3X3_4_   (aPOffset3X3_4_),       // offset table for 4-connectivity
    offset3X3_8_   (aPOffset3X3_8_)        // offset table for 8-connectivity

{
  // Index of last column of CC image
  colEndIdx_ = width_ - 1;
  // Index of last row of CC image
  rowEndIdx_ = height_ - 1;

  // Allocate space for run and label rows
  runRowsTab_.reserve(height_);
  labelRowsTab_.reserve(height_);

}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// RUN  THE  CONSTRUCTION  OF  CONNECTED  COMPONENTS
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ALGORITHM TO BUILD CONNECTED COMPONENTS FROM A BINARY IMAGE

void
ConnectedComponentsImpl::run()



{
  // =====================================================================
  // BEGIN run construction of connected components
  // =====================================================================


  // =====================================================================
  // (1) FIRST ROW
  // =====================================================================

  // WARNING: First row (like last row) is considered as WHITE
  // and belongs to component 0 representing the background

  equivLabelTab_.push_back(Component::LABEL_NO_);  // no equivalent label

  // First component

  inLabel_.push_back(0);           // 0 is conventionally included in 0
  color_.push_back(QGE_BW_WHITE);  // color
  xTopLeftPix_.push_back(0);       // top left pixel
  yTopLeftPix_.push_back(0);
  xTopLeft_.push_back(0);          // bounding box
  yTopLeft_.push_back(0);
  xBottomRight_.push_back(colEndIdx_);
  yBottomRight_.push_back(0);
  areaPx_.push_back(width_);   // area

  // First run row and first label row
  runRowsTab_.push_back(vector<int>(1, width_));
  labelRowsTab_.push_back(vector<Component::label_type>(1, 0));

  // Run count for this first row,
  // to get correct data when processing next row
  currRunIdx_ = 0;


  // =====================================================================
  // (2) PROCESS NEXT ROWS OF THE BINARY IMAGE
  // =====================================================================

  // Initialize pointer to the current row (in the pixel map of the given
  // image) to beginning of the 2nd row
  ptRow_ += width_;


  for (rowIdx_ = 1 ; rowIdx_ < height_ ; ++rowIdx_ )
    // FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    // BLOCK-FOR
    // for each row of the given image
    // FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    {

      // Next row
      // WARNING: Rows are supposed to be consecutively stored
      //          in the pixel map
      ptRowEnd_ = ptRow_ + colEndIdx_;

      // Index of previous row
      prevRowIdx_ = rowIdx_ - 1;

      // To save current run row and current label row
      runRowsTab_.push_back(vector<int>());
      labelRowsTab_.push_back(vector<Component::label_type>());

      // Current run in previous iteration becomes previous run
      // in this iteration
      prevRunCnt_  = currRunIdx_;

      // Initializations to get correct data from function nextPrevRun()
      prevColor_   = QGE_BW_BLACK; // => first run will be WHITE
      prevRunIdx_  = -1;
      prevRunEndX_ = -1;

      // pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp
      // Get first previous run
      // pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp

       // Initializations to get correct data from function nextPrevRun()
      prevColor_   = QGE_BW_BLACK; // => first run will be WHITE
      prevRunIdx_  = -1;
      prevRunEndX_ = -1;

      nextPrevRun(); // Get first run
      // pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp


      // cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      // Get first current run
      // cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      if (rowIdx_ == rowEndIdx_)
	{
	  // Processing last row
	  // WARNING: Last row (like first row) is considered as WHITE
	  // and belongs to component 0 representing the background
	  // => last row features are known

	  currRunBeginX_ = 0;
	  currRunEndX_   = colEndIdx_;
	  currColor_     = QGE_BW_WHITE;           // white run
	  currLabel_     = Component::LABEL_NO_;   // not yet labelled
	}
      else
	{
	  // Processing any row but the last one

	  // Initializations to get correct data from function nextCurrRun()
	  currColor_   = QGE_BW_BLACK;  // => first run will be WHITE
	  currRunEndX_ = -1;
	  currRunIdx_  = -1;
	  currLabel_   = Component::LABEL_NO_;  // not yet labelled
	  
	  // WARNING: First pixel is considered as WHITE
	  // => skip first pixel, whatever its color is
	  ++ptRow_;

	  nextCurrRun(); // Get next current run

	  // Increment run end index to take first pixel into account
	  ++currRunEndX_;
	}
      // cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc


      // Current row is not processed
      moreCurrentRuns_ = true;

      while (moreCurrentRuns_)
	// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	// WHILE-BLOCK 1
	// while all runs in current row are not processed
	//
	// PREVIOUS RUN AND CURRENT RUN ARE ALWAYS ADJACENT
	// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	{

	  if (currColor_ == prevColor_)
	    {
	      //____________________________________________________________
	      //
	      // PREVIOUS RUN AND CURRENT RUN HAVE THE SAME COLOR
	      // => current run belongs to the same component as previous run
	      
	      mergePrevAndCurrComponents();
	      //____________________________________________________________
	    }


	  if (prevRunEndX_ < currRunEndX_)
	    {
	      //____________________________________________________________
	      //
	      // (i) CURRENT RUN OVERLAPS PREVIOUS RUN
	      //     => get next previous run

	      nextPrevRun();
	      //____________________________________________________________
	    }

	  else

	    {
	      // (ii) END OF PREVIOUS AND CURRENT RUNS COINCIDE,
	      //      OR PREVIOUS RUN OVERLAPS CURRENT RUN
	      // => if current run is not labelled, it starts a new component 

	      if (currLabel_ == Component::LABEL_NO_)
		{
		  // Get a new label
		  if (labelCnt_ == Component::LABEL_MAX_)
		    {
		      ostringstream os;
		      os << "Cannot deal with more than " << labelCnt_ << " labels";
		      throw QgarErrorAlgorithm(__FILE__, __LINE__,
					       "void qgar::ConnectedComponentsImpl::run()",
					       os.str());
		    }
		  else
		    {
		      ++labelCnt_;
		    }

		  currLabel_ = labelCnt_;
		  // Label of the comprising component:
		  // As previous run has a different color, it always belongs
		  // to the component that surrounds the new component
		  inLabel_.push_back(prevLabel_);

		  equivLabelTab_.push_back(Component::LABEL_NO_); // no equivalent label
		  xTopLeftPix_.push_back(currRunBeginX_);         // top left pixel
		  yTopLeftPix_.push_back(rowIdx_);                //
		  xTopLeft_.push_back(currRunBeginX_);            // bounding box
		  yTopLeft_.push_back(rowIdx_);                   //
		  xBottomRight_.push_back(currRunEndX_);          //
		  yBottomRight_.push_back(rowIdx_);               //
		  color_.push_back(currColor_);                   // color
		  areaPx_.push_back(currRunEndX_ - currRunBeginX_ + 1); // area

		  // SAVE current run and its label
		  runRowsTab_[rowIdx_].push_back(currRunEndX_ - currRunBeginX_ + 1);
		  labelRowsTab_[rowIdx_].push_back(currLabel_);
		}


	      if (prevRunEndX_ > currRunEndX_)
		{
		//__________________________________________________________
		//
		// PREVIOUS RUN OVERLAPS CURRENT RUN
		// => get next current run

		  nextCurrRun();
                //__________________________________________________________
		}

	      else

		{
		//__________________________________________________________
		//
		// ENDS OF PREVIOUS RUN AND CURRENT RUN COINCIDE

		  if (currRunEndX_ == colEndIdx_)
		    {
		      // END OF ROW IS REACHED
		      moreCurrentRuns_ = false;
		    }
		  else
		    {
		      prevAndCurrRunsCoincide();
		    }
	        //__________________________________________________________
		}

	    } // END (ii) else part of if(current run overlaps previous run)

	}
        // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
        // END BLOCK-WHILE
        // all runs in current row are processed
        // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

    }
    // FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    // END BLOCK-FOR
    // each row of the given image is processed
    // FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF


  // ============================================================================
  // (3) GET THE FINAL COMPONENTS AND THEIR VALID LABELS
  // ============================================================================

  // At this point:
  //
  //   0  1  2  3  4...  <- component labels (<= labelCnt_)
  //  +--+--+--+--+--+-
  //  |NO|L1|NO|NO|L4|   equivLabelTab_ : equivalent labels
  //  +--+--+--+--+--+-
  //
  //  +--+--+--+--+--+-                                                  --+  C
  //  |i0|**|i2|i3|**|   inLabel_      : label of the comprising component |  O
  //  +--+--+--+--+--+-                                                    |  M
  //  |c0|**|c2|c3|**|   color_        : color                             |  P
  //  +--+--+--+--+--+-                                                    |  O
  //  |p0|**|p2|p3|**|   xTopLeftPix_  : X of top left pixel               |  N
  //  +--+--+--+--+--+-                                                    |  E
  //  |P0|**|P2|P3|**|   yTopLeftPix_  : Y of top left pixel               |  N
  //  +--+--+--+--+--+-                                                    |  T
  //  |t0|**|t2|t3|**|   xTopLeft_     : X of top left corner              >
  //  +--+--+--+--+--+-                                                    |
  //  |T0|**|T2|T3|**|   yTopLeft_     : Y of top left corner              |  F
  //  +--+--+--+--+--+-                                                    |  E
  //  |b0|**|b2|b3|**|   xBottomRight_ : X of bottom right corner          |  A
  //  +--+--+--+--+--+-                                                    |  T
  //  |B0|**|B2|B3|**|   yBottomRight_ : Y of bottom right corner          |  U
  //  +--+--+--+--+--+-                                                    |  R
  //  |a0|**|a2|a3|**|   areaPx_       : area                              |  E
  //  +--+--+--+--+--+-                                                  --+  S
  //
  //
  // In equivLabelTab_:
  //
  // - NO_LABEL (qgar::Component::LABEL_NO_) means that the corresponding
  //   index in the table represents a valid label, thus corresponds to
  //   a valid component. BY CONSTRUCTION, THIS LABEL IS THE SMALLEST OF ALL
  //   THE LABELS (TRANSITIVELY) EQUIVALENT TO IT.
  //   The component features are available in tables inLabel_, color_,
  //    etc. at the same corresponding index.
  // - Li means that the corresponding index does not represent a valid
  //   label, thus corresponds to a component which has been merged into
  //   another one. The features of such a component (**) have no use in
  //   the construction of the final component tree.

  // PURPOSE OF THIS SECTION:
  //
  // - Construct table finalLabelTab_ that gives the final labels of the
  //   valid components. New labelling is computed so as to get a consecutive
  //   final numbering.
  //   finalLabelTab_[i] gives the final label of component initially labelled
  //   i, whose features are still available in inLabel_[i], color_[i], etc.
  // - Update labels in table inLabel_ by substituting the final valid
  //   label (given by table finalLabelTab_) for each label (see 3.2 below).
  // - Construct list validCompIdxList_ that records the indexes
  //   of the valid components.
  //   Such an index provides a direct access to the features of the
  //   corresponding component in tables inLabel_, color_, etc. In table
  //   equivLabelTab_, the value at such an index always is NO_LABEL
  //   (see 3.1 below).
  //   Index 0, which always corresponds to the component representing the
  //   background, is not registered in this list (see 3.3 below).
  //
  //        +---+---+---
  //        |   |   |...  validCompIdxList_
  //        +-|-+-|-+---
  //          |   |
  //          |   |
  //          v   v
  //    0  1  2   3  4 ...
  //   +--+--+--+--+--+-
  //   |NO|L1|NO|NO|L4|   equivLabelTab_
  //   +--+--+--+--+--+-
  //
  //   +--+--+--+--+--+-
  //   |I0|**|I2|I3|**|   inLabel_ (updated)
  //   +--+--+--+--+--+-
  //   |c0|**|c2|c3|**|   color_
  //   +--+--+--+--+--+-
  //   |  |**|  |  |**|   etc.
  //   +--+--+--+--+--+-
  //
  //   +--+--+--+--+--+-
  //   |l0|l1|l2|l3|  |   finalLabelTab_ : final labels
  //   +--+--+--+--+--+-
  //
  // NOTE: Once the required information is computed, table equivLabelTab_
  //       becomes useless...

  // Allocate space for the table of final labels 
  finalLabelTab_.reserve((unsigned int) labelCnt_);

  // By construction, final label of component 0 (background) is 0
  finalLabelTab_.push_back(0);

  // Free labels from the initial equivalence table
  deque<Component::label_type> freeLabels;

  // For each initial label, excepting 0
  for (int lab = 1 ; lab <= labelCnt_ ; ++lab)
    {
      if (equivLabelTab_[lab] == Component::LABEL_NO_)  // **** (3.1) ****
	{
	  // ____________________________________________________________________
	  //
	  // CURRENT LABEL IS VALID
	  // => it corresponds to a valid component
	  // => give this component a new label when possible

	  if (freeLabels.empty())
	    {
	      // No free label
	      // => the current label number remains unchanged
	      finalLabelTab_.push_back(lab);
	    }
	  else
	    {
	      // Free labels are available

	      // Use first free label
	      finalLabelTab_.push_back(freeLabels.back());
	      freeLabels.pop_back();

	      // Current label is now free
	      freeLabels.push_front(lab);
	    }

	  // Update final label count
	  // (by construction, it can never exceed the maximum label count)
	  ++finalLabelCnt_;

	  // (3.2) Update label of comprising component
	  // By construction, the corresponding valid label is already known
	  // (the valid label of a set of equivalent labels is the smallest one)
	  inLabel_[lab] = finalLabelTab_[inLabel_[lab]];

	  // (3.3) Component corresponding to current label is valid
	  // => save its index
	  validCompIdxList_.push_back(lab);
	  // ____________________________________________________________________
	}

      else

	{
	  // ____________________________________________________________________
	  //
	  // CURRENT LABEL IS NOT VALID
	  // => get the corresponding valid label and set equivalence
	  // By construction, the valid label is not greater than the current label

	  finalLabelTab_.push_back(finalLabelTab_[validLabel(lab)]);

	  // Current label is now free
	  freeLabels.push_front(lab);
	  // ____________________________________________________________________
	}

    } // END for


  // ============================================================================
  // (4) CONSTRUCTION OF THE FINAL IMAGE OF LABELS
  // ============================================================================

  // For each row rdx of the given binary image
  // - runRowsTab_[rdx] gives the successive run lengths
  // - labelRowsTab_[rdx] gives the corresponding labels
  //   These labels have not been updated and must be substituted by their
  //   final equivalent label, given by table finalLabelTab_
  
  // Pointer to the current pixel in the related pixel map
  Component::label_type* pMap = pMapCCImg_;

  // For each row
  for (int rdx = 0 ; rdx < height_ ; ++rdx)
    {
      int size = (int) (labelRowsTab_[rdx]).size();

      // for each run
      for (int ldx = 0 ; ldx < size ; ++ldx)
	{
	  // Get current run length
	  int lg = runRowsTab_[rdx][ldx];
	  // Get corresponding label and update it
	  Component::label_type lab = finalLabelTab_[labelRowsTab_[rdx][ldx]];

	  // Copy the labelled run into the pixel map
	  for (int idx = 0 ; idx < lg ; ++idx, ++pMap)
	    {
	      (*pMap) = lab;
	    }
	}
    } // END for each row


  // ============================================================================
  // (5) CONSTRUCT THE COMPONENT TREE
  // ============================================================================

  //                     _rCompTree
  //                  ________________
  //                 |                |    0     j     k
  //  +----------+   |      +--+      |   +--+--+--+--+--+- -+--+
  //  |COMPONENT |<----------C0|<----------- |  |  |  |  |   |  |  _rCompTab
  //  |LABELLED 0|   |      +--+      |   +--+--+|-+--+|-+- -+--+
  //  +----------+   |       /\       |          |     |
  //                 |      /  \      |          |     |
  //  +----------+   |  +--+    +--+  |          |     |
  //  |COMPONENT |<------Ci|    |Cj|<------------+     |
  //  |LABELLED i|   |  +--+    +--+  |                |
  //  +----------+   |    |     /||\  |                |
  //  +----------+   |  +--+          |                |
  //  |COMPONENT |<------Ck|<--------------------------+
  //  |LABELLED k|   |  +--+          |
  //  +----------+   |________________|
  //
  // Each component is associated with a label, which is an integer number.
  // In the resulting image, the value of the pixels of the component is
  // this same number.
  // See class qgar::Component for the way a component is represented.
  //
  // The set of components is hierarchically organized as a tree. Each node
  // represents a component (in fact, the data associated with the node is a
  // pointer to the component, Ci in the figure above), and its children
  // represent the components which are directly included into (i.e. has a
  // common border with) the component.
  //
  // The so-called component table provides a direct access to the nodes
  // representing the components, using their labels to index the table.
  // In other words, an element of this table is a pointer to the node
  // of the tree representing the component having the same label
  // as the element index.
  //
  // Indexes of valid components are given by list validCompIdxList_.
  // By construction, index 0 (background) is not included in this list
  // (see section 3).


  // Allocate space for the component table, and initialize it.
  // Each element of this table will be a pointer to the component
  // having the same label as the index of the element.

  rCompTab_.reserve((unsigned int) finalLabelCnt_);
  rCompTab_.insert(rCompTab_.begin(),
		   (unsigned int) finalLabelCnt_ + 1,
		   0);

  // Create component 0 (background)
  // and insert it as root of the component tree (initially empty)

  rCompTree_.insertParent
    (new Component
           (pCompImg_,    // pointer to component image
	    0,            // label
	    0,            // conventional self-inclusion
	    QGE_BW_WHITE, // color
	    0,            // X top left pixel
	    0,            // Y top left pixel
	    0,            // X top left corner (bounding box)
	    0,            // Y top left corner (bounding box)
	    colEndIdx_,   // X bottom right corner (bounding box)
	    rowEndIdx_ ,  // Y bottom right corner (bounding box)
	    areaPx_[0],   // area
	    offset3X3_4_, // offset table for 4-connectivity
	    offset3X3_8_) // offset table for 8-connectivity
     );

  // Update component table
  rCompTab_[0] = rCompTree_.pRoot();

  // Insert other components
  constructComponentTree(rCompTree_, rCompTree_.pRoot(), rCompTab_);

  // Set root as current node of the resulting tree
  rCompTree_.gotoRoot();

  // ============================================================================
  // END run construction of connected components
  // ============================================================================
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


ConnectedComponentsImpl::~ConnectedComponentsImpl()
{
  // VOID
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// F U N C T I O N S   W O R K I N G   O N   L A B E L S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// GET THE VALID LABEL OF (I.E. EQUIVALENT TO) A GIVEN LABEL

int
ConnectedComponentsImpl::validLabel(Component::label_type aLabel)
{
  Component::label_type l = aLabel;

  // The valid label is the smallest equivalent label
  // => just follow the equivalent links until finding no link

  while (equivLabelTab_[l] != Component::LABEL_NO_)
    {
      l = equivLabelTab_[l];
    }

  return l;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// F U N C T I O N S   W O R K I N G   O N   C O M P O N E N T S 
// -------------------------------------------------------------------
// -------------------------------------------------------------------

// MERGE COMPONENT INCLUDING PREVIOUS RUN
// AND COMPONENT INCLUDING CURRENT RUN
//
// WARNING: By construction, component with the greatest label must be
// merged into component with the smallest label

void
ConnectedComponentsImpl::mergePrevAndCurrComponents()
{
  if (currLabel_ == Component::LABEL_NO_)

    // ______________________________________________________________
    {
      // CURRENT RUN IS NOT YET LABELLED
      // => merge current run into previous valid component

      // The valid label of the previous run becomes the current label
      currLabel_ = validLabel(prevLabel_);

      // The top left pixel of the component should not change
      // No update necessary

      // Update bounding box
      if (currRunBeginX_ < xTopLeft_[currLabel_])
	{
	  xTopLeft_[currLabel_] = currRunBeginX_;
	}
      if (currRunEndX_ > xBottomRight_[currLabel_])
	{
	  xBottomRight_[currLabel_] = currRunEndX_;
	}
      yBottomRight_[currLabel_] = rowIdx_;

      // Update area
      areaPx_[currLabel_] += currRunEndX_ - currRunBeginX_ + 1;

      // SAVE current run and its label
      runRowsTab_[rowIdx_].push_back(currRunEndX_ - currRunBeginX_ + 1);
      labelRowsTab_[rowIdx_].push_back(currLabel_);
    }
    // ______________________________________________________________

  else

    {
      // Valid labels of previous and current runs
      Component::label_type prevValidLabel = validLabel(prevLabel_);
      Component::label_type currValidLabel = validLabel(currLabel_);

      if (prevValidLabel == currValidLabel)
	// __________________________________________________________
	{
	  // PREVIOUS AND CURRENT RUNS
	  // ALREADY BELONG TO THE SAME COMPONENT
	  // => nothing to do
	  return;
	}
	// __________________________________________________________

      if (prevValidLabel < currValidLabel)

	// __________________________________________________________
	{
	  // THE VALID LABEL OF THE PREVIOUS RUN
	  // IS SMALLER THAN THE VALID LABEL OF THE CURRENT RUN
	  // => merge component of the current run
	  //    into component of the previous run

	  // Update top left pixel
	  if (yTopLeftPix_[currValidLabel] < yTopLeftPix_[prevValidLabel])
	    {
	      xTopLeftPix_[prevValidLabel] = xTopLeftPix_[currValidLabel];
	      yTopLeftPix_[prevValidLabel] = yTopLeftPix_[currValidLabel];
	    }

	  // Update bounding box
	  if (xTopLeft_[currValidLabel] < xTopLeft_[prevValidLabel])
	    {
	      xTopLeft_[prevValidLabel] = xTopLeft_[currValidLabel];
	    }
	  if (yTopLeft_[currValidLabel] < yTopLeft_[prevValidLabel])
	    {
	      yTopLeft_[prevValidLabel] = yTopLeft_[currValidLabel];
	    }
	  if (xBottomRight_[currValidLabel] > xBottomRight_[prevValidLabel])
	    {
	      xBottomRight_[prevValidLabel] = xBottomRight_[currValidLabel];
	    }
	  if (yBottomRight_[currValidLabel] > yBottomRight_[prevValidLabel])
	    {
	      yBottomRight_[prevValidLabel] = yBottomRight_[currValidLabel];
	    }

	  // Update area
	  areaPx_[prevValidLabel] += areaPx_[currValidLabel];
	  
	  // Update table of equivalent labels
	  equivLabelTab_[currLabel_]     = prevValidLabel;
	  equivLabelTab_[currValidLabel] = prevValidLabel;

	  // Update labels
	  prevLabel_ = prevValidLabel;
	  currLabel_ = prevValidLabel;
	}
	// __________________________________________________________

      else

	// __________________________________________________________
	{
	  // THE VALID LABEL OF THE CURRENT RUN
	  // IS SMALLER THAN THE VALID LABEL OF THE PREVIOUS RUN
	  // => merge component of the previous run
	  //    into component of the current run

	  // Update top left pixel
	  if (yTopLeftPix_[prevValidLabel] < yTopLeftPix_[currValidLabel])
	    {
	      xTopLeftPix_[currValidLabel] = xTopLeftPix_[prevValidLabel];
	      yTopLeftPix_[currValidLabel] = yTopLeftPix_[prevValidLabel];
	    }

	  // Update bounding box
	  if (xTopLeft_[prevValidLabel] < xTopLeft_[currValidLabel])
	    {
	      xTopLeft_[currValidLabel] = xTopLeft_[prevValidLabel];
	    }
	  if (yTopLeft_[prevValidLabel] < yTopLeft_[currValidLabel])
	    {
	      yTopLeft_[currValidLabel] = yTopLeft_[prevValidLabel];
	    }
	  if (xBottomRight_[prevValidLabel] > xBottomRight_[currValidLabel])
	    {
	      xBottomRight_[currValidLabel] = xBottomRight_[prevValidLabel];
	    }
	  if (yBottomRight_[prevValidLabel] > yBottomRight_[currValidLabel])
	    {
	      yBottomRight_[currValidLabel] = yBottomRight_[prevValidLabel];
	    }

	  // Update area
	  areaPx_[currValidLabel] += areaPx_[prevValidLabel];

	  // Update equivalent labels
	  equivLabelTab_[prevLabel_]     = currValidLabel;
	  equivLabelTab_[prevValidLabel] = currValidLabel;
	  
	  // Update labels
	  prevLabel_ = currValidLabel;
	  currLabel_ = currValidLabel;
	}
	// __________________________________________________________
    }

}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// F U N C T I O N S   W O R K I N G   O N   R U N S
// -------------------------------------------------------------------
// -------------------------------------------------------------------

// MOVE TO NEXT RUN IN PREVIOUS ROW

void
ConnectedComponentsImpl::nextPrevRun()
{
  // Increment previous run index
  ++prevRunIdx_;

  // New current run label
  prevLabel_ = labelRowsTab_[prevRowIdx_][prevRunIdx_];

  // New current run indexes
  prevRunBeginX_ = prevRunEndX_ + 1;
  prevRunEndX_   = prevRunBeginX_ + runRowsTab_[prevRowIdx_][prevRunIdx_] - 1;

  // New current run color
  prevColor_ = qgBWswitch(prevColor_);
}


// MOVE TO NEXT RUN IN CURRENT ROW

void
ConnectedComponentsImpl::nextCurrRun()
{
  if (ptRow_ != ptRowEnd_)
    {
      // _____________________________________________________________
      //
      // End of current row is not yet reached

      currRunBeginX_ = currRunEndX_ + 1;    // new run beginning index
      currColor_ = qgBWswitch(currColor_);  // new current color

      // Look for index of new run end (while pixels have the current color)

      while ((*ptRow_ == currColor_) && (ptRow_ < ptRowEnd_))
	//                               ^^^^^^^^^^^^^^^^^^
	// WARNING: The last pixel pixel is not taken into account
	//          as it is always considered as WHITE
	{
	  ++ptRow_;
	  ++currRunEndX_;
	}
      
      // WARNING: Last pixel considered as WHITE
      // => If row end is reached and new run is WHITE,
      //    add last pixel to new run

      if ((ptRow_ == ptRowEnd_) && (currColor_ == QGE_BW_WHITE))
	{
	  ++ptRow_;
	  ++currRunEndX_;
	}
      // _____________________________________________________________
    }
  else
    {
      // _____________________________________________________________
      //
      // End of current row is reached: Whatever the color
      // of the last pixel is, it is considered as WHITE
      // By construction, current run is BLACK before this point
      // (see above): The last pixel determines a one-pixel WHITE run.

      ++ptRow_;

      // New run includes only 1 pixel and is WHITE
      currRunEndX_  += 1;
      currRunBeginX_ = currRunEndX_;
      currColor_     = QGE_BW_WHITE;
      // _____________________________________________________________
    }

  ++currRunIdx_;                      // New current run index
  currLabel_ = Component::LABEL_NO_;  // New run is not yet labelled
}


// END OF PREVIOUS RUN AND END OF CURRENT RUN COINCIDE
// => PERFORM MOVES ACCORDING TO BLACK- AND WHITE-CONNECTIVITY
//
// WARNING
// End of current row must be tested before calling this function

void
ConnectedComponentsImpl::prevAndCurrRunsCoincide()
{
  if (currColor_ == prevColor_)
    {
      // PREVIOUS RUN AND CURRENT HAVE THE SAME COLOR
      //
      //  end of previous run
      //            v 
      //  -+-+-+-+-+-+-+-+-+-+-
      //   |x|x|x|x|x||y|y|y|
      //  -+-+-+-+-+-+-+-+-+-+-
      //   |x|x|x|x|x|y|y|y|y|
      //  -+-+-+-+-+-+-+-+-+-+-
      //            ^
      //  end of current run
      //
      // => just move to next run in previous and current rows

      nextPrevRun();
      nextCurrRun();
    }

  //      b b b               w
  //      b * b             w * w
  //      b b b               w
  //
  //  8-connectivity    4-connectivity
  //    for BLACK         for WHITE

  else if (currColor_ == QGE_BW_WHITE)
    {
      // PREVIOUS RUN IS BLACK AND CURRENT RUN IS WHITE
      //
      //  end of previous run
      //            v 
      //  -+-+-+-+-+-+-+-+-+-+-
      //   |b|b|b|b|b|w|w|w|w|        previous run
      //  -+-+-+-+-+-+-+-+-+-+-       is connected to
      //   |w|w|w|w|w|b|b|b|b|        next current run
      //  -+-+-+-+-+-+-+-+-+-+-
      //            ^
      //  end of current run
      //
      // => move to next run in current row
  
      nextCurrRun();
    }
  else
    {
      // PREVIOUS RUN IS WHITE AND CURRENT RUN IS BLACK
      //
      //  end of previous run
      //            v 
      //  -+-+-+-+-+-+-+-+-+-+-
      //   |w|w|w|w|w|b|b|b|b|        next previous run
      //  -+-+-+-+-+-+-+-+-+-+-       is connected to
      //   |b|b|b|b|b|w|w|w|w|        current run
      //  -+-+-+-+-+-+-+-+-+-+-
      //            ^
      //  end of current run
      //
      // => move to next run in previous row
      
      nextPrevRun();
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// FUNCTIONS  WORKING  ON  THE  COMPONENT  TREE
// -------------------------------------------------------------------
// -------------------------------------------------------------------

// CONSTRUCT THE COMPONENT TREE

// Each node represents a component
// Components represented by children nodes are included
// in the component represented by their parent node

// aTree  : reference to the tree being constructed
// aPNode : pointer to a node representing a component
//          which has not yet children
// aCCTab : reference to the table containing pointers to components
//          aCCTab[lab] gives a pointer to the component labelled lab
//          (lab is final valid label)

// validCompIdxList_ provides components which are not yet included
// in the tree: Each of its elements is an index of a valid component
// in tables storing component features.

void
ConnectedComponentsImpl::constructComponentTree
  (ConnectedComponents::tree_type&          aTree,
   ConnectedComponents::node_type*          aPNode,
   vector<ConnectedComponents::node_type*>& aCCTab)
{
  // No more component to insert in the tree
  if (validCompIdxList_.size() == 0)
    {
      return;
    }

  // Label of the given component
  Component::label_type parentLabel = (aPNode->accessData())->label();
  
  list<int>::iterator itCC = validCompIdxList_.begin();

  while (itCC != validCompIdxList_.end())
    {

    // While there are components
    // ______________________________________________________________
    //
      // Index of the current component
      int ccIdx = *itCC;
      // Valid label of the current component
      Component::label_type lab = finalLabelTab_[ccIdx];

      if (inLabel_[ccIdx] == parentLabel)
	{
	  // CURRENT COMPONENT IS INCLUDED IN GIVEN COMPONENT (NODE)
	  // => it becomes a child of the given component

	  // Instantiation of a new component
	  // and insertion in the component tree
	  aTree.insertFirstChild
	    (new Component
	           (pCompImg_,            // pointer to component image
		    lab,                  // label
		    inLabel_[ccIdx],      // comprising component label
		    color_[ccIdx],        // color
		    xTopLeftPix_[ccIdx],  // top left pixel
		    yTopLeftPix_[ccIdx],  //
		    xTopLeft_[ccIdx],     // bounding box
		    yTopLeft_[ccIdx],     //
		    xBottomRight_[ccIdx], //
		    yBottomRight_[ccIdx], //
		    areaPx_[ccIdx],       // area
		    offset3X3_4_,         // offset table for 4-connectivity
		    offset3X3_8_),        // offset table for 8-connectivity

	     aPNode);

	  // Update component table
	  aCCTab[lab] = aPNode->pFirstChild();

	  // Remove index of current component from available indexes
	  // WARNING: Removal invalidates the iterator that points
	  //          to the removed element

	  // Save iterator
	  list<int>::iterator itCCaux = itCC;
	  // Increment iterator to get next component index
	  ++itCC;
	  // Delete used index
	  validCompIdxList_.erase(itCCaux);
	}
      else
	{
	  // CURRENT COMPONENT IS NOT INCLUDED IN GIVEN COMPONENT (NODE)
	  // => just increment iterator to get next component index
	  ++itCC;
	}

    } // END while
    // ______________________________________________________________

  
  // Look for children of each new included component

  ConnectedComponents::node_type* pChild = aPNode->pFirstChild();

  while (pChild != 0)
    {
      constructComponentTree(aTree, pChild, aCCTab);
      pChild = pChild->pRSibling();
    }
}

// -------------------------------------------------------------------
// -------------------------------------------------------------------

} // namespace qgar
