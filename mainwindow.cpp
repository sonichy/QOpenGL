#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardPaths"
#include <QSettings>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    path = "";
    ui->setupUi(this);
    readSettings();
    openGLWidget = new Tutorial06;
    setCentralWidget(openGLWidget);
    connect(ui->action_export_image,SIGNAL(triggered()),this,SLOT(export_image()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::export_image()
{
    QDialog *dialog = new QDialog(this);
    dialog->setFixedWidth(300);
    dialog->setWindowTitle("Export Image");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *label = new QLabel("Width");
    gridLayout->addWidget(label,0,0);
    QSpinBox *spin_width = new QSpinBox;
    spin_width->setRange(1, 160000);
    spin_width->setValue(openGLWidget->width());
    gridLayout->addWidget(spin_width,0,1,1,1,Qt::AlignLeft);
    label = new QLabel("Height");
    gridLayout->addWidget(label,1,0,1,1);
    QSpinBox *spin_height = new QSpinBox;
    spin_height->setRange(1, 16000);
    spin_height->setValue(openGLWidget->height());
    gridLayout->addWidget(spin_height,1,1,1,1,Qt::AlignLeft);
    label = new QLabel("Save Path");
    gridLayout->addWidget(label,2,0,1,1);
    QLineEdit *lineEdit_path = new QLineEdit;
    QAction *action_browse = new QAction;
    action_browse->setIcon(QIcon::fromTheme("folder"));
    lineEdit_path->addAction(action_browse, QLineEdit::TrailingPosition);
    lineEdit_path->setFixedWidth(200);
    if(path == "") path = "./preview.jpg";
    connect(action_browse, &QAction::triggered, [=](){
        path = QFileDialog::getSaveFileName(this, "Save Image", path, "Image File(*.jpg *.png *.bmp)");
    });
    lineEdit_path->setText(path);
    gridLayout->addWidget(lineEdit_path,2,1,1,1);
    vbox->addLayout(gridLayout);
    QPushButton *pushbutton_confirm = new QPushButton("Confirm");
    QPushButton *pushbutton_cancel = new QPushButton("Cancel");
    hbox = new QHBoxLayout;
    hbox->addStretch();
    hbox->addWidget(pushbutton_confirm);
    hbox->addWidget(pushbutton_cancel);
    hbox->addStretch();
    vbox->addLayout(hbox);
    dialog->setLayout(vbox);
    connect(pushbutton_confirm, SIGNAL(clicked()), dialog, SLOT(accept()));
    connect(pushbutton_cancel, SIGNAL(clicked()), dialog, SLOT(reject()));
    if(dialog->exec() == QDialog::Accepted){
        QSize size = openGLWidget->size();
        openGLWidget->resize(spin_width->value(),spin_height->value());
        QImage image = openGLWidget->grabFramebuffer();
        image.save(path,0,100);
        ui->statusBar->showMessage("export " + path, 5000);
        openGLWidget->resize(size);
    }
    dialog->close();
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}