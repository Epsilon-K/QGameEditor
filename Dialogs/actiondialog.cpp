#include "actiondialog.h"
#include "ui_actiondialog.h"

ActionDialog::ActionDialog(ActionType _actionType, QString dialogTitle, QVector<Actor*> _actors, Actor *_eventActor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog)
{
    ui->setupUi(this);

    actionType = _actionType;
    setWindowTitle(dialogTitle);
    actors = _actors;
    eventActor = _eventActor;

    ui->stackedWidget->setCurrentIndex(int(actionType));
    ui->waitForFrameGroupBox->setChecked(false);

    for(int i = 0; i < actors.size(); i++){
        ui->actorComboBox->addItem(actors[i]->name);
    }
    ui->actorComboBox->addItem("Event Actor");
    ui->actorComboBox->addItem("Parent Actor");

    ui->actorComboBox->setCurrentIndex(0);
}

ActionDialog::~ActionDialog()
{
    delete ui;
}

void ActionDialog::on_waitForFrameGroupBox_toggled(bool checked)
{
    ui->waitForFrameGroupBox->setMaximumHeight(checked ? 32000 : 25);
}

void ActionDialog::on_addActionBtn_clicked()
{
    Actor * selectedActor = nullptr;
    if(ui->actorComboBox->currentText() == "Event Actor"){
        selectedActor = eventActor;
    }else if(ui->actorComboBox->currentText() == "Parent Actor"){
        selectedActor = eventActor->parentActor;
    }else{
        selectedActor = actors[ui->actorComboBox->currentIndex()];
    }

    switch (actionType) {
        case Change_Animation:{  if(ui->animCombo_d0->count() == 0) return;

            ChangeAnimationAction * action = new ChangeAnimationAction();

            action->actor = ui->actorComboBox->currentText();
            action->animation = ui->animCombo_d0->currentText();
            action->animState = ui->animDirCombo_d0->currentIndex();

            finalAction = action;
        } break;

        case Change_Animation_Direction:{
            ChangeAnimationDirectionAction * action = new ChangeAnimationDirectionAction;

            action->actor = ui->actorComboBox->currentText();
            action->animState = ui->animDirCombo_d1->currentIndex();
            finalAction = action;
        } break;

    }// end switch

    if(finalAction != nullptr) accept();
}

void ActionDialog::on_cancelBtn_clicked()
{
    reject();
}

void ActionDialog::on_actorComboBox_currentIndexChanged(const QString &text)
{
    Actor * selectedActor;
    if(text == "Event Actor"){
        selectedActor = eventActor;
    }else if(text == "Parent Actor"){
        if(eventActor->parentActor != nullptr)
            selectedActor = eventActor->parentActor;
        else{
            // Error Message : No Parent
            ui->actorComboBox->setCurrentText("Event Actor");
            return ;
        }
    }else{
        selectedActor = actors[ui->actorComboBox->currentIndex()];
    }

    switch(actionType){
    case Change_Animation:
        ui->animCombo_d0->clear();
        if(selectedActor->type != NORMAL){
            return;
        }else{
            NormalActor * norm = (NormalActor*) selectedActor;
            for(int i = 0; i < norm->animations.size(); i++){
                ui->animCombo_d0->addItem(norm->animations[i]->name);
            }
        }
        break;
    }// end switch
}
