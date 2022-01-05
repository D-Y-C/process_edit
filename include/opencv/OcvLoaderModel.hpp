#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>

#include <opencv2\opencv.hpp> 
#include <OcvData.hpp>
#include "OcvBaseNode.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class OcvLoaderModel : public OcvBaseNode
{
  Q_OBJECT

public:
  OcvLoaderModel();

  virtual
  ~OcvLoaderModel() {}
  void process();

public:

  QString
  caption() const override
  { return QString("Load Image"); }

  QString
  name() const override { return QString("OcvLoaderModel"); }

public:

  virtual QString
  modelName() const
  { return QString("Source Image"); }

  void
  setInData(std::shared_ptr<NodeData>, int) override
  { }

  bool
  resizable() const override { return true; }

  std::shared_ptr<NodeData> outData(PortIndex port) override;

protected:
private:
  QPixmap _pixmap;

  cv::Mat* mat_;
};
