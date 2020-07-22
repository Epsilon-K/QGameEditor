#ifndef CHANGEANIMATIONDIALOG_H
#define CHANGEANIMATIONDIALOG_H

#include <QDialog>
#include "Actions/changeanimationaction.h"
#include "Actors/actor.h"
#include "Actors/normalactor.h"

namespace Ui {
class ChangeAnimationDialog;
}

class ChangeAnimationDialog : public QDialog
{
    Q_OBJECT

public:
    ChangeAnimationDialog(QVector<Actor*> acts, Actor *_eventActor, QWidget *parent = nullptr);
    ~ChangeAnimationDialog();
    ChangeAnimationAction * finalAction{nullptr};
    QVector<Actor*> actors;
    Actor * eventActor;

private slots:
    void on_addBtn_clicked();

    void on_cancelBtn_clicked();

    void on_actorCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::ChangeAnimationDialog *ui;
};

#endif // CHANGEANIMATIONDIALOG_H
