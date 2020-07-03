#ifndef ANIMATIONSEQUENCEDIALOG_H
#define ANIMATIONSEQUENCEDIALOG_H

#include <QDialog>
#include <Components/animation.h>
#include <QListWidgetItem>
#include <QTabWidget>
#include <QTimeLine>
#include <QMessageBox>

namespace Ui {
class AnimationSequenceDialog;
}

class AnimationSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationSequenceDialog(QWidget *parent, QVector<Animation *> actorAnimations);
    ~AnimationSequenceDialog();

    QVector<Animation*> baseAnimations;
    QVector<QString> names;
    QTimeLine timeLine;
    void startPlayingAnimation();
    void stopPlayingAnimation();
    Animation * finalAnimation;

private slots:
    void on_CancelBtn_clicked();

    void on_OkBtn_clicked();

    void on_baseAnimationComboBox_currentIndexChanged(int index);

    void on_sequenceFramesList_itemDoubleClicked(QListWidgetItem *item);

    void on_deleteBtn_clicked();

    void setFrame(int index);

    void on_previewBtn_clicked(bool checked);

private:
    Ui::AnimationSequenceDialog *ui;
};

#endif // ANIMATIONSEQUENCEDIALOG_H
