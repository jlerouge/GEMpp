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
 * @file QgarApp.cpp
 *
 * @brief Implementation of class qgar::QgarApp.
 *
 * See file QgarApp.h for the interface.
 *
 *
 * @author   <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Yvan Norsa">Yvan Norsa</a>
 * @date     July 25, 2002  11:34
 * @since    Qgar 2.0
 */



// STD
#include <cstring>
#include <iostream>
// Qgar
#include "QgarApp.h"
#include "QgarArgs.h"



using namespace std;



namespace qgar
{


// -------------------------------------------------------------------
// T E R M I N A T I O N    C O D E S    ( S T A T I C )
// -------------------------------------------------------------------


// VALUE TO BE RETURNED BY AN APPLICATION WHICH NORMALLY TERMINATES

const unsigned char
QgarApp::_CODE_END   = 100;


// VALUE TO BE RETURNED BY AN APPLICATION INVOKED WITH FLAG '-gui'

const unsigned char
QgarApp::_CODE_GUI   = 101;
    

// VALUE TO BE RETURNED BY AN APPLICATION WHICH ABNORMALLY TERMINATES

const unsigned char
QgarApp::_CODE_ERROR = 200;


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

QgarApp::QgarApp()
  
  : _exit(false),
    _action(QGE_ACTION_NONE),
    _actionCnt(0)
  
{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


// VIRTUAL DESTRUCTOR

QgarApp::~QgarApp()
{
  // VOID
}


// -------------------------------------------------------------------
// T H E   C O M M A N D   L I N E
// -------------------------------------------------------------------


// GET NEXT WORD OF COMMAND LINE (BLANK SPACE AS SEPARATOR)

char*
QgarApp::nextWord(char* aComLine, int* anIdx)
{
  int idx;

  for(idx = *anIdx ; idx < (int)strlen(aComLine) ; ++idx)
    {
      if(aComLine[idx] == ' ')
	{
	  break;
	}
    }

  char* res = new char[idx - (*anIdx) + 1];

  int kdx = 0;

  for(int jdx = (*anIdx); jdx < idx; ++jdx, ++kdx)
    {
      res[kdx] = aComLine[jdx];
    }
  res[kdx + 1] = '\0';

  (*anIdx) = idx + 1;

  return(res);
}


// -------------------------------------------------------------------
// I N P U T
// -------------------------------------------------------------------


// READ ON STANDARD INPUT

void 
QgarApp::nextCommand()
{
  char command[64];  
  cin.getline(command, 64, '\n');

  if(strcmp(command, "EXIT") == 0)
    {
      _exit = true;
      return;
    }

  int * pos2 = new int();
  *pos2 = 0;
  
  char * cmd = nextWord(command, pos2);

  if(strcmp(cmd, "SET") == 0)
    {
      _action = QGE_ACTION_SET;
    }
  else
    {
      return;
    }

  // Looking for a variable name
  while(*pos2 < (int)strlen(command))
    {
      char * target = nextWord(command, pos2);

      list<string>::iterator it;

      bool ok = false;

      for (it = _paramNameTab.begin(); it != _paramNameTab.end(); ++it)
	{
	  const char * tmp2 = (*it).c_str();
	  char * tmp = new char[strlen(tmp2) + 1];
      
	  int i = 1;
	  int j;
      
	  for(j = 0; j < (int)strlen(tmp2); ++j)
	    {
	      tmp[j] = tmp2[i];
	      ++i;
	    }

	  tmp[j] = '\0';
      
	  if(strcmp(tmp, target) == 0)
	    {
	      ok = true;
	      break;
	    }
	  delete[] tmp;
	}
            
      if(!ok)
	{
	  return;
	}

      char* value = nextWord(command, pos2);

      _value = value;
      setValue(target, value);

      if(_action == QGE_ACTION_SET)
	{
	  ++_actionCnt;
	}
    } // END while
}


// HAS a "SET <name> <value>" COMMAND BEEN READ?

bool 
QgarApp::newValue(const char* aName)
{
  if(_action == QGE_ACTION_SET)
    {
      string tmp("-");
      tmp += aName;
    
      QgarArgs::QgarParam* param = _args.findParam(tmp.c_str());
      
      if(param != 0)
	{
	  return(param->newValue());
	}
    }
  
  return false;
}


// -------------------------------------------------------------------
// T H E   P A R A M E T E R S
// -------------------------------------------------------------------


// DECLARE A PARAMETER SUPPORTED BY AN APPLICATION

void
QgarApp::addParameter(const char* aParamName,
		      QgarArgs::QGEparamStatus aParamStatus,
		      QgarArgs::QGEparamType aParamType,
		      const char* aDescription,
		      const char* anExtension,
		      const char* aDefault)
{
  if((aParamType >= QgarArgs::INT) && (aParamType <= QgarArgs::BOOL))
    {
      _paramNameTab.push_back(string(aParamName));
    }

  _args.addParameter(aParamName,
		     aParamStatus,
		     aParamType,
		     aDescription,
		     anExtension,
		     aDefault);
}


// GET THE STRING ASSOCIATED WITH A PARAMETER

const char*
QgarApp::getStringOption (const char* aFlag)
{
  bool special = false;
    
  int size = (int)strlen(aFlag);
  char* tmp = new char[size+1];

  int idx;

  for(idx = 0; idx < size; ++idx)
    {
      tmp[idx] = aFlag[idx];
    }

  tmp[idx] = '\0';

  char* _flag = new char[strlen(tmp)];

  int jdx = 0;

  for(idx = 1; idx < (int)strlen(tmp); ++idx)
    {
      _flag[jdx] = tmp[idx];
      ++jdx;
    }
  _flag[jdx] = '\0';
    
  if(_action == QGE_ACTION_SET)
    {
      if(_actionCnt > 0)
	{
	  --_actionCnt;
	}
      else
	{
	  _action = QGE_ACTION_NONE;
	}
      
      special = true;           
    }
    
  const char* res = _args.getStringOption(aFlag, special);
  
  delete [] tmp;
  delete [] _flag;

  return(res);
}
   

// -------------------------------------------------------------------
// DIALOG WITH THE QgarGui USER INTERFACE
// -------------------------------------------------------------------


// DISPLAY A DIALOG TO CHANGE PARAMETER VALUES

void
QgarApp::showDialog()
{
  cout << "Show slider";

  list<string>::iterator it;

  // Display the list of every modifiable parameter

  for (it = _paramNameTab.begin(); it != _paramNameTab.end(); ++it)
    {
      cout << ' ';
      QgarArgs::QgarParam* param = _args.findParam(it->c_str());
      param->printGUI(false);
    }

  cout << endl;
}


// -------------------------------------------------------------------


} // namespace qgar
