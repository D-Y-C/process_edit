#include <opencv2\opencv.hpp>

using namespace cv;

int TemplateMatch(const cv::Mat& src,const cv::Mat& temp, cv::Mat& dst)
{
  cv::Mat result;
  int result_cols = src.cols - temp.cols + 1;
  int result_rows = src.rows - temp.rows + 1;


  result.create(result_cols, result_rows, CV_32FC1);
  cv::matchTemplate(src, temp, result, cv::TemplateMatchModes::TM_SQDIFF_NORMED);
  cv::normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

  double min_val = -1;
  double max_val;
  cv::Point min_loc;
  cv::Point max_loc;
  cv::Point match_loc;

  cv::minMaxLoc(result, &min_val, &min_val, &min_loc, &max_loc, Mat());
  std::cout << "suitability" << min_val << std::endl;

  match_loc = min_loc;

  dst = src;
  cv::rectangle(dst,
                match_loc,
                cv::Point(match_loc.x + temp.cols, match_loc.y + temp.rows),
                cv::Scalar(0, 255, 0),
                2,
                8,
                0);


  return 0;
}

void show_test(const Mat& src,Mat& det)
{
  det = src.clone();
}

int EdgeDetectionTest(cv::Mat& src,cv::Mat& dst)
{
  if (src.empty()) return -1;
  Mat src_gray, src_blur;
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  blur(src_gray, src_blur, Size(3, 3));
  Canny(src_blur, dst, 30, 200);
  return 0;
}

int main(int argc, char* argv[])
{
  try {
    Mat img = imread("E:\\project\\process_edit\\data\\nba.jpg");
    cv::Mat temp = imread("E:\\project\\process_edit\\data\\76.png");
    cv::Mat dst;
    
    //这个图片需要自己准备，放在project目录下，或者直接写绝对路径 imshow("f22", img);//显示图片6秒
    /*
    {
      std::vector<cv::Mat> planes;
      // split image onto the color planes.
      //
      cv::split(img, planes);
      cv::Mat b = planes[0], g = planes[1], r = planes[2], s;
      // Add equally weighted rgb values.
      //
      cv::addWeighted(r, 1. / 3., g, 1. / 3., 0.0, s);
      cv::addWeighted(s, 1., b, 1. / 3., 0.0, s);
      dst = s;

    }
    */

   //TemplateMatch(img,temp,dst);
    EdgeDetectionTest(img,dst);
        //    show_test(img,det);
    imshow("f22", dst);  //显示图片6秒
  //  waitKey(6000);
    waitKey(0);
  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    std::cout << "exception caught: " << err_msg << std::endl;
  }
}