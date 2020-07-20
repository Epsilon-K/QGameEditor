#ifndef ADDACTORDIALOG_H
#define ADDACTORDIALOG_H

#include <QDialog>
#include <Actors/actor.h>

namespace Ui {
class AddActorDialog;
}

class AddActorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddActorDialog(QWidget *parent, QVector<QString> &actorNames);
    ~AddActorDialog();
    QVector<QString> names;
    QString getName();
    ActorType getType();

private slots:


    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_actorNameLineEdit_textChanged(const QString &arg);

private:
    Ui::AddActorDialog *ui;
};

#endif // ADDACTORDIALOG_H
