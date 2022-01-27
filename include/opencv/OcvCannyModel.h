#pragma once

#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class QcvCannyModel : public OcvBaseNode
{
  Q_OBJECT
 public:
  QcvCannyModel();
  ~QcvCannyModel();

  QString caption() const override { return QString("Canny"); }
  QString name() const override { return QString("CannyModel"); }
  virtual QString modelName() const { return QString("OcvCannyModel"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Canny(cv::Mat &src, cv::Mat &dst);

  cv::Mat *mat_;
};