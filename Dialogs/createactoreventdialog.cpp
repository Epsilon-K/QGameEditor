#include "createactoreventdialog.h"
#include "ui_createactoreventdialog.h"

createActorEventDialog::createActorEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createActorEventDialog)
{
    ui->setupUi(this);
}

createActorEventDialog::~createActorEventDialog()
{
    delete ui;
}

void createActorEventDialog::on_addActionBtn_clicked()
{
    EventDialogCommon edc;
    edc.getAction();
    finalAction = edc.finalAction;

    if(finalAction != nullptr)
        accept();
}

void createActorEventDialog::on_cancelBtn_clicked()
{
    reject();
}
