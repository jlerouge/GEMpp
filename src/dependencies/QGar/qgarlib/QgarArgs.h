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


#ifndef __QGARARGS_H_INCLUDED__
#define __QGARARGS_H_INCLUDED__

/**
 * @file QgarArgs.h
 *
 * @brief Header file of class qgar::QgarArgs.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   July 02, 2001  17:20
 * @since  Qgar 1.0
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarArgs.h,v 1.20 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <iostream>
#include <list>
#include <vector>

// QGar
#include "qgar.h"

using namespace std;



namespace qgar
{

/** 
 * @class QgarArgs QgarArgs.h "qgarlib/QgarArgs.h"
 * @ingroup APP
 * @brief To handle the parameters given to an application. 
 * 
 * The class can be used alone, or coupled with class qgar::QgarApp which
 * allows an application to be interactively used. See class qgar::QgarApp
 * for further instructions.
 *
 * The class allows a quick and easy definition of the different
 * parameters accepted by an application.
 * <ul>
 * <li>
 * The application declares all the parameters it may receive.
 * </li>
 * <li>
 * The parameters effectively given to the application are transmitted
 * to an object of class qgar::QgarArgs, which updates its internal
 * structure and checks if all the required parameters are given.
 * </li>
 * <li>
 * The client can then send a query to the object to know if some parameter
 * is declared, to get the characteristics of some parameter, etc.
 * </li>
 * </ul>
 *
 * A user can get help about an application parameters by launching
 * the application with flag <b>-h</b>.
 *
 * Flag <b>-gui</b> allows the QgarGui QGar user interface to be provided
 * with the arguments of a given application.
 *
 * Here is a minimal and typical example of use of the class
 * for text-graphic separation:
@code
#include "QgarApp.h"
#include "QgarArgs.h"

using namespace std;
using namespace qgar;

int main(int argc, char* argv[])
{
  QgarApp app;

  // INITIALIZATIONS
  // ===============

  // Description of the parameters

  app.addParameter("-in",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEIN,
		   "Source image:");

  app.addParameter("-t",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Text image:",
		   ".text.pbm");

  app.addParameter("-g",
		   QgarArgs::REQPARAM,
		   QgarArgs::FILEOUTD,
		   "Graphic image:",
		   ".graph.pbm");

  app.addParameter("-s",
		   QgarArgs::REQPARAM,
		   QgarArgs::INT,
		   "Dimension threshold:",
		   0,
		   "20");

  app.addParameter("-thr",
		   QgarArgs::OPTPARAM,
		   QgarArgs::INT,
		   "Threshold:",
		   0,
		   "3");

  app.addParameter("-d",
		   QgarArgs::REQPARAM,
		   QgarArgs::FLOAT,
		   "Black pixel density:",
		   0,
		   ".6");

  // Description of the application
  app.setDescription("Text-graphic separation", QgarArgs::PBM);

  // COMMAND LINE ANALYSIS
  // =====================

  app.analyzeLine(argc, argv);

  // Error while parsing parameters?
  if (app.isError())
    {
      return app._CODE_ERROR;
    }

  // Application invoked with flag '-gui'?
  if (app.isExit())
    {
      return app._CODE_GUI;
    }

  // Set progress bar on
  app.showProgressBar();
  app.setProgressBar(0);

  // GET ARGUMENTS
  // =============

  // Get the value of parameter introduced by flag '-in'
  // (it must be given, as this parameter is required)
  const char* name = app.getStringOption("-in");

  // Get the threshold value if defined by the command line
  int threshold = 3;
  if (app.isOptionSet("-thr"))
    {
      threshold = atoi(app.getStringOption("-thr"));
    }

  app.setProgressBar(5);

  // AND SO ON...
  // ============

  ...

  // NORMAL TERMINATION
  // ==================

  return app._CODE_END;

} // END main()
@endcode
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date    July 02, 2001  17:20
 * @since   Qgar 1.0
 */

class QgarArgs
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Type definitions */
  //        ================
  //@{

  /**
   * @brief Parameter status.
   *
   * - <b>SINGLEFLAG</b>: single flag, associated with no value (<b>-f</b>)
   * - <b>REQPARAM</b>: required (i.e. non-optional) parameter,
   *                    introducing a value (<b>-f *val*</b>)
   * - <b>OPTPARAM</b>: optional parameter,
   *                    introducing a value (<b>-f *val*</b>)
   * - <b>REQMULTIPARAM</b>: required parameter, introducing
   *                         several values (<b>-f *val1* .. *valN*</b>)
   * - <b>OPTMULTIPARAM</b>: optional parameter, introducing
   *                         several values (<b>-f *val1* .. *valN*</b>)
   */
  enum QGEparamStatus
    {
      SINGLEFLAG,
      REQPARAM,
      OPTPARAM,
      REQMULTIPARAM,
      OPTMULTIPARAM
    };
	     
  /**
   * @brief Types of the values associated to parameters.
   *
   * - <b>INT</b>: integer number
   * - <b>FLOAT</b>: floating number
   * - <b>STRING</b>: string
   * - <b>BOOL</b>: boolean
   * - <b>FILEIN</b>: name of an input data file
   * - <b>FILEOUT</b>: name of an output data file
   * - <b>FILEOUTD</b>: name of an output data file,
   *                    whose content is intended to be displayed
   * - <b>FILEOUTDS</b>: name of an output data file,
   *                     whose content is intended to be displayed in
   *                     superimposition mode
   * - <b>PATH</b>: path of a directory
   */
  enum QGEparamType
    {
      INT,
      FLOAT,
      STRING,
      BOOL,
      FILEIN,
      FILEOUT,
      FILEOUTD,
      FILEOUTDS,
      PATH
    };

 /**
   * @brief File formats.
   *
   * - <b>PPM</b>: color bitmap image
   * - <b>PGM</b>: grey-level bitmap image
   * - <b>PBM</b>: black and white bitmap image
   * - <b>DXF</b>: vectorial image
   */
  enum QGEfileType
    {
      PPM,
      PGM,
      PBM,
      DXF
    };

  //@}


/*-------------------------------------------------------------------*
 |                                                                   |
 |                 I N N E R   C L A S S   QgarParam                 |
 |                                                                   |
 *-------------------------------------------------------------------*/
public:

  /**
   * @ingroup APP
   *
   * @class QgarParam
   *
   * @brief Internal representation of an application parameter.
   * 
   * Inner class of class qgar::QgarArgs
   *
   * @todo Complete the documentation
   *
   * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
   * @date  July 02, 2001  17:20
   * @since Qgar 1.0
   */
  class QgarParam
  {
    // ---------------------------
    // P U B L I C   M E M B E R S
    // ---------------------------
  public:

    /** @name Constructors */
    //       ============
    //@{

    /**
     * @brief Construct from full data.
     *
     * @param aParamName    parameter name, first character is a minus (e.g. <b>-f</b>)
     * @param aParamStatus  parameter status (see enum type qgar::QgarArgs::ParamStatus)
     * @param aParamType    parameter type (see enum type qgar::QgarArgs::ParamType)
     * @param aDescription  short description of the parameter
     * @param anExtension   file extension, in case of an output file
     * @param aDefault      default value (given as a string) for a parameter
     *                      which is not a file
     */
    QgarParam(const char* aParamName,
	      QGEparamStatus aParamStatus,
	      QGEparamType aParamType,
	      const char* aDescription,
	      const char* anExtension = 0,
	      const char* aDefault = 0);

    //@}


    /** @name Access */
    //       ======
    //@{

    /**
     * @brief Get the parameter status.
     */
    inline QGEparamStatus paramStatus() const;

    /**
     * @brief Get flag for use.
     */
    inline bool useFlag() const;

    /**
     * @brief Get parameter name.
     */
    inline const char* name() const;

    /**
     * @brief Get parameter value.
     *
     * @param aSpecial 
     */
    const char* value(bool aSpecial);

    /**
     * @brief Get parameter number.
     */
    inline int numbOptions() const;

    /**
     * @brief Get indexed argument.
     *
     * @param anIdx  argument index.
     */
    inline const char* argument(int anIdx);

    /**
     * @brief Get parameter description.
     */
    inline const char* description() const;

    /**
     * @brief Get new value.
     */
    inline bool newValue() const;

    //@}


    /** @name Transformation */
    //       ==============
    //@{

    /**
     * @brief Set flag for use (default <b>true</b>).
     *
     * @param aBool  new value of the flag
     */
    inline void setUseFlag(bool aBool = true);

    /**
     * @brief Set parameter value.
     *
     * @param aVal  new value of the parameter
     */
    inline void setValue(char* aVal);

    /**
     * @brief Set new value.
     *
     * @param aVal  value to assign
     */
    inline void setNewValue(char* aVal);

    /**
     * @brief Add an argument to the argument list.
     *
     * @param anArg  argument to be added
     */
    inline void addArgument(char* anArg);

    //@}


    /**@name Display */
    //       =======
    //@{

    /**
     * @brief Display information about the parameter on standard output.
     *
     * @param anEndl
     */
    void printGUI(bool anEndl) const;

    /**
     * @brief Display usage message on standard output.
     */
    void showUsage() const;

    //@}

    // ---------------------------------
    // P R O T E C T E D   M E M B E R S
    // ---------------------------------
  protected:

    /** @name Parameter features */
    //       ==================
    //@{

    /**
     * @brief Parameter name.
     */
    const char* _name;

    /**
     * @brief Parameter description.
     */
    const char* _description;

    /**
     * @brief Flag...
     */
    bool _useFlag;

    /**
     * @brief Parameter status.
     */
    QGEparamStatus _paramStatus;

    /**
     * @brief Parameter type.
     */
    QGEparamType _paramType;

    /**
     * @brief File extension.
     */
    const char* _extension;

    //@}


    /** @name Parameter values */
    //       ================
    //@{

    /**
     * @brief Parameter default value.
     */
    const char* _default;

    /**
     * @brief Parameter value.
     */
    char* _value;
    
    /**
     * @brief Parameter new value.
     */
    bool _newValue;

    /**
     * @brief Parameter arguments.
     */
    vector<char*> _args;

    //@}

  }; // inner class QgarParam

/*-------------------------------------------------------------------*
 |                                                                   |
 |          E N D    O F   I N N E R   C L A S S   QgarParam         |
 |                                                                   |
 *-------------------------------------------------------------------*/




// -------------------------------------------------------------------
// P U B L I C   M E M B E R S
// -------------------------------------------------------------------
public:


  /**@name Constructors */
  //       ============
  //@{

  /**
   * @brief Default constructor.
   */
  QgarArgs();

  //@}


  /** @name Destructor */
  //       ==========
  //@{

  /**
   * @brief Non-virtual destructor
   */
  ~QgarArgs();

  //@}


  /** @name Command line */
  //       ============
  //@{

  /**
   * @brief Analyze the command line.
   */
  void analyzeLine(int argc, char* argv[]);

  //@}


  /** @name Predicates */
  //       ==========
  //@{

  /**
   * @brief Is given flag set?
   */
  bool isOptionSet(const char* aFlag) const;

  /**
   * @brief Does the client have to exit the application?
   *
   * The client has to exit if the application has been launched
   * with either a <b>-h</b> flag (help) or a <b>-gui</b> flag
   * (get application parameters).
   */
  inline bool isExit() const;
  
  /**
   * @brief Is there an error in the command line?
   */
  inline bool isError() const;

  /**
   * @brief Is the application in interactive mode?
   */
  inline bool isInteractive() const;

  //@}


  /** @name Access */
  //       ======
  //@{

  /**
   * @brief Get the string associated with a parameter.
   *
   * @param aFlag     flag introducing the parameter
   * @param aSpecial
   *
   * @warning If the parameter is optional, check first that
   * the parameter is set, using function qgar::QgarArgs::isOptionSet.
   */
  const char* getStringOption (const char* aFlag, bool aSpecial) const;

  /**
   * @brief Get the number of strings (representing values)
   * associated with a multi-valued parameter.
   *
   * @param aFlag  flag introducing the parameter
   */
  int getNumberOptions(const char* aFlag) const;

  /**
   * @brief Get string index associated with a multi-valued parameter.
   *
   * @param aFlag  flag introducing the parameter
   * @param anIdx  index
   */
  const char* getStringOptionMulti(const char* aFlag, int anIdx) const;

  /**
   * @brief Get the parameter description (null pointer if none).
   */
  QgarParam* findParam(const char* aParam) const;

  //@}


  /**@name Transformation */
  //       ==============
  //@{

  /**
   * @brief Declare global information about the parameter.
   */
  void setDescription(const char* aDescription, QGEfileType aFileType);

  /**
   * @brief Declare a parameter.
   * 
   * This method must be called for each supported parameter.
   *	
   * If the parameter is an output file, its name is the concatenation
   * of the name of the input file (without its extension) and of
   * argument <b>anExtension</b>.
   *
   * If the parameter is not an output file, its default value may be given
   * by argument <b>aDefault</b>.
   *
   * If the parameter status is qgar::QgarArgs::SINGLEFLAG, the corresponding
   * type must be qgar::QgarArgs::BOOL.
   *
   * @param aParamName    parameter name, first character is a minus (e.g. <b>-f</b>)
   * @param aParamStatus  parameter status (see enum type qgar::QgarArgs::ParamStatus)
   * @param aParamType    parameter type (see enum type qgar::QgarArgs::ParamType)
   * @param aDescription  short description of the parameter
   * @param anExtension   file extension, in case of an output file
   * @param aDefault      default value (given as a string) for a parameter
   *                      which is not a file
   */
  void addParameter(const char* aParamName,
		    QGEparamStatus aParamStatus,
		    QGEparamType aParamType,
		    const char* aDescription,
		    const char* anExtension = 0,
		    const char* aDefault = 0);

  /**
   * @brief Declare the number of messages which will be displayed
   * during the execution of the corresponding application.
   *
   * @warning This function must be called before displaying the first
   * message, to allow the progress bar to be correctly managed.
   */
  inline void setNumberOfMessages(int aCnt);

  /**
   * @brief Set the parameter value.
   *
   * @param aFlag  flag introducing the parameter
   * @param aVal   value to assign
   */
  void setParamValue(char* aFlag, char* aVal);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**@name Application features */
  //       ====================
  //@{

  /**
   * @brief Application parameters
   */
  list<QgarParam*> _args;

  /**
   * @brief File type.
   */
  QGEfileType _fileType;

  /**
   * @brief Application description.
   */
  char* _description;

  /**
   * @brief Exit/do not exit the application.
   */
  bool _exit;

  /**
   * @brief Error/no error in the command line.
   */
  bool _error;

  /**
   * @brief Interactive/non-interactive application.
   */
  bool _interactive;

  //@}


  /**@name Display */
  //       =======
  //@{

  /**
  * @brief Dispaly parameters.
  */
  void printGUI() const;
  
  /**
   * @brief Display usage message.
   * @param aCommand
   */
  void showUsage(const char* aCommand) const;

  //@}


// -------------------------------------------------------------------
}; // class QgarArgs




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII



/*-------------------------------------------------------------------*
 |                 I N N E R   C L A S S   QgarParam                 |
 *-------------------------------------------------------------------*/


// ======
// Access
// ======


// GET THE PARAMETER STATUS

inline QgarArgs::QGEparamStatus
QgarArgs::QgarParam::paramStatus() const
{
  return _paramStatus;
}


// GET FLAG FOR USE

inline bool
QgarArgs::QgarParam::useFlag() const
{
  return _useFlag;
}


// GET PARAMETER NAME

inline const char*
QgarArgs::QgarParam::name() const
{
  return _name;
}


// GET PARAMETER NUMBER

inline int
QgarArgs::QgarParam::numbOptions() const
{
  return _args.size();
}


// GET INDEXED ARGUMENT

inline const char* 
QgarArgs::QgarParam::argument(int anIdx)
{
  return _args[anIdx];
}


// GET PARAMETER DESCRIPTION

inline const char*
QgarArgs::QgarParam::description() const
{
  return _description;
}


// GET NEW VALUE

inline bool 
QgarArgs::QgarParam::newValue() const
{
  return _newValue;
}


// ==============
// TRANSFORMATION
// ==============


// SET FLAG FOR USE (DEFAULT 'true')

inline void
QgarArgs::QgarParam::setUseFlag(bool aBool)
{
  _useFlag = aBool;
}


// SET PARAMETER VALUE

inline void
QgarArgs::QgarParam::setValue(char* aVal)
{
  _value = aVal;
}


// SET NEW VALUE

inline void
QgarArgs::QgarParam::setNewValue(char* aVal)
{
  _newValue = true;
  setValue(aVal);
}


// ADD AN ARGUMENT TO THE ARGUMENT LIST

inline void
QgarArgs::QgarParam::addArgument(char* anArg)
{
  _args.push_back(anArg);
}




/*-------------------------------------------------------------------*
 |                        C L A S S   QgarArgs                       |
 *-------------------------------------------------------------------*/


// ==========
// PREDICATES
// ==========


// DOES THE CLIENT HAVE TO EXIT THE APPLICATION?

inline bool
QgarArgs::isExit() const
{
  return _exit;
}
  

// IS THERE AN ERROR IN THE COMMAND LINE?

inline bool
QgarArgs::isError() const
{
  return _error;
}


// IS THE APPLICATION IN INTERACTIVE MODE?

inline bool
QgarArgs::isInteractive() const
{
  return _interactive;
}


// ==============
// TRANSFORMATION
// ==============


// Set the number of messages

inline void
QgarArgs::setNumberOfMessages(int aCnt)
{
  cout << aCnt
       << endl;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

} // namespace qgar


#endif /* __QGARARGS_H_INCLUDED__ */
