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
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ParameterEstimationDialog
{
public:
    QLabel *label_11;
    QLineEdit *lineEditZrotMax;
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
    QLineEdit *lineEditZrotMin;
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
    QPushButton *pushButtonRegressionDirectory;
    QLabel *label_5;
    QLineEdit *lineEditRegressionDirectory;
    QLineEdit *lineEditFovMax;
    QLineEdit *lineEditFovMin;
    QLabel *label_12;
    QLabel *label_15;
    QLabel *label_9;
    QRadioButton *radioButtonStreetView;
    QRadioButton *radioButtonAerialView;
    QCheckBox *checkBoxSubtractMean;

    void setupUi(QDialog *ParameterEstimationDialog)
    {
        if (ParameterEstimationDialog->objectName().isEmpty())
            ParameterEstimationDialog->setObjectName(QStringLiteral("ParameterEstimationDialog"));
        ParameterEstimationDialog->resize(621, 370);
        label_11 = new QLabel(ParameterEstimationDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(203, 260, 16, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditZrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditZrotMax->setObjectName(QStringLiteral("lineEditZrotMax"));
        lineEditZrotMax->setGeometry(QRect(230, 260, 61, 20));
        lineEditYrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMin->setObjectName(QStringLiteral("lineEditYrotMin"));
        lineEditYrotMin->setGeometry(QRect(140, 230, 61, 20));
        lineEditXrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMin->setObjectName(QStringLiteral("lineEditXrotMin"));
        lineEditXrotMin->setGeometry(QRect(140, 200, 61, 20));
        label_13 = new QLabel(ParameterEstimationDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(203, 200, 16, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditYrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditYrotMax->setObjectName(QStringLiteral("lineEditYrotMax"));
        lineEditYrotMax->setGeometry(QRect(230, 230, 61, 20));
        lineEditXrotMax = new QLineEdit(ParameterEstimationDialog);
        lineEditXrotMax->setObjectName(QStringLiteral("lineEditXrotMax"));
        lineEditXrotMax->setGeometry(QRect(230, 200, 61, 20));
        label_14 = new QLabel(ParameterEstimationDialog);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(203, 230, 16, 20));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(ParameterEstimationDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 260, 101, 20));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditCameraDistance = new QLineEdit(ParameterEstimationDialog);
        lineEditCameraDistance->setObjectName(QStringLiteral("lineEditCameraDistance"));
        lineEditCameraDistance->setGeometry(QRect(140, 170, 61, 20));
        label_7 = new QLabel(ParameterEstimationDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 170, 91, 20));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(ParameterEstimationDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 200, 91, 20));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(ParameterEstimationDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 230, 91, 20));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEditZrotMin = new QLineEdit(ParameterEstimationDialog);
        lineEditZrotMin->setObjectName(QStringLiteral("lineEditZrotMin"));
        lineEditZrotMin->setGeometry(QRect(140, 260, 61, 20));
        pushButtonCancel = new QPushButton(ParameterEstimationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(510, 330, 91, 31));
        pushButtonOK = new QPushButton(ParameterEstimationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(410, 330, 91, 31));
        checkBoxCentering = new QCheckBox(ParameterEstimationDialog);
        checkBoxCentering->setObjectName(QStringLiteral("checkBoxCentering"));
        checkBoxCentering->setGeometry(QRect(290, 170, 91, 17));
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
        label_2->setGeometry(QRect(20, 110, 101, 21));
        lineEditOutputDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(140, 110, 431, 20));
        pushButtonOutputDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(580, 110, 31, 23));
        label_3 = new QLabel(ParameterEstimationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 50, 101, 21));
        lineEditTestDataDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditTestDataDirectory->setObjectName(QStringLiteral("lineEditTestDataDirectory"));
        lineEditTestDataDirectory->setGeometry(QRect(140, 50, 431, 20));
        pushButtonTestDataDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonTestDataDirectory->setObjectName(QStringLiteral("pushButtonTestDataDirectory"));
        pushButtonTestDataDirectory->setGeometry(QRect(580, 50, 31, 23));
        pushButtonRegressionDirectory = new QPushButton(ParameterEstimationDialog);
        pushButtonRegressionDirectory->setObjectName(QStringLiteral("pushButtonRegressionDirectory"));
        pushButtonRegressionDirectory->setGeometry(QRect(580, 80, 31, 23));
        label_5 = new QLabel(ParameterEstimationDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 80, 111, 21));
        lineEditRegressionDirectory = new QLineEdit(ParameterEstimationDialog);
        lineEditRegressionDirectory->setObjectName(QStringLiteral("lineEditRegressionDirectory"));
        lineEditRegressionDirectory->setGeometry(QRect(140, 80, 431, 20));
        lineEditFovMax = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMax->setObjectName(QStringLiteral("lineEditFovMax"));
        lineEditFovMax->setGeometry(QRect(230, 290, 61, 20));
        lineEditFovMin = new QLineEdit(ParameterEstimationDialog);
        lineEditFovMin->setObjectName(QStringLiteral("lineEditFovMin"));
        lineEditFovMin->setGeometry(QRect(140, 290, 61, 20));
        label_12 = new QLabel(ParameterEstimationDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 290, 91, 20));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_15 = new QLabel(ParameterEstimationDialog);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(203, 290, 16, 20));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(ParameterEstimationDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 140, 91, 20));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        radioButtonStreetView = new QRadioButton(ParameterEstimationDialog);
        radioButtonStreetView->setObjectName(QStringLiteral("radioButtonStreetView"));
        radioButtonStreetView->setGeometry(QRect(140, 140, 82, 17));
        radioButtonAerialView = new QRadioButton(ParameterEstimationDialog);
        radioButtonAerialView->setObjectName(QStringLiteral("radioButtonAerialView"));
        radioButtonAerialView->setGeometry(QRect(270, 140, 82, 17));
        checkBoxSubtractMean = new QCheckBox(ParameterEstimationDialog);
        checkBoxSubtractMean->setObjectName(QStringLiteral("checkBoxSubtractMean"));
        checkBoxSubtractMean->setGeometry(QRect(400, 170, 101, 17));
        QWidget::setTabOrder(lineEditCGADirectory, pushButtonCGADirectory);
        QWidget::setTabOrder(pushButtonCGADirectory, lineEditTestDataDirectory);
        QWidget::setTabOrder(lineEditTestDataDirectory, pushButtonTestDataDirectory);
        QWidget::setTabOrder(pushButtonTestDataDirectory, lineEditRegressionDirectory);
        QWidget::setTabOrder(lineEditRegressionDirectory, pushButtonRegressionDirectory);
        QWidget::setTabOrder(pushButtonRegressionDirectory, lineEditOutputDirectory);
        QWidget::setTabOrder(lineEditOutputDirectory, pushButtonOutputDirectory);
        QWidget::setTabOrder(pushButtonOutputDirectory, radioButtonStreetView);
        QWidget::setTabOrder(radioButtonStreetView, radioButtonAerialView);
        QWidget::setTabOrder(radioButtonAerialView, lineEditCameraDistance);
        QWidget::setTabOrder(lineEditCameraDistance, checkBoxCentering);
        QWidget::setTabOrder(checkBoxCentering, checkBoxSubtractMean);
        QWidget::setTabOrder(checkBoxSubtractMean, lineEditXrotMin);
        QWidget::setTabOrder(lineEditXrotMin, lineEditXrotMax);
        QWidget::setTabOrder(lineEditXrotMax, lineEditYrotMin);
        QWidget::setTabOrder(lineEditYrotMin, lineEditYrotMax);
        QWidget::setTabOrder(lineEditYrotMax, lineEditZrotMin);
        QWidget::setTabOrder(lineEditZrotMin, lineEditZrotMax);
        QWidget::setTabOrder(lineEditZrotMax, lineEditFovMin);
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
        label_10->setText(QApplication::translate("ParameterEstimationDialog", "Rot around view dir:", 0));
        label_7->setText(QApplication::translate("ParameterEstimationDialog", "Camera distance:", 0));
        label_6->setText(QApplication::translate("ParameterEstimationDialog", "Rot around X axis:", 0));
        label_8->setText(QApplication::translate("ParameterEstimationDialog", "Rot around Y axis:", 0));
        pushButtonCancel->setText(QApplication::translate("ParameterEstimationDialog", "Cancel", 0));
        pushButtonOK->setText(QApplication::translate("ParameterEstimationDialog", "OK", 0));
        checkBoxCentering->setText(QApplication::translate("ParameterEstimationDialog", "Centering", 0));
        label->setText(QApplication::translate("ParameterEstimationDialog", "CGA directory:", 0));
        pushButtonCGADirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_2->setText(QApplication::translate("ParameterEstimationDialog", "Output directory:", 0));
        pushButtonOutputDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_3->setText(QApplication::translate("ParameterEstimationDialog", "Test data directory:", 0));
        pushButtonTestDataDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        pushButtonRegressionDirectory->setText(QApplication::translate("ParameterEstimationDialog", "...", 0));
        label_5->setText(QApplication::translate("ParameterEstimationDialog", "Regression directory:", 0));
        label_12->setText(QApplication::translate("ParameterEstimationDialog", "Field of view:", 0));
        label_15->setText(QApplication::translate("ParameterEstimationDialog", "~", 0));
        label_9->setText(QApplication::translate("ParameterEstimationDialog", "Camera type:", 0));
        radioButtonStreetView->setText(QApplication::translate("ParameterEstimationDialog", "Street view", 0));
        radioButtonAerialView->setText(QApplication::translate("ParameterEstimationDialog", "Aerial view", 0));
        checkBoxSubtractMean->setText(QApplication::translate("ParameterEstimationDialog", "Subtract mean", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterEstimationDialog: public Ui_ParameterEstimationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERESTIMATIONDIALOG_H
