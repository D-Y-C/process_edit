#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvBlurModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvBlurModel();
  ~OcvBlurModel(){};

  QString caption() const override { return QString("Blur"); }
  QString name() const override { return QString("OcvBlurModel"); }
  virtual QString modelName() const { return QString("OcvBlur"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Blur(cv::Mat& src, cv::Mat& dst, cv::Size& kel_size);

 private:
  cv::Mat* mat_;
};
