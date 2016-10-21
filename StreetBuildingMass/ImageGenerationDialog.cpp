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
	ui.lineEditImageSize->setText("227");
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("-40");
	ui.lineEditXrotMax->setText("0");
	ui.lineEditXrotSample->setText("4");
	ui.lineEditYrotMin->setText("-70");
	ui.lineEditYrotMax->setText("-20");
	ui.lineEditYrotSample->setText("4");
	ui.lineEditZrotMin->setText("-10");
	ui.lineEditZrotMax->setText("10");
	ui.lineEditZrotSample->setText("4");
	ui.lineEditFovMin->setText("20");
	ui.lineEditFovMax->setText("90");
	ui.lineEditFovSample->setText("4");
	ui.lineEditOXMin->setText("-0.8");
	ui.lineEditOXMax->setText("0.8");
	ui.lineEditOXSample->setText("4");
	ui.lineEditOYMin->setText("-0.8");
	ui.lineEditOYMax->setText("0.8");
	ui.lineEditOYSample->setText("4");
	ui.lineEditXMin->setText("-15");
	ui.lineEditXMax->setText("15");
	ui.lineEditXSample->setText("4");
	ui.lineEditYMin->setText("-15");
	ui.lineEditYMax->setText("15");
	ui.lineEditYSample->setText("4");
	ui.lineEditPMSample->setText("4");
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
	ui.checkBoxEdgeBlur->setChecked(false);
	ui.lineEditEdgeBlurSize->setEnabled(false);
	ui.lineEditEdgeBlurSize->setText("5");

	connect(ui.pushButtonCGADirectory, SIGNAL(clicked()), this, SLOT(onCGADirectory()));
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.lineEditXrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditZrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditFovSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditOXSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditOYSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditPMSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.checkBoxModifyImage, SIGNAL(clicked()), this, SLOT(onModifyImageClicked()));
	connect(ui.checkBoxEdgeNoise, SIGNAL(clicked()), this, SLOT(onEdgeNoiseClicked()));
	connect(ui.checkBoxEdgeBlur, SIGNAL(clicked()), this, SLOT(onEdgeBlurClicked()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

	updateTotalNumImages();
}

ImageGenerationDialog::~ImageGenerationDialog() {
}

void ImageGenerationDialog::updateTotalNumImages() {
	int xrot_sam = ui.lineEditXrotSample->text().toInt();
	if (xrot_sam == 0) {
		xrot_sam = 1;
	}

	int yrot_sam = ui.lineEditYrotSample->text().toInt();
	if (yrot_sam == 0) {
		yrot_sam = 1;
	}

	int zrot_sam = ui.lineEditZrotSample->text().toInt();
	if (zrot_sam == 0) {
		zrot_sam = 1;
	}

	int f_sam = ui.lineEditFovSample->text().toInt();
	if (f_sam == 0) {
		f_sam = 1;
	}

	int ox_sam = ui.lineEditOXSample->text().toInt();
	if (ox_sam == 0) {
		ox_sam = 1;
	}

	int oy_sam = ui.lineEditOYSample->text().toInt();
	if (oy_sam == 0) {
		oy_sam = 1;
	}

	int x_sam = ui.lineEditXSample->text().toInt();
	if (x_sam == 0) {
		x_sam = 1;
	}

	int y_sam = ui.lineEditYSample->text().toInt();
	if (y_sam == 0) {
		y_sam = 1;
	}

	int pm_sam = ui.lineEditPMSample->text().toInt();
	if (pm_sam == 0) {
		pm_sam = 1;
	}

	int total = xrot_sam * yrot_sam * zrot_sam * f_sam * ox_sam * oy_sam * x_sam * y_sam * pm_sam * pm_sam * pm_sam;
	ui.lineEditTotalNumImages->setText(QString::number(total));
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
	ui.checkBoxEdgeBlur->setEnabled(ui.checkBoxModifyImage->isChecked());
	ui.lineEditEdgeBlurSize->setEnabled(ui.checkBoxModifyImage->isChecked());
}

void ImageGenerationDialog::onEdgeNoiseClicked() {
	ui.lineEditEdgeNoiseMax->setEnabled(ui.checkBoxEdgeNoise->isChecked());
}

void ImageGenerationDialog::onEdgeBlurClicked() {
	ui.lineEditEdgeBlurSize->setEnabled(ui.checkBoxEdgeBlur->isChecked());
}

void ImageGenerationDialog::onOK() {
	accept();
}

void ImageGenerationDialog::onCancel() {
	reject();
}