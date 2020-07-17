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
        actor->setPos(0,0);
        ui->actorNameComboBox->blockSignals(true);
            ui->actorNameComboBox->insertItem(0,actor->name);
        ui->actorNameComboBox->blockSignals(false);
        connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
        connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), this, SLOT(onActorSelectionChanged(Actor *, bool)));
        connect(actor, SIGNAL(snappingStateChanged(Actor*)), this, SLOT(copySnappingOfActor(Actor*)));
        connect(actor, SIGNAL(originChanged(Actor*)), this, SLOT(onActorOriginChanged(Actor*)));
    }
    ui->editorView->gameScene->actors.last()->setSelected(true);


    // make data folder for resources
    QDir dir;
    dir.mkdir(projectPath + "/data");
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
    nonSignalSetValue(ui->actorOriginXSpinBox, actor->originPointItem->finalPosition.x());
    nonSignalSetValue(ui->actorOriginYSpinBox, actor->originPointItem->finalPosition.y());


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

    // Normal Actor stuff
    if(actor->type == NORMAL){
        NormalActor *normal = (NormalActor *)actor;
        // Set Animations Name
        ui->actorAnimationNameComboBox->blockSignals(true);
            ui->actorAnimationNameComboBox->clear();
            for(int i = 0; i < normal->animations.size(); i++){
                QString text = normal->animations[i]->name;
                QIcon ico(normal->animations[i]->getFramePixmap(0)->scaled(32,32));
                ui->actorAnimationNameComboBox->addItem(ico,text);
            }
            if(!normal->animations.isEmpty()){
                ui->actorAnimationNameComboBox->setCurrentText(normal->animations[normal->animindex]->name);
            }
        ui->actorAnimationNameComboBox->blockSignals(false);

        ui->editAnimationBtn->setDisabled(normal->animations.isEmpty());
        ui->removeAnimationBtn->setDisabled(normal->animations.isEmpty());

        // Playing state
        nonSignalSetValue(ui->actorAnimationStateCheckBox, normal->animationState == FORWARD ? true : false);

        // Frame rate
        if(!normal->animations.isEmpty()){
            nonSignalSetValue(ui->animationFPSSpinBox, normal->animations[normal->animindex]->frameRate);
        }

        // Antialiasing
        nonSignalSetValue(ui->antialiasingCheckBox, normal->antialiasing);

        // Composition Mode
        QString mode;
        switch (normal->compositionMode) {
        default:
        case QPainter::CompositionMode_SourceOver:  mode = "Normal (Source Over)"; break;
        case QPainter::CompositionMode_Plus:  mode = "Plus"; break;
        case QPainter::CompositionMode_Multiply:  mode = "Multiply"; break;
        case QPainter::CompositionMode_Screen:  mode = "Screen"; break;
        case QPainter::CompositionMode_Overlay:  mode = "Overlay"; break;
        case QPainter::CompositionMode_Darken:  mode = "Darken"; break;
        case QPainter::CompositionMode_Lighten:  mode = "Lighten"; break;
        case QPainter::CompositionMode_ColorDodge:  mode = "Color Dodge"; break;
        case QPainter::CompositionMode_ColorBurn:  mode = "Color Burn"; break;
        case QPainter::CompositionMode_HardLight:  mode = "Hard Light"; break;
        case QPainter::CompositionMode_SoftLight:  mode = "Soft Light"; break;
        case QPainter::CompositionMode_Difference:  mode = "Difference"; break;
        case QPainter::CompositionMode_Exclusion:  mode = "Exclusion"; break;
        case QPainter::CompositionMode_DestinationOver:  mode = "Destination Over"; break;
        case QPainter::CompositionMode_Clear:  mode = "Clear"; break;
        case QPainter::CompositionMode_Source:  mode = "Source"; break;
        case QPainter::CompositionMode_Destination:  mode = "Destination"; break;
        case QPainter::CompositionMode_SourceIn:  mode = "Source-In"; break;
        case QPainter::CompositionMode_DestinationIn:  mode = "Destination-In"; break;
        case QPainter::CompositionMode_SourceOut:  mode = "Source Out"; break;
        case QPainter::CompositionMode_DestinationOut:  mode = "Destination Out"; break;
        case QPainter::CompositionMode_SourceAtop:  mode = "Source Atop"; break;
        case QPainter::CompositionMode_DestinationAtop:  mode = "Destination Atop"; break;
        case QPainter::CompositionMode_Xor:  mode = "XOR"; break;
        }
        nonSignalSetValue(ui->actorCompositionModeComboBox, mode);

    }// end Normal Actor

    if(actor->type == LABEL){   // Text-Actor
        TextActor *textActor = (TextActor *)actor;
        QFont font = textActor->font();

        nonSignalSetValue(ui->textLineEdit, textActor->toPlainText());

        ui->fontComboBox->blockSignals(true);
            ui->fontComboBox->setCurrentFont(font);
        ui->fontComboBox->blockSignals(false);

        nonSignalSetValue(ui->actorTextSizeSpinBox, font.pointSize());
        ui->setTextColorBtn->setStyleSheet("background-color: " + textActor->defaultTextColor().name());

        nonSignalSetValue(ui->textWidthDSpinBox, textActor->textWidth());

        QString al = "Center";
        switch(textActor->document()->defaultTextOption().alignment()){
        case Qt::AlignLeft: al = "Left"; break;
        default : case Qt::AlignHCenter: al = "Center"; break;
        case Qt::AlignRight: al = "Right"; break;
        case Qt::AlignJustify: al = "Justify"; break;
        }
        nonSignalSetValue(ui->textAlignComboBox, al);
    }// end Text-Actor
}

void QGameEditor::addActor(Actor *actor)
{
    ui->editorView->gameScene->addItem(actor);
    actor->setPos(ui->editorView->mapToScene(ui->editorView->viewport()->visibleRegion().boundingRect().x()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().width()/2,
                                             ui->editorView->viewport()->visibleRegion().boundingRect().y()
                                             + ui->editorView->viewport()->visibleRegion().boundingRect().height()/2));
    connect(actor, SIGNAL(positionChanged(Actor *)), this, SLOT(onActorPositionChange(Actor *)));
    connect(actor, SIGNAL(actorSelectionChanged(Actor *, bool)), this, SLOT(onActorSelectionChanged(Actor *, bool)));
    connect(actor, SIGNAL(snappingStateChanged(Actor*)), this, SLOT(copySnappingOfActor(Actor*)));
    connect(actor, SIGNAL(originChanged(Actor*)), this, SLOT(onActorOriginChanged(Actor*)));
    ui->editorView->gameScene->actors.append(actor);
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->insertItem(0,actor->name);
    ui->actorNameComboBox->blockSignals(false);

    deselectAllActors();
    actor->setSelected(true);
}

void QGameEditor::deselectAllActors()
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->blockSignals(true);
            selectedActors[i]->setSelected(false);
        selectedActors[i]->blockSignals(false);
    }
    ui->actorNameComboBox->blockSignals(true);
        ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
    ui->actorNameComboBox->blockSignals(false);
    selectedActors.clear();
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

void QGameEditor::nonSignalSetValue(QCheckBox *widget, bool value)
{
    widget->blockSignals(true);
        widget->setChecked(value);
    widget->blockSignals(false);
}

void QGameEditor::nonSignalSetValue(QLineEdit *widget, QString value)
{
    widget->blockSignals(true);
        widget->setText(value);
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


// TODO: clean up this function, pls.

// What it does is manage the properties tab, based on what actors are selected...
// if multiple are selected then only the shared properties are enabled and what is
// changed through the gui is then applied to all of them.
// and if one is selected then based on what type of actor it is the related
// groupboxes are activated and the other's are disabled.
// (NormalActor's animations,  TextActor's styling options  etc...)
void QGameEditor::onActorSelectionChanged(Actor *actor, bool selectionState)
{
    if(selectionState){
        selectedActors.append(actor);
    }else{
        selectedActors.removeOne(actor);
        if(selectedActors.size() < 2){
            ui->actorNameComboBox->blockSignals(true);
                ui->actorNameComboBox->removeItem(ui->actorNameComboBox->findText("Multiple Actors"));
            ui->actorNameComboBox->blockSignals(false);
        }
    }

    // Hide all non-shared groups
    ui->actorAnimationGroupBox->setVisible(false);
    ui->actorTextGroupBox->setVisible(false);

    if(!selectedActors.isEmpty()){ // if there are selected actors
        ui->actorPropertiesGroupBox->setVisible(true);
        // enable everything
        QList<QWidget*> list = ui->actorControlTab->findChildren<QWidget*>() ;
        foreach( QWidget* w, list ) {
           w->setEnabled( true ) ;
        }
        // then show the properties of last actor in selection list
        onActorLeftClicked(selectedActors.last());

        if(selectedActors.size() > 1){ // multiple selected
            if(ui->actorNameComboBox->findText("Multiple Actors") == -1){
                ui->actorNameComboBox->blockSignals(true);
                    ui->actorNameComboBox->insertItem(0, "Multiple Actors");
                    ui->actorNameComboBox->setCurrentIndex(0);
                ui->actorNameComboBox->blockSignals(false);
            }else ui->actorNameComboBox->setCurrentText("Multiple Actors");

            ui->actorAnimationGroupBox->setVisible(false);
        }
        else{   // Only One Actor is selected

            switch (selectedActors.last()->type) {
            case NORMAL:
                ui->actorAnimationGroupBox->setVisible(true);
                break;
            case VIEW:
                    // view stuff later??
                break;
            case LABEL:
                ui->actorTextGroupBox->setVisible(true);
                break;
            default:
                // sigh...
                ;
            }
        }

    }else{
        // if no currently selected actor.. disable everything
        ui->actorPropertiesGroupBox->setVisible(false);
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

void QGameEditor::onActorOriginChanged(Actor *actor)
{
    if(actor->name == ui->actorNameComboBox->currentText()){
        nonSignalSetValue(ui->actorOriginXSpinBox, actor->originPointItem->pos().x());
        nonSignalSetValue(ui->actorOriginYSpinBox, actor->originPointItem->pos().y());
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
    QVector<QString> actorNames;
    foreach (Actor * actor, ui->editorView->gameScene->actors) {
        actorNames.append(actor->name);
    }

    AddActorDialog dialog(this, actorNames);
    if(dialog.exec()){
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
            case LABEL:{
                TextActor * actor = new TextActor(actorName);
                addActor(actor);
                break;
            }
            default:{
                // Should never happen!! unknown or unimplementd somehow
                Helper::debugMSG("Error", "Unknown ActorType in function QGameEditor::on_actionAdd_Actor_triggered()");
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
        deselectAllActors();

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
        selectedActors[i]->update();
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

void QGameEditor::on_actorOriginXSpinBox_valueChanged(int xVal)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->originPointItem->setX(xVal);
    }
}

void QGameEditor::on_actorOriginYSpinBox_valueChanged(int yVal)
{
    for(int i = 0; i < selectedActors.size(); i++){
        selectedActors[i]->originPointItem->setY(yVal);
    }
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
        AnimationDialog dialog(projectPath, this, actor->animations);

        if(dialog.exec()){
            actor->addAnimation(dialog.animation);
            showPropertiesOfActor(actor);
        }
    }
}

void QGameEditor::on_actorAnimationStateCheckBox_toggled(bool checked)
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->changeAnimationDirection(checked ? FORWARD : STOPPED);
    }
}

void QGameEditor::on_animationFPSSpinBox_valueChanged(int fps)
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->changeAnimationFrameRate(fps);
    }
}

void QGameEditor::on_actorAnimationNameComboBox_currentIndexChanged(int index)
{
    // change to animation at index
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->changeAnimation(ui->actorAnimationNameComboBox->itemText(index), actor->animationState);
        showPropertiesOfActor(actor);
    }
}

void QGameEditor::on_antialiasingCheckBox_toggled(bool checked)
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->antialiasing = checked;
        actor->Actor::update();
    }
}

void QGameEditor::on_actorCompositionModeComboBox_currentIndexChanged(const QString &mode)
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->setCompositionMode(mode);
    }
}

void QGameEditor::on_addSequenceBtn_clicked()
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        AnimationSequenceDialog dialog(this, actor->animations);
        if(dialog.exec()){
            actor->addAnimation(dialog.finalAnimation);
            showPropertiesOfActor(actor);
        }
    }
}

void QGameEditor::on_editAnimationBtn_clicked()
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        Animation * anim = actor->animations[actor->getAnimationIndex(ui->actorAnimationNameComboBox->currentText())];

        if(anim->type == PURE_ANIMATION){
            AnimationDialog dialog(projectPath, this, actor->animations, true, anim);
            if(dialog.exec()){
                actor->editAnimation(dialog.animation, anim);
                showPropertiesOfActor(actor);
            }
        }
        else if(anim->type == SEQUENCE_ANIMATION){
            AnimationSequenceDialog dialog(this, actor->animations,true, anim);
            if(dialog.exec()){
                actor->editAnimation(dialog.finalAnimation, anim);
                showPropertiesOfActor(actor);
            }
        }
    }
}

void QGameEditor::on_removeAnimationBtn_clicked()
{
    if(selectedActors.last()->type == NORMAL){
        NormalActor *actor = (NormalActor *)selectedActors.last();
        actor->removeAnimation(ui->actorAnimationNameComboBox->currentText());
        showPropertiesOfActor(actor);
    }
}

void QGameEditor::on_setFontBtn_clicked()
{
    QFontDialog fd(this);
    bool *ok = new bool;
    QFont f = fd.getFont(ok, ((TextActor *)selectedActors.last())->font());
    ((TextActor *)selectedActors.last())->setFont(f);
    delete ok;
}

void QGameEditor::on_fontComboBox_currentFontChanged(const QFont &f)
{
    TextActor * actor = (TextActor*)selectedActors.last();
    QFont font = actor->font();
    font.setFamily(f.family());
    actor->setFont(font);
}

void QGameEditor::on_actorTextSizeSpinBox_valueChanged(int size)
{
    TextActor * actor = (TextActor*)selectedActors.last();
    QFont font = actor->font();
    font.setPointSize(size);
    actor->setFont(font);
}

void QGameEditor::on_textLineEdit_textChanged(const QString &text)
{
    TextActor * actor = (TextActor*)selectedActors.last();
    actor->setPlainText(text);
}

void QGameEditor::on_setTextColorBtn_clicked()
{
    TextActor * actor = (TextActor*)selectedActors.last();
    QColorDialog cd;
    QColor newColor = cd.getColor(actor->defaultTextColor(), this, "Select Text Color");

    if(newColor.isValid()){
        ui->setTextColorBtn->setStyleSheet("background-color: " + newColor.name());
        actor->setDefaultTextColor(newColor);
    }
}

void QGameEditor::on_textWidthDSpinBox_valueChanged(double wid)
{
    TextActor * actor = (TextActor*)selectedActors.last();
    actor->setTextWidth(wid);
}

void QGameEditor::on_textAlignComboBox_currentIndexChanged(int index)
{
    TextActor * actor = (TextActor*)selectedActors.last();
    switch (index) {
        case 0:
            actor->setAlignment(Qt::AlignLeft); break;
        default:
        case 1:
            actor->setAlignment(Qt::AlignHCenter); break;
        case 2:
            actor->setAlignment(Qt::AlignRight); break;
        case 3:
            actor->setAlignment(Qt::AlignJustify); break;
    }
}

void QGameEditor::on_actorTextGroupBox_toggled(bool checked)
{
    ui->actorTextGroupBox->setMaximumHeight(checked ? 32000 : 25);
}
