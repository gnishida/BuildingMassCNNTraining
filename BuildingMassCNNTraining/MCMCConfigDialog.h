#ifndef MCMCCONFIGDIALOG_H
#define MCMCCONFIGDIALOG_H

#include <QDialog>
#include "ui_MCMCConfigDialog.h"

class MCMCConfigDialog : public QDialog {
	Q_OBJECT

public:
	Ui::MCMCConfigDialog ui;

public:
	MCMCConfigDialog(QWidget *parent = 0);
	~MCMCConfigDialog();

public slots:
	void onCGAFilename();
	void onTargetFilename();
	void onStart();
	void onCancel();
};

#endif // MCMCCONFIGDIALOG_H
