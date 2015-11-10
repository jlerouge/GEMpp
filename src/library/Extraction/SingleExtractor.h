#ifndef GEMPP_SINGLEEXTRACTOR_H
#define GEMPP_SINGLEEXTRACTOR_H

#include "GenericExtractor.h"

/**
 * @brief The SingleExtractor class allows the extraction of data on a single file.
 * Input, output and metadata all filenames.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT SingleExtractor : virtual public GenericExtractor {
    public:
        /**
         * @brief Constructs a new SingleExtractor object.
         */
        SingleExtractor();

        /**
         * @brief Constructs a SingleExtractor object with parameters.
         * @param input the input filename of the extraction
         * @param output the output filename of the extraction
         * @param metadata the metadata filename on the extraction
         * @param excfg configuration of the extractor
         */
        SingleExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a SingleExtractor object.
         */
        ~SingleExtractor();

        /**
         * @brief Returns the input filename of the extraction.
         * @return the input
         */
        QString getInput();

        /**
         * @brief Returns the output filename of the extraction.
         * @return the input
         */
        QString getOutput();

        /**
         * @brief Returns the metadata filename of the extraction.
         * @return the input
         */
        QString getMetadata();
};

#endif /* GEMPP_SINGLEEXTRACTOR_H */
