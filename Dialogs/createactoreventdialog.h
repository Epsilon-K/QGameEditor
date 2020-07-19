#ifndef CREATEACTOREVENTDIALOG_H
#define CREATEACTOREVENTDIALOG_H

#include <QDialog>
#include "Dialogs/eventdialogcommon.h"

namespace Ui {
class createActorEventDialog;
}

class createActorEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createActorEventDialog(QWidget *parent = nullptr);
    ~createActorEventDialog();
    Action * finalAction{nullptr};

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::createActorEventDialog *ui;
};

#endif // CREATEACTOREVENTDIALOG_H
