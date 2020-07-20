#include "keyupeventdialog.h"
#include "ui_keyupeventdialog.h"

KeyUpEventDialog::KeyUpEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyUpEventDialog)
{
    ui->setupUi(this);
}

KeyUpEventDialog::~KeyUpEventDialog()
{
    delete ui;
}

void KeyUpEventDialog::enableAll()
{
    ui->label->setDisabled(false);
    ui->disbaleBtn->setDisabled(false);
    ui->addActionBtn->setDisabled(false);
    ui->cancelBtn->setDisabled(false);
}

void KeyUpEventDialog::on_addActionBtn_clicked()
{
    EventDialogCommon edc;
    edc.getAction();
    finalAction = edc.finalAction;

    if(finalAction != nullptr){
        accept();
    }
}

void KeyUpEventDialog::on_cancelBtn_clicked()
{
    reject();
}

void KeyUpEventDialog::keyPressEvent(QKeyEvent *e)
{
    key = e->key();
    ui->label->setText("Press event key or right click for 'any' key : " + qtKeys.value(key));
}

void KeyUpEventDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        key = -1;
        ui->label->setText("Press event key or right click for 'any' key : " + qtKeys.value(-1));
    }
}

void KeyUpEventDialog::on_disbaleBtn_clicked()
{
    QTimer::singleShot(2000, this, SLOT(enableAll()));

    ui->label->setDisabled(true);
    ui->disbaleBtn->setDisabled(true);
    ui->addActionBtn->setDisabled(true);
    ui->cancelBtn->setDisabled(true);
}
