#pragma once

#include <glew.h>
#include "Shader.h"
#include "Vertex.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include "Camera.h"
#include "ShadowMapping.h"
#include "RenderManager.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "CGA.h"
#include <QTextStream>

class MainWindow;

class GLWidget3D : public QGLWidget {
public:
	MainWindow* mainWin;

	// camera
	Camera camera;
	glm::vec3 light_dir;
	glm::mat4 light_mvpMatrix;

	// rendering engine
	RenderManager renderManager;

	// key status
	bool ctrlPressed;
	bool shiftPressed;

public:
	GLWidget3D(MainWindow *parent = 0);

	void drawScene();
	void render();
	void loadCGA(const std::string& cga_filename);
	void generateTrainingImages(const QString& cga_dir, const QString& out_dir, int numSamples, int image_size, bool grayscale, float cameraDistanceBase, const std::pair<float, float>& xrotRange, float xrotSample, const std::pair<float, float>& yrotRange, float yrotSample, const std::pair<float, float>& zrotRange, float zrotSample, const std::pair<float, float>& fovRange, float fovSample, const std::pair<float, float>& xRange, float xSample, const std::pair<float, float>& yRange, float ySample, bool generateMean, int render_option, bool discardIfTopFaceIsVisible, bool discardIfBottomFaceIsVisible, bool modifyImage, int lineWidthMin, int lineWidthMax, bool edgeNoise, float edgeNoiseMax);
	void parameterEstimation(const QString& cga_dir, const QString& testdata_dir, const QString& regression_dir, const QString& output_dir, bool centering, bool subtract_mean, int camera_type, float cameraDistanceBase, float cameraHeight, const std::pair<int, int>& xrotRange, const std::pair<int, int>& yrotRange, const std::pair<int, int>& zrotRange, const std::pair<int, int>& fovRange);
	bool moveCenter(cv::Mat& img);
	bool validateImage(const cv::Mat& img);
	void translateImage(cv::Mat source, cv::Mat& target, int shift_x, int shift_y);
	void updateStatusBar();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

	void outputVector(QTextStream& out, const std::vector<float>& values);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	//void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void wheelEvent(QWheelEvent* e);

};

