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


#ifndef ___QGAR_PRIMITIVETYPES_H_INCLUDED__
#define ___QGAR_PRIMITIVETYPES_H_INCLUDED__


/**
 * @file    _QGAR_primitiveTypes.h
 * @brief   Specific types for primitives.
 *
 * @author  <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date    January 06, 2005  15:15
 * @since   Qgar 2.2
 */

// For RCS/CVS use: Do not delete
/* $Id: _QGAR_primitiveTypes.h,v 1.3 2005/07/13 16:29:03 masini Exp $ */



namespace qgar
{


/**
 * @name Types related to graphical primitives
 * @ingroup DS_PRIM_QGAR
 */
//@{


/**
 * @brief Colors.
 *
 * Default is black.
 * See Tgif <i>Color</i> menu for visual appearance.
 */

enum QGEcolor
{
QGE_COLOR_NONE,
QGE_COLOR_DEFAULT,
QGE_COLOR_BLACK,
QGE_COLOR_DARK_GRAY,
QGE_COLOR_GRAY,
QGE_COLOR_LIGHT_GRAY,
QGE_COLOR_WHITE,
QGE_COLOR_MAGENTA,
QGE_COLOR_PURPLE,
QGE_COLOR_CYAN,
QGE_COLOR_MEDIUM_BLUE,
QGE_COLOR_BLUE,
QGE_COLOR_OLIVE_GREEN,
QGE_COLOR_DARK_GREEN,
QGE_COLOR_GREEN,
QGE_COLOR_YELLOW,
QGE_COLOR_ORANGE,
QGE_COLOR_RED,
QGE_COLOR_PINK,
QGE_COLOR_SALMON_PINK,
QGE_COLOR_BROWN,
QGE_COLOR_CHOCOLATE_BROWN
}; 


/**
 * @brief Outline types.
 *
 * Default is solid.
 * See <i>Line Dash</i> in Tgif <i>Properties</i> menu
 * for real visual appearance.
 *
@verbatim
   QGE_OUTLINE_SOLID        : __________________
   QGE_OUTLINE_DASH_SSPACED : -  -  -  -  -  -  
   QGE_OUTLINE_DASH_SPACED  : - - - - - - - - - 
   QGE_OUTLINE_DASH_REGULAR : ------------------
   QGE_OUTLINE_DASH_LS      : __.__.__.__.__.__.
   QGE_OUTLINE_DASH_SS      : ------------------
   QGE_OUTLINE_DASH_LSS     : __..__..__..__..__
   QGE_OUTLINE_DASH_LSPACED : __  __  __  __  __
   QGE_OUTLINE_DOT          : ..................

@endverbatim
 */

enum QGEoutline
{
QGE_OUTLINE_NONE,
QGE_OUTLINE_DEFAULT,
QGE_OUTLINE_SOLID,
QGE_OUTLINE_DASH_SSPACED,
QGE_OUTLINE_DASH_SPACED,
QGE_OUTLINE_DASH_REGULAR,
QGE_OUTLINE_DASH_LS,
QGE_OUTLINE_DASH_SS,
QGE_OUTLINE_DASH_LSS,
QGE_OUTLINE_DASH_LSPACED,
QGE_OUTLINE_DOT
};


//@}


} // namespace qgar


#endif /* ___QGAR_PRIMITIVETYPES_H_INCLUDED__ */
