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

class OcvEqualizeHistModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvEqualizeHistModel();
  ~OcvEqualizeHistModel();

  QString caption() const override { return QString("Equalize Hist"); }
  QString name() const override { return QString("EqualizeHistModel"); }
  virtual QString modelName() const { return QString("OcvEqualizeHistModel"); }
  void process() override;

  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void EqualizeHistModel(const cv::Mat& src, cv::Mat& dst);

  cv::Mat* mat_;
};
