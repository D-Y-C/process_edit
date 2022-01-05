#include "OcvResizeModel.hpp"

using namespace cv;

OcvResizeModel::OcvResizeModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<eInt>(EPT_ENUM, "type", 0, 255, 0);
  _parameters.back()->setDescription("nearest|linear|cubic|area|lanczos4");
  addParameter<eIXY>(EPT_IXY, "size(x,y)", 0, 100000, eIXY(0, 0));
  addParameter<eFXY>(EPT_FXY, "scale(fx,fy)", 0, 10, eFXY(1.0f, 1.0f));
  
  mat_ = new Mat();
}

void OcvResizeModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      Resize(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvResizeModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvResizeModel::Resize(Mat& src, Mat& dst)
{
  int type = getParameter("type")->getValueAsEnum();
  eIXY size = getParameter("size(x,y)")->getValueAsIXY();
  eFXY scale = getParameter("scale(fx,fy)")->getValueAsFXY();

  if (size.x == 0 && size.y == 0 && scale.x == 0 && scale.y == 0) return;

  if (scale.x == 0 || scale.y == 0) return;

  try {
    Mat tmp_mat;
    cv::resize(src, dst, Size(size.y, size.x), scale.y, scale.x, type);
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
