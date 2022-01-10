#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <iostream>
#include <nodes/DataModelRegistry>
#include <nodes/NodeDataModel>
#include "OcvData.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataModel;
using QtNodes::NodeDataType;
using QtNodes::NodeValidationState;
using QtNodes::PortIndex;
using QtNodes::PortType;

/* The model dictates the number of inputs and outputs for the Node.
 In this example it has no logic. */
class OcvShowModel : public NodeDataModel
{
  Q_OBJECT

 public:
  OcvShowModel();

  virtual ~OcvShowModel() {}

 public:
  QString caption() const override { return QString("Image Display"); }

  QString name() const override { return QString("OcvShowModel"); }

  std::shared_ptr<NodeData> outData(PortIndex port) override;
public slots:
  void SetImage(const QImage &image);

  void SetMat(const cv::Mat &mat);

public:
  virtual QString modelName() const { return QString("Resulting Image"); }

  unsigned int nPorts(PortType portType) const override;

  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

  void setInData(std::shared_ptr<NodeData> nodeData, PortIndex port) override;

  QWidget *embeddedWidget() override { return _label; }

  bool resizable() const override { return false; }

 protected:
  bool eventFilter(QObject *object, QEvent *event) override;

 private:

  QLabel* _label;

  cv::Mat* mat_;

  std::shared_ptr<NodeData> _nodeData;
};
