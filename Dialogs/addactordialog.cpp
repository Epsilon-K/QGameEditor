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
