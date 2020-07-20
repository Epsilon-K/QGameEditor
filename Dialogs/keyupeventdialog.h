#ifndef KEYUPEVENTDIALOG_H
#define KEYUPEVENTDIALOG_H

#include <QDialog>
#include "Dialogs/eventdialogcommon.h"
#include "Events/keyupevent.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "helper.h"

namespace Ui {
class KeyUpEventDialog;
}

class KeyUpEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyUpEventDialog(QWidget *parent = nullptr);
    ~KeyUpEventDialog();
    Action * finalAction{nullptr};
    int key{Qt::Key_A};

public slots:
    void enableAll();

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

    void on_disbaleBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent * e);
    void mousePressEvent(QMouseEvent * e);

private:
    Ui::KeyUpEventDialog *ui;
};

#endif // KEYUPEVENTDIALOG_H
