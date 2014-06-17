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
 * @file   Maer.cpp
 * @brief  Implementation of class qgar::Maer.
 *
 * See file Maer.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   May 13, 2004  11:30
 * @since  Qgar 2.1
 */



// STD
#include <cmath>
#include <limits>
#include <list>
// QGAR
#include "FreemanChain.h"
#include "GenConvexHull.h"
#include "Maer.h"
#include "math.h"
#include "primitives.h"
#include "QgarErrorDeveloper.h"



namespace qgar
{

    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // C O N S T R U C T O R S
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // ___________________________________________________________________
    //
    // WARNING: the default constructor belongs to the private section
    // so that clients cannot use it

    Maer::Maer()
    {
        throw QgarErrorDeveloper(__FILE__, __LINE__,
                                 "qgar::Maer::Maer()",
                                 "Disabled constructor: should not be used!");
    }
    // ___________________________________________________________________


    // CREATE FROM A FREEMAN CHAIN

    Maer::Maer(const FreemanChain& aCh)
    {
        PRIVATEcomputeMaer(aCh.toDPointList());
    }


    // COPY CONSTRUCTOR

    Maer::Maer(const Maer& aMaer)

        : vertices_  (aMaer.vertices_),
          areaPx_    (aMaer.areaPx_)

    {
        // VOID
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // D E S T R U C T O R
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // NON-VIRTUAL DESTRUCTOR

    Maer::~Maer()
    {
        // VOID
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // A C C E S S   T O   C O R N E R S
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------

    // GET THE LIST INCLUDING THE 4 CORNERS OF THE MAER

    const std::list<DPoint>&
    Maer::accessVertices() const
    {
        return vertices_;
    }

    // GET A COPY OF THE LIST INCLUDING THE 4 CORNERS OF THE MAER

    std::list<DPoint>
    Maer::vertices() const
    {
        return vertices_;
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // O P E R A T O R S
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // ASSIGNMENT

    Maer&
    Maer::operator=(const Maer& aMaer)
    {
        // Are left hand side and right hand side different objects?
        if (this != &aMaer)
        {
            vertices_ = aMaer.vertices_;
            areaPx_   = aMaer.areaPx_;
        }

        return *this;
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // C O N S T R U C T I O N   O F   T H E   M A E R   (PRIVATE)
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    void
    Maer::PRIVATEcomputeMaer(const std::list<DPoint>& aPtList)
    {
        // THE CONVEX HULL OF THE GIVEN POINTS
        // ===================================

        DConvexHull hull(aPtList);

        // THE COMPONENT IS A SINGLE POINT: DEGENERATED MAER
        // =================================================

        if (hull.size() == 1)
        {
            // 4 same corners and null area
            vertices_.push_back(hull.accessPivot());
            vertices_.push_back(hull.accessPivot());
            vertices_.push_back(hull.accessPivot());
            vertices_.push_back(hull.accessPivot());
            areaPx_ = 1.;

            return;
        }

        // COMPUTE THE DIFFERENT RECTANGLES AND SELECT THE MINIMAL ONE
        // ===========================================================

        // List of the vertices of the hull
        const std::list<DPoint>& vList = hull.accessVertices();

        // 2 consecutive points of the hull
        std::list<DPoint>::const_iterator itPrev = vList.begin();
        std::list<DPoint>::const_iterator itCurr = itPrev;
        itCurr++;

        // Current minimum area
        areaPx_ = std::numeric_limits<double>::max();

        // Consider each consecutive pair of hull vertices
        // and compute the corresponding rectangle
        // WARNING: The last pair includes the last and first vertices

        do
            // DO WHILE BLOCK  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
        {

            // Coordinates of previous point
            double xPrev = itPrev->x();
            double yPrev = itPrev->y();

            // Direction of the vector joining previous and current points
            double theta = atan2(itCurr->y() - yPrev, itCurr->x() - xPrev);
            if (theta < 0.)
            {
                theta += Math::QG_2PI;
            }

            // Sinus and cosinus
            double cosTheta = cos(theta);
            double sinTheta = sin(theta);

            // Initializations
            double minX = std::numeric_limits<double>::max();
            double maxX = std::numeric_limits<double>::min();
            double minY = std::numeric_limits<double>::max();
            double maxY = std::numeric_limits<double>::min();

            // Minimum and maximum X and Y
            for (std::list<DPoint>::const_iterator itV  = vList.begin() ;
                 itV != vList.end() ;
                 itV++)
            {
                // Translation
                double xTmp = itV->x() - xPrev;
                double yTmp = itV->y() - yPrev;

                // Rotation
                double x = ( xTmp * cosTheta) + (yTmp * sinTheta);
                double y = (-xTmp * sinTheta) + (yTmp * cosTheta);

                // Update coordinates min's and max's
                if (x < minX)
                {
                    minX = x;
                }
                else if (x > maxX)
                {
                    maxX = x;
                }

                if (y < minY)
                {
                    minY = y;
                }
                else if (y > maxY)
                {
                    maxY = y;
                }
            }

            // The four corners of the corresponding rectangle

            double minXC = minX * cosTheta;
            double minXS = minX * sinTheta;
            double minYC = minY * cosTheta;
            double minYS = minY * sinTheta;
            double maxYC = maxY * cosTheta;
            double maxYS = maxY * sinTheta;
            double maxXC = maxX * cosTheta;
            double maxXS = maxX * sinTheta;

            double xTopL = minXC - minYS + xPrev;
            double yTopL = minXS + minYC + yPrev;

            double xTopR = minXC - maxYS + xPrev;
            double yTopR = minXS + maxYC + yPrev;

            double xBotR = maxXC - maxYS + xPrev;
            double yBotR = maxXS + maxYC + yPrev;

            double xBotL = maxXC - minYS + xPrev;
            double yBotL = maxXS + minYC + yPrev;

            // _______________________________________________________________
            //
            // WARNING: PARTICULAR CASES
            // - the area is supposed to be expressed in pixels
            // - the pixels defining the borders belong to the rectangle
            // ==>
            // - add 1 to the difference between X and Y coordinates
            //   unless the difference is 0
            // - if a couple of differences are both 0,
            //   let one difference be 1

            double dX1 = qgAbs(xTopL - xTopR);
            double dY1 = qgAbs(yTopL - yTopR);
            double dX2 = qgAbs(xTopR - xBotR);
            double dY2 = qgAbs(yTopR - yBotR);

            if (qgEq0(dX1))
            {
                dX1 = 0.;

                if (qgEq0(dY1))
                {
                    dY1 = 1.;
                }
                else
                {
                    dY1 += 1.;
                }
            }
            else
            {
                dX1 += 1.;

                if (qgEq0(dY1))
                {
                    dY1 = 0.;
                }
                else
                {
                    dY1 += 1.;
                }
            }

            if (qgEq0(dX2))
            {
                dX2 = 0.;

                if (qgEq0(dY2))
                {
                    dY2 = 1.;
                }
                else
                {
                    dY2 += 1.;
                }
            }
            else
            {
                dX2 += 1.;

                if (qgEq0(dY2))
                {
                    dY2 = 0.;
                }
                else
                {
                    dY2 += 1.;
                }
            }

            double currArea = hypot(dX1,dY1) * hypot(dX2,dY2);
            // _______________________________________________________________

            // Update minimum area
            if (currArea < areaPx_)
            {
                // Current rectangle is the minimum one up to now
                areaPx_ = currArea;

                // Save new maer
                vertices_.clear();
                vertices_.push_back(DPoint(xTopL, yTopL));
                vertices_.push_back(DPoint(xTopR, yTopR));
                vertices_.push_back(DPoint(xBotR, yBotR));
                vertices_.push_back(DPoint(xBotL, yBotL));
            }

            // Next vertices pair
            // WARNING: The last pair includes the last and first vertices
            itPrev = itCurr;
            itCurr++;
            if (itCurr == vList.end())
            {
                itCurr = vList.begin();
            }

        }
        // END OF DO WHILE BLOCK  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

        while (itPrev != vList.begin());

    }

    // -------------------------------------------------------------------

} // namespace qgar
