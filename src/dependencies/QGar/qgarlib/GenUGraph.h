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


#ifndef __GENUGRAPH_H_INCLUDED__
#define __GENUGRAPH_H_INCLUDED__


/**
 * @file GenUGraph.h
 *
 * @brief Header file of class qgar::GenUGraph.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.2
 */



// For RCS/CVS use: Do not delete
/* $Id: GenUGraph.h,v 1.9 2006/07/04 13:37:42 masini Exp $ */



// STD
#include <list>
// QGAR
#include "GenEdge.h"
#include "GenNode.h"



namespace qgar
{


/**
 * @ingroup DS_GRAPH
 *
 * @class GenUGraph GenUGraph.h "qgarlib/GenUGraph.h"
 *
 * @brief Parameterized undirected graph.
 *
 * A node is described by class qgar::GenNode. It contains:
 *
 * - an object of type <b>TNODE</b>, called the <i>node type</i>,
 * - an <b>integer</b> flag, at client's disposal,
 * - a STL list of (pointers to) edges adjacent to the node.
 *
 * An edge is described by class qgar::GenEdge. It contains:
 *
 * - an object of type <b>TEDGE</b>, called the <i>edge type</i>,
 * - an <b>integer</b> flag, at client's disposal,
 * - two (pointers to its) adjacent nodes, arbitrarily called
 *   <i>source</i> and <i>target</i> nodes.
 *
 * A graph is represented as:
 *
 * - A STL list of pointers to its nodes, called the <i>nodes list</i>.
 *   The first node of the list is called the <i>entry</i> node.
 * - A STL list of pointers to its edges called the <i>edges list</i>.
 *   The first edge of the list is called the <i>entry</i> edge.
 *
 * Partially inspired by the LEDA library (when it was a free software).
 * See <a href="http://www.mpi-sb.mpg.de/LEDA/" target="_blank">http://www.mpi-sb.mpg.de/LEDA/</a>.
 *
 * @warning
 *
 * <ul>
 *
 * <li><p>
 * The class is not supposed to be derived: No function
 * member (destructor or whatever else) is virtual.
 * </p></li>
 *
 * <li><p>
 * Neither copy constructor nor assignment operator are defined.
 * </p></li>
 *
 * <li><p>
 * <b>For efficiency reasons, the validity of pointers given as
 * arguments to function members is not checked.</b>
 * In particular:
 *     - pointers may be equal to <b>0</b>, which will undoubtedly be
 *       the cause of a further program abortion,
 *     - pointed nodes or edges may not belong to the current graph,
 *       with similar consequences.
 * </p></li>
 *
 * <li><p>
 * <b>The deletion of a graph causes the deletion of all its nodes and
 * edges.</b> Consequently, a program abortion may occur when:
 *     - a (pointer to a) same node or a same edge belongs
 *       to different graphs,
 *     - the nodes (resp. edges) list of a graph contains multiple
 *       occurrences of (pointers to) a same node (resp. edge), or
 *       contains null pointers,
 *     - nodes (resp. edges) of the nodes (resp. edges) list of a
 *       graph are explicitely deleted, using operator <tt>delete</tt>,
 *       before exiting the block of program containing the graph,
 *     - local variables are used to insert nodes (resp. edges)
 *       in a graph, for example:
@code
GenUGraph<int,int> g;
GenNode<int,int> n(1);
GenEdge<int,int> e(1);

g.addNode(&n);  // prohibited!
g.addEdge(&e);  // prohibited!
@endcode
 * </p></li>
 *
 * </ul>
 *
 *
 * @warning No copy constructor is provided.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   July 29, 2004  17:18
 * @since  Qgar 2.2
 */
template <class TNODE, class TEDGE>
class GenUGraph
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types */
  //        =====
  //@{
 
  /**
   * @brief Type of the data stored in a node.
   */
  typedef TNODE node_type;

  /**
   * @brief Reference to qgar::GenUGraph::node_type.
   */
  typedef node_type& node_type_reference;

  /**
   * @brief Constant reference to qgar::GenUGraph::node_type.
   */
  typedef const node_type& node_type_const_reference;

  /**
   * @brief Pointer to qgar::GenUGraph::node_type.
   */
  typedef node_type* node_type_pointer;

  /**
   * @brief Constant pointer to qgar::GenUGraph::node_type.
   */
  typedef const node_type* node_type_const_pointer;

 /**
   * @brief Type of the data stored in an edge.
   */
  typedef TEDGE edge_type;

  /**
   * @brief Reference to qgar::GenUGraph::edge_type.
   */
  typedef edge_type& edge_type_reference;

  /**
   * @brief Constant reference to qgar::GenUGraph::edge_type.
   */
  typedef const edge_type& edge_type_const_reference;

  /**
   * @brief Pointer to qgar::GenUGraph::edge_type.
   */
  typedef edge_type* edge_type_pointer;

  /**
   * @brief Constant pointer to qgar::GenUGraph::edge_type.
   */
  typedef const edge_type* edge_type_const_pointer;

  /**
   * @brief Type of the nodes list.
   */
  typedef std::list< GenNode<node_type,edge_type>* > nodes_list_type;

  /**
   * @brief Type of the edges list.
   */
  typedef std::list< GenEdge<node_type,edge_type>* > edges_list_type;

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
   * Edges and nodes lists are empty.
   */
  GenUGraph();

  /**
   * @brief Initialize from (a pointer to) a node.
   *
   * @param  aPNode  a pointer to a node: <b>must not be 0!</b>
   */
  explicit GenUGraph(GenNode<node_type,edge_type>* const aPNode);

  /**
   * @brief Initialize from (a pointer to) an edge.
   *
   * @param  aPEdge  a pointer to an edge: <b>must not be 0!</b>
   */
  GenUGraph(GenEdge<node_type,edge_type>* const aPEdge);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenUGraph();

  //@}


  /** @name Graph characteristics */
  //        =====================
  //@{

  /**
   * @brief Return <b>true</b> if the graph is empty.
   */
  inline bool empty() const;

  /**
   * @brief Return the number of nodes.
   */
  inline int sizeNodes() const;

  /**
   * @brief Return the number of edges.
   */
  inline int sizeEdges() const;

  //@}


  /** @name Node access */
  //        ===========
  //@{
  /**
   * @brief Return a pointer to the entry node,
   * or <b>0</b> if the nodes list is empty.
   */
  inline GenNode<node_type,edge_type>* pEntryNode() const;

  /**
   * @brief Get the nodes list.
   */
  inline nodes_list_type& getNodes();

  /**
   * @brief Get (a constant reference to) the nodes list.
   */
  inline const nodes_list_type& accessNodes() const;

  /**
   * @brief Get a copy of the nodes list.
   */
  inline nodes_list_type nodes() const;

  //@}


  /** @name Edge access */
  //        ===========
  //@{

  /**
   * @brief Get a pointer to the entry edge,
   * or <b>0</b> if the edges list is empty.
   */
  inline GenEdge<node_type,edge_type>* pEntryEdge() const;

  /**
   * @brief Get the edges list.
   */
  inline edges_list_type& getEdges();

  /**
   * @brief Get (a constant reference to) the edges list.
   */
  inline const edges_list_type& accessEdges() const;

  /**
   * @brief Get a copy of the edges list.
   */
  inline edges_list_type edges() const;

  //@}


  /** @name Insertion of created nodes */
  //        ==========================
  //@{
  /**
   * @brief Just insert a new node created from given data and flag.
   *
   * The (pointer to the) node is just inserted in the nodes list
   * of the graph, and is not connected to any edge.
   *
   * @param  aData   data to be contained in the node
   * @param  aFlag   value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the new node.
   */
  inline GenNode<node_type,edge_type>*
  addNode(node_type_const_reference aData, short int aFlag = 0);

  /**
   * @brief Insert a new node and link it to given edge of the graph.
   *
   * The (pointer to the) node is inserted in the nodes list of the graph.
   * The (pointer to the) edge is inserted in the edges list of the node.
   * The new node becomes the source of the given edge if the source
   * is free, otherwise it becomes the target of the edge.
   *
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   * @param  aData   data to be contained in the node
   * @param  aFlag   value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the new node.
   *
   * @warning
   * <b>The given (pointed) edge must belong to the graph.</b>
   */
  inline GenNode<node_type,edge_type>*
  addNode(GenEdge<node_type,edge_type>* const aPEdge,
	  node_type_const_reference aData,	  
	  short int aFlag = 0);

  /**
   * @brief Insert a new node between given edges of the graph.
   *
   * The (pointer to the) node is inserted in the nodes list of the graph.
   * The (pointers to the) edges are inserted in the edges list of the node.
   * The new node becomes the source of the first (resp. second) edge
   * if the source is free, otherwise it becomes the target of the first
   * (resp. second) edge.
   *
   * @param  aPEdge1  pointer to an edge: <b>must not be 0!</b>
   * @param  aPEdge2  pointer to an edge: <b>must not be 0!</b>
   * @param  aData    data to be contained in the node
   * @param  aFlag    value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the new node.
   *
   * @warning
   * <b>The 2 given (pointed) edges must belong to the graph.</b>
   */
  inline GenNode<node_type,edge_type>*
  addNode(GenEdge<node_type,edge_type>* const aPEdge1,
	  GenEdge<node_type,edge_type>* const aPEdge2,
	  node_type_const_reference aData,
	  short int aFlag = 0);

  /**
   * @brief Insert a new node as source of given edge of the graph.
   *
   * - The node is inserted in the nodes list of the graph.
   * - The edge is included in the edges list of the node.
   * - The node becomes the source of the edge.
   *
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   * @param  aData   data to be contained in the node
   * @param  aFlag   value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the node.
   *
   * @warning
   * <b>The given (pointed) edge must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNodeAtSource(GenEdge<node_type,edge_type>* const aPEdge,
		  node_type_const_reference aData,
		  short int aFlag = 0);

  /**
   * @brief Insert a new node as target of given edge of the graph.
   *
   * - The node is inserted in the nodes list of the graph.
   * - The edge is included in the edges list of the node.
   * - The node becomes the target of the edge.
   *
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   * @param  aData   data to be contained in the node
   * @param  aFlag   value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the node.
   *
   * @warning
   * <b>The given (pointed) edge must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNodeAtTarget(GenEdge<node_type,edge_type>* const aPEdge,
		  node_type_const_reference aData,
		  short int aFlag = 0);

  //@}


  /** @name Insertion of existing nodes */
  //        ===========================
  //@{

  /**
   * @brief Just insert (a pointer to) a node in the graph.
   *
   * The (pointer to the) node is just inserted in the nodes list
   * of the graph, and is not connected to any edge.
   *
   * @param  aPNode  a pointer to a node: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * <b>The given (pointed) node must not belong to the graph.</b>
   */
  inline GenNode<node_type,edge_type>*
  addNode(GenNode<node_type,edge_type>* const aPNode);

  /**
   * @brief Insert given (pointer to) node in the graph,
   *   as source or target of given (pointed) edge.
   *
   * The given edge is supposed to belong to the current graph:
   * - The node is inserted in the nodes list of the graph.
   * - The edge is inserted in the edges list of the node.
   * - <b>The node becomes the source of the edge if the edge
   *   source is free. Otherwise, the node becomes the target.</b>
   *
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) node must not belong to the graph.</b>
   * - <b>The given (pointed) edge must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNode(GenNode<node_type,edge_type>* const aPNode,
	  GenEdge<node_type,edge_type>* const aPEdge);

  /**
   * @brief Insert a node between two given edges of the graph.
   *
   * The given edges are supposed to belong to the current graph:
   * - The node is inserted in the nodes list of the graph.
   * - The edges are included in the edges list of the node.
   * - The node becomes the source of the first (resp. second)
   *   edge, if the edge source is free. Otherwise, the node
   *   becomes the target of the first (resp. second) edge.
   *
   * @param  aPNode   pointer to a node: <b>must not be 0!</b>
   * @param  aPEdge1  pointer to an edge: <b>must not be 0!</b>
   * @param  aPEdge2  pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) node must not belong to the graph.</b>
   * - <b>The given (pointed) edges must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNode(GenNode<node_type,edge_type>* const aPNode,
	  GenEdge<node_type,edge_type>* const aPEdge1,
	  GenEdge<node_type,edge_type>* const aPEdge2);

  /**
   * @brief Insert given node as source of given edge of the graph.
   *
   * The given edge is supposed to belong to the current graph:
   * - The node is inserted in the nodes list of the graph.
   * - The edge is included in the edges list of the node.
   * - The node becomes the source of the edge.
   *
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) node must not belong to the graph.</b>
   * - <b>The given (pointed) edge must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNodeAtSource(GenNode<node_type,edge_type>* const aPNode,
		  GenEdge<node_type,edge_type>* const aPEdge);

  /**
   * @brief Insert given node as target of given edge of the graph.
   *
   * The given edge is supposed to belong to the current graph:
   * - The node is inserted in the nodes list of the graph.
   * - The edge is included in the edges list of the node.
   * - The node becomes the target of the edge.
   *
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) node must not belong to the graph.</b>
   * - <b>The given (pointed) edge must belong to the graph.</b>
   */
  GenNode<node_type,edge_type>*
  addNodeAtTarget(GenNode<node_type,edge_type>* const aPNode,
		  GenEdge<node_type,edge_type>* const aPEdge);
  //@}


  /** @name Insertion of created edges */
  //        ==========================
  //@{
  /**
   * @brief Just insert a new edge created from given data and flag.
   *
   * The (pointer to the) edge is just inserted in the edges list
   * of the graph, and is not connected to any node.
   *
   * @param  aData   data to be contained in the edge
   * @param  aFlag   value of the edge flag (default <b>0</b>)
   *
   * @return a pointer to the new edge.
   */
  inline GenEdge<node_type,edge_type>*
  addEdge(edge_type_const_reference aData,	  
	  short int aFlag = 0);

  /**
   * @brief Insert a new edge in the graph, so that given (pointed)
   *   node becomes its source.
   *
   * The (pointer to the) new edge is inserted in the edges list
   * of the node, and in the edges list of the graph.
   * The given node becomes the source of the new edge.
   *
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   * @param  aData   data to be contained in the edge
   * @param  aFlag   value of the edge flag (default <b>0</b>)
   *
   * @return A pointer to the new edge.
   *
   * @warning
   * <b>The given (pointed) node must belong to the graph.</b>
   */
  inline GenEdge<node_type,edge_type>*
  addEdge(GenNode<node_type,edge_type>* const aPNode,
	  edge_type_const_reference aData,	  
	  short int aFlag = 0);

  /**
   * @brief Insert an new edge between two given nodes of the graph.
   *
   * An edge is created, with (pointers to) nodes <b>aPSource</b>
   * and <b>aPTarget</b> as source and target, respectively.
   * The new edge is inserted in the edges list of both nodes,
   * and in the edges list of the graph.
   *
   * @param  aPSource  pointer to a node: <b>must not be 0!</b>
   * @param  aPTarget  pointer to a node: <b>must not be 0!</b>
   * @param  aData     data to be contained in the edge
   * @param  aFlag     value of the node flag (default <b>0</b>)
   *
   * @return A pointer to the new edge.
   *
   * @warning
   * <b>The given (pointed) nodes must belong to the graph.</b>
   */
  inline GenEdge<node_type,edge_type>*
  addEdge(GenNode<node_type,edge_type>* const aPSource,
	  GenNode<node_type,edge_type>* const aPTarget,
	  edge_type_const_reference aData,
	  short int aFlag = 0);
  //@}


  /** @name Insertion of existing edges */
  //        ===========================
  //@{
  /**
   * @brief Insert (a pointer to) an edge in the graph.
   *
   * The (pointer to the) edge is just inserted in the edges list
   * of the graph, and is not connected to any node.
   *
   * @param  aPEdge  a pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the new edge.
   *
   * @warning
   * <b>The given (pointed) edge must not belong to the graph.</b>
   */
  inline GenEdge<node_type,edge_type>*
  addEdge(GenEdge<node_type,edge_type>* const aPEdge);

  /**
   * @brief Insert given (pointer to) edge in the graph,
   *   so as given (pointed) node becomes its source or its target.
   *
   * The given node is supposed to belong to the graph:
   * - The edge is inserted in the edges list of the graph.
   * - The edge is inserted in the edges list of the node.
   * - <b>The node becomes the source of the edge if the
   *   source is free. Otherwise, the node becomes the target.</b>
   *
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   *
   * @return A pointer to the edge.
   *
   * @warning
   * - <b>The given (pointed) edge must not belong to the graph.</b>
   * - <b>The given (pointed) node must belong to the graph.</b>
   */
  GenEdge<node_type,edge_type>*
  addEdge(GenEdge<node_type,edge_type>* const aPEdge,
	  GenNode<node_type,edge_type>* const aPNode);

  /**
   * @brief Insert an edge between two given nodes of the graph.
   *
   * The given nodes are supposed to belong to the current graph:
   * - The edge is included in the edges list of the graph.
   * - The first (resp. second) node becomes the source
   *   (resp. target) of the edge.
   * - The edge is inserted in the edges lists of the nodes.
   *
   * @param  aPEdge   pointer to an edge: <b>must not be 0!</b>
   * @param  aPNode1  pointer to a node: <b>must not be 0!</b>
   * @param  aPNode2  pointer to a node: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) edge must not belong to the graph.</b>
   * - <b>The given (pointed) nodes must belong to the graph.</b>
   */
  GenEdge<node_type,edge_type>*
  addEdge(GenEdge<node_type,edge_type>* const aPEdge,
	  GenNode<node_type,edge_type>* const aPNode1,
	  GenNode<node_type,edge_type>* const aPNode2);

  /**
   * @brief Insert given (pointer to) edge in the graph,
   *   so as given (pointed) node becomes its source.
   *
   * The given node is supposed to belong to the graph:
   * - The edge is inserted in the edges list of the graph.
   * - The edge is inserted in the edges list of the node.
   * - The node becomes the source of the given edge.
   *
   * @param  aPEdge  pointer to an edge: <b>must not be 0!</b>
   * @param  aPNode  pointer to a node: <b>must not be 0!</b>
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) edge must not belong to the graph.</b>
   * - <b>The given (pointed) node must belong to the graph.</b>
   */
  GenEdge<node_type,edge_type>*
  addEdgeBySource(GenEdge<node_type,edge_type>* const aPEdge,
		  GenNode<node_type,edge_type>* const aPNode);

  /**
   * @brief Insert given (pointer to) edge in the graph,
   *   so as given (pointed)  node becomes its target.
   *
   * The given node is supposed to belong to the graph:
   * - The edge is inserted in the edges list of the graph.
   * - The edge is inserted in the edges list of the node.
   * - The node becomes the target of the edge.
   *
   * @param  aPEdge  pointer to an edge
   * @param  aPNode  pointer to a node
   *
   * @return A pointer to the node.
   *
   * @warning
   * - <b>The given (pointed) edge must not belong to the graph.</b>
   * - <b>The given (pointed) node must belong to the graph.</b>
   */
  GenEdge<node_type,edge_type>*
  addEdgeByTarget(GenEdge<node_type,edge_type>* const aPEdge,
		  GenNode<node_type,edge_type>* const aPNode);

  //@}


  // =========================================================
  /** @name Node removal
      <b>Warning:</b> The user is in charge of the deletion of
      the removed nodes. 
   */
  // =========================================================
  //@{

  /**
   * @brief Remove given (pointer to) node from the graph,
   *   and return it.
   *
   * If the given (pointer to) node is not in the nodes list
   * of the graph, the graph remains unchanged and the function
   * returns <b>0</b>. Otherwise, each edge adjacent to the given
   * node is removed from the graph, and the given node is removed
   * from the nodes list of the graph.
   *
   * @param  aPNode  a pointer to a node: <b>must not be 0!</b>
   *
   * @return A pointer to the removed node.
   *
   * @warning
   * - <b>Each edge adjacent to the removed node is deleted.</b>
   * - The edges list of the returned (pointed) node is cleared.
   */
  inline GenNode<node_type,edge_type>*
  remove(GenNode<node_type,edge_type>* const aPNode);

  /**
   * @brief Remove (pointer to) node at given position in the nodes
   *   list of the graph, and return it.
   *
   * If the given position is the end of the nodes list  of the graph,
   * the graph remains unchanged and the function returns <b>0</b>.
   * Otherwise, each edge adjacent to the given node is removed from
   * the graph, and the given node is removed from the nodes list
   * of the graph.
   *
   * @param  aPos  a position in the nodes list of the graph
   *
   * @return A pointer to the removed node.
   *
   * @warning
   * - <b>Each edge adjacent to the removed node is deleted.</b>
   * - The edges list of the returned (pointed) node is cleared.
   *
   * @todo
   * Maybe the way adjacent edges of the nodes are deleted
   * could be more efficient. In particular, the use of function
   * qgar::GenUGraph::removeEdge implies:
   * - a copy of the edges list of the current node,
   * - an update of the edges list of the current node each time
   *   an edge is removed from the graph, whereas this edges list
   *   could be cleared in one time, once all edges are removed.
   */
  GenNode<node_type,edge_type>*
  remove(typename nodes_list_type::iterator aPos);

  //@}


  // =========================================================
  /** @name Edge removal
      <b>Warning:</b> The user is in charge of the deletion of
      the removed edges.
   */
  // =========================================================
  //@{

  /**
   * @brief Remove given (pointer to) edge from the graph,
   *   and return it.
   *
   * If the given (pointer to) edge is not in the edges list of the
   * graph, the graph remains unchanged and the function returns
   * <b>0</b>. Otherwise, the given edge is removed from the edges
   * list of its source and target nodes, and is removed from the
   * edges list of the graph.
   *
   * @param  aPEdge  a pointer to an edge: <b>should not be 0!</b>
   *
   * @return A pointer to the removed edge.
   */
  inline GenEdge<node_type,edge_type>*
  remove(GenEdge<node_type,edge_type>* const aPEdge);

  /**
   * @brief Remove (pointer to) edge at given position in the edges
   *   list of the graph, and return it.
   *
   * If the given position is the end of the edges list of the graph,
   * the graph remains unchanged and the function returns <b>0</b>.
   * Otherwise, the given edge is removed from the edges list of its
   * source and target nodes, and is removed from the edges list of
   * the graph.
   *
   * @param  aPos  a position in the edges list of the graph
   *
   * @return a pointer to the removed edge.
   */
  GenEdge<node_type,edge_type>*
  remove(typename edges_list_type::iterator aPos);
  //@}


  ///** @name Operators */
  ////        ==========
  ////@{
  //
  ///**
  // * @brief Assignment.
  // * @warning No assignment operator is defined.
  // */
  //GenUGraph<node_type,edge_type>&
  //operator=(const GenUGraph<node_type,edge_type>& aGraph);
  //
  ////@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Nodes and edges lists */
  //        =====================
  //@{

  /**
   * @brief List of the nodes of the graph.
   */
  nodes_list_type _nodes;

  /**
   * @brief List of the edges of the graph.
   */
  edges_list_type _edges;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Disabled copy constructor.
   *
   * The copy constructor belongs to the private section
   * so that clients cannot use it.
   */
  GenUGraph(const GenUGraph<node_type,edge_type>& aGraph);

  //@}

// -------------------------------------------------------------------
}; // class GenUGraph


} // namespace qgar




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenUGraph.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII




#endif /* __GENUGRAPH_H_INCLUDED__ */
