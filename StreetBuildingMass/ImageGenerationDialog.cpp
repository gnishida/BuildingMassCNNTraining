#include "ImageGenerationDialog.h"
#include <QFileDialog>

ImageGenerationDialog::ImageGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	QButtonGroup group(this);
	group.addButton(ui.radioButtonRenderSilhouette);
	group.addButton(ui.radioButtonRenderLine);

	ui.lineEditCGADirectory->setText("../cga/mass");
	ui.lineEditOutputDirectory->setText("C:/Anaconda/caffe/contour_regression/data/images");
	ui.lineEditNumSamples->setText("1");
	ui.lineEditImageSize->setText("227");
	ui.checkBoxGrayscale->setChecked(false);
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("-40");
	ui.lineEditXrotMax->setText("0");
	ui.lineEditXrotSample->setText("4");
	ui.lineEditYrotMin->setText("-70");
	ui.lineEditYrotMax->setText("-20");
	ui.lineEditYrotSample->setText("5");
	ui.lineEditZrotMin->setText("-10");
	ui.lineEditZrotMax->setText("10");
	ui.lineEditZrotSample->setText("2");
	ui.lineEditFovMin->setText("20");
	ui.lineEditFovMax->setText("90");
	ui.lineEditFovSample->setText("7");
	ui.lineEditXMin->setText("-15");
	ui.lineEditXMax->setText("15");
	ui.lineEditXSample->setText("3");
	ui.lineEditYMin->setText("-15");
	ui.lineEditYMax->setText("15");
	ui.lineEditYSample->setText("3");
	ui.checkBoxGenerateMean->setChecked(false);
	ui.radioButtonRenderSilhouette->setChecked(true);
	ui.radioButtonRenderLine->setChecked(false);
	ui.checkBoxModifyImage->setChecked(false);
	ui.lineEditLineWidthMin->setText("1");
	ui.lineEditLineWidthMax->setText("1");
	ui.checkBoxEdgeNoise->setEnabled(false);
	ui.checkBoxEdgeNoise->setChecked(false);
	ui.lineEditEdgeNoiseMax->setText("1.0");

	connect(ui.pushButtonCGADirectory, SIGNAL(clicked()), this, SLOT(onCGADirectory()));
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.lineEditNumSamples, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXrotMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXrotMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYrotMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYrotMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditZrotMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditZrotMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditZrotSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditFovMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditFovMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditFovSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditXSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYMin, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYMax, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.lineEditYSample, SIGNAL(textChanged(const QString&)), this, SLOT(updateTotalNumImages()));
	connect(ui.checkBoxModifyImage, SIGNAL(clicked()), this, SLOT(onModifyImageClicked()));
	connect(ui.checkBoxEdgeNoise, SIGNAL(clicked()), this, SLOT(onEdgeNoiseClicked()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

	updateTotalNumImages();
}

ImageGenerationDialog::~ImageGenerationDialog() {
}

void ImageGenerationDialog::updateTotalNumImages() {
	int samples = ui.lineEditNumSamples->text().toInt();
	float xrot_min = ui.lineEditXrotMin->text().toFloat();
	float xrot_max = ui.lineEditXrotMax->text().toFloat();
	float xrot_sam = ui.lineEditXrotSample->text().toFloat();
	if (xrot_sam == 0) {
		xrot_sam = 1;
		ui.lineEditXrotSample->setText("1");
	}

	float yrot_min = ui.lineEditYrotMin->text().toFloat();
	float yrot_max = ui.lineEditYrotMax->text().toFloat();
	float yrot_sam = ui.lineEditYrotSample->text().toFloat();
	if (yrot_sam == 0) {
		yrot_sam = 1;
		ui.lineEditYrotSample->setText("1");
	}

	float zrot_min = ui.lineEditZrotMin->text().toFloat();
	float zrot_max = ui.lineEditZrotMax->text().toFloat();
	float zrot_sam = ui.lineEditZrotSample->text().toFloat();
	if (zrot_sam == 0) {
		zrot_sam = 1;
		ui.lineEditZrotSample->setText("1");
	}

	float f_min = ui.lineEditFovMin->text().toFloat();
	float f_max = ui.lineEditFovMax->text().toFloat();
	float f_sam = ui.lineEditFovSample->text().toFloat();
	if (f_sam == 0) {
		f_sam = 1;
		ui.lineEditFovSample->setText("1");
	}

	float x_min = ui.lineEditXMin->text().toFloat();
	float x_max = ui.lineEditXMax->text().toFloat();
	float x_sam = ui.lineEditXSample->text().toFloat();
	if (x_sam == 0) {
		x_sam = 1;
		ui.lineEditXSample->setText("1");
	}

	float y_min = ui.lineEditYMin->text().toFloat();
	float y_max = ui.lineEditYMax->text().toFloat();
	float y_sam = ui.lineEditYSample->text().toFloat();
	if (y_sam == 0) {
		y_sam = 1;
		ui.lineEditYSample->setText("1");
	}

	int total = ((xrot_max - xrot_min) / xrot_sam + 1) * ((yrot_max - yrot_min) / yrot_sam + 1) * ((zrot_max - zrot_min) / zrot_sam + 1) * ((f_max - f_min) / f_sam + 1) * ((x_max - x_min) / x_sam + 1) * ((y_max - y_min) / y_sam + 1) * samples;
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