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


#ifndef __QGARAPPPARAMDESCR_H_INCLUDED__
#define __QGARAPPPARAMDESCR_H_INCLUDED__


/**
 * @file QgarAppParamDescr.h
 *
 * @brief Header file of class qgar::QgarAppParamDescr.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 15, 2003  10:26
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarAppParamDescr.h,v 1.13 2007/03/12 15:34:18 vasconcv Exp $ */



// STD
#include <cstring>

// STL
#include <string>


using namespace std;



namespace qgar
{

/**
 * @ingroup APP
 *
 * @class QgarAppParamDescr QgarAppParamDescr.h "qgarlib/QgarAppParamDescr.h"
 *
 * @brief Memory representation of an application parameter
 * description.
 *
 * @see QgarAppDescr
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 15, 2003  10:26
 * @since  Qgar 2.1.1
 */
class QgarAppParamDescr
{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:


/**
 * @brief The parameters passing methods.
 */
  enum ParamPassing
    {
      QGE_NONE,
      QGE_IN,
      QGE_OUT,
      QGE_INOUT
    };

/** 
 * @var QgarAppParamDescr::QGE_IN
 * @brief The parameter is an input of the application and will not be
 * modified by its execution.
 */
/** 
 * @var QgarAppParamDescr::QGE_OUT
 * @brief The parameter is an output of the application and will be
 * created by its execution.
 */
/** 
 * @var QgarAppParamDescr::QGE_INOUT
 * @brief The parameter is used by the application as both input and
 * output.
 * The parameter will be modified by the execution of the application.
 */


/**
 * @brief The parameters types.
 */
  enum ParamType
    {
      QGE_UNKNOWN_TYPE,
      QGE_NUM, 
      QGE_IMAGE
    };
/** 
 * @var QgarAppParamDescr::QGE_UNKNOWN_TYPE
 * @brief The type of the parameter is either unknown, or is not
 * recognized as a basic parameter type.
 */
/** 
 * @var QgarAppParamDescr::QGE_NUM
 * @brief The parameter is a number.
 */
/** 
 * @var QgarAppParamDescr::QGE_IMAGE
 * @brief The parameter is an image.
 */


/**
 * @brief The parameters formats. 
 */
  enum ParamFormat
    {
      QGE_UNKNOWN_FORMAT,
      QGE_PBM, 
      QGE_PPM, 
      QGE_PGM, 
      QGE_DXF, 
      QGE_SVG,
      QGE_INT,
      QGE_REAL
    };
/** 
 * @var qgar::QgarAppParamDescr::QGE_UNKNOWN_FORMAT
 * @brief The format of the parameter is either unknown, or is not 
 * recognized as a basic parameter format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_PBM
 * @brief The parameter is an image in PBM format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_PPM
 * @brief The parameter is an image in PPM format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_PGM
 * @brief The parameter is an image in PGM format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_DXF
 * @brief The parameter is an image in DXF format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_SVG
 * @brief The parameter is an image in SVG format.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_INT
 * @brief The parameter is an integer number.
 */
/** 
 * @var qgar::QgarAppParamDescr::QGE_REAL
 * @brief The parameter is a real number.
 */


/** @name Constructors */
//        ============
//@{
/**
 * @brief Builds an empty parameter description.
 *
 * The created description cannot be used as is. Its members must be
 * updated using the class setters.
 */
  QgarAppParamDescr();

/**
 * @brief Creates a parameter description from a full set of parameter
 * data.
 *
 * @param name The name of the parameter.
 * @param flag The flag introducing the parameter on the command line.
 * @param required Whether the parameter is mandatory.
 * @param passingMode The passing mode of the parameter.
 * @param type The type of the parameter.
 * @param format The format of the parameter.
 * @param briefDoc The brief documentation of the parameter.
 * @param longDoc The detailed documentation of the parameter.
 * @param defaultValue The default value for this parameter (if any).
 * @param minValue The minimum value for this parameter (if any).
 * @param maxValue The maximum value for this parameter (if any).
 */
  QgarAppParamDescr(const string& name,
		    const string& flag,
		    bool required,
		    ParamPassing passingMode,
		    ParamType type,
		    ParamFormat format,
		    const string& briefDoc,
		    const string& longDoc,
		    const string& defaultValue = "",
		    const string& minValue     = "",
		    const string& maxValue     = "");

/**
 * @brief Copy constructor
 */
  QgarAppParamDescr(const QgarAppParamDescr&);
//@}


/** @name Destructors */
//        ===========
//@{
/**
 * @brief Destructor
 */
  virtual ~QgarAppParamDescr();
//@}


/** @name Access */
//        ======
//@{
/**
 * @brief Retrieve the name of the parameter.
 *
 * @return The name of the parameter.
 */
  string name() const;

/**
 * @brief Retrieve the flag introducing the parameter on the command
 * line.
 *
 * @return The flag introducing the parameter on the command line.
 */
  string flag() const;
  
/**
 * @brief Query if the parameter is required.
 *
 * @return True if the parameter is required, false if it is optional
 */
  bool required() const;

/**
 * @brief Retrieve the parameter passing mode.
 *
 * @return The parameter passing mode.
 */
  ParamPassing passingMode() const;

/**
 * @brief Retrieve the parameter type.
 *
 * @return The parameter type.
 */
  ParamType type() const;

/**
 * @brief Retrieve the parameter format
 *
 * @return The parameter format.
 */
  ParamFormat format() const;
  
/**
 * @brief Retrieve the parameter default value.
 *
 * @return The default value serialized as a string, or an empty
 * string if none was provided
 */
  string defaultValue() const;

/**
 * @brief Retrieve the parameter minimum value.
 *
 * @return The minimum value serialized as a string, or an empty
 * string if none was provided
 */
  string minValue() const;

/**
 * @brief Retrieve the parameter maximum value.
 *
 * @return The maximum value serialized as a string, or an empty
 * string if none was provided
 */
  string maxValue() const;

/**
 * @brief Retrieve the parameter brief documentation.
 *
 * @return The parameter brief documentation.
 */
  string briefDoc() const;

/**
 * @brief Retrieve the parameter detailed documentation.
 *
 * @return The parameter detailed documentation.
 */
  string longDoc() const;
//@}




/** @name Transformation */
//        ==============
//@{

/**
 * @brief Sets the parameter name.
 *
 * @param aName  new name of the parameter
 */
  void setName(const string& aName);

/**
 * @brief Sets the parameter introducing flag.
 *
 * @param aFlag  new flag for the parameter
 */
  void setFlag(const string& aFlag);

/**
 * @brief Sets if the parameter is mandatory.
 *
 * @param required True if the parameter is required, false
 * otherwise.
 */
  void setRequired(bool required);

/**
 * @brief Sets the parameter passing mode.
 *
 * @param passingMode The new parameter passing mode.
 */
  void setPassingMode(ParamPassing passingMode);

/**
 * @brief Sets the parameter type.
 *
 * @param type The new parameter type.
 */
  void setType(ParamType type);

/**
 * @brief Sets the parameter format.
 *
 * @param format The new parameter format.
 */
  void setFormat(ParamFormat format);

/**
 * @brief Sets the parameter default value.
 *
 * @param aVal new default value for the parameter serialized as a string
 */
  void setDefaultValue(const string& aVal);

/**
 * @brief Sets the parameter minimum value.
 *
 * @param aVal new minimum value for the parameter serialized as a string
 */
  void setMinValue(const string& aVal);

/**
 * @brief Sets the parameter maximum value.
 *
 * @param aVal new maximum value for the parameter serialized as a string
 */
  void setMaxValue(const string& aVal);

/**
 * @brief Sets the brief documentation for the parameter.
 *
 * @param aBriefDoc new brief documentation for the parameter
 */
  void setBriefDoc(const string& aBriefDoc);

/**
 * @brief Sets the detailed documentation for the parameter.
 *
 * @param aLongDoc new detailed documentation for the parameter
 */
  void setLongDoc(const string& aLongDoc);

//@}



/** @name Operators */
//        =========
//@{
/**
 * @brief Assignment operator
 */
  QgarAppParamDescr& operator=(const QgarAppParamDescr&);
//@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /// The name of the parameter.
  string _name;
 
/**
 * @brief The flag introducing this parameter on the command line
 * invoking  the application.
 */
  string _flag;
  
  /// Flag indicating if the parameter is required or optional.
  bool _required;

  /// The passing mode for this parameter.  
  ParamPassing _passingMode;

  /// The type of this parameter.
  ParamType _type;

  /// The format of this parameter.
  ParamFormat _format;

  /// The brief documentation for this parameter.
  string _briefDoc;

  /// The long documentation for this parameter.
  string _longDoc;

  /// The default value for this parameter (if any).
  string _defaultValue;

  /// The minimum value for this parameter (if any).
  string _minValue;

  /// The max value for this parameter (if any).
  string _maxValue;

// -------------------------------------------------------------------
}; // class QgarAppParamDescr

} // namespace qgar


#endif /* __QGARAPPPARAMDESCR_H_INCLUDED__ */
