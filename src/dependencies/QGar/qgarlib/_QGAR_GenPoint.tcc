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
 * @file _QGAR_GenPoint.tcc
 *
 * @brief Implementation of function members of class qgar::GenPoint.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   December 15, 2004  15:55
 * @since  Qgar 2.2
 */



// STD
#include <algorithm>
#include <cmath>
//#include <cctype>
#include <iostream>
// QGAR
#include "ISerializable.h"



namespace qgar
{


    // -------------------------------------------------------------------
    // JUST A FAKE CLASS (NOT DEFINED)
    // TO BE USED TO CAUSE COMPILATION ERRORS WHEN SOME TEMPLATE FUNCTION
    // CANNOT BE INSTANTIATED USING ANY TYPE
    // -------------------------------------------------------------------


    class TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC;


    // -------------------------------------------------------------------
    // C O N S T R U C T O R S
    // -------------------------------------------------------------------


    // DEFAULT CONSTRUCTOR

    template <class T>
    GenPoint<T>::GenPoint() : x_(0), y_(0) {
        // VOID
    }


    // COPY-CONSTRUCTOR

    template <class T>
    GenPoint<T>::GenPoint(const GenPoint<T>& aPt) : x_(aPt.x_), y_(aPt.y_) {
        // VOID
    }


    // CONVERSION OF A POINT OF A TYPE DIFFERENT FROM THE EFFECTIVE TYPE

    template <class T>
    template <class U>
    GenPoint<T>::GenPoint(const GenPoint<U>& aPt) : x_(static_cast<T>(aPt.x())), y_(static_cast<T>(aPt.y())){
        // VOID
    }


    // INITIALIZE FROM COORDINATES

    template <class T>
    GenPoint<T>::GenPoint(T aX, T aY) : x_(aX), y_(aY) {
        // VOID
    }


    // -------------------------------------------------------------------
    // D E S T R U C T O R
    // -------------------------------------------------------------------


    // NON-VIRTUAL DESTRUCTOR

    template <class T>
    GenPoint<T>::~GenPoint()
    {
        // VOID
    }


    // -------------------------------------------------------------------
    // A C C E S S   T O   C O O R D I N A T E S
    // -------------------------------------------------------------------


    // GET X COORDINATE

    template <class T>
    inline T
    GenPoint<T>::x() const
    {
        return x_;
    }


    // GET Y COORDINATE

    template <class T>
    inline T
    GenPoint<T>::y() const
    {
        return y_;
    }


    // GET RADIUS (rho) IN POLAR COORDINATES

    template <class T>
    inline double
    GenPoint<T>::rho() const
    {
        return hypot((double) x_, (double) y_);
    }


    // GET ANGLE (theta) IN POLAR COORDINATES

    template <class T>
    inline double
    GenPoint<T>::theta() const
    {
        return atan2((double)y_, (double)x_);
    }


    // -------------------------------------------------------------------
    // A S S I G N   C O O R D I N A T E S
    // -------------------------------------------------------------------


    // SET X COORDINATE


    template <class T>
    inline void
    GenPoint<T>::setX(T aX)
    {
        x_ = aX;
    }


    // SET Y COORDINATE

    template <class T>
    inline void
    GenPoint<T>::setY(T aY)
    {
        y_ = aY;
    }


    // SET BOTH X AND Y COORDINATES

    template <class T>
    inline void
    GenPoint<T>::setXY(T aX, T aY)
    {
        x_ = aX;
        y_ = aY;
    }


    // -------------------------------------------------------------------
    // G E O M E T R Y :   p r o j e c t i o n
    // -------------------------------------------------------------------


    // ******************************************************
    // ******************************************************
    // WARNING: Functions applying to points with coordinates
    // of type other than double are not defined
    // ******************************************************
    // ******************************************************


    template <class T>
    inline void
    GenPoint<T>::project(const GenSegment<T>& aSeg)
    {
        TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    }


    template <class T>
    inline void
    GenPoint<T>::project(const GenQgarSegment<T>& aQSeg)
    {
        TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    }


    // ORTHOGONAL PROJECTION OF THE CURRENT POINT
    // ONTO THE LINE SUPPORTING A GIVEN SEGMENT

    template <>
    inline void
    GenPoint<double>::project(const GenSegment<double>& aSeg)
    {
        qgProject(*this, aSeg);
    }


    // CASE OF A Qgar SEGMENT

    template <>
    inline void
    GenPoint<double>::project(const GenQgarSegment<double>& aQSeg)
    {
        qgProject(*this, aQSeg);
    }


    // -------------------------------------------------------------------
    // G E O M E T R Y :   t r a n s l a t i o n
    // -------------------------------------------------------------------


    // TRANSLATE ALONG X AND Y AXIS

    template <class T>
    inline void
    GenPoint<T>::translate(T aTransX, T aTransY)
    {
        x_ += aTransX;
        y_ += aTransY;
    }


    // // -------------------------------------------------------------------
    // // G E O M E T R Y :   r o t a t i o n
    // // -------------------------------------------------------------------


    // // ******************************************************
    // // ******************************************************
    // // WARNING: Functions applying to points with coordinates
    // // of type other than double are not defined
    // // ******************************************************
    // // ******************************************************


    // // ROTATE USING ORIGIN AS CENTER
    // // =============================


    // template <class T>
    // void
    // GenPoint<T>::rotate(double anAngle)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate(double anAngle)
    // {
    //   double cosA = cos(anAngle);
    //   double sinA = sin(anAngle);
    //   double tmpX = x_;

    //   x_ = (tmpX * cosA) - (y_ * sinA);
    //   y_ = (tmpX * sinA) + (y_ * cosA);
    // }


    // // ROTATE USING A CENTER AND AN ANGLE
    // // ==================================


    // template <class T>
    // void
    // GenPoint<T>::rotate(double anAngle, const GenPoint<T>& aPt)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate(double anAngle,
    // 			 const GenPoint<double>& aPt)
    // {
    //   this->translate(-aPt.x(), -aPt.y());
    //   this->rotate(anAngle);
    //   this->translate(aPt.x(), aPt.y());
    // }


    // // ROTATE BY PI/2 USING ORIGIN AS CENTER
    // // =====================================


    // template <class T>
    // void
    // GenPoint<T>::rotate90()
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate90()
    // {
    //   double tmpX = x_;

    //   x_ = -y_;
    //   y_ = tmpX;
    // }


    // // ROTATE BY PI/2 USING A GIVEN CENTER
    // // ===================================


    // template <class T>
    // void
    // GenPoint<T>::rotate90(const GenPoint<T>& aPt)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate90(const GenPoint<double>& aPt)
    // {
    //   double tmpX = x_;

    //   x_ = (aPt.y() -y_)    + aPt.x();
    //   y_ = (tmpX - aPt.x()) + aPt.y();
    // }


    // // ROTATE BY PI USING ORIGIN AS CENTER
    // // ===================================

    // template <class T>
    // inline void
    // GenPoint<T>::rotate180()
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // inline void
    // GenPoint<double>::rotate180()
    // {
    //   this->symmetry();
    // }


    // // ROTATE BY PI USING A GIVEN CENTER
    // // =================================

    // template <class T>
    // inline void
    // GenPoint<T>::rotate180(const GenPoint<T>& aPt)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // inline void
    // GenPoint<double>::rotate180(const GenPoint<double>& aPt)
    // {
    //   this->symmetry(aPt);
    // }


    // // ROTATE BY 3*PI/2 USING ORIGIN AS ROTATION CENTER
    // // ================================================

    // template <class T>
    // void
    // GenPoint<T>::rotate270()
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate270()
    // {
    //   double tmpX = x_;

    //   x_ = y_;
    //   y_ = -tmpX;
    // }


    // // ROTATE BY 3*PI/2 USING A GIVEN CENTER
    // // =====================================

    // template <class T>
    // void
    // GenPoint<T>::rotate270(const GenPoint<T>& aPt)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::rotate270(const GenPoint<double>& aPt)
    // {
    //   double tmpX = x_;

    //   x_ = aPt.x() - aPt.y() + y_;
    //   y_ = aPt.x() + aPt.y() - tmpX;
    // }


    // // -------------------------------------------------------------------
    // // G E O M E T R Y :   h o m o t h e t y
    // // -------------------------------------------------------------------


    // // ******************************************************
    // // ******************************************************
    // // WARNING: Functions applying to points with coordinates
    // // of type other than double are not defined
    // // ******************************************************
    // // ******************************************************


    // // HOMOTHETY USING GIVEN DILATION FACTOR AND THE ORIGIN AS CENTER
    // // ==============================================================


    // template <class T>
    // void
    // GenPoint<T>::homothety(double aDilFactor)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::homothety(double aDilFactor)
    // {
    //   x_ = aDilFactor * x_;
    //   y_ = aDilFactor * y_;
    // }


    // // HOMOTHETY USING GIVEN DILATION FACTOR AND CENTER
    // // ================================================


    // template <class T>
    // void
    // GenPoint<T>::homothety(double aDilFactor,
    // 		       const GenPoint<T>& aPt)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::homothety(double aDilFactor,
    // 			    const GenPoint<double>& aPt)
    // {
    //   x_ = aPt.x() + aDilFactor * (x_ - aPt.x());
    //   y_ = aPt.y() + aDilFactor * (y_ - aPt.y());
    // }


    // // -------------------------------------------------------------------
    // // G E O M E T R Y :   s y m m e t r y
    // // -------------------------------------------------------------------


    // // CENTRAL SYMMETRY USING THE ORIGIN AS CENTER
    // // ===========================================


    // template <class T>
    // void
    // GenPoint<T>::symmetry()
    // {
    //   x_ = -x_;
    //   y_ = -y_;
    // }


    // // CENTRAL SYMMETRY USING A GIVEN CENTER
    // // =====================================


    // template <class T>
    // void
    // GenPoint<T>::symmetry(const GenPoint<T>& aPt)
    // {
    //   x_ = (2 * aPt.x()) - x_;
    //   y_ = (2 * aPt.y()) - y_;
    // }


    // // ******************************************************
    // // ******************************************************
    // // WARNING: Functions applying to points with coordinates
    // // of type other than double are not defined
    // // ******************************************************
    // // ******************************************************


    // // MIRROR SYMMETRY, USING THE LINE SUPPORTING THE GIVEN SEGMENT
    // // ============================================================


    // class  TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC;

    // template <class T>
    // void
    // GenPoint<T>::symmetry(const GenSegment<T>& aSeg)
    // {
    //   TEMPLATE_FUNCTION_CANNOT_BE_INSTANTIATED_SEE_DOC();
    // }


    // template <>
    // void
    // GenPoint<double>::symmetry(const GenSegment<double>& aSeg)
    // {
    //   // Project a copy of the current segment onto the given line
    //   GenPoint<double> p(*this);
    //   p.project(aSeg);

    //   // Use the projection as symmetry center
    //   this->symmetry(p);
    // }


    // -------------------------------------------------------------------
    // O P E R A T O R S
    // -------------------------------------------------------------------


    // ASSIGNMENT

    template <class T>
    GenPoint<T>&
    GenPoint<T>::operator=(const GenPoint<T>& aPt)
    {
        // ___________________________________________________________
        //
        // TEST DISABLED FOR MORE EFFICIENCY
        // ___________________________________________________________
        //
        // Are left hand side and right hand side different objects?
        //    if (this != &aPt)
        //      {
        // ___________________________________________________________

        x_ = aPt.x_;
        y_ = aPt.y_;

        // ___________________________________________________________
        //
        //      }
        // ___________________________________________________________

        return *this;
    }


    // SAME AS FUNCTION qgar::GenPoint::plus

    template <class T>
    inline const GenPoint<T>
    GenPoint<T>::operator+(const GenPoint<T>& aPt) const
    {
        return plus(aPt);
    }


    // SAME AS FUNCTION qgar::GenPoint::plusEqual

    template <class T>
    inline GenPoint<T>&
    GenPoint<T>::operator+=(const GenPoint<T>& aPt)
    {
        return plusEqual(aPt);
    }


    // SAME AS FUNCTION qgar::GenPoint::minus

    template <class T>
    inline const GenPoint<T>
    GenPoint<T>::operator-(const GenPoint<T>& aPt) const
    {
        return minus(aPt);
    }


    // SAME AS FUNCTION qgar::GenPoint::minusEqual

    template <class T>
    inline GenPoint<T>&
    GenPoint<T>::operator-=(const GenPoint<T>& aPt)
    {
        return minusEqual(aPt);
    }


    // SAME AS FUNCTION qgar::GenPoint::eq

    template <class T>
    inline bool
    GenPoint<T>::operator==(const GenPoint<T>& aPt) const
    {
        return eq(aPt);
    }


    // SAME AS FUNCTION qgar::GenPoint::notEq

    template <class T>
    inline bool
    GenPoint<T>::operator!=(const GenPoint<T>& aPt) const
    {
        return notEq(aPt);
    }


    // -------------------------------------------------------------------
    // F U N C T I O N A L   O P E R A T O R S
    // -------------------------------------------------------------------


    // ADD COORDINATES OF THE GIVEN POINT TO THOSE
    // OF THE CURRENT POINT, AND RETURN THEM AS A NEW POINT

    template <class T>
    const GenPoint<T>
    GenPoint<T>::plus(const GenPoint<T>& aPt) const
    {
        return GenPoint(*this).plusEqual(aPt);
    }


    // ADD COORDINATES OF THE GIVEN POINT TO THOSE OF THE CURRENT POINT

    template <class T>
    GenPoint<T>&
    GenPoint<T>::plusEqual(const GenPoint<T>& aPt)
    {
        x_ += aPt.x();
        y_ += aPt.y();
        return *this;
    }


    // SUBSTRACT COORDINATES OF THE GIVEN POINT TO THOSE
    // OF THE CURRENT POINT, AND RETURN THEM AS A NEW POINT

    template <class T>
    const GenPoint<T>
    GenPoint<T>::minus(const GenPoint<T>& aPt) const
    {
        return GenPoint(*this).minusEqual(aPt);
    }


    // SUBSTRACT COORDINATES OF THE GIVEN POINT TO THOSE OF THE CURRENT POINT

    template <class T>
    GenPoint<T>&
    GenPoint<T>::minusEqual(const GenPoint<T>& aPt)
    {
        x_ -= aPt.x();
        y_ -= aPt.y();
        return *this;
    }


    // EQUALITY

    template <class T>
    bool
    GenPoint<T>::eq(const GenPoint<T>& aPt) const
    {
        return ((x_ == aPt.x()) && (y_ == aPt.y()));
    }


    // INEQUALITY

    template <class T>
    bool
    GenPoint<T>::notEq(const GenPoint<T>& aPt) const
    {
        return (! this->eq(aPt) );
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------
    // S E R I A L I Z A T I O N / D E S E R I A L I Z A T I O N
    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


    // CLASS qgar::GenPoint DOES NOT DERIVE FROM CLASS qgar::ISerializable
    // TO GET A SMALLER IMPLEMENTATION OF A POINT
    //
    // => THESE ARE GLOBAL FUNCTIONS


    // DESERIALIZE A POINT (READ IT FROM AN INPUT STREAM)

    template <class T>
    inline std::istream&
    operator>>(std::istream& anInStream, GenPoint<T>& aPt)
    {
        qgReadObjName(anInStream, "Point");

        T x;
        qgReadObjData(anInStream, x);

        T y;
        qgReadObjData(anInStream, y);

        aPt = GenPoint<T>(x,y);

        return anInStream;
    }


    // SERIALIZE A POINT (WRITE IT INTO AN OUTPUT STREAM)

    template <class T>
    inline std::ostream&
    operator<<(std::ostream& anOutStream, const GenPoint<T>& aPt)
    {
        anOutStream << "Point("
                    << aPt.x()
                    << ")("
                    << aPt.y()
                    << ')';

        return anOutStream;
    }


    // -------------------------------------------------------------------
    // -------------------------------------------------------------------


} // namespace qgar
