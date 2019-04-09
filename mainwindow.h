#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qgl_tutorial06.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Tutorial06 *openGLWidget;
    void readSettings();
    QString path;

private slots:
    void export_image();

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H