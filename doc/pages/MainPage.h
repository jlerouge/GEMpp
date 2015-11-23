/** @mainpage Overview
    <table>
        <tr><td style="background-image: url('tab_b.png'); background-size: 1% 100%; border-right: none;"><img src="../../ressources/images/logo/logo2.png" alt="GEM++ logo"/></td>
        <td style="background-image: url('tab_b.png'); background-size: 1% 100%; border-left: none;">
            - **Name** : GEM++
            - **Version** : 1.0.0-beta (build: 2015-11-23)
            - **Description** : A Graph Extraction and Matching C++ software
            - **Developers** : Julien Lerouge, Maroua Hammami, Pierre Héroux, Sébastien Adam
            - **Contributors** : Pierre Le Bodic
            - **Contact** : gem-contact@litislab.eu
        </td></tr>
    </table>

    @section Features

    GEM++ is a software implementing several graph matching approaches, using [binary linear programming](https://en.wikipedia.org/wiki/Integer_programming).
    It is composed of five main executables and one common library :
        - **GEM++dist** is a command-line executable, that computes an edit distance between two graphs;
        - **GEM++sub** is a second command-line executable, that searches a subgraph isomorphism between a pattern graph and a target graph;
        - **GEM++multidist** and **GEM++multisub** provides the same functionalities as the two former commands, but for sets of graphs (they compute a distance matrix);
        - **GEM++gui** is a graphical user interface that lets the user load graphs, select subgraphs, set the parameters of the matching algorithm and see its results.
        - **libGEM++.so / GEM++.dll** is the shared library that provides methods to extract graphs from various data, to load and save graph and weights files,
          and to solve a graph matching problem.

    Here are the main functionnalities of GEM++ :
        - Supports undirected or directed, labeled or unlabeled graphs, stored in the following graph file formats :
            - [GML](https://en.wikipedia.org/wiki/Graph_Modelling_Language) (Graph Modeling Language)
            - [GXL](https://en.wikipedia.org/wiki/GXL) (Graph eXchange Language)
        - Supports the weighting of vertices and edges labels, with feature weights configuration files (see \ref weights);
        - Provides different matching algorithms, solved by binary linear programming :
            - Graph edit distance (GED), that can be used in its exact form or with following approximations :
                - Upper-bound, reducing the number of possible matchings by forbidding some substitutions,
                - Bipartite graph matching \cite riesen2009approximate;
            - Subgraph isomorphism, that comes with different levels of tolerance :
                - Exact subgraph isomorphism,
                - Substitution-tolerant subgraph isomorphism\cite le2012integer \cite le2009symbol,
                - Error-tolerant subgraph isomorphism\cite prl2015
        - Supports the following integer programming solvers :
            - IBM [CPLEX Optimizer](http://www-01.ibm.com/software/commerce/optimization/cplex-optimizer/ "CPLEX homepage")
            - [Gurobi Optimizer](http://www.gurobi.com/ "Gurobi homepage")
            - [GLPK](http://www.gnu.org/software/glpk/ "GLPK homepage")

    @section reference Reference
    If you used GEM++ software in any published work, you are highly encouraged (though not required) to cite the following paper:<br />
        - J. Lerouge, P. Le Bodic, P. Héroux and S. Adam, "GEM++: A Tool for Solving Substitution-Tolerant Subgraph Isomorphism" , Proceedings of GbRPR 2015 10th IAPR-TC-15 International Workshop. LNCS Vol. 9069. Springer, 2015. \cite gbr2015

    See also our @ref citelist.

    @section contact Contact

    Please report bugs and suggestions to gem-contact@litislab.eu

    @section thirdparty Third-party libraries
    GEM++ has been developed with the following softwares and tools :
        - [Qt Open-Source SDK](http://qt-project.org/ "Qt-project homepage"), a multi-plateform object-oriented C++ framework, developed by [The Qt Company Ltd](http://www.qt.io/ "Qt homepage") and released under the GNU LGPL (see @ref tpqt),
        - [QgarLib](http://www.qgar.org/ "Qgar project homepage"), a document analysis C++ library, developed by [LORIA](http://www.loria.fr/la-recherche-en/equipes/qgar "LORIA's Qgar homepage") and released under the GNU LGPL (see @ref tpqgarlib).

    See @ref thirdpartynotices for more detailed information.

    @section copyright Copyright
    GEM++ is the property of LITIS lab &copy; 2013-2015 LITIS.

    @section license License
    GEM++ is a free software, distributed under the terms of
    the CeCILL version 2.1 license.

    See @ref licensing for more detailed information.

    @date 2015-11-23
    @author J.Lerouge <julien.lerouge@litislab.fr>
*/
