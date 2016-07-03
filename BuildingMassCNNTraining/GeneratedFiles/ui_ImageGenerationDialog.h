/********************************************************************************
** Form generated from reading UI file 'ImageGenerationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEGENERATIONDIALOG_H
#define UI_IMAGEGENERATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ImageGenerationDialog
{
public:
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditCGADirectory;
    QPushButton *pushButtonCGADirectory;
    QLineEdit *lineEditOutputDirectory;
    QPushButton *pushButtonOutputDirectory;
    QLabel *label_3;
    QLineEdit *lineEditNumSamples;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEditImageSize;
    QCheckBox *checkBoxGrayscale;
    QCheckBox *checkBoxCentering;
    QLabel *label_6;
    QLineEdit *lineEditCameraDistance;
    QLabel *label_7;
    QLineEdit *lineEditXrotMin;
    QLineEdit *lineEditXrotMax;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEditYrotMin;
    QLineEdit *lineEditYrotMax;
    QLabel *label_10;
    QLineEdit *lineEditFovMax;
    QLineEdit *lineEditFovMin;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *groupBox;
    QCheckBox *checkBoxModifyImage;
    QLineEdit *lineEditLineWidthMax;
    QLabel *label_13;
    QLineEdit *lineEditLineWidthMin;
    QLabel *label_14;
    QCheckBox *checkBoxEdgeNoise;
    QLineEdit *lineEditEdgeNoiseMax;
    QLabel *label_15;

    void setupUi(QDialog *ImageGenerationDialog)
    {
        if (ImageGenerationDialog->objectName().isEmpty())
            ImageGenerationDialog->setObjectName(QStringLiteral("ImageGenerationDialog"));
        ImageGenerationDialog->resize(579, 437);
        pushButtonOK = new QPushButton(ImageGenerationDialog);
        pushButtonOK->setObjectName(QStringLiteral("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(360, 390, 91, 31));
        pushButtonCancel = new QPushButton(ImageGenerationDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(460, 390, 91, 31));
        label = new QLabel(ImageGenerationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 16));
        label_2 = new QLabel(ImageGenerationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 91, 16));
        lineEditCGADirectory = new QLineEdit(ImageGenerationDialog);
        lineEditCGADirectory->setObjectName(QStringLiteral("lineEditCGADirectory"));
        lineEditCGADirectory->setGeometry(QRect(140, 20, 381, 20));
        pushButtonCGADirectory = new QPushButton(ImageGenerationDialog);
        pushButtonCGADirectory->setObjectName(QStringLiteral("pushButtonCGADirectory"));
        pushButtonCGADirectory->setGeometry(QRect(530, 20, 31, 23));
        lineEditOutputDirectory = new QLineEdit(ImageGenerationDialog);
        lineEditOutputDirectory->setObjectName(QStringLiteral("lineEditOutputDirectory"));
        lineEditOutputDirectory->setGeometry(QRect(140, 50, 381, 20));
        pushButtonOutputDirectory = new QPushButton(ImageGenerationDialog);
        pushButtonOutputDirectory->setObjectName(QStringLiteral("pushButtonOutputDirectory"));
        pushButtonOutputDirectory->setGeometry(QRect(530, 50, 31, 23));
        label_3 = new QLabel(ImageGenerationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 111, 16));
        lineEditNumSamples = new QLineEdit(ImageGenerationDialog);
        lineEditNumSamples->setObjectName(QStringLiteral("lineEditNumSamples"));
        lineEditNumSamples->setGeometry(QRect(140, 80, 51, 20));
        label_4 = new QLabel(ImageGenerationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(198, 110, 16, 21));
        label_5 = new QLabel(ImageGenerationDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 110, 91, 16));
        lineEditImageSize = new QLineEdit(ImageGenerationDialog);
        lineEditImageSize->setObjectName(QStringLiteral("lineEditImageSize"));
        lineEditImageSize->setGeometry(QRect(140, 110, 51, 20));
        checkBoxGrayscale = new QCheckBox(ImageGenerationDialog);
        checkBoxGrayscale->setObjectName(QStringLiteral("checkBoxGrayscale"));
        checkBoxGrayscale->setGeometry(QRect(280, 110, 70, 17));
        checkBoxCentering = new QCheckBox(ImageGenerationDialog);
        checkBoxCentering->setObjectName(QStringLiteral("checkBoxCentering"));
        checkBoxCentering->setGeometry(QRect(370, 110, 91, 17));
        label_6 = new QLabel(ImageGenerationDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 140, 91, 16));
        lineEditCameraDistance = new QLineEdit(ImageGenerationDialog);
        lineEditCameraDistance->setObjectName(QStringLiteral("lineEditCameraDistance"));
        lineEditCameraDistance->setGeometry(QRect(140, 140, 51, 20));
        label_7 = new QLabel(ImageGenerationDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 170, 91, 16));
        lineEditXrotMin = new QLineEdit(ImageGenerationDialog);
        lineEditXrotMin->setObjectName(QStringLiteral("lineEditXrotMin"));
        lineEditXrotMin->setGeometry(QRect(140, 170, 51, 20));
        lineEditXrotMax = new QLineEdit(ImageGenerationDialog);
        lineEditXrotMax->setObjectName(QStringLiteral("lineEditXrotMax"));
        lineEditXrotMax->setGeometry(QRect(210, 170, 51, 20));
        label_8 = new QLabel(ImageGenerationDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(196, 170, 16, 16));
        label_9 = new QLabel(ImageGenerationDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 200, 91, 16));
        lineEditYrotMin = new QLineEdit(ImageGenerationDialog);
        lineEditYrotMin->setObjectName(QStringLiteral("lineEditYrotMin"));
        lineEditYrotMin->setGeometry(QRect(140, 200, 51, 20));
        lineEditYrotMax = new QLineEdit(ImageGenerationDialog);
        lineEditYrotMax->setObjectName(QStringLiteral("lineEditYrotMax"));
        lineEditYrotMax->setGeometry(QRect(210, 200, 51, 20));
        label_10 = new QLabel(ImageGenerationDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(196, 200, 16, 16));
        lineEditFovMax = new QLineEdit(ImageGenerationDialog);
        lineEditFovMax->setObjectName(QStringLiteral("lineEditFovMax"));
        lineEditFovMax->setGeometry(QRect(210, 230, 51, 20));
        lineEditFovMin = new QLineEdit(ImageGenerationDialog);
        lineEditFovMin->setObjectName(QStringLiteral("lineEditFovMin"));
        lineEditFovMin->setGeometry(QRect(140, 230, 51, 20));
        label_11 = new QLabel(ImageGenerationDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 230, 91, 16));
        label_12 = new QLabel(ImageGenerationDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(196, 230, 16, 16));
        groupBox = new QGroupBox(ImageGenerationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 260, 521, 111));
        checkBoxModifyImage = new QCheckBox(groupBox);
        checkBoxModifyImage->setObjectName(QStringLiteral("checkBoxModifyImage"));
        checkBoxModifyImage->setGeometry(QRect(40, 20, 141, 17));
        lineEditLineWidthMax = new QLineEdit(groupBox);
        lineEditLineWidthMax->setObjectName(QStringLiteral("lineEditLineWidthMax"));
        lineEditLineWidthMax->setGeometry(QRect(230, 50, 51, 20));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(40, 50, 91, 16));
        lineEditLineWidthMin = new QLineEdit(groupBox);
        lineEditLineWidthMin->setObjectName(QStringLiteral("lineEditLineWidthMin"));
        lineEditLineWidthMin->setGeometry(QRect(160, 50, 51, 20));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(215, 50, 16, 16));
        checkBoxEdgeNoise = new QCheckBox(groupBox);
        checkBoxEdgeNoise->setObjectName(QStringLiteral("checkBoxEdgeNoise"));
        checkBoxEdgeNoise->setGeometry(QRect(40, 80, 91, 17));
        lineEditEdgeNoiseMax = new QLineEdit(groupBox);
        lineEditEdgeNoiseMax->setObjectName(QStringLiteral("lineEditEdgeNoiseMax"));
        lineEditEdgeNoiseMax->setGeometry(QRect(160, 80, 51, 20));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(216, 80, 16, 21));

        retranslateUi(ImageGenerationDialog);

        QMetaObject::connectSlotsByName(ImageGenerationDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageGenerationDialog)
    {
        ImageGenerationDialog->setWindowTitle(QApplication::translate("ImageGenerationDialog", "ImageGenerationDialog", 0));
        pushButtonOK->setText(QApplication::translate("ImageGenerationDialog", "OK", 0));
        pushButtonCancel->setText(QApplication::translate("ImageGenerationDialog", "Cancel", 0));
        label->setText(QApplication::translate("ImageGenerationDialog", "CGA directory:", 0));
        label_2->setText(QApplication::translate("ImageGenerationDialog", "Output directory:", 0));
        pushButtonCGADirectory->setText(QApplication::translate("ImageGenerationDialog", "...", 0));
        pushButtonOutputDirectory->setText(QApplication::translate("ImageGenerationDialog", "...", 0));
        label_3->setText(QApplication::translate("ImageGenerationDialog", "#Samples / viewpoint:", 0));
        label_4->setText(QApplication::translate("ImageGenerationDialog", "px", 0));
        label_5->setText(QApplication::translate("ImageGenerationDialog", "Image size:", 0));
        checkBoxGrayscale->setText(QApplication::translate("ImageGenerationDialog", "Grayscale", 0));
        checkBoxCentering->setText(QApplication::translate("ImageGenerationDialog", "Centering", 0));
        label_6->setText(QApplication::translate("ImageGenerationDialog", "Camera distance:", 0));
        label_7->setText(QApplication::translate("ImageGenerationDialog", "Xrot:", 0));
        label_8->setText(QApplication::translate("ImageGenerationDialog", "~", 0));
        label_9->setText(QApplication::translate("ImageGenerationDialog", "Yrot:", 0));
        label_10->setText(QApplication::translate("ImageGenerationDialog", "~", 0));
        label_11->setText(QApplication::translate("ImageGenerationDialog", "Field of view:", 0));
        label_12->setText(QApplication::translate("ImageGenerationDialog", "~", 0));
        groupBox->setTitle(QApplication::translate("ImageGenerationDialog", "Image modification", 0));
        checkBoxModifyImage->setText(QApplication::translate("ImageGenerationDialog", "Modify rendered image", 0));
        label_13->setText(QApplication::translate("ImageGenerationDialog", "Line width:", 0));
        label_14->setText(QApplication::translate("ImageGenerationDialog", "~", 0));
        checkBoxEdgeNoise->setText(QApplication::translate("ImageGenerationDialog", "Edge noise", 0));
        label_15->setText(QApplication::translate("ImageGenerationDialog", "%", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageGenerationDialog: public Ui_ImageGenerationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEGENERATIONDIALOG_H
