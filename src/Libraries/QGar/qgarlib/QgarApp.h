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


#ifndef __QGARAPP_H_INCLUDED__
#define __QGARAPP_H_INCLUDED__


/**
 * @file    QgarApp.h
 * @brief   Header file of class qgar::QgarApp.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Yvan Norsa">Yvan Norsa</a>
 * @date    July 25, 2002  12:52
 * @since   Qgar 1.0
 */



// STD
#include <cstring>
#include <iostream>
// QGAR
#include "QgarArgs.h"



using namespace std;



namespace qgar
{

/** 
 * @ingroup APP
 *
 * @class QgarApp QgarApp.h "qgarlib/QgarApp.h"
 *
 * @brief To handle parameters and interactive mode of an application. 
 *
 * It is based on class qgar::QgarArgs.
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
 * @todo Complete and update documentation
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Yvan Norsa">Yvan Norsa</a>
 * @date    July 25, 2002  12:52
 * @since   Qgar 1.0
 */

class QgarApp
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
   */
  QgarApp();

  //@}


  /**@name Destructor */
  //       ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~QgarApp();

  //@}


  /**@name The application */
  //       ===============
  //@{

  /**
   * @brief Set application description.
   *
   * @param aDescription  application description
   * @param aFileType     type of the source file
   */
  inline void setDescription(const char* aDescription,
			     QgarArgs::QGEfileType aFileType);

  /**
   * @brief Does the client have to exit the application?
   *
   * The client has to exit if the application has been launched
   * with either a <b>-h</b> flag (help) or a <b>-gui</b> flag
   * (get application parameters).
   */
  inline bool isExit() const;
    
  /**
   * @brief Is the application in interactive mode?
   */
  inline bool isInteractive() const;
   
  /**
   * @brief Does the application have to exit?
   */
  inline bool exit() const;

  //@}


  /**@name The command line */
  //       ================
  //@{

  /**
   * @brief Analyze the command line.
   *
   * @param argc  number of arguments
   * @param argv  the full command line
   */
  inline void analyzeLine(int argc, char* argv[]);

  /**
   * @brief Get next word of command line (blank space as separator).
   *
   * @param aComLine  number of arguments
   * @param anIdx     current index in line
   */
  char* nextWord(char* aComLine, int* anIdx);

  /**
   * @brief Is there an error in the command line?
   */
  inline bool isError() const;

  //@}


  /**@name Termination codes */
  //       =================
  //@{

  /**
   * @brief Value to be returned by an application
   *   which normally terminates.
   */
  static const unsigned char _CODE_END;

  /**
   * @brief Value to be returned by an application invoked
   *   with flag <b>-gui</b>.
   */
  static const unsigned char _CODE_GUI;

  /**
   * @brief Value to be returned by an application
   *   which abnormally terminates.
   */
  static const unsigned char _CODE_ERROR;

  //@}


  /**@name Input */
  //       =====
  //@{

  /**
   * @brief Read on standard input.
   */
  void nextCommand();

  /**
   * @brief Has a <b>SET *name* *value*</b> command been read?
   * @param aName
   */
  bool newValue(const char* aName); 

  //@}


  /**@name The parameters */
  //       ==============
  //@{

  /**
   * @brief Declare a parameter supported by an application.
   *
   * This method must be called for each supported parameter.
   *	
   * If a parameter is an output file, its name is the concatenation
   * of the name of the input file (without its extension) and of
   * argument <b>anExtension</b>.
   *
   * If a parameter is not an output file, its default value may be given
   * by argument <b>aDefault</b>.
   *
   * If the parameter status is qgar::QgarArgs::SINGLEFLAG, the corresponding
   * type must be qgar::QgarArgs::BOOL.
   *
   * @param aParamName    parameter name, first character must be '<b>-</b>'
   * @param aParamStatus  parameter status (see enum type qgar::QgarArgs::ParamStatus)
   * @param aParamType    parameter type (see enum type qgar::QgarArgs::ParamType)
   * @param aDescription  short description of the parameter
   * @param anExtension   file extension, in case of an output file
   * @param aDefault      default value (given as a string) for a parameter
   *                      which is not a file
   *
   * @see class qgar::QgarArgs
   */
  void addParameter(const char* aParamName,
		    QgarArgs::QGEparamStatus aParamStatus,
		    QgarArgs::QGEparamType aParamType,
		    const char* aDescription,
		    const char* anExtension = 0,
		    const char* aDefault = 0);    

  /**
   * @brief Is an optional parameter set?
   *
   * @param aFlag  flag introducing the parameter
   */
  bool isOptionSet(const char* aFlag) const;

  /**
   * @brief Get the string associated with a parameter.
   *
   * @param aFlag  flag introducing the parameter
   *
   * @warning If the parameter is optional, check first that
   * the parameter is set, using function qgar::QgarApp::isOptionSet.
   *
   * @todo The code of the function is very strange,
   * and it surely has to be refactored!
   */
  const char* getStringOption (const char* aFlag);

  /**
   * @brief Set a parameter value.
   *
   * @param aFlag  flag introducing the parameter
   * @param aVal   value to assign
   */
  inline void setValue(char* aFlag, char* aVal);

  //@}


  /**@name The progress bar */
  //       ================
  //@{

  /**
   * @brief Display the progress bar.
   */
  inline void showProgressBar();

  /**
   * @brief Close the progress bar.
   */
  inline void closeProgressBar();

  /**
   * @brief Set progress bar to a given percentage.
   *
   * @param aPercentage  value between <b>0</b> and <b>100</b>
   */
  inline void setProgressBar(int aPercentage);

  //@}


  /**@name The dialog with the QgarGui user interface */
  //       ==========================================
  //@{

  /**
   * @brief Display an image.
   *
   * @param aFileName  name of the file including the image to be displayed
   */
  inline void showPicture(char* aFileName);

  /**
   * @brief Display the superimpose file.
   *
   * @param aFileName  a file name
   */
  inline void showSuperImpose(char* aFileName);

  /**
   * @brief Display a dialog to change parameter values.
   */
  void showDialog();

  //@}

// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**@name Type definitions */
  //       ================
  //@{

  /**
   * @brief Action types.
   */
  enum QGEaction
    {
      QGE_ACTION_NONE,
      QGE_ACTION_SET
    };

  //@}


  /**@name Information about parameters */
  //       ============================
  //@{

  /**
   * @brief Table of parameter names.
   */
  list<string> _paramNameTab;

  //@}


  /**@name Information about the application */
  //       =================================
  //@{

  /**
   * @brief Application arguments.
   */
  QgarArgs _args;

  /**
   * @brief Flag set if the application is about to end.
   */
  bool _exit;

  //@}


  /**@name Information about actions */
  //       =========================
  //@{

  /**
   * @brief Nature of the current command.
   */
  QGEaction _action;

  /**
   * @brief Parameter of the current command.
   */
  char* _value;

  /**
   * @brief Current number of processed actions.
   */
  int _actionCnt;

  //@}

// -------------------------------------------------------------------
}; // class QgarApp




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I N L I N E   F U N C T I O N S   I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// ===============
// THE APPLICATION
// ===============


// SET APPLICATION DESCRIPTION

inline void
QgarApp::setDescription(const char* aDescription,
			QgarArgs::QGEfileType aFileType)
{
  _args.setDescription(aDescription, aFileType);
}


// DOES THE CLIENT HAVE TO EXIT THE APPLICATION?

inline bool
QgarApp::isExit() const
{
  return _args.isExit();
}


// IS THE APPLICATION IN INTERACTIVE MODE?
inline bool
QgarApp::isInteractive() const
{
  return _args.isInteractive();
}
   

// DOES THE APPLICATION HAVE TO EXIT?

inline bool
QgarApp::exit() const
{
  return _exit;
}


// ================
// THE COMMAND LINE
// ================


// ANALYZE THE COMMAND LINE

inline void
QgarApp::analyzeLine(int argc, char* argv[])
{
  _args.analyzeLine(argc, argv);
}


// IS THERE AN ERROR IN THE COMMAND LINE?

inline bool
QgarApp::isError() const
{
  return _args.isError();
}


// ==============
// THE PARAMETERS
// ==============


// IS AN OPTIONAL PARAMETER SET?

inline bool
QgarApp::isOptionSet(const char* aFlag) const
{
  return _args.isOptionSet(aFlag);
}


// SET A PARAMETER NAME

inline void
QgarApp::setValue(char* aFlag, char* aVal)
{
  _args.setParamValue(aFlag, aVal);
}


// ================
// THE PROGRESS BAR
// ================


// DISPLAY THE PROGRESS BAR

void 
QgarApp::showProgressBar()
{
  cout << "Set progress bar ON"
       << endl;
}


// CLOSE THE PROGRESS BAR

void 
QgarApp::closeProgressBar()
{
  cout << "Set progress bar OFF"
       << endl;
}


// SET PROGRESS BAR TO A GIVEN PERCENTAGE

void 
QgarApp::setProgressBar(int aPercentage)
{
  cout << "Set progress bar "
       << aPercentage
       << endl;
}


// DISPLAY AN IMAGE

void
QgarApp::showPicture(char *aFileName)
{
  cout << "Show picture "
       << aFileName
       << endl;
}


// DISPLAY THE SUPERIMPOSE FILE

void 
QgarApp::showSuperImpose(char *aFileName)
{
  cout << "Show superimpose "
       << aFileName
       << endl;
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

} // namespace qgar


#endif /* __QGARAPP_H_INCLUDED__ */
