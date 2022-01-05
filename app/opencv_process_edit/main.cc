#include <QApplication>
#include <iostream>
#include <opencv2\opencv.hpp>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/NodeData>

#include "OcvCvtColorModel.hpp"
#include "OcvLoaderModel.hpp"
#include "OcvShowModel.hpp"
#include "OcvThresholdModel.hpp"
#include "OcvMorphologyModel.hpp"
#include "OcvResizeModel.hpp"
#include "OcvBilateralFilterModel.hpp"
#include "OcvBlurModel.hpp"
#include "OcvMedianBlurModel.hpp"
#include "OcvGaussianBlurModel.hpp"
#include "OcvFindContours.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;

static std::shared_ptr<DataModelRegistry> registerDataModels();

using namespace cv;

int main(int argc, char* argv[])
{
  /*
        try {
                Mat img = imread("E:\\project\\process_edit\\thirdparty\\opencv\\data\\aloeL.jpg");
     //这个图片需要自己准备，放在project目录下，或者直接写绝对路径 imshow("f22", img);//显示图片6秒
                waitKey(6000);
        }
        catch (cv::Exception& e)
        {
                        const char* err_msg = e.what();
                        std::cout << "exception caught: " << err_msg << std::endl;
        }
  */
  QApplication app(argc, argv);

  FlowScene scene(registerDataModels());

  FlowView view(&scene);

  view.setWindowTitle("Node-based flow editor");
  view.resize(1200, 1200);
  view.show();

  return app.exec();
}

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<OcvShowModel>();
  ret->registerModel<OcvLoaderModel>();
  ret->registerModel<OcvThresholdModel>();
  ret->registerModel<OcvCvtColorModel>();
  ret->registerModel<OcvMophologyModel>();
  ret->registerModel<OcvResizeModel>();
//  ret->registerModel<OcvBilateralFilterModel>();
  ret->registerModel<OcvBlurModel>();
  ret->registerModel<OcvGaussianBlurModel>();
//  ret->registerModel<OcvMedianBlurModel>();
  ret->registerModel<OcvFindContoursModel>();

  return ret;
}

