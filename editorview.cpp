#include "editorview.h"

EditorView::EditorView(QWidget *&p)
{
    setParent(p);
    setInteractive(true);
    // this should be a preference, for performance
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setTransformationAnchor(AnchorUnderMouse);
    setViewportUpdateMode(NoViewportUpdate);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameScene = new GameScene();
    setScene(gameScene);

    mainLoopTimer.setInterval(1000 / gameScene->properties->frameRate);
    connect(&mainLoopTimer, SIGNAL(timeout()), this, SLOT(frameUpdate()));
    mainLoopTimer.start();

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

    emit signalZoomLevelChanged();
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
}

void EditorView::frameUpdate()
{
    viewport()->update();
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

    clamp(&scaleLevel, 0.002, 30);
    updateScale();
    e->accept();
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);
    emit signalMouseMoveEvent(e->pos());
}

void EditorView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect, gameScene->properties->backgroundColor);
    painter->setRenderHint(QPainter::Antialiasing, false);

    // draw the grid
    if(gameScene->preferences->showGrid){
        QPen pen(gameScene->preferences->gridColor, 0, Qt::SolidLine);
        painter->setPen(pen);

        // draw vertical lines
        int gridWidth = gameScene->preferences->gridSize.width();
        int start = rect.x(); while(start % gridWidth != 0) {start++;}
        int end = rect.x() + rect.width();
        for(int i = start; i <= end; i += gridWidth){
            painter->drawLine(i, rect.y(), i, rect.y() + rect.height());
        }

        // draw horizontal lines
        int gridHeight = gameScene->preferences->gridSize.height();
        start = rect.y(); while(start % gridHeight != 0) {start++;}
        end = rect.y() + rect.height();
        for(int i = start; i <= end; i += gridHeight){
            painter->drawLine(rect.x(), i, rect.x() + rect.width(), i);
        }
    }

    // draw screen rects
    QPen pen(gameScene->preferences->resoultionColor, 0, Qt::SolidLine);
    painter->setPen(pen);

        // draw vertical lines
        int screenWidth = gameScene->properties->windowSize.width();
        int halfScrnWidth = screenWidth/2;
        int start = rect.x() - halfScrnWidth; while((start % screenWidth) != 0) {start++;}
        start += halfScrnWidth;
        int end = rect.x() + rect.width();
        for(int i = start; i <= end; i += screenWidth){
            painter->drawLine(i, rect.y(), i, rect.y() + rect.height());
        }

        // draw horizontal lines
        int screenHeight = gameScene->properties->windowSize.height();
        int halfScrnHeight = screenHeight/2;
        start = rect.y() - halfScrnHeight; while(start % screenHeight != 0) {start++;}
        start += halfScrnHeight;
        end = rect.y() + rect.height();
        for(int i = start; i <= end; i += screenHeight){
            painter->drawLine(rect.x(), i, rect.x() + rect.width(), i);
        }
}






