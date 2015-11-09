#ifndef GEMPP_PAIREXTRACTOR_H
#define GEMPP_PAIREXTRACTOR_H

#include "GenericExtractor.h"

/**
 * @brief The PairExtractor class allows the extraction of data on pair of files.
 * The pair of inputs, outputs and metadata are all filenames.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT PairExtractor : virtual public GenericExtractor {
    public:
        /**
         * @brief Constructs a new PairExtractor object.
         */
        PairExtractor();

        /**
         * @brief Constructs a PairExtractor object with parameters.
         * @param inputs the pair of input filenames of the extraction
         * @param outputs the pair of output filenames of the extraction
         * @param metadata the pair of metadata filenames on the extraction
         * @param excfg configuration of the extractor
         */
        PairExtractor(const QPair<QString, QString> &inputs, const QPair<QString, QString> &outputs,
                      const QPair<QString, QString> &metadata, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a PairExtractor object.
         */
        virtual ~PairExtractor();

        /**
         * @brief Sets the two input filenames of the extraction.
         * @param filenames the input filenames
         */
        void setInput(const QPair<QString, QString> &filenames);

        /**
         * @brief Returns the two input filenames of the extraction.
         * @return the two input filenames
         */
        QPair<QString, QString> getInput() const;

        /**
         * @brief Sets the two output filenames of the extraction.
         * @param filenames the two output filenames
         */
        void setOutput(const QPair<QString, QString> &filenames);

        /**
         * @brief Returns the two output filenames of the extraction.
         * @return the two output filenames
         */
        QPair<QString, QString> getOutput() const;

        /**
         * @brief Sets the two metadata filenames of the extraction.
         * @param metadata the two metadata filenames
         */
        void setMetadata(const QPair<QString, QString> &filenames);

        /**
         * @brief Returns the two metadata filenames of the extraction.
         * @return the two metadata filenames
         */
        QPair<QString, QString> getMetadata() const;

    private:
        /**
         * @brief Transforms a pair to a two elements list.
         * @param pair the pair
         * @return a list
         */
        static QStringList toList(const QPair<QString, QString> &pair);

        /**
         * @brief Transforms a two elements list to a pair.
         * @param list the list
         * @return a pair
         */
        static QPair<QString, QString> toPair(const QStringList &list);
};


#endif /*EXTRACTOR_H*/
