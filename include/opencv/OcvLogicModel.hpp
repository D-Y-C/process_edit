#pragma once

#include "OcvBaseNode.hpp"
#include "OcvData.hpp"

enum class OcvLogicOpration
{
  Add,
  Mask
};

class OcvLogicModel : public OcvBaseNode
{
  Q_OBJECT

 public:
  OcvLogicModel();
  virtual ~OcvLogicModel() {}
  QString caption() const override { return QString("Logic"); }
  QString name() const override { return QString("OcvLogicModel"); }
  virtual QString modelName() const { return QString("OcvLogic"); }
  void process();
  std::shared_ptr<NodeData> outData(PortIndex idx) override;

 private:
  void Logic(cv::Mat& bg,cv::Mat& mask, cv::Mat& dst, OcvLogicOpration op,eIXY& offset);
  void Add(cv::Mat& bg, cv::Mat& mask,cv::Mat& dst, int offset_x, int offset_y);
 private:
  cv::Mat* mat_;
};
