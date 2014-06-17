TEMPLATE = subdirs
SUBDIRS = Libraries GEM++ Plugins Apps
GEM++.depends = Libraries
Apps.depends = GEM++
Apps.depends = Libraries
Plugins.depends = GEM++
HEADERS += ../doc/user/pages/Installation.h \
           ../doc/user/pages/License.h \
           ../doc/user/pages/MainPage.h \
           ../doc/user/pages/ThirdPartyNotices.h \
           ../doc/dev/pages/MainPage.h
