#ifndef GEMPP_RAGEXTRACTOR_H
#define GEMPP_RAGEXTRACTOR_H

#include <QPoint>
#include "SingleExtractor.h"
#include "Zernike.h"
#include "BinaryPNG.h"
#include "Model/Graph.h"
#include "qgarlib/CleanedBinaryImage.h"
#include "qgarlib/Dist34BlackCCImage.h"
#include "qgarlib/HysteresisBinaryImage.h"
#include "qgarlib/LabeledSkeletonImage.h"
#include "qgarlib/LinkedChainList.h"
#include "qgarlib/PbmFile.h"
#include "qgarlib/ConnectedComponents.h"
#include "qgarlib/DilatedBinaryImage.h"
#include "qgarlib/ErodedBinaryImage.h"

using namespace qgar;

/**
 * @brief The RegionAdjacencyGraphExtractor class allows the extraction of region adjacency graphs
 * on binary images, by computing the skeleton of the image, extraction the connected components to
 * make the vertices of the graph, and connecting the neighbor components to make the edges of the graph.
 *
 * @author J.Lerouge <julien.lerouge@litislab.fr>
 */
class DLL_EXPORT RegionAdjacencyGraphExtractor : public SingleExtractor {
    public:
        /**
         * @brief Constructs a new RegionAdjacencyGraphExtractor object.
         */
        RegionAdjacencyGraphExtractor();

        /**
         * @brief Constructs a RegionAdjacencyGraphExtractor object with parameters.
         * @param input the input of the extraction
         * @param output the output of the extraction
         * @param metadata metadata on the extraction
         * @param excfg configuration of the extractor
         */
        RegionAdjacencyGraphExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg);

        /**
         * @brief Destructs a HomogeneousZoneExtractor object.
         */
        ~RegionAdjacencyGraphExtractor();

        /**
         * @brief Returns the output graph.
         * @return a graph
         */
        Graph *getGraph();

    private:
        /**
         * @brief The output graph.
         */
        Graph *graph_;

        /**
         * @brief The input binary image.
         */
        BinaryImage img_;

        void performExtraction();

        /**
         * @brief Inverts inplace a binary image.
         * @param img the image
         */
        static void invert(BinaryImage &img);

        /**
         * @brief Computes the centroid point of a white connected component in a binary image.
         * @param img the binary image
         * @param origin the origin top left point in the original image coordinates
         * @return the centroid point
         */
        static QPoint getCentroid(BinaryImage &img, const GenPoint<int> &origin);

        /**
         * @brief Computes the pixel area of a white connected component in a binary image.
         * @param img the binary image
         * @return the pixel area
         */
        static int getArea(BinaryImage &img);

        /**
         * @brief Tests whether two connected components are adjacent, with the tolerance
         * stored in the ExtractionConfiguration.
         * @param im1 the binary image of the first connected component
         * @param bb1 the bounding box of the first connected component expressed in the original image coordinates
         * @param im2 the binary image of the second connected component
         * @param bb2 the bounding box of the second connected component expressed in the original image coordinates
         * @return a boolean
         */
        bool areAdjacent(BinaryImage &im1, BoundingBox &bb1, BinaryImage &im2, BoundingBox &bb2);

        /**
         * @brief Dilates the white connected component using the tolerance stored in the ExtractionConfiguration,
         * and store it in a large enough image to store two possibly adjacent connected components.
         * @param im the binary image of the connected component
         * @param bb the bounding box of the connected component expressed in the original image coordinates
         * @param bbUnion the union of the bounding boxes of two two possibly adjacent connected components
         * @return a binary image
         */
        BinaryImage adjacencyImage(BinaryImage &im, BoundingBox &bb, BoundingBox &bbUnion);
};

#endif /*RAGEXTRACTOR_H*/
