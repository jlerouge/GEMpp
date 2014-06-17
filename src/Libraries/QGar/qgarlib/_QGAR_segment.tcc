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
 * @file   _QGAR_segment.tcc
 * @brief  Implementation of functions which compute segments.
 *
 * Computational geometry equations can be found in the FAQ section
 * of comp.graphics.algorithms and are based on
 * [<a href="Bibliography.html#Kirk-1992">Kirk,&nbsp;1992</a>],
 * pages 199-202, and
 * [<a href="Bibliography.html#ORourke-1994">O'Rourke,&nbsp;1994</a>],
 * pages 249-51.
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   February 03, 2005  19:18
 * @since  Qgar 2.2
 */



namespace qgar
{


// -------------------------------------------------------------------
// P R O J E C T I O N S
// -------------------------------------------------------------------


// SEGMENT PERPENDICULAR TO A GIVEN SEGMENT
// ========================================
// The source of the new segment is the given point, the target
// is the orthogonal projection of the given point onto the line
// supporting the given segment


template <class T>
inline GenSegment<double>
qgPerpendicular(const GenPoint<T>& aPt, const GenSegment<T>& aSeg)
{
  return GenSegment<double>(static_cast< GenPoint<double> >(aPt),
			    qgProject(aPt,aSeg));
}


// SEGMENT PERPENDICULAR TO A GIVEN Qgar SEGMENT
// =============================================


template <class T>
inline GenQgarSegment<double>
qgPerpendicular(const GenPoint<T>& aPt, const GenQgarSegment<T>& aQSeg)
{
  return GenQgarSegment<double>(static_cast< GenPoint<double> >(aPt),
				qgProject(aPt,aQSeg),
				aQSeg.color(),
				aQSeg.thickness(),
				aQSeg.outLine());
}


// -------------------------------------------------------------------


} // namespace qgar
