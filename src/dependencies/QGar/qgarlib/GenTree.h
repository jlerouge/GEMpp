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


#ifndef __GENTREE_H_INCLUDED__
#define __GENTREE_H_INCLUDED__


/**
 * @file GenTree.h
 *
 * @brief Header file of classes qgar::GenTreeNode and qgar::GenTree.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 3, 2001  16:23
 * @since  Qgar 2.0
 */


// For RCS/CVS use: Do not delete
/* $Id: GenTree.h,v 1.26 2006/07/04 13:37:42 masini Exp $ */



// QGAR
#include "QgarErrorUser.h"



namespace qgar
{


/*---------------------------------------------------------------------*
 |                                                                     |
 |         C  L  A  S  S      G  E  N  T  R  E  E  N  O  D  E          |
 |                                                                     |
 *---------------------------------------------------------------------*/


/**
 * @ingroup DS_GRAPH
 *
 * @class GenTreeNode GenTree.h
 *
 * @brief Template class for a node of a Qgar Tree
 *        (see class qgar::GenTree).
 *
@verbatim
                      o parent
                     /|\ 
                    / | \
             /     /  |  \     \
            /     /   |   \     \
           o ... o   NODE  o ... o
                 ^   /|\   ^
      left sibling  / | \  right sibling
                   /  |  \
                  /   |   \     \
   first child > o    o    o ... o
                /|\  /|\  /|\ 
@endverbatim
 * A node is a container including:
 * - a link to its parent node in the tree,
 * - a link to its left sibling node in the tree,
 * - a link to its right sibling node in the tree,
 * - a link to its first (leftmost) child node in the tree,
 * - data of type <b>T</b>, representing the information
 *   associated with the node.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 3, 2001  16:23
 * @since  Qgar 2.0
 */
template <class T> class GenTreeNode
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
   *
   * Create an empty node with no link and default data.
   */
  GenTreeNode();

  /**
   * @brief Create a node with given data and no link.
   *
   * @param aData  data to be stored in the node
   */
  GenTreeNode(const T& aData);

  /**
   * @brief Create a node with given links and data.
   *
   * @param aPParent      pointer to the parent in tree
   * @param aPLSibling    pointer to the left sibling in tree
   * @param aPRSibling    pointer to the right sibling in tree
   * @param aPFirstChild  pointer to the FirstChild in tree    
   * @param aData         data stored in the node
   */
  GenTreeNode(GenTreeNode<T>* aPParent,
	      GenTreeNode<T>* aPLSibling,
	      GenTreeNode<T>* aPRSibling,
	      GenTreeNode<T>* aPFirstChild,
	      const T& aData);

  /**
   * @brief Copy constructor.
   *
   * @param aNode  a node
   */
  GenTreeNode(const GenTreeNode<T>& aNode);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenTreeNode();

  //@}
    

  /** @name Access to links */
  //        ===============
  //@{ 

  /**
   * @brief Get link to parent.
   */
  inline GenTreeNode<T>* pParent() const;

  /**
   * @brief Get link to left sibling.
   */
  inline GenTreeNode<T>* pLSibling() const;

  /**
   * @brief Get link to right sibling.
   */
  inline GenTreeNode<T>* pRSibling() const;

  /**
   * @brief Get link to first child.
   */
  inline GenTreeNode<T>* pFirstChild() const;

  //@}


  /** @name Set links */
  //        =========
  //@{

  /**
   * @brief Set link to parent.
   *
   * @param aPNode  a pointer to a node
   */
  inline void setPParent(GenTreeNode<T>* aPNode);

  /**
   * @brief Set link to left sibling.
   *
   * @param aPNode  a pointer to a node
   */
  inline void setPLSibling(GenTreeNode<T>* aPNode);

  /**
   * @brief Set link to right sibling.
   *
   * @param aPNode  a pointer to a node
   */
  inline void setPRSibling(GenTreeNode<T>* aPNode);

  /**
   * @brief Set link to first child.
   *
   * @param aPNode  a pointer to a node
   */
  inline void setPFirstChild(GenTreeNode<T>* aPNode);

  //@}


  /** @name Access to data stored in nodes */
  //        ==============================
  //@{

  /**
   * @brief Get data.
   */
  inline const T& accessData() const;

  /**
   * @brief Get a copy of data.
   */
  inline T data() const;

  //@}


  /** @name Store data in nodes */
  //        ===================
  //@{

  /**
   * @brief Store data in current node.
   *
   * @param aData  data to be stored
   */
  inline void setData(const T& aData);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aNode  a node
   */
  GenTreeNode& operator=(const GenTreeNode<T>& aNode);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of a node */
  //        ========================
  //@{

  /**
   * @brief Pointer to parent.
   */
  GenTreeNode<T>* _pParent;

  /**
   * @brief Pointer to left sibling.
   */
  GenTreeNode<T>* _pLSibling;

  /**
   * @brief Pointer to right sibling.
   */
  GenTreeNode<T>* _pRSibling;

  /**
   * @brief Pointer to first (leftmost) child.
   */
  GenTreeNode<T>* _pFirstChild;

  /**
   * @brief Data contained by node.
   */
  T _data;

  //@}


// -------------------------------------------------------------------

}; // Class GenTreeNode





/*---------------------------------------------------------------------*
 |                                                                     |
 |               C  L  A  S  S      G  E  N  T  R  E  E                |
 |                                                                     |
 *---------------------------------------------------------------------*/


/**
 * @class GenTree GenTree.h "qgarlib/GenTree.h"
 *
 * @ingroup DS_GRAPH
 *
 * @brief A tree whose nodes contain data of type <b>T</b>.
 *
 * Such a tree is represented by:
 * - a pointer to the root node of the tree,
 * - a pointer to the current node, <i>i.e.</i> last accessed node.
 *
 * See class qgar::GenTreeNode for the way the inner nodes
 * are linked together.
 *
 * @warning
 *
 * <ul>
 * <li>
 * <p><b>For efficiency reasons, the validity of pointers given as
 * arguments to function members is not checked.</b>
 * In particular:
 *     - pointers may be equal to <b>0</b>, which will undoubtedly be
 *       the cause of a further program abortion,
 *     - pointed nodes may not belong to the current graph,
 *       with similar consequences.</p>
 * </li>
 * <li>
 * <p><b>The deletion of a tree causes the deletion of all its nodes.</b>
 * Consequently, a program abortion may occur when:
 *     - an ill-formed tree contains multiple occurrences of
 *       (pointers to) a same node, or contains null pointers,
 *     - nodes are explicitely deleted, using operator <b>delete</b>,
 *       before exiting the block of program containing the tree.</p>
 * </li>
 * </ul>
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   Jul 3, 2001  16:23
 * @since  Qgar 2.0
*/
template <class T> class GenTree
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:


  /** @name Types */
  //        =====
  //@{

  /**
   * @brief Type of the data stored in nodes.
   */
  typedef T value_type;

  /**
   * @brief Reference to qgar::GenTree::value_type.
   */
  typedef value_type& reference;

  /**
   * @brief Constant reference to qgar::GenTree::value_type.
   */
  typedef const value_type& const_reference;

  /**
   * @brief Pointer to qgar::GenTree::value_type.
   */
  typedef value_type* pointer;

  /**
   * @brief Constant pointer to qgar::GenTree::value_type.
   */
  typedef const value_type* const_pointer;

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
   * Create an empty tree.
   */
  GenTree();

  /**
   * @brief Copy constructor.
   *
   * The current node of the resulting tree is its root.
   *
   * @warning Perform a <b>deep copy</b>:
   * All the nodes of the given tree are duplicated.
   */
  GenTree(const GenTree<value_type>& aTree);

  /**
   * @brief Create a tree with a single node
   *        containing the given data.
   *
   * This node becomes the current node.
   *
   * @param aData  data to be stored in the node
   */
  explicit GenTree(const_reference aData);

  /**
   * @brief Create a tree from a given node.
   *
   * If the pointer is <b>0</b>, create an empty tree.
   * Otherwise, the given node is considered as a root of a tree,
   * which is copied to become the current tree.
   * The current node is the root.
   *
   * @param  aPNode a pointer to a node
   *
   * @warning <b>Perform a deep copy</b>.
   */
  explicit GenTree(GenTreeNode<value_type>* aPNode);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Virtual destructor.
   */
  virtual ~GenTree();

  //@}


  /** @name Predicates */
  //        ==========
  //@{

  /**
   * @brief Is tree empty?
   */
  bool empty() const;

  //@}


  // =======================================================
  /** @name Access to links
      <b>WARNING</b>
      The behavior of functions taking a pointer to a node
      as extra argument is undefined if:
      <ul>
      <li>the tree is empty,</li>
      <li>or the given node does not belong to the tree.</li>
      </ul>
  */
  // =======================================================
  //@{

  /**
   * @brief Get pointer to the root of the tree.
   */
  inline GenTreeNode<value_type>* pRoot() const;

  /**
   * @brief Get pointer to the current node.
   */
  inline GenTreeNode<value_type>* pCurrent() const;

  /**
   * @brief Get pointer to the parent of the current node.
   */
  inline GenTreeNode<value_type>* pParent() const;

  /**
   * @brief Get pointer to the parent of the given node.
   *
   * @param aPNode  a pointer to a node
   */
  inline GenTreeNode<value_type>*
  pParent(GenTreeNode<value_type>* aPNode) const;

  /**
   * @brief Get pointer to the left sibling of the current node.
   */
  inline GenTreeNode<value_type>* pLSibling() const;
  
  /**
   * @brief Get pointer to the left sibling of the given node.
   *
   * @param aPNode  a pointer to a node
   */
  inline GenTreeNode<value_type>*
  pLSibling(GenTreeNode<value_type>* aPNode) const;

  /**
   * @brief Get pointer to the right sibling of the current node.
   */
  inline GenTreeNode<value_type>* pRSibling() const;

  /**
   * @brief Get pointer to the right sibling of the given node.
   *
   * @param aPNode  a pointer to a node
   */
  inline GenTreeNode<value_type>*
  pRSibling(GenTreeNode<value_type>* aPNode) const;

  /**
   * @brief Get pointer to the first child of the current node.
   */
  inline GenTreeNode<value_type>* pFirstChild() const;

  /**
   * @brief Get pointer to the first child of the given node.
   *
   * @param aPNode  a pointer to a node
   */
  inline GenTreeNode<value_type>*
  pFirstChild(GenTreeNode<value_type>* aPNode) const;

  //@}


  // =======================================================
  /** @name Access to data
      <b>WARNING</b>
      The behavior of functions taking a pointer to a node
      as extra extra argument is undefined if:
      <ul>
      <li>the tree is empty,</li>
      <li>or the given node does not belong to the tree.</li>
      </ul>
  */
  // =======================================================
  //@{

  /**
   * @brief Get data stored in current node.
   */
  inline const_reference accessData() const;

  /**
   * @brief Get data stored in given node.
   *
   * @param aPNode  a pointer to a node
   */
  inline const_reference accessData(GenTreeNode<value_type>* aPNode) const;

  /**
   * @brief Get a copy of the data stored in current node.
   */
  inline value_type data() const;

  /**
   * @brief Get a copy of the data stored in current node.
   *
   * @param aPNode  a pointer to a node
   */
  inline value_type data(GenTreeNode<value_type>* aPNode) const;

  //@}


  // ===================================================================
  /** @name Moving in the tree
      <b>WARNING</b>
      <ul>
      <li>If the destination node does not exist, the pointer
          to the current node is set to <i>0</i>.</li>
      <li>When a pointer to a node is given as argument,
          the corresponding node is supposed to belong to the tree!</li>
      </ul>
  */
  // ===================================================================
  //@{

  /**
   * @brief The root becomes the current node.
   */
  inline void gotoRoot();

  /**
   * @brief The parent of the current node becomes the current node.
   */
  inline void gotoParent();

  /**
   * @brief The parent of the given node becomes the current node.
   *
   * @param aPNode  a pointer to a node
   */
  inline void gotoParent(GenTreeNode<value_type>* aPNode);

  /**
   * @brief The left sibling of the current node becomes the current node.
   */
  inline void gotoLSibling();

  /**
   * @brief The left sibling of the given node becomes the current node.
   *
   * @param aPNode  a pointer to a node
   */
  inline void gotoLSibling(GenTreeNode<value_type>* aPNode);

  /**
   * @brief The right sibling of the current node becomes the current node.
   */
  inline void gotoRSibling();

  /**
   * @brief The right sibling of the given node becomes the current node.
   *
   * @param aPNode  a pointer to a node
   */
  inline void gotoRSibling(GenTreeNode<value_type>* aPNode);

  /**
   * @brief The first child of the current node becomes the current node.
   */
  inline void gotoFirstChild();

  /**
   * @brief The first child of the given node becomes the current node.
   *
   * @param aPNode  a pointer to a node
   */
  inline void gotoFirstChild(GenTreeNode<value_type>* aPNode);
  //@}


  // =======================================================
  /** @name Store data in nodes
      <b>WARNING</b>
      The behavior of functions taking a pointer to a node
      as extra extra argument is undefined if:
      <ul>
      <li>the tree is empty,</li>
      <li>or the given node does not belong to the tree.</li>
      </ul>
  */
  // =======================================================
  //@{

  /**
   * @brief Store data in current node.
   *
   * @param aData  data to be stored in current node
   */
  inline void setData(const_reference aData);

  /**
   * @brief Store data in given node.
   *
   * @param aData   data to be stored in current node
   * @param aPNode  a pointer to a node
   */
  inline void
  setData(const_reference aData, GenTreeNode<value_type>* aPNode);

  //@}


  // ==========================================================
  /** @name Insert new nodes
      <b>WARNING</b>
      When a pointer to a node is given as argument,
      the corresponding node is supposed to belong to the tree!
  */
  // ==========================================================
  //@{

  /**
   * @brief Insert a node containing given data
   *   as parent of current root.
   *
@verbatim
                            NEW
                             |                                             
                             |                                             
   ROOT        ===>         ROOT
   /|\                      /|\
@endverbatim
   *
   * If the tree is empty, the new node becomes the only node
   * of the tree, <i>i.e.</i> the root and the current node.
   *
   * Otherwise:
   * - The new node becomes the parent of the current root.
   * - The current root becomes the first child of the new node.
   * - The new node becomes the new root of the tree.
   * - The current node remains unchanged.
   *
   * @param aData  data to be stored in the new node
   */
  void insertParent(const_reference aData);


  /**
   * @brief Insert a node containing given data as left sibling
   *   of current node, <b>which must not be the root</b>.
   *
@verbatim
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->NEW<-->CUR<-->rs<-
   /|\    /|\   /|\           /|\           /|\   /|\
@endverbatim
   *
   * If the tree is empty, the new node becomes the only node
   * of the tree, <i>i.e.</i> the root and the current node.
   *
   * Otherwise:
   * - If the current node has a left sibling, the latter becomes the left
   *   sibling of the new node; otherwise, the new node becomes the first
   *   child of the parent node.
   * - The current node becomes the right sibling of the new node.
   * - The parent of the current node becomes the parent of the new node.
   * - The current node remains unchanged.
   *
   * @param aData  data to be stored in the new node
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void insertLSibling(const_reference aData);


  /**
   * @brief Insert a node containing given data as left sibling
   *   of given node, <b>which must not be the root</b>.
   *
@verbatim
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->NEW<-->GIV<-->rs<-
   /|\    /|\   /|\           /|\           /|\   /|\
@endverbatim
   *
   * - If the given node has a left sibling, the latter becomes the left
   *   sibling of the new node; otherwise, the new node becomes the first
   *   child of the parent node.
   * - The given node becomes the right sibling of the new node.
   * - The parent of the given node becomes the parent of the new node.
   * - The given node becomes the current node
   *
   * @param aData   data to be stored in the new node
   * @param aPNode  a pointer to a node
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  inline void insertLSibling(const_reference aData,
			     GenTreeNode<value_type>* aPNode)
   ;


  /**
   * @brief Insert a node containing given data as right sibling
   *   of current node, <b>which must not be the root</b>.
   *
@verbatim
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->CUR<-->NEW<-->rs<-
   /|\    /|\   /|\           /|\    /|\          /|\
@endverbatim
   *
   * If the tree is empty, the new node becomes the only node
   * of the tree, <i>i.e.</i> the root and the current node.
   *
   * Otherwise:
   * - The right sibling of the current node becomes the right
   *   sibling of the new node.
   * - The current node becomes the left sibling of the new node.
   * - The parent of the current node becomes the parent of the new node.
   * - The current node remains unchanged.
   *
   * @param aData  data to be stored in the new node
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void insertRSibling(const_reference aData);


  /**
   * @brief Insert a node containing given data as right sibling
   *   of given node, <b>which must not be the root</b>.
   *
@verbatim
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->GIV<-->NEW<-->rs<-
   /|\    /|\   /|\           /|\    /|\          /|\
@endverbatim
   *
   * - The right sibling of the given node becomes the right
   *   sibling of the new node.
   * - The given node becomes the left sibling of the new node.
   * - The parent of the given node becomes the parent of the new node.
   * - The given node becomes the current node.
   *
   * @param aData   data to be stored in the new node
   * @param aPNode  a pointer to a node
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  inline void insertRSibling(const_reference aData,
			     GenTreeNode<value_type>* aPNode)
   ;


  /**
   * @brief Insert a node containing given data as first child
   *   of current node.
   *
@verbatim
     CUR                         CUR
      |\                         /|\
      | \                       / | \
      |  \         ===>        /  |  \
      |   \                   /   |   \
      |    \                 /    |    \
     fc<-->rs<-            NEW<-->fc<-->rs<-
    /|\   /|\                    /|\   /|\
@endverbatim
   *
   * If the tree is empty, the new node becomes the only node
   * of the tree, <i>i.e.</i> the root and the current node.
   *
   * Otherwise:
   * - The first child of the current node becomes the right sibling
   *   of the given node.
   * - The new node becomes the first child of the current node.
   * - The current node remains unchanged.
   *
   * @param aData  data to be stored in the new node
   */
  void insertFirstChild(const_reference aData);


   /**
   * @brief Insert a node containing given data
   *  as first child of given node.
   *
@verbatim
     GIV                         GIV
      |\                         /|\
      | \                       / | \
      |  \         ===>        /  |  \
      |   \                   /   |   \
      |    \                 /    |    \
     fc<-->rs<-            NEW<-->fc<-->rs<-
    /|\   /|\                    /|\   /|\
@endverbatim
   *
   * - The first child of the given node becomes the right sibling
   *   of the given node.
   * - The new node becomes the first child of the given node.
   * - The given node becomes the current node.
   *
   * @param aData   data to be stored in the new node
   * @param aPNode  a pointer to a node
   */
  inline void insertFirstChild(const_reference aData,
			       GenTreeNode<value_type>* aPNode);

 //@}


  // ===================================================================
  /** @name Merge
      <b>WARNING</b>
      <ul>
      <li>All the nodes of the given tree are duplicated.</li>
      <li>When a pointer to a node is given as argument,
          the corresponding node is supposed to belong to the tree!</li>
      </ul>
   */
  // ===================================================================
  //@{

  /**
   * @brief Merge given tree as left sibling of current node,
   *   <b>which must not be the root</b>.
   *
@verbatim
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->GIV<-->CUR<-->rs<-
   /|\    /|\   /|\           /|\    /|\    /|\   /|\
                                    / | \
                                  c1  c2 c3
          GIV
          /|\
         / | \
       c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * If the current tree is empty, the given tree becomes the current tree.
   * The new root becomes the current node.
   *
   * Otherwise:
   * - The left sibling of the current node becomes the left sibling
   *   of the root of the given tree.
   * - The current node becomes the right sibling of the root of the given tree.
   * - The parent of the current node becomes the parent
   *   of the root of the given tree.
   * - The current node remains unchanged.
   *
   * @param aTree  a tree
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void mergeLSibling(const GenTree<value_type>& aTree);


  /**
   * @brief Merge given tree as left sibling of given node,
   *   <b>which must not be the root</b>.
   *
@verbatim
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->NEW<-->GIV<-->rs<-
   /|\    /|\   /|\           /|\    /|\    /|\   /|\
                                    / | \
                                  c1  c2 c3
          NEW
          /|\
         / | \
       c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * Otherwise:
   * - The left sibling of the given node becomes the left sibling
   *   of the root of the given tree.
   * - The given node becomes the right sibling of the root of the given tree.
   * - The parent of the given node becomes the parent
   *   of the root of the given tree.
   * - The given node becomes the current node.
   *
   *.@warning The given node is supposed to belong
   * to the current tree!
   *
   * @param aTree   a tree
   * @param aPNode  a pointer to a node
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void mergeLSibling(const GenTree<value_type>& aTree,
		     GenTreeNode<value_type>* aPNode)
   ;


  /**
   * @brief Merge given tree as right sibling of current node,
   *   <b>which must not be the root</b>.
   *
@verbatim
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->CUR<-->GIV<-->rs<-
   /|\    /|\    /|\          /|\    /|\    /|\    /|\
                                           / | \
                                         c1  c2 c3
                 GIV
                 /|\
                / | \
              c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * If the current tree is empty, the given tree becomes the current tree.
   * The new root becomes the current node.
   *
   * Otherwise:
   * - The right sibling of the current node becomes the right
   *   sibling of the root of the given tree.
   * - The current node becomes the left sibling of the root of the given tree.
   * - The parent of the current node becomes the parent
   *   of the root of the given tree.
   * - The current node remains unchanged.
   *
   * @param aTree  a tree
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void mergeRSibling(const GenTree<value_type>& aTree);


  /**
   * @brief Merge given tree as right sibling of current node,
   *   <b>which must not be the root</b>.
   *
@verbatim
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->GIV<-->NEW<-->rs<-
   /|\    /|\    /|\          /|\    /|\    /|\    /|\
                                           / | \
                                         c1  c2 c3
                 NEW
                 /|\
                / | \
              c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * Otherwise:
   * - The right sibling of the given node becomes the right
   *   sibling of the root of the given tree.
   * - The given node becomes the left sibling of the root of the given tree.
   * - The parent of the given node becomes the parent
   *   of the root of the given tree.
   * - The given node becomes the current node.
   *
   * @param aTree   a tree
   * @param aPNode  a pointer to a node
   *
   * @warning The given node is supposed to belong
   * to the current tree!
   *
   * @exception qgar::QgarErrorUser  current node is the root
   */
  void mergeRSibling(const GenTree<value_type>& aTree,
		     GenTreeNode<value_type>* aPNode)
   ;


  /**
   * @brief Merge given tree as first child of current node.
   *
@verbatim
     CUR                        CUR
      |\                        /|\
      | \                      / | \
      |  \         ===>       /  |  \
      |   \                  /   |   \
      |    \                /    |    \
     fc<-->rs<-          GIV<-->fc<-->rs<-
     /|\                 /|\    /|\
                        / | \
                      c1  c2 c3
     GIV
     /|\
    / | \
  c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * If the current tree is empty, the given tree becomes the current tree.
   * The new root becomes the current node.
   *
   * Otherwise:
   * - The first child of the current node becomes the right sibling
   *   of the root of the given tree.
   * - The root of the given tree becomes the first child of the current node.
   * - The current node becomes the parent of the root of the given tree.
   * - The current node remains unchanged.
   *
   * @param aTree  a tree
   */
  void mergeFirstChild(const GenTree<value_type>& aTree);


  /**
   * @brief Merge given tree as first child of current node.
   *
@verbatim
     GIV                        GIV
      |\                        /|\
      | \                      / | \
      |  \         ===>       /  |  \
      |   \                  /   |   \
      |    \                /    |    \
     fc<-->rs<-          NEW<-->fc<-->rs<-
     /|\                 /|\    /|\
                        / | \
                      c1  c2 c3
     NEW
     /|\
    / | \
  c1  c2 c3
@endverbatim
   *
   * If the given tree is empty, the function has no effect.
   *
   * Otherwise:
   * - The first child of the given node becomes the right sibling
   *   of the root of the given tree.
   * - The root of the given tree becomes the first child of the given node.
   * - The given node becomes the parent of the root of the given tree.
   * - The given node becomes the current node.
   *
   * @param aTree   a tree
   * @param aPNode  a pointer to a node
   *
   * @warning The given node is supposed to belong
   * to the current tree!
   */
  void mergeFirstChild(const GenTree<value_type>& aTree,
		       GenTreeNode<value_type>* aPNode);

  //@}


  /** @name Remove nodes */
  //        ============
  //@{
  /**
   * @brief Remove current node and return it.
   *
@verbatim
           p                          p
          /|\                        /|
         / | \                      / |
        /  |  \         ===>       /  |
       /   |   \                  /   |
      /    |    \                /    |
  ->ls<-->CUR<-->rs<-        ->ls<-->rs<-
   /|\    /|\   /|\           /|\   /|\
@endverbatim
   *
   * No effect if the tree is empty.
   *
   * @warning
   * - <b>The (sub)tree whose root is the initial current
   *   node is not deleted: The deletion must be explicitely
   *   performed by the user.</b>
   * - <b>The root becomes the current node after the removal.</b>
   */ 
  GenTreeNode<value_type>* remove();

  /**
   * @brief Remove given node and return it.
   *
@verbatim
           p                          p
          /|\                        /|
         / | \                      / |
        /  |  \         ===>       /  |
       /   |   \                  /   |
      /    |    \                /    |
  ->ls<-->GIV<-->rs<-        ->ls<-->rs<-
   /|\    /|\   /|\           /|\   /|\
@endverbatim
   *
   * @param aPNode  a pointer to a node
   *
   * @warning
   * - <b>The (sub)tree whose root is the given node is not deleted:
   *   The deletion must be explicitely performed by the user.</b>
   * - If the given node is the current node, the root becomes
   *   the current node after the removal. Otherwise, the current node
   *   remains unchanged.
   * - The given node is supposed to belong to the current tree!
   */ 
  GenTreeNode<value_type>* remove(GenTreeNode<value_type>* aPNode);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * The current node of the resulting tree is its root.
   *
   * @param aTree  a tree
   *
   * @warning Perform a <b>deep copy</b>:
   * All the nodes of the given tree are duplicated.
   */ 
  GenTree<value_type>& operator=(const GenTree<value_type>& aTree);

  //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:


  /** @name Representation of a tree */
  //        ========================
  //@{

  /**
   * @brief Pointer to the root of the tree.
   */
  GenTreeNode<value_type>* _pRoot;

  /**
   * @brief Pointer to the current node.
   */
  GenTreeNode<value_type>* _pCurrent;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:


  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Perform a deep copy of a part of the tree
   * and return a pointer to the root of the copy.
   *
   * @param aPNode    pointer a node, representing the root
   *                  of the subtree to be copied
   * @param aPFCopy   pointer to link the copy of the given node
   *                  to its parent (default <b>0</b>)
   * @param aPLSCopy  pointer to link the copy of the given node
   *                  to its left sibling (default <b>0</b>)
   */
  GenTreeNode<value_type>*
  PRIVATEdeepCopy(GenTreeNode<value_type>* aPNode,
		  GenTreeNode<value_type>* aPFCopy = 0,
		  GenTreeNode<value_type>* aPLSCopy = 0) const;

  /**
   * @brief Delete the (sub)tree of given root
   *
   * @param aPNode  pointer to the root of the subtree to be deleted
   */
  void PRIVATEdelete(GenTreeNode<value_type>* aPNode);

  //@}


// -------------------------------------------------------------------

}; // class GenTree


} // namespace qgar 




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// I M P L E M E N T A T I O N S
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

#include "GenTree.tcc"

// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


#endif /* __GENTREE_H_INCLUDED__ */
