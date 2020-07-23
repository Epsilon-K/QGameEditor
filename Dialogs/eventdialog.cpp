#include "eventdialog.h"
#include "ui_eventdialog.h"

EventDialog::EventDialog(EventType _eventType, QString dialogTitle, QVector<Actor*> _actors, Actor *_eventActor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog)
{
    ui->setupUi(this);
    setWindowTitle(dialogTitle);

    eventType = _eventType;
    actors = _actors;
    eventActor = _eventActor;

    // init events UI
    ui->stackedWidget->setCurrentIndex(int(_eventType));
    for(int i = 0; i < actors.size(); i++){
        if(actors[i]->name != eventActor->name)
        ui->collisionActorCombo->addItem(actors[i]->name);
    }
    ui->collisionActorCombo->addItem("Any Actor");
}

EventDialog::~EventDialog()
{
    delete ui;
}


// Action Dialogs ------------------------
void EventDialog::createActionDialog(ActionType actionType, QString dialogTitle)
{
    ActionDialog actionDialog(eventType, actionType, dialogTitle, actors, eventActor, this);
    if(actionDialog.exec()){
        finalAction = actionDialog.finalAction;
    }
}

void EventDialog::changeAnimDialog()
{
    createActionDialog(Change_Animation, "Change Animation");
}

void EventDialog::changeAnimDirDialog()
{
    createActionDialog(Change_Animation_Direction, "Change Animation Direction");
}

void EventDialog::changeCursorDialog()
{
    createActionDialog(Change_Cursor, "Change Cursor");
}

void EventDialog::changeParentDialog()
{
    createActionDialog(Change_Parent, "Change Parent");
}

void EventDialog::physicalResponseDialog()
{
    createActionDialog(Change_Animation, "Change Animation");
}

void EventDialog::scriptEditorDialog()
{
    createActionDialog(Script_Editor, "Script Editor : " + eventActor->name);
}

void EventDialog::enableUI()
{
    if(eventType == Key_Down){
        ui->keySequenceLineEdit->setDisabled(false);
        ui->clearBtn->setDisabled(false);
        ui->disbaleBtn->setDisabled(false);
        ui->executionCombo->setDisabled(false);
        ui->repeatCheckBox->setDisabled(false);
        ui->addActionBtn->setDisabled(false);
        ui->cancelBtn->setDisabled(false);
    }else if(eventType == Key_Up){
        ui->keyUpDisableBtn->setDisabled(false);
        ui->addActionBtn->setDisabled(false);
        ui->cancelBtn->setDisabled(false);
    }
}

void EventDialog::on_addActionBtn_clicked()
{
    // create context menu
    QMenu menu;
    menu.setStyleSheet("QMenu{color: #fff;"
                       "background-color: rgb(21, 21, 22);}"
                       "QMenu::item:selected{ color: #000;"
                       "background-color: #f09427;}");

    QAction *changeAnim = menu.addAction("Change Animation");
    QAction *changeAnimDir = menu.addAction("Change Animation Direction");
    QAction *changeCursor = menu.addAction("Change Cursor");
    QAction *changeParent = menu.addAction("Change Parent");
    QAction *changePath = menu.addAction("Change Path");
    QAction *changeTransparency = menu.addAction("Change Transparency");
    QAction *ChangeZDepth = menu.addAction("Change Z Depth");
    QAction *collisionState = menu.addAction("Collision State");
    QAction *conditionalAction = menu.addAction("Conditional Action");
    QAction *createActor = menu.addAction("Create Actor");
    QAction *createTimer = menu.addAction("Create Timer");
    QAction *destroyActor = menu.addAction("Destroy Actor");
    QAction *destroyTimer = menu.addAction("Destroy Timer");
    QAction *eventDisable = menu.addAction("Event Disable");
    QAction *eventEnable = menu.addAction("Event Enable");
    QAction *followMouse = menu.addAction("Follow Mouse");
    QAction *moveTo = menu.addAction("Move To");
    QAction *physicalResponse = menu.addAction("Physical Response");
    QAction *playMusic = menu.addAction("Play Music");
    QAction *playSound = menu.addAction("Play Sound");
    QAction *scriptEditor = menu.addAction("Script Editor");
    QAction *setText = menu.addAction("Set Text");
    QAction *toAnteriorPos = menu.addAction("To Anterior Position");
    QAction *visibilityState = menu.addAction("Visibility State");

    QAction *selectedAction = menu.exec(QCursor::pos());

    //connect those actions to slots
    connect(changeAnim, &QAction::triggered, this, &EventDialog::changeAnimDialog);
    connect(changeAnimDir, &QAction::triggered, this, &EventDialog::changeAnimDirDialog);
    connect(changeCursor, &QAction::triggered, this, &EventDialog::changeCursorDialog);
    connect(changeParent, &QAction::triggered, this, &EventDialog::changeParentDialog);
    connect(physicalResponse, &QAction::triggered, this, &EventDialog::physicalResponseDialog);
    connect(scriptEditor, &QAction::triggered, this, &EventDialog::scriptEditorDialog);


    if(selectedAction){
        selectedAction->trigger();
    }


    if(finalAction != nullptr){
        // create the event object

        switch (eventType) {
        case Activation_Event :
        break;

        case Animation_Finished :
        break;

        case Collision :{
            CollisionEvent * event = new CollisionEvent();
            event->side = Sides (ui->sideCombo->currentIndex());
            event->collideActor = ui->collisionActorCombo->currentText();
            event->repeat = ui->collisionRepeatCheckBox->isChecked();
            finalEvent = event;
        } break;

        case Collision_Finished :
        break;

        default:
        case Actor_Created :{
            CreateActorEvent * event = new CreateActorEvent();
            finalEvent = event;
        }
        break;

        case Actor_Destroyed :
        break;

        case Draw_Actor :{
            DrawActorEvent * event = new DrawActorEvent();
            finalEvent = event;
        } break;

        case Key_Down :{
            KeyDownEvent * event = new KeyDownEvent();
            event->keys = keys;
            event->executeWhen = ExecutionType (ui->executionCombo->currentIndex());
            event->repeat = ui->repeatCheckBox->isChecked();
            finalEvent = event;
        } break;

        case Key_Up :{
            KeyUpEvent * event = new KeyUpEvent();
            event->key = key;
        }break;

        case Mouse_Down :
        break;

        case Mouse_Up :
        break;

        case Mouse_Enter :
        break;

        case Mouse_Leave :
        break;

        case Move_Finished :
        break;

        case Out_Of_Vision :
        break;

        case Path_Finished :
        break;

        case Timer_Up :
        break;

        }   // end Switch

        if(finalEvent != nullptr){
            finalEvent->action = finalAction;
            accept();
        }
    }
}

void EventDialog::on_cancelBtn_clicked()
{
    reject();
}

void EventDialog::keyPressEvent(QKeyEvent *e)
{
    if(eventType == Key_Down){
        if(keys.at(0) == -1){
            on_clearBtn_clicked();
        }

        keys.append(e->key());
        QString t = ui->keySequenceLineEdit->text();
        t += qtKeys.value(e->key()) + " ";
        ui->keySequenceLineEdit->setText(t);
    }else if(eventType == Key_Up){
        key = e->key();
        ui->keyUpLabel->setText("Press event key or right click for 'any' key : " + qtKeys.value(e->key()));
    }else{
        QDialog::keyPressEvent(e);
    }
}

void EventDialog::mousePressEvent(QMouseEvent *e)
{
    if(eventType == Key_Down){
        if(e->button() == Qt::RightButton){
            on_clearBtn_clicked();
            keys.append(-1);
            QString t = ui->keySequenceLineEdit->text();
            t += qtKeys.value(-1) + " ";
            ui->keySequenceLineEdit->setText(t);
        }
    }else if(eventType == Key_Up){
        if(e->button() == Qt::RightButton){
            key = -1;
            ui->keyUpLabel->setText("Press event key or right click for 'any' key : " + qtKeys.value(-1));
        }
    }else{
        QDialog::mousePressEvent(e);
    }
}

void EventDialog::on_clearBtn_clicked()
{
    keys.clear();
    ui->keySequenceLineEdit->clear();
}

void EventDialog::on_disbaleBtn_clicked()
{
    QTimer::singleShot(5000, this, SLOT(enableUI()));

    ui->keySequenceLineEdit->setDisabled(true);
    ui->clearBtn->setDisabled(true);
    ui->disbaleBtn->setDisabled(true);
    ui->executionCombo->setDisabled(true);
    ui->repeatCheckBox->setDisabled(true);
    ui->addActionBtn->setDisabled(true);
    ui->cancelBtn->setDisabled(true);
}

void EventDialog::on_keyUpDisableBtn_clicked()
{
    QTimer::singleShot(2000, this, SLOT(enableUI()));

    ui->keyUpDisableBtn->setDisabled(true);
    ui->addActionBtn->setDisabled(true);
    ui->cancelBtn->setDisabled(true);
}
