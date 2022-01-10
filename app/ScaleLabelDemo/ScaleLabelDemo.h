#pragma once

#include <QtWidgets/QMainWindow>

class MyLabel;
class QPushButton;

class ScaleLabelDemo : public QMainWindow
{
	Q_OBJECT

public:
	ScaleLabelDemo(QWidget *parent = Q_NULLPTR);

private slots:
	void openImage();

private:
	MyLabel *m_pMyLabel;
	QWidget *m_pCenterWgt;
	QPushButton *m_pOpenBtn;
};
