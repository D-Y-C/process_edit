/*
 * @description: Opencv Inpaint model
 * @author: Yongchang Dong
 */
#include "OcvEqualizeHistModel.h"

OcvEqualizeHistModel::OcvEqualizeHistModel()
{
  /* Input */
  _inputs.push_back(
      new ePort(PortType::In, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  mat_ = new cv::Mat();
}

OcvEqualizeHistModel::~OcvEqualizeHistModel() {}

std::shared_ptr<NodeData> OcvEqualizeHistModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvEqualizeHistModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());
  if (ocv_data) {
    cv::Mat* mat = ocv_data->GetData();
    if (!mat->empty()) {
      EqualizeHistModel(*(ocv_data->GetData()), *mat_);

      dataUpdated(0);
    }
  }
}
void OcvEqualizeHistModel::EqualizeHistModel(const cv::Mat& src, cv::Mat& dst)
{
  try {
    cv::Mat img_hsv;
    // cv::cvtColor(src, img_hsv, cv::COLOR_BGR2HSV);
    std::vector<cv::Mat> hsv_split;
    cv::split(src, hsv_split);
    cv::equalizeHist(hsv_split[0], hsv_split[0]);
    cv::equalizeHist(hsv_split[1], hsv_split[1]);
    cv::equalizeHist(hsv_split[2], hsv_split[2]);
    cv::merge(hsv_split, dst);
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
}
