#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mappropertiesdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionMapProperties_triggered()
{
     MapPropertiesDialog(this).exec();
}

void MainWindow::on_actionGrid_triggered(bool checked)
{
     ui->tileWorkspace->setShowGrid(checked);
}
