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

public slots:
    void on_editorView_mouse_moved(QPoint point);
    void on_editorView_zoom_changed();

private slots:
    void on_actionExit_triggered();

    void on_comboBoxZoomLevel_activated(const QString &arg1);

    void on_actionConfig_triggered();

    void on_actionAdd_Actor_triggered();

private:
    Ui::QGameEditor *ui;
    QStringList stylesheets;
};

#endif // QGAMEEDITOR_H
