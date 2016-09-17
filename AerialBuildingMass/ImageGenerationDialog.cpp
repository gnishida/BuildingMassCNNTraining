#include "ImageGenerationDialog.h"
#include <QFileDialog>

ImageGenerationDialog::ImageGenerationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	QButtonGroup group(this);
	group.addButton(ui.radioButtonStreetView);
	group.addButton(ui.radioButtonAerialView);

	ui.lineEditCGADirectory->setText("../cga/mass");
	ui.lineEditOutputDirectory->setText("C:/Anaconda/caffe/contour_regression/data/images");
	ui.lineEditNumSamples->setText("1");
	ui.lineEditImageSize->setText("227");
	ui.checkBoxGrayscale->setChecked(false);
	ui.checkBoxCentering->setChecked(false);
	ui.radioButtonStreetView->setChecked(true);
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("-40");
	ui.lineEditXrotMax->setText("0");
	ui.lineEditXrotSample->setText("4");
	ui.lineEditYrotMin->setText("20");
	ui.lineEditYrotMax->setText("70");
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
	ui.checkBoxGenerateMean->setChecked(true);
	ui.checkBoxModifyImage->setChecked(true);
	ui.lineEditLineWidthMin->setText("1");
	ui.lineEditLineWidthMax->setText("1");
	ui.checkBoxEdgeNoise->setChecked(true);
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
	int xrot_min = ui.lineEditXrotMin->text().toInt();
	int xrot_max = ui.lineEditXrotMax->text().toInt();
	int xrot_sam = ui.lineEditXrotSample->text().toInt();
	int yrot_min = ui.lineEditYrotMin->text().toInt();
	int yrot_max = ui.lineEditYrotMax->text().toInt();
	int yrot_sam = ui.lineEditYrotSample->text().toInt();
	int zrot_min = ui.lineEditZrotMin->text().toInt();
	int zrot_max = ui.lineEditZrotMax->text().toInt();
	int zrot_sam = ui.lineEditZrotSample->text().toInt();
	int f_min = ui.lineEditFovMin->text().toInt();
	int f_max = ui.lineEditFovMax->text().toInt();
	int f_sam = ui.lineEditFovSample->text().toInt();
	int x_min = ui.lineEditXMin->text().toInt();
	int x_max = ui.lineEditXMax->text().toInt();
	int x_sam = ui.lineEditXSample->text().toInt();
	int y_min = ui.lineEditYMin->text().toInt();
	int y_max = ui.lineEditYMax->text().toInt();
	int y_sam = ui.lineEditYSample->text().toInt();

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