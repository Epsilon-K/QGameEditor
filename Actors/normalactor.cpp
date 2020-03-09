#include "normalactor.h"

NormalActor::NormalActor(QString _name)
{
    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    QPixmap pix(":/Resources/images/GE Actor in editor.png");
    setPixmap(pix);

    name = _name;
}
