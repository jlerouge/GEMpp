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
 * @file  QgarAppDescr.cpp
 * @brief Implementation of class qgar::QgarAppDescr.
 *
 *        See file QgarAppDescr.h for the interface.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 14, 2003  15:29
 * @since  Qgar
 */



// STD
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
// QGAR
#include "QgarAppDescr.h"
#include "QgarErrorDeveloper.h"
#include "QgarErrorUser.h"
#include "stl.h"
#include "sax/Attributes.h"
#include "sax/SAXParseException.h"
#include "sax/XMLReader.h"
#include "sax/XMLReaderFactory.h"



using namespace std;
using namespace qgxml;



// ---------------------------------------------------------------------
// S T A T I C   M E M B E R   I N I T
// ---------------------------------------------------------------------

namespace qgar {

const char* const QgarAppDescr::ELT_APPLICATION   = "application";
const char* const QgarAppDescr::ELT_DESCR         = "descr";
const char* const QgarAppDescr::ELT_DOCUMENTATION = "documentation";
const char* const QgarAppDescr::ELT_PARAMLIST     = "paramlist";
const char* const QgarAppDescr::ELT_PARAM         = "param";
const char* const QgarAppDescr::ELT_NAME          = "name";
const char* const QgarAppDescr::ELT_AUTHOR        = "author";
const char* const QgarAppDescr::ELT_COPYRIGHT     = "copyright";
const char* const QgarAppDescr::ELT_DOC           = "doc";
const char* const QgarAppDescr::ELT_BRIEF         = "brief";
const char* const QgarAppDescr::ELT_LONG          = "long";

const char* const QgarAppDescr::ATT_REVISION     = "revision";
const char* const QgarAppDescr::ATT_LANG         = "lang";
const char* const QgarAppDescr::ATT_NAME         = "name";
const char* const QgarAppDescr::ATT_FLAG         = "flag";
const char* const QgarAppDescr::ATT_REQUIRED     = "required";
const char* const QgarAppDescr::ATT_PASSING_MODE = "passing-mode";
const char* const QgarAppDescr::ATT_FORMAT       = "format";
const char* const QgarAppDescr::ATT_TYPE         = "type";



// ---------------------------------------------------------------------
// C O N S T R U C T O R S
// ---------------------------------------------------------------------

// Default constructor
QgarAppDescr::QgarAppDescr(const char* const filename)



    : _parseData(0)

{
    ifstream stream(filename);
    init(InputSource(stream));
}

// ---------------------------------------------------------------------

QgarAppDescr::QgarAppDescr(const std::string& filename)



    : _parseData(0)

{
    ifstream stream(filename.c_str());
    init(InputSource(stream));
}

// ---------------------------------------------------------------------

QgarAppDescr::QgarAppDescr(std::istream& stream)



    : _parseData(0)

{
    init(InputSource(stream));
}

// ---------------------------------------------------------------------

QgarAppDescr::QgarAppDescr(const std::string& name,
                           const std::string& copyright,
                           const std::string& briefDoc,
                           const std::string& longDoc,
                           const std::vector<QgarAppParamDescr *>& pVect)
    : _name(name),
      _copyright(copyright),
      _briefDoc(briefDoc),
      _longDoc(longDoc),
      _parseData(0)
{

    // Duplicate parameters vector

    transform(pVect.begin(),
              pVect.end(),
              back_inserter(_paramVect),
              qstlCloneObject());
}

// ---------------------------------------------------------------------

// Copy constructor
QgarAppDescr::QgarAppDescr(const QgarAppDescr& rhs)

    : _name(rhs._name),
      _copyright(rhs._copyright),
      _briefDoc(rhs._briefDoc),
      _longDoc(rhs._longDoc)
{

    // Duplicate parsing data if any
    _parseData = (rhs._parseData)? new ParseData(*rhs._parseData) : 0;

    // Duplicate parameters vector
    _paramVect.reserve(rhs._paramVect.size());

    transform(rhs._paramVect.begin(),
              rhs._paramVect.end(),
              back_inserter(_paramVect),
              qstlCloneObject());
}



// ---------------------------------------------------------------------
// D E S T R U C T O R
// ---------------------------------------------------------------------

QgarAppDescr::~QgarAppDescr()
{

    for_each(_paramVect.begin(), _paramVect.end(), qstlDeleteObject());

    delete _parseData;
}



// ---------------------------------------------------------------------
// M E T H O D S
// ---------------------------------------------------------------------

void
QgarAppDescr::addParamDescr(QgarAppParamDescr* descr)
{
    _paramVect.push_back(new QgarAppParamDescr(*descr));
}

// ---------------------------------------------------------------------

string
QgarAppDescr::toXml() const
{
    throw QgarErrorDeveloper(__FILE__, __LINE__,
                             "std::string qgar::QgarAppDescr::toXml() const",
                             "Function not yet implemented!");

    return string();
}

// ---------------------------------------------------------------------

void
QgarAppDescr::init(InputSource source)

{
    // Create parse data structure
    _parseData = new ParseData();

    // Parse input source

    // Parse
    XMLReader* parser = XMLReaderFactory::createXMLReader();
    parser->setContentHandler(this);
    parser->parse(source);

    // Clean-up
    delete _parseData;
    _parseData = 0;
    delete parser;
}



// ---------------------------------------------------------------------
// D E F A U L T H A N D L E R   R E D E F I N I T I O N
// ---------------------------------------------------------------------

void 
QgarAppDescr::characters(const char* ch, 
                         const unsigned int start,
                         const unsigned int length)
{
    Q_UNUSED(start);
    Q_UNUSED(length);
    // Append parsed data to the buffer.
    _parseData->buffer += string(ch);
}

// ---------------------------------------------------------------------

void 
QgarAppDescr::startElement(const std::string& uri,
                           const std::string& localName,
                           const std::string& qName,
                           const Attributes& atts)
{
    Q_UNUSED(uri);
    Q_UNUSED(qName);
    // Check if document is really an application description

    if ((_parseData->firstElt) && (localName != "application"))
    {
        throw QgarErrorUser(__FILE__, __LINE__,
                            "void qgar::startElement(const std::string&, const std::string&,const std::string&, const qgxml::Attributes&)",
                            "Invalid document type.");
    }
    else
    {
        _parseData->firstElt = false;
    }


    // Reset buffer

    _parseData->buffer = "";


    // Redirect action on the function matching the tag.

    if (localName == ELT_PARAM)
    {
        startParam(atts);
    }
}

// ---------------------------------------------------------------------

void 
QgarAppDescr::endElement(const std::string& uri, 
                         const std::string& localName,
                         const std::string& qName)
{
    Q_UNUSED(uri);
    Q_UNUSED(qName);
    // Redirect action on the function matching the tag.

    if (localName == ELT_PARAM)
    {
        endParam();
    }
    else if (localName == ELT_NAME)
    {
        endName();
    }
    else if (localName == ELT_AUTHOR)
    {
        endAuthor();
    }
    else if (localName == ELT_COPYRIGHT)
    {
        endCopyright();
    }
    else if (localName == ELT_BRIEF)
    {
        endBrief();
    }
    else if (localName == ELT_LONG)
    {
        endLong();
    }
}

// ---------------------------------------------------------------------

void
QgarAppDescr::fatalError(const SAXParseException& exception)
{
    throw runtime_error(exception.getMessage());
}

// ---------------------------------------------------------------------
// A C C E S S
// ---------------------------------------------------------------------

std::string
QgarAppDescr::name() const
{
    return _name;
}

// ---------------------------------------------------------------------

std::string
QgarAppDescr::author() const
{
    return _author;
}

// ---------------------------------------------------------------------
std::string
QgarAppDescr::copyright() const
{
    return _copyright;
}

// ---------------------------------------------------------------------

std::string
QgarAppDescr::briefDoc() const
{
    return _briefDoc;
}

// ---------------------------------------------------------------------

std::string
QgarAppDescr::longDoc() const
{
    return _longDoc;
}

// ---------------------------------------------------------------------

std::vector<QgarAppParamDescr*>
QgarAppDescr::paramVect() const
{
    vector<QgarAppParamDescr*> retval;

    transform(_paramVect.begin(),
              _paramVect.end(),
              back_inserter(retval),
              qstlCloneObject());

    return retval;
}


// ---------------------------------------------------------------------

const std::string&
QgarAppDescr::accessName() const
{
    return _name;
}

// ---------------------------------------------------------------------

const std::string&
QgarAppDescr::accessAuthor() const
{
    return _author;
}

// ---------------------------------------------------------------------
const std::string&
QgarAppDescr::accessCopyright() const
{
    return _copyright;
}

// ---------------------------------------------------------------------

const std::string&
QgarAppDescr::accessBriefDoc() const
{
    return _briefDoc;
}

// ---------------------------------------------------------------------

const std::string&
QgarAppDescr::accessLongDoc() const
{
    return _longDoc;
}

// ---------------------------------------------------------------------

const std::vector<QgarAppParamDescr*>&
QgarAppDescr::accessParamVect() const
{
    return _paramVect;
}



// ---------------------------------------------------------------------
// T R A N S F O R M A T I O N
// ----------------------------------------------------------------------

void
QgarAppDescr::setName(const std::string& aName)
{
    _name = aName;
}

// ----------------------------------------------------------------------

void
QgarAppDescr::setAuthor(const std::string& anAuthor)
{
    _author = anAuthor;
}

// ----------------------------------------------------------------------
void
QgarAppDescr::setCopyright(const std::string& aCopyright)
{
    _copyright = aCopyright;
}

// ----------------------------------------------------------------------

void
QgarAppDescr::setBriefDoc(const std::string& aBriefDoc)
{
    _briefDoc = aBriefDoc;
}

// ----------------------------------------------------------------------

void
QgarAppDescr::setLongDoc(const std::string& aLongDoc)
{
    _longDoc = aLongDoc;
}

// ----------------------------------------------------------------------

void
QgarAppDescr::setParamVect(const std::vector<QgarAppParamDescr*>& pVect)
{
    // Delete all previous items
    for_each(_paramVect.begin(), _paramVect.end(), qstlDeleteObject());

    // Insert new ones
    // Duplicate parameters vector
    insert_iterator < vector<QgarAppParamDescr *> >
            ii(_paramVect, _paramVect.begin());
    transform(pVect.begin(), pVect.end(), ii, qstlCloneObject());
}



// ---------------------------------------------------------------------
// P A R S I N G   M E T H O D S
// ----------------------------------------------------------------------

void
QgarAppDescr::startParam(const Attributes& atts)
{
    // Set flag indicating that we're parsing a parameter now
    _parseData->state = PARAM;

    // Reset current parameter
    delete  _parseData->currentParam;
    _parseData->currentParam = new QgarAppParamDescr();


    //-- Read Parameter Attributes

    for (int i = 0; i < atts.getLength(); ++i)
    {
        string name  = atts.getLocalName(i);
        string value = atts.getValue(i);

        if (name == "name")
        {
            (_parseData->currentParam)->setName(value);
        }


        else if (name == "flag")
        {
            (_parseData->currentParam)->setFlag(value);
        }


        else if (name == "required")
        {
            if (value == "false")
            {
                (_parseData->currentParam)->setRequired(false);
            }
            else
            {
                (_parseData->currentParam)->setRequired(true);
            }
        }


        else if (name == "passing-mode")
        {
            QgarAppParamDescr::ParamPassing mode;

            if (value == "in")
            {
                mode = QgarAppParamDescr::QGE_IN;
            }
            else if (value == "out")
            {
                mode = QgarAppParamDescr::QGE_OUT;
            }
            else if (value == "inout")
            {
                mode = QgarAppParamDescr::QGE_INOUT;
            }
            else
            {
                mode = QgarAppParamDescr::QGE_NONE;

                ostringstream os;
                os << "Unknown mode: "
                   << value;
                throw QgarErrorDeveloper(__FILE__, __LINE__,
                                         "void QgarAppDescr::startParam(const Attributes&)",
                                         os.str());
            }
            (_parseData->currentParam)->setPassingMode(mode);
        }


        else if (name == "type")
        {
            if ( (value == "grayscale") ||
                 (value == "binary") ||
                 (value == "vectorial") )
            {
                (_parseData->currentParam)->setType(QgarAppParamDescr::QGE_IMAGE);
            }
            else
            {
                (_parseData->currentParam)->setType(QgarAppParamDescr::QGE_NUM);
            }
        }


        else if (name == "format")
        {
            QgarAppParamDescr::ParamFormat format;

            if (value == "PBM")
            {
                format = QgarAppParamDescr::QGE_PBM;
            }
            else if (value == "PPM")
            {
                format = QgarAppParamDescr::QGE_PPM;
            }
            else if (value == "PGM")
            {
                format = QgarAppParamDescr::QGE_PGM;
            }
            else if (value == "DXF")
            {
                format = QgarAppParamDescr::QGE_DXF;
            }
            else if (value == "SVG")
            {
                format = QgarAppParamDescr::QGE_SVG;
            }
            else if (value == "int")
            {
                format = QgarAppParamDescr::QGE_INT;
            }
            else if (value == "real")
            {
                format = QgarAppParamDescr::QGE_REAL;
            }
            else
            {
                format = QgarAppParamDescr::QGE_UNKNOWN_FORMAT;
            }

            (_parseData->currentParam)->setFormat(format);
        }


        else if (name == "default")
        {
            (_parseData->currentParam)->setDefaultValue(value);
        }


        else if (name == "min")
        {
            (_parseData->currentParam)->setMinValue(value);
        }


        else if (name == "max")
        {
            (_parseData->currentParam)->setMaxValue(value);
        }
    }
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endParam()
{
    // A parameter has been parsed, store it in the parameter vect.
    addParamDescr(_parseData->currentParam);

    _parseData->state = MAIN;
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endName()
{
    setName(_parseData->buffer);
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endAuthor()
{
    setAuthor(_parseData->buffer);
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endCopyright()
{
    setCopyright(_parseData->buffer);
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endBrief()
{
    if (_parseData->state == MAIN)
    {
        setBriefDoc(_parseData->buffer);
    }
    else
    {
        (_parseData->currentParam)->setBriefDoc(_parseData->buffer);
    }
}

// ---------------------------------------------------------------------

void
QgarAppDescr::endLong()
{
    if (_parseData->state == MAIN)
    {
        setLongDoc(_parseData->buffer);
    }
    else
    {
        (_parseData->currentParam)->setLongDoc(_parseData->buffer);
    }
}



// ---------------------------------------------------------------------
// O P E R A T O R S
// ----------------------------------------------------------------------

// Assignment operator
QgarAppDescr&
QgarAppDescr::operator=(const QgarAppDescr& rhs)
{
    if (this != &rhs)
    {
        _name      = rhs._name;
        _copyright = rhs._copyright;
        _briefDoc  = rhs._briefDoc;
        _longDoc   = rhs._longDoc;
        _paramVect = rhs._paramVect;
        _parseData = (rhs._parseData)? new ParseData(*rhs._parseData) : 0;
    }

    return *this;
}

// ----------------------------------------------------------------------

} // namespace qgar
