#include "animationdialog.h"
#include "ui_animationdialog.h"

AnimationDialog::AnimationDialog(QString projectPath, QWidget *parent, QVector<Animation *> &actorAnimations) :
    QDialog(parent),
    ui(new Ui::AnimationDialog)
{
    ui->setupUi(this);
    setWindowTitle("Add Animation");

    foreach (Animation *anim, actorAnimations) {
        names.append(anim->name);
    }

    dataPath = projectPath;
    tempAnimation = nullptr;
    localTimeLine.setCurveShape(QTimeLine::LinearCurve);
    localTimeLine.setLoopCount(0);
    connect(&localTimeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
}

AnimationDialog::~AnimationDialog()
{
    delete ui;
    delete tempAnimation;
}

void AnimationDialog::startPlayingAnimation()
{
    if(tempAnimation == nullptr) return;
    localTimeLine.stop();
    localTimeLine.setDuration((double(tempAnimation->frames.size()) / tempAnimation->frameRate) * 1000);
    localTimeLine.setFrameRange(0, tempAnimation->frames.size());

    localTimeLine.start(); /* this won't work if range is 0 to 1 so... */ setFrame(0);
}

void AnimationDialog::createTempAnimation()
{
    if(path.isEmpty() || ui->nameLineEdit->text().isEmpty()) return;
    // Create temporary animation
    if(tempAnimation != nullptr) delete tempAnimation;
    tempAnimation = new Animation(ui->nameLineEdit->text(), path, dataPath, (AnimationFileType) ui->typeComboBox->currentIndex(),
                                     ui->hFramesSpinBox->value(), ui->vFramesSpinBox->value(),
                                     ui->fpsSpinBox->value(), ui->alphaPixelCheckBox->isChecked(), true);
    startPlayingAnimation();
}

void AnimationDialog::setFrame(int frameIndex)
{
    if(tempAnimation == nullptr) return;
    if(frameIndex > tempAnimation->frames.size()-1 || frameIndex < 0) return;

    QPixmap thumbnail = *tempAnimation->frames[frameIndex]->pixmap;
    QString fileInfo;
    fileInfo += "Dimensions : " +
            QString::number(thumbnail.width()) + " x " +
            QString::number(thumbnail.height());
    ui->dimensionsLabel->setText(fileInfo);
    thumbnail = thumbnail.scaled(360,240,Qt::KeepAspectRatio);
    ui->imgLabel->setPixmap(thumbnail);
    ui->currentFrameLabel->setText("Frame " + QString::number(frameIndex+1) +
                                   " of " + QString::number(tempAnimation->frames.size()));
}

void AnimationDialog::on_OkBtn_clicked()
{
    QString animName = ui->nameLineEdit->text();

    if(path.isEmpty() || animName.isEmpty()){
        QMessageBox mb(this);
        mb.setWindowTitle("Warning");
        if(animName.isEmpty())
            mb.setText("Give a name for this animation.");
        else mb.setText("Browse for a file.");
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

    // create final animation & and Accept dialog
    Animation * anim = new Animation(animName, path, dataPath, (AnimationFileType) ui->typeComboBox->currentIndex(),
                                     ui->hFramesSpinBox->value(), ui->vFramesSpinBox->value(),
                                     ui->fpsSpinBox->value(), ui->alphaPixelCheckBox->isChecked(), false);
    animation = anim;
    accept();
}

void AnimationDialog::on_browseButton_clicked()
{
    // NOTE : Qt doesn't actually support all the image formats listed below. but it can read most of them.
    QString filePath = QFileDialog::getOpenFileName(this,
          "Open Image", QDir::currentPath(), "Image File (*.png *.bmp *.jpg *.jpe *.jpeg *.gif *.tiff *.tif *.iff *.xpm *.xcf *.pcx *.jfif)");
    if(filePath.isEmpty())
        return;

    path = filePath;
    QDir::setCurrent(path.left(path.lastIndexOf("/")));
    QString fileName = Helper::getFileNameWithExtension(filePath);
    fileName = Helper::getNameWithOutExtension(fileName);
    ui->nameLineEdit->setText(fileName);

    createTempAnimation();
}

void AnimationDialog::on_alphaPixelCheckBox_toggled(bool checked)
{
    createTempAnimation();
}

void AnimationDialog::on_typeComboBox_currentIndexChanged(const QString &txt)
{
    if(txt == "Single File"){
        ui->hFramesSpinBox->setEnabled(true);
        ui->vFramesSpinBox->setEnabled(true);
    }else if(txt == "Multiple Files"){
        ui->hFramesSpinBox->setEnabled(false);
        ui->vFramesSpinBox->setEnabled(false);
    }
    createTempAnimation();
}

void AnimationDialog::on_hFramesSpinBox_valueChanged(int arg1)
{
    createTempAnimation();
}

void AnimationDialog::on_vFramesSpinBox_valueChanged(int arg1)
{
    createTempAnimation();
}

void AnimationDialog::on_fpsSpinBox_valueChanged(int fps)
{
    if(tempAnimation == nullptr) return;

    tempAnimation->frameRate = fps;
    QTimeLine::State originalState = localTimeLine.state();
    if(originalState == QTimeLine::Running) localTimeLine.setPaused(true);
    localTimeLine.setDuration((double(tempAnimation->frames.size()) / tempAnimation->frameRate) * 1000);
    localTimeLine.setFrameRange(0, tempAnimation->frames.size());
    if(originalState == QTimeLine::Running) localTimeLine.setPaused(false);
}
