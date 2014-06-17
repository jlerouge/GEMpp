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


#ifndef __CONNECTEDCOMPONENTS_H_INCLUDED__
#define __CONNECTEDCOMPONENTS_H_INCLUDED__

/**
 * @file ConnectedComponents.h
 *
 * @brief Header file of class qgar::ConnectedComponents.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 21, 2004  12:58
 * @since  Qgar 2.1.1
 */


// For RCS/CVS use: Do not delete
/* $Id: ConnectedComponents.h,v 1.16 2007/02/14 17:34:04 masini Exp $ */


// STD
#include <vector>
// QGAR
#include "Component.h"
#include "GenImage.h"
#include "GenTree.h"



namespace qgar
{


/**
 * @ingroup GRAPHPROC_CC
 *
 * @class ConnectedComponents ConnectedComponents.h "qgarlib/ConnectedComponents.h"
 *
 * @brief Connected components extracted from a binary image.
 *
 * A (connected) component is a region defined by a set of connected
 * pixels having the same color.
@verbatim
      b b b                    x w x
      b B b                    w W w
      b b b                    x w x

 8-connectivity            4-connectivity
    for BLACK                for WHITE
@endverbatim
 * <ul>
 * <li>
 * Black components are constructed using 8-connectivity: when black,
 * the central point (<b>B</b> on the figure) is connected
 * to its 8 black neighbors marked <b>b</b>.
 * </li>
 * <li>
 * White components are constructed using 4-connectivity: When white,
 * the central point (<b>W</b> on the figure) is connected to its 4 white
 * neighbors marked <b>w</b> and is not connected to the 4 white
 * neighbors marked <b>x</b>.
 * </li>
 * </ul>
 *
 * Each component is associated with a label, which is
 * an integer number of type qgar::Component::label_type.
 * See class qgar::Component for the way a component is represented.
 *
@verbatim
                 componentTree_
                ________________
               |                |    0     j     k
+----------+   |      +--+      |   +--+--+--+--+--+- -+--+
|COMPONENT |<----------C0|<----------- |  |  |  |  |   |  |  componentTab_
|LABELLED 0|   |      +--+      |   +--+--+|-+--+|-+- -+--+
+----------+   |       /\       |          |     |
               |      /  \      |          |     |
+----------+   |  +--+    +--+  |          |     |
|COMPONENT |<------Ci|    |Cj|<------------+     |
|LABELLED i|   |  +--+    +--+  |                |
+----------+   |    |     /||\  |                |
+----------+   |  +--+          |                |
|COMPONENT |<------Ck|<--------------------------+
|LABELLED k|   |  +--+          |
+----------+   |________________|
@endverbatim
 *
 * The set of components is hierarchically organized as a tree,
 * the so-called <i>component tree</i> (see functions
 * qgar::ConnectedComponents::accessComponentTree
 * and qgar::ConnectedComponents::componentTree).
 * Each node represents a component (in fact, the data associated
 * with the node is a pointer to the component, <b>Ci</b> in the
 * figure above), and its children represent the components which
 * are directly included into the component, that is to say
 * has a common border with it.
 *
 * The root of the tree is always a white component labelled <b>0</b>.
 * It represents the background of the given binary image, in which
 * all the other components are (transitively) included.
 *
 * To be sure to get a component representing the background,
 * the first and last rows of the given binary image, as well as
 * its first and last columns, are considered as being white.
 *
 * The so-called <i>component table</i>
 * (see functions qgar::ConnectedComponents::accessComponentTab
 * and qgar::ConnectedComponents::componentTab).
 * provides a direct access to the nodes representing the
 * components, using their labels to index the table.
 * In other words, an element of this table is a pointer
 * to the node of the tree representing the component
 * having the same label as the table index of the element.
 * Operator qgar::ConnectedComponents::operator[] gives a direct
 * access to a component using its label.
 *
 * The location of the components is given by the so-called
 * <i>component image</i>
 * (see qgar::ConnectedComponents::componentImg_):
 * the value of a pixel is the label of the component to which
 * the pixel belongs.
 *  
 *
 * @warning No default constructor is provided.
 *
 *
 * @todo
 * Give the user the choice between implementing components as
 * labelled regions in an image (like now) and implementing
 * components through tables of runs and labels (presently,
 * these tables are deleted once components are constructed)
 *
 * @todo
 * qgar::ConnectedComponents::PRIVATEcopyCC perfoms a deep copy
 * of a tree. This method should be moved to class qgar::GenTree.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   April 21, 2004  12:58
 * @since  Qgar 2.1.1
 */
class ConnectedComponents
{
// -------------------------------------------------------------------
// T Y P E   D E F I N I T I O N S
// -------------------------------------------------------------------
public:

  /** @name Types related to connected components */
  //        =====================================
  //@{

  /**
   * @brief Type of the pixels of the component image.
   */
  typedef GenImage<Component::label_type> image_type;

  /**
   * @brief Reference to qgar::ConnectedComponents::image_type.
   */
  typedef image_type& reference;

  /**
   * @brief Constant reference to qgar::ConnectedComponents::image_type.
   */
  typedef const image_type& const_reference;

  /**
   * @brief Pointer to qgar::ConnectedComponents::image_type.
   */
  typedef image_type* pointer;

  /**
   * @brief Constant pointer to qgar::ConnectedComponents::image_type.
   */
  typedef const image_type* const_pointer;

  /**
   * @brief Type of the component tree.
   */
  typedef GenTree<Component*> tree_type;

  /**
   * @brief Type of a node of the component tree.
   */
  typedef GenTreeNode<Component*> node_type;

  //@}


// -------------------------------------------------------------------
// P U B L I C    M E M B E R S
// -------------------------------------------------------------------
public:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Construct from given binary image.
   */
  DLL_EXPORT explicit ConnectedComponents(const BinaryImage& aBinImg);

  /**
   * @brief Copy constructor.
   *
   * @param aCC  connected components to be copied
   *
   * @warning
   * Perform a <b>deep copy</b>: the component image (including its pixel
   * map), the component tree and all the components are duplicated.
   */
  ConnectedComponents(const ConnectedComponents& aCC);

  //@}


  /** @name Destructor */
  //        ==========
  //@{

  /**
   * @brief Non-virtual destructor.
   */
  DLL_EXPORT ~ConnectedComponents();

  //@}


  /** @name Access to the component image */
  //        =============================
  //@{

  /**
   * @brief Get the component image.
   */
  inline const image_type& accessComponentImage() const;

  /**
   * @brief Get a copy of the component image.
   */
  inline image_type componentImage() const;

  //@}


  /** @name Access to the component tree */
  //        ============================
  //@{

  /**
   * @brief Get the component tree.
   */
  inline const tree_type& accessComponentTree() const;

  /**
   * @brief Get a copy of the component tree.
   */
  inline tree_type componentTree() const;

  /**
   * @brief Get a pointer to the root of the component tree.
   */
  inline node_type* pRoot() const;

  /**
   * @brief Get a pointer to the node of the component tree
   * representing the component of given label.
   *
   * @param aLabel  a component label
   *
   * @warning If the label is out of the range of current labels,
   * the function behavior is undefined.
   */
  inline node_type* pNode(Component::label_type aLabel) const;

  //@}


  /** @name Access to components */
  //        ====================
  //@{

  /**
   * @brief Get number of components.
   */
  inline int componentCnt() const;

  /**
   * @brief Get the component table.
   */
  inline const std::vector<node_type*>& accessComponentTab() const;

  /**
   * @brief Get a copy of the component table.
   */
  inline std::vector<node_type*> componentTab() const;

  /**
   * @brief Get a pointer to the component of given label.
   *
   * @param aLabel  a component label
   *
   * @warning If the label is out of the range of current labels,
   * the function behavior is undefined.
   */
  inline Component* pComponent(Component::label_type aLabel) const;

  //@}


  /** @name Reconstruct a binary image from components */
  //        ==========================================
  //@{

  /**
   * @brief Return a pointer to a binary image reconstructed from
   * components corresponding to given labels.
   *
   * @param aLabSet  a vector of component labels
   * 
   * A pixel of the resulting image is black (see qgar::QGEbw)
   * if it belongs to a black component whose label is in the set
   * of given labels. Otherwise, the pixel is white.
   *
   * @warning
   * Given labels out of the range of current labels are ignored.
   *
   * @warning
   * The client is responsible for the deletion of the image provided.
   */
  DLL_EXPORT BinaryImage*
  makeBinaryImg(const std::vector<Component::label_type>& aLabSet);

  //@}


  /** @name Operators */
  //        =========
  //@{

  /**
   * @brief Assignment.
   *
   * @param aCC  connected components to be assigned
   *
   * @warning Perform a <b>deep copy</b>:
   * The component image (including its pixel map), the component
   * tree and all the components are duplicated.
   */
  ConnectedComponents& operator=(const ConnectedComponents& aCC);

  /**
   * @brief Get component of given label.
   *
   * @param aLabel  a component label
   *
   * @warning If the label is out of the range of current labels,
   * the operator behavior is undefined.
    */
  inline Component& operator[](Component::label_type aLabel);

  /**
   * @brief Get component of given label
   *  (to be applied to a constant object).
   *
   * @param aLabel  a component label
   *
   * @warning If the label is out of the range of current labels,
   * the operator behavior is undefined.
    */
  inline const Component& operator[](Component::label_type aLabel) const;

   //@}


// -------------------------------------------------------------------
// P R O T E C T E D    M E M B E R S
// -------------------------------------------------------------------
protected:

  /** @name Representation of the components */
  //        ================================
  //@{

  /**
   * @brief Component image.
   *
   * It gives the location of the components: the value of a pixel
   * is the label of the component to which the pixel belongs.
   */
  image_type componentImg_;

  /**
   * @brief Tree of the components.
   *
   * The root component is always labelled <b>0</b> and represents
   * the (white) background of the image. The children of a given
   * component represent the components which are directly included
   * in the given component, that is to say have a common border
   * with the given component.
   */
  tree_type componentTree_;

  /**
   * @brief Table of the components.
   *
   * Vector of pointers to the nodes (of the component tree)
   * representing the components labelled by the corresponding indexes
   * in the vector: <b>componentTab_[i]</b> points
   * to the node representing the component labelled <b>i</b>.
   */
  std::vector<node_type*> componentTab_;

  //@}


  /** @name 3X3 neighborhood */
  //        ================
  //@{

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * 4-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
   * See qgar::Component::offset3X3_4_ for full details.
   */
  int* offset3X3_4_;

  /**
   * @brief Offsets to add to a pixel pointer to get the successive
   * pertinent 8-connected neighbors in a \f$3\times 3\f$ neighborhood.
   *
   * See qgar::Component::offset3X3_8_ for full details.
   */
  int* offset3X3_8_;

  //@}


// -------------------------------------------------------------------
// P R I V A T E    M E M B E R S
// -------------------------------------------------------------------
private:

  /** @name Constructors */
  //        ============
  //@{

  /**
   * @brief Disabled default constructor.
   *
   * The default constructor belongs to the private section
   * so that clients cannot use it.
   */
  ConnectedComponents();

  //@}


  /** @name Auxiliaries */
  //        ===========
  //@{

  /**
   * @brief Copy components stored in tree whose root is node
   * <b>in</b> and store them in corresponding nodes of tree whose
   * root is node <b>out</b> (in fact, the current component tree).
   *
   * The component table of the current tree is subsequently updated.
   *
   * @param aPNodeIn   pointer to the root of the tree including
   *                   component to be copied
   * @param aPNodeOut  pointer to the root of the tree where to store
   *                   copied components
   *
   * @warning
   * Both trees must have the same structure: the tree including node
   * <b>out</b> (the current tree) is supposed to be a copy of the tree
   * including node <b>in</b>.
   */
  void PRIVATEcopyCC(node_type* aPNodeIn, node_type* aPNodeOut);

  //@}

// -------------------------------------------------------------------
}; // class ConnectedComponents




// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// F U N C T I O N    M E M B E R S    I M P L E M E N T A T I O N
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


// =============================
// ACCESS TO THE COMPONENT IMAGE
// =============================


// GET THE COMPONENT IMAGE

inline const ConnectedComponents::image_type&
ConnectedComponents::accessComponentImage() const
{
  return componentImg_;
}


// GET A COPY OF THE COMPONENT IMAGE

inline ConnectedComponents::image_type
ConnectedComponents::componentImage() const
{
  return componentImg_;
}


// ============================
// ACCESS TO THE COMPONENT TREE
// ============================


// GET THE COMPONENT TREE

inline const ConnectedComponents::tree_type&
ConnectedComponents::accessComponentTree() const
{
  return componentTree_;
}

// GET A COPY OF THE COMPONENT TREE

inline ConnectedComponents::tree_type
ConnectedComponents::componentTree() const
{
  return componentTree_;
}


// GET A POINTER TO THE ROOT OF THE COMPONENT TREE

inline ConnectedComponents::node_type*
ConnectedComponents::pRoot() const
{
  return componentTree_.pRoot();
}


// GET A POINTER TO THE NODE OF THE COMPONENT TREE
// REPRESENTING THE COMPONENT OF GIVEN LABEL

inline ConnectedComponents::node_type*
ConnectedComponents::pNode(Component::label_type aLabel) const
{
  return componentTab_[aLabel];
}


// ====================
// ACCESS TO COMPONENTS
// ====================


// GET NUMBER OF COMPONENTS

inline int
ConnectedComponents::componentCnt() const
{
  return (int) componentTab_.size();
}

// GET THE COMPONENT TABLE

inline const std::vector<ConnectedComponents::node_type*>&
ConnectedComponents::accessComponentTab() const
{
  return componentTab_;
}

// GET A COPY OF THE COMPONENT TABLE

inline std::vector<ConnectedComponents::node_type*>
ConnectedComponents::componentTab() const
{
  return componentTab_;
}

// GET A POINTER TO THE COMPONENT OF GIVEN LABEL

inline Component*
ConnectedComponents::pComponent(Component::label_type aLabel) const
{
  return componentTab_[aLabel]->data();
}


// =========
// OPERATORS
// =========


// GET COMPONENT OF GIVEN LABEL

inline Component&
ConnectedComponents::operator[](Component::label_type aLabel)
{
  return *(componentTab_[aLabel]->data());
}


// GET COMPONENT OF GIVEN LABEL

inline const Component&
ConnectedComponents::operator[](Component::label_type aLabel) const
{
  return *(componentTab_[aLabel]->data());
}


// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
// IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII


} // namespace qgar


#endif /* __CONNECTEDCOMPONENTS_H_INCLUDED__ */
