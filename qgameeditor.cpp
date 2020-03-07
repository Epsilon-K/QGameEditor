#include "qgameeditor.h"
#include "ui_qgameeditor.h"

QGameEditor::QGameEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QGameEditor)
{
    ui->setupUi(this);

    // GUI Stuff for now... later on this should be saved as a preference!
    showMaximized();
    loadStylesheets();
    QFont f = font();
    setStyleSheet(stylesheets[0]);
    ui->menuBar->setFont(f);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    QTimer::singleShot(30,ui->editorView, SLOT(centering()));

    // Connections
    connect(ui->editorView, SIGNAL(signalMouseMoveEvent(QPoint)), this, SLOT(on_editorView_mouse_moved(QPoint)));
    connect(ui->editorView, SIGNAL(signalZoomLevelChanged()), this, SLOT(on_editorView_zoom_changed()));

    // Zoom levels
    ui->comboBoxZoomLevel->addItem("10%");
    ui->comboBoxZoomLevel->addItem("25%");
    ui->comboBoxZoomLevel->addItem("50%");
    ui->comboBoxZoomLevel->addItem("75%");
    ui->comboBoxZoomLevel->addItem("100%");
    ui->comboBoxZoomLevel->addItem("200%");
    ui->comboBoxZoomLevel->addItem("400%");
    ui->comboBoxZoomLevel->addItem("800%");
    ui->comboBoxZoomLevel->addItem("1600%");
    ui->comboBoxZoomLevel->addItem("3000%");
}

QGameEditor::~QGameEditor()
{
    delete ui;
}

void QGameEditor::loadStylesheets()
{
    // later on, scan the :/Resources/StyleSheets folder and load all of them

    QFile file(":/Resources/StyleSheets/darkorange.stylesheet");
    //QFile file(":/Resources/StyleSheets/ClassicGE.stylesheet");   // not complete
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // TODO: Error Message!
        stylesheets.append("");
        return;
    }

    QTextStream in(&file);
    stylesheets.append(in.readAll());
}

void QGameEditor::on_editorView_mouse_moved(QPoint point)
{
    QString str = "Screen(" + QString::number(point.x())
            + ", " + QString::number(point.y()) + ")";
    QPoint sp = ui->editorView->mapToScene(point).toPoint();
    str += "  Game(" + QString::number(sp.x()) + ", " + QString::number(sp.y()) + ")";
    ui->viewInfoLabel->setText(str);
}

void QGameEditor::on_editorView_zoom_changed()
{
    QString str = QString::number(int(ui->editorView->scaleLevel*100)) + "%";
    ui->comboBoxZoomLevel->setItemText(0, str);
    ui->comboBoxZoomLevel->setCurrentIndex(0);
}

void QGameEditor::on_actionExit_triggered()
{
    // TODO: confirmation to exit program
    close();
}

void QGameEditor::on_comboBoxZoomLevel_activated(const QString &arg1)
{
    QString s = arg1;
    s.remove(s.length()-1, 1);
    ui->editorView->scaleLevel = s.toDouble()/100;
    ui->editorView->updateScale();
}

void QGameEditor::on_actionConfig_triggered()
{
    ConfigDialog * configDialog = new ConfigDialog(ui->editorView->gameScene->properties,
                                 ui->editorView->gameScene->preferences, this);
    if(configDialog->exec() == QDialog::Accepted){
        ui->editorView->updateSceneConfigurations();
    }
    delete configDialog;
}

void QGameEditor::on_actionAdd_Actor_triggered()
{
    // Add Actor
    AddActorDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        //....
    }
}
