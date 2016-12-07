#include "ImageGenerationDialog.h"
#include <QFileDialog>

ImageGenerationDialog::ImageGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	QButtonGroup group(this);
	group.addButton(ui.radioButtonRenderSilhouette);
	group.addButton(ui.radioButtonRenderLine);

	ui.lineEditCGADirectory->setText("../cga/mass");
	//ui.lineEditOutputDirectory->setText("C:/Anaconda/caffe/contour_regression/data/images");
	ui.lineEditOutputDirectory->setText("//cuda.cs.purdue.edu/scratch2/contour_regression/data/images");
	ui.lineEditNumSamples->setText("1");
	ui.lineEditImageSize->setText("227");
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("-40");
	ui.lineEditXrotMax->setText("0");
	ui.lineEditYrotMin->setText("-70");
	ui.lineEditYrotMax->setText("-20");
	ui.lineEditZrotMin->setText("-10");
	ui.lineEditZrotMax->setText("10");
	ui.lineEditFovMin->setText("20");
	ui.lineEditFovMax->setText("90");
	ui.lineEditOXMin->setText("-0.8");
	ui.lineEditOXMax->setText("0.8");
	ui.lineEditOYMin->setText("-0.8");
	ui.lineEditOYMax->setText("0.8");
	ui.lineEditXMin->setText("-15");
	ui.lineEditXMax->setText("15");
	ui.lineEditYMin->setText("-15");
	ui.lineEditYMax->setText("15");
	ui.radioButtonRenderSilhouette->setChecked(true);
	ui.radioButtonRenderLine->setChecked(false);
	ui.checkBoxDiscardTooBig->setChecked(true);
	ui.checkBoxDiscardTopFaceVisible->setChecked(true);
	ui.checkBoxDiscardBottomFaceVisible->setChecked(true);
	ui.checkBoxModifyImage->setChecked(true);
	ui.lineEditLineWidthMin->setText("1");
	ui.lineEditLineWidthMax->setText("1");
	ui.checkBoxEdgeNoise->setChecked(true);
	ui.lineEditEdgeNoiseMax->setText("0.5");

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