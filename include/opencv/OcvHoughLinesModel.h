#pragma once

#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvHoughLinesModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  OcvHoughLinesModel();

  QString caption() const override { return QString("HoughLines"); }
  QString name() const override { return QString("HoughLinesModel"); }
  virtual QString modelName() const { return QString("OcvHoughLinesModel"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void HoughLines(cv::Mat &src, cv::Mat &dst);

  cv::Mat *mat_;
};
