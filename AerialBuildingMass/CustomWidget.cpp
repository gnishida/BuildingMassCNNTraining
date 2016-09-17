#include "CustomWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QWidget>
#include "MainWindow.h"
#include <iostream>

CustomWidget::CustomWidget(QWidget *parent, const QString& text, const QImage& image, int option_index) : QLabel(parent) {
	mainWin = (MainWindow*)parent;
	this->option_index = option_index;

	connect(this, SIGNAL(clicked(int)), this, SLOT(onClicked(int)));

	this->setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);

	QImage img = image;

	QPainter painter(&img);
	painter.setPen(Qt::blue);
	painter.setFont(QFont("Arial", 20));
	painter.drawText(image.rect(), Qt::AlignHCenter | Qt::AlignBottom, text);

	this->setPixmap(QPixmap::fromImage(img));
	this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void CustomWidget::mousePressEvent(QMouseEvent* e) {
	emit clicked(option_index);
}

void CustomWidget::onClicked(int option_index) {
	mainWin->getGLWidget()->selectOption(option_index);
}