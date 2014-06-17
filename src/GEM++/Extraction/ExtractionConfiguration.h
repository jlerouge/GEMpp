#ifndef __EXTRACTIONCONFIGURATION_H__
#define __EXTRACTIONCONFIGURATION_H__

#include "../Core/IPrintable.h"

class DLL_EXPORT ExtractionConfiguration : virtual public IPrintable {
    public:
        ExtractionConfiguration();
        ~ExtractionConfiguration();

        void reset();
        //bool check();
        void print(Printer *p);

        bool verbose;

        int pruningSize;
        int tolerance;
        int zernikeOrder;
};

#endif /* __EXTRACTIONCONFIGURATION_H__ */
