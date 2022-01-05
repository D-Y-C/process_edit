#pragma once

#include <QImage>
#include <opencv2/opencv.hpp> 
#include <nodes/NodeDataModel>
#include <QDebug>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class OcvData : public NodeData
{
 public:
  OcvData() {}

  OcvData(cv::Mat* image) : mat_ptr_(image) {}

  NodeDataType type() const override
  {
    //  id  name
    return {"mat", "cv::mat"};
  }

  cv::Mat* GetData() const { return mat_ptr_; }

  static void CvMatToQImage(const cv::Mat &inMat,QImage& image)
  {
    switch (inMat.type()) {
      // 8-bit, 4 channel
      case CV_8UC4: {
        image = QImage(inMat.data,
                     inMat.cols,
                     inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_ARGB32);
        break;
      }

      // 8-bit, 3 channel
      case CV_8UC3: {
        image = QImage(inMat.data,
                     inMat.cols,
                     inMat.rows,
                     static_cast<int>(inMat.step),
                     QImage::Format_RGB888);
        image = image.rgbSwapped();
        break;
        ;
      }
      // 8-bit, 1 channel
      case CV_8UC1: {
        image = QImage(
            inMat.data,
            inMat.cols,
            inMat.rows,
            static_cast<int>(inMat.step),
            QImage::Format_Grayscale8);  // Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
        break;;
      }

      default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:"
                   << inMat.type();
        break;
    }

    return;
  }


 private:
  cv::Mat* mat_ptr_;
};
