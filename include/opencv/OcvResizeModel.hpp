#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvResizeModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvResizeModel();
  ~OcvResizeModel(){};

  QString caption() const override { return QString("Resize"); }
  QString name() const override { return QString("OcvResizeModel"); }
  virtual QString modelName() const { return QString("CvtResize"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Resize(cv::Mat& src, cv::Mat& dst);

 private:
  cv::Mat* mat_;
};
