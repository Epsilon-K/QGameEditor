#include "changeanimationdialog.h"
#include "ui_changeanimationdialog.h"

ChangeAnimationDialog::ChangeAnimationDialog(QVector<Actor*> acts, Actor *_eventActor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeAnimationDialog)
{
    ui->setupUi(this);
    for(int i = 0; i < acts.size(); i++){
        if(acts[i]->type == NORMAL){
            actors.append(acts[i]);
            ui->actorCombo->addItem(acts[i]->name);
        }
    }

    if(_eventActor->type == NORMAL){
        ui->actorCombo->addItem("Event Actor");
        eventActor = _eventActor;
    }

    ui->actorCombo->setCurrentIndex(0);
}

ChangeAnimationDialog::~ChangeAnimationDialog()
{
    delete ui;
}

void ChangeAnimationDialog::on_addBtn_clicked()
{
    if(ui->animCombo->currentText().isEmpty()) return;
    finalAction = new ChangeAnimationAction();

    finalAction->actor = ui->actorCombo->currentText();
    finalAction->animation = ui->animCombo->currentText();
    finalAction->animState = ui->animDirCombo->currentIndex();

    accept();
}

void ChangeAnimationDialog::on_cancelBtn_clicked()
{
    reject();
}

void ChangeAnimationDialog::on_actorCombo_currentIndexChanged(const QString &txt)
{
    ui->animCombo->clear();
    NormalActor * norm;
    if(txt == "Event Actor")
        NormalActor * norm = (NormalActor*) eventActor;
    else NormalActor * norm = (NormalActor*) actors[ui->actorCombo->currentIndex()];

    for(int i = 0 ; i < norm->animations.size(); i++){
        ui->animCombo->addItem(norm->animations[i]->name);
    }
}
