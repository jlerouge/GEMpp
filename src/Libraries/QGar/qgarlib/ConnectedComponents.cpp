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
 * @file ConnectedComponents.cpp
 *
 * @brief Implementation of class qgar::ConnectedComponents.
 *
 * See file ConnectedComponents.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 21, 2004  12:58
 * @since  Qgar 2.1.1
 */



// STD
#include <cstring>
#include <deque>
#include <list>
#include <vector>
// QGAR
#include "Component.h"
#include "ConnectedComponents.h"
#include "ConnectedComponentsImpl.h"
#include "GenImage.h"
#include "QgarErrorDeveloper.h"



namespace qgar
{

// -------------------------------------------------------------------
// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
// WARNING: the default constructor belongs to the private section
// so that clients cannot use it

ConnectedComponents::ConnectedComponents()
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::ConnectedComponents::ConnectedComponents()",
			   "Disabled constructor: should not be used!");
}
// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW



// CONSTRUCT FROM GIVEN BINARY IMAGE

ConnectedComponents::ConnectedComponents(const BinaryImage& aBinImg)

  : componentImg_(ConnectedComponents::image_type(aBinImg.width(),
						  aBinImg.height()))

{
  // Initialize offset tables used during contour following
  // to get 4- and 8-connected neighbors in a 3X3 neighborhood.
  // See class qgar::Component for full details.

  int w = aBinImg.width();

  // 4-CONNECTIVITY
  //
  //   current (contour) direction
  //   N       E       S       W
  //   0   1   2   3   4   5   6   7   8   9  10  11  12 
  // +---+---+---+---+---+---+---+---+---+---+---+---+---+
  // | -1| * | -w| * | 1 | * | w | * | -1| * |-w | * | 1 |
  // +---+---+---+---+---+---+---+---+---+---+---+---+---+

  int tmpOff4[13] =
    {
      -1, 0, -w, 0, 1, 0, w, 0, -1, 0, -w, 0, 1
    };

  offset3X3_4_ = new int[13];
  memcpy(offset3X3_4_, tmpOff4, 13 * sizeof(int));

  // 8-CONNECTIVITY
  //
  //                      search rank
  //                      0    1    2    3    4    5  
  //                   +----+----+----+----+----+----+
  //            / N  0 | -1 | -w |-w-1|  1 |-w+1|  w |
  //            |      +----+----+----+----+----+----+
  //            | NE 1 | -w |-w-1|  1 |-w+1| w+1| w-1|
  //            |      +----+----+----+----+----+----+
  //            | E  2 | -w |  1 |-w+1|  w | w+1| -1 |
  //            |      +----+----+----+----+----+----+
  //  current   | SE 3 |  1 |-w+1|  w | w+1| w-1|-w-1|
  //  contour  <       +----+----+----+----+----+----+
  // direction  | S  4 |  1 |  w | w+1| -1 | w-1| -w |
  //            |      +----+----+----+----+----+----+
  //            | SW 5 |  w | w+1| -1 | w-1|-w-1|-w+1|
  //            |      +----+----+----+----+----+----+
  //            | W  6 |  w | -1 | w-1| -w |-w-1|  1 |
  //            |      +----+----+----+----+----+----+
  //            \ NW 7 | -1 | w-1| -w |-w-1|-w+1| w+1|
  //                   +----+----+----+----+----+----+

  int tmpOff8[48] =
    {
      -1,   -w, -w-1,    1, -w+1,    w,
      -w, -w-1,    1, -w+1,  w+1,  w-1,
      -w,    1, -w+1,    w,  w+1,   -1,
       1, -w+1,    w,  w+1,  w-1, -w-1,
       1,    w,  w+1,   -1,  w-1,   -w,
       w,  w+1,   -1,  w-1, -w-1, -w+1,
       w,   -1,  w-1,   -w, -w-1,    1,
      -1,  w-1,   -w, -w-1, -w+1,  w+1 
   };

  offset3X3_8_ = new int[48];
  memcpy(offset3X3_8_, tmpOff8, 48 * sizeof(int));

  // Initialize data in order to run the construction of components
  ConnectedComponentsImpl ccImpl(aBinImg,
				 &componentImg_,
				 componentTree_,
				 componentTab_,
				 offset3X3_4_,
				 offset3X3_8_);

   // Run the construction of connected components
  ccImpl.run();
}


// COPY CONSTRUCTOR
// WARNING: Perform a deep copy

ConnectedComponents::ConnectedComponents(const ConnectedComponents& aCC)

  : componentImg_  (aCC.componentImg_),
    componentTree_ (aCC.componentTree_),
    componentTab_  ((aCC.componentTab_).size(), 0),
    offset3X3_4_   (aCC.offset3X3_4_),
    offset3X3_8_   (aCC.offset3X3_8_)

{
  // Components are not duplicated
  // as data stored in tree nodes are pointers to components
  // => effective duplication of components
  //    and subsequent updating of the component table

  PRIVATEcopyCC((aCC.componentTree_).pRoot(), componentTree_.pRoot());
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------
// -------------------------------------------------------------------


ConnectedComponents::~ConnectedComponents()
{
  // Delete offset tables

  delete [] offset3X3_4_;
  delete [] offset3X3_8_;

  // Delete components

  for(std::vector<ConnectedComponents::node_type*>::iterator itN
	= componentTab_.begin();
      itN != componentTab_.end();
      ++itN)
    {
      delete (*itN)->data();
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// R E C O N S T R U C T   B I N A R Y   I M A G E S 
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// RECONSTRUCT A BINARY IMAGE FROM GIVEN LABELS
// A pixel of the resulting image is BLACK if it belongs to a black
// component whose label is in the set of given labels.
// Given labels out of the range of current labels are ignored.

BinaryImage*
ConnectedComponents::makeBinaryImg
  (const std::vector<Component::label_type>& aLabSet)
{
  // Create the resulting image
  BinaryImage* pImgBin = new BinaryImage(componentImg_.width(),
					 componentImg_.height());

  // Pointers to pixel maps
  Component::label_type* pMapCC  = componentImg_.pPixMap();
  BinaryImage::pointer   pMapBin = pImgBin->pPixMap();

  // Current label and color
  Component::label_type currLab   = Component::LABEL_NO_;
  QGEbw                 currColor = QGE_BW_WHITE;

  // Number of pixels of both images
  int size = componentImg_.width() * componentImg_.height();


  // For each pixel of the component image

  for (int iCnt = 0 ; iCnt< size ; ++iCnt, ++pMapCC, ++pMapBin)
    {

      if (*pMapCC != currLab)
	{
	  // The new pixel belongs to a new component
	  
	  currLab = *pMapCC;

	  std::vector<Component::label_type>::const_iterator it =
	    find(aLabSet.begin(), aLabSet.end(), currLab);

	  if (   (it == aLabSet.end())
	      || ((*this)[currLab].color() == QGE_BW_WHITE))
	    {
	      // Current label does not belong to the given set
	      // or belongs to a WHITE component
	      currColor = QGE_BW_WHITE;
	    }
	  else
	    {
	      // Current label belongs to a BLACK component
	      currColor = QGE_BW_BLACK;
	    }
	}

      // Set the corresponding pixel of the resulting image
      // to current color
      *pMapBin = currColor;

    } // END for iCnt


  // Return a pointer to the resulting image
  return pImgBin;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// ASSIGNMENT

ConnectedComponents&
ConnectedComponents::operator=(const ConnectedComponents& aCC)
{
  // Are left hand side and right hand side different objects?
  if (this != &aCC)
    {
      // Copy component tree and component table
      componentImg_  = aCC.componentImg_;
      componentTree_ = aCC.componentTree_;
      componentTab_  = aCC.componentTab_;

      // The tree of the given CC image is duplicated, but the data
      // pointed by nodes (i.e. components) are not

      // Effective duplication of components
      // and subsequent updating of the component table
      PRIVATEcopyCC((aCC.componentTree_).pRoot(),
		    componentTree_.pRoot());
    }

  return *this;
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------
// A U X I L I A R I E S
// -------------------------------------------------------------------
// -------------------------------------------------------------------


// Copy components stored in tree whose root is node IN and store them
// in corresponding nodes of tree whose root is node OUT.
// WARNING: both trees must have the same structure (the tree including
// node OUT is supposed to be a copy of the tree including node IN).

void
ConnectedComponents::PRIVATEcopyCC(ConnectedComponents::node_type* aPNodeIn,
				   ConnectedComponents::node_type* aPNodeOut)
{
  if (aPNodeIn != 0)
    {
      // Copy current component
      Component* cc = new Component(*(aPNodeIn->data()));

      // Store copy and update component table
      aPNodeOut->setData(cc);
      componentTab_[cc->label()] = aPNodeOut;

      // Copy children and siblings
      PRIVATEcopyCC(aPNodeIn->pFirstChild(), aPNodeOut->pFirstChild());
      PRIVATEcopyCC(aPNodeIn->pRSibling(),   aPNodeOut->pRSibling());
    }
}


// -------------------------------------------------------------------
// -------------------------------------------------------------------

} // namespace qgar
