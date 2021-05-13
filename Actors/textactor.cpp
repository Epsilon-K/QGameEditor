#include "textactor.h"

TextActor::TextActor(QString _name)
{
    name = _name;
    Actor::setToolTip(name);
    Actor::type = LABEL;
    setEditingMode(false);
    QGraphicsTextItem::setFlag(QGraphicsItem::ItemClipsToShape);
    setAlignment(Qt::AlignHCenter);
    setTextWidth(-1);

    QFont f("Century Gothic", 14);
    setFont(f);
    QGraphicsTextItem::setDefaultTextColor(Qt::white);
    setPlainText("Text");

    width = getWidth();
    height = getHeight();
    originPointItem->setPos(QPoint(0, 0));
    updateOriginPoint();
}

int TextActor::getWidth()
{
    return int (QGraphicsTextItem::boundingRect().width());
}

int TextActor::getHeight()
{
    return int (QGraphicsTextItem::boundingRect().height());
}

void TextActor::setPlainText(QString _text)
{
    text = _text;
    QGraphicsTextItem::setPlainText(text);

    updateSize();
}

void TextActor::setEditingMode(bool edit)
{
    editing = edit;
    if(editing){
        Actor::setFocus(Qt::MouseFocusReason);  // Qt bug, This doesn't work soo The Application shortcuts will interfere with the user typing...
        setTextInteractionFlags(Qt::TextEditorInteraction);
        QTextCursor cursor(document());
        textCursor().setPosition(0);
        setTextCursor(cursor);
    }else{
        setTextInteractionFlags(Qt::NoTextInteraction);
        QTextCursor nullTC;
        setTextCursor(nullTC);

        updateSize();
    }
}

void TextActor::setFont(const QFont &font)
{
    QGraphicsTextItem::setFont(font);

    updateSize();
}

void TextActor::updateSize()
{
    width = getWidth();
    height = getHeight();
}

void TextActor::setAlignment(Qt::AlignmentFlag f)
{
    QTextOption op = document()->defaultTextOption();
    op.setAlignment(f);
    document()->setDefaultTextOption(op);
}

QRectF TextActor::boundingRect() const
{
    return QGraphicsTextItem::boundingRect();
}

void TextActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter,option,widget);
    if(editing){
        QPen p(selectionColor, 0, Qt::SolidLine);
        painter->setPen(p);
        painter->drawRect(boundingRect().adjusted(0,0, -p.width(), -p.width()));
    }
}

void TextActor::setTintColor(QColor color)
{
    tint = color;
}

void TextActor::setTintStrength(qreal strength)
{
    colorFXStrenght = strength;
    Actor::update();
}

QPainterPath TextActor::shape() const
{
    if(! clipShape) return QGraphicsTextItem::shape();

    // this doesn't work ....
    QPainterPath textPath;
    textPath.addText(QPointF(0.5,0.5), font(), toPlainText());
    QPainterPathStroker ps; ps.setWidth(font().pointSize());
    QPainterPath outline = ps.createStroke(textPath);

    return outline;
}

QVariant TextActor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSelectedHasChanged){
        bool selected = value.toBool();
        if(!selected){
            setEditingMode(selected);
        }
    }

    return Actor::itemChange(change, value);
}


// ------------------------------------------------------------------

void TextActor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(editing)
        QGraphicsTextItem::hoverEnterEvent(event);
    else Actor::hoverEnterEvent(event);
}

void TextActor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(editing)
        QGraphicsTextItem::hoverLeaveEvent(event);
    else Actor::hoverLeaveEvent(event);
}

void TextActor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setEditingMode(!editing);
}

void TextActor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(editing)
        QGraphicsTextItem::mousePressEvent(event);
    else Actor::mousePressEvent(event);
}

void TextActor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(editing)
        QGraphicsTextItem::mouseReleaseEvent(event);
    else Actor::mouseReleaseEvent(event);
}

void TextActor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(editing)
        QGraphicsTextItem::mouseMoveEvent(event);
    else Actor::mouseMoveEvent(event);
}

void TextActor::keyPressEvent(QKeyEvent *event)
{
    if(editing)
        QGraphicsTextItem::keyPressEvent(event);
    else Actor::keyPressEvent(event);
}
