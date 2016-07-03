#include "ImageGenerationDialog.h"
#include <QFileDialog>

ImageGenerationDialog::ImageGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.lineEditCGADirectory->setText("../cga/mass");
	ui.lineEditOutputDirectory->setText("C:/Anaconda/caffe/contour_regression/data/images");
	ui.lineEditNumSamples->setText("100");
	ui.lineEditImageSize->setText("128");
	ui.checkBoxGrayscale->setChecked(true);
	ui.checkBoxCentering->setChecked(true);
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("50");
	ui.lineEditXrotMax->setText("70");
	ui.lineEditYrotMin->setText("20");
	ui.lineEditYrotMax->setText("70");
	ui.lineEditFovMin->setText("30");
	ui.lineEditFovMax->setText("30");
	ui.checkBoxModifyImage->setChecked(true);
	ui.lineEditLineWidthMin->setText("1");
	ui.lineEditLineWidthMax->setText("1");
	ui.checkBoxEdgeNoise->setChecked(true);
	ui.lineEditEdgeNoiseMax->setText("1.0");

	connect(ui.pushButtonCGADirectory, SIGNAL(clicked()), this, SLOT(onCGADirectory()));
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.checkBoxModifyImage, SIGNAL(clicked()), this, SLOT(onModifyImageClicked()));
	connect(ui.checkBoxEdgeNoise, SIGNAL(clicked()), this, SLOT(onEdgeNoiseClicked()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

}

ImageGenerationDialog::~ImageGenerationDialog() {
}

void ImageGenerationDialog::onCGADirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditCGADirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditCGADirectory->setText(dir);
	}
}

void ImageGenerationDialog::onOutputDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutputDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutputDirectory->setText(dir);
	}

}

void ImageGenerationDialog::onModifyImageClicked() {
	ui.lineEditLineWidthMin->setEnabled(ui.checkBoxModifyImage->isChecked());
	ui.lineEditLineWidthMax->setEnabled(ui.checkBoxModifyImage->isChecked());
	ui.checkBoxEdgeNoise->setEnabled(ui.checkBoxModifyImage->isChecked());
	ui.lineEditEdgeNoiseMax->setEnabled(ui.checkBoxModifyImage->isChecked());
}

void ImageGenerationDialog::onEdgeNoiseClicked() {
	ui.lineEditEdgeNoiseMax->setEnabled(ui.checkBoxEdgeNoise->isChecked());
}

void ImageGenerationDialog::onOK() {
	accept();
}

void ImageGenerationDialog::onCancel() {
	reject();
}