#include "MainWindow.h"
#include <QFileDialog>
#include "ImageGenerationDialog.h"
#include "ParameterEstimationDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionOpenCGA, SIGNAL(triggered()), this, SLOT(onOpenCGA()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionGenerateTrainingImages, SIGNAL(triggered()), this, SLOT(onGenerateTrainingImages()));
	connect(ui.actionParameterEstimation, SIGNAL(triggered()), this, SLOT(onParameterEstimation()));

	glWidget3D = new GLWidget3D(this);
	this->setCentralWidget(glWidget3D);
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
	glWidget3D->keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	glWidget3D->keyReleaseEvent(e);
}

void MainWindow::onOpenCGA() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load CGA file..."), "", tr("CGA Files (*.xml)"));
	if (filename.isEmpty()) return;

	glWidget3D->loadCGA(filename.toUtf8().constData());
}

void MainWindow::onGenerateTrainingImages() {
	ImageGenerationDialog dlg;
	if (dlg.exec() && !dlg.ui.lineEditCGADirectory->text().isEmpty() && !dlg.ui.lineEditOutputDirectory->text().isEmpty()) {
		int numSamples = dlg.ui.lineEditNumSamples->text().toInt();
		int imageSize = dlg.ui.lineEditImageSize->text().toInt();
		bool grayscale = dlg.ui.checkBoxGrayscale->isChecked();
		float cameraDistanceBase = dlg.ui.lineEditCameraDistance->text().toFloat();
		std::pair<int, int> xrotRange = std::make_pair(dlg.ui.lineEditXrotMin->text().toInt(), dlg.ui.lineEditXrotMax->text().toInt());
		int xrotSample = dlg.ui.lineEditXrotSample->text().toInt();
		std::pair<int, int> yrotRange = std::make_pair(dlg.ui.lineEditYrotMin->text().toInt(), dlg.ui.lineEditYrotMax->text().toInt());
		int yrotSample = dlg.ui.lineEditYrotSample->text().toInt();
		std::pair<int, int> zrotRange = std::make_pair(dlg.ui.lineEditZrotMin->text().toInt(), dlg.ui.lineEditZrotMax->text().toInt());
		int zrotSample = dlg.ui.lineEditZrotSample->text().toInt();
		std::pair<int, int> fovRange = std::make_pair(dlg.ui.lineEditFovMin->text().toInt(), dlg.ui.lineEditFovMax->text().toInt());
		int fovSample = dlg.ui.lineEditFovSample->text().toInt();
		std::pair<int, int> xRange = std::make_pair(dlg.ui.lineEditXMin->text().toInt(), dlg.ui.lineEditXMax->text().toInt());
		int xSample = dlg.ui.lineEditXSample->text().toInt();
		std::pair<int, int> yRange = std::make_pair(dlg.ui.lineEditYMin->text().toInt(), dlg.ui.lineEditYMax->text().toInt());
		int ySample = dlg.ui.lineEditYSample->text().toInt();
		bool generateMean = dlg.ui.checkBoxGenerateMean->isChecked();
		bool modifyImage = dlg.ui.checkBoxModifyImage->isChecked();
		int lineWidthMin = dlg.ui.lineEditLineWidthMin->text().toInt();
		int lineWidthMax = dlg.ui.lineEditLineWidthMax->text().toInt();
		bool edgeNoise = dlg.ui.checkBoxEdgeNoise->isChecked();
		float edgeNoiseMax = dlg.ui.lineEditEdgeNoiseMax->text().toFloat();

		glWidget3D->generateTrainingImages(dlg.ui.lineEditCGADirectory->text(), dlg.ui.lineEditOutputDirectory->text(), numSamples, imageSize, grayscale, cameraDistanceBase, xrotRange, xrotSample, yrotRange, yrotSample, zrotRange, zrotSample, fovRange, fovSample, xRange, xSample, yRange, ySample, generateMean, modifyImage, lineWidthMin, lineWidthMax, edgeNoise, edgeNoiseMax);
	}
}

void MainWindow::onParameterEstimation() {
	ParameterEstimationDialog dlg;
	if (dlg.exec() && !dlg.ui.lineEditCGADirectory->text().isEmpty() && !dlg.ui.lineEditTestDataDirectory->text().isEmpty()) {
		bool centering = dlg.ui.checkBoxCentering->isChecked();
		int camera_type = dlg.ui.radioButtonStreetView->isChecked() ? 0 : 1;
		float cameraDistanceBase = dlg.ui.lineEditCameraDistance->text().toFloat();
		bool subtract_mean = dlg.ui.checkBoxSubtractMean->isChecked();
		std::pair<int, int> xrotRange = std::make_pair(dlg.ui.lineEditXrotMin->text().toInt(), dlg.ui.lineEditXrotMax->text().toInt());
		std::pair<int, int> yrotRange = std::make_pair(dlg.ui.lineEditYrotMin->text().toInt(), dlg.ui.lineEditYrotMax->text().toInt());
		std::pair<int, int> zrotRange = std::make_pair(dlg.ui.lineEditZrotMin->text().toInt(), dlg.ui.lineEditZrotMax->text().toInt());
		std::pair<int, int> fovRange = std::make_pair(dlg.ui.lineEditFovMin->text().toInt(), dlg.ui.lineEditFovMax->text().toInt());

		glWidget3D->parameterEstimation(dlg.ui.lineEditCGADirectory->text(), dlg.ui.lineEditTestDataDirectory->text(), dlg.ui.lineEditRegressionDirectory->text(), dlg.ui.lineEditOutputDirectory->text(), centering, subtract_mean, camera_type, cameraDistanceBase, 1.7f, xrotRange, yrotRange, zrotRange, fovRange);
	}
}
