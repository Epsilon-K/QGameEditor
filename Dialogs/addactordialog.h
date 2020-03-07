#ifndef ADDACTORDIALOG_H
#define ADDACTORDIALOG_H

#include <QDialog>

namespace Ui {
class AddActorDialog;
}

class AddActorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddActorDialog(QWidget *parent = nullptr);
    ~AddActorDialog();

    QString getName();
    QString getType();

private:
    Ui::AddActorDialog *ui;
};

#endif // ADDACTORDIALOG_H
