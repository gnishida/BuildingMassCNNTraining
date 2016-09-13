#include "GLWidget3D.h"
#include "MainWindow.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "GLUtils.h"
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <QProcess>
#include "Utils.h"
#include "MCMC.h"
#include "GrammarParser.h"
#include "CGA.h"
#include "Rectangle.h"
#include <fstream>
#include <opencv2/core.hpp>
#include <QFileDialog>
#include "Classifier.h"
#include "Regression.h"
#include <boost/algorithm/string.hpp>

#ifndef M_PI
#define	M_PI	3.141592653
#endif
#ifndef SQR
#define SQR(x)	((x) * (x))
#endif

GLWidget3D::GLWidget3D(MainWindow *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers)) {
	this->mainWin = parent;
	shiftPressed = false;

	// This is necessary to prevent the screen overdrawn by OpenGL
	//setAutoFillBackground(false);

	// 光源位置をセット
	// ShadowMappingは平行光源を使っている。この位置から原点方向を平行光源の方向とする。
	light_dir = glm::normalize(glm::vec3(-4, -5, -8));

	// シャドウマップ用のmodel/view/projection行列を作成
	glm::mat4 light_pMatrix = glm::ortho<float>(-50, 50, -50, 50, 0.1, 200);
	glm::mat4 light_mvMatrix = glm::lookAt(-light_dir * 50.0f, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	light_mvpMatrix = light_pMatrix * light_mvMatrix;
}

void GLWidget3D::updateStatusBar() {
	QString msg = QString("xrot: %1, yrot: %2, zrot: %3, pos: (%4, %5, %6)").arg(camera.xrot).arg(camera.yrot).arg(camera.zrot).arg(camera.pos.x).arg(camera.pos.y).arg(camera.pos.z);
	mainWin->statusBar()->showMessage(msg);
}

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::RightButton) {
		camera.mousePress(e->x(), e->y());
	}
	else if (e->buttons() & Qt::MidButton) { // Rotate around viewing direction
		camera.mousePress(e->x(), e->y());
	}
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e) {
}

/**
 * This event handler is called when the mouse move events occur.
 */
void GLWidget3D::mouseMoveEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::RightButton) { // Rotate
		if (shiftPressed) { // Move
			camera.move(e->x(), e->y());
		}
		else {
			camera.rotate(e->x(), e->y());
		}
	}
	else if (e->buttons() & Qt::MidButton) { // Rotate around viewing direction
		camera.rotateAroundZ(e->x(), e->y());
	}
	updateStatusBar();
	update();
}

void GLWidget3D::wheelEvent(QWheelEvent* e) {
	camera.zoom(e->delta() * 0.01);
	updateStatusBar();
	update();
}

/**
 * This function is called once before the first call to paintGL() or resizeGL().
 */
void GLWidget3D::initializeGL() {
	// init glew
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	if (glewIsSupported("GL_VERSION_4_2"))
		printf("Ready for OpenGL 4.2\n");
	else {
		printf("OpenGL 4.2 not supported\n");
		exit(1);
	}
	const GLubyte* text = glGetString(GL_VERSION);
	printf("VERSION: %s\n", text);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_3D);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glDisable(GL_TEXTURE_3D);

	glEnable(GL_TEXTURE_2D_ARRAY);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glDisable(GL_TEXTURE_2D_ARRAY);

	////////////////////////////////
	renderManager.init("", "", "", true, 8192);
	renderManager.resize(this->width(), this->height());
	renderManager.renderingMode = RenderManager::RENDERING_MODE_LINE;

	glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "tex0"), 0);//tex0: 0

	/*
	std::vector<Vertex> vertices;
	glutils::drawBox(30, 30, 15, glm::vec4(1, 1, 1, 1), glm::translate(glm::rotate(glm::mat4(), -(float)M_PI * 0.5f, glm::vec3(1, 0, 0)), glm::vec3(0, 0, 7.5)), vertices);
	glutils::drawGrid(30, 30, 2, glm::vec4(0, 0, 1, 1), glm::vec4(0.95, 0.95, 1, 1), glm::rotate(glm::mat4(), -(float)M_PI * 0.5f, glm::vec3(1, 0, 0)), vertices);
	renderManager.addObject("box", "", vertices, true);
	*/

	updateStatusBar();
}

/**
 * This function is called whenever the widget has been resized.
 */
void GLWidget3D::resizeGL(int width, int height) {
	height = height ? height : 1;
	glViewport(0, 0, width, height);
	camera.updatePMatrix(width, height);

	renderManager.resize(width, height);
}

/**
 * This function is called whenever the widget needs to be painted.
 */
void GLWidget3D::paintGL() {	
	render();

	glActiveTexture(GL_TEXTURE0);
}

/**
 * Draw the scene.
 */
void GLWidget3D::drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);

	renderManager.renderAll();
}

void GLWidget3D::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PASS 1: Render to texture
	glUseProgram(renderManager.programs["pass1"]);

	glBindFramebuffer(GL_FRAMEBUFFER, renderManager.fragDataFB);
	glClearColor(0.95, 0.95, 0.95, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderManager.fragDataTex[0], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, renderManager.fragDataTex[1], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, renderManager.fragDataTex[2], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, renderManager.fragDataTex[3], 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderManager.fragDepthTex, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, DrawBuffers); // "3" is the size of DrawBuffers
	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("+ERROR: GL_FRAMEBUFFER_COMPLETE false\n");
		exit(0);
	}

	glUniformMatrix4fv(glGetUniformLocation(renderManager.programs["pass1"], "mvpMatrix"), 1, false, &camera.mvpMatrix[0][0]);
	glUniform3f(glGetUniformLocation(renderManager.programs["pass1"], "lightDir"), light_dir.x, light_dir.y, light_dir.z);
	glUniformMatrix4fv(glGetUniformLocation(renderManager.programs["pass1"], "light_mvpMatrix"), 1, false, &light_mvpMatrix[0][0]);

	glUniform1i(glGetUniformLocation(renderManager.programs["pass1"], "shadowMap"), 6);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, renderManager.shadow.textureDepth);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	drawScene();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// PASS 2: Create AO
	if (renderManager.renderingMode == RenderManager::RENDERING_MODE_SSAO) {
		glUseProgram(renderManager.programs["ssao"]);
		glBindFramebuffer(GL_FRAMEBUFFER, renderManager.fragDataFB_AO);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderManager.fragAOTex, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderManager.fragDepthTex_AO, 0);
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Always check that our framebuffer is ok
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			printf("++ERROR: GL_FRAMEBUFFER_COMPLETE false\n");
			exit(0);
		}

		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);

		glUniform2f(glGetUniformLocation(renderManager.programs["ssao"], "pixelSize"), 2.0f / this->width(), 2.0f / this->height());

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "tex0"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[0]);

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "tex1"), 2);
		glActiveTexture(GL_TEXTURE2);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[1]);

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "tex2"), 3);
		glActiveTexture(GL_TEXTURE3);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[2]);

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "depthTex"), 8);
		glActiveTexture(GL_TEXTURE8);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDepthTex);

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "noiseTex"), 7);
		glActiveTexture(GL_TEXTURE7);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragNoiseTex);

		{
			glUniformMatrix4fv(glGetUniformLocation(renderManager.programs["ssao"], "mvpMatrix"), 1, false, &camera.mvpMatrix[0][0]);
			glUniformMatrix4fv(glGetUniformLocation(renderManager.programs["ssao"], "pMatrix"), 1, false, &camera.pMatrix[0][0]);
		}

		glUniform1i(glGetUniformLocation(renderManager.programs["ssao"], "uKernelSize"), renderManager.uKernelSize);
		glUniform3fv(glGetUniformLocation(renderManager.programs["ssao"], "uKernelOffsets"), renderManager.uKernelOffsets.size(), (const GLfloat*)renderManager.uKernelOffsets.data());

		glUniform1f(glGetUniformLocation(renderManager.programs["ssao"], "uPower"), renderManager.uPower);
		glUniform1f(glGetUniformLocation(renderManager.programs["ssao"], "uRadius"), renderManager.uRadius);

		glBindVertexArray(renderManager.secondPassVAO);

		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		glDepthFunc(GL_LEQUAL);
	}
	else if (renderManager.renderingMode == RenderManager::RENDERING_MODE_LINE || renderManager.renderingMode == RenderManager::RENDERING_MODE_HATCHING) {
		glUseProgram(renderManager.programs["line"]);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);

		glUniform2f(glGetUniformLocation(renderManager.programs["line"], "pixelSize"), 1.0f / this->width(), 1.0f / this->height());
		glUniformMatrix4fv(glGetUniformLocation(renderManager.programs["line"], "pMatrix"), 1, false, &camera.pMatrix[0][0]);
		if (renderManager.renderingMode == RenderManager::RENDERING_MODE_LINE) {
			glUniform1i(glGetUniformLocation(renderManager.programs["line"], "useHatching"), 0);
		}
		else {
			glUniform1i(glGetUniformLocation(renderManager.programs["line"], "useHatching"), 1);
		}

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "tex0"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[0]);

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "tex1"), 2);
		glActiveTexture(GL_TEXTURE2);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[1]);

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "tex2"), 3);
		glActiveTexture(GL_TEXTURE3);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[2]);

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "tex3"), 4);
		glActiveTexture(GL_TEXTURE4);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[3]);

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "depthTex"), 8);
		glActiveTexture(GL_TEXTURE8);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDepthTex);

		glUniform1i(glGetUniformLocation(renderManager.programs["line"], "hatchingTexture"), 5);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_3D, renderManager.hatchingTextures);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindVertexArray(renderManager.secondPassVAO);

		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		glDepthFunc(GL_LEQUAL);
	}
	else if (renderManager.renderingMode == RenderManager::RENDERING_MODE_CONTOUR) {
		glUseProgram(renderManager.programs["contour"]);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);

		glUniform2f(glGetUniformLocation(renderManager.programs["contour"], "pixelSize"), 1.0f / this->width(), 1.0f / this->height());

		glUniform1i(glGetUniformLocation(renderManager.programs["contour"], "depthTex"), 8);
		glActiveTexture(GL_TEXTURE8);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDepthTex);

		glBindVertexArray(renderManager.secondPassVAO);

		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		glDepthFunc(GL_LEQUAL);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Blur

	if (renderManager.renderingMode == RenderManager::RENDERING_MODE_BASIC || renderManager.renderingMode == RenderManager::RENDERING_MODE_SSAO) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		qglClearColor(QColor(0xFF, 0xFF, 0xFF));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);

		glUseProgram(renderManager.programs["blur"]);
		glUniform2f(glGetUniformLocation(renderManager.programs["blur"], "pixelSize"), 2.0f / this->width(), 2.0f / this->height());
		//printf("pixelSize loc %d\n", glGetUniformLocation(vboRenderManager.programs["blur"], "pixelSize"));

		glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "tex0"), 1);//COLOR
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[0]);

		glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "tex1"), 2);//NORMAL
		glActiveTexture(GL_TEXTURE2);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[1]);

		/*glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "tex2"), 3);
		glActiveTexture(GL_TEXTURE3);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDataTex[2]);*/

		glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "depthTex"), 8);
		glActiveTexture(GL_TEXTURE8);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragDepthTex);

		glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "tex3"), 4);//AO
		glActiveTexture(GL_TEXTURE4);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, renderManager.fragAOTex);

		if (renderManager.renderingMode == RenderManager::RENDERING_MODE_SSAO) {
			glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "ssao_used"), 1); // ssao used
		}
		else {
			glUniform1i(glGetUniformLocation(renderManager.programs["blur"], "ssao_used"), 0); // no ssao
		}

		glBindVertexArray(renderManager.secondPassVAO);

		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);
		glDepthFunc(GL_LEQUAL);

	}

	// REMOVE
	glActiveTexture(GL_TEXTURE0);
}

void GLWidget3D::loadCGA(const std::string& cga_filename) {
	cga::Grammar grammar;
	cga::parseGrammar(cga_filename.c_str(), grammar);

	cga::CGA cga;
	cga.modelMat = glm::rotate(glm::mat4(), -3.1415926f * 0.5f, glm::vec3(1, 0, 0));

	renderManager.removeObjects();

	// set axiom
	cga::Rectangle* start = new cga::Rectangle("Start", "", glm::translate(glm::rotate(glm::mat4(), -3.141592f * 0.5f, glm::vec3(1, 0, 0)), glm::vec3(0, 0, 0)), glm::mat4(), 0, 0, glm::vec3(1, 1, 1));
	cga.stack.push_back(boost::shared_ptr<cga::Shape>(start));

	// generate 3d model
	cga.derive(grammar, true);
	std::vector<boost::shared_ptr<glutils::Face> > faces;
	cga.generateGeometry(faces, true);
	renderManager.addFaces(faces, true);

	renderManager.updateShadowMap(this, light_dir, light_mvpMatrix);

	// render 2d image
	render();
}

/**
* @param cga_dir			directory of CGA files
* @param out_dir			directory for the output files
* @param numSamples		number of samples per viewpoint
* @param image_width		image width
* @param image_height		image height
* @param grayscale			true if the output file is to be grayscale
* @param cameraTYpe		0 -- street view / 1 -- aerial view
* @param cameraDistance	distance to the camera
* @param cameraHeight		height of the camera
* @param xrotMean			mean of xrot
* @param xrotRange			range of xrot
* @param yrotMean			mean of yrot
* @param yrotRange			range of yrot
* @param fovMin			min of fov
* @param fovMax			max of fov
*/
void GLWidget3D::generateTrainingImages(const QString& cga_dir, const QString& out_dir, int numSamples, int image_size, bool grayscale, bool centering, int camera_type, float cameraDistanceBase, float cameraHeight, const std::pair<int, int>& xrotRange, int xrotSample, const std::pair<int, int>& yrotRange, int yrotSample, const std::pair<int, int>& zrotRange, int zrotSample, const std::pair<int, int>& fovRange, int fovSample, bool generateMean, bool modifyImage, int lineWidthMin, int lineWidthMax, bool edgeNoise, float edgeNoiseMax) {
	if (QDir(out_dir).exists()) {
		std::cout << "Clearning output directory..." << std::endl;
		QDir(out_dir).removeRecursively();
		std::cout << "Done." << std::endl;
	}
	QDir().mkpath(out_dir);

	std::cout << "Training images are being generated with following parameters:" << std::endl;
	std::cout << "  cga_dir: " << cga_dir.toUtf8().constData() << std::endl;
	std::cout << "  out_dir: " << out_dir.toUtf8().constData() << std::endl;
	std::cout << "  #Samples: " << numSamples << std::endl;
	std::cout << "  image size: " << image_size << std::endl;
	std::cout << "  grayscale: " << (grayscale ? "true" : "false") << std::endl;
	std::cout << "  centering: " << (centering ? "true" : "false") << std::endl;
	std::cout << "  camera type: " << (camera_type == 0 ? "street view" : "aerial view") << std::endl;
	std::cout << "  camera distance base: " << cameraDistanceBase << std::endl;
	std::cout << "  camera height: " << cameraHeight << std::endl;
	std::cout << "  x rot: " << xrotRange.first << " - " << xrotRange.second << " (every " << xrotSample << ")" << std::endl;
	std::cout << "  y rot: " << yrotRange.first << " - " << yrotRange.second << " (every " << yrotSample << ")" << std::endl;
	std::cout << "  z rot: " << zrotRange.first << " - " << zrotRange.second << " (every " << zrotSample << ")" << std::endl;
	std::cout << "  FOV: " << fovRange.first << " - " << fovRange.second << " (every " << fovSample << ")" << std::endl;
	std::cout << "  generate Mean: " << (generateMean ? "true" : "false") << std::endl;
	std::cout << "  modify image: " << (modifyImage ? "true" : "false") << std::endl;
	std::cout << "  line width: " << lineWidthMin << " - " << lineWidthMax << std::endl;
	std::cout << "  edge noise: " << (edgeNoise ? "true" : "false") << std::endl;
	std::cout << "  edge noise max: " << edgeNoiseMax << std::endl;
	std::cout << std::endl;

	srand(0);
	renderManager.useShadow = false;
	renderManager.renderingMode = RenderManager::RENDERING_MODE_CONTOUR;

	int origWidth = width();
	int origHeight = height();
	resize(512, 512);
	resizeGL(512, 512);

	// setup grammars
	std::vector<cga::Grammar> grammars;
	std::vector<QString> grammar_filenames;
	QStringList filters;
	filters << "*.xml";
	QFileInfoList fileInfoList = QDir(cga_dir).entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
	for (int i = 0; i < fileInfoList.size(); ++i) {
		cga::Grammar grammar;
		cga::parseGrammar(fileInfoList[i].absoluteFilePath().toUtf8().constData(), grammar);
		grammars.push_back(grammar);

		int index = fileInfoList[i].baseName().indexOf("_");
		if (index >= 0) {
			grammar_filenames.push_back(fileInfoList[i].baseName().mid(index + 1));
		}
		else {
			grammar_filenames.push_back(QString().number(i + 1));
		}
	}

	for (int grammar_id = 0; grammar_id < grammars.size(); ++grammar_id) {
		int count = 0;

		QString out_dir_for_snippet = out_dir + "/" + grammar_filenames[grammar_id];	// images/01, images/02, ...
		if (!QDir(out_dir_for_snippet).exists()) QDir().mkdir(out_dir_for_snippet);

		QFile file(out_dir_for_snippet + "/parameters.txt");
		if (!file.open(QIODevice::WriteOnly)) {
			std::cerr << "Cannot open file for writing: " << qPrintable(file.errorString()) << std::endl;
			return;
		}
		QTextStream out(&file);

		cv::Mat meanImg;
		if (grayscale) {
			meanImg = cv::Mat(image_size, image_size, CV_64F, cv::Scalar(0));
		}
		else {
			meanImg = cv::Mat(image_size, image_size, CV_64FC3, cv::Scalar(0, 0, 0));
		}

		// show the progress
		printf("Grammar #%d:", grammar_id + 1);
	
		for (int yrot = yrotRange.first; yrot <= yrotRange.second; yrot += yrotSample) {
			for (int xrot = xrotRange.first; xrot <= xrotRange.second; xrot += xrotSample) {
				for (int zrot = zrotRange.first; zrot <= zrotRange.second; zrot += zrotSample) {
					for (int fov = fovRange.first; fov <= fovRange.second; fov += fovSample) {
						float cameraDistance = cameraDistanceBase / tanf((float)fov * 0.5 / 180.0f * M_PI);

						camera.xrot = xrot;
						camera.yrot = yrot;
						camera.zrot = zrot;
						if (camera_type == 0) {
							camera.pos.x = 0;
							camera.pos.y = -cameraDistance * sinf(camera.xrot / 180.0f * M_PI) + cameraHeight * cosf(camera.xrot / 180.0f * M_PI);
							camera.pos.z = cameraDistance * cosf(camera.xrot / 180.0f * M_PI) + cameraHeight * sinf(camera.xrot / 180.0f * M_PI);
						}
						else {
							camera.pos = glm::vec3(0, 0, cameraDistance);
						}
						camera.fovy = fov;
						camera.updatePMatrix(width(), height());

						// randomly sample N parameter values
						for (int k = 0; k < numSamples; ++k) {
							printf("\rGrammar %s: count = %d", grammar_filenames[grammar_id].toUtf8().constData(), count + 1);

							std::vector<float> param_values;
							param_values = cga.randomParamValues(grammars[grammar_id]);

							// set axiom
							boost::shared_ptr<cga::Shape> start = boost::shared_ptr<cga::Shape>(new cga::Rectangle("Start", "", glm::translate(glm::rotate(glm::mat4(), -3.141592f * 0.5f, glm::vec3(1, 0, 0)), glm::vec3(0, 0, 0)), glm::mat4(), 0, 0, glm::vec3(1, 1, 1)));
							cga.stack.push_back(start);

							// generate 3d model
							cga.derive(grammars[grammar_id], true);
							std::vector<boost::shared_ptr<glutils::Face> > faces;
							renderManager.removeObjects();
							cga.generateGeometry(faces, centering);
							renderManager.addFaces(faces, true);

							// render 2d image
							render();
							QImage img = grabFrameBuffer();
							cv::Mat mat = cv::Mat(img.height(), img.width(), CV_8UC4, img.bits(), img.bytesPerLine()).clone();
							cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);

							// translate the image to the center
							if (centering) {
								if (!moveCenter(mat)) continue;
								//moveCenter(mat);
							}

							if (modifyImage) {
								// extract contour vectors
								std::vector<std::pair<glm::vec2, glm::vec2>> contour;
								utils::extractEdges(mat, contour);

								// add noise
								if (edgeNoise) {
									for (int ci = 0; ci < contour.size(); ++ci) {
										contour[ci].first.x += round(utils::genRand(-width() * edgeNoiseMax * 0.01f, width() * edgeNoiseMax * 0.01f));
										contour[ci].first.y += round(utils::genRand(-height() * edgeNoiseMax * 0.01f, height() * edgeNoiseMax * 0.01f));
										contour[ci].second.x += round(utils::genRand(-width() * edgeNoiseMax * 0.01f, width() * edgeNoiseMax * 0.01f));
										contour[ci].second.y += round(utils::genRand(-height() * edgeNoiseMax * 0.01f, height() * edgeNoiseMax * 0.01f));
									}
								}

								// 画像を縮小
								glm::vec2 scale((float)image_size / width(), (float)image_size / height());
								for (int ci = 0; ci < contour.size(); ++ci) {
									contour[ci].first.x *= scale.x;
									contour[ci].first.y *= scale.y;
									contour[ci].second.x *= scale.x;
									contour[ci].second.y *= scale.y;
								}

								// generate the rendered image
								cv::Scalar color;
								if (grayscale) {
									mat = cv::Mat(image_size, image_size, CV_8U, cv::Scalar(255));
									color = cv::Scalar(0);
								}
								else {
									mat = cv::Mat(image_size, image_size, CV_8UC3, cv::Scalar(255, 255, 255));
									color = cv::Scalar(0, 0, 0);
								}
								for (int ci = 0; ci < contour.size(); ++ci) {
									int lineWidth = utils::genIntRand(lineWidthMin, lineWidthMax);
									cv::line(mat, cv::Point(contour[ci].first.x, contour[ci].first.y), cv::Point(contour[ci].second.x, contour[ci].second.y), color, lineWidth, cv::LINE_AA);
								}
							}
							else {
								// 画像を縮小
								utils::resizeImage(mat, cv::Size(image_size, image_size));

								if (grayscale) {
									cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
								}
							}

							// create the subfolder
							int subfolder_idx = count / 100000;
							QString subfolder_name = QString("%1").arg(subfolder_idx, 3, 10, QChar('0'));
							QString subfolder_path = out_dir_for_snippet + "/" + subfolder_name;
							if (!QDir(subfolder_path).exists()) QDir().mkdir(subfolder_path);	// images/01/000, images/01/001, ...

							// save an image to a file
							QString filename = subfolder_path + "/" + QString("%1.png").arg(count, 6, 10, QChar('0'));
							cv::imwrite(filename.toUtf8().constData(), mat);

							// add camera parameters to the params
							if (fovRange.first != fovRange.second) {
								param_values.insert(param_values.begin(), (float)(fov - fovRange.first) / (fovRange.second - fovRange.first));
							}
							if (zrotRange.first != zrotRange.second) {
								param_values.insert(param_values.begin(), (float)(zrot - zrotRange.first) / (zrotRange.second - zrotRange.first));
							}
							if (yrotRange.first != yrotRange.second) {
								param_values.insert(param_values.begin(), (float)(yrot - yrotRange.first) / (yrotRange.second - yrotRange.first));
							}
							if (xrotRange.first != xrotRange.second) {
								param_values.insert(param_values.begin(), (float)(xrot - xrotRange.first) / (xrotRange.second - xrotRange.first));
							}

							// write all the param values [xrot, yrot, zrot, fov, param1, param2, ...] to the file
							outputVector(out, param_values);

							// update mean image
							if (generateMean) {
								if (grayscale) {
									mat.convertTo(mat, CV_64F);
								}
								else {
									mat.convertTo(mat, CV_64FC3);
								}
								meanImg += mat;
							}

							count++;
						}
					}
				}
			}
		}

		if (generateMean) {
			// generate mean image
			meanImg /= count;
			if (grayscale) {
				meanImg.convertTo(meanImg, CV_8U);
			}
			else {
				meanImg.convertTo(meanImg, CV_8UC3);
			}

			// save the mean image to a file
			QFile file(out_dir_for_snippet + "/parameters.txt");
			QString filename = out_dir_for_snippet + "/mean.png";
			cv::imwrite(filename.toUtf8().constData(), meanImg);
		}

		file.close();
		printf("\n");
	}

	resize(origWidth, origHeight);
	resizeGL(origWidth, origHeight);

	std::cout << "Training images were successfully generated." << std::endl;
}

void GLWidget3D::parameterEstimation(const QString& cga_dir, const QString& testdata_dir, const QString& regression_dir, const QString& output_dir, bool centering, bool subtract_mean, int camera_type, float cameraDistanceBase, float cameraHeight, const std::pair<int, int>& xrotRange, const std::pair<int, int>& yrotRange, const std::pair<int, int>& zrotRange, const std::pair<int, int>& fovRange) {
	int origWidth = width();
	int origHeight = height();
	resize(512, 512);
	resizeGL(512, 512);

	// setup grammars
	std::vector<cga::Grammar> grammars;
	QStringList filters;
	filters << "*.xml";
	QFileInfoList fileInfoList = QDir(cga_dir).entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);
	for (int i = 0; i < fileInfoList.size(); ++i) {
		cga::Grammar grammar;
		cga::parseGrammar(fileInfoList[i].absoluteFilePath().toUtf8().constData(), grammar);
		grammars.push_back(grammar);
	}

	// load pretrained models
	std::vector<Regression*> regressions(grammars.size());
	for (int i = 0; i < regressions.size(); ++i) {
		QString deploy_name = regression_dir + QString("/model/deploy_%1.prototxt").arg(i + 1, 2, 10, QChar('0'));
		QString model_name = regression_dir + QString("/model/train_%1_iter_80000.caffemodel").arg(i + 1, 2, 10, QChar('0'));
		regressions[i] = new Regression(deploy_name.toUtf8().constData(), model_name.toUtf8().constData());
		std::cout << "Model: " << model_name.toUtf8().constData() << std::endl;
		std::cout << "deploy file: " << deploy_name.toUtf8().constData() << std::endl;
	}

	// read the ground truth of parameter values
	std::map<int, std::vector<std::vector<float>>> params_truth;
	for (int i = 0; i < regressions.size(); ++i) {
		params_truth[i] = std::vector<std::vector<float>>();

		QFile file_true_params(testdata_dir + QString("/images/%1/parameters.txt").arg(i + 1, 2, 10, QChar('0')));
		file_true_params.open(QIODevice::ReadOnly);
		QTextStream in_true_params(&file_true_params);
		while (!in_true_params.atEnd()) {
			QString line = in_true_params.readLine();
			if (line.isEmpty()) break;

			QStringList strs = line.split(",");
			std::vector<float> values;
			for (auto str : strs) {
				values.push_back(str.toFloat());
			}

			params_truth[i].push_back(values);
		}
	}

	std::map<int, std::vector<float>> rmse;
	std::map<int, int> rmse_count;

	for (int grammar_id = 0; grammar_id < grammars.size(); ++grammar_id) {
		printf("Grammar #%d:", grammar_id + 1);

		// read mean image
		cv::Mat mean_img;
		if (subtract_mean) {
			mean_img = cv::imread((testdata_dir + QString("/images/%1/mean.png").arg(grammar_id + 1, 2, 10, QChar('0'))).toUtf8().constData());
			mean_img.convertTo(mean_img, CV_32F);
		}

		// open the output file for the predicted parameter values
		QFile file_predicted_params(output_dir + QString("/predicted_params_%1.txt").arg(grammar_id + 1, 2, 10, QChar('0')));
		if (!file_predicted_params.open(QIODevice::WriteOnly)) {
			std::cout << "ERROR: can't open " << file_predicted_params.fileName().toUtf8().constData() << std::endl;
			return;
		}
		QTextStream out_predicted_param(&file_predicted_params);

		int iter = 0;

		// open test data
		QFile file_testdata(testdata_dir + QString("/test_%1.txt").arg(grammar_id + 1, 2, 10, QChar('0')));
		file_testdata.open(QIODevice::ReadOnly);
		QTextStream in_testdata(&file_testdata);

		while (!in_testdata.atEnd()) {
			printf("\rGrammar #%d: %d", grammar_id + 1, iter + 1);

			QString line = in_testdata.readLine();
			if (line.isEmpty()) break;
			QString file_path = line.split(" ")[0];
			int file_id = line.split(" ")[1].toInt();

			// read the test image
			cv::Mat img = cv::imread((testdata_dir + QString("/images/%1/").arg(grammar_id + 1, 2, 10, QChar('0')) + file_path).toUtf8().constData());

			moveCenter(img);

			cv::Mat input_img = img.clone();
			input_img.convertTo(input_img, CV_32F);
			if (subtract_mean) {
				input_img -= mean_img;
			}

			// parameter estimation
			std::vector<float> predicted_params;
			predicted_params = regressions[grammar_id]->Predict(input_img);
			for (int i = 0; i < predicted_params.size(); ++i) {
				if (i > 0) out_predicted_param << ",";
				out_predicted_param << predicted_params[i];
			}
			out_predicted_param << "\n";

			// 誤差を計算
			if (rmse[grammar_id].size() == 0) {
				rmse[grammar_id].resize(predicted_params.size(), 0);
				rmse_count[grammar_id] = 0;
			}
			for (int i = 0; i < predicted_params.size(); ++i) {
				rmse[grammar_id][i] += SQR(params_truth[grammar_id][file_id][i] - predicted_params[i]);
			}
			rmse_count[grammar_id]++;
			
			// predictedカメラパラメータをセット
			if (xrotRange.first != xrotRange.second) {
				camera.xrot = xrotRange.first + (xrotRange.second - xrotRange.first) * predicted_params[0];
				predicted_params.erase(predicted_params.begin());
			}
			else {
				camera.xrot = xrotRange.first;
			}
			if (yrotRange.first != yrotRange.second) {
				camera.yrot = yrotRange.first + (yrotRange.second - yrotRange.first) * predicted_params[0];
				predicted_params.erase(predicted_params.begin());
			}
			else {
				camera.yrot = yrotRange.first;
			}
			if (zrotRange.first != zrotRange.second) {
				camera.zrot = zrotRange.first + (zrotRange.second - zrotRange.first) * predicted_params[0];
				predicted_params.erase(predicted_params.begin());
			}
			else {
				camera.zrot = zrotRange.first;
			}
			if (fovRange.first != fovRange.second) {
				camera.fovy = fovRange.first + (fovRange.second - fovRange.first) * predicted_params[0];
				predicted_params.erase(predicted_params.begin());
			}
			float cameraDistance = cameraDistanceBase / tanf(camera.fovy * 0.5 / 180.0f * M_PI);
			if (camera_type == 0) {
				camera.pos.x = 0;
				camera.pos.y = -cameraDistance * sinf(camera.xrot / 180.0f * M_PI) + cameraHeight * cosf(camera.xrot / 180.0f * M_PI);
				camera.pos.z = cameraDistance * cosf(camera.xrot / 180.0f * M_PI) + cameraHeight * sinf(camera.xrot / 180.0f * M_PI);
			}
			else {
				camera.pos = glm::vec3(0, 0, cameraDistance);
			}
			camera.updatePMatrix(width(), height());

			// predictdパラメータをセット
			cga.setParamValues(grammars[grammar_id], predicted_params);

			// set axiom
			boost::shared_ptr<cga::Shape> start = boost::shared_ptr<cga::Shape>(new cga::Rectangle("Start", "", glm::translate(glm::rotate(glm::mat4(), -3.141592f * 0.5f, glm::vec3(1, 0, 0)), glm::vec3(0, 0, 0)), glm::mat4(), 0, 0, glm::vec3(1, 1, 1)));
			cga.stack.push_back(start);

			// generate 3d model
			cga.derive(grammars[grammar_id], true);
			std::vector<boost::shared_ptr<glutils::Face> > faces;
			renderManager.removeObjects();
			cga.generateGeometry(faces, centering);
			renderManager.addFaces(faces, true);

			// render 2d image
			render();
			QImage rendered_img = grabFrameBuffer();
			cv::Mat predicted_img = cv::Mat(rendered_img.height(), rendered_img.width(), CV_8UC4, rendered_img.bits(), rendered_img.bytesPerLine()).clone();
			cv::cvtColor(predicted_img, predicted_img, cv::COLOR_BGRA2BGR);

			// translate the image to the center
			if (centering) moveCenter(predicted_img);

			// resize the image
			utils::resizeImage(predicted_img, img.size());

			// make the predicted image blue
			utils::blueImage(predicted_img);

			// blend the prediction and the input image
			utils::blendImages(predicted_img, img, cv::Scalar(255, 255, 255));

			//cv::imwrite((output_dir + QString("/%1_%2_input.png").arg(grammar_id, 2, 10, QChar('0')).arg(iter, 2, 10, QChar('0'))).toUtf8().constData(), img);
			cv::imwrite((output_dir + QString("/%1_%2_pred.png").arg(grammar_id, 2, 10, QChar('0')).arg(iter, 6, 10, QChar('0'))).toUtf8().constData(), predicted_img);

			iter++;
		}

		printf("\n");
		file_predicted_params.close();
	}
	
	// 誤差を計算
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Parameter estimation RMSE:" << std::endl;
	for (int i = 0; i < rmse.size(); ++i) {
		std::cout << "Grammar #" << i + 1 << ":" << std::endl;
		for (int j = 0; j < rmse[i].size(); ++j) {
			if (j > 0) std::cout << ", ";
			rmse[i][j] = sqrt(rmse[i][j] / rmse_count[i]);
			std::cout << rmse[i][j];
		}
		std::cout << std::endl;
	}
	
	resize(origWidth, origHeight);
	resizeGL(origWidth, origHeight);

	for (int i = 0; i < regressions.size(); ++i) {
		delete regressions[i];
	}
}

bool GLWidget3D::moveCenter(cv::Mat& img) {
	bool scan_r = false;
	int min_r = -1;
	int max_r = -1;
	for (int r = 0; r < img.rows; ++r) {
		for (int c = 0; c < img.cols; ++c) {
			cv::Vec3b color = img.at<cv::Vec3b>(r, c);

			if (color[0] < 100 && color[1] < 100 && color[2] < 100) {
				if (!scan_r) {
					min_r = r;
					max_r = r;
					scan_r = true;
				}
				else {
					max_r = r;
				}
			}
		}
	}

	bool scan_c = false;
	int min_c = -1;
	int max_c = -1;
	for (int c = 0; c < img.rows; ++c) {
		for (int r = 0; r < img.cols; ++r) {
			cv::Vec3b color = img.at<cv::Vec3b>(r, c);

			if (color[0] < 100 && color[1] < 100 && color[2] < 100) {
				if (!scan_c) {
					min_c = c;
					max_c = c;
					scan_c = true;
				}
				else {
					max_c = c;
				}
			}
		}
	}
	
	bool acrossBoundary = false;

	// if there is no image, no translation is necessary.
	if (min_r == -1 || min_c == -1) return true;

	// if the image is not strictly inside the canvas, set the flag.
	if (min_r == 0 || min_c == 0 || max_r == img.rows - 1 || max_c == img.cols - 1) acrossBoundary = true;

	// translate the image
	int offset_c = img.cols * 0.5 - (min_c + max_c) * 0.5;
	int offset_r= img.rows * 0.5 - (min_r + max_r) * 0.5;
	utils::translateImage(img, offset_c, offset_r);

	return !acrossBoundary;
}

void GLWidget3D::translateImage(cv::Mat source, cv::Mat& target, int shift_x, int shift_y) {
	target = cv::Mat(source.size(), source.type(), cv::Scalar(255, 255, 255));
	
	for (int r = 0; r < target.rows; ++r) {
		for (int c = 0; c < target.cols; ++c) {
			if (c - shift_x < 0 || c - shift_x >= source.cols) continue;
			else if (r - shift_y < 0 || r - shift_y >= source.rows) continue;
			else {
				cv::Vec3b color = source.at<cv::Vec3b>(r - shift_y, c - shift_x);
				target.at<cv::Vec3b>(r, c) = color;
			}
		}
	}
}

void GLWidget3D::keyPressEvent(QKeyEvent *e) {
	shiftPressed = false;

	switch (e->key()) {
	case Qt::Key_Shift:
		shiftPressed = true;
		break;
	default:
		break;
	}
}

void GLWidget3D::keyReleaseEvent(QKeyEvent* e) {
	shiftPressed = false;
}

void GLWidget3D::outputVector(QTextStream& out, const std::vector<float>& values) {
	for (int i = 0; i < values.size(); ++i) {
		if (i > 0) out << ",";
		out << values[i];
	}
	out << "\n";
}