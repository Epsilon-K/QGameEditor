#include "settextdialog.h"
#include "ui_settextdialog.h"

SetTextDialog::SetTextDialog(QString text, QFont f, QColor textColor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTextDialog)
{
    ui->setupUi(this);
    ui->textEdit->setFont(f);
    ui->textEdit->setPlainText(text); finalText = text;
    ui->textEdit->setTextColor(textColor);
}

SetTextDialog::~SetTextDialog()
{
    delete ui;
}

void SetTextDialog::on_okBtn_clicked()
{
    finalText = ui->textEdit->toPlainText();
    accept();
}

void SetTextDialog::on_cancelBtn_clicked()
{
    reject();
}
