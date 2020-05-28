#include "editorview.h"

EditorView::EditorView(QWidget *&p)
{
    setParent(p);
    setInteractive(true);
    // this should be a preference, for performance
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setTransformationAnchor(AnchorUnderMouse);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameScene = new GameScene();
    setScene(gameScene);

    // Draw Cross at (0,0)
    QPen pen;
    pen.setColor(QColor(220,220,220));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(0);
    QGraphicsLineItem * hLine = new QGraphicsLineItem(-20, 0, 20, 0);
    hLine->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    QGraphicsLineItem * vLine = new QGraphicsLineItem(0, -20, 0, 20);
    vLine->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    hLine->setPen(pen); vLine->setPen(pen);
    hLine->setZValue(-1); vLine->setZValue(-1);
    gameScene->addItem(hLine); gameScene->addItem(vLine);

    // apply gameScene preferences and properties
    updateSceneConfigurations();
}

void EditorView::updateScale()
{
    QMatrix matrix;
    matrix.scale(scaleLevel, scaleLevel);

    setMatrix(matrix);

    if(scaleLevel < 0.5){
        gameScene->preferences->showGrid = false;
    }else if(scaleLevel >= 0.5 && gameScene->preferences->showGrid == false){
        gameScene->preferences->showGrid = true;
    }
    setGridVisibility();

    emit signalZoomLevelChanged();
}

void EditorView::drawGrid()
{
    // TODO : optimize this [there is no need to redraw the grid if not changed in configuration]
    // Delete previous grid and screen rects!!!
    while(!gridLines.isEmpty()){
        delete gridLines[0];
        gridLines.removeAt(0);
    }
    while(!screenRects.isEmpty()){
        delete screenRects[0];
        screenRects.removeAt(0);
    }

    // draw the grid
    QPen pen;
    pen.setColor(gameScene->preferences->gridColor);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(0);
        // draw Vertical Lines
    int st = int(sceneRect().left());
    int d = gameScene->preferences->gridSize.width();
    while(st % d != 0) st++;
    for(double i = st; i < sceneRect().right(); i += gameScene->preferences->gridSize.width()){
        QGraphicsLineItem * line = new QGraphicsLineItem(i, sceneRect().top(), i, sceneRect().bottom());
        line->setPen(pen);
        line->setZValue(-1);
        gridLines.append(line);
        gameScene->addItem(line);
    }
        // draw Horizontal Lines
    st = int(sceneRect().top());
    d = gameScene->preferences->gridSize.height();
    while(st % d != 0) st++;
    for(double i = st; i < sceneRect().bottom(); i += gameScene->preferences->gridSize.height()){
        QGraphicsLineItem * line = new QGraphicsLineItem(sceneRect().left(), i, sceneRect().right(), i);
        line->setPen(pen);
        line->setZValue(-1);
        gridLines.append(line);
        gameScene->addItem(line);
    }

    // draw ScreenRects...
    pen.setWidth(0);
    pen.setColor(gameScene->preferences->resoultionColor);
    double w = gameScene->properties->windowSize.width();
    double h = gameScene->properties->windowSize.height();
    double w2 = gameScene->properties->windowSize.width()/2;
    double h2 = gameScene->properties->windowSize.height()/2;

    int hst = int(sceneRect().left());
    d = int(w);
    while(hst % d != 0) hst++;
    int vst = int(sceneRect().top());
    d = int(h);
    pen.setWidth(0);
    while(vst % d != 0) vst++;
    for(double i = hst; i < sceneRect().right(); i += w){
        for(double j = vst; j < sceneRect().bottom(); j += h){
            QGraphicsRectItem * rect = new QGraphicsRectItem(i - w2, j - h2, w, h);
            rect->setBrush(Qt::NoBrush);
            rect->setPen(pen);
            rect->setZValue(-1);
            gameScene->addItem(rect);
            screenRects.append(rect);
        }
    }
}

void EditorView::setGridVisibility()
{
    for(int i = 0; i < gridLines.size(); i++){
        gridLines[i]->setVisible(gameScene->preferences->showGrid);
    }
}

void EditorView::centering()
{
    centerOn(QPointF(0,0));
}

void EditorView::updateSceneConfigurations()
{
    gameScene->setBackgroundBrush(gameScene->properties->backgroundColor);
    QSize ssize = gameScene->properties->sceneSize;
    gameScene->setSceneRect(ssize.width()/2 * -1, ssize.height()/2 * -1, ssize.width(), ssize.height());
    drawGrid();
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        setDragMode(QGraphicsView::ScrollHandDrag);
    }else if(e->button() == Qt::RightButton){
        setDragMode(QGraphicsView::RubberBandDrag);
    }

    QGraphicsView::mousePressEvent(e);
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    QGraphicsView::mouseReleaseEvent(e);
    setDragMode(QGraphicsView::NoDrag);

    if(scene()->selectedItems().size() != 1 && e->button() == Qt::LeftButton){
        emit(clicked());
    }
    else if(scene()->selectedItems().isEmpty() && e->button() == Qt::RightButton){
        // Context Menu
    }
}

void EditorView::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
        scaleLevel += scaleLevel/6;
    else
        scaleLevel -= scaleLevel/6;

    clamp(&scaleLevel, 0.05, 30);
    updateScale();
    e->accept();
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);
    emit signalMouseMoveEvent(e->pos());
}
