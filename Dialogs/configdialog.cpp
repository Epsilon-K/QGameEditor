#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(SceneProperties *scnProps, Preferences *pref, QWidget *parent):
    QDialog(parent),
    sceneProps(scnProps),
    preferences(pref),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(on_Accepted()));

    // view SceneProps on UI
    ui->winWidthSpinBox->setValue(sceneProps->windowSize.width());
    ui->winHeightSpinBox->setValue(sceneProps->windowSize.height());
    ui->winModeComboBox->setCurrentIndex(sceneProps->windowMode);
    ui->winTitleLineEdit->setText(sceneProps->windowTitle);
    ui->iconFilelabel->setText(sceneProps->windowIcon);
    ui->frameRateDSpinBox->setValue(sceneProps->frameRate);
    ui->showMouseCheckBox->setChecked(sceneProps->showMouse);
    ui->escapeCheckBox->setChecked(sceneProps->exitWithESC);
    ui->suspendCheckBox->setChecked(sceneProps->suspendWithoutFocus);
    ui->motionCompCheckBox->setChecked(sceneProps->motionCompensation);
    scnBGColor = sceneProps->backgroundColor;
    ui->sceneBGColorBtn->setStyleSheet("background-color:" + scnBGColor.name() + ";");
    ui->audioFormatsComboBox->setCurrentIndex(sceneProps->audioFormat);
    ui->audioChannelsComboBox->setCurrentIndex(sceneProps->audioChannels);
    ui->maxAudioSpinBox->setValue(sceneProps->maxNumOfSimultaneousSounds);

    ui->sceneWidthSpinBox->setValue(sceneProps->sceneSize.width());
    ui->sceneHeightSpinBox->setValue(sceneProps->sceneSize.height());
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_Accepted()
{
    // copy scene props
    sceneProps->windowSize = QSize(ui->winWidthSpinBox->value(), ui->winHeightSpinBox->value());
    sceneProps->windowMode = ui->winModeComboBox->currentText() == "Window" ? WindowModes::Windowed : WindowModes::FullScreen;
    sceneProps->windowTitle = ui->winTitleLineEdit->text();
    sceneProps->windowIcon = ui->iconFilelabel->text();
    sceneProps->frameRate = ui->frameRateDSpinBox->value();
    sceneProps->showMouse = ui->showMouseCheckBox->isChecked();
    sceneProps->exitWithESC = ui->escapeCheckBox->isChecked();
    sceneProps->suspendWithoutFocus = ui->suspendCheckBox->isChecked();
    sceneProps->motionCompensation = ui->motionCompCheckBox->isChecked();
    sceneProps->backgroundColor = scnBGColor;
    QString af = ui->audioFormatsComboBox->currentText();
    if(af == "44100 Hz") sceneProps->audioFormat = AudioFormats::_44100Hz;
    else if(af == "22050 Hz") sceneProps->audioFormat = AudioFormats::_22050Hz;
    else if(af == "11050 Hz") sceneProps->audioFormat = AudioFormats::_11050Hz;
    sceneProps->audioChannels = ui->audioChannelsComboBox->currentText() == "Stereo" ? AudioChannels::Stereo : AudioChannels::Mono;
    sceneProps->maxNumOfSimultaneousSounds = ui->maxAudioSpinBox->value();

    sceneProps->sceneSize = QSize(ui->sceneWidthSpinBox->value(), ui->sceneHeightSpinBox->value());
}

void ConfigDialog::on_winSizeComboBox_currentTextChanged(const QString &arg1)
{
    QStringList size = arg1.split(" x ", QString::SkipEmptyParts);
    ui->winWidthSpinBox->setValue(size[0].toInt());
    ui->winHeightSpinBox->setValue(size[1].toInt());
}

void ConfigDialog::on_sceneBGColorBtn_clicked()
{
    QColor newColor = QColorDialog::getColor(scnBGColor, this, "Select scene background color");
    if(newColor.isValid()){
        scnBGColor = newColor;
        ui->sceneBGColorBtn->setStyleSheet("background-color:" + scnBGColor.name() + ";");
    }
}
