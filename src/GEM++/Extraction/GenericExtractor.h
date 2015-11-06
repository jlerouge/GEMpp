#ifndef __GENERICEXTRACTOR_H__
#define __GENERICEXTRACTOR_H__

#include "ExtractionConfiguration.h"

/**
 * @brief The GenericExtractor class represents a data extraction process.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT GenericExtractor {
    public:

        /**
         * @brief Constructs a new GenericExtractor object.
         */
        GenericExtractor();

        /**
         * @brief Destructs a GenericExtractor object with parameters.
         * @param input the input of the extraction
         * @param output the output of the extraction
         * @param metadata metadata on the extraction
         * @param excfg configuration of the extractor
         */
        GenericExtractor(const QVariant &input, const QVariant &output, const QVariant &metadata, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a GenericExtractor object.
         */
        virtual ~GenericExtractor();

        /**
         * @brief Sets the input of the extraction.
         * @param input the input
         */
        void setInput(const QVariant &input);

        /**
         * @brief Returns the input of the extraction.
         * @return the input
         */
        QVariant getInput() const;

        /**
         * @brief Sets the output of the extraction.
         * @param input the output
         */
        void setOutput(const QVariant &output);

        /**
         * @brief Returns the output of the extraction.
         * @return the output
         */
        QVariant getOutput() const;

        /**
         * @brief Sets the metadata of the extraction.
         * @param metadata the metadata
         */
        void setMetadata(const QVariant &metadata);

        /**
         * @brief Returns the metadata of the extraction.
         * @return the metadata
         */
        QVariant getMetadata() const;

        /**
         * @brief Sets the configuration of the extractor.
         * @param excfg the configuration
         */
        void setConfiguration(ExtractionConfiguration *excfg);

        /**
         * @brief Returns the configuration of the extractor.
         * @return the configuration
         */
        ExtractionConfiguration *getConfiguration() const;

        /**
         * @brief Runs the extraction.
         */
        void extract();

    protected:
        /**
         * @brief The input of the extraction.
         */
        QVariant input_;
        /**
         * @brief The output of the extraction.
         */
        QVariant output_;
        /**
         * @brief The metadata of the extraction.
         */
        QVariant metadata_;
        /**
         * @brief The configuration of the extraction.
         */
        ExtractionConfiguration *excfg_;

        /**
         * @brief The implementation of the extraction process.
         */
        virtual void performExtraction() = 0;
};

#endif /*__GENERICEXTRACTOR_H__*/
