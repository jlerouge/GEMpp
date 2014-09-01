#ifndef __PAIREXTRACTOR_H__
#define __PAIREXTRACTOR_H__

#include "GenericExtractor.h"

class DLL_EXPORT PairExtractor : virtual public GenericExtractor {
    public:
        PairExtractor();
        PairExtractor(const QPair<QString, QString> &inputs, const QPair<QString, QString> &outputs,
                      const QPair<QString, QString> &metadata, ExtractionConfiguration *excfg);
        virtual ~PairExtractor();

        void setInput(const QPair<QString, QString> &filenames);
        QPair<QString, QString> getInput() const;
        void setOutput(const QPair<QString, QString> &filenames);
        QPair<QString, QString> getOutput() const;
        void setMetadata(const QPair<QString, QString> &filenames);
        QPair<QString, QString> getMetadata() const;

    private:
        static QStringList toList(const QPair<QString, QString> &pair);
        static QPair<QString, QString> toPair(const QStringList &list);
};


#endif /*__EXTRACTOR_H__*/
