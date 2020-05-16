#include "addactordialog.h"
#include "ui_addactordialog.h"

AddActorDialog::AddActorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActorDialog)
{
    ui->setupUi(this);
    ui->actorNameLineEdit->setText(getRandomString(5));
}

AddActorDialog::~AddActorDialog()
{
    delete ui;
}

QString AddActorDialog::getRandomString(int size)
{
    QString str;
    for(int i = 0; i < size; i++){
        str.append(rand()%26 + 65);
    }
    return str;
}

QString AddActorDialog::getName()
{
    return ui->actorNameLineEdit->text();
}

ActorType AddActorDialog::getType()
{
    QString type = ui->actorTypeComboBox->currentText();
    if(type == "Normal"){
        return ActorType::NORMAL;
    }else if(type == "View"){
        return ActorType::VIEW;
    }else if(type == "Canvas"){
        return ActorType::CANVAS;
    }else if(type == "Wire Frame Region"){
        return ActorType::WIRE_FRAME_REGION;
    }else if(type == "Filled Region"){
        return ActorType::FILLED_REGION;
    }else if(type == "Label"){
        return ActorType::LABEL;
    }

    // Should NOT HAPPEN!!!
    return ActorType::NORMAL;
}
