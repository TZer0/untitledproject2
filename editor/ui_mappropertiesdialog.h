/********************************************************************************
** Form generated from reading ui file 'mappropertiesdialog.ui'
**
** Created: Sun 8. Nov 20:24:16 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAPPROPERTIESDIALOG_H
#define UI_MAPPROPERTIESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MapPropertiesDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txt_mapname;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *lbl_filename;
    QPushButton *btn_browse;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MapPropertiesDialog)
    {
        if (MapPropertiesDialog->objectName().isEmpty())
            MapPropertiesDialog->setObjectName(QString::fromUtf8("MapPropertiesDialog"));
        MapPropertiesDialog->resize(400, 275);
        verticalLayout_2 = new QVBoxLayout(MapPropertiesDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(MapPropertiesDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        txt_mapname = new QLineEdit(groupBox);
        txt_mapname->setObjectName(QString::fromUtf8("txt_mapname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txt_mapname);

        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setMargin(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbl_filename = new QLabel(frame);
        lbl_filename->setObjectName(QString::fromUtf8("lbl_filename"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbl_filename->sizePolicy().hasHeightForWidth());
        lbl_filename->setSizePolicy(sizePolicy1);
        lbl_filename->setFrameShape(QFrame::Panel);
        lbl_filename->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(lbl_filename);

        btn_browse = new QPushButton(frame);
        btn_browse->setObjectName(QString::fromUtf8("btn_browse"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_browse->sizePolicy().hasHeightForWidth());
        btn_browse->setSizePolicy(sizePolicy2);
        btn_browse->setMinimumSize(QSize(0, 0));
        btn_browse->setMaximumSize(QSize(25, 16777215));
        btn_browse->setCheckable(false);
        btn_browse->setChecked(false);
        btn_browse->setAutoRepeat(false);
        btn_browse->setFlat(false);

        horizontalLayout->addWidget(btn_browse);


        formLayout->setWidget(3, QFormLayout::FieldRole, frame);


        verticalLayout_2->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(MapPropertiesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(MapPropertiesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MapPropertiesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MapPropertiesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MapPropertiesDialog);
    } // setupUi

    void retranslateUi(QDialog *MapPropertiesDialog)
    {
        MapPropertiesDialog->setWindowTitle(QApplication::translate("MapPropertiesDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MapPropertiesDialog", "Map settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MapPropertiesDialog", "Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MapPropertiesDialog", "Background:", 0, QApplication::UnicodeUTF8));
        lbl_filename->setText(QString());
        btn_browse->setText(QApplication::translate("MapPropertiesDialog", "...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MapPropertiesDialog);
    } // retranslateUi

};

namespace Ui {
    class MapPropertiesDialog: public Ui_MapPropertiesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPROPERTIESDIALOG_H
