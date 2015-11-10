TEMPLATE = subdirs
SUBDIRS = Libraries GEM++ Plugins Apps
GEM++.depends = Libraries
Apps.depends = GEM++
Apps.depends = Libraries
Plugins.depends = GEM++
HEADERS += ../doc/pages/GettingStarted.h \
           ../doc/pages/License.h \
           ../doc/pages/MainPage.h \
           ../doc/pages/ThirdPartyNotices.h
