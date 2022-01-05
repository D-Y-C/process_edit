#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvGaussianBlurModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvGaussianBlurModel();
  ~OcvGaussianBlurModel(){};

  QString caption() const override { return QString("Gaussian Blur"); }
  QString name() const override { return QString("OcvGaussianBlurModel"); }
  virtual QString modelName() const { return QString("OcvBilateralBlur"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void GaussianBlur(cv::Mat& src, cv::Mat& dst, cv::Size& kel_size, double sigma_x, double sigma_y,int type);
 private:
  cv::Mat* mat_;
};
