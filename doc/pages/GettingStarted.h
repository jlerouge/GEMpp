/** @page gettingstarted Getting started

    @section download Download
    You can download the latest compiled binaries :
        - Windows :
            - GEM++
            - optional plugins :
                - GEM++CPLEX
                - GEM++GLPK
                - GEM++Gurobi
        - Linux :
            - GEM++
            - optional plugins :
                - GEM++CPLEX
                - GEM++GLPK
                - GEM++Gurobi

    You must install at least one plugin (with one back-end solver) in order to solve graph matching problems.

    Alternatively, you can also download the latest source archive :
        - gem++_source_v2015_11_04.tar.gz

    @section installation Installation
    @subsection packages Pre-compiled binaries
    @subsubsection packages-windows On Windows
    @subsubsection packages-linux On Linux

    @subsection linux-source From source
    First, you need to install some dependencies. You will need *git* to download the sources :

        sudo apt-get install git

    In order to compile the program, you will also need the Qt SDK (http://qt-project.org/downloads).
    GEM++ minimal requirement for Qt is version 5.2. Depending on your computer architecture,
    you can use 32-bit or 64-bit version of Qt.

    Then, you can download the latest sources from ... :

        cd /path/to/download/directory
        git clone http://.../GEM++.git

    @date 2015-11-09
    @author J.Lerouge <julien.lerouge@litislab.fr>
*/
