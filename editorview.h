#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QtCore>
#include <QWidget>
#include <QGraphicsView>

#include <QTransform>
#include <QMouseEvent>
#include "gamescene.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT
public:
    EditorView(QWidget*& p);

    GameScene * gameScene;
    QTimer mainLoopTimer;
    double scaleLevel = 1;

    void updateScale();
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
    void frameUpdate();

protected :
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // EDITORVIEW_H
