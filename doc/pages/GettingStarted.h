/** @page gettingstarted Getting started

    @section download Download
    You may download the latest (v1.0.0) compiled binaries from this page :
        - Windows :
            - GEM++ [(32 bits)](https://github.com/jlerouge/GEMpp/releases/download/1.0.0/gempp_win32.exe) [(64 bits)](https://github.com/jlerouge/GEMpp/releases/download/1.0.0/gempp_win64.exe)
            - optional plugins :
                - CPLEX
                - GLPK [(32 bits)](https://github.com/jlerouge/GEMppGLPK/releases/download/1.0.0/gemppglpk_win32.exe) [(64 bits)](https://github.com/jlerouge/GEMppGLPK/releases/download/1.0.0/gemppglpk_win64.exe)
                - GuRoBi
        - Linux :
            - GEM++ [(.deb)](https://github.com/jlerouge/GEMpp/releases/download/1.0.0/gempp_amd64.deb) [(.tar.gz)](https://github.com/jlerouge/GEMpp/releases/download/1.0.0/gempp_amd64.tar.gz)
            - optional plugins :
                - CPLEX
                - GLPK
                - GuRoBi

    You must install at least one plugin (with one back-end solver) in order to solve graph matching problems.

    Alternatively, you can also download the latest source archives:
        - GEM++ (also contains CPLEX and GuRoBi plugins sources): [(.zip)](https://github.com/jlerouge/GEMpp/archive/1.0.0.zip) [(.tar.gz)](https://github.com/jlerouge/GEMpp/archive/1.0.0.tar.gz)
        - optional GLPK plugin, distributed under the terms of the GNU GPL v3: [(.zip)](https://github.com/jlerouge/GEMppGLPK/archive/1.0.0.zip) [(.tar.gz)](https://github.com/jlerouge/GEMppGLPK/archive/1.0.0.tar.gz)

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

    @date 2015-11-23
    @author J.Lerouge <julien.lerouge@litislab.fr>
*/
