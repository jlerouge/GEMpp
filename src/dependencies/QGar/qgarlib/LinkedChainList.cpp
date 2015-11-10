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
 * @file LinkedChainList.cpp
 *
 * @brief Implementation of class qgar::LinkedChainList.
 *
 * See file LinkedChainList.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Karl Tombre">Karl Tombre</a>
 * @date   July 3,  2001  16:14
 * @since  Qgar 1.0
 */



// STD
#include <string>
// STL
#include <algorithm>
#include <cstdlib>
// QGAR
#include "GenPointChain.h"
#include "LabeledSkeletonImage.h"
#include "LinkedChainList.h"
#include "QgarErrorDeveloper.h"



using namespace std;


namespace qgar
{

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // L O C A L    D A T A
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    // The mark
    const unsigned char LINKEDCHAINLIST_MARK = 2;

    // For the checking
    static int LINKEDCHAINLIST_MINL = 0;


    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // L O C A L    I N L I N E S
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Is this dangerous?
    // Do comparisons always return 1 or 0?

    int
    LINKEDCHAINLIST_connect4(unsigned char* p, int w)
    {
        return   (*(p - w) == 255)
                + (*(p + w) == 255)
                + (*(p - 1) == 255)
                + (*(p + 1) == 255);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int
    LINKEDCHAINLIST_connect4M(unsigned char* p, int w)
    {
        return   (*(p - w) == LINKEDCHAINLIST_MARK)
                + (*(p + w) == LINKEDCHAINLIST_MARK)
                + (*(p - 1) == LINKEDCHAINLIST_MARK)
                + (*(p + 1) == LINKEDCHAINLIST_MARK);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int
    LINKEDCHAINLIST_connect8(unsigned char* p, int w)
    {
        return   (*(p - w - 1) == 255)
                + (*(p - w + 1) == 255)
                + (*(p + w - 1) == 255)
                + (*(p + w + 1) == 255);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int
    LINKEDCHAINLIST_connect8M(unsigned char* p, int w)
    {
        return   (*(p - w - 1) == LINKEDCHAINLIST_MARK)
                + (*(p - w + 1) == LINKEDCHAINLIST_MARK)
                + (*(p + w - 1) == LINKEDCHAINLIST_MARK)
                + (*(p + w + 1) == LINKEDCHAINLIST_MARK);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neigh(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + 1) == 255)
        {
            x += 1;
        }
        else if (*(p + w) == 255)
        {
            y += 1;
        }
        else if (*(p - 1) == 255)
        {
            x -= 1;
        }
        else if (*(p - w) == 255)
        {
            y -= 1;
        }
        else if (*(p + w + 1) == 255)
        {
            x += 1;
            y += 1;
        }
        else if (*(p + w - 1) == 255)
        {
            x -= 1;
            y += 1;
        }
        else if (*(p - w - 1) == 255)
        {
            x -= 1;
            y -= 1;
        }
        else if (*(p - w + 1) == 255)
        {
            x += 1;
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Get any non null neighbor

    Point
    LINKEDCHAINLIST_neighPlus(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + 1) != 0)
        {
            x += 1;
        }
        else if (*(p + w) != 0)
        {
            y += 1;
        }
        else if (*(p - 1) != 0)
        {
            x -= 1;
        }
        else if (*(p - w) != 0)
        {
            y -= 1;
        }
        else if (*(p + w + 1) != 0)
        {
            x += 1;
            y += 1;
        }
        else if (*(p + w - 1) != 0)
        {
            x -= 1;
            y += 1;
        }
        else if (*(p - w - 1) != 0)
        {
            x -= 1;
            y -= 1;
        }
        else if (*(p - w + 1) != 0)
        {
            x += 1;
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neigh4(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + 1) == 255)
        {
            x += 1;
        }
        else if (*(p + w) == 255)
        {
            y += 1;
        }
        else if (*(p - 1) == 255)
        {
            x -= 1;
        }
        else if (*(p - w) == 255)
        {
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neigh8(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + w + 1) == 255)
        {
            x += 1;
            y += 1;
        }
        else if (*(p + w - 1) == 255)
        {
            x -= 1;
            y += 1;
        }
        else if (*(p - w - 1) == 255)
        {
            x -= 1;
            y -= 1;
        }
        else if (*(p - w + 1) == 255)
        {
            x += 1;
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neighM(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
        }
        else if (*(p + w) == LINKEDCHAINLIST_MARK)
        {
            y += 1;
        }
        else if (*(p - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
        }
        else if (*(p - w) == LINKEDCHAINLIST_MARK)
        {
            y -= 1;
        }
        else if (*(p + w + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
            y += 1;
        }
        else if (*(p + w - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
            y += 1;
        }
        else if (*(p - w - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
            y -= 1;
        }
        else if (*(p - w + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neigh4M(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
        }
        else if (*(p + w) == LINKEDCHAINLIST_MARK)
        {
            y += 1;
        }
        else if (*(p - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
        }
        else if (*(p - w) == LINKEDCHAINLIST_MARK)
        {
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Point
    LINKEDCHAINLIST_neigh8M(unsigned char* p, int l, int c, int w)
    {
        int x = c;
        int y = l;

        if (*(p + w + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
            y += 1;
        }
        else if (*(p + w - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
            y += 1;
        }
        else if (*(p - w - 1) == LINKEDCHAINLIST_MARK)
        {
            x -= 1;
            y -= 1;
        }
        else if (*(p - w + 1) == LINKEDCHAINLIST_MARK)
        {
            x += 1;
            y -= 1;
        }
        //  else
        //    {
        //      // do nothing
        //    }

        return Point(x,y);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    void
    LINKEDCHAINLIST_markNeigh(unsigned char* p, int w, int c4, int c8)
    {
        if (c4 != 0 && c8 == 0)   // Only 4-neighbors: mark 4-neighbors
        {

            if (*(p + 1) != 0)
            {
                *(p + 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p + w) != 0)
            {
                *(p + w) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - 1) != 0)
            {
                *(p - 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - w) != 0)
            {
                *(p - w) = LINKEDCHAINLIST_MARK;
            }
        }
        else if (c4 == 0 && c8 != 0) // Only 8-neighbors: mark 8-neighbors
        {

            if (*(p + w + 1) != 0)
            {
                *(p + w + 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p + w - 1) != 0)
            {
                *(p + w - 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - w - 1) != 0)
            {
                *(p - w - 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - w + 1) != 0)
            {
                *(p - w + 1) = LINKEDCHAINLIST_MARK;
            }
        }
        else // there are both 4- and 8-neighbors
        {
            // mark 4-neighbors

            if (*(p + 1) != 0)
            {
                *(p + 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p + w) != 0)
            {
                *(p + w) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - 1) != 0)
            {
                *(p - 1) = LINKEDCHAINLIST_MARK;
            }

            if (*(p - w) != 0)
            {
                *(p - w) = LINKEDCHAINLIST_MARK;
            }

            // and mark others which have no connected path
            if ((*(p + w + 1) != 0) && (*(p + 1) == 0) && (*(p + w) == 0))
            {
                *(p + w + 1) = LINKEDCHAINLIST_MARK;
            }

            if ((*(p + w - 1) != 0) && (*(p + w) == 0) && (*(p - 1) == 0))
            {
                *(p + w - 1) = LINKEDCHAINLIST_MARK;
            }

            if ((*(p - w - 1) != 0) && (*(p - 1) == 0) && (*(p - w) == 0))
            {
                *(p - w - 1) = LINKEDCHAINLIST_MARK;
            }

            if ((*(p - w + 1) != 0) && (*(p - w) == 0) && (*(p + 1) == 0))
            {
                *(p - w + 1) = LINKEDCHAINLIST_MARK;
            }
        }
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int
    LINKEDCHAINLIST_degree(unsigned char* p, int w)
    {
        int d = 0;

        if((*(p-1)) != 0)
        {
            ++d;
        }

        if((*(p-w-1)) != 0)
        {
            ++d;
        }

        if((*(p-w)) != 0)
        {
            ++d;
        }

        if((*(p-w+1)) != 0)
        {
            ++d;
        }

        if((*(p+1)) != 0)
        {
            ++d;
        }

        if((*(p+w+1)) != 0)
        {
            ++d;
        }

        if((*(p+w)) != 0)
        {
            ++d;
        }

        if((*(p+w-1)) != 0)
        {
            ++d;
        }

        return d;
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    void
    LINKEDCHAINLIST_loadBinNeigh(unsigned char* p, unsigned char* n, int w)
    {
        *n = *p ? 1 : 0;
        ++n;
        *n = *(p-1) ? 1 : 0;
        ++n;
        *n = *(p - w - 1) ? 1 : 0;
        ++n;
        *n = *(p - w) ? 1 : 0;
        ++n;
        *n = *(p - w + 1) ? 1 : 0;
        ++n;
        *n = *(p + 1) ? 1 : 0;
        ++n;
        *n = *(p + w + 1) ? 1 : 0;
        ++n;
        *n = *(p + w) ? 1 : 0;
        ++n;
        *n = *(p + w - 1) ? 1 : 0;
        ++n;
        *n = *(p - 1) ? 1 : 0;  // n[9] == n[1]
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int
    LINKEDCHAINLIST_crossNb(unsigned char* n, int w)
    {
        Q_UNUSED(w);
        int x4=0;

        for(int k = 1 ; k <= 8 ; ++k)
        {
            x4 += std::abs(n[k + 1] - n[k]);
        }

        x4 /= 2;

        return x4;
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // To check if a chain is OK

    static bool
    LINKEDCHAINLIST_tooSmall(PointChain& xChain)
    {
        return (xChain.size() < LINKEDCHAINLIST_MINL);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Are two points neighbors?

    bool
    LINKEDCHAINLIST_areNeigh(Point p1, Point p2)
    {
        return    (std::fabs((double)p1.x() - p2.x()) <= 1)
                && (std::fabs((double)p1.y() - p2.y()) <= 1);
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Can two chains merge?

    int
    LINKEDCHAINLIST_canMerge(PointChain& ch1, PointChain& ch2)
    {
        return    LINKEDCHAINLIST_areNeigh(ch1.back(),  ch2.front())
                || LINKEDCHAINLIST_areNeigh(ch1.front(), ch2.back())
                || LINKEDCHAINLIST_areNeigh(ch1.front(), ch2.front())
                || LINKEDCHAINLIST_areNeigh(ch1.back(),  ch2.back());
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    void
    LINKEDCHAINLIST_mergeChains(PointChain& ch1, PointChain& ch2)
    {
        if (LINKEDCHAINLIST_areNeigh(ch1.front(), ch2.front()))
        {
            ch1.reverse();
        }
        else if (LINKEDCHAINLIST_areNeigh(ch1.back(), ch2.back()))
        {
            ch1.reverse();
        }

        if (LINKEDCHAINLIST_areNeigh(ch1.back(), ch2.front()))
        {
            (ch1.pointList()).insert(ch1.pointList().end(),
                                     ch2.pointList().begin(),
                                     ch2.pointList().end());
        }

        // add ch2 after ch1
        else if (LINKEDCHAINLIST_areNeigh(ch1.front(), ch2.back()))
        {
            (ch1.pointList()).insert(ch1.pointList().begin(),
                                     ch2.pointList().begin(),
                                     ch2.pointList().end());
        }

        //  // add ch2 before ch1
        //  else
        //
        //    ;
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // E N D    O F    L O C A L S
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // C O N S T R U C T O R S
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // BUILD FROM GIVEN BINARY IMAGE

    LinkedChainList::LinkedChainList(const BinaryImage& img,
                                     unsigned int minChainLength,
                                     unsigned int minCycleLength)

        : _minChainLength(minChainLength),
          _minCycleLength(minCycleLength)

    {
        // Let us first create a work image with pixel values
        GreyLevelImage wkImg(img);

        // Set the static global variable
        LINKEDCHAINLIST_MINL = minChainLength;

        // Get hold of the pixmap and of height and length
        GreyLevelImage::pointer pixmap = wkImg.pPixMap();
        int width = img.width();
        int height = img.height();

        // Set borders to zero
        GreyLevelImage::pointer p = pixmap;
        for (int i = 0; i < width ; ++i)
        {
            *p = 0;
            ++p;
        }

        p = pixmap;
        for (int i = 0 ; i < height ; ++i, p += width)
        {
            *p = 0;
        }

        p = pixmap + width - 1;
        for (int i = 0 ; i < height ; ++i, p += width)
        {
            *p = 0;
        }

        p = pixmap + (height - 1) * width;
        for (int i = 0 ; i < width ; ++i)
        {
            *p = 0;
            ++p;
        }

        int i;
        // Process the whole image
        for (i = 1, p = pixmap + width + 1 ; i < (height - 1) ; ++i, p += 2)
            for (int j = 1 ; j < (width - 1) ; ++j, ++p)
                if (*p != 0)  // contour point
                {
                    int c4 = LINKEDCHAINLIST_connect4(p, width);
                    int c8 = LINKEDCHAINLIST_connect8(p, width);

                    if ((c4 == 0) && (c8 == 0))
                    {
                        // Isolated point: delete it
                        *p = 0;
                    }
                    else if ((c4 + c8) == 1)
                    {
                        // Single choice: create a chain and follow it
                        PointChain* ch1 = new PointChain;
                        ch1 = aChain(ch1, i, j, wkImg);

                        if (ch1 != 0)
                        {
                            if (ch1->size() < _minChainLength)
                            {
                                delete ch1;
                            }
                            else
                            {
                                push_back(*ch1);   // add to list
                            }
                        }
                    }
                    else
                    {
                        // All other cases
                        // Create a first chain
                        PointChain* ch1 = new PointChain;
                        // Build a first chain
                        ch1 = aChain(ch1, i, j, wkImg);
                        // And if there are still neighbors, build other chains and
                        // merge

                        if ((LINKEDCHAINLIST_connect4(p, width) +
                             LINKEDCHAINLIST_connect8(p, width)) != 0)
                        {
                            // get a neighbor
                            Point v = LINKEDCHAINLIST_neigh(p, i, j, width);
                            PointChain* ch2 = new PointChain;
                            ch2 = aChain(ch2, v.y(), v.x(), wkImg); // chain

                            if ((ch1 != 0) && (ch2 != 0) && LINKEDCHAINLIST_canMerge(*ch1, *ch2))
                            {
                                LINKEDCHAINLIST_mergeChains(*ch1, *ch2);
                                delete ch2;
                            }
                            else if (ch2 != 0)
                            {
                                if(ch2->size() < _minChainLength)
                                {
                                    delete ch2;
                                }
                                else
                                {
                                    push_back(*ch2);   // add to list
                                }
                            }
                        }

                        if (ch1 != 0)
                        {
                            if(ch1->size() < _minChainLength)
                            {
                                delete ch1;
                            }
                            else
                            {
                                push_back(*ch1);   // add to list
                            }
                        }
                    }

                }
    }


    // -------------------------------------------------------------------


    // CONSTRUCT FROM A LABELED SKELETON

    LinkedChainList::LinkedChainList(const LabeledSkeletonImage& skel)



        : _minChainLength(0),
          _minCycleLength(0)

    {
        // Let us first create a work image with pixel values
        GreyLevelImage wkImg(skel);

        // Get hold of the pixmap and of height and length
        GreyLevelImage::pointer pixmap = wkImg.pPixMap();
        int width = skel.width();
        int height = skel.height();

        int i = 0;
        GreyLevelImage::pointer p = pixmap;

        GreyLevelImage::value_type n[10];
        // Mark all points of degree different from 2
        // or of degree equal to 2, but with special configuration

        for (i = 1, p = pixmap + width + 1 ; i < height - 1 ; ++i, p += 2)
            for (int j = 1 ; j < width - 1 ; ++j, ++p)
                if (*p != 0)  // we are on a skeleton point
                {
                    LINKEDCHAINLIST_loadBinNeigh(p, n, width);

                    if (((*(p-width) != 0) && (*(p-width+1) != 0) && (*(p+1) != 0)) ||
                            ((*(p+1) != 0) && (*(p+width+1) != 0) && (*(p+width) != 0)) ||
                            ((*(p+width) != 0) && (*(p+width-1) != 0) && (*(p-1) != 0)) ||
                            ((*(p-1) != 0) && (*(p-width-1) != 0) && (*(p-width) != 0)))
                    {
                        *p = LINKEDCHAINLIST_MARK;  // special square configuration
                    }
                    else if (LINKEDCHAINLIST_crossNb(n, width) == 2)
                    {
                        *p = 255;
                    }
                    else
                    {
                        *p = LINKEDCHAINLIST_MARK;
                    }
                }

        int encore = 1;
        // Now, go through image and chain

        while (encore)
        {
            for (i = 1, p = pixmap + width + 1 ; i < height - 1 ; ++i, p += 2)
                for (int j = 1 ; j < width - 1 ; ++j, ++p)
                    if (*p == LINKEDCHAINLIST_MARK)  // marked point
                    {
                        int d = LINKEDCHAINLIST_degree(p, width);

                        if (d == 0)
                            // Isolated point: delete it
                            *p = 0;
                        else // there are points to follow
                        {
                            // Create the starting point for all the chains
                            Point fPoint(j, i);
                            // Get all its non-null neighbors and mark them as potential
                            // points to follow by decrementing their value by 1
                            list<Point> pList;

                            if(*(p+1) != 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(1, 0);
                                pList.push_back(aPoint);
                                *(p+1) -= 1;
                            }

                            if(*(p+width) != 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(0, 1);
                                pList.push_back(aPoint);
                                *(p+width) -= 1;
                            }

                            if(*(p-1) != 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(-1, 0);
                                pList.push_back(aPoint);
                                *(p-1) -= 1;
                            }

                            if(*(p-width) != 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(0, -1);
                                pList.push_back(aPoint);
                                *(p-width) -= 1;
                            }

                            if(*(p+width+1) != 0 && *(p+1) == 0 && *(p+width) == 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(1, 1);
                                pList.push_back(aPoint);
                                *(p+width+1) -= 1;
                            }

                            if(*(p+width-1) != 0 && *(p+width) == 0 && *(p-1) == 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(-1, 1);
                                pList.push_back(aPoint);
                                *(p+width-1) -= 1;
                            }

                            if(*(p-width-1) !=0 && *(p-1) == 0 && *(p-width) == 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(-1, -1);
                                pList.push_back(aPoint);
                                *(p-width-1) -= 1;
                            }

                            if(*(p-width+1) != 0 && *(p-width) == 0 && *(p+1) == 0)
                            {
                                Point aPoint = fPoint;
                                aPoint.translate(1, -1);
                                pList.push_back(aPoint);
                                *(p-width+1) -= 1;
                            }

                            list<Point>::iterator myIter = pList.begin();

                            while (myIter != pList.end())
                            {
                                Point cPoint = fPoint;
                                // create a chain
                                PointChain* ch = new PointChain;
                                ch->push_back(cPoint); // put the first point in chain
                                // temporarily delete start point so that we do not fall
                                // back to it prematurely
                                *p = 0;
                                // put the second point in the chain
                                cPoint = *myIter;
                                ch->push_back(cPoint);
                                GreyLevelImage::pointer pp = pixmap + cPoint.y() * width + cPoint.x();
                                // If we had removed it at a previous step (loop)
                                // forget the whole thing

                                if (*pp == 0)
                                {
                                    delete ch;
                                    ++myIter;
                                    continue;
                                }

                                // Increment it again
                                *pp += 1;

                                int continueChain = 1;

                                if (*pp == LINKEDCHAINLIST_MARK)
                                    continueChain = 0;
                                else
                                    *pp = 0;

                                while (continueChain)
                                {
                                    int checkLoop = 0;
                                    // try to get a non marked 4-neighbor
                                    Point nPoint = LINKEDCHAINLIST_neigh4(pp, cPoint.y(), cPoint.x(), width);

                                    if (nPoint == cPoint)
                                    { // If I did not find a non-marked 4-neighbor
                                        // try to get a marked 4-neighbor
                                        nPoint = LINKEDCHAINLIST_neigh4M(pp, cPoint.y(), cPoint.x(), width);

                                        if (nPoint == cPoint)
                                        {
                                            // If no marked 4-neighbor, look for a
                                            // non-marked 8-neighbor
                                            nPoint = LINKEDCHAINLIST_neigh8(pp, cPoint.y(),
                                                                            cPoint.x(), width);

                                            if (nPoint == cPoint)
                                            {
                                                // no non-marked, look for marked 8 neighbor
                                                nPoint = LINKEDCHAINLIST_neigh8M(pp,
                                                                                 cPoint.y(),
                                                                                 cPoint.x(),
                                                                                 width);

                                                if (nPoint == cPoint)
                                                    // Nothing found
                                                {
                                                    // get a neighbor (mark decremented)
                                                    nPoint = LINKEDCHAINLIST_neighPlus(pp, cPoint.y(), cPoint.x(), width);

                                                    if (nPoint == cPoint)
                                                    {
                                                        // Nothing found
                                                        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                                                                 "qgar::LinkedChainList::LinkedChainList(const qgar::LabeledSkeletonImage&)",
                                                                                 "Strange things happen: See Karl!");
                                                    }
                                                    else
                                                        checkLoop = 1;

                                                    continueChain = 0;
                                                }
                                                else
                                                    continueChain = 0;
                                            }
                                        }
                                        else
                                            continueChain = 0; // we have a marked 4-neighbor
                                    }

                                    // update current point
                                    cPoint = nPoint;

                                    // add to chain
                                    ch->push_back(cPoint);

                                    // update pointer
                                    pp = pixmap + cPoint.y() * width + cPoint.x();

                                    // if we were on a continuation pixel, delete it
                                    if (continueChain)
                                        *pp = 0;
                                    else if (checkLoop)
                                    {
                                        // We came back to the beginning
                                        // If we are on a marked point, we must stop
                                        // it not we can loop

                                        if (*pp != (LINKEDCHAINLIST_MARK - 1))
                                        {
                                            // add first point to chain again (loop)
                                            ch->push_back(fPoint);
                                            // and set point to zero
                                            *pp = 0;
                                        }
                                    }
                                }

                                // We have ended the chaining.
                                push_back(*ch);   // add to list

                                // restore mark on current pixel
                                *p = LINKEDCHAINLIST_MARK;

                                // get next point to follow
                                ++myIter;
                            }

                            // At end, set point to 0 as it is completely processed
                            *p = 0;
                        }

                    }

            // OK: Do we have perfect loops?
            encore = 0;

            for (i = 1, p = pixmap + width + 1 ;
                 (encore == 0) && (i < height - 1) ;
                 ++i, p += 2)
            {
                for (int j = 1 ; j < width - 1 ; ++j, ++p)
                {
                    if (*p != 0)  // we are on a skeleton point
                    {
                        *p = LINKEDCHAINLIST_MARK;
                        encore = 1;
                        break;
                    }
                }
            }
        }

    }


    // -------------------------------------------------------------------


    // BUILD WITH GIVEN MINIMAL LENGTH PARAMETERS
    //
    // For temporary use!

    LinkedChainList::LinkedChainList(unsigned int minChainLength,
                                     unsigned int minCycleLength)

        : _minChainLength(minChainLength),
          _minCycleLength(minCycleLength)

    {
        // VOID
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // D E S T R U C T O R
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // VIRTUAL DESTRUCTOR
    LinkedChainList::~LinkedChainList()
    {
        erase(begin(), end());
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // P R I V A T E   A U X I L I A R Y   F U N C T I O N S
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // RECURSIVE FUNCTION FOR CHAINING

    PointChain*
    LinkedChainList::aChain(PointChain* ch,
                            int l,
                            int c,
                            GreyLevelImage& wkImg)
    {
        // Get hold of the pixmap and of height and length
        GreyLevelImage::pointer pixmap = wkImg.pPixMap();
        int width = wkImg.width();

        // Possible list of temporary chain
        LinkedChainList tmpList(_minChainLength, _minCycleLength);

        // Add current point to the chain
        Point cPoint(c, l);
        ch->push_back(cPoint);

        // Set the point to zero
        GreyLevelImage::pointer p = pixmap + l * width + c;
        *p = 0;
        int c4 = LINKEDCHAINLIST_connect4(p, width);
        int c8 = LINKEDCHAINLIST_connect8(p, width);

        if ((c4 == 0) && (c8 == 0))
        {
            // if there is a cycle, insert last point

            if ((ch->size() >= _minCycleLength) &&
                    (LINKEDCHAINLIST_connect4M(p, width) == 1) &&
                    (LINKEDCHAINLIST_connect8M(p, width) == 0))
            {
                Point v = LINKEDCHAINLIST_neigh4M(p, l, c, width); // get marked neighbor
                ch->push_back(v);
                *(pixmap + v.y() * width + v.x()) = 0; // set to zero
            }
            else if ((ch->size() >= _minCycleLength) &&
                     (LINKEDCHAINLIST_connect8M(p, width) == 1) &&
                     (LINKEDCHAINLIST_connect4M(p, width) == 0))
            {
                Point v = LINKEDCHAINLIST_neigh8M(p, l, c, width); // get marked neighbor
                ch->push_back(v);
                *(pixmap + v.y() * width + v.x()) = 0; // set to zero
            }

            return ch;
        }

        else if ((c4 + c8) == 1)  // only one choice to continue
        {
            Point v = LINKEDCHAINLIST_neigh(p, l, c, width);  // get continuation
            // recursion
            return aChain(ch, v.y(), v.x(), wkImg);
        }
        else // in all other cases
        {
            LINKEDCHAINLIST_markNeigh(p, width, c4, c8);    // mark the neighbors

            while (LINKEDCHAINLIST_connect4M(p, width) +
                   LINKEDCHAINLIST_connect8M(p, width) != 0)
            {
                // As long as there are unprocessed neighbors
                // create chains and add them to a temporary list
                Point v = LINKEDCHAINLIST_neighM(p, l, c, width);  // get a marked neighbor
                PointChain* tmpch = new PointChain;
                tmpch = aChain(tmpch, v.y(), v.x(), wkImg);

                if (tmpch != 0)
                    tmpList.push_back(*tmpch);
            }

            // Remove from tmpList too small chains
            LinkedChainList::iterator newend =
                    std::remove_if(tmpList.begin(), tmpList.end(), LINKEDCHAINLIST_tooSmall);

            //  remove_if(tmpList.begin(), tmpList.end(), LINKEDCHAINLIST_tooSmall);
            tmpList.erase(newend, tmpList.end());

            // if there is a single remaining chain, see if we can merge with ch
            if (tmpList.size() == 1 && LINKEDCHAINLIST_canMerge(*ch, tmpList.front()))
            {
                PointChain tmpChain = tmpList.front(); // get chain
                tmpList.pop_front();   // remove it from list

                // Merge them
                LINKEDCHAINLIST_mergeChains(*ch, tmpChain);

                // return
                return ch;
            }
            else if (tmpList.size() > 1 && ch->size() == 1) // ch is a single point
            {
                LinkedChainList::iterator tmpIter = tmpList.begin();

                while (tmpIter != tmpList.end())
                    if ((*tmpIter).size() > 0 &&
                            LINKEDCHAINLIST_canMerge(*ch, *tmpIter))
                    {
                        LINKEDCHAINLIST_mergeChains(*tmpIter, *ch);
                        delete ch;
                        ch = 0;
                        break;
                    }
                    else
                    {
                        ++tmpIter;
                    }
            }

            // Add to global list all remaining chains in tmpList
            insert(end(),tmpList.begin(),tmpList.end());

            return ch;
        }
    }


    // -------------------------------------------------------------------

} // namespace qgar
