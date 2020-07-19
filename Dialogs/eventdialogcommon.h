#ifndef EVENTDIALOGCOMMON_H
#define EVENTDIALOGCOMMON_H

// since form dialogs can't inherit each other (i think)
// this class will provide common event dialogs functionality
// for example the Actions contex Menu and... that's all really.

#include <QObject>
#include <QMenu>
#include <QAction>
#include "Actions/action.h"

class EventDialogCommon : public QObject
{
    Q_OBJECT
public:
    EventDialogCommon(){}

    Action * finalAction{nullptr};

    void getAction(){
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
        connect(changeAnim, &QAction::triggered, this, &EventDialogCommon::changeAnimDialog);
        connect(changeAnimDir, &QAction::triggered, this, &EventDialogCommon::changeAnimDirDialog);
        connect(changeCursor, &QAction::triggered, this, &EventDialogCommon::changeCursorDialog);
        connect(changeParent, &QAction::triggered, this, &EventDialogCommon::changeParentDialog);

        if(selectedAction){
            selectedAction->trigger();
        }

    }// end getAction()

public slots:
    void changeAnimDialog(){

    }

    void changeAnimDirDialog(){

    }

    void changeCursorDialog(){

    }

    void changeParentDialog(){

    }
};

#endif // EVENTDIALOGCOMMON_H
