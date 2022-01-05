#pragma once

#include "BaseNode.h"

enum CvDataType
{
  CvDataType_Mat = 0
};

static const NodeDataType CV_NODE_DATA_TYPE[] = {
    {"mat", "cv::mat"},
};

class OcvBaseNode : public BaseNode
{
  Q_OBJECT
 public:
  OcvBaseNode(){};

  virtual bool portCaptionVisible(PortType, PortIndex) const override { return false; }
  virtual bool resizable() const override { return true; }
};
