#pragma once

#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class OcvThresholdModel : public OcvBaseNode
{
  Q_OBJECT

 public:
  OcvThresholdModel();

  virtual ~OcvThresholdModel() {}

  QString caption() const override { return QString("Threshold"); }

  QString name() const override { return QString("OcvThresholdModel"); }

  virtual QString modelName() const { return QString("OcvThreshold"); }

  void process();

  std::shared_ptr<NodeData> outData(PortIndex idx) override;

private:
  void OcvThresholdModel::SumRgb(const cv::Mat &src, cv::Mat &dst);

  void Threshold(const cv::Mat &source, cv::Mat &dst);

 private: 
  cv::Mat* mat_;
};
