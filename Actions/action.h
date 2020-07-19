#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT
public:
    Action();
    QString name;
    QString description;

signals:

public slots:
};

#endif // ACTION_H
