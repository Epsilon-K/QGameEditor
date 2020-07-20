#include "keydowneventdialog.h"
#include "ui_keydowneventdialog.h"

KeyDownEventDialog::KeyDownEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyDownEventDialog)
{
    ui->setupUi(this);
    //ui->keySequenceLineEdit->setDisabled(true);
}

KeyDownEventDialog::~KeyDownEventDialog()
{
    delete ui;
}

void KeyDownEventDialog::enableAll()
{
    ui->label->setDisabled(false);
    ui->label_2->setDisabled(false);
    ui->keySequenceLineEdit->setDisabled(false);
    ui->clearBtn->setDisabled(false);
    ui->disbaleBtn->setDisabled(false);
    ui->executionCombo->setDisabled(false);
    ui->repeatCheckBox->setDisabled(false);
    ui->addActionBtn->setDisabled(false);
    ui->cancelBtn->setDisabled(false);
}

void KeyDownEventDialog::on_addActionBtn_clicked()
{
    if(keys.isEmpty()){
        // Message Please!!!
        return;
    }

    EventDialogCommon edc;
    edc.getAction();
    finalAction = edc.finalAction;

    if(finalAction != nullptr){
        execution = ExecutionType (ui->executionCombo->currentIndex());
        repeat = ui->repeatCheckBox->isChecked();
        accept();
    }
}

void KeyDownEventDialog::on_cancelBtn_clicked()
{
    reject();
}

void KeyDownEventDialog::on_clearBtn_clicked()
{
    keys.clear();
    ui->keySequenceLineEdit->clear();

}

void KeyDownEventDialog::keyPressEvent(QKeyEvent *e)
{
    if(keys.at(0) == -1){
        on_clearBtn_clicked();
    }

    keys.append(e->key());
    QString t = ui->keySequenceLineEdit->text();
    t += qtKeys.value(e->key()) + " ";
    ui->keySequenceLineEdit->setText(t);
}

void KeyDownEventDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton){
        on_clearBtn_clicked();
        keys.append(-1);
        QString t = ui->keySequenceLineEdit->text();
        t += qtKeys.value(-1) + " ";
        ui->keySequenceLineEdit->setText(t);
    }
}

void KeyDownEventDialog::on_disbaleBtn_clicked()
{
    QTimer::singleShot(5000, this, SLOT(enableAll()));

    ui->label->setDisabled(true);
    ui->label_2->setDisabled(true);
    ui->keySequenceLineEdit->setDisabled(true);
    ui->clearBtn->setDisabled(true);
    ui->disbaleBtn->setDisabled(true);
    ui->executionCombo->setDisabled(true);
    ui->repeatCheckBox->setDisabled(true);
    ui->addActionBtn->setDisabled(true);
    ui->cancelBtn->setDisabled(true);
}
