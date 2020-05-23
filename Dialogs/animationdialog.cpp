#include "animationdialog.h"
#include "ui_animationdialog.h"

AnimationDialog::AnimationDialog(QString projectPath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationDialog)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{40,60});
    dataPath = projectPath;
}

AnimationDialog::~AnimationDialog()
{
    delete ui;
}

void AnimationDialog::on_OkBtn_clicked()
{
    if(path.isEmpty()){reject(); return;}   // or maybe ask user for path

    // create animation & and Accept dialog
    Animation * anim = new Animation(path, dataPath, (AnimationFileType) ui->typeComboBox->currentIndex(),
                                     ui->hFramesSpinBox->value(), ui->vFramesSpinBox->value(),
                                     ui->fpsSpinBox->value());
    animation = anim;
    accept();
}

void AnimationDialog::on_browseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
          "Open Image", QDir::currentPath(), "Image File (*.png *.bmp *.jpg *.jpe *.jpeg *.gif *.tiff *.tif *.iff *.xpm *.xcf *.pcx *.jfif)");
    path = filePath;
    QDir::setCurrent(path.left(path.lastIndexOf("/")));
    QString fileName = path.right(path.length() - path.lastIndexOf("/") - 1);
    fileName = fileName.left(fileName.indexOf("."));
    ui->nameLineEdit->setText(fileName);

    // set Image
    if(ui->typeComboBox->currentText() == "Single File"){
        QPixmap preview = QPixmap(filePath);
        ui->dimensionsLabel->setText("Dimensions : " +
                                       QString::number(preview.width()) + " x " +
                                       QString::number(preview.height()));
        preview = preview.scaled(360,240,Qt::KeepAspectRatio);
        ui->imgLabel->setPixmap(preview);
    }
}
