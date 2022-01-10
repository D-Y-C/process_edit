/*
 * @description: Opencv Inpaint model
 * @author: Yongchang Dong
 */

#include "OcvInpaintModel.hpp"
#include <OcvData.hpp>
#include <QDebug>
#include <QString>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <memory>

OcvInpaintModel::OcvInpaintModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<float>(EPT_FLOAT, "Radius", 0, 255, 0);
  addParameter<int>(EPT_ENUM, "Flags", 0, 2, 0);
  _parameters.back()->setDescription("INPAINT_NS");
  _parameters.back()->setDescription("NPAINT_TELEA");

  mat_ = new cv::Mat();
}

void OcvInpaintModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      Inpaint(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvInpaintModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvInpaintModel::Inpaint(cv::Mat& src, cv::Mat& dst)
{
  cv::Mat result;

  double radius = getParameter("Radius")->getValueAsFloat();
  int flag = getParameter("Flags")->getValueAsInt();

  try {
    cv::Mat tmp_mat;

    cv::Mat image_gray;
    /* RGB to GRAY */
    cv::cvtColor(src, image_gray, cv::COLOR_RGB2GRAY, 0);
    cv::Mat image_mask = cv::Mat(src.size(), CV_8UC1, cv::Scalar::all(0));

    //通过阈值处理生成Mask
    cv::threshold(image_gray, image_mask, 240, 255, cv::THRESH_BINARY);
    cv::Mat Kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    //对Mask膨胀处理，增加Mask面积
    cv::dilate(image_mask, image_mask, Kernel);

    cv::inpaint(src, image_mask, dst, radius, flag);
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
