#include "OcvBlurModel.hpp"

using namespace cv;

OcvBlurModel::OcvBlurModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<eIXY>(EPT_IXY, "kernel size", 0, 100, eIXY(3, 3));

  mat_ = new Mat();
}

void OcvBlurModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      eIXY kel_size = getParameter("kernel size")->getValueAsIXY();
      Blur(mat, *mat_, cv::Size(kel_size.x, kel_size.y));
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvBlurModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvBlurModel::Blur(Mat& src, Mat& dst, cv::Size& kel_size)
{
  try {
    cv::blur(src, dst, kel_size);
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
