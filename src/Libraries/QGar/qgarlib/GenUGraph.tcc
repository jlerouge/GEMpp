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
 * @file GenUGraph.tcc
 *
 * @brief Implementation of function members of class qgar::GenUGraph.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  22:32
 * @since  Qgar 2.2
 */



// STD
#include <algorithm>
#include <list>
// QGAR
#include "GenEdge.h"
#include "GenNode.h"
#include "QgarErrorDeveloper.h"




namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
// WARNING - WARNING - WARNING - WARNING - WARNING - WARNING - WARNING

// THE COPY CONSTRUCTOR BELONGS TO THE PRIVATE SECTION
// SO THAT CLIENTS CANNOT USE IT

template <class TNODE, class TEDGE>
GenUGraph<TNODE,TEDGE>::GenUGraph(const GenUGraph<TNODE,TEDGE>& aGraph)
{
  throw QgarErrorDeveloper(__FILE__, __LINE__,
			   "qgar::GenUGraph<TNODE,TEDGE>::GenUGraph(const qgar::GenUGraph<TNODE,TEDGE>&)",
			   "Disabled constructor: should not be used!");
}

// WARNING - WARNING - WARNING - WARNING - WARNING - WARNING - WARNING
// WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW



// DEFAULT CONSTRUCTOR

template <class TNODE, class TEDGE>
GenUGraph<TNODE,TEDGE>::GenUGraph()
{
  // VOID
}


// INITIALIZE FROM (A POINTER TO) A NODE

template <class TNODE, class TEDGE>
GenUGraph<TNODE,TEDGE>::GenUGraph(GenNode<TNODE,TEDGE>* const aPNode)
{
  _nodes.push_back(aPNode);
}


// INITIALIZE FROM (A POINTER TO) AN EDGE

template <class TNODE, class TEDGE>
GenUGraph<TNODE,TEDGE>::GenUGraph(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  _edges.push_back(aPEdge);
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


template <class TNODE, class TEDGE>
GenUGraph<TNODE,TEDGE>::~GenUGraph()
{
  // Delete nodes
  for (typename std::list< GenNode<TNODE,TEDGE>* >::iterator itN = _nodes.begin();
       itN != _nodes.end();
       ++itN)
    {
      delete *itN;
    }

  // Delete edges
  for (typename std::list< GenEdge<TNODE,TEDGE>* >::iterator itE = _edges.begin();
       itE != _edges.end();
       ++itE)
    {
      delete *itE;
    }
}


// -------------------------------------------------------------------
// G R A P H   C H A R A C T E R I S T I C S
// -------------------------------------------------------------------


// IS THE GRAPH EMPTY?

template <class TNODE, class TEDGE>
bool
GenUGraph<TNODE,TEDGE>::empty() const
{
  return _nodes.empty() && _edges.empty();
}


// RETURN THE NUMBER OF NODES

template <class TNODE, class TEDGE>
int
GenUGraph<TNODE,TEDGE>::sizeNodes() const
{
  return (int) _nodes.size();
}


// RETURN THE NUMBER OF EDGES

template <class TNODE, class TEDGE>
int
GenUGraph<TNODE,TEDGE>::sizeEdges() const
{
  return (int) _edges.size();
}


// -------------------------------------------------------------------
// N O D E   A C C E S S
// -------------------------------------------------------------------


// GET A POINTER TO THE ENTRY NODE
// OR 0 IF THE NODES LIST IS EMPTY

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::pEntryNode() const
{
  if (_nodes.empty())
    {
      return 0;
    }
  else
    {
      return _nodes.front();
    }
}


// GET THE NODES LIST

template <class TNODE, class TEDGE>
inline std::list< GenNode<TNODE,TEDGE>* >&
GenUGraph<TNODE,TEDGE>::getNodes()
{
  return _nodes;
}


// GET (A CONSTANT REFERENCE TO) THE NODES LIST

template <class TNODE, class TEDGE>
inline const std::list< GenNode<TNODE,TEDGE>* >&
GenUGraph<TNODE,TEDGE>::accessNodes() const
{
  return _nodes;
}


// GET A COPY OF THE NODES LIST
template <class TNODE, class TEDGE>
inline std::list< GenNode<TNODE,TEDGE>* >
GenUGraph<TNODE,TEDGE>::nodes() const
{
  return _nodes;
}


// -------------------------------------------------------------------
// E D G E   A C C E S S
// -------------------------------------------------------------------


// GET A POINTER TO THE ENTRY EDGE
// OR 0 IF THE EDGES LIST IS EMPTY

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::pEntryEdge() const
{
  if (_edges.empty())
    {
      return 0;
    }
  else
    {
      return _edges.front();
    }
}


// GET THE EDGES LIST

template <class TNODE, class TEDGE>
inline std::list< GenEdge<TNODE,TEDGE>* >&
GenUGraph<TNODE,TEDGE>::getEdges()
{
  return _edges;
}


// GET (A CONSTANT REFERENCE TO) THE EDGES LIST

template <class TNODE, class TEDGE>
inline const std::list< GenEdge<TNODE,TEDGE>* >&
GenUGraph<TNODE,TEDGE>::accessEdges() const
{
  return _edges;
}


// GET A COPY OF THE EDGES LIST
template <class TNODE, class TEDGE>
inline std::list< GenEdge<TNODE,TEDGE>* >
GenUGraph<TNODE,TEDGE>::edges() const
{
  return _edges;
}


// -------------------------------------------------------------------
// I N S E R T I O N   O F   C R E A T E D   N O D E S
// -------------------------------------------------------------------


// JUST INSERT A NEW NODE CREATED FROM GIVEN DATA AND FLAG

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(const TNODE& aData, short int aFlag)
{
  return addNode(new GenNode<TNODE,TEDGE>(aData, aFlag));
}


// INSERT A NEW NODE AND LINK IT TO GIVEN EDGE OF THE GRAPH

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(GenEdge<TNODE,TEDGE>* const aPEdge,
				const TNODE& aData,
				short int aFlag)
{
  return addNode(new GenNode<TNODE,TEDGE>(aData, aFlag), aPEdge);
}


// INSERT A NEW NODE BETWEEN GIVEN EDGES OF THE GRAPH

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(GenEdge<TNODE,TEDGE>* const aPEdge1,
				GenEdge<TNODE,TEDGE>* const aPEdge2,
				const TNODE& aData,
				short int aFlag)
{
  return addNode(new GenNode<TNODE,TEDGE>(aData, aFlag), aPEdge1, aPEdge2);
}


// INSERT A NEW NODE AS SOURCE OF THE GIVEN EDGE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNodeAtSource(GenEdge<TNODE,TEDGE>* const aPEdge,
					const TNODE& aData,
					short int aFlag)
{
  return addNodeAtSource(new GenNode<TNODE,TEDGE>(aData, aFlag), aPEdge);
}


// INSERT A NEW NODE AS TARGET OF THE GIVEN EDGE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNodeAtTarget(GenEdge<TNODE,TEDGE>* const aPEdge,
					const TNODE& aData,
					short int aFlag)
{
  return addNodeAtTarget(new GenNode<TNODE,TEDGE>(aData, aFlag), aPEdge);
}


// -------------------------------------------------------------------
// I N S E R T I O N   O F   E X I S T I N G   N O D E S
// -------------------------------------------------------------------


// JUST INSERT A NODE IN THE NODES LIST OF THE GRAPH

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(GenNode<TNODE,TEDGE>* const aPNode)
{
  // The node is inserted at the end of the nodes list of the graph
  _nodes.push_back(aPNode);

  return aPNode;
}

// INSERT A NODE AS SOURCE OR TARGET OF A GIVEN EDGE

template <class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(GenNode<TNODE,TEDGE>* const aPNode,
				GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // The edge is inserted in the edges list of the node
  aPNode->addEdge(aPEdge);

  // The node becomes the source or target of the edge,
  // depending on which one is free
  aPEdge->setPNode(aPNode);

  // The node is inserted in the nodes list of the graph
  return addNode(aPNode);
}


// INSERT A NODE BETWEEN TWO GIVEN EDGES OF THE GRAPH

template <class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNode(GenNode<TNODE,TEDGE>* const aPNode,
				GenEdge<TNODE,TEDGE>* const aPEdge1,
				GenEdge<TNODE,TEDGE>* const aPEdge2)
{
  // The given edges are included in the edges list of the given node
  aPNode->addEdge(aPEdge1);
  aPNode->addEdge(aPEdge2);

  // The node becomes the source of a given edge if the source is free
  // Otherwise, the node becomes the target
  aPEdge1->setPNode(aPNode);
  aPEdge2->setPNode(aPNode);

  // The node is inserted in the nodes list of the graph
  return addNode(aPNode);
}


// INSERT GIVEN NODE AS SOURCE OF GIVEN EDGE OF THE GRAPH
 
template <class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNodeAtSource(GenNode<TNODE,TEDGE>* const aPNode,
					GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // The given edge is supposed to belong to the current graph.
  // It is included in the edges list of the given node.
  aPNode->addEdge(aPEdge);

  // The node becomes the source of the given edge
  aPEdge->setPSource(aPNode);

  // The node is inserted in the nodes list of the graph
  return addNode(aPNode);
}


// INSERT GIVEN NODE AS TARGET OF GIVEN EDGE OF THE GRAPH
 
template <class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addNodeAtTarget(GenNode<TNODE,TEDGE>* const aPNode,
					GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // The given edge is supposed to belong to the current graph.
  // It is included in the edges list of the given node.
  aPNode->addEdge(aPEdge);

  // The node becomes the target of the given edge
  aPEdge->setPTarget(aPNode);

  // The node is inserted in the nodes list of the graph
  return addNode(aPNode);
}


// -------------------------------------------------------------------
// I N S E R T I O N   O F   C R E A T E D   E D G E S
// -------------------------------------------------------------------


// INSERT A NEW EDGE CREATED FROM GIVEN DATA AND FLAG

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(const TEDGE& aData,
				short int aFlag)
{
  return addEdge(new GenEdge<TNODE,TEDGE>(aData, aFlag));
}


// LINK THE SOURCE OF A NEW EDGE TO A GIVEN NODE OF THE GRAPH

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(GenNode<TNODE,TEDGE>* const aPNode,
				const TEDGE& aData,	  
				short int aFlag)
{
  return addEdge(new GenEdge<TNODE,TEDGE>(aData, aFlag), aPNode);
}


// INSERT AN NEW EDGE BETWEEN TWO GIVEN NODES OF THE GRAPH

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(GenNode<TNODE,TEDGE>* const aPSource,
				GenNode<TNODE,TEDGE>* const aPTarget,
				const TEDGE& aData,
				short int aFlag)
{
  return addEdge(new GenEdge<TNODE,TEDGE>(aData, aFlag), aPSource, aPTarget);
}


// -------------------------------------------------------------------
// I N S E R T I O N   O F   E X I S T I N G   E D G E S
// -------------------------------------------------------------------


// JUST INSERT (A POINTER TO) AN EDGE IN THE GRAPH

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  // The edge is inserted at the end of the edges list of the graph
  _edges.push_back(aPEdge);

  return aPEdge;
}


// INSERT GIVEN (POINTER TO) EDGE IN THE GRAPH,
// SO AS GIVEN (POINTED) NODE BECOMES ITS SOURCE OR ITS TARGET

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const aPEdge,
				GenNode<TNODE,TEDGE>* const aPNode)
{
  // Insert given edge in the edges list of the given node
  aPNode->addEdge(aPEdge);

  // The node becomes the source of the given edge if the source is free
  // Otherwise, the node becomes the target
  aPEdge->setPNode(aPNode);

  // Insert edge in the edges list of the graph
  return addEdge(aPEdge);
}


// INSERT GIVEN (POINTER TO) EDGE IN THE GRAPH,
// SO AS GIVEN (POINTED) NODEs BECOMES ITS SOURCE AND ITS TARGET

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdge(GenEdge<TNODE,TEDGE>* const aPEdge,
				GenNode<TNODE,TEDGE>* const aPNode1,
				GenNode<TNODE,TEDGE>* const aPNode2)
{
  // Insert given edge in the edges list of the given nodes
  aPNode1->addEdge(aPEdge);
  aPNode2->addEdge(aPEdge);

  // The first node becomes the source of the given edge
  // The second node becomes the target of the given edge
  aPEdge->setPSource(aPNode1);
  aPEdge->setPTarget(aPNode2);

  // Insert edge in the edges list of the graph
  return addEdge(aPEdge);
}


// INSERT GIVEN (POINTER TO) EDGE IN THE GRAPH,
// SO AS GIVEN (POINTED) NODE BECOMES ITS SOURCE

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdgeBySource(GenEdge<TNODE,TEDGE>* const aPEdge,
					GenNode<TNODE,TEDGE>* const aPNode)
{
  // Insert edge in the edges list of the given node
  aPNode->addEdge(aPEdge);

  // Insert node as source of the given edge
  aPEdge->setPSource(aPNode);

  // Insert edge in the edges list of the graph
  return addEdge(aPEdge);
}


// INSERT GIVEN (POINTER TO) EDGE IN THE GRAPH,
// SO AS GIVEN (POINTED)  NODE BECOMES ITS TARGET

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::addEdgeByTarget(GenEdge<TNODE,TEDGE>* const aPEdge,
					GenNode<TNODE,TEDGE>* const aPNode)
{
  // Insert edge in the edges list of the given node
  aPNode->addEdge(aPEdge);

  // Insert node as target of the given edge
  aPEdge->setPTarget(aPNode);

  // Insert edge in the edges list of the graph
  return addEdge(aPEdge);
}


// -------------------------------------------------------------------
// N O D E   R E M O V A L
// -------------------------------------------------------------------


// REMOVE GIVEN (POINTER TO) NODE FROM THE GRAPH,
// AND RETURN IT

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::remove(GenNode<TNODE,TEDGE>* const aPNode)
{
  return remove(std::find(_nodes.begin(), _nodes.end(), aPNode));
}


// REMOVE (POINTER TO) NODE AT GIVEN POSITION IN THE NODES LIST,
// AND RETURN IT.

template <class TNODE, class TEDGE>
GenNode<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::remove(typename std::list< GenNode<TNODE,TEDGE>* >::iterator aPos)
{
  if (aPos == _nodes.end())
    {
      return 0;
    }
  else
    {
      // Save pointer to the node
      GenNode<TNODE,TEDGE>* pn = *aPos;

      // WARNING: Get a copy of the list of adjacent edges
      //          as edge removals alter this list
      std::list< GenEdge<TNODE,TEDGE>* >  el = (*pn).edges();

      // For each edge adjacent to the node

      for (typename std::list<GenEdge<TNODE,TEDGE>*>::const_iterator itE = el.begin();
	   itE != el.end();
	   ++itE)
	{
	  // Remove current edge from the graph,
	  // and delete it
	  delete(remove(*itE));
	}

      // Remove pointer to node from the nodes list of the graph
      _nodes.erase(aPos);
      
      return pn;
    }
}


// -------------------------------------------------------------------
// E D G E   R E M O V A L
// -------------------------------------------------------------------


// REMOVE GIVEN (POINTER TO) EDGE FROM THE GRAPH,
// AND RETURN IT

template <class TNODE, class TEDGE>
inline GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::remove(GenEdge<TNODE,TEDGE>* const aPEdge)
{
  return remove(std::find(_edges.begin(), _edges.end(), aPEdge));
}


// REMOVE (POINTER TO) EDGE AT GIVEN POSITION IN THE EDGES LIST,
// AND RETURN IT

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>*
GenUGraph<TNODE,TEDGE>::remove(typename std::list<GenEdge<TNODE,TEDGE>*>::iterator aPos)
{
  if (aPos == _edges.end())
    {
      return 0;
    }
  else
    {
      // Save pointer to the edge
      GenEdge<TNODE,TEDGE>* pe = *aPos;
      
      // Remove pointer from the edges list of the graph
      _edges.erase(aPos);
      
      // Remove pointer from edges lists of source and target nodes
      (pe->pSource())->removeEdge(pe);
      return (pe->pTarget())->removeEdge(pe);
    }
}


// -------------------------------------------------------------------


} // namespace qgar
