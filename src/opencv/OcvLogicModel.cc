#include "OcvLogicModel.hpp"
#include <limits>

using namespace cv;

OcvLogicModel::OcvLogicModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  _inputs[0]->name = "backgroud";

  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  _inputs[1]->name = "mask";

  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<eInt>(EPT_ENUM, "operation", 0, 255, 0);
  _parameters.back()->setDescription("add|mask");
  addParameter<eIXY>(EPT_IXY, "offset(x,y)", 0, std::numeric_limits<int>::max(), eIXY(0, 0));

  mat_ = new Mat();
}

void OcvLogicModel::process()
{
  OcvData* bg_ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());
  OcvData* mask_ocv_data = dynamic_cast<OcvData*>(_inputs[1]->data.get());

  if (bg_ocv_data && mask_ocv_data) {
    Mat bg_mat = bg_ocv_data->GetData()->clone();
    Mat mask_mat = mask_ocv_data->GetData()->clone();

    if (!bg_mat.empty() && !mask_mat.empty()) {
      int op = getParameter("operation")->getValueAsEnum();
      eIXY offset = getParameter("offset(x,y)")->getValueAsIXY();
      Logic(bg_mat,mask_mat, *mat_, static_cast<OcvLogicOpration>(op), offset);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvLogicModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

/* dst image as backgound */
void OcvLogicModel::Logic(Mat& bg, Mat& mask, Mat& dst, OcvLogicOpration op, eIXY& offset)
{
  int max_rows = bg.rows;
  int max_cols = bg.cols;

  try {
    Mat tmp_mat;
    switch (op) {
      case OcvLogicOpration::Add:
        // cv::addWeighted(
        break;
      case OcvLogicOpration::Mask:
        break;
      default:
        break;
    }
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}

void OcvLogicModel::Add(cv::Mat& bg, cv::Mat& mask,cv::Mat& dst, int offset_x, int offset_y) 
{
  
}
