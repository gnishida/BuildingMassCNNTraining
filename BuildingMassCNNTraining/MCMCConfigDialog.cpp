#include "MCMCConfigDialog.h"
#include <QFileDialog>

MCMCConfigDialog::MCMCConfigDialog(QWidget *parent) : QDialog(parent) {
	ui.setupUi(this);

	ui.lineEditIterations->setText("300");

	connect(ui.pushButtonCGAFilename, SIGNAL(clicked()), this, SLOT(onCGAFilename()));
	connect(ui.pushButtonTargetFilename, SIGNAL(clicked()), this, SLOT(onTargetFilename()));
	connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(onStart()));
	connect(ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
}

MCMCConfigDialog::~MCMCConfigDialog() {

}

void MCMCConfigDialog::onCGAFilename() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open CGA file..."), "", tr("CGA Files (*.xml)"));
	if (filename.isEmpty()) return;

	ui.lineEditCGAFilename->setText(filename);
}

void MCMCConfigDialog::onTargetFilename() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open image file..."), "", tr("Image Files (*.png)"));
	if (filename.isEmpty()) return;

	ui.lineEditTargetFilename->setText(filename);
}

void MCMCConfigDialog::onStart() {
	accept();
}

void MCMCConfigDialog::onCancel() {
	reject();
}