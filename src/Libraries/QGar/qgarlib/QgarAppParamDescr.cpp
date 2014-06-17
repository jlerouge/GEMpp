/*---------------------------------------------------------------------*
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2003  Qgar Project, LORIA                             |
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


/**
 * @file  QgarAppParamDescr.cpp
 * @brief Implementation of class qgar::QgarAppParamDescr.
 *
 *        See file QgarAppParamDescr.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 15, 2003  10:26
 * @since  Qgar 
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarAppParamDescr.cpp,v 1.10 2006/04/14 15:30:48 gerald Exp $ */



// STD
#include <iostream>
// QGAR
#include "QgarAppParamDescr.h"



using namespace std;


namespace qgar
{
// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QgarAppParamDescr::QgarAppParamDescr()

  : _required(false),
    _passingMode(QGE_IN),
    _type(QGE_UNKNOWN_TYPE),
    _format(QGE_UNKNOWN_FORMAT)

{
  /* EMPTY */
}

// ---------------------------------------------------------------------

QgarAppParamDescr::QgarAppParamDescr(const string& name,
				     const string& flag,
				     bool required,
				     ParamPassing passingMode,
				     ParamType type,
				     ParamFormat format,
				     const string& briefDoc,
				     const string& longDoc,
				     const string& defaultValue,
				     const string& minValue,
				     const string& maxValue)

  : _name(name),
    _flag(flag),
    _required(required),
    _passingMode(passingMode),
    _type(type),
    _format(format),
    _briefDoc(briefDoc),
    _longDoc(longDoc),
    _defaultValue(defaultValue),
    _minValue(minValue),
    _maxValue(maxValue)

{
  /* EMPTY */
}
  

// ---------------------------------------------------------------------

// Copy constructor
QgarAppParamDescr::QgarAppParamDescr(const QgarAppParamDescr& rhs)

  : _name(rhs._name),
    _flag(rhs._flag),
    _required(rhs._required),
    _passingMode(rhs._passingMode),
    _type(rhs._type),
    _format(rhs._format),
    _briefDoc(rhs._briefDoc),
    _longDoc(rhs._longDoc),
    _defaultValue(rhs._defaultValue),
    _minValue(rhs._minValue),
    _maxValue(rhs._maxValue)

{
  /* EMPTY */
}


// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QgarAppParamDescr::~QgarAppParamDescr()
{
  /* EMPTY */
}


// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

string
QgarAppParamDescr::name() const
{ 
  return _name;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::flag() const
{ 
  return _flag;
}

// ---------------------------------------------------------------------

bool
QgarAppParamDescr::required() const
{ 
  return _required;
}

// ---------------------------------------------------------------------

QgarAppParamDescr::ParamPassing 
QgarAppParamDescr::passingMode() const
{ 
  return _passingMode;
}

// ---------------------------------------------------------------------

QgarAppParamDescr::ParamType
QgarAppParamDescr::type() const
{ 
  return _type;
}

// ---------------------------------------------------------------------

QgarAppParamDescr::ParamFormat
QgarAppParamDescr::format() const
{ 
  return _format;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::briefDoc() const
{ 
  return _briefDoc;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::longDoc() const
{ 
  return _longDoc;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::defaultValue() const
{
  return _defaultValue;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::minValue() const
{
  return _minValue;
}

// ---------------------------------------------------------------------

string
QgarAppParamDescr::maxValue() const
{
  return _maxValue;
}

// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QgarAppParamDescr::setName(const std::string& aName)
{
  _name = aName;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setFlag(const std::string& aFlag)
{
  _flag = aFlag;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setRequired(bool required)
{
  _required = required;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setPassingMode(ParamPassing passingMode)
{
  _passingMode = passingMode;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setType(ParamType type)
{
  _type = type;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setFormat(ParamFormat format)
{
  _format = format;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setBriefDoc(const std::string& aBriefDoc)
{
  _briefDoc = aBriefDoc;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setLongDoc(const std::string& aLongDoc)
{
  _longDoc = aLongDoc;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setDefaultValue(const std::string& aVal)
{
  _defaultValue = aVal;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setMinValue(const std::string& aVal)
{
  _minValue = aVal;
}

// ---------------------------------------------------------------------

void
QgarAppParamDescr::setMaxValue(const std::string& aVal)
{
  _maxValue = aVal;
}


// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QgarAppParamDescr& 
QgarAppParamDescr::operator=(const QgarAppParamDescr& rhs)
{
  if (this != &rhs)
    {
      _name        = rhs._name;
      _flag        = rhs._flag;
      _required    = rhs._required;
      _passingMode = rhs._passingMode;
      _type        = rhs._type;
      _format      = rhs._format;
      _briefDoc    = rhs._briefDoc;
      _longDoc     = rhs._longDoc;
    }

  return *this;
}


// ----------------------------------------------------------------------

} // namespace qgar
