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
  addParameter<eInt>(EPT_ENUM, "kernel type", 0, 255, 0);
  _parameters.back()->setDescription("rect|cross|ellipse");
  addParameter<eIXY>(EPT_IXY, "kernel size", 0, 10000, eIXY(3, 3));
  addParameter<eInt>(EPT_ENUM, "type", 0, 255, 0);
  _parameters.back()->setDescription("erode|dilate|open|close|gradient|tophat|blackhat|hitmiss");

  mat_ = new Mat();
}

void OcvMedianBlurModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      Mophology(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvMedianBlurModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvMedianBlurModel::Mophology(Mat& src, Mat& dst)
{
  int kel_type = getParameter("kernel type")->getValueAsEnum();
  eIXY kel_size = getParameter("kernel size")->getValueAsIXY();
  int type = getParameter("type")->getValueAsEnum();

  try {
    Mat tmp_mat;
    Mat kernel = getStructuringElement(kel_type, Size(kel_size.x, kel_size.y));
    morphologyEx(src, dst, type, kernel);
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
