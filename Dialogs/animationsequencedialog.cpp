#include "animationsequencedialog.h"
#include "ui_animationsequencedialog.h"

AnimationSequenceDialog::AnimationSequenceDialog(QWidget *parent, QVector<Animation*> actorAnimations, bool edit, Animation *animToEdit) :
    QDialog(parent),
    ui(new Ui::AnimationSequenceDialog)
{
    ui->setupUi(this);
    setWindowTitle(edit ? "Edit Sequence Animation" : "Add Sequence Animation");

    for(int i = 0; i < actorAnimations.size(); i++){
        if(actorAnimations[i]->type == PURE_ANIMATION){
            baseAnimations.append(actorAnimations[i]);
        }

        if(edit && actorAnimations[i]->name == animToEdit->name) continue;
        names.append(actorAnimations[i]->name);
    }


    if(edit) ui->baseAnimationComboBox->blockSignals(true);
    for(int i = 0; i < baseAnimations.size(); i++){
        ui->baseAnimationComboBox->addItem(baseAnimations[i]->name);
    }
    if(edit) ui->baseAnimationComboBox->blockSignals(false);

    timeLine.setCurveShape(QTimeLine::LinearCurve);
    timeLine.setLoopCount(0);
    connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));

    if(edit){
        ui->baseAnimationComboBox->blockSignals(true);
            ui->baseAnimationComboBox->setCurrentText(animToEdit->baseAnimation->name);
        ui->baseAnimationComboBox->blockSignals(false);

        for(int i = 0; i < animToEdit->baseAnimation->frames.size(); i++){
            QListWidgetItem *item = new QListWidgetItem(QIcon(animToEdit->baseAnimation->getFramePixmap(i)->scaled(32,32)), QString::number(i));
            ui->baseAnimationFramesList->addItem(item);
        }
        ui->nameLineEdit->setText(animToEdit->name);
        ui->fpsSpinBox->setValue(animToEdit->frameRate);

        for(int i = 0; i < animToEdit->sequence.size(); i++){
            QListWidgetItem *item = new QListWidgetItem(QIcon(animToEdit->getFramePixmap(i)->scaled(32,32)), QString::number(animToEdit->sequence[i]));
            ui->sequenceFramesList->addItem(item);
        }
    }
}

AnimationSequenceDialog::~AnimationSequenceDialog()
{
    delete ui;
}

void AnimationSequenceDialog::on_CancelBtn_clicked()
{
    reject();
}

void AnimationSequenceDialog::on_OkBtn_clicked()
{
    QString animName = ui->nameLineEdit->text();

    if(animName.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Warning");
        mb.setText("Give a name for this animation.");
        mb.exec();
        return;
    }

    if(ui->sequenceFramesList->count() == 0){
        QMessageBox mb(this);
        mb.setWindowTitle("Warning");
        mb.setText("There are no sequence frames.");
        mb.exec();
        return;
    }

    // check for name uniqueness
    for(int i = 0 ; i < names.size(); i++){
        if(names[i] == animName){
            QMessageBox mb(this);
            mb.setWindowTitle("Warning");
            mb.setText("Invalid, Animation name already exists.");
            mb.exec();
            return;
        }
    }

    // Make final animation and accept the dialog
    QVector<int> seq;
    for(int i = 0; i < ui->sequenceFramesList->count(); i++){
        seq.append(ui->sequenceFramesList->item(i)->text().toInt());
    }
    finalAnimation = new Animation(animName,
                        baseAnimations[ui->baseAnimationComboBox->currentIndex()], seq,
                        ui->fpsSpinBox->value());
    accept();
}

void AnimationSequenceDialog::on_baseAnimationComboBox_currentIndexChanged(int index)
{
    if(ui->previewBtn->isChecked()) {
        on_previewBtn_clicked(false);
    }
    ui->baseAnimationFramesList->clear();
    ui->sequenceFramesList->clear();

    for(int i = 0; i < baseAnimations[index]->frames.size(); i++){
        QListWidgetItem *item = new QListWidgetItem(QIcon(baseAnimations[index]->getFramePixmap(i)->scaled(32,32)), QString::number(i));
        ui->baseAnimationFramesList->addItem(item);
    }

    ui->fpsSpinBox->setValue(baseAnimations[index]->frameRate);
}

void AnimationSequenceDialog::on_sequenceFramesList_itemDoubleClicked(QListWidgetItem *item)
{
    delete item;
}

void AnimationSequenceDialog::on_deleteBtn_clicked()
{
    // delete all selected frames
    foreach (QListWidgetItem * item, ui->sequenceFramesList->selectedItems()) {
        delete item;
    }
}

void AnimationSequenceDialog::setFrame(int index)
{
    if(index > ui->sequenceFramesList->count()-1 || index < 0) return;

    //if(ui->baseAnimationComboBox->count() == 0) return;
    int bIndex = ui->sequenceFramesList->item(index)->text().toInt();
    Animation * animation = baseAnimations[ui->baseAnimationComboBox->currentIndex()];
    if(bIndex > animation->getNumberOfFrames()-1 || bIndex < 0) return;


    // set
    QPixmap thumbnail = *animation->frames[bIndex]->pixmap;
    QString fileInfo;
    fileInfo += "Dimensions : " +
            QString::number(thumbnail.width()) + " x " +
            QString::number(thumbnail.height());
    ui->dimensionsLabel->setText(fileInfo);
    thumbnail = thumbnail.scaled(360,240,Qt::KeepAspectRatio);
    ui->imgLabel->setPixmap(thumbnail);
    ui->currentFrameLabel->setText("Frame " + QString::number(index+1) +
                                   " of " + QString::number(ui->sequenceFramesList->count()));
}

void AnimationSequenceDialog::startPlayingAnimation()
{
    timeLine.setDuration((double(ui->sequenceFramesList->count()) / ui->fpsSpinBox->value()) * 1000);
    timeLine.setFrameRange(0, ui->sequenceFramesList->count());

    timeLine.start(); /* this won't work if range is 0 to 1 so... */ setFrame(0);
}

void AnimationSequenceDialog::stopPlayingAnimation()
{
    timeLine.stop();
}

void AnimationSequenceDialog::on_previewBtn_clicked(bool checked)
{
    ui->sequenceFramesList->setDisabled(checked);
    ui->fpsSpinBox->setDisabled(checked);
    ui->deleteBtn->setDisabled(checked);

    if(checked && ui->sequenceFramesList->count() > 0){
        startPlayingAnimation();
        ui->previewBtn->setText("Stop");    
    }else{
        stopPlayingAnimation();
        ui->imgLabel->setText("Preview");
        ui->previewBtn->setText("Preview");
    }
}
