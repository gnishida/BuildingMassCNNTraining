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
		std::pair<float, float> xrotRange = std::make_pair(dlg.ui.lineEditXrotMin->text().toFloat(), dlg.ui.lineEditXrotMax->text().toFloat());
		float xrotSample = dlg.ui.lineEditXrotSample->text().toFloat();
		std::pair<float, float> yrotRange = std::make_pair(dlg.ui.lineEditYrotMin->text().toFloat(), dlg.ui.lineEditYrotMax->text().toFloat());
		float yrotSample = dlg.ui.lineEditYrotSample->text().toFloat();
		std::pair<float, float> zrotRange = std::make_pair(dlg.ui.lineEditZrotMin->text().toFloat(), dlg.ui.lineEditZrotMax->text().toFloat());
		float zrotSample = dlg.ui.lineEditZrotSample->text().toFloat();
		std::pair<float, float> fovRange = std::make_pair(dlg.ui.lineEditFovMin->text().toFloat(), dlg.ui.lineEditFovMax->text().toFloat());
		float fovSample = dlg.ui.lineEditFovSample->text().toFloat();
		std::pair<float, float> xRange = std::make_pair(dlg.ui.lineEditXMin->text().toFloat(), dlg.ui.lineEditXMax->text().toFloat());
		float xSample = dlg.ui.lineEditXSample->text().toFloat();
		std::pair<float, float> yRange = std::make_pair(dlg.ui.lineEditYMin->text().toFloat(), dlg.ui.lineEditYMax->text().toFloat());
		float ySample = dlg.ui.lineEditYSample->text().toFloat();
		bool generateMean = dlg.ui.checkBoxGenerateMean->isChecked();
		int render_option = dlg.ui.radioButtonRenderSilhouette->isChecked() ? RenderManager::RENDERING_MODE_CONTOUR : RenderManager::RENDERING_MODE_LINE;
		bool discardIfTopFaceIsVisible = dlg.ui.checkBoxDiscardTopFaceVisible->isChecked();
		bool discardIfBottomFaceIsVisible = dlg.ui.checkBoxDiscardBottomFaceVisible->isChecked();
		bool modifyImage = dlg.ui.checkBoxModifyImage->isChecked();
		int lineWidthMin = dlg.ui.lineEditLineWidthMin->text().toInt();
		int lineWidthMax = dlg.ui.lineEditLineWidthMax->text().toInt();
		bool edgeNoise = dlg.ui.checkBoxEdgeNoise->isChecked();
		float edgeNoiseMax = dlg.ui.lineEditEdgeNoiseMax->text().toFloat();

		glWidget3D->generateTrainingImages(dlg.ui.lineEditCGADirectory->text(), dlg.ui.lineEditOutputDirectory->text(), numSamples, imageSize, grayscale, cameraDistanceBase, xrotRange, xrotSample, yrotRange, yrotSample, zrotRange, zrotSample, fovRange, fovSample, xRange, xSample, yRange, ySample, generateMean, render_option, discardIfTopFaceIsVisible, discardIfBottomFaceIsVisible, modifyImage, lineWidthMin, lineWidthMax, edgeNoise, edgeNoiseMax);
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
