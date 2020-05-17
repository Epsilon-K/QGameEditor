#ifndef QGAMEEDITOR_H
#define QGAMEEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "editorview.h"
#include "Dialogs/configdialog.h"
#include "Dialogs/addactordialog.h"

namespace Ui {
class QGameEditor;
}

class QGameEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QGameEditor(QWidget *parent = nullptr);
    ~QGameEditor();
    void loadStylesheets();
    void showPropertiesOfActor(Actor * actor);
    void addActor(Actor * actor);

public slots:
    void on_editorView_mouse_moved(QPoint point);
    void on_editorView_zoom_changed();
    void onActorLeftClicked(Actor * actor);
    void onActorPositionChange(Actor * actor);
    void onActorSelectionChanged(Actor *actor, bool state);

private slots:
    void on_actionExit_triggered();

    void on_comboBoxZoomLevel_activated(const QString &arg1);

    void on_actionConfig_triggered();

    void on_actionAdd_Actor_triggered();

    void on_snappingBtn_toggled(bool checked);


    void on_actorXSpinBox_valueChanged(int arg1);

    void on_actorYSpinBox_valueChanged(int arg1);

    void on_actorNameComboBox_currentIndexChanged(int index);

    void on_actorTintBtn_clicked();

    void on_actorTintStrengthSlider_valueChanged(int value);

    void on_actorXScaleDoubleSpinBox_valueChanged(double xs);

    void on_actorYScaleDoubleSpinBox_valueChanged(double xy);

    void on_actorRotationSlider_valueChanged(int value);

    void on_actorTranspSlider_valueChanged(int value);

    void on_actorTranspDoubleSpinBox_valueChanged(double arg1);

    void on_actorZDepthSlider_valueChanged(int value);

    void on_actorZDepthDoubleSpinBox_valueChanged(double arg1);

private:
    Ui::QGameEditor *ui;
    QStringList stylesheets;
    QVector<Actor *> selectedActors;
};

#endif // QGAMEEDITOR_H
