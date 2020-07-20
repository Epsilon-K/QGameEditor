#ifndef COLLISIONEVENTDIALOG_H
#define COLLISIONEVENTDIALOG_H

#include <QDialog>
#include "Dialogs/eventdialogcommon.h"
#include "Events/collisionevent.h"

namespace Ui {
class CollisionEventDialog;
}

class CollisionEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollisionEventDialog(QVector<QString> &actorNames, QWidget *parent = nullptr);
    ~CollisionEventDialog();
    Action * finalAction{nullptr};
    Sides side{Any};
    QString collideActor;

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::CollisionEventDialog *ui;
};

#endif // COLLISIONEVENTDIALOG_H
