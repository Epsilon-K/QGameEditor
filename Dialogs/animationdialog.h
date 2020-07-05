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
    explicit AnimationDialog(QString projectPath, QWidget *parent, QVector<Animation *> &actorAnimations);
    ~AnimationDialog();
    QVector<QString> names;
    Animation * animation;
    QString path, dataPath;
    bool transpPix{false};

    QTimeLine localTimeLine;
    Animation * tempAnimation;
    void startPlayingAnimation();
    void createTempAnimation();

public slots:
    void setFrame(int frameIndex);

private slots:
    void on_OkBtn_clicked();

    void on_browseButton_clicked();

    void on_alphaPixelCheckBox_toggled(bool checked);

    void on_typeComboBox_currentIndexChanged(const QString &txt);

    void on_hFramesSpinBox_valueChanged(int arg1);

    void on_vFramesSpinBox_valueChanged(int arg1);

    void on_fpsSpinBox_valueChanged(int fps);

private:
    Ui::AnimationDialog *ui;
};

#endif // ANIMATIONDIALOG_H
