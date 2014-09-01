#ifndef __SINGLEEXTRACTOR_H__
#define __SINGLEEXTRACTOR_H__

#include "GenericExtractor.h"

class DLL_EXPORT SingleExtractor : virtual public GenericExtractor {
    public:
        SingleExtractor();
        SingleExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);
        ~SingleExtractor();

        QString getInput();
        QString getOutput();
        QString getMetadata();
};

#endif /*__SINGLEEXTRACTOR_H__*/
