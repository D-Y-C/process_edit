/*
 * @description: Opencv Canny model
 * @author: Yongchang Dong
 */

#include "OcvCannyModel.h"

QcvCannyModel::QcvCannyModel() : mat_(new cv::Mat)
{
  /* input */
  _inputs.push_back(
      new ePort(PortType::In, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));
  /* output */
  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));

  /* Parmas */
  addParameter<eF32>(EPT_FLOAT, "threshold1", 0, 255, 128);
  addParameter<eF32>(EPT_FLOAT, "threshold2", 0, 255, 200);
  addParameter<eInt>(EPT_INT, "aperture_size", 3, 7, 3);
}

QcvCannyModel::~QcvCannyModel() {}

void QcvCannyModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      Canny(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> QcvCannyModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void QcvCannyModel::Canny(cv::Mat& src, cv::Mat& dst)
{
  float threshold1 = getParameter("threshold1")->getValueAsFloat();
  float threshold2 = getParameter("threshold2")->getValueAsFloat();
  int apperture_size = getParameter("aperture_size")->getValueAsInt();

  try {
    apperture_size += apperture_size % 2 == 0 ? 1 : 0;

    cv::Canny(src, dst, threshold1, threshold2, apperture_size);
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
}
