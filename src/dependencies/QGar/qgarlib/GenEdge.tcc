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
 * @file GenEdge.tcc
 *
 * @brief Implementation of function members of class qgar::GenEdge.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  21:04
 * @since  Qgar 2.2
 */



namespace qgar
{


// -------------------------------------------------------------------
// C O N S T R U C T O R S
// -------------------------------------------------------------------


// DEFAULT CONSTRUCTOR

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::GenEdge(short int aFlag)

  : _flag(aFlag),
    _pSource (0),
    _pTarget (0)

{
  // VOID
}


// INITIALIZE WITH DATA

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::GenEdge(const TEDGE& aData, short int aFlag)

  : _data    (aData),
    _flag    (aFlag),
    _pSource (0),
    _pTarget (0)

{
  // VOID
}


// INITIALIZE WITH SOURCE AND TARGET

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::GenEdge(GenNode<TNODE,TEDGE>* const aPSource,
			      GenNode<TNODE,TEDGE>* const aPTarget,
			      short int aFlag)

  : _flag    (aFlag),
    _pSource (aPSource),
    _pTarget (aPTarget)

{
  // VOID
}


// INITIALIZE WITH SOURCE, TARGET, AND DATA

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::GenEdge(GenNode<TNODE,TEDGE>* const aPSource,
			      GenNode<TNODE,TEDGE>* const aPTarget,
			      const TEDGE& aData,
			      short int aFlag)

  : _data    (aData),
    _flag    (aFlag),
    _pSource (aPSource),
    _pTarget (aPTarget)

{
  // VOID
}


// COPY CONSTRUCTOR

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::GenEdge(const GenEdge<TNODE,TEDGE>& anEdge)

  : _data    (anEdge._data),
    _flag    (anEdge._flag),
    _pSource (anEdge._pSource),
    _pTarget (anEdge._pTarget)

{
  // VOID
}


// -------------------------------------------------------------------
// D E S T R U C T O R 
// -------------------------------------------------------------------


// NON-VIRTUAL DESTRUCTOR

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>::~GenEdge()
{
  // VOID
}


// -------------------------------------------------------------------
// E D G E   D A T A
// -------------------------------------------------------------------


// GET EDGE DATA

template <class TNODE, class TEDGE>
inline const TEDGE&
GenEdge<TNODE,TEDGE>::accessData() const
{
  return _data;
}


// GET A COPY OF EDGE DATA

template <class TNODE, class TEDGE>
inline TEDGE
GenEdge<TNODE,TEDGE>::data() const
{
  return _data;
}


// SET EDGE DATA

template <class TNODE, class TEDGE>
inline void
GenEdge<TNODE,TEDGE>::setData(const TEDGE& aData)
{
  _data = aData;
}


// GET EDGE FLAG

template <class TNODE, class TEDGE>
inline short int
GenEdge<TNODE,TEDGE>::flag() const
{
  return _flag;
}


// SET EDGE FLAG

template <class TNODE, class TEDGE>
inline void
GenEdge<TNODE,TEDGE>::setFlag(short int aFlag)
{
  _flag = aFlag;
}


// -------------------------------------------------------------------
// A D J A C E N T   N O D E S
// -------------------------------------------------------------------


// GET SOURCE NODE

template <class TNODE, class TEDGE>
inline const GenNode<TNODE,TEDGE>&
GenEdge<TNODE,TEDGE>::accessSource() const
{
  return *_pSource;
}


// GET A COPY OF THE SOURCE NODE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>
GenEdge<TNODE,TEDGE>::source() const
{
  return *_pSource;
}


// GET A POINTER TO THE SOURCE NODE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenEdge<TNODE,TEDGE>::pSource() const
{
  return _pSource;
}


// GET TARGET NODE

template <class TNODE, class TEDGE>
inline const GenNode<TNODE,TEDGE>&
GenEdge<TNODE,TEDGE>::accessTarget() const
{
  return *_pTarget;
}


// GET A COPY OF THE TARGET NODE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>
GenEdge<TNODE,TEDGE>::target() const
{
  return *_pTarget;
}


// RETURN A POINTER TO THE TARGET NODE

template <class TNODE, class TEDGE>
inline GenNode<TNODE,TEDGE>*
GenEdge<TNODE,TEDGE>::pTarget() const
{
  return _pTarget;
}


// SET POINTER TO SOURCE NODE

template <class TNODE, class TEDGE>
inline void
GenEdge<TNODE,TEDGE>::setPSource(GenNode<TNODE,TEDGE>* aPSource)
{
  _pSource = aPSource;
}


// SET POINTER TO TARGET NODE

template <class TNODE, class TEDGE>
inline void
GenEdge<TNODE,TEDGE>::setPTarget(GenNode<TNODE,TEDGE>* aPTarget)
{
  _pTarget = aPTarget;
}


// SET POINTER TO SOURCE NODE WHEN FREE,
// OTHERWISE SET POINTER TO TARGET NODE

template <class TNODE, class TEDGE>
inline void
GenEdge<TNODE,TEDGE>::setPNode(GenNode<TNODE,TEDGE>* aPNode)
{
  if (_pSource == 0)
    {
      _pSource = aPNode;
    }
  else
    {
      _pTarget = aPNode;
    }
}


// -------------------------------------------------------------------
// O P E R A T O R S
// -------------------------------------------------------------------


// ASSIGNMENT

template <class TNODE, class TEDGE>
GenEdge<TNODE,TEDGE>&
GenEdge<TNODE,TEDGE>::operator=(const GenEdge<TNODE,TEDGE>& anEdge)
{
  // Are left hand side and right hand side different objects?
  if (this != &anEdge)
    {
      _data    = anEdge._data;
      _flag    = anEdge._flag;
      _pSource = anEdge._pSource;
      _pTarget = anEdge._pTarget;
    }

  return *this;
}
 

// EQUALITY

template <class TNODE, class TEDGE>
bool
GenEdge<TNODE,TEDGE>::operator==(const GenEdge<TNODE,TEDGE>& anEdge)
{
  return _data == anEdge._data;
}


// INEQUALITY

template <class TNODE, class TEDGE>
bool
GenEdge<TNODE,TEDGE>::operator!=(const GenEdge<TNODE,TEDGE>& anEdge)
{
  return _data != anEdge._data;
}


// -------------------------------------------------------------------


} // namespace qgar
