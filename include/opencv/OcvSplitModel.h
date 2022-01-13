#pragma once

#include <vector>
#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

class OcvSplitModel : public OcvBaseNode
{
  Q_OBJECT

 public:
  OcvSplitModel();
  ~OcvSplitModel(){};

  QString caption() const override { return QString("Split"); }
  QString name() const override { return QString("SplitModel"); }
  virtual QString modelName() const { return QString("OcvSplitModel"); }
  void process() override;
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Split(cv::Mat& src, std::vector<cv::Mat>& dst);

 private:
  std::vector<cv::Mat> mat_;
};
