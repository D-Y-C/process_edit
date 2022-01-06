#include "OcvThresholdModel.hpp"
#include <OcvData.hpp>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>
#include <memory>
#include <nodes/DataModelRegistry>
#include <vector>

OcvThresholdModel::OcvThresholdModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<eInt>(EPT_INT, "thresh", 0, 255, 128);
  addParameter<eInt>(EPT_INT, "max val", 0, 255, 255);
  addParameter<eInt>(EPT_ENUM, "type", 0, 255, 0);
  _parameters.back()->setDescription("binary|binary-inv|trunc|tozero|tozero-inv|mask|otsu");
  mat_ = new cv::Mat();
}

void OcvThresholdModel::Threshold(const cv::Mat& source, cv::Mat& dst)
{
  cv::Mat result;

  int thresh = getParameter("thresh")->getValueAsInt();
  int max_value = getParameter("max val")->getValueAsInt();
  int type = getParameter("type")->getValueAsEnum();

  try {
    /* sum rgb channel */
    cv::Mat sum_mat;
    SumRgb(source, sum_mat);
    /* threshold */
    cv::threshold(sum_mat, dst, thresh, max_value, type);
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}

void OcvThresholdModel::SumRgb(const cv::Mat& src, cv::Mat& dst)
{
  if (!src.empty()) {
    /* mat is 3 channels image */
    if (src.channels() == 3) {
      std::vector<cv::Mat> planes;
      /* split image onto the color planes. */
      cv::split(src, planes);
      cv::Mat b = planes[0], g = planes[1], r = planes[2], s;
      /* Add equally weighted rgb values. */
      cv::addWeighted(r, 1. / 3., g, 1. / 3., 0.0, s);
      cv::addWeighted(s, 1., b, 1. / 3., 0.0, s);
      dst = s;
    } else {
      dst = src;
    }
  }
  return;
}

void OcvThresholdModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();

    Threshold(mat, *mat_);

    dataUpdated(0);
  }
}

std::shared_ptr<NodeData> OcvThresholdModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}
