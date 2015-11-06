#ifndef __EXTRACTIONCONFIGURATION_H__
#define __EXTRACTIONCONFIGURATION_H__

#include "Core/IPrintable.h"

/**
 * @brief The ExtractionConfiguration class contains parameters for graphs extraction.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT ExtractionConfiguration : virtual public IPrintable {
    public:
        /**
         * @brief Constructs a new ExtractionConfiguration object.
         */
        ExtractionConfiguration();
        /**
         * @brief Destructs an ExtractionConfiguration object.
         */
        ~ExtractionConfiguration();

        /**
         * @brief Resets the parameters to default values.
         */
        void reset();

        /**
         * @brief Prints the configuration.
         */
        void print(Printer *p);

        // Generic options
        /**
         * @brief Activates the verbosity of the extractor.
         */
        bool verbose;

        // RAG
        /**
         * @brief Size of the binary image pruning after skeletonization.
         */
        int pruningSize;

        /**
         * @brief Tolerance on region adjacency.
         */
        int tolerance;

        /**
         * @brief The maximal order of the zernike invariant moments to extract.
         */
        int zernikeOrder;
};

#endif /* __EXTRACTIONCONFIGURATION_H__ */
