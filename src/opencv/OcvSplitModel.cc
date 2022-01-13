/*
 * @description: Opencv Inpaint model
 * @author: Yongchang Dong
 */

#include "OcvSplitModel.h"
#include <OcvData.hpp>
#include <QDebug>
#include <QString>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <memory>

OcvSplitModel::OcvSplitModel()
{
  /* input */
  _inputs.push_back(
      new ePort(PortType::In, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("G"), NodeClassMat));

  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("B"), NodeClassMat));

  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("R"), NodeClassMat));

  /* parameter */
  addParameter<int>(EPT_ENUM, "Type", 0, 2, 0);
  _parameters.back()->setDescription("BGR|HVS");

  cv::Mat mat;
  mat_.push_back(mat);
  mat_.push_back(mat);
  mat_.push_back(mat);
}

void OcvSplitModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      Split(mat, mat_);
      dataUpdated(0);
      dataUpdated(1);
      dataUpdated(2);
    }
  }
}

std::shared_ptr<NodeData> OcvSplitModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(&mat_[idx]);
}

void OcvSplitModel::Split(cv::Mat& src, std::vector<cv::Mat>& dst)
{
  int type = getParameter("Type")->getValueAsEnum();

  if (src.channels() == 3) {
    /* BGR */
    if (type == 0) {
      cv::split(src, dst);
      /* Set visible string */
      _outputs[0]->name = "G";
      _outputs[1]->name = "B";
      _outputs[2]->name = "R";
    } else {
      cv::cvtColor(src, src, cv::COLOR_BGR2HSV);
      cv::split(src, dst);
      /* Set visible string */
      _outputs[0]->name = "H";
      _outputs[1]->name = "S";
      _outputs[2]->name = "V";
    }
  } else {
    dst[0] = src;
    dst[1] = src;
    dst[2] = src;
  }
}
