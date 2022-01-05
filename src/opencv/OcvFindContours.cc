#include "OcvFindContours.hpp"
#include <vector>
#include <string>
#include <cstdint>

using namespace cv;

OcvFindContoursModel::OcvFindContoursModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  // set reflect_101 as default value
  addParameter<eInt>(EPT_ENUM, "mode", 0, 255, 1);
  _parameters.back()->setDescription("external|list|ccomp|tree|floodfill");
  addParameter<eInt>(EPT_ENUM, "method", 0, 255, 1);
  _parameters.back()->setDescription("none|simple|TC89_L1|TC89_KCOS");

  mat_ = new Mat();
}

void OcvFindContoursModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      int mode = getParameter("mode")->getValueAsEnum();
      int method = getParameter("method")->getValueAsEnum();
      FindContours(mat, *mat_,mode,method+1);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvFindContoursModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvFindContoursModel::FindContours(Mat& src, Mat& dst, int mode, int method)
{
  try {
    std::vector<std::vector<Point>> counters;
    std::vector<Vec4i> hierarchy;

    cv::findContours(src, counters, hierarchy, RETR_LIST, CHAIN_APPROX_NONE);
    dst = Mat(src.rows, src.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < counters.size(); i++) { 
      drawContours(dst, counters, i, Scalar(0,0,255), 1, 8, hierarchy);
    }  
  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
