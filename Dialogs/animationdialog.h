#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "Components/animation.h"

#include <QDebug>

namespace Ui {
class AnimationDialog;
}

class AnimationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationDialog(QString projectPath, QWidget *parent = nullptr);
    ~AnimationDialog();
    Animation * animation;
    QString path, dataPath;

private slots:
    void on_OkBtn_clicked();

    void on_browseButton_clicked();

private:
    Ui::AnimationDialog *ui;
};

#endif // ANIMATIONDIALOG_H
