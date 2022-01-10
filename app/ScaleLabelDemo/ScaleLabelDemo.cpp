#include "ScaleLabelDemo.h"
#include <QImage>
#include "MyLabel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>

ScaleLabelDemo::ScaleLabelDemo(QWidget *parent)
	: QMainWindow(parent)
{
	m_pCenterWgt = new QWidget(this);
	m_pMyLabel = new MyLabel(this);
	m_pOpenBtn = new QPushButton("Open", this);

	connect(m_pOpenBtn, &QPushButton::clicked, this, &ScaleLabelDemo::openImage);

	QVBoxLayout *mainLayout = new QVBoxLayout;

	mainLayout->addWidget(m_pOpenBtn);
	mainLayout->addWidget(m_pMyLabel);
	mainLayout->addStretch();
	m_pCenterWgt->setLayout(mainLayout);

	this->setCentralWidget(m_pCenterWgt);
	this->resize(800, 600);
}

void ScaleLabelDemo::openImage()
{
	QString fileName = QFileDialog::getOpenFileName(this, "open", QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "image (*.bmp *.png *.jpg)");

	if (fileName.isEmpty())
	{
		return;
	}

	QImage image(fileName);
	m_pMyLabel->setBackImage(image);
}