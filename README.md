# GEM++ : a Graph Extraction and Matching C++ software


<table>
<tr>
<td><div>
<img src="https://raw.githubusercontent.com/jlerouge/GEMpp/master/ressources/images/logo/logo2.png"  alt="GEM++ logo"/>
</div>
 </td><td><ul>
<li><b>Name</b> : GEM++</li>
<li><b>Description</b> : A Graph Extraction and Matching C++ software</li>
<li><b>Developers</b> : Julien Lerouge, Maroua Hammami, Pierre Héroux, Sébastien Adam</li>
<li><b>Contributors</b> : Pierre Le Bodic</li>
<li><b>Contact</b> : <a href="mailto:gem-contact@litislab.eu">gem-contact@litislab.eu</a></li>
</ul>
</td></tr>
</table>

## Detailed features
GEM++ is a software implementing several graph matching approaches, using [binary linear programming](https://en.wikipedia.org/wiki/Integer_programming). It is composed of five main executables and one common library :
  - **GEM++dist** is a command-line executable, that computes an edit distance between two graphs;
  - **GEM++sub** is a second command-line executable, that searches a subgraph isomorphism between a pattern graph and a target graph;
  - **GEM++multidist** and **GEM++multisub** provides the same functionalities as the two former commands, but for sets of graphs (they compute a distance matrix);
  - **GEM++gui** is a graphical user interface that lets the user load graphs, select subgraphs, set the parameters of the matching algorithm and see its results.
  - **libGEM++.so** / **GEM++.dll** is the shared library that provides methods to extract graphs from various data, to load and save graph and weights files, and to solve a graph matching problem.

Here are the main functionnalities of GEM++ :
  - Supports undirected or directed, labeled or unlabeled graphs, stored in the following graph file formats :
    - [GML](https://en.wikipedia.org/wiki/Graph_Modelling_Language) (Graph Modeling Language)
    - [GXL](https://en.wikipedia.org/wiki/GXL) (Graph eXchange Language)
  - Supports the weighting of vertices and edges labels, with feature weights configuration files (see weights);
  - Provides different matching algorithms, solved by Integer Programming, especially Binary Linear Programming (BLP) :
    - Graph edit distance (GED), that can be used in its exact form or with following approximations :
      - Upper-bound, reducing the number of possible matchings by forbidding some substitutions,
      - Bipartite graph matching [[1]](#riesen2009approximate);
    - Subgraph isomorphism, that comes with different levels of tolerance :
      - Exact subgraph isomorphism,
      - Substitution-tolerant subgraph isomorphism  [[2]](#lebodic2009symbol)  [[3]](#lebodic2012integer),
      - Error-tolerant subgraph isomorphism [[4]](#lerouge2015minimum)
  - Supports the following integer programming solvers :
    - [IBM CPLEX Optimizer](http://www-01.ibm.com/software/commerce/optimization/cplex-optimizer/ "CPLEX homepage")
    - [Gurobi Optimizer](http://www.gurobi.com/ "Gurobi homepage")
    - [GLPK](http://www.gnu.org/software/glpk/ "GLPK homepage")


## References
If you used GEM++ software in any published work, you are highly encouraged (though not required) to cite the following paper:
  - J. Lerouge, P. Le Bodic, P. Héroux and S. Adam, "GEM++: A Tool for Solving Substitution-Tolerant Subgraph Isomorphism" , Proceedings of GbRPR 2015 10th IAPR-TC-15 International Workshop. LNCS Vol. 9069. Springer, 2015.

Here are some of our references :
  - <a name="riesen2009approximate">[1]</a> Kaspar Riesen and Horst Bunke. Approximate graph edit distance computation by means of bipartite graph matching. Image and Vision Computing, 27(7):950–959, 2009.
  - <a name="lebodic2009symbol">[2]</a> Pierre Le Bodic, Hervé Locteau, Sébastien Adam, Pierre Héroux, Yves Lecourtier, and Arnaud Knippel. Symbol detection using region adjacency graphs and integer linear programming. In Proceedings of the International Conference on Document Analysis and Recognition (ICDAR'09), pages 1320–1324. IEEE, 2009.
  - <a name="lebodic2012integer">[3]</a> Pierre Le Bodic, Pierre Héroux, Sébastien Adam, and Yves Lecourtier. An integer linear program for substitution-tolerant subgraph isomorphism and its use for symbol spotting in technical drawings. Pattern Recognition, 45(12):4214–4224, 2012.
  - <a name="lerouge2015minimum">[4]</a> Julien Lerouge, Maroua Hammami, Sébastien Adam, and Pierre Héroux. Minimum cost subgraph matching using a binary linear program. Pattern Recognition Letters, 2015. Preprint submitted to Elsevier.




## Third party libraries
GEM++ has been developed with the following softwares and tools :
  - [Qt Open-Source SDK](http://qt-project.org/ "Qt-project homepage"), a multi-plateform object-oriented C++ framework, developed by [The Qt Company Ltd](http://www.qt.io/ "Qt homepage") and released under the GNU LGPL,
  - [QgarLib](http://www.qgar.org/ "Qgar project homepage"), a document analysis C++ library, developed by [LORIA](http://www.loria.fr/la-recherche-en/equipes/qgar "LORIA's Qgar homepage") and released under the GNU LGPL.

## Copyright
GEM++ is the property of LITIS lab (c) 2013-2015 LITIS.

## License
GEM++ is a free software, distributed under the terms of the CeCILL version 2.1 license (see LICENSE.en file).

