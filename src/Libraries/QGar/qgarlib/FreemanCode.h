/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2004  Qgar Project, LORIA                             |
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


#ifndef __FREEMANCODE_H_INCLUDED__
#define __FREEMANCODE_H_INCLUDED__


/**
 * @file FreemanCode.h
 *
 * @brief Header file of class qgar::FreemanCode.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 3, 2004  17:17
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete.
/* $Id: FreemanCode.h,v 1.17 2007/02/14 17:34:04 masini Exp $ */



// STD
#include <iostream>
// QGAR
#include "image.h"
#include "ISerializable.h"
#include "primitives.h"
#include "QgarErrorInvalidArg.h"



using namespace std;



namespace qgar
{


/**
 * @ingroup DS_POINT
 *
 * @class FreemanCode FreemanCode.h "qgarlib/FreemanCode.h"
 *
 * @brief A Freeman code, defined as a pair (direction, length).
 * 
 * A direction is coded using predefined enum type qgar::QGEdirection.
 * As the origin of the coordinates system in images is at top left
 * corner, NORTH and SOUTH are upside down for more convenience:
@verbatim
  (0,0) +---------------------------------------------> X
        |
        |                 QGE_DIRECTION_N
        |                        |  
        |     QGE_DIRECTION_NW \ | / QGE_DIRECTION_NE
        |                       \|/
        |   QGE_DIRECTION_W -----+----- QGE_DIRECTION_E
        |                       /|\
        |     QGE_DIRECTION_SW / | \ QGE_DIRECTION_SE
        |                        |
        |                 QGE_DIRECTION_S
      Y V
@endverbatim
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 3, 2004  17:17
 * @since  Qgar 2.1.1
 */
class FreemanCode

  : public ISerializable

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Default constructor.
   *
   * Direction is initialized to qgar::QGE_DIRECTION_N
   * and length to <b>0</b>.
   */
  FreemanCode();

  /**
   * @brief Copy constructor.
   *
   * @param aCode  a Freeman code
   */
  FreemanCode(const FreemanCode& aCode);

  /**
   * @brief Initialize with a direction and a length.
   *
   * @param aDir     a direction
   * @param aLength  a length
   *
   * @warning Length may be initialized to <b>0</b>.
   */
  FreemanCode(QGEdirection aDir, unsigned int aLength);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~FreemanCode();

  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Get direction.
   */
  inline QGEdirection direction() const;

  /**
   * @brief Get length.
   */
  inline int length() const;

  //@}


  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Set direction.
   *
   * @param aDir  a direction
   */
  inline void setDir(QGEdirection aDir);

  /**
   * @brief Set length.
   *
   * @param aLength  a direction
   *
   * @warning Length may be initialized to <b>0</b>.
   */
  inline void setLength(unsigned int aLength);

  /**
   * @brief Set both direction and length.
   *
   * @param aDir     a direction
   * @param aLength  a length
   *
   * @warning Length may be initialized to <b>0</b>.
   */
  inline void setDirLength(QGEdirection aDir, unsigned int aLength);

  //@}


  /** @name Conversions */
  //        ===========
  //@{

  /**
   * @brief Return the point at the location defined by the current Freeman
   * code, starting from the given point.
   *
   * @param aPt  a point
   *
   * @exception qgar::QgarErrorInvalidArg  unknown direction
   */
  template <class T>
  GenPoint<T> toPoint(const GenPoint<T>& aPt) const;

  /**
   * @brief Return the point at the location defined by the current Freeman
   * code, whose direction is changed into its opposite, starting from the
   * given point.
   *
   * @param aPt  a point
   *
   * @exception qgar::QgarErrorInvalidArg   unknown direction
   */
  template <class T>
  GenPoint<T> toOppositePoint(const GenPoint<T>& aPt) const;

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment operator.
   *
   * @param aCode  a Freeman code
   */
  FreemanCode& operator=(const FreemanCode& aCode);

  //@}


  /** @name Serialization/deserialization */
  //        =============================
  //@{
  /**
   * @brief Deserializes the current Freeman code from an input stream.
   *
   * A serialized Freeman code is represented as:
@verbatim
FreemanCode(<DIRECTION>)(<LENGTH>)
@endverbatim
   *
   * @param anInStream  the input stream
   *
   * @see qgar::qgReadObjName, qgar::qgReadObjData
   */
  virtual std::istream& read(std::istream& anInStream);


  /**
   * @brief Serializes the current Freeman code to an input stream.
   *
   * A serialized Freeman code is represented as:
@verbatim
FreemanCode(<DIRECTION>)(<LENGTH>)
@endverbatim
   *
   * @param anOutStream  the output stream
   */
  virtual std::ostream& write(std::ostream& anOutStream) const;

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Representation of a Freeman code */
  //        ================================
  //@{

  /**
   * @brief The direction code.
   */
  QGEdirection _direction;

  /**
   * @brief The length.
   */
  int _length;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Return the point located at given length in given direction
   *        from the given point.
   *
   * @param aPt      a point
   * @param aDir     a direction
   * @param aLength  a length
   */
  template <class T>
  GenPoint<T> toPointAUX(const GenPoint<T>& aPt,
			 QGEdirection aDir,
			 unsigned int aLength)

    const
   ;

  //@}

// -------------------------------------------------------------------
}; // class FreemanCode




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E    F U N C T I O N S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ======
// ACCESS
// ======


// GET DIRECTION

QGEdirection
FreemanCode::direction() const
{
  return _direction;
}


// GET LENGTH

int
FreemanCode::length() const
{
  return _length;
}


// ==============
// TRANSFORMATION
// ==============


// SET DIRECTION

void
FreemanCode::setDir(QGEdirection aDir)
{
  _direction = aDir;
}


// SET LENGTH

void
FreemanCode::setLength(unsigned int aLength)
{
  _length = aLength;
}


// SET BOTH DIRECTION AND LENGTH

void
FreemanCode::setDirLength(QGEdirection aDir, unsigned int aLength)
{
  _direction = aDir;
  _length    = aLength;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF INLINE FUNCTIONS IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// T E M P L A T E    F U N C T I O N S   I M P L E M E N T A T I O N
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT


// ===========
// CONVERSIONS
// ===========


// APPLY THE CURRENT FREEMAN CODE TO THE GIVEN POINT

template <class T>
GenPoint<T>
FreemanCode::toPoint(const GenPoint<T>& aPt) const
{
  return toPointAUX(aPt, _direction, _length);
}


// APPLY THE CURRENT FREEMAN CODE TO THE GIVEN POINT,
// IN THE OPPOSITE DIRECTION

template <class T>
GenPoint<T>
FreemanCode::toOppositePoint(const GenPoint<T>& aPt) const
{
  return toPointAUX(aPt, qgOpposite(_direction), _length);
}


// ===========
// AUXILIARIES
// ===========


// RETURN THE POINT LOCATED IN GIVEN DIRECTION AT GIVEN LENGTH
// FROM THE GIVEN POINT.

template <class T>
GenPoint<T>
FreemanCode::toPointAUX(const GenPoint<T>& aPt,
			QGEdirection aDir,
			unsigned int aLength) const



{
  switch (aDir)
    {
    case QGE_DIRECTION_N:
      {
	return GenPoint<T>(aPt.x(), aPt.y() - aLength);
      }
    case QGE_DIRECTION_NE:
      {
	return GenPoint<T>(aPt.x() + aLength, aPt.y() - aLength);
      }
    case QGE_DIRECTION_E:
      {
	return GenPoint<T>(aPt.x() + aLength, aPt.y());
      }
    case QGE_DIRECTION_SE:
      {
	return GenPoint<T>(aPt.x() + aLength, aPt.y() + aLength);
      }
    case QGE_DIRECTION_S:
      {
	return GenPoint<T>(aPt.x(), aPt.y() + aLength);
      }
    case QGE_DIRECTION_SW:
      {
	return GenPoint<T>(aPt.x() - aLength, aPt.y() + aLength);
      }
    case QGE_DIRECTION_W:
      {
	return GenPoint<T>(aPt.x() - aLength, aPt.y());
      }
    case QGE_DIRECTION_NW:
      {
	return GenPoint<T>(aPt.x() - aLength, aPt.y() - aLength);
      }
    default:
      {
	// *************************************************************
	// CONTROL SHOULD NEVER REACH THIS POINT
	// *************************************************************
	ostringstream os;
	os << "Unknown direction: "
	   << aDir;
	throw QgarErrorInvalidArg(__FILE__, __LINE__,
				  "template <class T> qgar::GenPoint<T> qgar::FreemanCode::toPointAUX(const qgar::GenPoint<T>&, qgar::QGEdirection, unsigned int) const",
				  os.str());
	// *************************************************************
      }
    }
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// END OF TEMPLATE FUNCTIONS IMPLEMENTATION
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __FREEMANCODE_H_INCLUDED__ */
