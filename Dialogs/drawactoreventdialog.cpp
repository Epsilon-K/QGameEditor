#include "drawactoreventdialog.h"
#include "ui_drawactoreventdialog.h"

DrawActorEventDialog::DrawActorEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawActorEventDialog)
{
    ui->setupUi(this);
}

DrawActorEventDialog::~DrawActorEventDialog()
{
    delete ui;
}

void DrawActorEventDialog::on_addActionBtn_clicked()
{
    EventDialogCommon edc;
    edc.getAction();
    finalAction = edc.finalAction;

    if(finalAction != nullptr)
        accept();
}

void DrawActorEventDialog::on_cancelBtn_clicked()
{
    reject();
}
