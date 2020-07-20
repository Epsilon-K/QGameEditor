#include "collisioneventdialog.h"
#include "ui_collisioneventdialog.h"

CollisionEventDialog::CollisionEventDialog(QVector<QString> &actorNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollisionEventDialog)
{
    ui->setupUi(this);

    foreach(QString name, actorNames){
        ui->actorCombo->addItem(name);
    }
}

CollisionEventDialog::~CollisionEventDialog()
{
    delete ui;
}

void CollisionEventDialog::on_addActionBtn_clicked()
{
    EventDialogCommon edc;
    edc.getAction();
    finalAction = edc.finalAction;

    if(finalAction != nullptr){
        collideActor = ui->actorCombo->currentText();
        side = Sides (ui->sideCombo->currentIndex());
        accept();
    }
}

void CollisionEventDialog::on_cancelBtn_clicked()
{
    reject();
}
