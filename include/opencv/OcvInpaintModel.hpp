/*
 * @description: Opencv Inpaint model
 * @author: Yongchang Dong
 */

#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvInpaintModel : public OcvBaseNode
{
  Q_OBJECT

 public:
  OcvInpaintModel();
  ~OcvInpaintModel(){};

  QString caption() const override { return QString("Inpaint"); }
  QString name() const override { return QString("InpaintModel"); }
  virtual QString modelName() const { return QString("OcvInpaintModel"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Inpaint(cv::Mat& src, cv::Mat& dst);

 private:
  cv::Mat* mat_;
};
