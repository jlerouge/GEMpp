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
 * @file PbmFile.cpp
 *
 * @brief Implementation of class qgar::PbmFile.
 *
 * See file PbmFile.h for the interface.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Karl Tombre & Gérald Masini</a>
 * @date   Jul 3, 2001  17:50
 * @since  qgar 1.0
 */



// STD
#include <cstring>
#include <iostream>
#include <sstream>
// QGAR
#include "AbstractPbmPlusFile.h"
#include "PbmFile.h"
#include "qgar.h"
#include "QgarErrorIO.h"



using namespace std;



namespace qgar
{

// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS


// MAXIMUM LENGTH OF A LINE OF THE FILE HEADER
const int PbmFile::s_pbm_header_line_size_       = 255;

// CHARACTER FOR FORMAT plain IN THE MAGIC NUMBER
const unsigned char  PbmFile::s_pbm_magic_plain_ = '1';

// CHARACTER FOR FORMAT raw IN THE MAGIC NUMBER
const unsigned char  PbmFile::s_pbm_magic_raw_   = '4';


// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// E N D   O F   S T A T I C   M E M B E R S
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
// SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS




// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// ====================================
// INITIALIZE FROM FILE NAME AND FORMAT
// ====================================


PbmFile::PbmFile(const char* aFileName, QGEpbm aPbm)

  : AbstractPbmPlusFile(aFileName, aPbm),
    inBuf_(new char[s_pbm_header_line_size_ + 1])

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R
// -------------------------------------------------------------------


PbmFile::~PbmFile()
{
  // Delete I/O buffer
  delete [] inBuf_;
}


// -------------------------------------------------------------------
// I N P U T
// -------------------------------------------------------------------


// ===========================
// READ AN IMAGE FROM THE FILE
// ===========================


BinaryImage
PbmFile::read()
{
  // Open file in read-only mode
  openRONLY();

  // Read file header
  readHeader();

  // Create the pixel map of the image
  // according to the features given by the file header
  int         size = colCnt_ * rowCnt_;
  BinaryPixel* pMap = new BinaryPixel[size];


  if (format_ == QGE_PBM_RAW)

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS raw
      // _____________________________________________________________

      BinaryPixel* pm  = pMap; // pointer to pixel map

      for (int rCnt = 0 ; rCnt < rowCnt_ ; ++rCnt)
    {
      unsigned char c;  // current input character
      int shift = -1;   // shifting count to get the value of the
                        // current pixel from the previous character

      // EACH ROW IS SEPARATELY CODED
      for (int cCnt = 0 ; cCnt < colCnt_ ; ++cCnt, ++pm)
        {
          if (shift < 0)
        {
          // No more pixel to get from the last input character
          // => get a new character from the file and reset shifting count
          c = (unsigned char) fstream_.get();
          shift = 7;
        }

          // Get the current pixel value from the appropriate bit
          *pm = (c >> shift) & 1;
          // Update shifting count
          --shift;
        } // END for cCnt

    } // END for rCnt
      // _____________________________________________________________
    }


  else

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS plain
      // _____________________________________________________________

      BinaryPixel* pm = pMap; // pointer to pixel map

      for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pm)
    {

      // Skip possible separator characters
      // and get current significant character
      char c;

      do
        {
          c = fstream_.get();
        }
      while ((c == ' ')  ||
         (c == '\n') ||
         (c == '\r') ||
         (c == '\t'));

      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
      // WARNING: A CHARACTER DIFFERENT FROM '0' IS SUPPOSED
      // TO REPRESENT A 1 PIXEL, WHATEVER THE CHARACTER IS.
      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
      if (c == '0')
        {
          *pm = (BinaryPixel) 0;
        }
      else
        {
          *pm = (BinaryPixel) 1;
        }
      // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

    } // END for iCnt
      // _____________________________________________________________
      //
    } // END if format_


  // Close file
  close();

  // Return image
  return BinaryImage(colCnt_, rowCnt_, pMap);
}


// -------------------------------------------------------------------
// O U T P U T
// -------------------------------------------------------------------



// ==========================
// WRITE AN IMAGE IN THE FILE
// ==========================


void
PbmFile::write(const BinaryImage& anImg)
{
  // Open file in write-only mode
  openWONLY();

  // Get image characteristics
  colCnt_   = anImg.width();
  rowCnt_   = anImg.height();

  // Write file header
  writeHeader();

  BinaryPixel* pMap = anImg.pPixMap();    // pointer to the pixel map
  int         size = colCnt_ * rowCnt_;  // image size

  if (format_ == QGE_PBM_RAW)

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS raw
      // _____________________________________________________________

      for (int rCnt = 0 ; rCnt < rowCnt_ ; ++rCnt)
    {
      // Character to store pixel values
      unsigned char c = 0;
      // Shifting count to put the value of the current pixel at
      // the appropriate location in the previous character
      int shift       = 7;

      // EACH ROW IS SEPARATELY CODED
      for (int cCnt = 0 ; cCnt < colCnt_ ; ++cCnt, ++pMap)
        {
          if (*pMap != 0)
        {
          // Set appropriate bit in character storing pixels
          c += (1 << shift);
        }

          --shift;

          if (shift == -1 )
        {
          // Character storing pixels is full: write it in the file
          fstream_.put(c);
          // Reset character and shifting count
          shift = 7;
          c = 0;
        }
        } // END for cCnt

      // The image width may be not a multiple of 8
      if (shift != 7)
        {
          fstream_.put(c);
        }

    } // END for rCnt

      // _____________________________________________________________
    }

  else

    {
      // _____________________________________________________________
      //
      // FILE FORMAT IS plain
      // _____________________________________________________________

      for (int iCnt = 0 ; iCnt < size ; ++iCnt, ++pMap)
    {
      fstream_ << ((*pMap != 0) ? '1' : '0');
    }

      fstream_ << endl;
      // _____________________________________________________________
      //
    } // END if format_


  // Close file
  close();
}


// -------------------------------------------------------------------
// H E A D E R
// -------------------------------------------------------------------


// ================
// READ FILE HEADER
// ================


void
PbmFile::readHeader()
{
  // READ THE FIRST LINE AND GET THE MAGIC NUMBER

  fstream_.getline(inBuf_, s_pbm_header_line_size_, '\n');
  int charsRead = fstream_.gcount();
  bool imDimReadFlag = false;

  char m1 = inBuf_[0];
  char m2 = inBuf_[1];

  // Check if there is more than the Magic Number in the first line
  if (charsRead > 4)
    {
      fstream_.seekg(0);
      istringstream iss(string((const char*)inBuf_), istringstream::in);

      string tmp;
      iss >> tmp; // Re-read the Magic Number and discard it

      iss >> colCnt_;
      iss >> rowCnt_;

      // SET the dimensions read FLAG
      imDimReadFlag = true;
    }

   // CHECK MAGIC NUMBER

  if ((m1 != s_pbm_magic_) ||
      ((m2 != s_pbm_magic_plain_) && (m2 != s_pbm_magic_raw_)))
    {
      ostringstream os;
      os << "Bad magic number ("
     << m1 << m2
     << ") in header of file "
     << name_;
      throw QgarErrorIO(__FILE__, __LINE__,
            "void qgar::PbmFile::readHeader()", os.str());
    }

  // SET FILE FORMAT

  if (m2 == s_pbm_magic_plain_)
    {
      format_ = QGE_PBM_PLAIN;
    }
  else
    {
      format_ = QGE_PBM_RAW;
    }

  // SKIP POSSIBLE COMMENTS

  do
    {
      fstream_.getline(inBuf_, s_pbm_header_line_size_, '\n');
    }
  while (inBuf_[0] == s_pbm_comment_);



  // GET IMAGE SIZE if it's not yet gotten
  if(!imDimReadFlag)
    {
      // Store current line in a string stream
      istringstream iss(string((const char*)inBuf_), istringstream::in);
      iss >> colCnt_;
      iss >> rowCnt_;
    }
}


// =================
// WRITE FILE HEADER
// =================


void
PbmFile::writeHeader()
{
  // MAGIC NUMBER

  fstream_ << s_pbm_magic_;

  if (format_ == QGE_PBM_RAW)
    {
      fstream_ << s_pbm_magic_raw_;     // RAW
    }
  else
    {
      fstream_ << s_pbm_magic_plain_;  // PLAIN
    }

  // QGAR VERSION (COMMENT)

  fstream_ << endl
       << "# Created by "
       << qgVersion()
       << endl;

  // IMAGE FEATURES

  fstream_ << colCnt_    // image width
       << ' '
       << rowCnt_    // image height
       << endl;
}


// -------------------------------------------------------------------


} // namespace qgar
