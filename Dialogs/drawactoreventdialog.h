#ifndef DRAWACTOREVENTDIALOG_H
#define DRAWACTOREVENTDIALOG_H

#include <QDialog>
#include "Dialogs/eventdialogcommon.h"

namespace Ui {
class DrawActorEventDialog;
}

class DrawActorEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawActorEventDialog(QWidget *parent = nullptr);
    ~DrawActorEventDialog();
    Action *finalAction{nullptr};

private slots:
    void on_addActionBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::DrawActorEventDialog *ui;
};

#endif // DRAWACTOREVENTDIALOG_H
