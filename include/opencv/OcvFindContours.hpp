#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvFindContoursModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvFindContoursModel();
  ~OcvFindContoursModel(){};

  QString caption() const override { return QString("Find Contours"); }
  QString name() const override { return QString("OcvFindContoursModel"); }
  virtual QString modelName() const { return QString("OcvFundContours"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void FindContours(cv::Mat& src, cv::Mat& dst, int mode, int method);

 private :
  cv::Mat* mat_;
};
