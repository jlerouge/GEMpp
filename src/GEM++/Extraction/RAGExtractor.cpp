#include "RAGExtractor.h"

RegionAdjacencyGraphExtractor::RegionAdjacencyGraphExtractor() : SingleExtractor() {
    graph_ = 0;
}

RegionAdjacencyGraphExtractor::RegionAdjacencyGraphExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg) : SingleExtractor(input, output, metadata, excfg) {
    graph_ = 0;
}

RegionAdjacencyGraphExtractor::~RegionAdjacencyGraphExtractor() {
    delete graph_;
}

Graph* RegionAdjacencyGraphExtractor::getGraph() {
    return graph_;
}

void RegionAdjacencyGraphExtractor::performExtraction() {
    graph_ = new Graph(Graph::UNDIRECTED);

    if(excfg_->verbose)
        qcout << "Loading binary image..." << endl;
    BinaryImage sourceImg = BinaryPNG::read(getInput(), excfg_->tolerance);
    CleanedBinaryImage cleanedImg(sourceImg);

    if(excfg_->verbose)
        cout << "Performing skeletonization..." << endl;
    Dist34BlackCCImage dist34Img(cleanedImg);
    LabeledSkeletonImage chImg(dist34Img, excfg_->pruningSize);
    LinkedChainList chainsList(chImg);

    BinaryImage skelImg(sourceImg.width(), sourceImg.height());
    memset(skelImg.pPixMap(), QGE_BW_WHITE, sizeof(BinaryImage::value_type) * skelImg.width() * skelImg.height());
    for (auto itChain = chainsList.begin(); itChain != chainsList.end(); ++itChain)
        for(auto itPoint = (itChain->pointList()).begin(); itPoint != (itChain->pointList()).end() ; ++itPoint)
            skelImg.setPixel(itPoint->x(), itPoint->y(), QGE_BW_BLACK);
    DilatedBinaryImage dilSkelImg(skelImg);
    invert(dilSkelImg);

    if(excfg_->verbose)
        qcout << "Finding connected components..." << endl;
    ConnectedComponents imCC(dilSkelImg);
    QList<BinaryImage> CCs;
    QList<BoundingBox> BBs;
    BinaryImage *temp;
    Vertex *v;
    bool background = true;
    for(int k=0; k < imCC.componentCnt(); ++k) {
        if(imCC.pComponent(k)->color() == QGE_BW_BLACK) {
            if(background) { // Ignores the background component
                background = false;
                continue;
            }
            std::vector<int> labels;
            labels.push_back(k);
            temp = imCC.makeBinaryImg(labels);
            BinaryImage bounded(*temp, imCC.pComponent(k)->accessBoundingBox());
            delete temp;
            invert(bounded);

            // Filter the CCs area
            BBs.push_back(imCC.pComponent(k)->accessBoundingBox());
            CCs.push_back(bounded);

            v = new Vertex();
            // Zernike invariant moments
            QList<double> moments = zernike2D(CCs.last(), excfg_->zernikeOrder);
            for(int m=0; m<moments.size(); ++m)
                v->addNumericAttribute("zm"+QString::number(m).rightJustified(2, '0'), moments[m]);
            v->addNumericAttribute("area", getArea(CCs.last()));
            graph_->addVertex(v);

            // Metadata about the vertex :
            //  * Connected component position
            //  * area
            //  * bounding box dimensions
            // There is a position shift because of the border
            QPoint centroid = getCentroid(CCs.last(), BBs.last().accessTopLeft());
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "centroid_x", centroid.x()-excfg_->tolerance);
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "centroid_y", centroid.y()-excfg_->tolerance);
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "area", v->getNumericAttribute("area"));
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "x", BBs.last().xTopLeft()-excfg_->tolerance);
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "y", BBs.last().yTopLeft()-excfg_->tolerance);
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "width", BBs.last().width());
            graph_->getMetadata()->setAttribute(GraphElement::VERTEX, v->getIndex(), "height", BBs.last().height());
        }
    }
    if(excfg_->verbose)
        qcout << "Making graph topology..." << endl;
    Edge *e;
    Vertex *origin, *target;
    for(int i=0; i < graph_->getVertexCount(); ++i) {
        for(int j=i+1; j < graph_->getVertexCount(); ++j) {
            if(areAdjacent(CCs[i], BBs[i], CCs[j], BBs[j])) {
                origin = graph_->getVertex(i);
                target = graph_->getVertex(j);
                e = new Edge();
                e->setIndex(graph_->getEdgeCount());
                e->setOrigin(origin);
                e->setTarget(target);
                // Undirected graph
                origin->addEdge(e, Vertex::EDGE_OUT);
                target->addEdge(e, Vertex::EDGE_IN);

                double x1, x2, y1, y2, area1, area2;
                x1 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, origin->getIndex(), "centroid_x").toDouble();
                x2 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, target->getIndex(), "centroid_x").toDouble();
                y1 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, origin->getIndex(), "centroid_y").toDouble();
                y2 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, target->getIndex(), "centroid_y").toDouble();
                area1 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, origin->getIndex(), "area").toDouble();
                area2 = graph_->getMetadata()->getAttribute(GraphElement::VERTEX, target->getIndex(), "area").toDouble();

                // Relative position and area
                e->addNumericAttribute("dist", sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))/(area1 + area2)));
                e->addNumericAttribute("areaRatio", min(area1, area2)/max(area1, area2));
                graph_->addEdge(e);
            }
        }
    }

    graph_->save(getOutput());
    QDir dir = QFileInfo(getMetadata()).absoluteDir();
    graph_->getMetadata()->setGraphAttribute("graphfile", dir.relativeFilePath(QFileInfo(getOutput()).absoluteFilePath()));
    graph_->getMetadata()->setGraphAttribute("imagefile", dir.relativeFilePath(QFileInfo(getInput()).absoluteFilePath()));
    graph_->getMetadata()->save(getMetadata());
}

void RegionAdjacencyGraphExtractor::invert(BinaryImage &img) {
    for(int i=0; i < img.height(); ++i) {
        for(int j=0; j < img.width(); ++j) {
            img.setPixel(j, i, 1-img.pixel(j, i));
        }
    }
}

QPoint RegionAdjacencyGraphExtractor::getCentroid(BinaryImage &img, const GenPoint<int> &origin) {
    double x = 0;
    double y = 0;
    int area = getArea(img);
    for(int i=0; i<img.height(); ++i) {
        for(int j=0; j<img.width(); ++j) {
            if(img.pixel(j,i) == QGE_BW_WHITE) {
                x += j;
                y += i;
            }
        }
    }
    return QPoint(x/area+origin.x(), y/area+origin.y());
}

int RegionAdjacencyGraphExtractor::getArea(BinaryImage &img) {
    int area = 0;
    for(int i=0; i<img.height(); ++i)
        for(int j=0; j<img.width(); ++j)
            area += (img.pixel(j,i) == QGE_BW_WHITE);
    return area;
}

bool RegionAdjacencyGraphExtractor::areAdjacent(BinaryImage &im1, BoundingBox &bb1, BinaryImage &im2, BoundingBox &bb2) {
    // DEBUG
    // qcout << bb1.xTopLeft() << ":" << bb1.yTopLeft() << "," << bb1.xBottomRight() << ":" << bb1.yBottomRight() << " / " << bb2.xTopLeft() << " : " << bb2.yTopLeft() << "," << bb2.xBottomRight() << ":" << bb2.yBottomRight() << endl;
    if(bb1.xBottomRight() < (bb2.xTopLeft() - 2*excfg_->tolerance) || bb1.xTopLeft() > (bb2.xBottomRight() + 2*excfg_->tolerance) ||
            bb1.yBottomRight() < (bb2.yTopLeft() - 2*excfg_->tolerance) || bb1.yTopLeft() > (bb2.yBottomRight() + 2*excfg_->tolerance))
        return false; // no possible intersection

    BoundingBox bbUnion = BoundingBox(min(bb1.xTopLeft(), bb2.xTopLeft()), min(bb1.yTopLeft(), bb2.yTopLeft()),
                                      max(bb1.xBottomRight(), bb2.xBottomRight()), max(bb1.yBottomRight(), bb2.yBottomRight()));

    if(bbUnion.width() <= (2*excfg_->tolerance+1) || bbUnion.height() <= (2*excfg_->tolerance+1))
        return true; // tiny bb => components are really close

    BinaryImage temp1 = adjacencyImage(im1, bb1, bbUnion);
    BinaryImage temp2 = adjacencyImage(im2, bb2, bbUnion);
    int tol = excfg_->tolerance;
    for(int x=tol; x < bbUnion.width()-tol; ++x)
        for(int y=tol; y < bbUnion.height()-tol; ++y)
            if(temp1.pixel(x, y) == QGE_BW_WHITE && temp2.pixel(x, y) == QGE_BW_WHITE)
                return true;
    return false;
}

BinaryImage RegionAdjacencyGraphExtractor::adjacencyImage(BinaryImage &im, BoundingBox &bb, BoundingBox &bbUnion) {
    BinaryImage result = BinaryImage(bbUnion.width(), bbUnion.height());
    memset(result.pPixMap(), QGE_BW_BLACK, sizeof(BinaryImage::value_type) * result.width() * result.height());
    for(int x=bb.xTopLeft(); x <= bb.xBottomRight(); ++x)
        for(int y=bb.yTopLeft(); y <= bb.yBottomRight(); ++y)
            result.setPixel(x-bbUnion.xTopLeft(), y-bbUnion.yTopLeft(), im.pixel(x-bb.xTopLeft(), y-bb.yTopLeft()));
    return ErodedBinaryImage(result, excfg_->tolerance);
}
