#include "ParameterEstimationDialog.h"
#include <QFileDialog>

ParameterEstimationDialog::ParameterEstimationDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.lineEditCGADirectory->setText("../cga/mass");
	ui.lineEditTestDataDirectory->setText("C:/Anaconda/caffe/contour_regression/data");
	ui.lineEditClassificationDirectory->setText("C:/Anaconda/caffe/contour");
	ui.lineEditRegressionDirectory->setText("C:/Anaconda/caffe/contour_regression");
	ui.lineEditOutputDirectory->setText("results");
	ui.checkBoxCentering->setChecked(true);
	ui.lineEditCameraDistance->setText("25");
	ui.lineEditXrotMin->setText("50");
	ui.lineEditXrotMax->setText("70");
	ui.lineEditYrotMin->setText("20");
	ui.lineEditYrotMax->setText("70");
	ui.lineEditFovMin->setText("30");
	ui.lineEditFovMax->setText("30");

	connect(ui.pushButtonCGADirectory, SIGNAL(clicked()), this, SLOT(onCGADirectory()));
	connect(ui.pushButtonTestDataDirectory, SIGNAL(clicked()), this, SLOT(onTestDataDirectory()));
	connect(ui.pushButtonClassificationDirectory, SIGNAL(clicked()), this, SLOT(onClassificationDirectory()));
	connect(ui.pushButtonRegressionDirectory, SIGNAL(clicked()), this, SLOT(onRegressionDirectory()));
	connect(ui.pushButtonOutputDirectory, SIGNAL(clicked()), this, SLOT(onOutputDirectory()));
	connect(ui.pushButtonOK, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

ParameterEstimationDialog::~ParameterEstimationDialog() {
}

void ParameterEstimationDialog::onCGADirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditCGADirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditCGADirectory->setText(dir);
	}
}

void ParameterEstimationDialog::onTestDataDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditTestDataDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditTestDataDirectory->setText(dir);
	}
}

void ParameterEstimationDialog::onClassificationDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditClassificationDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditClassificationDirectory->setText(dir);
	}
}

void ParameterEstimationDialog::onRegressionDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditRegressionDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditRegressionDirectory->setText(dir);
	}
}

void ParameterEstimationDialog::onOutputDirectory() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ui.lineEditOutputDirectory->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		ui.lineEditOutputDirectory->setText(dir);
	}
}

void ParameterEstimationDialog::onOK() {
	accept();
}

void ParameterEstimationDialog::onCancel() {
	reject();
}
