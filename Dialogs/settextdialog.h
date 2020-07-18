#ifndef SETTEXTDIALOG_H
#define SETTEXTDIALOG_H

#include <QDialog>

namespace Ui {
class SetTextDialog;
}

class SetTextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetTextDialog(QString text, QFont f, QColor textColor, QWidget *parent = nullptr);
    ~SetTextDialog();
    QString finalText;

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::SetTextDialog *ui;
};

#endif // SETTEXTDIALOG_H
