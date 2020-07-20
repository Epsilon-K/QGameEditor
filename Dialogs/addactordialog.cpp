#include "addactordialog.h"
#include "ui_addactordialog.h"

AddActorDialog::AddActorDialog(QWidget *parent, QVector<QString> &actorNames) :
    QDialog(parent),
    ui(new Ui::AddActorDialog)
{
    ui->setupUi(this);
    names = actorNames;
    // This is temporary for development purposes
    ui->actorNameLineEdit->setText(Helper::getRandomString(5));
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
    Helper::debugMSG("Warning", "Unknown Actor Type in function AddActorDialog::getType()");
    return ActorType::NORMAL;
}

void AddActorDialog::on_okBtn_clicked()
{
    QString actorName = getName();

    if(actorName.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Warning");
        mb.setText("Give a name for this actor.");
        mb.exec();
        return;
    }

    if(!actorName[0].isLetter()){
        QMessageBox mb(this);
        mb.setWindowTitle("Warning");
        mb.setText("Actor name should start with a letter.");
        mb.exec();
        return;
    }


    for(int i = 0; i < actorName.size(); i++){
        if(!(actorName[i].isLetter() || actorName[i].isDigit() || actorName[i] == '_')){
            QMessageBox mb(this);
            mb.setWindowTitle("Warning");
            mb.setText("Actor name can only contain letters, digits and '_' ");
            mb.exec();
            return;
        }
    }

    for(int i = 0; i < names.size(); i++){
        if(names[i] == actorName){
            QMessageBox mb(this);
            mb.setWindowTitle("Warning");
            mb.setText("Actor name already exists.");
            mb.exec();
            return;
        }
    }

    accept();
}

void AddActorDialog::on_cancelBtn_clicked()
{
    reject();
}

void AddActorDialog::on_actorNameLineEdit_textChanged(const QString &arg)
{
    QString text = ui->actorNameLineEdit->text();
    if(text[text.size()-1].toLatin1() == ' '){
        text[text.size()-1] = '_';
        ui->actorNameLineEdit->setText(text);
    }
}
