#include "qgameeditor.h"
#include "ui_qgameeditor.h"

QGameEditor::QGameEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QGameEditor)
{
    ui->setupUi(this);

    // GUI Stuff for now... later on this should be saved as a preference!
    showMaximized();
    loadStylesheets();
    QFont f = font();
    setStyleSheet(stylesheets[0]);
    ui->menuBar->setFont(f);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    QTimer::singleShot(30,ui->editorView, SLOT(centering()));

    // setAlignment of all tool buttons
    for(int i = 0; i < ui->toolsVerticalLayout->count(); i++){
        QWidget *widget = ui->toolsVerticalLayout->itemAt(i)->widget();
          if (widget != nullptr)
          {
            ui->toolsVerticalLayout->setAlignment(widget, Qt::AlignHCenter);
          }
    }


    // Connections
    connect(ui->editorView, SIGNAL(signalMouseMoveEvent(QPoint)), this, SLOT(on_editorView_mouse_moved(QPoint)));
    connect(ui->editorView, SIGNAL(signalZoomLevelChanged()), this, SLOT(on_editorView_zoom_changed()));

    // Zoom levels
    ui->comboBoxZoomLevel->addItem("10%");
    ui->comboBoxZoomLevel->addItem("25%");
    ui->comboBoxZoomLevel->addItem("50%");
    ui->comboBoxZoomLevel->addItem("75%");
    ui->comboBoxZoomLevel->addItem("100%");
    ui->comboBoxZoomLevel->addItem("200%");
    ui->comboBoxZoomLevel->addItem("400%");
    ui->comboBoxZoomLevel->addItem("800%");
    ui->comboBoxZoomLevel->addItem("1600%");
    ui->comboBoxZoomLevel->addItem("3000%");

    // add whatever default actors in the scene & connect their signals to the main UI
    for(int i = 0; i < ui->editorView->gameScene->actors.size(); i++){
        Actor * actor = ui->editorView->gameScene->actors[i];
        ui->actorNameComboBox->blockSignals(true);
            ui->actorNameComboBox->insertItem(0,actor->name);
        ui->actorNameComboBox->blockSignals(false);
        connect(actor, SIGNAL(actorClicked(Actor*)),this, SLOT(onActorLeftClicked(Actor*)));
        connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
        connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), ui->editorView, SLOT(onActorSelectionChanged(Actor *, bool)));
        onActorLeftClicked(actor);
    }
}

QGameEditor::~QGameEditor()
{
    delete ui;
}

void QGameEditor::loadStylesheets()
{
    // later on, scan the :/Resources/StyleSheets folder and load all of them

    QFile file(":/Resources/StyleSheets/darkorange.stylesheet");
    //QFile file(":/Resources/StyleSheets/ClassicGE.stylesheet");   // not complete
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // TODO: Error Message!
        stylesheets.append("");
        return;
    }

    QTextStream in(&file);
    stylesheets.append(in.readAll());
}

void QGameEditor::showPropertiesOfActor(Actor *actor)
{
    currentlySelectedActor = actor;

    bool oldState = ui->actorXSpinBox->blockSignals(true);
        ui->actorXSpinBox->setValue(actor->x);
    ui->actorXSpinBox->blockSignals(oldState);
    oldState = ui->actorYSpinBox->blockSignals(true);
        ui->actorYSpinBox->setValue(actor->y);
    ui->actorYSpinBox->blockSignals(oldState);

    ui->actorWidthSpinBox->setValue(actor->width);
    ui->actorHeightSpinBox->setValue(actor->height);

    // tint color
    ui->actorTintBtn->setStyleSheet("background-color: " + actor->tint.name());
    ui->actorTintLabel->setText("RGBA(" + QString::number(actor->tint.red()) + ", "
                                + QString::number(actor->tint.green()) + ", "
                                + QString::number(actor->tint.blue()) + ", "
                                + QString::number(actor->colorFXStrenght) +  ")");
}

void QGameEditor::addActor(Actor *actor)
{
    ui->editorView->gameScene->addItem(actor);
    actor->setPos(ui->editorView->mapToScene(ui->editorView->viewport()->visibleRegion().boundingRect().x()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().width()/2,
                                             ui->editorView->viewport()->visibleRegion().boundingRect().y()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().height()/2));
    connect(actor, SIGNAL(actorClicked(Actor*)), this, SLOT(onActorLeftClicked(Actor*)));
    connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
    connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), ui->editorView, SLOT(onActorSelectionChanged(Actor *, bool)));
    ui->editorView->gameScene->actors.prepend(actor);
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->insertItem(0,actor->name);
    ui->actorNameComboBox->blockSignals(false);
    onActorLeftClicked(actor);
}

void QGameEditor::on_editorView_mouse_moved(QPoint point)
{
    QString str = "Screen(" + QString::number(point.x())
            + ", " + QString::number(point.y()) + ")";
    QPoint sp = ui->editorView->mapToScene(point).toPoint();
    str += "  Game(" + QString::number(sp.x()) + ", " + QString::number(sp.y()) + ")";
    ui->viewInfoLabel->setText(str);
}

void QGameEditor::on_editorView_zoom_changed()
{
    QString str = QString::number(int(ui->editorView->scaleLevel*100)) + "%";
    ui->comboBoxZoomLevel->setItemText(0, str);
    ui->comboBoxZoomLevel->setCurrentIndex(0);
}

void QGameEditor::onActorLeftClicked(Actor *actor)
{
    showPropertiesOfActor(actor);

    bool oldState = ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->setCurrentText(actor->name);
    ui->actorNameComboBox->blockSignals(oldState);
}

void QGameEditor::onActorPositionChange(Actor *actor)
{
    if(actor->name == ui->actorNameComboBox->currentText()){
        bool oldState = ui->actorXSpinBox->blockSignals(true);
            ui->actorXSpinBox->setValue(actor->x);
        ui->actorXSpinBox->blockSignals(oldState);
        oldState = ui->actorYSpinBox->blockSignals(true);
            ui->actorYSpinBox->setValue(actor->y);
        ui->actorYSpinBox->blockSignals(oldState);
    }
}

void QGameEditor::on_actionExit_triggered()
{
    // TODO: confirmation to exit program
    close();
}

void QGameEditor::on_comboBoxZoomLevel_activated(const QString &arg1)
{
    QString s = arg1;
    s.remove(s.length()-1, 1);
    ui->editorView->scaleLevel = s.toDouble()/100;
    ui->editorView->updateScale();
}

void QGameEditor::on_actionConfig_triggered()
{
    ConfigDialog * configDialog = new ConfigDialog(ui->editorView->gameScene->properties,
                                 ui->editorView->gameScene->preferences, this);
    if(configDialog->exec() == QDialog::Accepted){
        ui->editorView->updateSceneConfigurations();
    }
    delete configDialog;
}

void QGameEditor::on_actionAdd_Actor_triggered()
{
    // Add Actor Button triggered
    AddActorDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QString actorName = dialog.getName();
        ActorType actorType = dialog.getType();

        switch (actorType) {
            case NORMAL:{
                NormalActor * actor = new NormalActor(actorName);
                addActor(actor);
                break;
            }
            case VIEW:{
                ViewActor * actor = new ViewActor(actorName,
                        ui->editorView->gameScene->getwindowRect());
                addActor(actor);
                break;
            }
            default:{
                // Should never happen!! unknown or unimplementd somehow
            }
        }
    }
}

void QGameEditor::on_snappingBtn_toggled(bool checked)
{
    // for now...
    ui->editorView->gameScene->preferences->gridSnap = checked;
}

void QGameEditor::on_actorXSpinBox_valueChanged(int arg1)
{
    //currentlySelectedActor->setX(arg1);
    for(int i = 0; i < ui->editorView->selectedActors.size(); i++){
        ui->editorView->selectedActors[i]->setX(arg1);
    }
}

void QGameEditor::on_actorYSpinBox_valueChanged(int arg1)
{
    //currentlySelectedActor->setY(arg1);
    for(int i = 0; i < ui->editorView->selectedActors.size(); i++){
        ui->editorView->selectedActors[i]->setY(arg1);
    }
}

void QGameEditor::on_actorNameComboBox_currentIndexChanged(int index)
{
    //get actor by index
    Actor * actor = ui->editorView->gameScene->actors[index];
    showPropertiesOfActor(actor);
    ui->editorView->centerOn(actor->scenePos());
}

void QGameEditor::on_actorTintBtn_clicked()
{
    QColorDialog cd;

    QColor newColor = cd.getColor(currentlySelectedActor->tint, this, "Select Actor (" + currentlySelectedActor->name + ") tint Color",
                QColorDialog::ShowAlphaChannel);

    if(newColor.isValid()){
        currentlySelectedActor->setTintColor(newColor);
        ui->actorTintBtn->setStyleSheet("background-color: " + newColor.name());
        ui->actorTintLabel->setText("RGBA(" + QString::number(newColor.red()) + ", "
                + QString::number(newColor.green()) + ", "
                + QString::number(newColor.blue()) + ", "
                + QString::number(newColor.alphaF()) +  ")");
    }
}
