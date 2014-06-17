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
 * @file QgarArgs.cpp
 *
 * @brief Implementation of class qgar::QgarArgs.
 *
 * See file QgarArgs.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date   July 2, 2001  17:22
 * @since  Qgar 1.0
 */



// STD
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
// QGAR
#include "QgarArgs.h"
#include "QgarErrorUser.h"



using namespace std;
using namespace qgar;



namespace qgar
{


/*-------------------------------------------------------------------*
 |                                                                   |
 |                 I N N E R   C L A S S   QgarParam                 |
 |                                                                   |
 *-------------------------------------------------------------------*/


// ============
// CONSTRUCTORS
// ============

// DEFAULT CONSTRUCTOR

QgarArgs::QgarParam::QgarParam(const char* aParamName,
			       QGEparamStatus aParamStatus,
			       QGEparamType aParamType,
			       const char* aDescription,
			       const char* anExtension,
			       const char* aDefault)

  : _name(aParamName),
    _description(aDescription),
    _useFlag(false),
    _paramStatus(aParamStatus),
    _paramType(aParamType),
    _extension(anExtension),
    _default(aDefault),
    _value(0),
    _newValue(false)

{
  // VOID
}


// ======
// ACCESS
// ======


const char*
QgarArgs::QgarParam::value(bool aSpecial)
{
  if(aSpecial)
    {
      _newValue = false;
    }

  return _value;
}


// =======
// DISPLAY
// =======


// DISPLAY INFORMATION ABOUT THE PARAMETER ON STANDARD OUTPUT

void
QgarArgs::QgarParam::printGUI(bool anEndl) const
{
  cout << _name << ';'          // parameter flag
       << _description << ';';  // description

  // Parameter type
  switch(_paramType)
    {
    case INT:
      cout << "int";
      break;
    case FLOAT:
      cout << "float";
      break;
    case STRING:
      cout << "string";
      break;
    case BOOL:
      cout << "bool";
      break;
    case FILEIN:
      cout << "in";
      break;
    case FILEOUT:
      cout << "out";
      break;
    case FILEOUTD:
      cout << "outd";
      break;
    case FILEOUTDS:
      cout << "outds";
      break;
    case PATH:
      cout << "path";
      break;
    }
  cout << ';';

  // Required or optional
  if (_paramStatus == REQPARAM || _paramStatus == REQMULTIPARAM)
    {
      cout << 'R';
    }
  else
    {
      cout << 'O';
    }
  cout << ';';

  // Extension or default value, according to parameter type

  if (_paramType == INT ||
      _paramType == FLOAT ||
      _paramType == STRING ||
      _paramType == BOOL)
    {
      if (_default)
	{
	  cout << _default;
	}
    }
  else
    {
      if (_extension)
	{
	  cout << _extension;
	}
    }
  cout << ';';
  
  if(anEndl)
    {
      cout << endl;
    }
}



// DISPLAY USAGE MESSAGE ON STANDARD OUTPUT

void
QgarArgs::QgarParam::showUsage() const
{
    cout << _description           // parameter description
	 << ' ' << _name << " (";  // parameter name

    // Parameter type
    switch(_paramType)
      {
      case INT:
	cout << "int";
	break;
      case FLOAT:
	cout << "float";
	break;
      case STRING:
	cout << "string";
	break;
      case BOOL:
	cout << "bool";
	break;
      case FILEIN:
      case FILEOUT:
      case FILEOUTD:
      case FILEOUTDS:
	cout << "filename";
	break;
      case PATH:
	cout << "path";
	break;
      }  
    cout << ", ";

  // Parameter status
  if ((_paramStatus == REQPARAM) || (_paramStatus == REQMULTIPARAM))
    {
      cout << "Required";
    }
  else
    {
      cout << "Optional";
    }

  cout << ')' << endl;
}



/*-------------------------------------------------------------------*
 |                                                                   |
 |                        C L A S S   QgarArgs                       |
 |                                                                   |
 *-------------------------------------------------------------------*/



// ============
// CONSTRUCTORS
// ============


// DEFAULT CONSTRUCTOR

QgarArgs::QgarArgs()

  : _description(0),
    _exit(false),
    _error(false),
    _interactive(false)

{
  // VOID
}


// ==========
// DESTRUCTOR
// ==========


QgarArgs::~QgarArgs()
{
  list<QgarParam*>::iterator itP;

  for (itP = _args.begin(); itP != _args.end(); ++itP)
    {
      delete *itP;
    }

  if (_description)
    {
      delete [] _description;
    }
}


// ============
// COMMAND LINE
// ============


// ANALYZE THE COMMAND LINE

void
QgarArgs::analyzeLine(int argc, char * argv[])
{
  int i = 1;

  while (i < argc)
    {
      QgarParam* pParam = findParam(argv[i]);

      // If the parameter is not recognized, try flags -h and -gui

      if (!pParam)
	{
	  if (!strcmp("-h", argv[i]))
	    {
	      _exit = true;
	      showUsage(argv[0]);
	    }
	  else
	    {
	      if (!strcmp("-gui", argv[i]))
		{
		  _exit = true;
		  printGUI();
		}
	      else
		{
		  if (!strcmp("-interact", argv[i]))
		    {
		      _interactive = true;
		    }
		  else
		    {
		      _error = true;
		      cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
			   << ">>> Bad flag: " << argv[i] << endl;
		    }
		}
	    }

	  return;
	}

 
      switch (pParam->paramStatus())
	{
	  // --------------------------------------------------------
          case SINGLEFLAG:

	    pParam->setUseFlag();
	    break;

	  // --------------------------------------------------------
	  case REQPARAM:
  	  case OPTPARAM:

	    ++i;

	    if (i == argc)
	      {
		_error = true;
		cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
		     << ">>> No value for flag "	<< argv[i-1] << endl;
		return;
	      }
      
	    if (findParam(argv[i]))
	      {
		_error = true;
		cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
		     << ">>> Bad value for flag " << argv[i - 1] << ": "
		     << argv[i] << endl;
		return;
	      }
      
	  pParam->setValue(argv[i]);
	  pParam->setUseFlag();
	  break;

	  // --------------------------------------------------------
	  case REQMULTIPARAM:
	  case OPTMULTIPARAM:

	    ++i;

	    if (i == argc)
	      {
		_error = true;
		cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
		     << ">>> No value for flag " << argv[i-1] << endl;
		return;
	      }
      
	    if (findParam(argv[i]))
	      {
		_error = true;
		cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
		     << ">>> Bad value for flag " << argv[i - 1] << ": "
		     << argv[i] << endl;
		return;
	      }

	    do
	      {
		pParam->addArgument(argv[i]);
		++i;
	      }
	    while ((i < argc) && (findParam(argv[i])));

	    pParam->setUseFlag();
	    --i;
	    break;

	  // --------------------------------------------------------
	} // END switch
    
      // Next argument
      ++i;

    } // END while


  // All the arguments are processed
  // Check required parameters
  
  for (list<QgarParam*>::iterator it = _args.begin();
       it != _args.end();
       ++it)
    {
      if ((((*it)->paramStatus() == REQPARAM) || ((*it)->paramStatus() == REQMULTIPARAM))
	  && !((*it)->useFlag()))
	{
	  _error = true;
	  cerr << "QGAR: ERROR NOTIFIED BY AN APPLICATION" << endl
	       << ">>> Missing flag: " << (*it)->name() << endl;
	  return;
	}
    }
}


// ==========
// PREDICATES
// ==========


// IS GIVEN FLAG SET?

bool
QgarArgs::isOptionSet(const char *aFlag) const
{
  QgarParam* pParam = findParam(aFlag);

  // The parameter must be declared
  if (pParam == 0)
    {
      ostringstream os;
      os << "Unknown flag: "
         << aFlag;
      throw QgarErrorUser(__FILE__, __LINE__,
			  "bool qgar::QgarArgs::isOptionSet(const char*) const",
			  os.str());
    }

  // The flag must be optional
  if ((pParam->paramStatus() != SINGLEFLAG) &&
      (pParam->paramStatus() != OPTPARAM)   &&
      (pParam->paramStatus() != OPTMULTIPARAM))
    {
      ostringstream os;
      os << "Flag "
         << aFlag
	 << " should be optional.";
      throw QgarErrorUser(__FILE__, __LINE__,
			  "bool qgar::QgarArgs::isOptionSet(const char*) const",
			  os.str());
    }

  return pParam->useFlag();
}


// ======
// ACCESS
// ======


// GET THE STRING ASSOCIATED WITH A PARAMETER

const char*
QgarArgs::getStringOption(const char* aFlag, bool aSpecial) const
{
  QgarParam* pParam = findParam(aFlag);

  // The parameter must be declared
  if (pParam == 0)
    {
      ostringstream os;
      os << "Unknown flag: "
         << aFlag;
      throw QgarErrorUser(__FILE__, __LINE__,
			  "const char* qgar::QgarArgs::getStringOption(const char*, bool) const",
			  os.str());
    }

  // The flag must match a single parameter
  if ((pParam->paramStatus() != OPTPARAM) && (pParam->paramStatus() != REQPARAM))
    {
      ostringstream os;
      os << "Flag "
         << aFlag
	 << " should match a single parameter.";
      throw QgarErrorUser(__FILE__, __LINE__,
			  "const char* qgar::QgarArgs::getStringOption(const char*, bool) const",
			  os.str());
    }

  return pParam->value(aSpecial);
}


// GET THE NUMBER OF STRINGS

int
QgarArgs::getNumberOptions(const char* aFlag) const
{
  QgarParam* pParam = findParam(aFlag);

  // The parameter must be declared
  if (pParam == 0)
    {
      ostringstream os;
      os << "Unknown flag: "
         << aFlag;
      throw QgarErrorUser(__FILE__, __LINE__,
			  "int qgar::QgarArgs::getNumberOptions(const char*) const",
			  os.str());
    }

  // The flag must match a multi-valued parameter
  if ((pParam->paramStatus() != OPTMULTIPARAM) && (pParam->paramStatus() != REQMULTIPARAM))
    {
      ostringstream os;
      os << "Flag "
         << aFlag
	 << " should match a multi-valued parameter.";
      throw QgarErrorUser(__FILE__, __LINE__,
			  "int qgar::QgarArgs::getNumberOptions(const char*) const",
			  os.str());
    }

  return pParam->numbOptions();
}


// GET STRING INDEX ASSOCIATED WITH A MULTI-VALUED PARAMETER

const char*
QgarArgs::getStringOptionMulti (const char* aFlag, int anIdx) const
{
  QgarParam* pParam = findParam(aFlag);

  // The parameter must be declared
  if (pParam == 0)
    {
      ostringstream os;
      os << "Unknown flag: "
         << aFlag;
      throw QgarErrorUser(__FILE__, __LINE__,
			  "const char* qgar::QgarArgs::getStringOptionMulti (const char*, int) const",
			  os.str());
    }

  // The flag must match a multi-valued parameter and a valid index
  if (   ( (pParam->paramStatus() != OPTMULTIPARAM) &&
	   (pParam->paramStatus() != REQMULTIPARAM)    )
      ||
	 (anIdx > pParam->numbOptions()))
    {
      ostringstream os;
      os << "Flag "
         << aFlag
	 << " should match a multi-valued parameter and a valid index.";
      throw QgarErrorUser(__FILE__, __LINE__,
			  "const char* qgar::QgarArgs::getStringOptionMulti (const char*, int) const",
			  os.str());
    }

  return pParam->argument(anIdx);
}


// GET THE PARAMETER DESCRIPTION

QgarArgs::QgarParam*
QgarArgs::findParam(const char* aParam) const
{
  list<QgarParam*>::const_iterator it;
  bool found = false;
  
  for (it = _args.begin(); it != _args.end(); ++it)
    {
      if (!strcmp(aParam, (*it)->name()))
	{
	  found = true;
	  break;
	}
    }

  return (found) ? (*it) : 0;
}


// ==============
// TRANSFORMATION
// ==============


// DECLARE GLOBAL INFORMATION ABOUT THE PARAMETER

void
QgarArgs::setDescription(const char* aDescription,
			 QGEfileType aFileType)
{
  _fileType = aFileType;

  _description = new char[strlen(aDescription) + 1];
  strcpy(_description, aDescription);
}


// DECLARE A PARAMETER

void
QgarArgs::addParameter(const char* aParamName,
		       QGEparamStatus aParamStatus,
		       QGEparamType aParamType,
		       const char* aDescription,
		       const char* anExtension,
		       const char* aDefault)
{
  _args.push_back(new QgarParam(aParamName,
				aParamStatus,
				aParamType,
				aDescription,
				anExtension,
				aDefault));
}


// SET THE PARAMETER VALUE

void 
QgarArgs::setParamValue(char* aFlag, char* aVal)
{
  string tmp("-");
  tmp += aFlag;

  QgarParam* pParam = findParam(tmp.c_str());

  if (pParam == 0)
    {
      ostringstream os;
      os << "Unknown flag: "
         << aFlag;
      throw QgarErrorUser(__FILE__, __LINE__,
			  "void qgar::QgarArgs::setParamValue(char*, char*)",
			  os.str());
    }

  pParam->setNewValue(aVal);
}


// ===================
// DISPLAY (protected)
// ===================


// DISPALY PARAMETERS

void
QgarArgs::printGUI() const
{
  // Source file type and description must be set
  if (_description == 0)
    {
      throw QgarErrorUser(__FILE__, __LINE__,
			  "void qgar::QgarArgs::printGUI()",
			  "The description of the application is not available.");
    }


  // The type of the expected source file
  switch(_fileType)
    {
      case PPM:
	cout << "PPM";
	break;
      case PGM:
	cout << "PGM";
	break;
      case PBM:
	cout << "PBM";
	break;
      case DXF:
	cout << "DXF";
	break;
    }
  cout << endl;

  // The description of the application (menu entry in GUI)
  cout << _description << endl;

  // A line for each of the parameter
  for (list<QgarParam*>::const_iterator it = _args.begin();
       it != _args.end() ;
       ++it)
    {
      (*it)->printGUI(true);
    }
}


// DISPLAY USAGE MESSAGE

void
QgarArgs::showUsage(const char* aCommand) const
{
  cout << "QGAR: USAGE FOR APPLICATION " << aCommand << ": "
       << _description << endl
       << ">>> Parameters:" << endl;

  for (list<QgarParam*>::const_iterator it = _args.begin();
       it != _args.end() ;
       ++it)
    {
      (*it)->showUsage();
    }
}


/*-------------------------------------------------------------------*
 |                                                                   |
 *-------------------------------------------------------------------*/


} // namespace qgar
