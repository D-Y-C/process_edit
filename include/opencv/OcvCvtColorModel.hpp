#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvCvtColorModel : public OcvBaseNode
{
  Q_OBJECT

 public:
  OcvCvtColorModel();
  ~OcvCvtColorModel(){};

  QString caption() const override { return QString("Cvt Color"); }
  QString name() const override { return QString("OcvCvtColorModel"); }
  virtual QString modelName() const { return QString("CvtColor"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void CvtColor(cv::Mat& src, cv::Mat& dst);

 private:
  cv::Mat* mat_;
};
