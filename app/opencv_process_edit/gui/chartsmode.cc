#pragma execution_character_set("utf-8")

#include "chartsmode.h"
#include "cwidgets.h"
#include "qcanpool/minisplitter.h"
#include "qcanpool/ministack.h"
#include "qcanpool/tinytabwidget.h"

#include "cwidgets.h"
#include "ctablewidget.h"
#include "qcustomplot.h"

ChartsMode::ChartsMode(QWidget* parent)
  : FancyMode(parent)
{
  setObjectName(QLatin1String("ChartsMode"));
  setDisplayName(tr("Charts"));
  setIcon(QIcon(":/mode/chart"));

  force_plot_ = new QCustomPlot();
  force_plot_->addGraph();
  force_plot_->graph(0)->setName("fron");
  force_plot_->graph(0)->setPen(QPen(Qt::red));

  force_plot_->addGraph();
  force_plot_->graph(1)->setName("back");
  force_plot_->graph(1)->setPen(QPen(Qt::yellow));
  force_plot_->addGraph();
  force_plot_->graph(2)->setName("left");
  force_plot_->graph(2)->setPen(QPen(Qt::blue));
  force_plot_->addGraph();
  force_plot_->graph(3)->setName("right");
  force_plot_->graph(3)->setPen(QPen(Qt::green));
  force_plot_->xAxis->setLabel("Time(s)");
  force_plot_->yAxis->setLabel("N/m");

  QPen pen;
  pen.setColor(Qt::black);//���̶Ⱥ�ɫ
  pen.setWidth(2);//�߿�2
  force_plot_->xAxis->setTickPen(pen);
  force_plot_->xAxis->setTickLengthIn(10);//���̶���������30
  force_plot_->xAxis->setTickLengthOut(0);//���̶���������10
  pen.setColor(Qt::black);
  force_plot_->xAxis->setSubTickPen(pen);
  force_plot_->xAxis->setSubTickLengthIn(5);//�ӿ̶���������15
  force_plot_->xAxis->setSubTickLengthOut(0);//�ӿ̶���������5

  force_plot_->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);//x���յ��ͷͼ��
  force_plot_->xAxis->setLowerEnding(QCPLineEnding::esDisc);//x�����Բ��ͼ��
  force_plot_->yAxis->setUpperEnding(QCPLineEnding::esSquare);//y���յ�С����ͼ��

  lmu_plot_ = new QCustomPlot();

  createWindow();
}

void ChartsMode::createWindow()
{
  MiniStack* stack1 = new MiniStack();
  stack1->setTitle(tr("Force(����)"));
  stack1->setTitleMargins(5, 1, 5, 1);
  stack1->addTab(tr("Force(����)"), force_plot_);

  MiniStack* stack3 = new MiniStack();
  stack3->setTitle(tr("LMU(������)"));
  stack3->setTitleMargins(5, 1, 5, 1);
  stack3->addTab(tr("LMU(������)"), lmu_plot_);

  QHBoxLayout* pStackLayout_1 = new QHBoxLayout();
  pStackLayout_1->setContentsMargins(10, 5, 10, 5);
  pStackLayout_1->setSpacing(10);
  pStackLayout_1->addWidget(stack1);

  QHBoxLayout* pStackLayout_2 = new QHBoxLayout();
  pStackLayout_2->setContentsMargins(10, 5, 10, 5);
  pStackLayout_2->setSpacing(10);
  pStackLayout_2->addWidget(stack3);

  /////////////////
  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addLayout(pStackLayout_1);
  layout->addLayout(pStackLayout_2);
  //layout->addStretch();
  QWidget* w = new QWidget();
  w->setLayout(layout);

  setWidget(w);
}


void ChartsMode::SetForceData(float key, float frot, float back, float left, float right)
{
  force_plot_->graph(0)->addData(key, frot);
  force_plot_->graph(1)->addData(key, back);
  force_plot_->graph(2)->addData(key, left);
  force_plot_->graph(3)->addData(key, right);

  force_plot_->rescaleAxes();
  force_plot_->xAxis->setRange(key + 3, 16.0, Qt::AlignRight);
  force_plot_->replot();
}
