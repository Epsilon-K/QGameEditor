#ifndef KEYDOWNEVENTDIALOG_H
#define KEYDOWNEVENTDIALOG_H

#include <QDialog>
#include "Dialogs/eventdialogcommon.h"
#include "Events/keydownevent.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "helper.h"

namespace Ui {
class KeyDownEventDialog;
}

class KeyDownEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyDownEventDialog(QWidget *parent = nullptr);
    ~KeyDownEventDialog();
    Action * finalAction;
    QVector<int> keys;
    ExecutionType execution{At_Least_One_Pressed};
    bool repeat{true};

public slots:
    void enableAll();

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

    void on_clearBtn_clicked();

    void on_disbaleBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);

private:
    Ui::KeyDownEventDialog *ui;
};

#endif // KEYDOWNEVENTDIALOG_H
