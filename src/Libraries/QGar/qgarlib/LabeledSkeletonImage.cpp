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
 * @file   LabeledSkeletonImage.cpp
 * @brief  Implementation of class qgar::LabeledSkeletonImage.
 *
 *         See file LabeledSkeletonImage.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Adlane Habed and Karl Tombre</a>
 * @date   July 3, 2001  16:57
 * @since  Qgar 1.0
 */



// STD
#include <vector>
#include <limits>
// QGAR
#include "Dist34BlackCCImage.h"
#include "GenImage.h"
#include "LabeledSkeletonImage.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"


using namespace std;

namespace qgar
{

// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//
// C O N S T A N T S
//
// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC


//***************************************************************//
//                                                               //
//                         NEIGHBORHOOD                          //
//                                                               //
//***************************************************************//

// +-----------------------------------------------------+
// |                                                     |
// |          |  |  |  |                                 |
// |         -+--+--+--+-                                |
// |          |N2|N3|N4|                                 |
// |         -+--+--+--+-                                |
// |          |N1|N0|N5|                                 |
// |         -+--+--+--+-                                |
// |          |N8|N7|N6|                                 |
// |         -+--+--+--+-                                |
// |          |  |  |  |                                 |
// |                                                     |
// +-----------------------------------------------------+

static const int N1 = 1;
static const int N2 = 2;
static const int N3 = 3;
static const int N4 = 4;
static const int N5 = 5;
static const int N6 = 6;
static const int N7 = 7;
static const int N8 = 8;
static const int N9 = 9;  //N9 == N1


//***************************************************************//
//                                                               //
//        3 KIND OF MARKERS TO MARK SKELETAL PIXELS              //
//                                                               //
//***************************************************************//


// ===============
// UNMARKED PIXELS
// ===============
//
// Used for unmarked pixels

static const GreyLevelImage::value_type SKELETON_UNMARKED_PIXEL =
  numeric_limits<GreyLevelImage::value_type>::max();

// =========
// PARALLELWISE DETECTABLE SKELETON PIXEL
// =========
//
// Used for pixels marked during the parallelwise detection

static const GreyLevelImage::value_type SKELETON_PARALLELWISE_PIXEL = 0;

// =========
// SEQUENTIALLY DETECTABLE SKELETON PIXEL
// =========
//
// Used for pixels marked during the sequentially detection

static const GreyLevelImage::value_type SKELETON_SEQUENTIALLY_PIXEL = 1;

// =========
// GENERAL MARKER
// =========
//
// Used for the other marked pixels

static const GreyLevelImage::value_type SKELETON_MARKER = 2;



//***************************************************************//
//                                                               //
//        LENGTH OF UNIT MOVES FOR THE (3,4) DT                  //
//                                                               //
//***************************************************************//


// =========
// LENGTH OF HORIZONTAL/VERTICAL UNIT MOVE
// =========
//
// 3 in the (3,4)-DT

static const GreyLevelImage::value_type LENGTH_HV_UNIT_MOVE = 3;
static const double LENGTH_HV_UNIT_MOVE_DOUBLE = 3.0;

// =========
// LENGTH OF DIAGONAL UNIT MOVE
// =========
//
// 4 in the (3,4)-DT

static const GreyLevelImage::value_type LENGTH_DIAG_UNIT_MOVE = 4;
static const double LENGTH_DIAG_UNIT_MOVE_DOUBLE = 4.0;


//***************************************************************//
//                                                               //
//                         LABELS                                //
//                                                               //
//***************************************************************//


// =========
// LABEL 1
// =========
//
// Used for pixels labeled 1

static const int LABEL_1 = 1;

// =========
// LABEL 3
// =========
//
// Used for pixels labeled 3

static const int LABEL_3 = 3;

// =========
// LABEL 5
// =========
//
// Used for pixels labeled 5

static const int LABEL_5 = 5;

// =========
// LABEL 6
// =========
//
// Used for pixels labeled 6

static const int LABEL_6 = 6;


//***************************************************************//
//                                                               //
//                           MISC                                //
//                                                               //
//***************************************************************//


// =========
// BACKGROUND LABEL
// =========
//
// Used for background pixels

static const GreyLevelImage::value_type BACKGROUND_PIXEL = 0;


// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//
// E N D   O F   C O N S T A N T S
//
// CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC


// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// L O C A L S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL


// ========================================
// UPDATE LABELS
// ========================================
// 3 -> 1 and 6 -> 5 in order to avoid
// wrong detections of maximal centers
// for the parallewise detectable skeleton
// pixels (see referenced article page 109)
// ========================================

GreyLevelPixel
updateLabel(GreyLevelImage::pointer pLabel)
{
  GreyLevelImage::value_type label = *pLabel;

  if (label == LABEL_3)
  {
    return LABEL_1;
  }

  else if (label == LABEL_6)
  {
    return LABEL_5;
  }
  else
  {
    return label;
  }
}

// ==================================================================
// STORE THE LABELS OR THE MARKERS FOR A NEIGHBORHOOD IN A TABLE
// ==================================================================
//
// pMap  : pointer to a map (labeled image or marker map)
// pNghb : table of 10 elements (neighborhood)
// aWidth: image width
//
//  <----------------- image width --------------------->
// +-----------------------------------------------------+
// |                                                     |
// |          |  |  |  |                                 |
// |         -+--+--+--+-                                |
// |          |N2|N3|N4|                                 |
// |         -+--+--+--+-                                |
// |          |N1|N0|N5|                                 |
// |         -+--+--+--+-                                |
// |          |N8|N7|N6|                                 |
// |         -+--+--+--+-                                |
// |          |  |  |  |                                 |
// |                                                     |
// +-----------------------------------------------------+
//
// - pImg initially points the center pixel of a neighborhood (N0)
// - the pixel values (N*) are stored in table pNghb according
//   to the neighborhood numbering
// - the last value is always N1
//
//         +--+--+--+--+--+--+--+--+--+--+
//   pNghb |N0|N1|N2|N3|N4|N5|N6|N7|N8|N1|
//         +--+--+--+--+--+--+--+--+--+--+
//          0  1  2  3  4  5  6  7  8  9
//
// ==================================================================

void
StoreNeighborsFromAMap(GreyLevelPixel pMap[], GreyLevelPixel pNghb[], int aWidth)
{

  GreyLevelImage::pointer QGL_UP   = pMap - aWidth;
  GreyLevelImage::pointer QGL_DOWN = pMap + aWidth;

  GreyLevelImage::value_type n1;

  //N0
  *pNghb = *pMap;

  //N1
  ++pNghb;
  n1 = *(pMap - 1);
  *pNghb = n1;

  //N2
  ++pNghb;
  *pNghb = *(QGL_UP - 1);

  //N3
  ++pNghb;
  *pNghb = *(QGL_UP);

  //N4
  ++pNghb;
  *pNghb = *(QGL_UP + 1);

  //N5
  ++pNghb;
  *pNghb = *(pMap + 1);

  //N6
  ++pNghb;
  *pNghb = *(QGL_DOWN + 1);

  //N7
  ++pNghb;
  *pNghb = *(QGL_DOWN);

  //N8
  ++pNghb;
  *pNghb = *(QGL_DOWN - 1);

  //N9
  ++pNghb;
  *pNghb = n1;  // n[9] == n[1]
}

// ====================================================================
// STORE THE UPDATED LABELS OF A LABELED IMAGE NEIGHBORHOOD IN A TABLE
// ====================================================================
// Store the neighborhood in a table with the
// transformation 3 -> 1 and 6 -> 5 for the labels
// ====================================================================

void
StoreUpdatedLabeledNeighborsFromALabeledImg(GreyLevelPixel pImg[], GreyLevelPixel pNghb[], int aWidth)
{

  GreyLevelImage::pointer QGL_UP   = pImg - aWidth;
  GreyLevelImage::pointer QGL_DOWN = pImg + aWidth;

  GreyLevelImage::value_type n1;

  //N0
  *pNghb = updateLabel(pImg);

  //N1
  ++pNghb;
  n1 = updateLabel(pImg - 1);
  *pNghb = n1;

  //N2
  ++pNghb;
  *pNghb = updateLabel(QGL_UP - 1);

  //N3
  ++pNghb;
  *pNghb = updateLabel(QGL_UP);

  //N4
  ++pNghb;
  *pNghb = updateLabel(QGL_UP + 1);

  //N5
  ++pNghb;
  *pNghb = updateLabel(pImg + 1);

  //N6
  ++pNghb;
  *pNghb = updateLabel(QGL_DOWN + 1);

  //N7
  ++pNghb;
  *pNghb = updateLabel(QGL_DOWN);

  //N8
  ++pNghb;
  *pNghb = updateLabel(QGL_DOWN - 1);

  //N9
  ++pNghb;
  *pNghb = n1;  // n[9] == n[1]
}

// ===========================================================
// GRADIENT IN A 3*3 NEIGHBORHOOD
// ===========================================================
//
// aGrad  : table of the gradient of each neighbor (N0 - N8)
// aNbgh : table of 10 elements (neighborhood)
//
//         +--+--+--+--+--+--+--+--+--+
//   aGrad |G0|G1|G2|G3|G4|G5|G6|G7|G8|
//         +--+--+--+--+--+--+--+--+--+
//          0  1  2  3  4  5  6  7  8
//
//         +--+--+--+--+--+--+--+--+--+--+
//   aNbgh |N0|N1|N2|N3|N4|N5|N6|N7|N8|N1|
//         +--+--+--+--+--+--+--+--+--+--+
//          0  1  2  3  4  5  6  7  8  9
//
//  the gradient of each element of the neighborhood (aNbgh)
//  is computed and stored in the table aGrad
//  See the referenced article page 112 for more details
//
// ==========================================================

void
gradient3x3(double aGrad[], GreyLevelImage::value_type aNbgh[])
{

  GreyLevelImage::value_type p = *aNbgh;

  *aGrad = 0.0;
  ++aGrad;

  GreyLevelImage::pointer pNeighbor = aNbgh + 1;

  for (int idx = 1 ; idx < 9 ; ++idx, ++aGrad, ++pNeighbor)
  {
    *aGrad = (*pNeighbor - p) / (((idx % 2) == 0) ? LENGTH_DIAG_UNIT_MOVE_DOUBLE : LENGTH_HV_UNIT_MOVE_DOUBLE);
  }
}

// =====================================================================
// FIND, IF ANY, SECOND POSITION WITH
// SAME MAXIMUM GRADIENT
// =====================================================================
// Two disjoint increasing paths may originate from the same pixel
// only when this is a saddle pixel of a hourglass saddle configuration.
// On the (3,4)-DT, the hourglass configuration may be centered only on
// pixels labeled 3 or 4. We check the possibility of growing a second
// path only for these pixels.
// =====================================================================

int
maxGrad2Idx(double aGrad[],
            GreyLevelImage::pointer pImg,
            int max1Idx)
{
  int max2Idx = 0;
  double previousMaxGrad = aGrad[max1Idx];

  //We have a second disjoint increasing path only on pixels labeled 3 or 4

  if ((*pImg == LENGTH_HV_UNIT_MOVE) || (*pImg == LENGTH_DIAG_UNIT_MOVE))
  {

    for(int idx = max1Idx + 1 ; idx < 9 ; ++idx)
    {
      if(aGrad[idx] == previousMaxGrad)
      {
        max2Idx = idx;
      }
    }
  }

  return max2Idx;
}


// =============================================================================
// FIND SEQUENTIALLY DETECTABLE SKELETON
// PIXELS FROM A MARKED PIXEL
// =============================================================================
//
//  The sequentially detectable skeletal pixels
//  are identified by growing increasing paths
//  along the direction of the steepest
//  gradient in the (3,4)-DT, starting from any
//  already marked pixel. The connecting path is
//  grown by marking as skeletal pixels for which
//  the maximal value of the gradient is positive.
//
//  Each pixels found as sequentially detectable
//  skeleton pixel is marked with SKELETON_SEQUENTIALLY_PIXEL
//
//  pLabeledImg : pointer to a label of a labeled image
//  pMarkerMap  : pointer to a marker
//  aWidth      : width of the labeled image (pLabeledImg)
//
//  pMarkerMap initially points a label marked with SKELETON_PARALLELWISE_PIXEL
//  pLabeledImg initially points to the corresponding label in the labeled image
//
// ==============================================================================

void
findSequentiallyDetectableSkeletonPixels(GreyLevelImage::pointer pLabeledImg,
    GreyLevelImage::pointer pMarkerMap,
    int aWidth)
{

  //Local constants
  const int QGL_WIDTH_MINUS_1  = aWidth - 1;
  const int QGL_WIDTH_PLUS_1   = aWidth + 1;

  //label of each neighbor of the current point
  GreyLevelImage::value_type labels[10];

  //gradient value for each neighbor of the current point
  double gradient[9];

  //we store the labels of the neighborhood in a table
  StoreNeighborsFromAMap(pLabeledImg, labels, aWidth);

  //compute gradient in distance image
  gradient3x3(gradient, labels);

  //find the max positive value of the gradient
  int max1Idx = qgMaxElement(gradient, 0 ,8);

  //find, if any, the second max positive value of the gradient
  int max2Idx = maxGrad2Idx(gradient, pLabeledImg, max1Idx);
  ;

  //used if there is a second increasing path
  bool notTerminated = true;


  while (notTerminated)
  {
    GreyLevelImage::pointer pLabeledImgAux = pLabeledImg;
    GreyLevelImage::pointer pMarkerMapAux = pMarkerMap;

    while (max1Idx != 0)
    {
      // Go in the direction of maximum gradient

      switch(max1Idx)
      {

        case N1:
        --pLabeledImgAux;
        --pMarkerMapAux;
        *pMarkerMapAux = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N2:
        pLabeledImgAux -= QGL_WIDTH_PLUS_1;
        pMarkerMapAux  -= QGL_WIDTH_PLUS_1;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N3:
        pLabeledImgAux -= aWidth;
        pMarkerMapAux  -= aWidth;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N4:
        pLabeledImgAux -= QGL_WIDTH_MINUS_1;
        pMarkerMapAux  -= QGL_WIDTH_MINUS_1;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N5:
        ++pLabeledImgAux;
        ++pMarkerMapAux;
        *pMarkerMapAux = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N6:
        pLabeledImgAux += QGL_WIDTH_PLUS_1;
        pMarkerMapAux  += QGL_WIDTH_PLUS_1;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N7:
        pLabeledImgAux += aWidth;
        pMarkerMapAux  += aWidth;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        case N8:
        pLabeledImgAux += QGL_WIDTH_MINUS_1;
        pMarkerMapAux  += QGL_WIDTH_MINUS_1;
        *pMarkerMapAux  = SKELETON_SEQUENTIALLY_PIXEL;
        break;

        default:
        ostringstream os;
        os << "Bad Gradient index: "
        << max1Idx;
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "qgar::LabeledSkeletonImage::LabeledSkeletonImage(const Dist34BlackCCImage&, int)",
                                 os.str());
        break;
      } // END switch

      //compute gradient at new position
      StoreNeighborsFromAMap(pLabeledImgAux, labels, aWidth);

      gradient3x3(gradient, labels);

      //find the max positive value of the gradient
      max1Idx = qgMaxElement(gradient, 0 ,8);

    } // END while max1Idx

    if (max2Idx != 0) // there was another starting point
    {
      max1Idx = max2Idx;
      max2Idx = 0;
    }
    else
    {
      notTerminated = false;
    }


  } // END while notTerminated

}

// ==================================================
// NUMBER OF 4-CONNECTED COMPONENTS IN A NEIGHBORHOOD
// ==================================================

int
crossingCnt(GreyLevelImage::value_type aNghb[])
{
  int c4 = 0;

  for(int idx = 1 ; idx <= 8 ; ++idx)
  {
    c4 += std::abs(aNghb[idx + 1] - aNghb[idx]);
  }

  return (c4 /= 2);
}

// ======================================================
// REDUCE TO UNIT WIDTH
// ======================================================
//
// Erase marker from any marked pixel satisfying both:
// - at least one odd-neighbor is not marked,
// - at least a triplet of neighbors (nk, nk+2, nk+5)
//   (k odd, addition modulo 8) exists such that
//   nk and nk+2 are marked, with nk+5 not marked
//
//  pMarkerMap : the pixel p we check
//  pMarkerMap : the neighborhood of p (markers)
//
// ======================================================

void
unitWidth(GreyLevelImage::pointer pMarkerMap,
          GreyLevelImage::value_type aMarkers[])
{

  if (aMarkers[N1] == SKELETON_UNMARKED_PIXEL)
  {
    if (aMarkers[N3] == SKELETON_UNMARKED_PIXEL)
    {
      if (aMarkers[N5] != SKELETON_UNMARKED_PIXEL)
      {
        if (aMarkers[N7] != SKELETON_UNMARKED_PIXEL)
        {
          if (aMarkers[N2] == SKELETON_UNMARKED_PIXEL)
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
    }
    else
    {
      if (aMarkers[N5] != SKELETON_UNMARKED_PIXEL)
      {
        if (aMarkers[N7] == SKELETON_UNMARKED_PIXEL)
        {
          if (aMarkers[N8] == SKELETON_UNMARKED_PIXEL)
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
        else
        {
          if ((aMarkers[N8] == SKELETON_UNMARKED_PIXEL) ||
              (aMarkers[N2] == SKELETON_UNMARKED_PIXEL))
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
    }
  }
  else
  {
    if (aMarkers[N3] == SKELETON_UNMARKED_PIXEL)
    {
      if (aMarkers[N5] == SKELETON_UNMARKED_PIXEL)
      {
        if (aMarkers[N7] != SKELETON_UNMARKED_PIXEL)
        {
          if (aMarkers[N4] == SKELETON_UNMARKED_PIXEL)
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
      else
      {
        if (aMarkers[N7] != SKELETON_UNMARKED_PIXEL)
        {
          if ((aMarkers[N4] == SKELETON_UNMARKED_PIXEL) ||
              (aMarkers[N2] == SKELETON_UNMARKED_PIXEL))
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
    }
    else
    {
      if (aMarkers[N5] == SKELETON_UNMARKED_PIXEL)
      {
        if (aMarkers[N7] == SKELETON_UNMARKED_PIXEL)
        {
          if (aMarkers[N6] == SKELETON_UNMARKED_PIXEL)
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
        else
        {
          if ((aMarkers[N6] == SKELETON_UNMARKED_PIXEL) ||
              (aMarkers[N4] == SKELETON_UNMARKED_PIXEL))
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
      else
      {
        if (aMarkers[N7] == SKELETON_UNMARKED_PIXEL)
        {
          if ((aMarkers[N6] == SKELETON_UNMARKED_PIXEL) ||
              (aMarkers[N8] == SKELETON_UNMARKED_PIXEL))
          {
            *pMarkerMap = SKELETON_UNMARKED_PIXEL;
          }
        }
      }
    }
  }
}

// ===============================================================
// STORE THE BINARY IMAGE OF A NEIGHBORHOOD IN A TABLE
// ===============================================================
//
// pMarkerMap : the markers of a labeled image
// pNBin : the binary image of a neighborhood (table)
//
// pMarkerMap initially points on a pixel p
//
// We compute the binary image of the neighborhood of the pixel p
// in pNBin according to the skeletal pixels (marked pixels)
//
// ===============================================================

void
StoreBinaryImageOfANeighborhoodFromAMarkerMap(GreyLevelImage::value_type pMarkerMap[], GreyLevelImage::value_type pNBin[], int aWidth)
{

  //local constants
  GreyLevelImage::pointer QGL_UP    = pMarkerMap - aWidth;
  GreyLevelImage::pointer QGL_DOWN  = pMarkerMap + aWidth;
  GreyLevelImage::pointer QGL_LEFT  = pMarkerMap - 1;
  GreyLevelImage::pointer QGL_RIGHT = pMarkerMap + 1;

  //used for the value of n1 (n9 == n1)
  GreyLevelImage::value_type n1;


  //N0
  *pNBin = (*pMarkerMap == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N1
  ++pNBin;
  n1 = (*(QGL_LEFT) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;
  *pNBin = n1;

  //N2
  ++pNBin;
  *pNBin = (*(QGL_UP - 1) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N3
  ++pNBin;
  *pNBin = (*(QGL_UP) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;


  //N4
  ++pNBin;
  *pNBin = (*(QGL_UP + 1) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N5
  ++pNBin;
  *pNBin = (*(QGL_RIGHT) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N6
  ++pNBin;
  *pNBin = (*(QGL_DOWN + 1) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N7
  ++pNBin;
  *pNBin = (*(QGL_DOWN) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N8
  ++pNBin;
  *pNBin = (*(QGL_DOWN - 1) == SKELETON_UNMARKED_PIXEL) ? 0 : 1;

  //N9
  ++pNBin;
  *pNBin = n1;  // n[9] == n[1]
}

// ===================================================
// DEGREE OF A POINT: ITS NUMBER OF MARKED NEIGHBORS
// ===================================================

int
degree(GreyLevelImage::value_type pMarkerMap[], int aWidth)
{

  //local constants
  GreyLevelImage::pointer QGL_UP    = pMarkerMap - aWidth;
  GreyLevelImage::pointer QGL_DOWN  = pMarkerMap + aWidth;
  GreyLevelImage::pointer QGL_LEFT  = pMarkerMap - 1;
  GreyLevelImage::pointer QGL_RIGHT = pMarkerMap + 1;

  int deg = 0;

  //N1 if marked ?

  if(*(QGL_LEFT) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N2 if marked ?
  if(*(QGL_UP - 1) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N3 if marked ?
  if(*(QGL_UP) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N4 if marked ?
  if(*(QGL_UP + 1) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N5 if marked ?
  if(*(QGL_RIGHT) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N6 if marked ?
  if(*(QGL_DOWN + 1) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N7 if marked ?
  if(*(QGL_DOWN) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  //N8 if marked ?
  if(*(QGL_DOWN - 1) != SKELETON_UNMARKED_PIXEL)
  {
    ++deg;
  }

  return deg;
}

// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
// E N D   O F   L O C A L S
//
// LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL


// -------------------------------------------------------------------
// C O N S T R U C T O R
// -------------------------------------------------------------------


LabeledSkeletonImage::LabeledSkeletonImage(const Dist34BlackCCImage& img,
    int maxPruning)

    : GreyLevelImage(img)

{

  //Local constants
  const int QGL_WIDTH_MINUS_1  = _width - 1;
  const int QGL_WIDTH_PLUS_1   = _width + 1;
  const int QGL_HEIGHT_MINUS_1 = _height - 1;
  const int QGL_SIZE           = _width * _height;

  // _________________________________________________________________
  //
  //  [1] INITIALIZE A TEMPORARY PIXEL MAP TO UNMARKED PIXEL
  //
  //  In this map, all the marked pixel are skeletal pixels
  // _________________________________________________________________


  _pPixMap2 = new GreyLevelImage::value_type[QGL_SIZE];
  qgFill(_pPixMap2, QGL_SIZE, SKELETON_UNMARKED_PIXEL);

  // _________________________________________________________________
  //
  //  [2] FIND PARALLELWISE DETECTABLE SKELETON PIXELS
  //      AND SEQUENTIALLY DETECTABLE SKELETON PIXELS
  //
  //  In the parallelwise detection, we find the maximal centers and
  //  the saddle pixels.They both belong to the skeletal and can be
  //  directly identified due to the structure of their neighborhood.
  //
  //  Whenever a pixel is marked as a parallelwise
  //  detectable skeletal pixel, the raster scan inspection is
  //  temporarily interrupted to check wether a connecting path can be
  //  grown (sequentially detectable skeleton pixels).
  //  The raster inspection is resumed after the path has been
  //  completly build." (see referenced article pg 112)
  //
  // _________________________________________________________________


  GreyLevelImage::value_type labels[10];
  GreyLevelImage::value_type suitbin[10];

  for (int iCnt = 1 ; iCnt < QGL_HEIGHT_MINUS_1 ; ++iCnt)
  {

    int offset = (iCnt * _width) + 1;
    GreyLevelImage::pointer pLabeledImg = _pPixMap + offset;
    GreyLevelImage::pointer pMarkerMap = _pPixMap2 + offset;

    for(int jCnt = 1 ; jCnt < QGL_WIDTH_MINUS_1 ; ++jCnt, ++pMarkerMap, ++pLabeledImg)
    {
      // the value of the current marker in the MarkerMap
      GreyLevelImage::value_type currentMarker = *pMarkerMap;

      if (*pLabeledImg != BACKGROUND_PIXEL) // Not background pixel
      {

        StoreUpdatedLabeledNeighborsFromALabeledImg(pLabeledImg, labels, _width);

        //Updated label of the current pixel
        GreyLevelPixel oglp = updateLabel(pLabeledImg);

        //Updated label of the current pixel plus a vertical/horizontal unit move
        GreyLevelPixel oglp3 = oglp + LENGTH_HV_UNIT_MOVE;

        //Updated label of the current pixel plus a diagonal unit move
        GreyLevelPixel oglp4 = oglp + LENGTH_DIAG_UNIT_MOVE;

        // --------------------------------------------------------------------------
        // Check if the current pixel is a maximal center :
        //
        // A pixel p on the (3,4)-DT is a maximal center if (with updated labels) :
        //         ni < p + 3 for every odd-neighbor ni
        //         ni < p+4 for every even-neighbor ni
        // --------------------------------------------------------------------------

        if ((labels[N2] < oglp4) && (labels[N3] < oglp3) &&
            (labels[N4] < oglp4) && (labels[N1] < oglp3) &&
            (labels[N5] < oglp3) && (labels[N6] < oglp4) &&
            (labels[N7] < oglp3) && (labels[N8] < oglp4))
        {

          //-------------------------------------------------------------
          // Any maximal center having a triple of consecutive neighbors
          // odd/even/odd which are all labeled more than it is not
          // marked (the sucessive reduction to unit width of the set of
          // the skeletal pixels is facilitated)
          //-------------------------------------------------------------

          if (!((labels[N1] > oglp)&&(((labels[N2] > oglp) && (labels[N3] > oglp)) || ((labels[N7] > oglp) && (labels[N8] > oglp))) ||
                (labels[N5] > oglp)&&(((labels[N4] > oglp) && (labels[N3] > oglp)) || ((labels[N7] > oglp) && (labels[N6] > oglp)))))
          {

            // We have a maximal center to mark
            // (if it is not already marked as sequentially detectable pixel to avoid
            // multiple detection of the same connecting path)

            if (currentMarker != SKELETON_SEQUENTIALLY_PIXEL)
            {
              *pMarkerMap = SKELETON_PARALLELWISE_PIXEL;

              //find sequentially detectable skeleton pixels from the current marked pixel
              findSequentiallyDetectableSkeletonPixels(pLabeledImg, pMarkerMap, _width);
            }
          }
        }
        else
        {
          //-------------------------------------------------------------------------
          // For any pixel p which is not a maximal center, we have a saddle pixel
          // if any of the following conditions holds :
          //
          //  - (i) In N(p) there is more than one 8-connected component of pixels
          //        labeled more than p
          //
          //  - (ii) In N(p) there is more than one 4-connected component of pixels
          //         labeles less than p
          //
          // For any pixel p labeled 3 the following additional condition is checked :
          //
          //  - (iii) In N(p) there exists a triple of consecutive neighbors of p
          //          (odd/even/odd) which are all labeled 3
          //
          // The 8-connected components and the 4-connected components of black pixels
          // in N(p) are counted by the connectivity number and by the crossing number
          //
          //---------------------------------------------------------------------------

          // .........................................................................
          // we compute the number of 8-connected components in a neighborhood
          // using a suitable binary version of N(p)
          // .........................................................................
          //
          // (a) Binarize the neighborhood :
          //     labels  : the neighborhood of a pixel p
          //     suitbin : the suitable binary neighborhood computed from labels
          //
          //     suitbin[i] = 1 for each neighbor higher than p
          //     suitbin[i] = 0 for the other
          // .........................................................................

          for (int idx = 1 ; idx < 10 ; ++idx)
          {
            if((labels[idx] > labels[0]))
            {
              suitbin[idx] = 1;
            }
            else
            {
              suitbin[idx] = 0;
            }
          }

          // .........................................................................
          // (b) Compute the number of 8-connected components
          // .........................................................................

          int c8 = 0;

          for (int idx = 1 ; idx <= 4 ; ++idx)
          {
            int idx2 = 2 * idx;
            int tmp = 1 - suitbin[idx2 - 1];
            c8 += tmp - (tmp * (1 - suitbin[idx2]) * (1 - suitbin[idx2 + 1]));
          }

          // .........................................................................
          // we compute the number of 4-connected components in a neighborhood
          // using a suitable X binary version of N(p)
          // .........................................................................
          //
          // (a) get a X suitable binary neighborhood :
          //     labels : a neighborhood of a pixel p (labels)
          //     suitbin : a suitable X binary neighborhood computed from labels
          //
          //     suitbin[i] = 1 for each neighbor lower than p
          //     suitbin[i] = 0 for the other
          // .........................................................................

          for (int idx = 1 ; idx < 10 ; ++idx)
          {
            if ((labels[idx] < labels[0]))
            {
              suitbin[idx] = 1;
            }
            else
            {
              suitbin[idx] = 0;
            }
          }

          // .........................................................................
          //compute the number of 4-connected components
          // .........................................................................

          int x4 = crossingCnt(suitbin);


          if (updateLabel(pLabeledImg) != LABEL_1)
          {
            // .........................................................................
            //  The current pixel on the labeled image is not labeled 3
            // (remember that here we have updated labels : 3 --> 1)
            //  therefore, we only check the conditions (i) and (ii)
            // .........................................................................

            if ((c8 > 1) || (x4 > 1))
            {

              // We have a saddle pixel to mark
              // (if it is not already marked as sequentially detectable pixel to avoid
              // multiple detection of the same connecting path)

              if (currentMarker != SKELETON_SEQUENTIALLY_PIXEL)
              {
                *pMarkerMap = SKELETON_PARALLELWISE_PIXEL;

                //find sequentially detectable skeleton pixels from the current marked pixel
                findSequentiallyDetectableSkeletonPixels(pLabeledImg, pMarkerMap, _width);
              }
            }

          }
          else
          {
            // .........................................................................
            //  The current pixel on the labeled image is labeled 3
            // (remember that here we have updated labels : 3 --> 1)
            //  Therefore, we check the conditions (i), (ii) and (iii)
            // .........................................................................

            if ((c8 > 1) || (x4 > 1) ||
                ((labels[N1] + labels[N2] +labels[N3]) == 3) ||
                ((labels[N3] + labels[N4] +labels[N5]) == 3) ||
                ((labels[N5] + labels[N6] +labels[N7]) == 3) ||
                ((labels[N7] + labels[N8] +labels[N1]) == 3))
            {

              // We have a saddle pixel to mark
              // (if it is not already marked as sequentially detectable pixel to avoid
              // multiple detection of the same connecting path)

              if (currentMarker != SKELETON_SEQUENTIALLY_PIXEL)
              {
                *pMarkerMap = SKELETON_PARALLELWISE_PIXEL;

                //find sequentially detectable skeleton pixels from the current marked pixel
                findSequentiallyDetectableSkeletonPixels(pLabeledImg, pMarkerMap, _width);
              }
            }
          }
        }

      }

    } // END for jCnt

  } // END for iCnt


  // _________________________________________________________________
  //
  //  [3] HOLE FILLING AND FINAL THINNING
  //
  //  (1) Reduction to unit width of the set of skeletal pixels
  //
  //  (2) Any nonmarked pixel p whose odd-neighbors are recognized as
  //      a spurious hole is marked. In this case, marking p could make
  //      it possible to remove the marker from some of its ALREADY
  //      inspected odd_neighbors (with unit with).
  //
  // _________________________________________________________________


  // Markers of a neighborhood
  GreyLevelImage::value_type markers[10];

  for (int iCnt = 1 ; iCnt < QGL_HEIGHT_MINUS_1 ; ++iCnt)
  {
    GreyLevelImage::pointer pMarkerMap = _pPixMap2 + (iCnt * _width) + 1;

    for (int jCnt = 1 ; jCnt < QGL_WIDTH_MINUS_1 ; ++jCnt, ++pMarkerMap)
    {
      if (*pMarkerMap != SKELETON_UNMARKED_PIXEL)
      {
        // marked pixel : reduce to unit width

        //we store the markers of the neighborhood in the table markers
        StoreNeighborsFromAMap(pMarkerMap, markers, _width);

        //reduce to unit width
        unitWidth(pMarkerMap, markers);
      }
      else
      {

        // not a marked pixel : we detect and fill holes

        if ((*(pMarkerMap - 1)      != SKELETON_UNMARKED_PIXEL) &&
            (*(pMarkerMap - _width) != SKELETON_UNMARKED_PIXEL) &&
            (*(pMarkerMap + 1)      != SKELETON_UNMARKED_PIXEL) &&
            (*(pMarkerMap + _width) != SKELETON_UNMARKED_PIXEL))
        {
          // Fill the hole
          *pMarkerMap = SKELETON_MARKER;

          // check again ALREADY inspected odd-neighbors to see
          // if we can remove marker with unit width

          GreyLevelImage::pointer pTmpMarkerMap = pMarkerMap;

          --pTmpMarkerMap;
          StoreNeighborsFromAMap(pTmpMarkerMap, markers, _width);
          unitWidth(pTmpMarkerMap, markers);

          pTmpMarkerMap = pMarkerMap - _width;
          StoreNeighborsFromAMap(pTmpMarkerMap, markers, _width);
          unitWidth(pTmpMarkerMap, markers);
        }
      }
    } // END for jCnt
  } // END for iCnt


  // _________________________________________________________________
  //
  //  [4] PRUNING
  //
  //  Pruning is done by erasing the marker from the pixels of a
  //  branch, which is not significant in the problem domain.
  //
  //  We find the end points computing the crossing number.
  //  For each end point, we identify the most internal pixel up to
  //  which pruning can be done.
  //
  // _________________________________________________________________


  // the set of pixels to be pruned
  vector<GreyLevelImage::pointer> pruneVector;

  // a neighborhood
  GreyLevelImage::value_type neighbors[10];

  // If pruning is requested
  if (maxPruning > 0)
  {

    for (int iCnt = 1 ; iCnt < QGL_HEIGHT_MINUS_1 ; ++iCnt)
    {
      int offset = (iCnt * _width);
      GreyLevelImage::pointer pLabeledImg = _pPixMap  + offset + 1;
      GreyLevelImage::pointer pMarkerMap  = _pPixMap2 + offset + 1;

      for (int jCnt = 1 ; jCnt < QGL_WIDTH_MINUS_1 ; ++jCnt, ++pMarkerMap, ++pLabeledImg)
      {
        if(*pMarkerMap != SKELETON_UNMARKED_PIXEL) // marked pixel
        {
          //...........................................................
          // we have a marked pixel, we compute the crossing number
          //...........................................................

          StoreBinaryImageOfANeighborhoodFromAMarkerMap(pMarkerMap, neighbors, _width);
          int x4=crossingCnt(neighbors);

          if(x4 == 1)
          {
            //...........................................................
            // we have an end point
            //...........................................................

            GreyLevelImage::value_type binaryNeighbors[10];

            // Put start pointers on right position
            GreyLevelImage::pointer pLabeledImgStart    =  pLabeledImg;
            GreyLevelImage::pointer pMarkerMapStart     =  pMarkerMap;

            // Put current pointers on right position
            GreyLevelImage::pointer pLabeledImgCurrent = pLabeledImgStart;
            GreyLevelImage::pointer pMarkerMapCurrent  = pMarkerMapStart;

            // Where do we go from here?
            int nextLocation = 0;

            // (3,4) distance between start point and current point
            int d34 = 0;

            // Points of a potential pruning branch
            vector<GreyLevelImage::pointer> possiblePointsToBePruned;

            // Can we go on?
            bool canContinue = true;

            // Can we prune?
            bool canPrune = true;

            // The location we come from
            int from = 0;

            //......................................................................
            // we identify the most internal pixel up to which pruning can be done.
            //......................................................................

            while (canContinue)
            {
              //......................................................................
              // Find where we are going, without going back to where we came from
              // We choose a marked pixel in the neighborhood
              //......................................................................

              nextLocation = 0;
              StoreBinaryImageOfANeighborhoodFromAMarkerMap(pMarkerMapCurrent, binaryNeighbors, _width);

              for (int k = 1 ; (k < 9) && (nextLocation == 0) ; ++k)
              {
                if ((binaryNeighbors[k] != 0) && (k != from))
                {
                  nextLocation = k;
                }
              }

              //.............................................................................
              // We go to the next point we found previously :
              //    we updated the pointers, the pixel we come from, and the (3,4) distance
              //    between the end point and the current point
              //.............................................................................

              switch (nextLocation)
              {

                case N1:
                --pLabeledImgCurrent;
                --pMarkerMapCurrent;
                d34 += LENGTH_HV_UNIT_MOVE;
                from = N5;
                break;

                case N2:
                pLabeledImgCurrent -= QGL_WIDTH_PLUS_1;
                pMarkerMapCurrent  -= QGL_WIDTH_PLUS_1;
                d34 += LENGTH_DIAG_UNIT_MOVE;
                from = N6;
                break;

                case N3:
                pLabeledImgCurrent -= _width;
                pMarkerMapCurrent  -= _width;
                d34 += LENGTH_HV_UNIT_MOVE;
                from = N7;
                break;

                case N4:
                pLabeledImgCurrent -= QGL_WIDTH_MINUS_1;
                pMarkerMapCurrent  -= QGL_WIDTH_MINUS_1;
                d34 += LENGTH_DIAG_UNIT_MOVE;
                from = N8;
                break;

                case N5:
                ++pLabeledImgCurrent;
                ++pMarkerMapCurrent;
                d34 += LENGTH_HV_UNIT_MOVE;
                from = N1;
                break;

                case N6:
                pLabeledImgCurrent += QGL_WIDTH_PLUS_1;
                pMarkerMapCurrent  += QGL_WIDTH_PLUS_1;
                d34 += LENGTH_DIAG_UNIT_MOVE;
                from = N2;
                break;

                case N7:
                pLabeledImgCurrent += _width;
                pMarkerMapCurrent  += _width;
                d34 += LENGTH_HV_UNIT_MOVE;
                from = N3;
                break;

                case N8:
                pLabeledImgCurrent += QGL_WIDTH_MINUS_1;
                pMarkerMapCurrent  += QGL_WIDTH_MINUS_1;
                d34 += LENGTH_DIAG_UNIT_MOVE;
                from = N4;
                break;

                default:
                ostringstream os;
                os << "Bad location: "
                << nextLocation;
                throw QgarErrorDeveloper(__FILE__, __LINE__,
                                         "qgar::LabeledSkeletonImage:LabeledSkeletonImage(const Dist34BlackCCImage&, int)",
                                         os.str());
                break;
              }

              //.........................................................................
              // Let p be the end point delimiting a skeleton branch
              // The pruning condition is checked for any pixel q labeled more than p.
              // For the pixels q labeled less than p, we can also check the pruning
              // condition if they belong to the same layer as p.
              //.........................................................................


              // if pruning condition does hold, start a pruning process
              if (((*pLabeledImgCurrent > *pLabeledImgStart) || // labeled more than startig point
                   (((*pLabeledImgCurrent + 2)/3) == ((*pLabeledImgStart +2)/3))) && // or same layer
                  ((*pLabeledImgStart - *pLabeledImgCurrent + d34) <= 3 * maxPruning)) //pruning condition
              {

                // The starting/previous point can be pruned
                possiblePointsToBePruned.push_back(pMarkerMapStart);

                // compute degree of current point (number of non-marked pixel)
                int deg = degree(pMarkerMapCurrent, _width);

                if (deg > 2)
                {
                  // we have reach the most internal pixel up to which pruning can be done.
                  canContinue = false;
                }
                else if (deg < 2) // Do not prune, we have come to an end
                {
                  canContinue = false;
                  canPrune = false;
                }
                else // with deg == 2, we continue the tracing
                {
                  // Save position from which we are
                  pMarkerMapStart = pMarkerMapCurrent;
                }

              }
              else
              {
                // if pruning condition does not hold, forget it
                canContinue = false;
                canPrune = false;
              }
            }



            if (canPrune)
            {
              // we actually can prune these points
              pruneVector.insert(pruneVector.end(),
                                 possiblePointsToBePruned.begin(),
                                 possiblePointsToBePruned.end());
            }

          }

        }
      } // END for j
    } // END for i



    // Now we have found all that can be pruned
    // Remove the corresponding points from

    vector<GreyLevelImage::pointer>::iterator iterPoints =
      pruneVector.begin();

    while (iterPoints != pruneVector.end())
    {
      *(*iterPoints) = SKELETON_UNMARKED_PIXEL;
      ++iterPoints;
    }

  }

  // _________________________________________________________________
  //
  //  [5] REMOVE JAGGEDNESS
  //
  //  To reduce skeleton jaggedness, the marker is shifted from a
  //  pixel p to one of its neigbors q if the following conditions
  //  are satified :
  //
  //  - p has exactly two neighbors, nk and nk+2 (k even addition
  //    modulo 8), in the skeletal
  //
  //  - q is the odd-neighbor nk+1 of p
  //
  // As noted by Sanniti di Baja in her article, we may want to make
  // this condition more strict, by allowing the shift only if the
  // resulting marked pixel belongs to the set of skeletal pixels
  // identified during the process. This would need a special marking
  // for those pixels.
  // I think this is not necessary, but let us keep it in mind. (KT)
  //
  // _________________________________________________________________


  for (int iCnt = 1 ; iCnt < QGL_HEIGHT_MINUS_1 ; ++iCnt)
  {
    int offset = (iCnt * _width) + 1;
    GreyLevelImage::pointer pMarkedMap  = _pPixMap2 +  offset;
    GreyLevelImage::pointer pLabeledImg = _pPixMap  + offset;

    for(int jCnt = 1 ; jCnt < QGL_WIDTH_MINUS_1 ; ++jCnt, ++pMarkedMap, ++pLabeledImg)
    {
      if ((*pMarkedMap != SKELETON_UNMARKED_PIXEL) && (degree(pMarkedMap, _width) == 2))
      {
        //...............................................
        // p has exactly two neighbors in the skeletal
        //...............................................

        StoreNeighborsFromAMap(pMarkedMap, neighbors, _width);

        if ((neighbors[N2] != SKELETON_UNMARKED_PIXEL) &&
            (neighbors[N4] != SKELETON_UNMARKED_PIXEL))
        {
          *pMarkedMap            = SKELETON_UNMARKED_PIXEL;
          *(pMarkedMap - _width) = SKELETON_MARKER;
        }
        else if ((neighbors[N4] != SKELETON_UNMARKED_PIXEL) &&
                 (neighbors[N6] != SKELETON_UNMARKED_PIXEL))
        {
          *pMarkedMap       = SKELETON_UNMARKED_PIXEL;
          *(pMarkedMap + 1) = SKELETON_MARKER;
        }
        else if ((neighbors[N6] != SKELETON_UNMARKED_PIXEL) &&
                 (neighbors[N8] != SKELETON_UNMARKED_PIXEL))
        {
          *pMarkedMap            = SKELETON_UNMARKED_PIXEL;
          *(pMarkedMap + _width) = SKELETON_MARKER;
        }

        else if ((neighbors[N8] != SKELETON_UNMARKED_PIXEL) &&
                 (neighbors[N2] != SKELETON_UNMARKED_PIXEL))
        {
          *pMarkedMap       = SKELETON_UNMARKED_PIXEL;
          *(pMarkedMap - 1) = SKELETON_MARKER;
        }

      } // END if
    } // END for j
  } // END for i

  // _________________________________________________________________
  //
  //  [6] UPDATE THE LABELED IMAGE
  //
  //      And now that we have marked everything, we create the
  //      labeled skeleton by setting to zero all non-skeletal pixels
  //      in original distance image
  // _________________________________________________________________

  GreyLevelImage::pointer pLabeledImg = _pPixMap;
  GreyLevelImage::pointer pMarkerMap  = _pPixMap2;

  for (int iCnt = 0 ; iCnt < QGL_SIZE ; ++iCnt, ++pLabeledImg, ++pMarkerMap)
  {
    if ((*pLabeledImg != BACKGROUND_PIXEL) && (*pMarkerMap == SKELETON_UNMARKED_PIXEL))
    {
      *pLabeledImg = BACKGROUND_PIXEL;
    }
  }
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

LabeledSkeletonImage::~LabeledSkeletonImage()
{
  if (_pPixMap2 != NULL)
  {
    delete [] _pPixMap2;
  }
}

// -------------------------------------------------------------------

} // namespace qgar
