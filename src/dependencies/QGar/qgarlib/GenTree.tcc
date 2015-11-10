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
 * @file GenTree.tcc
 *
 * @brief Implementation of function members
 * of classes qgar::GenTreeNode and qgar::GenTree.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date  January 27, 2005  22:25
 * @since Qgar 2.2
 */



// QGAR
#include "QgarErrorUser.h"



using namespace std;



namespace qgar
{


/*---------------------------------------------------------------------*
 |                                                                     |
 |         C  L  A  S  S      G  E  N  T  R  E  E  N  O  D  E          |
 |                                                                     |
 *---------------------------------------------------------------------*/


// ============
// CONSTRUCTORS
// ============


// DEFAULT CONSTRUCTOR

template <class T>
GenTreeNode<T>::GenTreeNode()

  : _pParent(0),
    _pLSibling(0),
    _pRSibling(0),
    _pFirstChild(0),
    _data()

{
  // VOID
}


// CREATE A NODE WITH GIVEN DATA AND NO LINK

template <class T>
GenTreeNode<T>::GenTreeNode(const T& aData)

  : _pParent(0),
    _pLSibling(0),
    _pRSibling(0),
    _pFirstChild(0),
    _data(aData)

{
  // VOID
}


// CREATE A NODE WITH GIVEN DATA AND LINKS

template <class T>
GenTreeNode<T>::GenTreeNode(GenTreeNode<T>* aPParent,
			    GenTreeNode<T>* aPLSibling,
			    GenTreeNode<T>* aPRSibling,
			    GenTreeNode<T>* aPFirstChild,
			    const T& aData)

  : _pParent(aPParent),
    _pLSibling(aPLSibling),
    _pRSibling(aPRSibling),
    _pFirstChild(aPFirstChild),
    _data(aData)

{
  // VOID
}

// Copy-constructor
template <class T>
GenTreeNode<T>::GenTreeNode(const GenTreeNode<T>& aNode)
  : _pParent(aNode._pParent),
    _pLSibling(aNode._pLSibling),
    _pRSibling(aNode._pRSibling),
    _pFirstChild(aNode._pFirstChild),
    _data(aNode._data)
{
  // VOID
}


// ==========
// DESTRUCTOR
// ==========


template <class T>
GenTreeNode<T>::~GenTreeNode()
{
  // VOID
}


// ===============
// ACCESS TO LINKS
// ===============


// GET POINTER TO PARENT

template <class T>
inline GenTreeNode<T>* GenTreeNode<T>::pParent() const
{
  return _pParent;
}


// GET POINTER TO LEFT SIBLING

template <class T>
inline GenTreeNode<T>* GenTreeNode<T>::pLSibling() const
{
  return _pLSibling;
}


// GET POINTER TO RIGHT SIBLING

template <class T>
inline GenTreeNode<T>* GenTreeNode<T>::pRSibling() const
{
  return _pRSibling;
}


// GET POINTER TO FIRST CHILD

template <class T>
inline GenTreeNode<T>* GenTreeNode<T>::pFirstChild() const
{
  return _pFirstChild;
}


// ====================
// SIMPLE LINK SETTINGS
// ====================


// SET POINTER TO PARENT

template <class T>
inline void GenTreeNode<T>::setPParent(GenTreeNode<T>* aPNode)
{
  _pParent = aPNode;
}


// SET POINTER TO LEFT SIBLING

template <class T>
inline void GenTreeNode<T>::setPLSibling(GenTreeNode<T>* aPNode)
{
  _pLSibling = aPNode;
}


// SET POINTER TO RIGHT SIBLING

template <class T>
inline void GenTreeNode<T>::setPRSibling(GenTreeNode<T>* aPNode)
{
  _pRSibling = aPNode;
}


// SET POINTER TO FIRST CHILD

template <class T>
inline void GenTreeNode<T>::setPFirstChild(GenTreeNode<T>* aPNode)
{
  _pFirstChild = aPNode;
}


// ==============================
// ACCESS TO DATA STORED IN NODES
// ==============================


// GET DATA CONTAINED BY CURRENT NODE

template <class T>
inline const T& GenTreeNode<T>::accessData() const
{
  return _data;
}


// GET A COPY OF THE DATA CONTAINED BY CURRENT NODE

template <class T>
inline T GenTreeNode<T>::data() const 
{
  return _data;
}


// ===================
// STORE DATA IN NODES
// ===================


// SET NEW DATA TO CURRENT NODE

template <class T>
inline void GenTreeNode<T>::setData(const T& aData)
{
  _data = aData;
}


// =========
// OPERATORS
// =========


// ASSIGNMENT

template <class T>
GenTreeNode<T>& GenTreeNode<T>::operator=(const GenTreeNode<T>& aNode)
{
  // Are left hand side and right hand side different objects?
  if (this != &aNode)
    {
      _pParent     = aNode.pParent();
      _pLSibling   = aNode.pLSibling();
      _pRSibling   = aNode.pRSibling();
      _pFirstChild = aNode.pFirstChild();
      _data        = aNode.data();
    }

  return *this;
}


/*---------------------------------------------------------------------*
 |                                                                     |
 *---------------------------------------------------------------------*/





/*---------------------------------------------------------------------*
 |                                                                     |
 |               C  L  A  S  S      G  E  N  T  R  E  E                |
 |                                                                     |
 *---------------------------------------------------------------------*/


// ============
// CONSTRUCTORS
// ============


// DEFAULT CONSTRUCTOR: CREATE AN EMPTY TREE

template <class T>
GenTree<T>::GenTree()

  : _pRoot(0),
    _pCurrent(0)

{
  // VOID
}


// CREATE A TREE WITH A SINGLE NODE CONTAINING GIVEN DATA

template <class T>
GenTree<T>::GenTree(const T& aData)

  : _pRoot(new GenTreeNode<T>(aData))

{
  _pCurrent = _pRoot;
}


// COPY-CONSTRUCTOR
// Warning: perform a deep copy

template <class T>
GenTree<T>::GenTree(const GenTree<T>& aTree)

  : _pRoot(PRIVATEdeepCopy(aTree._pRoot))

{
  _pCurrent = _pRoot;
}


// CREATE A TREE FROM A GIVEN NODE.
// WARNING: Perform a deep copy

template <class T>
GenTree<T>::GenTree(GenTreeNode<T>* aPNode)
{
  if (aPNode == 0)
    {
      // Create an empty tree
      _pRoot    = 0;
      _pCurrent = 0;
    }
  else
    {
      // Create a temporary root
      // and link it to the descendants of the given node
      GenTreeNode<T>* proot =
	new GenTreeNode<T>(0,                      // No parent
			   0,                      // No left sibling
			   0,                      // No right sibling
			   aPNode->pFirstChild(),  // Same first child as given node
			   aPNode->data());

      // Copy the corresponding tree
      _pRoot    = PRIVATEdeepCopy(proot);
      _pCurrent = _pRoot;

      // Delete useless temporary node
      proot->setPFirstChild(0);
      delete proot;
    }
}


// ==========
// DESTRUCTOR
// ==========


template <class T>
GenTree<T>::~GenTree()
{
  PRIVATEdelete(_pRoot);
}


// ==========
// PREDICATES
// ==========


// IS TREE EMPTY?

template <class T>
bool GenTree<T>::empty() const
{
  return _pRoot == 0;
}


// ===============
// ACCESS TO LINKS
// ===============


// GET POINTER TO ROOT

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pRoot() const
{
  return _pRoot;
}


// GET POINTER TO CURRENT NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pCurrent() const
{
  return _pCurrent;
}


// GET POINTER TO PARENT OF CURRENT NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pParent() const
{
  return _pCurrent->pParent();
}


// GET POINTER TO PARENT OF GIVEN NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pParent(GenTreeNode<T>* aPNode) const
{
  return aPNode->pParent();
}


// GET POINTER TO LEFT SIBLING OF CURRENT NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pLSibling() const
{
  return _pCurrent->pLSibling();
}

  
// GET POINTER TO LEFT SIBLING OF GIVEN NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pLSibling(GenTreeNode<T>* aPNode) const
{
  return aPNode->pLSibling();
}

  
// GET POINTER TO RIGHT SIBLING OF CURRENT NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pRSibling() const
{
  return _pCurrent->pRSibling();
}

  
// GET POINTER TO RIGHT SIBLING OF GIVEN NODE

template <class T>
inline GenTreeNode<T>* 
GenTree<T>::pRSibling(GenTreeNode<T>* aPNode) const
{
  return aPNode->pRSibling();
}
  

// GET POINTER TO FIRST CHILD OF CURRENT NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pFirstChild() const
{
  return _pCurrent->pFirstChild();
}


// GET POINTER TO FIRST CHILD OF GIVEN NODE

template <class T>
inline GenTreeNode<T>*
GenTree<T>::pFirstChild(GenTreeNode<T>* aPNode) const
{
  return aPNode->pFirstChild();
}


// ==============
// ACCESS TO DATA
// ==============


// GET THE DATA STORED IN CURRENT NODE

template <class T>
inline const T&
GenTree<T>::accessData() const
{
  return _pCurrent->accessData();
}


// GET THE DATA STORED IN GIVEN NODE

template <class T>
inline const T&
GenTree<T>::accessData(GenTreeNode<T>* aPNode) const
{
  return aPNode->accessData();
}


// GET A COPY OF THE DATA STORED IN CURRENT NODE

template <class T>
inline T
GenTree<T>::data() const
{
  return _pCurrent->data();
}


// GET A COPY OF THE DATA STORED IN GIVEN NODE

template <class T>
inline T
GenTree<T>::data(GenTreeNode<T>* aPNode) const
{
  return aPNode->data();
}


// ==================
// MOVING IN THE TREE
// ==================


// THE ROOT BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoRoot() 
{
  _pCurrent = _pRoot;
}


// THE PARENT OF THE CURRENT NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoParent()
{
  _pCurrent = _pCurrent->pParent();
}


// THE PARENT OF THE GIVEN NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoParent(GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode->pParent();
}

// THE LEFT SIBLING OF THE CURRENT NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoLSibling()
{
  _pCurrent = _pCurrent->pLSibling();
}


// THE LEFT SIBLING OF THE GIVEN NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoLSibling(GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode->pLSibling();
}


// THE RIGHT SIBLING OF THE CURRENT NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoRSibling()
{
  _pCurrent = _pCurrent->pRSibling();
}


// THE RIGHT SIBLING OF THE GIVEN NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoRSibling(GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode->pRSibling();
}


// THE FIRST CHILD OF THE CURRENT NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoFirstChild()
{
  _pCurrent = _pCurrent->pFirstChild();
}


// THE FIRST CHILD OF THE GIVEN NODE BECOMES THE CURRENT NODE

template <class T>
inline void
GenTree<T>::gotoFirstChild(GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode->pFirstChild();
}


// ==========
// STORE DATA
// ==========


// SET DATA TO CURRENT NODE

template <class T>
inline void
GenTree<T>::setData(const T& aData)
{
  _pCurrent->setData(aData);
}


// SET DATA TO GIVEN NODE

template <class T>
inline void
GenTree<T>::setData(const T& aData, GenTreeNode<T>* aPNode)
{
  aPNode->setData(aData);
}


// ================
// INSERT NEW NODES
// ================


/*
INSERT A NODE CONTAINING GIVEN DATA AS PARENT OF CURRENT ROOT
----------------------------------------------------------------
                                      pn
                                      |                                             
                                      |                                             
            ROOT        ===>         ROOT
            /|\                      /|\
           / | \                    / | \
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::insertParent(const T& aData)
{
  if (empty())
    {
      // Empty tree
      _pRoot    = new GenTreeNode<T>(aData);
      _pCurrent = _pRoot;
    }
  else
    {
      // Tree is not empty
      // Link a new node to present root
      _pRoot->setPParent(new GenTreeNode<T>(0,      // parent
					    0,      // left sibling
					    0,      // right sibling
					    _pRoot, // first son
					    aData));
      // Update root
      _pRoot = _pRoot->pParent();
    }
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS LEFT SIBLING OF CURRENT NODE
----------------------------------------------------------------
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->NEW<-->CUR<-->rs<-
   /|\    /|\   /|\           /|\           /|\   /|\
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::insertLSibling(const T& aData)



{
  if (empty())
    {
      // Empty tree
      _pRoot    = new GenTreeNode<T>(aData);
      _pCurrent = _pRoot;
    }
  else if (_pCurrent->pParent() == 0)
    {
      // Inserting siblings to root is forbidden
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> void qgar::GenTree<T>::insertLSibling(const T&)",			  
			  "A root of a tree cannot be provided with left siblings");
    }
  else
    {
      // Insert a new node in the tree
      GenTreeNode<T>* pNew
	= new GenTreeNode<T>(_pCurrent->pParent(),    // parent
			     _pCurrent->pLSibling(),  // left sibling
			     _pCurrent,               // right sibling
			     0,                       // first son
			     aData);

      // Update left sibling
      if (_pCurrent->pLSibling() == 0)
	{
	  // No left sibling: New node becomes first son
	  ( _pCurrent->pParent() )->setPFirstChild(pNew);
	}
      else
	{
	  // New node becomes right sibling of left sibling
	  ( _pCurrent->pLSibling() )->setPRSibling(pNew);
	}

      // Update current node: New node becomes its left sibling
      _pCurrent->setPLSibling(pNew);
    }
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS LEFT SIBLING OF GIVEN NODE
----------------------------------------------------------------
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->NEW<-->GIV<-->rs<-
   /|\    /|\   /|\           /|\           /|\   /|\
----------------------------------------------------------------
*/
template <class T>
inline void
GenTree<T>::insertLSibling(const T& aData, GenTreeNode<T>* aPNode)



{
  _pCurrent = aPNode;
  insertLSibling(aData);
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS RIGHT SIBLING OF CURRENT NODE
----------------------------------------------------------------
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->CUR<-->NEW<-->rs<-
   /|\    /|\    /|\          /|\    /|\           /|\
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::insertRSibling(const T& aData)



{
  if (empty())
    {
      // Empty tree
      _pRoot    = new GenTreeNode<T>(aData);
      _pCurrent = _pRoot;
    }
  else if (_pCurrent->pParent() == 0)
    {
      // Inserting siblings to root is forbidden
      throw QgarErrorUser(__FILE__, __LINE__,
			  "template <class T> void qgar::GenTree<T>::insertRSibling(const T&)",			  
			  "A root of a tree cannot be provided with right siblings");
    }
  else
    {
     // Insert a new node in the tree
      GenTreeNode<T>* pNew
	= new GenTreeNode<T>(_pCurrent->pParent(),    // parent
			     _pCurrent,               // left sibling
			     _pCurrent->pRSibling(),  // right sibling
			     0,                       // first son
			     aData);

      // Update right sibling
      if (_pCurrent->pRSibling() != 0)
	{
	  // New node becomes left sibling of right sibling
	  ( _pCurrent->pRSibling() )->setPLSibling(pNew);
	}

      // Update current node: New node becomes its right sibling
      _pCurrent->setPRSibling(pNew);
    }
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS RIGHT SIBLING OF GIVEN NODE
----------------------------------------------------------------
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->GIV<-->NEW<-->rs<-
   /|\    /|\    /|\          /|\    /|\           /|\
----------------------------------------------------------------
*/
template <class T>
inline void
GenTree<T>::insertRSibling(const T& aData, GenTreeNode<T>* aPNode)



{
  _pCurrent = aPNode;
  insertRSibling(aData);
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS FIRST CHILD OF CURRENT NODE
----------------------------------------------------------------
     CUR                         CUR
      |\                         /|\
      | \                       / | \
      |  \         ===>        /  |  \
      |   \                   /   |   \
      |    \                 /    |    \
     fc<-->rs<-            NEW<-->fc<-->rs<-
    /|\   /|\                    /|\   /|\
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::insertFirstChild(const T& aData)
{
  if (empty())
    {
      // Empty tree
      _pRoot = new GenTreeNode<T>(aData);
      _pCurrent = _pRoot;
    }
  else
    {
      // Tree is not empty: Insert a new node in the tree
      GenTreeNode<T>* pNew
	= new GenTreeNode<T>(_pCurrent,                 // parent
			     0,                         // left sibling
			     _pCurrent->pFirstChild(),  // right sibling
			     0,                         // first son
			     aData);

      // Update first child, if any
      GenTreeNode<T>* pfc = _pCurrent->pFirstChild();
      if (pfc != 0)
	{
	  pfc->setPLSibling(pNew);
	}

      // Update current node
      _pCurrent->setPFirstChild(pNew);
    }
}


/*
SET A NEW NODE CONTAINING GIVEN DATA AS FIRST CHILD OF CURRENT NODE
----------------------------------------------------------------
     GIV                         GIV
      |\                         /|\
      | \                       / | \
      |  \         ===>        /  |  \
      |   \                   /   |   \
      |    \                 /    |    \
     fc<-->rs<-            NEW<-->fc<-->rs<-
    /|\   /|\                    /|\   /|\
----------------------------------------------------------------
*/
template <class T>
inline void
GenTree<T>::insertFirstChild(const T& aData, GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode;
  insertFirstChild(aData);
}


// =====
// MERGE
// =====


/*
MERGE GIVEN TREE AS LEFT SIBLING OF CURRENT NODE
----------------------------------------------------------------
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->GIV<-->CUR<-->rs<-
   /|\    /|\    /|\          /|\    /|\    /|\    /|\
                                    / | \
                                  c1  c2 c3
          GIV
          /|\
         / | \
       c1  c2 c3
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::mergeLSibling(const GenTree<T>& aTree)



{
  // Merging an empty tree has no effect
  if (aTree.empty())
    {
      return;
    }

  if (empty())
    {
      // Current tree is empty
      _pRoot    = PRIVATEdeepCopy(aTree.pRoot());
      _pCurrent = _pRoot;
    }
  else
    {
      // Current tree is not empty

      if (_pCurrent == _pRoot)
	{
	  // Inserting siblings to root is forbidden
	  throw QgarErrorUser(__FILE__, __LINE__,
			      "template <class T> void qgar::GenTree<T>::mergeLSibling(const qgar::GenTree<T>&)",
			      "A root of a tree cannot be provided with left siblings");
	}

      // Copy the given tree
      GenTreeNode<T>* pRootCopy = PRIVATEdeepCopy(aTree.pRoot());

      pRootCopy->setPParent(_pCurrent->pParent());
      pRootCopy->setPLSibling(_pCurrent->pLSibling());
      pRootCopy->setPRSibling(_pCurrent);

      // Update left sibling of current node
      if (_pCurrent->pLSibling() == 0)
	{
	  // Current node has no left sibling, i.e. is first child:
	  // The root of the copy becomes first child instead
	  (_pCurrent->pParent())->setPFirstChild(pRootCopy);
	}
      else
	{
	  // Current node has a left sibling:
	  // The root of the copy becomes its right sibling
	  (_pCurrent->pLSibling())->setPRSibling(pRootCopy);
	}

      // Update left sibling of current node
      _pCurrent->setPLSibling(pRootCopy);
    }
}


/*
MERGE GIVEN TREE AS LEFT SIBLING OF GIVEN NODE
----------------------------------------------------------------
           p                          p
          /|\                        /|\
         / | \                      / | \
        /  |  \        ===>        /  |  \
       /   |   \                  /   |   \
      /    |    \                /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->NEW<-->GIV<-->rs<-
   /|\    /|\    /|\          /|\    /|\    /|\    /|\
                                    / | \
                                  c1  c2 c3
          NEW
          /|\
         / | \
       c1  c2 c3
----------------------------------------------------------------
*/
template <class T>
void
 GenTree<T>::mergeLSibling(const GenTree<T>& aTree,
			   GenTreeNode<T>* aPNode)



{
  _pCurrent = aPNode;
  mergeLSibling(aTree);
}


/*
MERGE GIVEN TREE AS RIGHT SIBLING OF CURRENT NODE
----------------------------------------------------------------
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->CUR<-->rs<-        ->ls<-->CUR<-->GIV<-->rs<-
   /|\    /|\   /|\           /|\    /|\    /|\   /|\
                                           / | \
                                         c1  c2 c3
                 GIV
                 /|\
                / | \
              c1  c2 c3
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::mergeRSibling(const GenTree<T>& aTree)



{
  // Merging an empty tree has no effect
  if (aTree.empty())
    {
      return;
    }

  if (empty())
    {
      // Current tree is empty
      _pRoot = PRIVATEdeepCopy(aTree.pRoot());
      _pCurrent = _pRoot;
    }
  else
    {
      // Current tree is not empty

      if (_pCurrent == _pRoot)
	{
	  // Inserting siblings to root is forbidden
	  throw QgarErrorUser(__FILE__, __LINE__,
			      "template <class T> void qgar::GenTree<T>::mergeRSibling(const qgar::GenTree<T>&)",
			      "A root of a tree cannot be provided with right siblings");
	}

      // Copy the given tree
      GenTreeNode<T>* pRootCopy = PRIVATEdeepCopy(aTree.pRoot());

      pRootCopy->setPParent(_pCurrent->pParent());
      pRootCopy->setPLSibling(_pCurrent);
      pRootCopy->setPRSibling(_pCurrent->pRSibling());

     // Update right sibling of current node
      if (_pCurrent->pRSibling() != 0)
	{
	  // The root of the copy becomes its left sibling
	  (_pCurrent->pRSibling())->setPLSibling(pRootCopy);
	}

      // Update right sibling of current node
      _pCurrent->setPRSibling(pRootCopy);
    }
}


/*
MERGE GIVEN TREE AS RIGHT SIBLING OF GIVEN NODE
----------------------------------------------------------------
           p                                 p
          /|\                               /|\
         / | \                             / | \
        /  |  \        ===>               /  |  \
       /   |   \                         /   |   \
      /    |    \                       /    |    \
  ->ls<-->GIV<-->rs<-        ->ls<-->GIV<-->NEW<-->rs<-
   /|\    /|\   /|\           /|\    /|\    /|\   /|\
                                           / | \
                                         c1  c2 c3
                 NEW
                 /|\
                / | \
              c1  c2 c3
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::mergeRSibling(const GenTree<T>& aTree,
			  GenTreeNode<T>* aPNode)



{
  _pCurrent = aPNode;
  mergeRSibling(aTree);
}


/*
MERGE GIVEN TREE AS FIRST CHILD OF CURRENT NODE
----------------------------------------------------------------
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
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::mergeFirstChild(const GenTree<T>& aTree)
{
  // Merging an empty tree has no effect
  if (aTree.empty())
    {
      return;
    }

  // Copy the given tree
  GenTreeNode<T>* pRootCopy = PRIVATEdeepCopy(aTree.pRoot());

  if (empty())
    {
      // Current tree is empty
      _pRoot = pRootCopy;
      _pCurrent = _pRoot;
    }
  else
    {
      // Current tree is not empty

      // Update root of the copy, if non-empty
      if (pRootCopy != 0)
	{
	  pRootCopy->setPParent(_pCurrent);
	  pRootCopy->setPLSibling(0);
	  pRootCopy->setPRSibling(_pCurrent->pFirstChild());
	}

     // Update right sibling of first child
      if (_pCurrent->pFirstChild() != 0)
	{
	  // The root of the copy becomes its left sibling
	  (_pCurrent->pFirstChild())->setPLSibling(pRootCopy);
	}

      // Update current node
      _pCurrent->setPFirstChild(pRootCopy);
    }
}



/*
MERGE GIVEN TREE AS FIRST CHILD OF GIVEN NODE
----------------------------------------------------------------
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
----------------------------------------------------------------
*/
template <class T>
void
GenTree<T>::mergeFirstChild(const GenTree<T>& aTree,
			    GenTreeNode<T>* aPNode)
{
  _pCurrent = aPNode;
  mergeFirstChild(aTree);
}


// ============
// REMOVE NODES
// ============


/*
REMOVE CURRENT NODE AND RETURN IT
----------------------------------------------------------------
           p                          p
          /|\                        /|
         / | \                      / |
        /  |  \         ===>       /  |
       /   |   \                  /   |
      /    |    \                /    |
  ->ls<-->CUR<-->rs<-        ->ls<-->rs<-
   /|\    /|\   /|\           /|\   /|\
----------------------------------------------------------------
*/
template <class T>
GenTreeNode<T>*
GenTree<T>::remove()
{
  if (empty())
    {
      // Current tree is empty
      return _pRoot;
    }

  if (_pCurrent == _pRoot)
    {
      // Root is being removed

      // Update root and current node
      GenTreeNode<T>* p = _pCurrent;
      _pRoot = 0;
      _pCurrent = 0;

      return p;
    }

  // Current node links
  GenTreeNode<T>* pp  = _pCurrent->pParent();   // parent (P)
  GenTreeNode<T>* prs = _pCurrent->pRSibling(); // right sibling (RS)
  GenTreeNode<T>* pls = _pCurrent->pLSibling(); // left sibling (LS)

  // Update RS, if any
  if (prs != 0)
    {
      prs->setPLSibling(pls);
    }

  // Update LS
  if (pls == 0)
    {
      // No LS: RS becomes first child of P
      pp->setPFirstChild(prs);
    }
  else
    {
      // RS becomes right sibling of LS
      pls->setPRSibling(prs);
    }

  // Update current node
  GenTreeNode<T>* p = _pCurrent;
  _pCurrent = _pRoot;

  return p;
}


/*
REMOVE GIVEN NODE AND RETURN IT
----------------------------------------------------------------
           p                          p
          /|\                        /|
         / | \                      / |
        /  |  \         ===>       /  |
       /   |   \                  /   |
      /    |    \                /    |
  ->ls<-->GIV<-->rs<-        ->ls<-->rs<-
   /|\    /|\   /|\           /|\   /|\
----------------------------------------------------------------
*/
template <class T>
GenTreeNode<T>*
GenTree<T>::remove(GenTreeNode<T>* aPNode)
{
  if (aPNode ==  _pCurrent)
    {
      return remove();
    }
  else
    {
      GenTreeNode<T>* pSaveCurr = _pCurrent;
      _pCurrent = aPNode;
      remove();
      _pCurrent = pSaveCurr;
      return aPNode;
    }
}


// =========
// OPERATORS
// =========


// ASSIGNMENT
// WARNING: Perform a deep copy

template <class T>
GenTree<T>&
GenTree<T>::operator=(const GenTree<T>& aTree)
{
  // Are left hand side and right hand side different objects?
  if (this != &aTree)
    {
      _pRoot = PRIVATEdeepCopy(aTree._pRoot);
      _pCurrent = _pRoot;
    }

  return *this;
}


// ===========
// AUXILIARIES
// ===========


// PERFORM A DEEP COPY OF A PART OF THE TREE
// AND RETURN A POINTER TO THE ROOT OF THE COPY

template <class T>
GenTreeNode<T>*
GenTree<T>::PRIVATEdeepCopy(GenTreeNode<T>* aPNode,
			    GenTreeNode<T>* aPFCopy,
			    GenTreeNode<T>* aPLSCopy)
  const

{
  if (aPNode == 0)
    {
      // Return null pointer
      return aPNode;
    }
  else
    {
      // Copy  given node
      GenTreeNode<T>* copy = new GenTreeNode<T>(aPNode->data());

      // Link given node to its parent and FirstChild
      copy->setPParent(aPFCopy);
      copy->setPLSibling(aPLSCopy);      

      // Copy first child and link it to the copy
      copy->setPFirstChild(PRIVATEdeepCopy(aPNode->pFirstChild(), copy, 0));

      // Copy right sibling and link it to the copy
      copy->setPRSibling(PRIVATEdeepCopy(aPNode->pRSibling(),
					 aPFCopy,
					 copy));

      // Return pointer to the copy
      return copy;
    }
}


// DELETE THE SUBTREE OF GIVEN ROOT BY DEPTH-FIRST TRAVERSAL

template <class T>
void
GenTree<T>::PRIVATEdelete(GenTreeNode<T>* aPNode)
{
  if (aPNode != 0)
    {
      // Delete first child
      PRIVATEdelete(aPNode->pFirstChild());
      // Delete siblings
      PRIVATEdelete(aPNode->pRSibling());

      // Delete given node
      delete aPNode;
    }
}


/*---------------------------------------------------------------------*
 |                                                                     |
 *---------------------------------------------------------------------*/


} // namespace qgar
