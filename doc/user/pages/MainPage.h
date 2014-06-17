/** @mainpage Overview
    <table>
        <tr><td style="background-image: url('tab_b.png'); background-size: 1% 100%; border-right: none;"><img src="../../../ressources/images/logo/GEM++logo2.png" alt="GEM++ logo"/></td>
        <td style="background-image: url('tab_b.png'); background-size: 1% 100%; border-left: none;">
            - **Name** : GEM++
            - **Version** : 1.0.0-beta (build: 2014-03-27)
            - **Description** : A Graph Extraction and Matching C++ software
            - **Developers** : Julien Lerouge, Pierre Héroux, Sébastien Adam
            - **Contact** : qui.donc@univ-rouen.fr
        </td></tr>
    </table>

    @section Features

    GEM++ is a software implementing several graph matching approaches, using [Integer Programming](http://en.wikipedia.org/wiki/Integer_programming "Wikipedia article on Integer Programming").
    It is composed of three main executables and one common library :
        - **GEM++dist** is a command-line executable, that computes an edit distance between two graphs;
        - **GEM++sub** is a  second command-line executable, that searches a subgraph isomorphism between a pattern graph and a target graph;
        - **GEM++gui** is a graphical user interface that lets the user load graphs, select subgraphs, choose and parameter a matching algorithm and see its result.
        - **libGEM++.so / GEM++.dll** is the shared library that provides methods to load and save graph matching related files, and to solve a graph matching problem.

    Here are the main functionnalities of GEM++ :
        - Supports undirected or directed, labeled or unlabeled graphs, stored in the following graph file formats :
            - GML (Graph Modeling Language)
            - GXL (Graph eXchange Language)
        - Supports the weighting of vertices and edges labels, with feature weights configuration files (see \ref weights);
        - Provides different matching algorithms, solved by [Integer Programming](http://en.wikipedia.org/wiki/Integer_programming "Wikipedia article on Integer Programming"),
          especially Binary Linear Programming (BLP) :
            - Graph edit distance (GED), that can be used in its exact form or with following approximations :
                - Lower-bound, aggregating the linear program constraints,
                - Row-generation approach, beginning with the lower bound and iteratively adding violated constraints,
                - Upper-bound, reducing the number of possible matchings by forbidding some substitutions,
                - Column-generation approach, beginning with the upper-bound and iteratively re-allowing some substitutions,
                - Bipartite graph matching \cite riesen2009approximate;
            - Quadratic GED, that is a Binary Quadratic Programming implementation of the GED;
            - Subgraph isomorphism, that comes with different levels of tolerance :
                - Exact subgraph isomorphism,
                - Substitution-tolerant subgraph isomorphism\cite le2012integer \cite le2009symbol,
                - Error-tolerant subgraph isomorphism\cite prl2014
        - Supports the following integer programming solvers :
            - IBM [CPLEX Optimizer](http://www-01.ibm.com/software/commerce/optimization/cplex-optimizer/ "CPLEX homepage")
            - [Gurobi Optimizer](http://www.gurobi.com/ "Gurobi homepage")
            - [GLPK](http://www.gnu.org/software/glpk/ "GLPK homepage") (*in progress*)

    @section reference Reference
    GEM++ is a software developed by Julien Lerouge, Pierre Héroux and Sébastien Adam.<br />
    Please cite the following paper in any published work which uses this sofware.<br />
        - Julien Lerouge, Pierre Héroux, and Sébastien Adam. GEM++ : a tool for solving substitution-tolerant subgraph isomorphism. In Proceedings of the IAPR Joint International Workshops on Structural and Syntactic Pattern Recognition (SSPR 2014), 2014. \cite sspr2014

    See also our @ref citelist, upon which parts of this software are based. \cite acompleter

    @section contact Contact

    Please report bugs and suggestions to qui.donc@univ-rouen.fr

    @section thirdparty Third-party libraries
    GEM++ has been developed with the following softwares and tools :
        - [Qt Open-Source SDK](http://qt-project.org/ "Qt-project homepage"), a multi-plateform object-oriented C++ framework, developed by [Digia](http://qt.digia.com/ "Digia's Qt homepage") and released under the GNU LGPL (see @ref tpqt),
        - [QgarLib](http://www.qgar.org/ "Qgar project homepage"), a document analysis C++ library, developed by [LORIA](http://www.loria.fr/la-recherche-en/equipes/qgar "LORIA's Qgar homepage") and released under the GNU LGPL (see @ref tpqgarlib),

    See @ref thirdpartynotices for more detailed information.

    @section license License
    GEM++ is copyright (C) 2013-2014 LITIS (www.litislab.fr)

    GEM++ is released under the <WHATEVER> license.

    See @ref licensing for more detailed information.

    @date 2014-03-27
    @author J.Lerouge <julien.lerouge@litislab.fr>
*/
