#include "HZExtractor.h"

HomogeneousZoneExtractor::HomogeneousZoneExtractor() : SingleExtractor() {
    graph_ = 0;
    img_ = 0;
}

HomogeneousZoneExtractor::HomogeneousZoneExtractor(const QString &input, const QString &output, const QString &metadata, ExtractionConfiguration *excfg) : SingleExtractor(input, output, metadata, excfg) {
    graph_ = 0;
    img_ = new QImage(input_.toString());
}

HomogeneousZoneExtractor::~HomogeneousZoneExtractor() {
    if(graph_)
        delete graph_;
    if(img_)
        delete img_;
}

QSet<int> HomogeneousZoneExtractor::visibility(QList<QRectF> rectangles, QRectF rect, double thresh) {
    QSet<int> result;
    // right, left, top, bottom
    QMap<qreal, int> rMap, lMap, tMap, bMap;
    QList<int> rList, lList, tList, bList;
    QRectF temp, hrect, vrect;
    QList<QRectF> tempListR;
    QList<int> tempListI;
    qreal vis;

    for(int i=0; i<rectangles.size(); ++i) {
        if(rect.intersects(rectangles[i])) {
            result.insert(i);
        } else {
            // Horizontal visibility
            if(((rectangles[i].top() <= rect.top()) && (rectangles[i].bottom() >= rect.top())) ||
                    ((rectangles[i].top() > rect.top()) && (rectangles[i].top() <= rect.bottom()))) {
                // Zones on the right
                if(rectangles[i].left() >= rect.right())
                    rMap.insertMulti(rectangles[i].left()-rect.right(), i);
                // Zones on the left
                else if(rectangles[i].right() <= rect.left())
                    lMap.insertMulti(rect.left()-rectangles[i].right(), i);
            }
            // Vertical visibility
            if(((rectangles[i].left() <= rect.left()) && (rectangles[i].right() >= rect.left())) ||
                    ((rectangles[i].left() > rect.left()) &&(rectangles[i].left() <= rect.right()))) {
                // Zones on the bottom
                if(rectangles[i].top() >= rect.bottom())
                    bMap.insertMulti(rectangles[i].top()-rect.bottom(), i);
                else if(rectangles[i].bottom() <= rect.top())
                    tMap.insertMulti(rect.top()-rectangles[i].bottom(), i);
            }
        }
    }

    // Rectangles are sorted by distance to rect thanks to the maps
    rList = rMap.values(); lList = lMap.values(); tList = tMap.values(); bList = bMap.values();

    // Horizontal
    hrect = rect;
    hrect.setLeft(0);
    hrect.setRight(1);
    for(auto i: rList) {
        rectangles[i].setLeft(0);
        rectangles[i].setRight(1);
    }
    for(auto i: lList) {
        rectangles[i].setLeft(0);
        rectangles[i].setRight(1);
    }

    // Right
    tempListR.clear();
    for(int i=0; i<rList.size(); ++i) {
        temp = rectangles[rList[i]] & hrect;
        vis = temp.height();
        if(tempListR.isEmpty()) {
            tempListR.append(temp);
        } else {
            tempListI.clear();
            for(int j=0; j<tempListR.size(); ++j) {
                if(temp.intersects(tempListR[j])) {
                    tempListI.append(j);
                    vis = vis - (temp & tempListR[j]).height();
                }
            }
            if(tempListI.isEmpty()) {
                tempListR.append(temp);
            } else {
                for(int j=tempListI.size()-1; j>=1; --j) {
                    tempListR[tempListI[0]] = tempListR[tempListI[0]] | tempListR.takeAt(tempListI[j]);
                }
                tempListR[tempListI[0]] = tempListR[tempListI[0]] | temp;
            }
        }
        vis = vis/qMin(rectangles[rList[i]].height(), hrect.height());
        if(vis >= thresh)
            result.insert(rList[i]);
    }

    // Left
    tempListR.clear();
    for(int i=0; i<lList.size(); ++i) {
        temp = rectangles[lList[i]] & hrect;
        vis = temp.height();
        if(tempListR.isEmpty()) {
            tempListR.append(temp);
        } else {
            tempListI.clear();
            for(int j=0; j<tempListR.size(); ++j) {
                if(temp.intersects(tempListR[j])) {
                    tempListI.append(j);
                    vis = vis - (temp & tempListR[j]).height();
                }
            }
            if(tempListI.isEmpty()) {
                tempListR.append(temp);
            } else {
                for(int j=tempListI.size()-1; j>=1; --j) {
                    tempListR[tempListI[0]] = tempListR[tempListI[0]] | tempListR.takeAt(tempListI[j]);
                }
                tempListR[tempListI[0]] = tempListR[tempListI[0]] | temp;
            }
        }
        vis = vis/qMin(rectangles[lList[i]].height(), hrect.height());
        if(vis >= thresh)
            result.insert(lList[i]);
    }

    // Vertical
    vrect = rect;
    vrect.setTop(0);
    vrect.setBottom(1);
    for(auto i: bList) {
        rectangles[i].setTop(0);
        rectangles[i].setBottom(1);
    }
    for(auto i: tList) {
        rectangles[i].setTop(0);
        rectangles[i].setBottom(1);
    }

    // Bottom
    tempListR.clear();
    for(int i=0; i<bList.size(); ++i) {
        temp = rectangles[bList[i]] & vrect;
        vis = temp.width();
        if(tempListR.isEmpty()) {
            tempListR.append(temp);
        } else {
            tempListI.clear();
            for(int j=0; j<tempListR.size(); ++j) {
                if(temp.intersects(tempListR[j])) {
                    tempListI.append(j);
                    vis = vis - (temp & tempListR[j]).width();
                }
            }
            if(tempListI.isEmpty()) {
                tempListR.append(temp);
            } else {
                for(int j=tempListI.size()-1; j>=1; --j) {
                    tempListR[tempListI[0]] = tempListR[tempListI[0]] | tempListR.takeAt(tempListI[j]);
                }
                tempListR[tempListI[0]] = tempListR[tempListI[0]] | temp;
            }
        }
        vis = vis/qMin(rectangles[bList[i]].width(), vrect.width());
        if(vis >= thresh)
            result.insert(bList[i]);
    }

    // Top
    tempListR.clear();
    for(int i=0; i<tList.size(); ++i) {
        temp = rectangles[tList[i]] & vrect;
        vis = temp.width();
        if(tempListR.isEmpty()) {
            tempListR.append(temp);
        } else {
            tempListI.clear();
            for(int j=0; j<tempListR.size(); ++j) {
                if(temp.intersects(tempListR[j])) {
                    tempListI.append(j);
                    vis = vis - (temp & tempListR[j]).width();
                }
            }
            if(tempListI.isEmpty()) {
                tempListR.append(temp);
            } else {
                for(int j=tempListI.size()-1; j>=1; --j) {
                    tempListR[tempListI[0]] = tempListR[tempListI[0]] | tempListR.takeAt(tempListI[j]);
                }
                tempListR[tempListI[0]] = tempListR[tempListI[0]] | temp;
            }
        }
        vis = vis/qMin(rectangles[tList[i]].width(), vrect.width());
        if(vis >= thresh)
            result.insert(tList[i]);
    }
    return result;
}

QSet<int> HomogeneousZoneExtractor::intersection(QList<QRectF> rectangles, QRectF rect, double thresh) {
    QSet<int> result;
    QRectF temp;
    for(int i = 0; i < rectangles.size(); ++i) {
        temp = rectangles[i].intersected(rect);
        if((temp.width()*temp.height()) / (rectangles[i].width()*rectangles[i].height()) >= thresh) {
            result.insert(i);
        }
    }
    return result;
}

void HomogeneousZoneExtractor::performExtraction() {
    if(excfg_->verbose)
        qcout << " PERFORMING " << endl;
}

QColor HomogeneousZoneExtractor::color(QRect rect) {
    double r(0), g(0), b(0);
    QColor c;
    for(int x=rect.x(); x < rect.x() + rect.width(); ++x) {
        for(int y=rect.y(); y < rect.y() + rect.height(); ++y) {
            c = QColor(img_->pixel(x, y));
            r += c.redF();
            g += c.greenF();
            b += c.blueF();
        }
    }
    r /= rect.width()*rect.height();
    g /= rect.width()*rect.height();
    b /= rect.width()*rect.height();
    c = QColor(r*255, g*255, b*255);

    return QColor::fromHsv(c.hue(), 255, 255);
}
