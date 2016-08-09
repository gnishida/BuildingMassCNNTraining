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
	ui.lineEditXrotSample->setText("1");
	ui.lineEditYrotMin->setText("20");
	ui.lineEditYrotMax->setText("70");
	ui.lineEditYrotSample->setText("1");
	ui.lineEditZrotMin->setText("-20");
	ui.lineEditZrotMax->setText("20");
	ui.lineEditZrotSample->setText("1");
	ui.lineEditFovMin->setText("10");
	ui.lineEditFovMax->setText("10");
	ui.lineEditFovSample->setText("1");
	ui.checkBoxGenerateMean->setChecked(true);
	ui.checkBoxModifyImage->setChecked(true);
	ui.lineEditLineWidthMin->setText("1");
	ui.lineEditLineWidthMax->setText("1");
	ui.checkBoxEdgeNoise->setChecked(true);
	ui.lineEditEdgeNoiseMax->setText("1.0");

	connect(ui.pushButtonCGADirectory, SIGNAL(clicked()), this, SLOT(onCGADirectory()));
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
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
	int xmin = ui.lineEditXrotMin->text().toInt();
	int xmax = ui.lineEditXrotMax->text().toInt();
	int xsam = ui.lineEditXrotSample->text().toInt();
	int ymin = ui.lineEditYrotMin->text().toInt();
	int ymax = ui.lineEditYrotMax->text().toInt();
	int ysam = ui.lineEditYrotSample->text().toInt();
	int zmin = ui.lineEditZrotMin->text().toInt();
	int zmax = ui.lineEditZrotMax->text().toInt();
	int zsam = ui.lineEditZrotSample->text().toInt();
	int fmin = ui.lineEditFovMin->text().toInt();
	int fmax = ui.lineEditFovMax->text().toInt();
	int fsam = ui.lineEditFovSample->text().toInt();

	int total = ((xmax - xmin) / xsam + 1) * ((ymax - ymin) / ysam + 1) * ((zmax - zmin) / zsam + 1) * ((fmax - fmin) / fsam + 1) * samples;
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