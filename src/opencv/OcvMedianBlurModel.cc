#include "OcvMedianBlurModel.hpp"

using namespace cv;

OcvMedianBlurModel::OcvMedianBlurModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<int>(EPT_INT, "kernel size", 0, 1000, 3);

  mat_ = new Mat();
}

void OcvMedianBlurModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      MedianBlur(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvMedianBlurModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvMedianBlurModel::MedianBlur(Mat& src, Mat& dst)
{
  int kel_size = getParameter("kernel size")->getValueAsInt();

  try {
    Mat tmp_mat;
    cv::medianBlur(src, dst,kel_size);
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
