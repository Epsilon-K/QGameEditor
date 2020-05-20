#ifndef ANIMATIONDIALOG_H
#define ANIMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AnimationDialog;
}

class AnimationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationDialog(QWidget *parent = nullptr);
    ~AnimationDialog();

private:
    Ui::AnimationDialog *ui;
};

#endif // ANIMATIONDIALOG_H
