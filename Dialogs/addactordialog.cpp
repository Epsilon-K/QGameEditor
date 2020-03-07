#include "addactordialog.h"
#include "ui_addactordialog.h"

AddActorDialog::AddActorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActorDialog)
{
    ui->setupUi(this);
}

AddActorDialog::~AddActorDialog()
{
    delete ui;
}

QString AddActorDialog::getName()
{
    return ui->actorNameLineEdit->text();
}

QString AddActorDialog::getType()
{
    return ui->actorTypeComboBox->currentText();
}
