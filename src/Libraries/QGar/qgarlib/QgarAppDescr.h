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


#ifndef __QGARAPPDESCR_H_INCLUDED__
#define __QGARAPPDESCR_H_INCLUDED__


/**
 * @file QgarAppDescr.h
 *
 * @brief Header file of class qgar::QgarAppDescr.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 14, 2003  15:29
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: QgarAppDescr.h,v 1.13 2007/02/14 17:34:05 masini Exp $ */



// STD
#include <cstring>
#include <stdexcept>
#include <vector>
// QGAR
#include "QgarAppParamDescr.h"
#include "sax/DefaultHandler.h"
#include "sax/InputSource.h"
namespace qgar
{
  // Avoid #include's when not necessary
  class QgarAppParamDescr;
}
// XML
namespace qgxml
{
  // Avoid #include's when not necessary
  class Attributes;
  class InputSource;
  class SAXParseException;
}



using namespace std;



namespace qgar
{


/**
 * @ingroup APP
 *
 * @class QgarAppDescr QgarAppDescr.h "qgarlib/QgarAppDescr.h"
 *
 * @brief Parses an XML description of a Qgar application
 *   and builds its representation.
 *
 * Each Qgar application is linked to an XML document containing its
 * description and the description of its parameter.
 * 
 * The main elements of the description are:
 * - its name
 * - its author
 * - the copyright attached to it
 * - its documentation
 * - the description of each of its parameters.
 *
 * This class allows the user to create a representation of
 * such a description by taking care of the parsing of the XML
 * document. Once this representation is created, the user can query
 * the various elements composing the description.
 *
 * Each parameter description is stored into an instance of
 * class qgar::QgarAppParamDescr.
 *
 * The user may also serialize instances of this class to XML using
 * the qgar::QgarAppDescr::toXml() function member.
 *
 * @todo Insert a link to the document DTD.
 * 
 * @see Class qgar::QgarAppParamDescr
 * 
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Jan Rendek">Jan Rendek</a>
 * @date   May 14, 2003  15:29
 * @since  Qgar 2.1.1
 */
class QgarAppDescr

  : public qgxml::DefaultHandler

{
// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** 
   * @name TAGs  
   * 
   * @brief The tags composing the XML document describing an
   * application description.
   */
  //@{

  static const char * const ELT_APPLICATION;
  static const char * const ELT_DESCR;
  static const char * const ELT_DOCUMENTATION;
  static const char * const ELT_PARAMLIST;
  static const char * const ELT_PARAM;
  static const char * const ELT_NAME;
  static const char * const ELT_AUTHOR;
  static const char * const ELT_COPYRIGHT;
  static const char * const ELT_DOC;
  static const char * const ELT_BRIEF;
  static const char * const ELT_LONG;
  
  static const char * const ATT_REVISION;
  static const char * const ATT_LANG;
  static const char * const ATT_NAME;
  static const char * const ATT_FLAG;
  static const char * const ATT_REQUIRED;
  static const char * const ATT_PASSING_MODE;
  static const char * const ATT_FORMAT;
  static const char * const ATT_TYPE;

//@}


  /** @name Constructors */
  //        ============
  //@{

  /** 
   * @brief Build a QgarAppDescr from a file
   *
   * @param filename The file to create the description from.
   */
  explicit QgarAppDescr(const char* const filename);
  /**
   * @brief Build a QgarAppDescr from a string
   *
   * @param filename The name of the file containing the XML document
   * to load the description from.
   */
  explicit QgarAppDescr(const string& filename);

  /**
   * @brief Build a QgarAppDescr from an input stream
   *
   * @param stream The input stream to parse the XML document from.
   */
  explicit QgarAppDescr(istream& stream);

  /**
   * @brief Build a QgarAppDescr from given data.
   *
   * @param name      The name of the application.
   * @param copyright The copyright notice attached to the application.
   * @param briefDoc  The brief documentation of this application.
   * @param longDoc   The detailed documentation of this application.
   * @param paramVect The descriptions of the application parameters.
   */
  QgarAppDescr(const string& name,
	       const string& copyright,
	       const string& briefDoc,
	       const string& longDoc,
	       const vector<QgarAppParamDescr *>& paramVect);

  /**
   * @brief Copy constructor
   */
  QgarAppDescr(const QgarAppDescr&);

  //@}


  /** @name Destructors */
  //        ===========
  //@{

  /**
   * @brief Destructor
   */
  virtual ~QgarAppDescr();
  
  //@}


  /** @name Parameters */
  //        ==========
  //@{

  /**
   * @brief Add the description of a parameter.
   *
   * @param descr the description of the parameter to be added
   */
  void addParamDescr(QgarAppParamDescr * descr);
  
  //@}


  /** @name XML Serialization */
  //        =================
  //@{

  /**
   * @brief Builds an XML document representating this application
   *   description
   *
   * @return 
   */
  string toXml() const;

//@}
  
  /** @name DefaultHandler Redefinitions */
  //        ============================
  //@{

  /**
   * @brief
   *
   * @todo To be documented!
   */
  virtual void characters(const char * ch, 
                          const unsigned int start, 
                          const unsigned int length);

  /**
   * @brief
   *
   * @todo To be documented!
   */
  virtual void startElement(const string& uri,
			    const string& localName,
			    const string& qName,
			    const qgxml::Attributes& atts);
  
  /**
   * @brief
   *
   * @todo To be documented!
   */
  virtual void endElement(const string& uri,
			  const string& localName, 
			  const string& qName);

  /**
   * @brief
   *
   * @todo To be documented!
   */
  virtual void fatalError(const qgxml::SAXParseException& exception);
  
  //@}


  /** @name Access */
  //        ======
  //@{

  /**
   * @brief Retrieve the name of the application.
   *
   * @return The name of the applcation, or an empty string if no name
   * was provided.
   */
  string name() const;

  /**
   * @brief Retrieve the author of the application.
   *
   * @return The author of the application, or an empty string if no name
   * was provided..
   */
  string author() const;

  /**
   * @brief Retrieve the copyright notice attached to the application
   *
   * @return The copyright for the application, or an empty string if no
   * notice was provided.
   */
  string copyright() const;

  /**
   * @brief Retrieve the brief documentation of the application.
   *
   * @return The brief documentation of the application, or an empty
   * string if no documenation was provided.
   */
  string briefDoc() const;

  /**
   * @brief Retrieve the detailed documentation for the application.
   *
   * @return The detailed documentation of the application, or an empty
   * string if no documentation was provided.
   */
  string longDoc() const;

  /**
   * @brief Retrieve the description of the parameters of the
   * application.
   *
   * @return A vector containing the memory representation of the
   * parameters description, or an empty vector if the application has
   * no parameter.
   */
  vector<QgarAppParamDescr *> paramVect() const;


  /**
   * @brief Access to the name of the application
   *
   * @return A reference on the name of the application, or on an empty
   * string if no name was provided.
   */
  const string& accessName() const;

  /**
   * @brief Access to the author information of the application
   *
   * @return A reference on the information about the author of the
   * application or an empty string if no author was provided.
   */
  const string& accessAuthor() const;

  /**
   * @brief Access to the copyright notice attached to the application.
   *
   * @return A reference on the copyright notice, or on an empty string
   * if no notice was provided.
   */
  const string& accessCopyright() const;

  /**
   * @brief Access to the brief documentation of the application.
   *
   * @return A reference on the brief documentation of the application,
   * or on an empty string if no documentation was provided.
   */
  const string& accessBriefDoc() const;

  /**
   * @brief Access to the detailed documentation of the application
   *
   * @return A reference on the detailed documentation of the
   * application or on an empty string if no detailed documentation was
   * provided.
   */
  const string& accessLongDoc() const;

  /**
   * @brief Access to the descriptions of the parameters of the
   * application.
   *
   * @return A reference on the vector containing the memory
   * representation of the  parameters description, or an empty vector
   * if the application has no parameter.
   */
  const vector<QgarAppParamDescr*>& accessParamVect() const;

//@}

  
  /** @name Transformation */
  //        ==============
  //@{

  /**
   * @brief Sets the name of the application.
   *
   * @param aName new name of the application
   */
  void setName(const string& aName);

  /**
   * @brief Sets the name of the author of the application.
   *
   * @param anAuthor new name of the author(s) of the application
   */
  void setAuthor(const string& anAuthor);

  /**
   * @brief Sets the copyright notice for the application.
   *
   * @param aCopyright new copyright notice for the application
   */
  void setCopyright(const string& aCopyright);

  /**
   * @brief Sets the brief documentation of the application.
   *
   * @param aBriefDoc new brief documentation of the application
   */
  void setBriefDoc(const string& aBriefDoc);

  /**
   * @brief Sets the detailed documentation of the application.
   *
   * @param aLongDoc The new detailed documentation of the application
   */
  void setLongDoc(const string& aLongDoc);

  /**
   * @brief Sets the descriptions of the application parameters.
   *
   * @param aParamVect  vector containing the new descriptions of the
   *                    application parameters
   */
  void setParamVect(const vector<QgarAppParamDescr*>& aParamVect);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment operator
   */
  QgarAppDescr& operator=(const QgarAppDescr& rhs);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /**
   * @brief Creates an instance from an XML document located by an input
   * source.
   *
   * @param source The input source referencing the XML document to
   * create an instance from.
   *
   * @throw std::runtime_error This exception is thrown if the input
   * source could not be accessed, or if an error occured while parsing
   * the XML document.
   */  
  void init(qgxml::InputSource source);


  /** 
   * @name Methods used for parsing elements 
   * @internal
   * @brief Theses methods are callbacks invoked from the DefaultHandler
   * function members implementations. 
   */
  //@{

  /**
   * @internal
   * @brief Callback invoked when the parser starts parsing a new
   * parameter section.
   *
   * The parameter sections are enclosed in a \<ELT_PARAM\> tag.
   *
   * @param atts The attributes of the \<ELT_PARAM\> element.
   *
   * @see qgar::QgarAppDescr::endParam()
   */
  void startParam(const qgxml::Attributes& atts);

  /**
   * @internal
   * @brief Callback invoked when the parser has finished the parsing of
   * a parameter section
   *
   * The parameter sections are enclosed by \<ELT_PARAM\> tags.
   *
   * @see qgar::QgarAppDescr::startParam()
   */
  void endParam();

  /**
   * @internal
   * @brief Callback invoked when the parser has finished the parsing of
   * the name section.
   *
   * The name section is enclosed in a pair of \<ELT_NAME\> \</ELT_NAME>
   * tags.
   */
  void endName();

  /**
   * @internal
   * @brief Callback invoked when the parser has finished the parsing of
   * the author section.
   *
   * The author section is enclosed in a pair of \<ELT_AUTHOR\>
   * \<ELT_AUTHOR/\> tags.
   */
  void endAuthor();

  /**
   * @internal
   * @brief Callabck invoked when the parser has finished the parsing of
   * the copyright section.
   *
   * The copyright section is enclosed in a pair of \<ELT_COPYRIGHT\>
   * \<ELT_COPYRIGHT/\> tags.
   */
  void endCopyright();

  /**
   * @internal
   * @brief Callabck invoked when the parser has finished the parsing of
   * the brief documentation section.
   *
   * The copyright section is enclosed in a pair of \<ELT_BRIEF\>
   * \<ELT_BRIEF/\> tags.
   */
  void endBrief();

  /**
   * @internal
   * @brief Callabck invoked when the parser has finished the parsing of
   * the detailed documentation section.
   *
   * The copyright section is enclosed in a pair of \<ELT_LONG\>
   * \<ELT_LONG/\> tags.
   */
  void endLong();

  //@}


  /// The name of the application.
  string _name;

  /// The author of the application
  string _author;

  /// The copyright notice
  string _copyright;

  /// The brief documentation
  string _briefDoc;

  /// The documentation verbose version.
  string _longDoc;

  /// The descriptions of the application parameters
  vector<QgarAppParamDescr *> _paramVect;


  /** @name Data Used for Parsing */
  //        =====================
  //@{

  /**
   * @internal
   */
  enum ParseState
    {
      MAIN,
      PARAM
    };

  /**
   * @internal
   * @brief Structure holding all the data used while parsing.
   * @ingroup APP
   *
   * Using a structure to regroup all these data allows to dynamically
   * allocate the room to store it. This space can the be desallocated
   * when parsing is over. This means the that the overall memory cost
   * for these data is 1 pointer size when no parsing is performed.
   */
  struct ParseData
  {

    /**
     * @brief Default constructor
     */
    ParseData() : state(MAIN), firstElt(true), currentParam(0)
    {
      /* EMPTY */
    }

    /**
     * @brief Copy-Constructor
     */
    ParseData(const ParseData& rhs)
      : state(rhs.state), firstElt(rhs.firstElt)
    { 
      currentParam = (rhs.currentParam) ? 
	new QgarAppParamDescr(*rhs.currentParam) : 0;
    }

    /**
     * @brief Destructor
     */
    ~ParseData()
    {
      delete currentParam;
    }

    /// Parsing state: Are we parsing the application or a param ?
    ParseState state;
    
    /**
     * @brief Flag used to indicate if the parsed element is the first
     * being parsed
     *
     * This flag is mainly used to test if the XML document is of the
     * correct document tag (ie. first tag is 'application').
     */
    bool firstElt;

    /// Buffer to store parsed characters of an element
    string buffer;
    
    /**
     * @brief Pointer to the current parameter being parsed.
     */
    qgar::QgarAppParamDescr* currentParam;
    
  } *_parseData; /**<
		  * @internal 
		  * @brief A pointer to the struct holding parsing data
		  */ 
  //@}

// -------------------------------------------------------------------
}; // class QgarAppDescr


} // namespace qgar


#endif /* __QGARAPPDESCR_H_INCLUDED__ */
