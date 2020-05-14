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

private:
    Ui::QGameEditor *ui;
    QStringList stylesheets;
    Actor * currentlySelectedActor;
};

#endif // QGAMEEDITOR_H
