/********************************************************************************
** Form generated from reading UI file 'ParameterEstimationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERESTIMATIONDIALOG_H
#define UI_PARAMETERESTIMATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParameterEstimationDialog
{
public:
    QLabel *label_11;
    QLineEdit *lineEditFovMax;
    QLineEdit *lineEditYrotMin;
    QLineEdit *lineEditXrotMin;
    QLabel *label_13;
    QLineEdit *lineEditYrotMax;
    QLineEdit *lineEditXrotMax;
    QLabel *label_14;
    QLabel *label_10;
    QLineEdit *lineEditCameraDistance;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *lineEditFovMin;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonOK;
    QCheckBox *checkBoxCentering;
    QLabel *label;
    QLineEdit *lineEditCGADirectory;
    QPushButton *pushButtonCGADirectory;
    QLabel *label_2;
    QLineEdit *lineEditOutputDirectory;
    QPushButton *pushButtonOutputDirectory;
    QLabel *label_3;
    QLineEdit *lineEditTestDataDirectory;
    QPushButton *pushButtonTestDataDirectory;
    QLabel *label_4;
    QLineEdit *lineEditClassificationDirectory;
    QPushButton *pushButtonClassificationDirectory;
    QPushButton *pushButtonRegressionDirectory;
    QLabel *label_5;
    QLineEdit *lineEditRegressionDirectory;

    void setupUi(QDialog *ParameterEstimationDialog)
    {
        if (ParameterEstimationDialog->objectName().isEmpty())
            ParameterEstimationDialog->setObjectName(QStringLiteral("ParameterEstimationDialog"));
        ParameterEstimationDialog->resize(621, 364);
        label_11 = new QLabel(ParameterEstimationDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(183, 280, 16, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditFovMax = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMax->setObjectName(QStringLiteral("lineEditFovMax"));
        lineEditFovMax->setGeometry(QRect(210, 280, 61, 20));
        lineEditYrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMin->setObjectName(QStringLiteral("lineEditYrotMin"));
        lineEditYrotMin->setGeometry(QRect(120, 250, 61, 20));
        lineEditXrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMin->setObjectName(QStringLiteral("lineEditXrotMin"));
        lineEditXrotMin->setGeometry(QRect(120, 220, 61, 20));
        label_13 = new QLabel(ParameterEstimationDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(183, 220, 16, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditYrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMax->setObjectName(QStringLiteral("lineEditYrotMax"));
        lineEditYrotMax->setGeometry(QRect(210, 250, 61, 20));
        lineEditXrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMax->setObjectName(QStringLiteral("lineEditXrotMax"));
        lineEditXrotMax->setGeometry(QRect(210, 220, 61, 20));
        label_14 = new QLabel(ParameterEstimationDialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(183, 250, 16, 20));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(ParameterEstimationDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(40, 280, 71, 16));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditCameraDistance = new QLineEdit(ParameterEstimationDialog);
        lineEditCameraDistance->setObjectName(QStringLiteral("lineEditCameraDistance"));
        lineEditCameraDistance->setGeometry(QRect(120, 190, 61, 20));
        label_7 = new QLabel(ParameterEstimationDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 190, 91, 20));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(ParameterEstimationDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 220, 71, 16));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(ParameterEstimationDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 250, 71, 16));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditFovMin = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMin->setObjectName(QStringLiteral("lineEditFovMin"));
        lineEditFovMin->setGeometry(QRect(120, 280, 61, 20));
        pushButtonCancel = new QPushButton(ParameterEstimationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(510, 320, 91, 31));
        pushButtonOK = new QPushButton(ParameterEstimationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(410, 320, 91, 31));
        checkBoxCentering = new QCheckBox(ParameterEstimationDialog);
        checkBoxCentering->setObjectName(QStringLiteral("checkBoxCentering"));
        checkBoxCentering->setGeometry(QRect(290, 190, 91, 17));
        label = new QLabel(ParameterEstimationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 101, 21));
        lineEditCGADirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditCGADirectory->setObjectName(QStringLiteral("lineEditCGADirectory"));
        lineEditCGADirectory->setGeometry(QRect(140, 20, 431, 20));
        pushButtonCGADirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonCGADirectory->setObjectName(QStringLiteral("pushButtonCGADirectory"));
        pushButtonCGADirectory->setGeometry(QRect(580, 20, 31, 23));
        label_2 = new QLabel(ParameterEstimationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 140, 101, 21));
        lineEditOutputDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(140, 140, 431, 20));
        pushButtonOutputDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(580, 140, 31, 23));
        label_3 = new QLabel(ParameterEstimationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 50, 101, 21));
        lineEditTestDataDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditTestDataDirectory->setObjectName(QStringLiteral("lineEditTestDataDirectory"));
        lineEditTestDataDirectory->setGeometry(QRect(140, 50, 431, 20));
        pushButtonTestDataDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonTestDataDirectory->setObjectName(QStringLiteral("pushButtonTestDataDirectory"));
        pushButtonTestDataDirectory->setGeometry(QRect(580, 50, 31, 23));
        label_4 = new QLabel(ParameterEstimationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 80, 121, 21));
        lineEditClassificationDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditClassificationDirectory->setObjectName(QStringLiteral("lineEditClassificationDirectory"));
        lineEditClassificationDirectory->setGeometry(QRect(140, 80, 431, 20));
        pushButtonClassificationDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonClassificationDirectory->setObjectName(QStringLiteral("pushButtonClassificationDirectory"));
        pushButtonClassificationDirectory->setGeometry(QRect(580, 80, 31, 23));
        pushButtonRegressionDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonRegressionDirectory->setObjectName(QStringLiteral("pushButtonRegressionDirectory"));
        pushButtonRegressionDirectory->setGeometry(QRect(580, 110, 31, 23));
        label_5 = new QLabel(ParameterEstimationDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 110, 111, 21));
        lineEditRegressionDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditRegressionDirectory->setObjectName(QStringLiteral("lineEditRegressionDirectory"));
        lineEditRegressionDirectory->setGeometry(QRect(140, 110, 431, 20));
        QWidget::setTabOrder(checkBoxCentering, lineEditCameraDistance);
        QWidget::setTabOrder(lineEditCameraDistance, lineEditXrotMin);
        QWidget::setTabOrder(lineEditXrotMin, lineEditXrotMax);
        QWidget::setTabOrder(lineEditXrotMax, lineEditYrotMin);
        QWidget::setTabOrder(lineEditYrotMin, lineEditYrotMax);
        QWidget::setTabOrder(lineEditYrotMax, lineEditFovMin);
        QWidget::setTabOrder(lineEditFovMin, lineEditFovMax);
        QWidget::setTabOrder(lineEditFovMax, pushButtonOK);
        QWidget::setTabOrder(pushButtonOK, pushButtonCancel);

        retranslateUi(ParameterEstimationDialog);

        QMetaObject::connectSlotsByName(ParameterEstimationDialog);
    } // setupUi

    void retranslateUi(QDialog *ParameterEstimationDialog)
    {
        ParameterEstimationDialog->setWindowTitle(QApplication::translate("ParameterEstimationDialog", "ParameterEstimationDialog", 0));
        label_11->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_13->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_14->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_10->setText(QApplication::translate("ParameterEstimationDialog", "Field of view:", 0));
        label_7->setText(QApplication::translate("ParameterEstimationDialog", "Camera distance:", 0));
        label_6->setText(QApplication::translate("ParameterEstimationDialog", "Xrot:", 0));
        label_8->setText(QApplication::translate("ParameterEstimationDialog", "Yrot:", 0));
        pushButtonCancel->setText(QApplication::translate("ParameterEstimationDialog", "Cancel", 0));
        pushButtonOK->setText(QApplication::translate("ParameterEstimationDialog", "OK", 0));
        checkBoxCentering->setText(QApplication::translate("ParameterEstimationDialog", "Centering", 0));
        label->setText(QApplication::translate("ParameterEstimationDialog", "CGA directory:", 0));
        pushButtonCGADirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_2->setText(QApplication::translate("ParameterEstimationDialog", "Output directory:", 0));
        pushButtonOutputDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_3->setText(QApplication::translate("ParameterEstimationDialog", "Test data directory:", 0));
        pushButtonTestDataDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_4->setText(QApplication::translate("ParameterEstimationDialog", "Classification directory:", 0));
        pushButtonClassificationDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        pushButtonRegressionDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_5->setText(QApplication::translate("ParameterEstimationDialog", "Regression directory:", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterEstimationDialog: public Ui_ParameterEstimationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERESTIMATIONDIALOG_H
