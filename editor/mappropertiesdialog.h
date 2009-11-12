#ifndef MAPPROPERTIESDIALOG_H
#define MAPPROPERTIESDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class MapPropertiesDialog;
}

class MapPropertiesDialog : public QDialog {
    Q_OBJECT
public:
    MapPropertiesDialog(QWidget *parent = 0);
    ~MapPropertiesDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MapPropertiesDialog *m_ui;

private slots:
    void on_btn_browse_clicked();
};

#endif // MAPPROPERTIESDIALOG_H
