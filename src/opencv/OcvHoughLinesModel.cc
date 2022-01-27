#include "OcvHoughLinesModel.h"
#include <vector>

OcvHoughLinesModel::OcvHoughLinesModel()
{
  /* input */
  _inputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));
  /* output */
  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));

  addParameter<float>(EPT_FLOAT, "rho", 0, 999, 1);
  addParameter<float>(EPT_FLOAT, "theta", 0, 360, 1);
  addParameter<float>(EPT_FLOAT, "threshold", 0, 999, 1);
  addParameter<bool>(EPT_BOOL, "draw_lines", 0, 0, false);

  mat_ = new cv::Mat();
}

void OcvHoughLinesModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      HoughLines(mat, *mat_);
      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvHoughLinesModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvHoughLinesModel::HoughLines(cv::Mat& src, cv::Mat& dst)
{
  float rho = getParameter("rho")->getValueAsFloat();
  float theta = getParameter("theta")->getValueAsFloat();
  float threshold = getParameter("threshold")->getValueAsFloat();
  bool draw_lines = getParameter("draw_lines")->getValueAsBool();

  try {
    if (src.channels() == 1) {
      std::vector<cv::Vec2f> lines;
      cv::HoughLines(src, lines, rho, CV_PI / theta, threshold);
      dst = src;
      if (draw_lines) {
        for (size_t i = 0; i < lines.size(); i++) {
          float rho = lines[i][0];    //就是圆的半径r
          float theta = lines[i][1];  //就是直线的角度
          cv::Point pt1, pt2;
          double a = cos(theta), b = sin(theta);
          double x0 = a * rho, y0 = b * rho;
          pt1.x = cvRound(x0 + 1000 * (-b));
          pt1.y = cvRound(y0 + 1000 * (a));
          pt2.x = cvRound(x0 - 1000 * (-b));
          pt2.y = cvRound(y0 - 1000 * (a));

          cv::line(dst, pt1, pt2, cv::Scalar(55, 100, 195), 1, cv::LINE_AA);
        }
      }
    } else {
    }
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
}
