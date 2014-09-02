#ifndef __GENERICEXTRACTOR_H__
#define __GENERICEXTRACTOR_H__

#include "ExtractionConfiguration.h"

class DLL_EXPORT GenericExtractor {
    public:
        GenericExtractor();
        GenericExtractor(const QVariant &input, const QVariant &output, const QVariant &metadata, ExtractionConfiguration *excfg);
        virtual ~GenericExtractor();

        void setInput(const QVariant &input);
        QVariant getInput() const;
        void setOutput(const QVariant &output);
        QVariant getOutput() const;
        void setMetadata(const QVariant &metadata);
        QVariant getMetadata() const;

        void setConfiguration(ExtractionConfiguration *excfg);
        ExtractionConfiguration *getConfiguration() const;

        void extract();

    protected:
        QVariant input_;
        QVariant output_;
        QVariant metadata_;
        ExtractionConfiguration *excfg_;
        virtual void performExtraction() = 0;
};

#endif /*__GENERICEXTRACTOR_H__*/
