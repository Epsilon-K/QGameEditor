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
        switch(ui->sideCombo->currentIndex()){
            default : case 0: side = Any; break;
            case 1: side = Top; break;
            case 2: side = Bottom; break;
            case 3: side = Left; break;
            case 4: side = Right; break;
            case 5: side = TopOrBottom; break;
            case 6: side = LeftOrRight; break;
        }
        accept();
    }
}

void CollisionEventDialog::on_cancelBtn_clicked()
{
    reject();
}
