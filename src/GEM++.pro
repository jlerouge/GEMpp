TEMPLATE = subdirs
SUBDIRS = dependencies library plugins apps
library.depends = dependencies
apps.depends = library
apps.depends = dependencies
plugins.depends = library
HEADERS += ../doc/pages/GettingStarted.h \
           ../doc/pages/License.h \
           ../doc/pages/MainPage.h \
           ../doc/pages/ThirdPartyNotices.h
