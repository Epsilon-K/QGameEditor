#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H

#include <QDialog>
#include "Actors/actor.h"
#include "Actors/normalactor.h"

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
    Q_OBJECT

public:
    ActionDialog(EventType _eventType, ActionType _actionType, QString dialogTitle, QVector<Actor*> _actors, Actor *_eventActor, QWidget *parent = nullptr);
    ~ActionDialog();
    ActionType actionType{Change_Transparency};
    EventType eventType{Actor_Created};

    QVector<Actor*> actors;
    Actor * eventActor{nullptr};

    Action * finalAction{nullptr};

private slots:
    void on_waitForFrameGroupBox_toggled(bool checked);

    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

    void on_actorComboBox_currentIndexChanged(const QString &text);

private:
    Ui::ActionDialog *ui;
};

#endif // ACTIONDIALOG_H
