#ifndef QGAMEEDITOR_H
#define QGAMEEDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include "editorview.h"
#include "Dialogs/configdialog.h"
#include "Dialogs/addactordialog.h"
#include "Dialogs/animationdialog.h"
#include "Dialogs/animationsequencedialog.h"
#include "Dialogs/settextdialog.h"

#include "Dialogs/createactoreventdialog.h"
#include "Dialogs/collisioneventdialog.h"

#include <QSpinBox>
#include <QSlider>
#include <QComboBox>
#include <QFontDialog>

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
    void deselectAllActors();

    // ------------
    void nonSignalSetValue(QSpinBox *widget, int value);
    void nonSignalSetValue(QDoubleSpinBox *widget, double value);
    void nonSignalSetValue(QSlider *widget, int value);
    void nonSignalSetValue(QComboBox *widget, QString value);
    void nonSignalSetValue(QCheckBox *widget, bool value);
    void nonSignalSetValue(QLineEdit * widget, QString value);

public slots:
    void on_editorView_mouse_moved(QPoint point);
    void on_editorView_zoom_changed();
    void onActorLeftClicked(Actor * actor);
    void onActorPositionChange(Actor * actor);
    void onActorSelectionChanged(Actor *actor, bool selectionState);
    void copySnappingOfActor(Actor* actor);
    void onActorOriginChanged(Actor *actor);

    // Event Dialogs Slots
    void createActorDialog();
    void collisionDialog();

private slots:
    void on_actionExit_triggered();

    void on_comboBoxZoomLevel_activated(const QString &arg1);

    void on_actionConfig_triggered();

    void on_actionAdd_Actor_triggered();        // ADD ACTOR <<<<<<<<<<<

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

    void on_actorWidthSpinBox_valueChanged(int arg1);

    void on_actorHeightSpinBox_valueChanged(int arg1);

    void on_actorOriginXSpinBox_valueChanged(int xVal);

    void on_actorOriginYSpinBox_valueChanged(int yVal);

    void on_actionShow_Hidden_Actors_triggered();

    void on_actorAnimationGroupBox_toggled(bool checked);

    void on_actorPropertiesGroupBox_toggled(bool arg1);

    void on_addAnimationBtn_clicked();

    void on_actorAnimationStateCheckBox_toggled(bool checked);

    void on_animationFPSSpinBox_valueChanged(int arg1);

    void on_actorAnimationNameComboBox_currentIndexChanged(int index);

    void on_antialiasingCheckBox_toggled(bool checked);

    void on_actorCompositionModeComboBox_currentIndexChanged(const QString &mode);

    void on_addSequenceBtn_clicked();

    void on_editAnimationBtn_clicked();

    void on_removeAnimationBtn_clicked();

    void on_setFontBtn_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_actorTextSizeSpinBox_valueChanged(int arg1);

    void on_textLineEdit_textChanged(const QString &text);

    void on_setTextColorBtn_clicked();

    void on_textWidthDSpinBox_valueChanged(double arg1);

    void on_textAlignComboBox_currentIndexChanged(int index);

    void on_actorTextGroupBox_toggled(bool checked);

    void on_animationFrameSpinBox_valueChanged(int index);

    void on_setTextBtn_clicked();

    void on_actorEventsGroupBox_toggled(bool arg1);

    void on_addEventBtn_clicked();

private:
    Ui::QGameEditor *ui;
    QStringList stylesheets;
    QString projectPath{QCoreApplication::applicationDirPath()};
    QVector<Actor *> selectedActors;
    QGraphicsLineItem *snappingGuideLine;
};

#endif // QGAMEEDITOR_H
