#ifndef __EXTRACTOR_H__
#define __EXTRACTOR_H__

#include "ExtractionConfiguration.h"

class DLL_EXPORT Extractor {
    public:
        Extractor();
        Extractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);
        ~Extractor();

        void setInputFile(const QString &filename);
        QString getInputFile();
        void setOutputFile(const QString &filename);
        QString getOutputFile();
        void setMetadataFile(const QString &filename);
        QString getMetadataFile();
        void configure(ExtractionConfiguration *excfg);
        ExtractionConfiguration *getConfig();
        void extract();

    protected:
        QString input_;
        QString output_;
        QString metadata_;
        ExtractionConfiguration *excfg_;
        virtual void performExtraction() = 0;
};

#endif /*__EXTRACTOR_H__*/
