#include "OcvFindContours.hpp"
#include <QDebug>
#include <cstdint>
#include <string>
#include <vector>

using namespace cv;

constexpr int kMaxDrawContours = 10;

constexpr int kGap = 2;

OcvFindContoursModel::OcvFindContoursModel()
{
  /* input */
  _inputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));
  /* output */
  _outputs.push_back(
      new ePort(PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("cv::mat"), NodeClassMat));

  /* parameter */
  addParameter<eInt>(EPT_ENUM, "mode", 0, 255, 1);
  _parameters.back()->setDescription("external|list|ccomp|tree|floodfill");
  addParameter<eInt>(EPT_ENUM, "method", 0, 255, 1);
  _parameters.back()->setDescription("none|simple|TC89_L1|TC89_KCOS");
  addParameter<bool>(EPT_BOOL, "Draw_Rect", 0, 0, false);

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
      FindContours(mat, *mat_, mode, method + 1);
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
  bool draw_rect = getParameter("Draw_Rect")->getValueAsBool();

  try {
    std::vector<std::vector<Point>> counters;
    std::vector<Vec4i> hierarchy;

    cv::findContours(src, counters, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    dst = Mat(src.rows, src.cols, CV_8UC3, Scalar(0, 0, 0));
    for (int i = 0; i < counters.size() && i < kMaxDrawContours; i++) {
      cv::drawContours(dst, counters, i, Scalar(0, 0, 255), 1, 8, hierarchy);
    }

    if (draw_rect) {
      for (int i = 0; i < counters.size() && i < kMaxDrawContours; i++) {
        // cv::Rect rect = cv::boundingRect(counters[i]);
        // cv::rectangle(dst, rect, Scalar(255, 0, 0));

        cv::RotatedRect rotate_rect = cv::minAreaRect(counters[i]);
        DrawRotatedRectangle(dst, rotate_rect);
      }
    }

  } catch (Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}

int GetDistance(Point point1, Point point2)
{
  int distance = sqrtf(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
  return distance;
}

void OcvFindContoursModel::DrawRotatedRectangle(cv::Mat& src, cv::RotatedRect& rect)
{
  /* Draw rect */
  cv::Scalar color = cv::Scalar(255.0, 255.0, 255.0);  // white

  cv::Point2f vertices2f[4];
  rect.points(vertices2f);

  cv::Point vertices[4];
  for (int i = 0; i < 4; ++i) {
    vertices[i] = vertices2f[i];
  }

  std::vector<cv::Point> contour;
  for (int i = 0; i < 4; i++) contour.push_back(vertices2f[i]);

  std::vector<std::vector<cv::Point>> contours;
  contours.push_back(contour);
  cv::drawContours(src, contours, 0, cv::Scalar(255, 255, 0), 1);

  cv::Scalar color_white = cv::Scalar(255.0, 255.0, 255.0);  // white
  cv::Point point1 = vertices2f[0];
  cv::Point point2 = vertices2f[1];
  cv::Point point3 = vertices2f[3];

  /* Draw point */
  cv::circle(src, point1, 2, cv::Scalar(255, 255, 255));
  cv::circle(src, point2, 2, cv::Scalar(255, 255, 255));
  cv::circle(src, point3, 3, cv::Scalar(255, 255, 255));

  /* Draw line */
  cv::line(src, point1, point2, color_white);
  cv::line(src, point1, point3, color_white);

  int weight = GetDistance(point1, point2);
  int height = GetDistance(point1, point3);
  cv::putText(src, std::to_string(weight), point2, cv::FONT_HERSHEY_PLAIN, 1, color_white);
  cv::putText(src, std::to_string(height), point3, cv::FONT_HERSHEY_PLAIN, 1, color_white);

  /* Show text */
  // cv::CvFont font;
  // cv::cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 1, 2, 8);
  // cv::cvPutText(pImg, "This is a picture named lena!", cvPoint(50, 50), &font, CV_RGB(255, 0,
  // 0));
}
