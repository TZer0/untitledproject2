#include "mappropertiesdialog.h"
#include "ui_mappropertiesdialog.h"
#include <QFileDialog>

MapPropertiesDialog::MapPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::MapPropertiesDialog)
{
    m_ui->setupUi(this);
}

MapPropertiesDialog::~MapPropertiesDialog()
{
    delete m_ui;
}

void MapPropertiesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MapPropertiesDialog::on_btn_browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                 tr("Images (*.png *.bmp *.jpg)"));

    if (fileName != NULL ){
        m_ui->lbl_filename->setText(fileName);
    }

}
