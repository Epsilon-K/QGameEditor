#ifndef TEXTACTOR_H
#define TEXTACTOR_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QTextCursor>
#include <QTextDocument>
#include <QGraphicsScene>
#include "Actors/actor.h"

class TextActor : public Actor, public QGraphicsTextItem
{
public:
    TextActor(QString _name);
    int getWidth();
    int getHeight();

    void setPlainText(QString _text);
    void setEditingMode(bool edit);
    void setFont(const QFont &font);
    void updateSize();
    void setAlignment(Qt::AlignmentFlag f);

    QString text;           // TODO : update this when set via TextItem editing mode
    bool editing{false};
    bool clipShape{false};

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTintColor(QColor color);
    void setTintStrength(qreal strength);

    QPainterPath shape() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // TEXTACTOR_H
