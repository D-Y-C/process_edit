#include "OcvCvtColorModel.hpp"
#include <OcvData.hpp>
#include <QDebug>
#include <QString>
#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>
#include <memory>
#include <opencv2/opencv.hpp>

OcvCvtColorModel::OcvCvtColorModel()
{
  /* input */
  _inputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));
  /* output */
  _outputs.push_back(new ePort(
      PortType::Out, NODE_DATA_TYPE[NodeClassMat], QString("NodeClassMat"), NodeClassMat));

  /* parameter */
  addParameter<eColor>(EPT_RGBA, "lower", 0, 255, eColor(0, 0, 0));
  addParameter<eColor>(EPT_RGBA, "upper", 0, 255, eColor(255, 255, 255));
  addParameter<int>(EPT_ENUM, "type", 0, 255, 0);
  _parameters.back()->setDescription("RGB2GRAY");

  mat_ = new cv::Mat();
}

void OcvCvtColorModel::process()
{
  OcvData* ocv_data = dynamic_cast<OcvData*>(_inputs[0]->data.get());

  if (ocv_data) {
    cv::Mat mat = ocv_data->GetData()->clone();
    if (!mat.empty()) {
      CvtColor(mat, *mat_);

      dataUpdated(0);
    }
  }
}

std::shared_ptr<NodeData> OcvCvtColorModel::outData(PortIndex idx)
{
  return std::make_shared<OcvData>(mat_);
}

void OcvCvtColorModel::CvtColor(cv::Mat& src, cv::Mat& dst)
{
  cv::Mat result;

  eColor lower = getParameter("lower")->getValueAsColor();
  eColor upper = getParameter("upper")->getValueAsColor();
  cv::ColorConversionCodes conver_code;
  int type = getParameter("type")->getValueAsInt();

  /* clang-format off */
  switch (type) {
    case 0: {conver_code = cv::COLOR_RGB2GRAY; break;}
    default: {
      conver_code = cv::COLOR_RGB2GRAY;
      break;
    }
  }
  /* clang-format on */

  try {
    cv::Mat tmp_mat;
    cv::cvtColor(src, tmp_mat, conver_code);
    //cv::inRange(
    //    tmp_mat, cv::Scalar(lower.r, lower.g, lower.b), cv::Scalar(upper.r, upper.g, upper.b), dst);

  } catch (cv::Exception& e) {
    const char* err_msg = e.what();
    qFatal("opecv exception caught: %s", err_msg);
  }
  return;
}
