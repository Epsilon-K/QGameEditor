#ifndef FILLEDREGIONACTOR_H
#define FILLEDREGIONACTOR_H

#include <QObject>
#include "Actors/actor.h"

class FilledRegionActor : public Actor, public QGraphicsRectItem
{
    Q_OBJECT
public:
    FilledRegionActor(QString _name, QRect r);
    int getWidth();
    int getHeight();

    // Pure Virtual functions...
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTintColor(QColor color);
    void setTintStrength(qreal strength);
};

#endif // FILLEDREGIONACTOR_H
