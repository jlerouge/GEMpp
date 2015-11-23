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


#ifndef __GENNODE_H_INCLUDED__
#define __GENNODE_H_INCLUDED__


/**
 * @file GenNode.h
 *
 * @brief Header file of class qgar::GenNode.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.1.2
 */


// For RCS/CVS use: Do not delete
/* $Id: GenNode.h,v 1.5 2006/07/04 13:37:42 masini Exp $ */



// STD
#include <list>
// QGAR
#include <qgarlib/GenEdge.h>



namespace qgar
{


/**
 * @ingroup DS_GRAPH
 *
 * @class GenNode GenNode.h "qgarlib/GenNode.h"
 *
 * @brief Node of a parameterized graph containing (user-defined) data.
 *
 * A node includes:
 *
 * - an object of type <b>TNODE</b>, called the <i>node type</i>,
 * - an <b>integer</b> flag, that any client may use
 *   for own specific purposes,
 * - a STL list of pointers to the edges which are adjacent to the node,
 *   called the <i>edges list</i>.
 *
 * See class qgar::GenEdge for edges.
 *
 * @warning
 * - The class is not supposed to be derived: No function
 *   member (destructor or whatever else) is virtual.
 * - <b>For efficiency reasons, the validity of pointers (to edges)
 *   given as arguments to constructors and other function members
 *   is not checked. In particular, they may be <i>null</i>, which
 *   will undoubtedly be the cause of a further program abortion.</b>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.1.2
 */
template <class TNODE, class TEDGE> class GenNode
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
   * The edges list of the node is empty.
   *
   * @param  aFlag  value of the node flag (default <b>0</b>)
   */
  GenNode(short int aFlag = 0);

  /**
   * @brief Initialize with data.
   *
   * The edges list of the node is empty.
   *
   * @param  aData  data to be contained in the node
   * @param  aFlag  value of the node flag (default <b>0</b>)
   */
  GenNode(node_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Initialize with a pointer to an edge, and data.
   *
   * The pointer to the edge is inserted in the edges list of the node.
   *
   * @param  aPEdge  pointer to an edge: <b>Should not be 0!</b>
   * @param  aData   data to be contained in the node
   * @param  aFlag   value of the node flag (default <b>0</b>)
   */
  GenNode(GenEdge<node_type,edge_type>* const aPEdge,
	  node_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Initialize with two pointers to an edge, and data.
   *
   * The pointers to edges are inserted in the edges list of the node.
   *
   * @param  aPEdge1  pointer to an edge <b>Should not be 0!</b>
   * @param  aPEdge2  pointer to an edge <b>Should not be 0!</b>
   * @param  aData    data to be contained in the node
   * @param  aFlag    value of the node flag (default <b>0</b>)
   */
  GenNode(GenEdge<node_type,edge_type>* const aPEdge1,
	  GenEdge<node_type,edge_type>* const aPEdge2,
	  node_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Initialize with three pointers to an edge, and data.
   *
   * The pointers to edges are inserted in the edges list of the node.
   *
   * @param  aPEdge1  pointer to an edge <b>Should not be 0!</b>
   * @param  aPEdge2  pointer to an edge <b>Should not be 0!</b>
   * @param  aPEdge3  pointer to an edge <b>Should not be 0!</b>
   * @param  aData    data to be contained in the node
   * @param  aFlag    value of the node flag (default <b>0</b>)
   */
  GenNode(GenEdge<node_type,edge_type>* const aPEdge1,
	  GenEdge<node_type,edge_type>* const aPEdge2,
	  GenEdge<node_type,edge_type>* const aPEdge3,
	  node_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Copy constructor.
   *
   * @param  aNode  a node to be copied
   *
   * @warning The constructor performs a shallow copy:
   * The edges adjacent to the node are not duplicated.
   *
   * @todo This constructor performs a shallow copy.
   * Could it perform a deep copy? Edges adjacent to the node
   * would thus be copied, and then all nodes adjacent to these
   * edges, and the edges adjacent to these nodes... and then
   * the whole graph!
   */
  GenNode(const GenNode<node_type,edge_type>& aNode);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  ~GenNode();

  //@}


  /** @name Node characteristics */
  //        ====================

  //@{
   /**
   * @brief Get node degree (number of edges adjacent to the node).
   */
  inline int degree() const;

  //@}


  /** @name Node data */
  //        =========
  //@{

  /**
   * @brief Get node data.
    */
  inline node_type_const_reference accessData() const;

   /**
    * @brief Get a copy of the node data.
    */
  inline node_type data() const;

  /**
   * @brief Set node data.
   *
   * @param  aData  data to be contained in the node
   */
  inline void setData(node_type_const_reference aData);

  /**
   * @brief Get node flag.
   */
  inline short int flag() const;

  /**
   * @brief Set node flag.
   *
   * @param aFlag  value to assign to the flag
   */
  inline void setFlag(short int aFlag);

  //@}


  /** @name Access to edges */
  //        ===============
  //@{

  /**
   * @brief Get (a constant reference to) the edges list.
   */
  inline const std::list< GenEdge<node_type,edge_type>* >&
  accessEdges() const;

  /**
   * @brief Get the edges list.
   */
  inline std::list< GenEdge<node_type,edge_type>* >& getEdges();

  /**
   * @brief Get a copy of the edges list.
   */
  inline std::list< GenEdge<node_type,edge_type>* > edges() const;

  //@}


  /** @name Edge insertion */
  //        ==============
  //@{

//   /**
//    * @brief Add a created edge from given data and flag,
//    * and return a pointer to it.
//    *
//    * The current node becomes the source of the new edge.
//    * The edge is inserted at the end of the edges list of the node.
//    * Iterators to the edges list are not invalidated.
//    *
//    * @param  aData  data to be contained in the new edge
//    * @param  aFlag  value of the edge flag (default <b>0</b>)
//    */
//   inline GenEdge<TNODE,TEDGE>*
//   addEdge(const TEDGE& aData, short int aFlag = 0);

  /**
   * @brief Add (a pointer to) an edge at the end
   *   of the edges list of the node.
   *
   * Iterators to the edges list are not invalidated.
   *
   * @param  aPEdge  a pointer to an edge: <b>Should not be 0!</b>
   */
  inline GenEdge<node_type,edge_type>*
  addEdge(GenEdge<node_type,edge_type>* const aPEdge);

  /**
   * @brief Add (a pointer to) an edge at the beginning
   * of the edges list of the node.
   *
   * Iterators to the edges list are not invalidated.
   *
   * @param  aPEdge  a pointer to an edge: <b>Should not be 0!</b>
   */
  inline GenEdge<node_type,edge_type>*
  addEdgeFront(GenEdge<node_type,edge_type>* const aPEdge);
  //@}


  // ==========================================================
  /** @name Edge removal
      <b>Warning:</b> The client is in charge of the deletion
      of the removed elements. Removals invalidate iterators
      pointing to removed elements.
   */
  // ==========================================================
  //@{
 
  /**
   * @brief Remove the edge at given position in the edges list,
   * and return it.
   *
   * No effect when <b>aPos</b> points to the end of the list.
   *
   * @param  aPos  a position in the STL list of adjacent edges
   */
  GenEdge<node_type,edge_type>*
  removeEdge(typename std::list< GenEdge<node_type,edge_type>* >::iterator aPos);
 
  /**
   * @brief Remove the <i>first</i> pointer to an edge that
   * compares equal to the given pointer in the edges list.
   *
   * The function return the given pointer if the removal
   * is performed, <b>0</b> otherwise.
   *
   * @param  aPEdge  a pointer to an edge: <b>Should not be 0!</b>
   */
  GenEdge<node_type,edge_type>*
  removeEdge(GenEdge<node_type,edge_type>* const aPEdge);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param  aNode  node to be assigned
   *
   * @warning The function performs a shallow copy:
   * The edges adjacent to the node are not duplicated.
   *
   * @todo This constructor performs a shallow copy.
   * Could it perform a deep copy? Edges adjacent to the node
   * would thus be copied, and then all nodes adjacent to these
   * edges, and the edges adjacent to these nodes... and then
   * the whole graph!
   */
  GenNode<node_type,edge_type>&
  operator=(const GenNode<node_type,edge_type>& aNode);
 
  /**
   * @brief Equality.
   *
   * Tests if the data of the current node compare equal to the data
   * of given node <b>aNode</b>, using operator <b>==</b>
   * applying to objects of type <b>TNODE</b>,
   * The values of the flags are not taken into account.
   *
   * @param  aNode  a node
   */
  inline bool operator==(const GenNode<node_type,edge_type>& aNode);

  /**
   * @brief Inequality.
   *
   * Tests if the data of the current node do not compare equal
   * to the data of given node <b>aNode</b>, using operator
   * <b>!=</b> applying to objects of type <b>TNODE</b>,
   * The values of the flags are not taken into account.
   *
   * @param  aNode  a node
   */
  inline bool operator!=(const GenNode<node_type,edge_type>& aNode);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of a node */
  //        ========================
  //@{

  /**
   * @brief Data contained in the node.
   */
  node_type _data;

  /**
   * @brief Flag at client's disposal (default <b>0</b>).
   */
  short int _flag;

  /**
   * @brief List of (pointers to) edges adjacent to the node.
   */
  std::list< GenEdge<node_type,edge_type>* > _edges;

  //@}

// -------------------------------------------------------------------
}; // class GenNode


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include <qgarlib/GenNode.tcc>

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




#endif /* __GENNODE_H_INCLUDED__ */
