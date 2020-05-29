#ifndef POINTHANDLE_H
#define POINTHANDLE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <QPen>

class PointHandleItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    PointHandleItem(QRect r, QGraphicsItem * _parent);

    QColor selectionColor{QColor(100,100,255)};
};

#endif // POINTHANDLE_H
