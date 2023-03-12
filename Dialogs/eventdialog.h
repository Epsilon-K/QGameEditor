#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "Dialogs/actiondialog.h"

#include <QMenu>
#include <QAction>

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    EventDialog(EventType _eventType, QString dialogTitle, QVector<Actor*> _actors, Actor *_eventActor, QWidget *parent = nullptr);
    ~EventDialog();
    EventType eventType{Actor_Created};

    QVector<Actor*> actors;
    Actor * eventActor{nullptr};

    Event * finalEvent{nullptr};
    Action * finalAction{nullptr};


    // specific events use this
    QList <int> keys; // for key down sequence
    int key{65};        // for key up

public slots:
    void createActionDialog(ActionType actionType, QString dialogTitle);
    void changeAnimDialog();
    void changeAnimDirDialog();
    void changeCursorDialog();
    void changeParentDialog();
    void physicalResponseDialog();
    void scriptEditorDialog();

    void enableUI();

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

    void on_clearBtn_clicked();

    void on_disbaleBtn_clicked();

    void on_keyUpDisableBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);

private:
    Ui::EventDialog *ui;
};

#endif // EVENTDIALOG_H
