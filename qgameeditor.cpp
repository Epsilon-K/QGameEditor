#include "qgameeditor.h"
#include "ui_qgameeditor.h"

QGameEditor::QGameEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QGameEditor)
{
    ui->setupUi(this);
    srand(uint(time(nullptr)));

    // GUI Stuff for now... later on this should be saved as a preference!
    showMaximized();
    loadStylesheets();
    QFont f = font();
    setStyleSheet(stylesheets[0]);
    ui->menuBar->setFont(f);
    QTimer::singleShot(30,ui->editorView, SLOT(centering()));
    snappingGuideLine = new QGraphicsLineItem(0,0,720,240);
    snappingGuideLine->setPen(QPen(QColor(160,70,255),0,Qt::SolidLine));
    ui->editorView->gameScene->addItem(snappingGuideLine);
    snappingGuideLine->setVisible(false);
    ui->mainSplitter->setSizes(QList<int>{1000,340});

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

    // add whatever default actors in the scene & connect their signals to the main UI
    for(int i = 0; i < ui->editorView->gameScene->actors.size(); i++){
        Actor * actor = ui->editorView->gameScene->actors[i];
        ui->actorNameComboBox->blockSignals(true);
            ui->actorNameComboBox->insertItem(0,actor->name);
        ui->actorNameComboBox->blockSignals(false);
        connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
        connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), this, SLOT(onActorSelectionChanged(Actor *, bool)));
        connect(actor, SIGNAL(snappingStateChanged(Actor*)), this, SLOT(copySnappingOfActor(Actor*)));
    }
    ui->editorView->gameScene->actors.last()->setSelected(true);
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
    // X & Y
    nonSignalSetValue(ui->actorXSpinBox, actor->x);
    nonSignalSetValue(ui->actorYSpinBox, actor->y);

    // Origin X & Y
    nonSignalSetValue(ui->actorOriginXSpinBox, actor->originPointItem->x());
    nonSignalSetValue(ui->actorOriginYSpinBox, actor->originPointItem->y());


    // Width & Height
    nonSignalSetValue(ui->actorWidthSpinBox, actor->width);
    nonSignalSetValue(ui->actorHeightSpinBox, actor->height);

    // tint color
    ui->actorTintBtn->setStyleSheet("background-color: " + actor->tint.name());
    ui->actorTintLabel->setText("RGB(" + QString::number(actor->tint.red()) + ", "
                                + QString::number(actor->tint.green()) + ", "
                                + QString::number(actor->tint.blue()) + ")");
    ui->actorTintStrengthLabel->setText("Color strength (" + QString::number(actor->colorFXStrenght*100) + "%) : ");
    nonSignalSetValue(ui->actorTintStrengthSlider, actor->colorFXStrenght * 100);

    // XScale & YScale
    nonSignalSetValue(ui->actorXScaleDoubleSpinBox, actor->xscale);
    nonSignalSetValue(ui->actorYScaleDoubleSpinBox, actor->yscale);

    // Rotation
    nonSignalSetValue(ui->actorRotationSlider, actor->rotation);
    nonSignalSetValue(ui->actorRotationSpinBox, actor->rotation);

    // Transparency
    nonSignalSetValue(ui->actorTranspSlider, actor->transp * 100);
    nonSignalSetValue(ui->actorTranspDoubleSpinBox, actor->transp);

    // ZDepth
    nonSignalSetValue(ui->actorZDepthSlider, actor->zdepth * 100);
    nonSignalSetValue(ui->actorZDepthDoubleSpinBox, actor->zdepth);

    // lock and hide checkboxes
    ui->actorLockedCheckBox->blockSignals(true);
        ui->actorLockedCheckBox->setChecked(actor->isLocked);
    ui->actorLockedCheckBox->blockSignals(false);
    ui->actorHiddenCheckBox->blockSignals(true);
        ui->actorHiddenCheckBox->setChecked(!actor->isVisible());
    ui->actorHiddenCheckBox->blockSignals(false);
}

void QGameEditor::addActor(Actor *actor)
{
    ui->editorView->gameScene->addItem(actor);
    //ui->editorView->gameScene->addItem(actor->originPointItem);
    actor->setPos(ui->editorView->mapToScene(ui->editorView->viewport()->visibleRegion().boundingRect().x()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().width()/2,
                                             ui->editorView->viewport()->visibleRegion().boundingRect().y()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().height()/2));
    connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
    connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), this, SLOT(onActorSelectionChanged(Actor *, bool)));
    connect(actor, SIGNAL(snappingStateChanged(Actor*)), this, SLOT(copySnappingOfActor(Actor*)));
    ui->editorView->gameScene->actors.append(actor);
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->insertItem(0,actor->name);
    ui->actorNameComboBox->blockSignals(false);
    onActorLeftClicked(actor);
}

void QGameEditor::nonSignalSetValue(QSpinBox *widget, int value)
{
    widget->blockSignals(true);
        widget->setValue(value);
    widget->blockSignals(false);
}

void QGameEditor::nonSignalSetValue(QDoubleSpinBox *widget, double value)
{
    widget->blockSignals(true);
        widget->setValue(value);
    widget->blockSignals(false);
}

void QGameEditor::nonSignalSetValue(QSlider *widget, int value)
{
    widget->blockSignals(true);
        widget->setValue(value);
    widget->blockSignals(false);
}

void QGameEditor::nonSignalSetValue(QComboBox *widget, QString value)
{
    widget->blockSignals(true);
        widget->setCurrentText(value);
    widget->blockSignals(false);
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
    nonSignalSetValue(ui->actorNameComboBox, actor->name);
}

void QGameEditor::onActorPositionChange(Actor *actor)
{
    if(actor->name == ui->actorNameComboBox->currentText()){
        nonSignalSetValue(ui->actorXSpinBox, actor->x);
        nonSignalSetValue(ui->actorYSpinBox, actor->y);
    }
}

void QGameEditor::onActorSelectionChanged(Actor *actor, bool state)
{
    if(state){
        selectedActors.append(actor);
    }else{
        selectedActors.removeOne(actor);
        if(selectedActors.size() < 2){
            ui->actorNameComboBox->blockSignals(true);
                ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
            ui->actorNameComboBox->blockSignals(false);
        }
    }

    if(!selectedActors.isEmpty()){ // if there are selected actors
        QList<QWidget*> list = ui->actorControlTab->findChildren<QWidget*>() ;
        foreach( QWidget* w, list ) {
           w->setEnabled( true ) ;
        }
        // then show the properties of last actor in selection list
        onActorLeftClicked(selectedActors.last());

        if(selectedActors.size() > 1){
            if(ui->actorNameComboBox->findText("Multiple Actors") == -1){
                ui->actorNameComboBox->blockSignals(true);
                    ui->actorNameComboBox->insertItem(0, "Multiple Actors");
                    ui->actorNameComboBox->setCurrentIndex(0);
                ui->actorNameComboBox->blockSignals(false);
            }else ui->actorNameComboBox->setCurrentText("Multiple Actors");

            ui->actorAnimationGroupBox->setChecked(false);
            ui->actorAnimationGroupBox->setEnabled(false);
        }
        else{
            // Only One Actor is selected
            if(selectedActors.last()->type == NORMAL){
                ui->actorAnimationGroupBox->setChecked(true);
                ui->actorAnimationGroupBox->setEnabled(true);
            }else{ui->actorAnimationGroupBox->setChecked(false);
                ui->actorAnimationGroupBox->setEnabled(false);}
        }

    }else{
        // if no currently selected actor..
        QList<QWidget*> list = ui->actorControlTab->findChildren<QWidget*>() ;
        foreach( QWidget* w, list ) {
           w->setEnabled( false ) ;
        }
    }
}

void QGameEditor::copySnappingOfActor(Actor *actor)
{
    for(int i = 0;i < selectedActors.size(); i++){
        selectedActors[i]->xSnap = actor->xSnap;
        selectedActors[i]->ySnap = actor->ySnap;
    }

    // draw snapping line if (xSnap | ySnap)
    if(actor->xSnap || actor->ySnap){
        snappingGuideLine->setVisible(true);
        QLine line;
        QPoint viewPort(ui->editorView->viewport()->visibleRegion().boundingRect().width(),
                        ui->editorView->viewport()->visibleRegion().boundingRect().height());
        QPoint actorPos(ui->editorView->mapFromScene(actor->pos()));
        if(actor->xSnap){   //XAxis
            line = QLine(ui->editorView->mapToScene(0, actorPos.ry()).toPoint(),
                         ui->editorView->mapToScene(viewPort.rx(), actorPos.ry()).toPoint());
        }else{  // YAxis
            line = QLine(ui->editorView->mapToScene(actorPos.rx(), 0).toPoint(),
            ui->editorView->mapToScene(actorPos.rx(), viewPort.ry()).toPoint());
        }
        snappingGuideLine->setLine(line);
    }else {
        snappingGuideLine->setVisible(false);
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
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setX(arg1);
    }
}

void QGameEditor::on_actorYSpinBox_valueChanged(int arg1)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setY(arg1);
    }
}

void QGameEditor::on_actorNameComboBox_currentIndexChanged(int index)
{
    //get actor by index
    QString name = ui->actorNameComboBox->itemText(index);
    if(name != "Multiple Actors"){
        Actor * actor = ui->editorView->gameScene->getActorByName(name);

        // deselect Everything...
        for(int i = 0; i < selectedActors.size(); i++){
            selectedActors[i]->blockSignals(true);
                selectedActors[i]->setSelected(false);
            selectedActors[i]->blockSignals(false);
        }
        ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
        selectedActors.clear();

        // and select only this actor
        actor->setSelected(true);

        showPropertiesOfActor(actor);
        ui->editorView->centerOn(actor->scenePos());
    }
}

void QGameEditor::on_actorTintBtn_clicked()
{
    QColorDialog cd;
    QColor newColor = cd.getColor(selectedActors.last()->tint, this, "Select Actor (" + ui->actorNameComboBox->currentText() + ") tint Color");

    if(newColor.isValid()){
        for(int i = 0; i < selectedActors.size(); i++){
            selectedActors[i]->setTintColor(newColor);
        }
        ui->actorTintBtn->setStyleSheet("background-color: " + newColor.name());
        ui->actorTintLabel->setText("RGB(" + QString::number(newColor.red()) + ", "
                + QString::number(newColor.green()) + ", "
                + QString::number(newColor.blue()) + ")");
    }
}

void QGameEditor::on_actorTintStrengthSlider_valueChanged(int value)
{
    qreal percent = qreal(value)/100;
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setTintStrength(percent);
    }
    ui->actorTintStrengthLabel->setText("Color strength (" + QString::number(value) + "%) : ");
}

void QGameEditor::on_actorXScaleDoubleSpinBox_valueChanged(double xs)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setXScale(xs);
    }

    // Also set the width on the control tab
    Actor * actor = selectedActors.last();
    nonSignalSetValue(ui->actorWidthSpinBox, actor->width);
}

void QGameEditor::on_actorYScaleDoubleSpinBox_valueChanged(double xy)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setYScale(xy);
    }

    // Aaand set the height on the control tab
    Actor * actor = selectedActors.last();
    nonSignalSetValue(ui->actorHeightSpinBox, actor->height);
}

void QGameEditor::on_actorRotationSlider_valueChanged(int value)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setRotation(value);
    }
}

void QGameEditor::on_actorTranspSlider_valueChanged(int value)
{
    qreal percent = qreal(value)/100;
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setOpacity(percent);
        selectedActors[i]->transp = percent;
    }

    // set the spinbox
    nonSignalSetValue(ui->actorTranspDoubleSpinBox, percent);
}

void QGameEditor::on_actorTranspDoubleSpinBox_valueChanged(double value)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setOpacity(value);
        selectedActors[i]->transp = value;
    }

    // set the slider
    nonSignalSetValue(ui->actorTranspSlider, value*100);
}

void QGameEditor::on_actorZDepthSlider_valueChanged(int value)
{
    qreal percent = qreal(value)/100;
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setZValue(percent);
        selectedActors[i]->zdepth = percent;
    }

    // set the spinbox
    nonSignalSetValue(ui->actorZDepthDoubleSpinBox, percent);
}

void QGameEditor::on_actorZDepthDoubleSpinBox_valueChanged(double value)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->setZValue(value);
        selectedActors[i]->zdepth = value;
    }

    // set the slider
    nonSignalSetValue(ui->actorZDepthSlider, value*100);
}

void QGameEditor::on_actorWidthSpinBox_valueChanged(int newWidth)
{
    for(int i = 0; i < selectedActors.size(); i++){
        qreal newXScale = qreal(newWidth)/selectedActors[i]->getWidth();
        selectedActors[i]->setXScale(newXScale);
    }

    // set the scale on the spinbox
    nonSignalSetValue(ui->actorXScaleDoubleSpinBox, selectedActors.last()->xscale);
}

void QGameEditor::on_actorHeightSpinBox_valueChanged(int newHeight)
{
    for(int i = 0; i < selectedActors.size(); i++){
        qreal newYScale = qreal(newHeight)/selectedActors[i]->getHeight();
        selectedActors[i]->setYScale(newYScale);
    }

    // set the scale on the spinbox
    nonSignalSetValue(ui->actorYScaleDoubleSpinBox, selectedActors.last()->yscale);
}

void QGameEditor::on_actorOriginXSpinBox_valueChanged(int arg1)
{

}

void QGameEditor::on_actorOriginYSpinBox_valueChanged(int arg1)
{

}

void QGameEditor::on_actionShow_Hidden_Actors_triggered()
{
    for(int i = 0;i < ui->editorView->gameScene->actors.size(); i++){
        if(!ui->editorView->gameScene->actors[i]->isVisible()){
            ui->editorView->gameScene->actors[i]->setVisible(true);
        }
    }
}

void QGameEditor::on_actorHiddenCheckBox_toggled(bool checked)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->blockSignals(true);
            selectedActors[i]->setVisible(!checked);
            selectedActors[i]->setSelected(false);
        selectedActors[i]->blockSignals(false);
    }
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
    ui->actorNameComboBox->blockSignals(false);
    selectedActors.clear();
}

void QGameEditor::on_actorLockedCheckBox_toggled(bool checked)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->blockSignals(true);
            selectedActors[i]->isLocked = !checked;
            selectedActors[i]->lockUnLock();
            selectedActors[i]->setSelected(false);
        selectedActors[i]->blockSignals(false);
    }
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
    ui->actorNameComboBox->blockSignals(false);
    selectedActors.clear();
}

void QGameEditor::on_actorAnimationGroupBox_toggled(bool checked)
{
    ui->actorAnimationGroupBox->setMaximumHeight(checked ? 32000 : 25);
}

void QGameEditor::on_actorPropertiesGroupBox_toggled(bool checked)
{
    ui->actorPropertiesGroupBox->setMaximumHeight(checked ? 32000 : 25);
}

void QGameEditor::on_addAnimationBtn_clicked()
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        AnimationDialog ad(this);

        if(ad.exec()){
            // create an animation and add it to actor
        }
    }
}
