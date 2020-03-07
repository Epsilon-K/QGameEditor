#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include "configdata.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(SceneProperties* scnProps, Preferences *pref, QWidget *parent = nullptr);
    ~ConfigDialog();
    SceneProperties *sceneProps;
    Preferences *preferences;
    QColor scnBGColor;

public slots:
    void on_Accepted();

private slots:
    void on_winSizeComboBox_currentTextChanged(const QString &arg1);

    void on_sceneBGColorBtn_clicked();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
