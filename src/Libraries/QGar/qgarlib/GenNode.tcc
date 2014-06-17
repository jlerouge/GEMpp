/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2005  Qgar Project, LORIA                             |
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
 * @file   GenNode.tcc
 * @brief  Implementation of function members of class qgar::GenNode.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  22:09
 * @since  Qgar 2.2
 */



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(short int aFlag)

  : _flag(aFlag)

{
  // VOID
}


// INITIALIZE WITH GIVEN DATA

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(const TNODE& aData, short int aFlag)

  : _data(aData),
    _flag(aFlag)

{
  // VOID
}


// INITIALIZE WITH 1 POINTER TO AN EDGE, AND DATA AND FLAG

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(GenEdge<TNODE,TEDGE>* const aPEdge,
			      const TNODE& aData,
			      short int aFlag)

  : _data(aData),
    _flag(aFlag)

{
  // --------------------------------------
  // WARNING: This pointer should not be 0!
  // --------------------------------------
  _edges.push_back(aPEdge);
}


// INITIALIZE WITH 2 POINTERS TO AN EDGE, AND DATA AND FLAG

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(GenEdge<TNODE,TEDGE>* const aPEdge1,
			      GenEdge<TNODE,TEDGE>* const aPEdge2,
			      const TNODE& aData,
			      short int aFlag)

  : _data(aData),
    _flag(aFlag)

{
  // ----------------------------------------
  // WARNING: These pointers should not be 0!
  // ----------------------------------------
  _edges.push_back(aPEdge1);
  _edges.push_back(aPEdge2);
}


// INITIALIZE WITH 3 POINTERS TO AN EDGE, AND DATA AND FLAG

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(GenEdge<TNODE,TEDGE>* const aPEdge1,
			      GenEdge<TNODE,TEDGE>* const aPEdge2,
			      GenEdge<TNODE,TEDGE>* const aPEdge3,
			      const TNODE& aData,
			      short int aFlag)

  : _data(aData),
    _flag(aFlag)

{
  // ----------------------------------------
  // WARNING: These pointers should not be 0!
  // ----------------------------------------
  _edges.push_back(aPEdge1);
  _edges.push_back(aPEdge2);
  _edges.push_back(aPEdge3);
}


// COPY CONSTRUCTOR

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::GenNode(const GenNode<TNODE,TEDGE>& aNode)

  : _data(aNode._data),
    _flag(aNode._flag),
    _edges(aNode._edges)

{
  // VOID
}

 
// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// NON-VIRTUAL DESTRUCTOR

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>::~GenNode()
{
  // VOID
  //
  // WARNING: Do not delete the elements of the edges list!
  // They are deleted by the destructor of the graph
  // in which the node is included.
}


// -------------------------------------------------------------------
// N O D E   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// GET NODE DEGREE

template<class TNODE, class TEDGE>
inline int
GenNode<TNODE,TEDGE>::degree() const
{
  return (int) _edges.size();
}


// -------------------------------------------------------------------
// N O D E   D A T A
// -------------------------------------------------------------------


// GET NODE DATA

template<class TNODE, class TEDGE>
inline const TNODE&
GenNode<TNODE,TEDGE>::accessData() const
{
  return _data;
}


// GET A COPY OF NODE DATA

template<class TNODE, class TEDGE>
inline TNODE
GenNode<TNODE,TEDGE>::data() const
{
  return _data;
}


// SET NODE DATA

template<class TNODE, class TEDGE>
inline void
GenNode<TNODE,TEDGE>::setData(const TNODE& aData)
{
  _data = aData;
}


// RETURN NODE FLAG

template<class TNODE, class TEDGE>
inline short int
GenNode<TNODE,TEDGE>::flag() const
{
  return _flag;
}


// SET NODE FLAG

template<class TNODE, class TEDGE>
inline void
GenNode<TNODE,TEDGE>::setFlag(short int aFlag)
{
  _flag = aFlag;
}


// -------------------------------------------------------------------
// A C C E S S   T O   E D G E S
// -------------------------------------------------------------------


// GET A CONSTANT REFERENCE TO THE EDGES LIST

template<class TNODE, class TEDGE>
inline const std::list< GenEdge<TNODE,TEDGE>* >&
GenNode<TNODE,TEDGE>::accessEdges() const
{
  return _edges;
}


// GET EDGES LIST

template<class TNODE, class TEDGE>
inline std::list< GenEdge<TNODE,TEDGE>* >&
GenNode<TNODE,TEDGE>::getEdges()
{
  return _edges;
}


// GET A COPY OF THE EDGES LIST

template<class TNODE, class TEDGE>
inline std::list< GenEdge<TNODE,TEDGE>* >
GenNode<TNODE,TEDGE>::edges() const
{
  return _edges;
}


// -------------------------------------------------------------------
// E D G E   I N S E R T I O N
// -------------------------------------------------------------------


// ADD (A POINTER TO) AN EDGE AT THE END OF THE EDGES LIST

template<class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenNode<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // --------------------------------------
  // WARNING: This pointer should not be 0!
  // --------------------------------------
  _edges.push_back(aPEdge);

  return aPEdge;
}


// ADD (A POINTER TO) AN EDGE
// AT THE BEGINNING OF THE EDGES LIST

template<class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>* 
GenNode<TNODE,TEDGE>::addEdgeFront(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // --------------------------------------
  // WARNING: This pointer should not be 0!
  // --------------------------------------
  _edges.push_front(aPEdge);

  return aPEdge;
}
 

// -------------------------------------------------------------------
// E D G E   R E M O V A L
// -------------------------------------------------------------------


// REMOVE THE EDGE AT GIVEN POSITION OF THE EDGES LIST

template<class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenNode<TNODE,TEDGE>::removeEdge(typename std::list< GenEdge<TNODE,TEDGE>* >::iterator aPos)
{
  GenEdge<TNODE,TEDGE>* pe = *aPos;
  _edges.erase(aPos);

  return pe;
}
 

// REMOVE FIRST EDGE THAT COMPARES EQUAL TO GIVEN EDGE
// IN THE EDGES LIST

template<class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenNode<TNODE,TEDGE>::removeEdge(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  GenEdge<TNODE,TEDGE>* pe = 0;

  for (typename std::list< GenEdge<TNODE,TEDGE>* >::iterator itE = _edges.begin();
       itE != _edges.end();
       ++itE)
    {
      if (*itE == aPEdge)
	{
	  return removeEdge(itE);
	}
    }

  return pe;
}


// -------------------------------------------------------------------
// OPERATORS
// -------------------------------------------------------------------


// ASSIGNMENT

template<class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>&
GenNode<TNODE,TEDGE>::operator=(const GenNode<TNODE,TEDGE>& aNode)
{
  // Are left hand side and right hand side different objects?
  if (this != &aNode)
    {
      _data  = aNode._data;
      _flag  = aNode._flag;
      _edges = aNode._edges;
    }

  return *this;
}

 
// EQUALITY

template<class TNODE, class TEDGE>
inline bool
GenNode<TNODE,TEDGE>::operator==(const GenNode<TNODE,TEDGE>& aNode)
{
  return _data == aNode._data;
}


// INEQUALITY

template<class TNODE, class TEDGE>
inline bool
GenNode<TNODE,TEDGE>::operator!=(const GenNode<TNODE,TEDGE>& aNode)
{
  return _data != aNode._data;
}


// -------------------------------------------------------------------


} // namespace qgar
