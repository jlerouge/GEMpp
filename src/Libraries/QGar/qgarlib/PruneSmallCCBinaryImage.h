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


#ifndef __PRUNESMALLCCBINARYIMAGE_H_INCLUDED__
#define __PRUNESMALLCCBINARYIMAGE_H_INCLUDED__


/**
 * @file    PruneSmallCCBinaryImage.h
 * @brief   Header file of class qgar::PruneSmallCCBinaryImage.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Philippe Dosch">Philippe Dosch</a>
 * @date    April 9, 2001  16:56
 * @since   Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: PruneSmallCCBinaryImage.h,v 1.3 2005/01/11 13:14:10 masini Exp $ */



// STD
#include <list>
#include <set>
#include <vector>
// QGAR
#include "GenImage.h"



namespace qgar
{

/** 
 * @class PruneSmallCCBinaryImage PruneSmallCCBinaryImage.h "qgarlib/PruneSmallCCBinaryImage.h"
 * @ingroup GRAPHPROC_CC
 * @brief Prune small connected components.
 *
 * This class provides a fast method to prune small connected components
 * of a binary image, without actually constructing any component.
 * For advanced operations on connected components, see class
 * qgar::ConnectedComponents.
 *
 * This class is based on the method described in
 * [<a href="Bibliography.html#Jain-et-al-1995">Jain&nbsp;et&nbsp;al,&nbsp;1995</a>].
 */
class PruneSmallCCBinaryImage

  : public BinaryImage

{

// ---------------------------------------------------------------------
// D A T A   S T R U C T U R E S
// ---------------------------------------------------------------------

  /** 
   * @class ComponentEntry PruneSmallCCBinaryImage.h
   * @internal
   */
  class ComponentEntry
  {
  public:
    // Constructor
    ComponentEntry(int x, int y)

      : _x(x),
	_y(y),
	_count(1),
	_valid(true)

    {
      // VOID
    }

    // Increments moment and update last point
    void inc(int x, int y, int i = 1)
    {
      _x = x;
      _y = y;
      _count += i;
    }

    // Increments moment
    void inc(int i)
    {
      _count += i;
    }

    // Last x-coordinate
    int x() const
    {
      return _x;
    }
    
    // Last y-coordinate
    int y() const
    {
      return _y;
    }

    // Return entry's moment
    int count() const
    {
      return _count;
    }
    
    // Return validity
    bool valid() const
    {
      return _valid;
    }

    // Set validity
    void setValid(bool state)
    {
      _valid = state;
    }

  protected:
    int _x;
    int _y;
    int _count;
    bool _valid;
  };

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /// Constructor.
  PruneSmallCCBinaryImage(const BinaryImage img, int size);


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  std::vector<ComponentEntry> _theEntries;
  std::list<int> _unusedEntries;
  std::list< std::set<int> > _equivTable;
  int* _lastRow;
  int* _curRow;
  int  _size;
  
  /// Process a black pixel.
  void processPixel(int i, int j);

  /// Create a new component entry.
  int createNewEntry(int i, int j);

  /// Attach a pixel to an existing entry.
  void attachPixel(int i, int j, int entry);

  /// Attach a pixel to existing entries and mark these entries as unificable.
  void attachPixelTwoEntries(int i, int j, int e1, int e2);

  /// Attach a pixel to existing entries and mark these entries as unificable.
  void attachPixelThreeEntries(int i, int j, int e1, int e2, int e3);

  /// Process executed after an end of line.
  void endOfLineProcess(int j);

  /// Add 2 entries in the equivalence table.
  void addEquivEntries(int e1, int e2);

  /// Unify entries matching the same connected component.
  void unification();

  /// Search small connected components and remove them from the image.
  void searchAndRemoveSmallComponents(int j);

  /// Remove a connected component recursively, by starting from one of its points.
  void removeComponent(int x, int y);

  /// Return true if it exists a black neighbor connected to the argument point.
  bool isNeighbor(int i, int j, int * a, int * b);

// -------------------------------------------------------------------
}; // class PruneSmallCCBinaryImage

} // namespace qgar


#endif /* __PRUNESMALLCCBINARYIMAGE_H_INCLUDED__ */
