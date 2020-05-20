#include "animationdialog.h"
#include "ui_animationdialog.h"

AnimationDialog::AnimationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationDialog)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{40,60});
}

AnimationDialog::~AnimationDialog()
{
    delete ui;
}
