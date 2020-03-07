#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QtCore>
#include <QWidget>
#include <QGraphicsView>

#include <QMatrix>
#include <QMouseEvent>
#include "gamescene.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT
public:
    EditorView(QWidget*& p);

    GameScene * gameScene;

    double scaleLevel = 1;
    QVector <QGraphicsLineItem*> gridLines;
    QVector <QGraphicsRectItem*> screenRects;

    void updateScale();
    void drawGrid();
    void setGridVisibility();
    void clamp(double * v, double min, double max){
        if(*v > max)  *v = max;
        else if(*v < min) *v = min;
    }

signals:
    void clicked();
    void signalMouseMoveEvent(QPoint point);
    void signalZoomLevelChanged();

public slots:
    void centering();
    void updateSceneConfigurations();

protected :
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // EDITORVIEW_H
