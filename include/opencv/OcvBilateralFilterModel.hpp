#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvBilateralFilterModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvBilateralFilterModel();
  ~OcvBilateralFilterModel(){};

  QString caption() const override { return QString("Bilateral Filter"); }
  QString name() const override { return QString("OcvBilateralFilterModel"); }
  virtual QString modelName() const { return QString("OcvBilateralFilter"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Mophology(cv::Mat& src, cv::Mat& dst);

 private:
  cv::Mat* mat_;
};
