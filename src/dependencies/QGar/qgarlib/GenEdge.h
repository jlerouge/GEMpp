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


#ifndef __GENEDGE_H_INCLUDED__
#define __GENEDGE_H_INCLUDED__


/**
 * @file GenEdge.h
 *
 * @brief Header file of class qgar::GenEdge.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.2
 */


// For RCS/CVS use: Do not delete
/* $Id: GenEdge.h,v 1.7 2006/07/04 13:37:41 masini Exp $ */



// QGAR
namespace qgar
{
  // ___________________________________________________________________
  // 
  // As class GenEdge is a client of class GenNode and class Genode
  // is a client of class GenEdge, compilation aborts because
  // of unresolved forward declarations without this prototype
  // (the text of one class is necessarily placed before the text
  // of the other by the precompiler). 
  // ___________________________________________________________________
  //
  template<class TNODE, class TEDGE> class GenNode;
}



namespace qgar
{

/**
 * @ingroup DS_GRAPH
 *
 * @class GenEdge GenEdge.h "qgarlib/GenEdge.h"
 *
 * @brief Edge of a parameterized graph containing (user-defined) data.
 *
 * An edge includes:
 * - an object of type <b>TEDGE</b>, called the <i>edge type</i>,
 * - an <b>integer</b> flag that any client may use
 *   for its own purposes,
 * - two pointers to the nodes which are adjacent to the edge.
 *
 * The adjacent nodes are arbitrarily called the <i>source</i> and
 * the <i>target</i>. The source (resp. target) is the first (resp.
 * second) node given as argument to the constructor at the creation
 * of the edge.
 *
 * See class qgar::GenNode for nodes.
 *
 * @warning
 * - The class is not supposed to be derived: No function
 *   member (destructor or whatever else) is virtual.
 * - <b>Pointers (to nodes) given as arguments to constructors and
 *   other function members may be null, which <i>may</i> further
 *   lead to hard bugs, when it results from a programmer's mistake.</b>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.2
 */
template <class TNODE, class TEDGE> class GenEdge
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the data stored in an edge.
   */
  typedef TEDGE edge_type;

  /**
   * @brief Reference to qgar::GenEdge::edge_type.
   */
  typedef edge_type& edge_type_reference;

  /**
   * @brief Constant reference to qgar::GenEdge::edge_type.
   */
  typedef const edge_type& edge_type_const_reference;

  /**
   * @brief Pointer to qgar::GenEdge::edge_type.
   */
  typedef edge_type* edge_type_pointer;

  /**
   * @brief Constant pointer to qgar::GenEdge::edge_type.
   */
  typedef const edge_type* edge_type_const_pointer;

  /**
   * @brief Type of the data stored in a node.
   */
  typedef TNODE node_type;

  /**
   * @brief Reference to qgar::GenEdge::node_type.
   */
  typedef node_type& node_type_reference;

  /**
   * @brief Constant reference to qgar::GenEdge::node_type.
   */
  typedef const node_type& node_type_const_reference;

  /**
   * @brief Pointer to qgar::GenEdge::node_type.
   */
  typedef node_type* node_type_pointer;

  /**
   * @brief Constant pointer to qgar::GenEdge::node_type.
   */
  typedef const node_type* node_type_const_pointer;

  //@}

// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Default constructor.
   *
   * The source and target of the edge are set to <b>0</b>.
   *
   * @param aFlag  value of the node flag (default <b>0</b>)
   */
  GenEdge(short int aFlag = 0);

   /**
    * @brief Initialize with data.
    *
    * The source and target of the edge are set to <b>0</b>.
    *
    * @param aData  data to be contained in the edge
    * @param aFlag  value of the node flag (default <b>0</b>)
    */
  GenEdge(edge_type_const_reference aData, short int aFlag = 0);

   /**
    * @brief Initialize with source and target.
    *
    * @param aPSource  a pointer to the source node (may be <b>0</b>)
    * @param aPTarget  a pointer to the target node (may be <b>0</b>)
    * @param aFlag     value of the node flag (default <b>0</b>)
    */
  GenEdge(GenNode<node_type, edge_type>* const aPSource,
	  GenNode<node_type, edge_type>* const aPTarget,
	  short int aFlag = 0);

   /**
    * @brief Initialize with data, source and target.
    *
    * @param aData     data to be contained in the edge
    * @param aPSource  a pointer to the source node (may be <b>0</b>)
    * @param aPTarget  a pointer to the target node (may be <b>0</b>)
    * @param aFlag     value of the node flag (default <b>0</b>)
    */
  GenEdge(GenNode<node_type, edge_type>* const aPSource,
	  GenNode<node_type, edge_type>* const aPTarget,
	  edge_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Copy constructor.
   *
   * @param anEdge  edge to be copied
   *
   * @warning The constructor performs a shallow copy:
   * The two nodes adjacent to the edge are not duplicated.
   *
   * @todo This constructor performs a shallow copy.
   * Could it perform a deep copy? Nodes adjacent to the edge
   * would thus be copied, and then all edges adjacent to these
   * nodes, and the nodes adjacent to these edges... and then
   * the whole graph!...
   */
  GenEdge(const GenEdge<node_type, edge_type>& anEdge);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  ~GenEdge();

  //@}


  /** @name Edge data */
  //        =========
  //@{

  /**
   * @brief Get edge data.
   */
  inline edge_type_const_reference accessData() const;

   /**
    * @brief Get a copy of edge data.
    */
  inline edge_type data() const;

  /**
   * @brief Set edge data.
   *
   * @param  aData  data to be contained in the edge
   */
  inline void setData(edge_type_const_reference aData);

  /**
   * @brief Get edge flag.
   */
  inline short int flag() const;

  /**
   * @brief Set edge flag.
   *
   * @param aFlag  value to assign to the flag
   */
  inline void setFlag(short int aFlag);

  //@}


  /** @name Adjacent nodes */
  //        ==============
  //@{

  /**
   * @brief Get source node.
   */
  inline const GenNode<node_type, edge_type>& accessSource() const;

  /**
   * @brief Get a copy of source node.
   */
  GenNode<node_type, edge_type> source() const;

  /**
   * @brief Get a pointer to source node.
   */
  inline GenNode<node_type, edge_type>* pSource() const;

  /**
   * @brief Get target node.
   */
  inline const GenNode<node_type, edge_type>& accessTarget() const;

  /**
   * @brief Get a copy of target node.
   */
  inline GenNode<node_type, edge_type> target() const;

  /**
   * @brief Get a pointer to target node.
   */
  inline GenNode<TNODE,TEDGE>* pTarget() const;

  /**
   * @brief Set (pointer to) source node.
   *
   * @param  aPSource  pointer to a node (may be <b>0</b>)
   */
  inline void setPSource(GenNode<node_type, edge_type>* aPSource);

  /**
   * @brief Set (pointer to the) target node.
   *
   * @param  aPTarget  pointer to a node (may be <b>0</b>)
   */
  inline void setPTarget(GenNode<node_type, edge_type>* aPTarget);

  /**
   * @brief Set (pointer to) given node as source or target.
   *
   * The given node becomes the source of the current edge
   * if the source is free. Otherwise, the given node becomes
   * the target of the current edge.
   *
   * @param  aPNode  pointer to a node (may be <b>0</b>)
   */
  inline void setPNode(GenNode<node_type, edge_type>* aPNode);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param  anEdge  edge to be assigned
   *
   * @warning The function performs a shallow copy:
   * The two nodes adjacent to the edge are not duplicated.
   *
   * @todo This constructor performs a shallow copy.
   * Could it perform a deep copy? Nodes adjacent to the edge
   * would thus be copied, and then all edges adjacent to these
   * nodes, and the nodes adjacent to these edges... and then
   * the whole graph!...
   */
  GenEdge<node_type, edge_type>&
  operator=(const GenEdge<node_type, edge_type>& anEdge);
 
  /**
   * @brief Equality.
   *
   * Test if the data of the current edge compare equal to the data
   * of given edge <b>anEdge</b>, using operator <b>==</b>
   * applying to objects of type <b>TEDGE</b>,
   * The values of the flags are not taken into account.
   *
   * @param  anEdge  an edge
   */
  inline bool operator==(const GenEdge<node_type, edge_type>& anEdge);

  /**
   * @brief Inequality.
   *
   * Test if the data of the current edge do not compare equal
   * to the data of given edge <b>anEdge</b>, using operator <b>==</b>
   * applying to objects of type <b>TEDGE</b>,
   * The values of the flags are not taken into account.
   *
   * @param  anEdge  an edge
   */
  inline bool operator!=(const GenEdge<node_type, edge_type>& anEdge);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of an edge */
  //        =========================
  //@{

  /**
   * @brief Data contained in the edge.
   */
  edge_type _data;

  /**
   * @brief Flag at client's disposal (default <b>0</b>).
   */
  short int _flag;

  /**
   * @brief Pointer to the source node.
   */
  GenNode<node_type, edge_type>* _pSource;

  /** 
   * @brief Pointer to the target node.
   */
  GenNode<node_type, edge_type>* _pTarget;

  //@}

// -------------------------------------------------------------------
}; // Class GenEdge


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenEdge.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




#endif /* __GENEDGE_H_INCLUDED__ */
