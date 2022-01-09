#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvMedianBlurModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvMedianBlurModel();
  ~OcvMedianBlurModel(){};

  QString caption() const override { return QString("Median Blur"); }
  QString name() const override { return QString("OcvMedianBlurModel"); }
  virtual QString modelName() const { return QString("OcvMedianBlur"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void MedianBlur(cv::Mat& src, cv::Mat& dst);

 private:
  cv::Mat* mat_;
};
