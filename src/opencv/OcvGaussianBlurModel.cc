#include "OcvGaussianBlurModel.hpp"

using namespace cv;

OcvGaussianBlurModel::OcvGaussianBlurModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  // set reflect_101 as default value
  addParameter<eInt>(EPT_ENUM, "border type", 0, 255, 4);
  _parameters.back()->setDescription("constant|replicate|reflect|wrap|reflect_101|transparent");
  addParameter<eIXY>(EPT_IXY, "kernel size", 0, 100, eIXY(3, 3));
  addParameter<eFXY>(EPT_FXY, "sigma(x,y)", 0, 100, eFXY(3, 0));

  mat_ = new Mat();
}

void OcvGaussianBlurModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      int type = getParameter("border type")->getValueAsEnum();
      eIXY kel_size = getParameter("kernel size")->getValueAsIXY();
      eFXY sigma = getParameter("sigma(x,y)")->getValueAsFXY();
      GaussianBlur(mat, *mat_,Size(kel_size.x,kel_size.y),sigma.x,sigma.y,type);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvGaussianBlurModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvGaussianBlurModel::GaussianBlur(
    Mat& src, Mat& dst, Size& kel_size, double sigma_x, double sigma_y, int type)
{
  if (kel_size.height % 2 == 0 || kel_size.width % 2 == 0) return;

  try {
    cv::GaussianBlur(src, dst, kel_size, sigma_x, sigma_y, type);
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
